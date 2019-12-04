#include <stdio.h>
#include <math.h>

#include <time.h>
#include <sys/time.h>

#include <GL/glut.h>
//#include <GL/glpng.h>

#define FPS 60

void Display(void);
void Reshape(int, int);
void Timer(int);
void drawCircle(double, double, double, int);
void drawGear(double, double, double, double, double, int);
void drawKana(double, double, double, double, double, int);
void drawGangi(double, double, double, double, double, int);
void drawHand(double, double, double, double);
void drawPendulum(double, double, double, double);
//void putSprite(GLuint, double, double, pngInfo *);

// 時刻
long double t;

// 画像
//GLuint dial_img;
//pngInfo dial_info;

int main(int argc, char *argv[]) {
    // 画像読み込み
    //dial_img = pngBind("images/dial.png", PNG_NOMIPMAP, PNG_ALPHA, &dial_info, GL_CLAMP, GL_NEAREST, GL_NEAREST);

    // アンチエイリアスを有効化
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    // 初期化・設定
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Mechanical Clock");
    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);

    Timer(0);
    glutMainLoop();

    return 0;
}

void Display(void) {
    time_t tv_sec = (int)t;
    struct tm *t_st = localtime(&tv_sec);

    int tictac = (t - (int)t) * 2;
    double decimal = (t - (int)t) * 2 - tictac;
    double tp = (int)t + (pow(decimal, 5) + tictac) / 2;

    double sec = t_st->tm_sec + tp - (int)t;
    double min = t_st->tm_min + sec / 60;
    double hour = t_st->tm_hour + min / 60;

    // 中心座標
    double x0 = 0;
    double y0 = 0.3;

    // 針の長さ
    double lh = 0.4;
    double lm = 0.45;
    double ls = 0.55;

    // 針の角度
    double ah = -2 * M_PI * hour / 12 + M_PI_2;
    double am = -2 * M_PI * min / 60 + M_PI_2;
    double as = -2 * M_PI * sec / 60 + M_PI_2;

    // 歯の長さ
    double l = 0.01;

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
    double rp = r * 40;

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

    glClear(GL_COLOR_BUFFER_BIT);

    drawPendulum(x0, y0 + r4 + rg + r + 0.01, rp, 3 * M_PI_2 + 0.1 * sin(t * wp));

    // 歯車描画
    glColor3ub(0, 0, 0);
    drawCircle(x0, y0, 0.6, 100);

    glColor3ub(200, 200, 200);
    drawGear(x0 + r0 + r, y0, tp * w0, r0, l, n0);
    drawGear(x0 + r0 + r, y0, tp * w0, r, l, n);

    drawGangi(x0, y0 + r4 + r, tp * wg, rg, 0.02, ng);
    drawGear(x0, y0 + r4 + r, tp * wg, r, l, n);

    drawGear(x0, y0, tp * w4, r4, l, n4);
    drawGear(x0, y0, tp * w4, r, l, n);

    drawGear(x0, y0 - r3 - r, tp * w3, r3, l, n3);
    drawGear(x0, y0 - r3 - r, tp * w3, r, l, n);

    drawGear(x0, y0, tp * w2, r2, l, n2);
    drawGear(x0, y0, tp * w2, r, l, n);

    drawGear(x0 - r1 - r, y0, tp * w1, r1, l, n1);
    drawGear(x0 - r1 - r, y0, tp * w1, r, l, n);

    drawGear(x0 + r5 + r, y0, tp * w5, r5, l, n5);
    drawGear(x0 + r5 + r, y0, tp * w5, r, l, n);

    drawGear(x0, y0, tp * w6, r6, l, n6);
    drawGear(x0, y0, tp * w6, r, l, n);

    // 針描画
    glColor3ub(0, 0, 0);
    drawHand(x0, y0, lh, ah);
    drawHand(x0, y0, lm, am);
    drawHand(x0, y0, ls, as);

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
    glutTimerFunc(1000.0 / FPS, Timer, 0);
    gettimeofday(&tv, NULL);
    t = tv.tv_sec + tv.tv_usec * 1e-6;

    Display();
}

// 正円を描画
void drawCircle(double x, double y, double r, int n) {
    int i;

    glBegin(GL_LINE_LOOP);

    for (i = 0; i < n; i++) {
        double theta = 2 * M_PI * i / n;
        glVertex2d(x + r * sin(theta), y + r * cos(theta));
    }

    glEnd();
}

// 歯車
void drawGear(double x, double y, double a, double r, double l, int n) {
    int i;
    double w = M_PI / n;
    double ws = 2 * M_PI / 5;
    GLfloat color[4];

    // 現在の色を取得
    glGetFloatv(GL_CURRENT_COLOR, color);

    // 円
    glBegin(GL_QUAD_STRIP);

    for (i = 0; i <= n * 2; i += 2) {
        glVertex2d(x + (r - l * 1.5) * cos(i * w + a), y + (r - l * 1.5) * sin(i * w + a));
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
    }

    glEnd();
    glBegin(GL_POLYGON);

    for (i = 0; i < n * 2; i++) {
        double theta = 2 * M_PI * i / n;
        glVertex2d(x + r * 0.2 * sin(theta), y + r * 0.2 * cos(theta));
    }

    glEnd();

    // 歯
    glColor3fv(color);
    glBegin(GL_QUADS);

    for (i = 0; i < n * 2; i += 2) {
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
        glVertex2d(x + (r - l / 2) * cos(i * w + a) + l * cos((i + 0.5) * w + a), y + (r - l / 2) * sin(i * w + a) + l * sin((i + 0.5) * w + a));
        glVertex2d(x + (r - l / 2) * cos((i + 1) * w + a) + l * cos((i + 0.5) * w + a), y + (r - l / 2) * sin((i + 1) * w + a) + l * sin((i + 0.5) * w + a));
        glVertex2d(x + (r - l / 2) * cos((i + 1) * w + a), y + (r - l / 2) * sin((i + 1) * w + a));
    }

    glEnd();

    // 縁線
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);

    for (i = 0; i < n * 2; i++) {
        double theta = 2 * M_PI * i / n;
        glVertex2d(x + r * 0.2 * sin(theta), y + r * 0.2 * cos(theta));
    }

    glEnd();
    drawCircle(x, y, r - l * 1.5, n);
    glBegin(GL_LINE_LOOP);

    for (i = 0; i < 2 * n; i++) {
        if (i % 2) {
            glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
            glVertex2d(x + (r - l / 2) * cos((i + 1) * w + a), y + (r - l / 2) * sin((i + 1) * w + a));
        } else {
            glVertex2d(x + (r - l / 2) * cos(i * w + a) + l * cos((i + 0.5) * w + a), y + (r - l / 2) * sin(i * w + a) + l * sin((i + 0.5) * w + a));
            glVertex2d(x + (r - l / 2) * cos((i + 1) * w + a) + l * cos((i + 0.5) * w + a), y + (r - l / 2) * sin((i + 1) * w + a) + l * sin((i + 0.5) * w + a));
        }
    }

    // 骨組み
    glEnd();
    glColor3fv(color);
    glBegin(GL_QUADS);

    for (i = 0; i < 5; i++) {
        glVertex2d(x + r * 0.07 * sin(i * ws + a), y - r * 0.07 * cos(i * ws + a));
        glVertex2d(x - r * 0.07 * sin(i * ws + a), y + r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l) * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + (r - l) * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l) * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + (r - l) * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
    }

    glEnd();
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);

    for (i = 0; i < 5; i++) {
        glVertex2d(x + r * 0.2 * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + r * 0.2 * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l * 1.5) * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + (r - l * 1.5) * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
        glVertex2d(x + r * 0.2 * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + r * 0.2 * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l * 1.5) * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + (r - l * 1.5) * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
    }

    glEnd();
    glColor3fv(color);
}

// カナ(小さい歯車)
void drawKana(double x, double y, double a, double r, double l, int n) {
    int i;
    double w = M_PI / n;

    drawCircle(x, y, r - l / 2, n * 2);

    glBegin(GL_QUADS);

    for (i = 0; i < n * 2; i += 2) {
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
        glVertex2d(x + (r - l / 2) * cos(i * w + a) + l * cos((i + 0.5) * w + a), y + (r - l / 2) * sin(i * w + a) + l * sin((i + 0.5) * w + a));
        glVertex2d(x + (r - l / 2) * cos((i + 1) * w + a) + l * cos((i + 0.5) * w + a), y + (r - l / 2) * sin((i + 1) * w + a) + l * sin((i + 0.5) * w + a));
        glVertex2d(x + (r - l / 2) * cos((i + 1) * w + a), y + (r - l / 2) * sin((i + 1) * w + a));
    }

    glEnd();

    glBegin(GL_LINE_LOOP);

    for (i = 0; i < 2 * n; i++) {
        if (i % 2) {
            glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
            glVertex2d(x + (r - l / 2) * cos((i + 1) * w + a), y + (r - l / 2) * sin((i + 1) * w + a));
        } else {
            glVertex2d(x + (r - l / 2) * cos(i * w + a) + l * cos((i + 0.5) * w + a), y + (r - l / 2) * sin(i * w + a) + l * sin((i + 0.5) * w + a));
            glVertex2d(x + (r - l / 2) * cos((i + 1) * w + a) + l * cos((i + 0.5) * w + a), y + (r - l / 2) * sin((i + 1) * w + a) + l * sin((i + 0.5) * w + a));
        }
    }

    glEnd();
}

// ガンギ車 
void drawGangi(double x, double y, double a, double r, double l, int n) {
    int i;
    double w = -2 * M_PI / n;
    float color[4];

    // 現在の色を取得
    glGetFloatv(GL_CURRENT_COLOR, color);

    // 円
    glBegin(GL_QUAD_STRIP);

    for (i = 0; i <= n; i++) {
        glVertex2d(x + (r - l * 1.5) * cos(i * w + a), y + (r - l * 1.5) * sin(i * w + a));
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
    }

    glEnd();

    // 歯
    glBegin(GL_TRIANGLES);

    for (i = 0; i < n; i++) {
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
        glVertex2d(x + (r + l / 2) * cos(i * w + a), y + (r + l / 2) * sin(i * w + a));
        glVertex2d(x + (r - l / 2) * cos((i + 1) * w + a), y + (r - l / 2) * sin((i + 1) * w + a));
    }

    glEnd();

    // 縁線
    glColor3ub(0, 0, 0);
    drawCircle(x, y, r - l * 1.5, n);
    glBegin(GL_LINE_LOOP);

    for (i = 0; i < n; i++) {
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
        glVertex2d(x + (r + l / 2) * cos(i * w + a), y + (r + l / 2) * sin(i * w + a));
    }

    glEnd();
    glColor3fv(color);
}

// 針
void drawHand(double x, double y, double r, double a) {
    glBegin(GL_LINES);
    glVertex2d(x, y);
    glVertex2d(x + r * cos(a), y + r * sin(a));
    glEnd();
}

// 振り子
void drawPendulum(double x, double y, double r, double a) {
    // 棒
    glBegin(GL_LINES);
    glVertex2d(x - 0.1 * cos(a), y - 0.1 * sin(a));
    glVertex2d(x + r * cos(a), y + r * sin(a));
    glEnd();

    // 重り
    drawCircle(x + (r + 0.1) * cos(a), y + (r + 0.1) * sin(a), 0.1, 100);

    // アンクル
    glBegin(GL_LINE_STRIP);
    glVertex2d(x - 0.08 * sin(a) + 0.02 * cos(a), y + 0.08 * cos(a) + 0.02 * sin(a));
    glVertex2d(x - 0.08 * sin(a), y + 0.08 * cos(a));
    glVertex2d(x + 0.08 * sin(a), y - 0.08 * cos(a));
    glVertex2d(x + 0.08 * sin(a) + 0.02 * cos(a), y - 0.08 * cos(a) + 0.02 * sin(a));
    glEnd();
}

// 画像表示
/*void putSprite(GLuint num, double x, double y, pngInfo *info) { 
    int w = info->Width;
    int h = info->Height;

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, num);
    glColor4ub(255, 255, 255, 255);

    glBegin(GL_QUADS);
    
    glTexCoord2i(0, 0);
    glVertex2d(x, y);
    
    glTexCoord2i(0, 1);
    glVertex2d(x, y + h);
    
    glTexCoord2i(1, 0);
    glVertex2d(x + w, y + h);
    
    glTexCoord2i(1, 1);
    glVertex2d(x + w, y);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}*/