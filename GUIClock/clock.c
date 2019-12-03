#include <stdio.h>
#include <math.h>

#include <time.h>
#include <sys/time.h>

#include <GL/glut.h>

#define FPS 60

void Display(void);
void Reshape(int, int);
void Timer(int);
void drawCircle(double, double, double, int);
void drawGear(double, double, double, double, double, int);
void drawHand(double, double, double, double);
void drawPendulum(double, double, double, double);

double start_time;
double hour = 0;
double min = 0;
double sec = 0;
double t = 0;

int main(int argc, char *argv[]) {
    // 開始時間を取得
    struct timeval tv;
    gettimeofday(&tv, NULL);
    start_time = tv.tv_sec + tv.tv_usec * 1e-6;

    // 初期化・設定
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Mechanical Clock");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // アンチエイリアスを有効
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

    glutTimerFunc(1000.0 / FPS, Timer, 0);
    glutMainLoop();

    return 0;
}

void Display(void) {
    // 中心座標
    double x0 = 0;
    double y0 = 0.4;

    // 針の長さ
    double lh = 0.35;
    double lm = 0.4;
    double ls = 0.45;

    // 針の角度
    double ah = -2 * M_PI * hour / 12 + M_PI_2;
    double am = -2 * M_PI * min / 60 + M_PI_2;
    double as = -2 * M_PI * sec / 60 + M_PI_2;

    // 歯の長さ
    double l = 0.01;

    // 歯車の大きさ
    double r = 0.02;
    double r1 = r * 10;
    double r2 = r * 2 * sqrt(15);
    double r3 = r * 2 * sqrt(15);
    double r4 = r * 6;
    double rg = r * 5;
    double rp = r * 50;

    // 歯車の角速度
    double w1 = 2 * M_PI / 3600;
    double w2 = -2 * M_PI / 3600;
    double w3 = 2 * M_PI / (120 * sqrt(15));
    double w4 = -2 * M_PI / 60;
    double wg = 2 * M_PI / 12;
    double wp = 2 * M_PI;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0, 0, 0);

    // 針描画
    drawHand(x0, y0, lh, ah);
    drawHand(x0, y0, lm, am);
    drawHand(x0, y0, ls, as);

    // 歯車描画
    drawCircle(x0, y0, 0.5, 100);

    drawGear(x0 - r1 - r, y0, t * w1, r1, l, 80);
    drawGear(x0 - r1 - r, y0, t * w1, r, l, 8);

    drawGear(x0, y0, t * w2, r2, l, 62);
    drawGear(x0, y0, t * w2, r, l, 8);

    drawGear(x0, y0 - r3 - r, t * w3, r3, l, 62);
    drawGear(x0, y0 - r3 - r, t * w3, r, l, 8);

    drawGear(x0, y0, t * w4, r4, l, 48);
    drawGear(x0, y0, t * w4, r, l, 8);

    drawGear(x0, y0 + r4 + r, t * wg, rg, l, 20);
    drawGear(x0, y0 + r4 + r, t * wg, r, l, 8);

    drawPendulum(x0, y0 + r4 + rg + r, rp, 3 * M_PI_2 + 0.2 * sin(t * wp));

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
    struct tm *t_st;

    glutTimerFunc(1000.0 / FPS, Timer, 0);

    // 時刻を取得
    gettimeofday(&tv, NULL);
    t_st = localtime(&tv.tv_sec);

    sec = t_st->tm_sec + tv.tv_usec * 1e-6;
    min = t_st->tm_min + sec / 60;
    hour = t_st->tm_hour + min / 60;

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

void drawHand(double x, double y, double r, double a) {
    glBegin(GL_LINES);
    glVertex2d(x, y);
    glVertex2d(x + r * cos(a), y + r * sin(a));
    glEnd();
}

void drawPendulum(double x, double y, double r, double a) {
    glBegin(GL_LINES);
    glVertex2d(x, y);
    glVertex2d(x + r * cos(a), y + r * sin(a));
    glEnd();

    drawCircle(x + r * cos(a), y + r * sin(a), 0.1, 100);
}
