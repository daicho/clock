#include <stdio.h>
#include <math.h>

#include <time.h>
#include <sys/time.h>

#include <GL/glut.h>
#include <GL/glpng.h>

#include "clock.h"
#include "shape.h"

#define FPS    60   // フレームレート
#define ASPECT 0.75 // アスペクト比(幅/高さ)

// プロトタイプ宣言
void Display(void);
void Reshape(int, int);
void Timer(int);

// 現在の時刻
long double t;

// 画像
GLuint dial_img;
pngInfo dial_info;

int main(int argc, char *argv[]) {
    // 初期化
    glutInit(&argc, argv);
    glutInitWindowSize(540, 720);
    glutCreateWindow("Mechanical Clock");
    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(0.9, 0.9, 0.9, 1.0);

    // 混合処理を有効化
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // 線のアンチエイリアスを有効化
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // 画像読み込み
    dial_img = pngBind("images/dial.png", PNG_NOMIPMAP, PNG_ALPHA, &dial_info, GL_CLAMP, GL_NEAREST, GL_NEAREST);

    // コールバック関数登録
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutTimerFunc(1000.0 / FPS + 0.5, Timer, 0);

    // メインループ開始
    glutMainLoop();

    return 0;
}

// 画面描画
void Display(void) {
    // 振り子の周期 (Beats/Second)
    double bps = 2;

    // 振り子の運動に合わせて時刻が変化するように数値変換
    time_t t_sec = (time_t)t;
    long double t_usec = t - t_sec;
    double map = t_usec * bps;
    double tt = t_sec + (pow(map - (int)map, 6) + (int)map) / bps;

    // 時・秒・分を取得
    struct tm *t_st = localtime(&t_sec);
    double sec = t_st->tm_sec + tt - t_sec;
    double min = t_st->tm_min + sec / 60;
    double hour = t_st->tm_hour + min / 60;

    // 時計の中心座標
    double x0 = 0;
    double y0 = 0.32;

    // 針の長さ
    double lh = 0.45;
    double lm = 0.56;
    double ls = 0.565;

    // 針の角度
    double ah = -2 * M_PI * hour / 12 + M_PI_2;
    double am = -2 * M_PI * min / 60 + M_PI_2;
    double as = -2 * M_PI * sec / 60 + M_PI_2;

    // 歯の長さ
    double l = 0.01;  // 普通の歯車
    double lg = 0.02; // ガンギ車

    // カナを1とした時のギア比
    double p0 = 9;    // 0番車
    double p1 = 8;    // 1番車
    double p2 = 7.75; // 2番車
    double p3 = 7.75; // 3番車
    double p4 = 6;    // 4番車
    double p5 = 3.5;  // 5番車
    double p6 = 3.5;  // 6番車
    double pg = 5;    // ガンギ車

    // 半径
    double rk = 0.03;    // カナ
    double r0 = rk * p0; // 0番車
    double r1 = rk * p1; // 1番車
    double r2 = rk * p2; // 2番車
    double r3 = rk * p3; // 3番車
    double r4 = rk * p4; // 4番車
    double r5 = rk * p5; // 5番車
    double r6 = rk * p6; // 6番車
    double rg = rk * pg; // ガンギ車
    double rp = 1.45;    // 振り子

    // 歯数
    int nk = 8;             // カナ
    int n0 = nk * p0 + 0.5; // 0番車
    int n1 = nk * p1 + 0.5; // 1番車
    int n2 = nk * p2 + 0.5; // 2番車
    int n3 = nk * p3 + 0.5; // 3番車
    int n4 = nk * p4 + 0.5; // 4番車
    int n5 = nk * p5 + 0.5; // 5番車
    int n6 = nk * p6 + 0.5; // 6番車
    int ng = 20;            // ガンギ車

    // 角速度
    double wp = M_PI * bps;  // 振り子
    double wg = wp / ng * 2; // ガンギ車
    double w4 = wg / -p4;    // 4番車
    double w3 = w4 / -p3;    // 3番車
    double w2 = w3 / -p2;    // 2番車
    double w1 = w2 / -p1;    // 1番車
    double w0 = w2 / -p0;    // 0番車
    double w5 = w2 / -p5;    // 5番車
    double w6 = w5 / -p6;    // 6番車

    // 位相
    double a0 = M_PI / n0; // 0番車
    double a1 = M_PI / n1; // 1番車
    double a2 = 0;         // 2番車
    double a3 = 0;         // 3番車
    double a4 = 0;         // 4番車
    double a5 = M_PI / 4;  // 5番車
    double a6 = M_PI / 4;  // 6番車
    double ag = M_PI / 8;  // ガンギ車
    double ap = 0.5;       // 振り子

    // 色
    GLubyte backColor[3] = {10, 10, 40};       // 時計の背景
    GLubyte gearColor[3] = {219, 180, 20};     // 歯車
    GLubyte pendulumColor[3] = {219, 180, 20}; // 振り子
    GLubyte handColor[3] = {142, 145, 154};    // 針
    GLubyte axisColor[3] = {0, 0, 0};          // 軸

    // 背景をクリア
    glClear(GL_COLOR_BUFFER_BIT);

    // 時計の背景
    glColor3ubv(backColor);
    drawPolygon(x0, y0, 0, 0.55, 6);

    // 振り子
    glColor3ubv(pendulumColor);
    drawPendulum(x0, y0 + r4 + rg + rk + 0.047, -M_PI_2 + 0.08 * sin(t * wp + ap), rp);
    glColor3ubv(axisColor);
    drawPolygon(x0, y0 + r4 + rg + rk + 0.047, 0, 0.008, 20);

    // ガンギ車
    glColor3ubv(gearColor);
    drawGangi(x0, y0 + r4 + rk, tt * wg + ag, rg, lg, ng);
    drawKana(x0, y0 + r4 + rk, tt * wg + ag, rk, l, nk);
    glColor3ubv(axisColor);
    drawPolygon(x0, y0 + r4 + rk, 0, 0.012, 20);

    // 4番車
    glColor3ubv(gearColor);
    drawGear(x0, y0, tt * w4 + a4, r4, l, n4);
    drawKana(x0, y0, tt * w4 + a4, rk, l, nk);

    // 0番車
    glColor3ubv(gearColor);
    drawGear(x0 + r0 + rk, y0, tt * w0 + a0, r0, l, n0);
    drawKana(x0 + r0 + rk, y0, tt * w0 + a0, rk, l, nk);
    glColor3ubv(axisColor);
    drawPolygon(x0 + r0 + rk, y0, 0, 0.012, 20);

    // 3番車
    glColor3ubv(gearColor);
    drawGear(x0, y0 - r3 - rk, tt * w3 + a3, r3, l, n3);
    drawKana(x0, y0 - r3 - rk, tt * w3 + a3, rk, l, nk);
    glColor3ubv(axisColor);
    drawPolygon(x0, y0 - r3 - rk, 0, 0.012, 20);

    // 2番車
    glColor3ubv(gearColor);
    drawGear(x0, y0, tt * w2 + a2, r2, l, n2);
    drawKana(x0, y0, tt * w2 + a2, rk, l, nk);

    // 1番車
    glColor3ubv(gearColor);
    drawGear(x0 - r1 - rk, y0, tt * w1 + a1, r1, l, n1);
    drawKana(x0 - r1 - rk, y0, tt * w1 + a1, rk, l, nk);
    glColor3ubv(axisColor);
    drawPolygon(x0 - r1 - rk, y0, 0, 0.012, 20);

    // 5番車
    glColor3ubv(gearColor);
    drawGear(x0 + r5 + rk, y0, tt * w5 + a5, r5, l, n5);
    drawKana(x0 + r5 + rk, y0, tt * w5 + a5, rk, l, nk);
    glColor3ubv(axisColor);
    drawPolygon(x0 + r5 + rk, y0, 0, 0.012, 20);

    // 6番車
    glColor3ubv(gearColor);
    drawGear(x0, y0, tt * w6 + a6, r6, l, n6);
    drawKana(x0, y0, tt * w6 + a6, rk, l, nk);

    // 文字盤
    putSprite(dial_img, x0 - 0.6, y0 - 0.6, 1.2, 1.2, &dial_info);

    // 針
    glColor3ubv(handColor);
    drawHour(x0, y0, ah, lh);
    drawMinute(x0, y0, am, lm);
    drawSecond(x0, y0, as, ls);
    glColor3ubv(gearColor);
    drawPolygon(x0, y0, 0, 0.012, 20);

    glFlush();
}

// ウィンドウサイズ変更
void Reshape(int w, int h) {
    // ウィンドウの縦横比
    double ratio = (double)w / h;

    // 座標系再設定
    glViewport(0, 0, w, h);
    glLoadIdentity();

    if (ratio > ASPECT)
        gluOrtho2D(-ratio, ratio, -1, 1);
    else
        gluOrtho2D(-ASPECT, ASPECT, -ASPECT / ratio, ASPECT / ratio);
}

// タイマー
void Timer(int value) {
    struct timeval tv;

    // 次のタイマーを登録
    glutTimerFunc(1000.0 / FPS + 0.5, Timer, 0);

    // 時刻を取得
    gettimeofday(&tv, NULL);
    t = tv.tv_sec + tv.tv_usec * 1e-6;

    Display();
}
