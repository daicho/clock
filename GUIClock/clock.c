#include <stdio.h>
#include <math.h>

#include <time.h>
#include <sys/time.h>

#include <GL/glut.h>

void Display(void);
void Reshape(int, int);
void Timer(int);
void drawCircle(double, double, double, int);
void drawHand(double, double, double, double);
void drawGear(double, double, double, double, double, int);

double t = 0;

int main(int argc, char *argv[]) {
    // 初期化・設定
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Mechanical Clock");
    glutDisplayFunc(Display);
    //glutReshapeFunc(Reshape);
    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // アンチエイリアスを有効
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);

    glutTimerFunc(500, Timer, 0);
    glutMainLoop();

    return 0;
}

void Display(void) {
    struct timeval tv;
    struct tm *t_st;
    double hour, min, sec;

    double l_h = 0.7;
    double l_m = 0.75;
    double l_s = 0.8;

    double x_c, y_c;
    double x_h, y_h;
    double x_m, y_m;
    double x_s, y_s;

    double theta_s;
    double theta_m;
    double theta_h;

    double l = 0.01;

    double r = 0.03;
    double r1 = r * 10;
    double r2 = r * 2 * sqrt(15);
    double r3 = r * 2 * sqrt(15);
    double r4 = r * 6;

    double w1 = 2 * M_PI / 3600;
    double w2 = -2 * M_PI / 3600;
    double w3 = 2 * M_PI / (120 * sqrt(15));
    double w4 = -2 * M_PI / 60;

    // 時刻を取得
    gettimeofday(&tv, NULL);
    t_st = localtime(&tv.tv_sec);

    sec = t_st->tm_sec + tv.tv_usec * 1e-6;
    min = t_st->tm_min + sec / 60;
    hour = t_st->tm_hour + min / 60;

    // 針の座標を決定
    x_c = 0;
    y_c = 0;

    theta_h = 2 * M_PI * hour / 12;
    x_h = x_c + l_h * sin(theta_h);
    y_h = y_c + l_h * cos(theta_h);

    theta_m = 2 * M_PI * min / 60;
    x_m = x_c + l_m * sin(theta_m);
    y_m = y_c + l_m * cos(theta_m);

    theta_s = 2 * M_PI * sec / 60;
    x_s = x_c + l_s * sin(theta_s);
    y_s = y_c + l_s * cos(theta_s);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0, 0, 0);

    // 針描画
    glBegin(GL_LINES);

    glVertex2d(x_c, y_c);
    glVertex2d(x_h, y_h);
    glVertex2d(x_c, y_c);
    glVertex2d(x_m, y_m);
    glVertex2d(x_c, y_c);
    glVertex2d(x_s, y_s);

    glEnd();

    // 歯車描画
    drawCircle(0, 0, 0.85, 100);

    drawGear(-r1 - r, 0, t * w1, r1, l, 80);
    drawGear(-r1 - r, 0, t * w1, r, l, 8);

    drawGear(0, 0, t * w2, r2, l, 62);
    drawGear(0, 0, t * w2, r, l, 8);

    drawGear(0, -r3 - r, t * w3, r3, l, 62);
    drawGear(0, -r3 - r, t * w3, r, l, 8);

    drawGear(0, 0, t * w4, r4, l, 48);
    drawGear(0, 0, t * w4, r, l, 8);

    glFlush();
}

void Reshape(int w, int h) {
    // 座標系再設定
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScaled(1, -1, 1);
    glTranslated(0, -h, 0);
}

// タイマー
void Timer(int value) {
    glutTimerFunc(500, Timer, 0);
    t += 0.5;
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
