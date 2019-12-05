#include <stdio.h>
#include <math.h>

#include <time.h>
#include <sys/time.h>

#include <GL/glut.h>
#include <GL/glpng.h>

#include "clock.h"
#include "shape.h"

#define FPS 60

void Display(void);
void Reshape(int, int);
void Timer(int);

// 時刻
long double t;
long double st;

// 画像
GLuint dial_img;
pngInfo dial_info;

int main(int argc, char *argv[]) {
    // 初期化
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Mechanical Clock");
    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // アンチエイリアスを有効化
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    // 画像読み込み
    dial_img = pngBind("images/dial.png", PNG_NOMIPMAP, PNG_ALPHA, &dial_info, GL_CLAMP, GL_NEAREST, GL_NEAREST);

    // 開始
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    Timer(0);
    st = t;
    glutMainLoop();

    return 0;
}

void Display(void) {
    long double tt = st + (t - st) * 1;

    time_t tv_sec = (int)tt;
    struct tm *t_st = localtime(&tv_sec);

    int tictac = (tt - (int)tt) * 2;
    double decimal = (tt - (int)tt) * 2 - tictac;
    double tp = (int)tt + (pow(decimal, 6) + tictac) / 2;

    double sec = t_st->tm_sec + tp - (int)tt;
    double min = t_st->tm_min + sec / 60;
    double hour = t_st->tm_hour + min / 60;

    // 中心座標
    double x0 = 0;
    double y0 = 0.3;

    // 針の長さ
    double lh = 0.45;
    double lm = 0.51;
    double ls = 0.57;

    // 針の角度
    double ah = -2 * M_PI * hour / 12 + M_PI_2;
    double am = -2 * M_PI * min / 60 + M_PI_2;
    double as = -2 * M_PI * sec / 60 + M_PI_2;

    // 歯の長さ
    double l = 0.01;
    double lg = 0.02;

    // カナを1とした時のギア比
    double p0 = 9;
    double p1 = 8;
    double p2 = 7.75;
    double p3 = 7.75;
    double p4 = 6;
    double p5 = 3.5;
    double p6 = 3.5;
    double pg = 5;

    // 歯車の大きさ
    double r = 0.03;
    double r0 = r * p0;
    double r1 = r * p1;
    double r2 = r * p2;
    double r3 = r * p2;
    double r4 = r * p4;
    double r5 = r * p5;
    double r6 = r * p6;
    double rg = r * pg;
    double rp = r * 48;

    // ギア数
    double n = 8;
    double n0 = (int)(n * p0 + 0.5);
    double n1 = (int)(n * p1 + 0.5);
    double n2 = (int)(n * p2 + 0.5);
    double n3 = (int)(n * p3 + 0.5);
    double n4 = (int)(n * p4 + 0.5);
    double n5 = (int)(n * p5 + 0.5);
    double n6 = (int)(n * p6 + 0.5);
    double ng = 20;

    // 歯車の角速度
    double wp = 2 * M_PI;
    double wg = wp / (ng / 2);
    double w4 = wg / -p4;
    double w3 = w4 / -p3;
    double w2 = w3 / -p2;
    double w1 = w2 / -p1;
    double w0 = w2 / -p0;
    double w5 = w2 / -p5;
    double w6 = w5 / -p6;

    // 歯車の位相
    double a0 = M_PI / n0;
    double a1 = M_PI / n1;
    double a2 = 0;
    double a3 = 0;
    double a4 = M_PI / n4;
    double a5 = M_PI / 4;
    double a6 = M_PI / 4;
    double ag = 0;
    double ap = 0.5;

    // 描画
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(200, 200, 200);
    drawPendulum(x0, y0 + r4 + rg + r + 0.050, rp, -M_PI_2 + M_PI / 40 * sin(tt * wp + ap));
    drawPolygon(x0, y0 + r4 + rg + r + 0.050, 0, 0.008, 20);

    drawGangi(x0, y0 + r4 + r, tp * wg + ag, rg, lg, ng);
    drawKana(x0, y0 + r4 + r, tp * wg + ag, r, l, n);
    drawPolygon(x0, y0 + r4 + r, 0, 0.012, 20);

    drawGear(x0, y0, tp * w4 + a4, r4, l, n4);
    drawKana(x0, y0, tp * w4 + a4, r, l, n);

    drawGear(x0 + r0 + r, y0, tp * w0 + a0, r0, l, n0);
    drawKana(x0 + r0 + r, y0, tp * w0 + a0, r, l, n);
    drawPolygon(x0 + r0 + r, y0, 0, 0.012, 20);

    drawGear(x0, y0 - r3 - r, tp * w3 + a3, r3, l, n3);
    drawKana(x0, y0 - r3 - r, tp * w3 + a3, r, l, n);
    drawPolygon(x0, y0 - r3 - r, 0, 0.012, 20);

    drawGear(x0, y0, tp * w2 + a2, r2, l, n2);
    drawKana(x0, y0, tp * w2 + a2, r, l, n);

    drawGear(x0 - r1 - r, y0, tp * w1 + a1, r1, l, n1);
    drawKana(x0 - r1 - r, y0, tp * w1 + a1, r, l, n);
    drawPolygon(x0 - r1 - r, y0, 0, 0.012, 20);

    putSprite(dial_img, x0 - 0.6, y0 - 0.6, 1.2, 1.2, &dial_info);

    drawGear(x0 + r5 + r, y0, tp * w5 + a5, r5, l, n5);
    drawKana(x0 + r5 + r, y0, tp * w5 + a5, r, l, n);
    drawPolygon(x0 + r5 + r, y0, 0, 0.012, 20);

    drawGear(x0, y0, tp * w6 + a6, r6, l, n6);
    drawKana(x0, y0, tp * w6 + a6, r, l, n);

    // 針描画
    glColor3ub(255, 255, 255);
    drawHand(x0, y0, lh, ah);
    drawHand(x0, y0, lm, am);
    drawHand(x0, y0, ls, as);
    drawPolygon(x0, y0, 0, 0.012, 20);

    glFlush();
}

void Reshape(int w, int h) {
    // 座標系再設定
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (w > h)
        gluOrtho2D((double)w / -h, (double)w / h, -1, 1);
    else
        gluOrtho2D(-1, 1, (double)h / -w, (double)h / w);
}

// タイマー
void Timer(int value) {
    struct timeval tv;

    // 時刻を取得
    glutTimerFunc(1000.0 / FPS + 0.5, Timer, 0);
    gettimeofday(&tv, NULL);
    t = tv.tv_sec + tv.tv_usec * 1e-6;

    Display();
}
