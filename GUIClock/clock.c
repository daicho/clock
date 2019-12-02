#include <stdio.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>

void Display(void);
void Reshape(int, int);
void Timer(int);
void drawCircle(int, int, int);
void drawHand();

int main(int argc, char *argv[]) {
    // 初期化・設定
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Color Sample");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutInitDisplayMode(GLUT_RGBA);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutTimerFunc(500, Timer, 0);
    glutMainLoop();

    return 0;
}

void Display(void) {
    time_t timer;
    struct tm *t_st;
    int hour, min, sec;

    int l_h = 90;
    int l_m = 100;
    int l_s = 110;

    int x_c, y_c;
    int x_h, y_h;
    int x_m, y_m;
    int x_s, y_s;

    double theta_s;
    double theta_m;
    double theta_h;

    // 時刻を取得
    time(&timer);
    t_st = localtime(&timer);

    hour = t_st->tm_hour;
    min = t_st->tm_min;
    sec = t_st->tm_sec;

    // 針の座標を決定
    x_c = glutGet(GLUT_WINDOW_WIDTH) / 2;
    y_c = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    theta_h = 2 * M_PI * (hour % 12) / 12;
    x_h = x_c + l_h * sin(theta_h);
    y_h = y_c - l_h * cos(theta_h);

    theta_m = 2 * M_PI * min / 60;
    x_m = x_c + l_m * sin(theta_m);
    y_m = y_c - l_m * cos(theta_m);

    theta_s = 2 * M_PI * sec / 60;
    x_s = x_c + l_s * sin(theta_s);
    y_s = y_c - l_s * cos(theta_s);

    glClear(GL_COLOR_BUFFER_BIT);

    // 針描画
    glColor3ub(0, 0, 0);

    drawCircle(x_c, y_c, 120);

    glBegin(GL_LINES);

    glVertex2i(x_c, y_c);
    glVertex2i(x_h, y_h);
    glVertex2i(x_c, y_c);
    glVertex2i(x_m, y_m);
    glVertex2i(x_c, y_c);
    glVertex2i(x_s, y_s);

    glEnd();

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
    Display();
    glutTimerFunc(500, Timer, 0);
}

// 正円を描画
void drawCircle(int x, int y, int r) {
    int i;
    int h = 180;

    glBegin(GL_LINE_LOOP);

    for (i = 0; i < h; i++) {
        double theta = 2 * M_PI * i / h;
        glVertex2i(x + r * sin(theta), y + r * cos(theta));
    }

    glEnd();
}
