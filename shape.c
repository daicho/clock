#include <math.h>

#include <GL/glut.h>
#include <GL/glpng.h>

#include "shape.h"

// 正多角形
void drawPolygon(double x, double y, double a, double r, int n) {
    int i;
    double w = 2 * M_PI / n;
    GLdouble color[4];

    // 現在の色を取得
    glGetDoublev(GL_CURRENT_COLOR, color);

    glBegin(GL_POLYGON);

    for (i = 0; i < n; i++) {
        glVertex2d(x + r * sin(i * w + a), y + r * cos(i * w + a));
    }

    glEnd();
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);

    for (i = 0; i < n; i++) {
        glVertex2d(x + r * sin(i * w + a), y + r * cos(i * w + a));
    }

    glEnd();
    glColor4dv(color);
}

// 歯車
void drawGear(double x, double y, double a, double r, double l, int n) {
    int i;
    double w = M_PI / n;
    double ws = 2 * M_PI / 5;
    GLdouble color[4];

    // 現在の色を取得
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 円
    glBegin(GL_QUAD_STRIP);

    for (i = 0; i <= n * 2; i++) {
        glVertex2d(x + (r - l * 1.5) * cos(i * w + a), y + (r - l * 1.5) * sin(i * w + a));
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
    }

    glEnd();
    drawPolygon(x, y, a, 0.045, n * 2);

    // 歯
    glColor4dv(color);
    glBegin(GL_QUADS);

    for (i = 0; i < n * 2; i += 2) {
        glVertex2d(x + (r - l / 2) * cos((i - 0.5) * w + a), y + (r - l / 2) * sin((i - 0.5) * w + a));
        glVertex2d(x + (r - l / 2) * cos((i - 0.5) * w + a) + l * cos((i) * w + a), y + (r - l / 2) * sin((i - 0.5) * w + a) + l * sin((i) * w + a));
        glVertex2d(x + (r - l / 2) * cos((i + 0.5) * w + a) + l * cos((i) * w + a), y + (r - l / 2) * sin((i + 0.5) * w + a) + l * sin((i) * w + a));
        glVertex2d(x + (r - l / 2) * cos((i + 0.5) * w + a), y + (r - l / 2) * sin((i + 0.5) * w + a));
    }

    glEnd();

    // 縁線
    glColor4ub(0, 0, 0, 0);
    drawPolygon(x, y, a, r - l * 1.5, n * 2);
    glColor4ub(0, 0, 0, 255);
    glBegin(GL_LINE_LOOP);

    for (i = 0; i < 2 * n; i++) {
        if (i % 2) {
            glVertex2d(x + (r - l / 2) * cos((i - 0.5) * w + a), y + (r - l / 2) * sin((i - 0.5) * w + a));
            glVertex2d(x + (r - l / 2) * cos((i + 0.5) * w + a), y + (r - l / 2) * sin((i + 0.5) * w + a));
        } else {
            glVertex2d(x + (r - l / 2) * cos((i - 0.5) * w + a) + l * cos((i) * w + a), y + (r - l / 2) * sin((i - 0.5) * w + a) + l * sin((i) * w + a));
            glVertex2d(x + (r - l / 2) * cos((i + 0.5) * w + a) + l * cos((i) * w + a), y + (r - l / 2) * sin((i + 0.5) * w + a) + l * sin((i) * w + a));
        }
    }

    glEnd();

    // 骨組み
    glColor4dv(color);
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
        glVertex2d(x + 0.045 * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + 0.045 * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l * 1.5) * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + (r - l * 1.5) * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
        glVertex2d(x + 0.045 * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + 0.045 * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l * 1.5) * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + (r - l * 1.5) * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
    }

    glEnd();
    glColor4dv(color);
}

// カナ(小さい歯車)
void drawKana(double x, double y, double a, double r, double l, int n) {
    int i;
    double w = M_PI / n;
    GLdouble color[4];

    // 現在の色を取得
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 円
    glBegin(GL_POLYGON);

    for (i = 0; i < n * 2; i++) {
        glVertex2d(x + (r - l / 2) * sin(i * w + a), y + (r - l / 2) * cos(i * w + a));
    }

    glEnd();

    // 歯
    glColor4dv(color);
    glBegin(GL_QUADS);

    for (i = 0; i < n * 2; i += 2) {
        glVertex2d(x + (r - l / 2) * cos((i - 0.5) * w + a), y + (r - l / 2) * sin((i - 0.5) * w + a));
        glVertex2d(x + (r - l / 2) * cos((i - 0.5) * w + a) + l * cos((i) * w + a), y + (r - l / 2) * sin((i - 0.5) * w + a) + l * sin((i) * w + a));
        glVertex2d(x + (r - l / 2) * cos((i + 0.5) * w + a) + l * cos((i) * w + a), y + (r - l / 2) * sin((i + 0.5) * w + a) + l * sin((i) * w + a));
        glVertex2d(x + (r - l / 2) * cos((i + 0.5) * w + a), y + (r - l / 2) * sin((i + 0.5) * w + a));
    }

    glEnd();

    // 縁線
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);

    for (i = 0; i < 2 * n; i++) {
        if (i % 2) {
            glVertex2d(x + (r - l / 2) * cos((i - 0.5) * w + a), y + (r - l / 2) * sin((i - 0.5) * w + a));
            glVertex2d(x + (r - l / 2) * cos((i + 0.5) * w + a), y + (r - l / 2) * sin((i + 0.5) * w + a));
        } else {
            glVertex2d(x + (r - l / 2) * cos((i - 0.5) * w + a) + l * cos((i) * w + a), y + (r - l / 2) * sin((i - 0.5) * w + a) + l * sin((i) * w + a));
            glVertex2d(x + (r - l / 2) * cos((i + 0.5) * w + a) + l * cos((i) * w + a), y + (r - l / 2) * sin((i + 0.5) * w + a) + l * sin((i) * w + a));
        }
    }

    glEnd();
    glColor4dv(color);
}

// ガンギ車
void drawGangi(double x, double y, double a, double r, double l, int n) {
    int i;
    double w = -2 * M_PI / n;
    double ws = 2 * M_PI / 5;
    GLdouble color[4];
    a += 0.12;

    // 現在の色を取得
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 円
    glBegin(GL_QUAD_STRIP);

    for (i = 0; i <= n; i++) {
        glVertex2d(x + (r - l) * cos(i * w + a), y + (r - l) * sin(i * w + a));
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
    }

    glEnd();
    drawPolygon(x, y, a, 0.045, n);

    // 歯
    glBegin(GL_TRIANGLES);

    for (i = 0; i < n; i++) {
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
        glVertex2d(x + (r + l / 2) * cos(i * w + a), y + (r + l / 2) * sin(i * w + a));
        glVertex2d(x + (r - l / 2) * cos((i + 1) * w + a), y + (r - l / 2) * sin((i + 1) * w + a));
    }

    glEnd();

    // 縁線
    glColor4ub(0, 0, 0, 0);
    drawPolygon(x, y, a, r - l, n);
    glColor4ub(0, 0, 0, 255);
    glBegin(GL_LINE_LOOP);

    for (i = 0; i < n; i++) {
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
        glVertex2d(x + (r + l / 2) * cos(i * w + a), y + (r + l / 2) * sin(i * w + a));
    }

    glEnd();

    // 骨組み
    glColor4dv(color);
    glBegin(GL_QUADS);

    for (i = 0; i < 5; i++) {
        glVertex2d(x + r * 0.07 * sin(i * ws + a), y - r * 0.07 * cos(i * ws + a));
        glVertex2d(x - r * 0.07 * sin(i * ws + a), y + r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l * 0.75) * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + (r - l * 0.75) * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l * 0.75) * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + (r - l * 0.75) * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
    }

    glEnd();
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);

    for (i = 0; i < 5; i++) {
        glVertex2d(x + 0.045 * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + 0.045 * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l) * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + (r - l) * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
        glVertex2d(x + 0.045 * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + 0.045 * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l) * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + (r - l) * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
    }

    glEnd();
    glColor4dv(color);
}

// 時針
void drawHour(double x, double y, double a, double r) {
    GLdouble color[4];

    // 現在の色を取得
    glGetDoublev(GL_CURRENT_COLOR, color);

    glBegin(GL_POLYGON);

    glVertex2d(x - 0.06 * cos(a) - 0.01 * sin(a), y - 0.06 * sin(a) + 0.01 * cos(a));
    glVertex2d(x - 0.06 * cos(a) + 0.01 * sin(a), y - 0.06 * sin(a) - 0.01 * cos(a));
    glVertex2d(x + 0.02 * sin(a), y - 0.02 * cos(a));
    glVertex2d(x + r * cos(a) + 0.01 * sin(a), y + r * sin(a) - 0.01 * cos(a));
    glVertex2d(x + r * cos(a) - 0.01 * sin(a), y + r * sin(a) + 0.01 * cos(a));
    glVertex2d(x - 0.02 * sin(a), y + 0.02 * cos(a));

    glEnd();
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);

    glVertex2d(x - 0.06 * cos(a) - 0.01 * sin(a), y - 0.06 * sin(a) + 0.01 * cos(a));
    glVertex2d(x - 0.06 * cos(a) + 0.01 * sin(a), y - 0.06 * sin(a) - 0.01 * cos(a));
    glVertex2d(x + 0.02 * sin(a), y - 0.02 * cos(a));
    glVertex2d(x + r * cos(a) + 0.01 * sin(a), y + r * sin(a) - 0.01 * cos(a));
    glVertex2d(x + r * cos(a) - 0.01 * sin(a), y + r * sin(a) + 0.01 * cos(a));
    glVertex2d(x - 0.02 * sin(a), y + 0.02 * cos(a));

    glEnd();
    glColor4dv(color);
}

// 分針
void drawMinute(double x, double y, double a, double r) {
    GLdouble color[4];

    // 現在の色を取得
    glGetDoublev(GL_CURRENT_COLOR, color);

    glBegin(GL_POLYGON);

    glVertex2d(x - 0.06 * cos(a) - 0.01 * sin(a), y - 0.06 * sin(a) + 0.01 * cos(a));
    glVertex2d(x - 0.06 * cos(a) + 0.01 * sin(a), y - 0.06 * sin(a) - 0.01 * cos(a));
    glVertex2d(x + 0.02 * sin(a), y - 0.02 * cos(a));
    glVertex2d(x + r * cos(a) + 0.003 * sin(a), y + r * sin(a) - 0.003 * cos(a));
    glVertex2d(x + r * cos(a) - 0.003 * sin(a), y + r * sin(a) + 0.003 * cos(a));
    glVertex2d(x - 0.02 * sin(a), y + 0.02 * cos(a));

    glEnd();
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);

    glVertex2d(x - 0.06 * cos(a) - 0.01 * sin(a), y - 0.06 * sin(a) + 0.01 * cos(a));
    glVertex2d(x - 0.06 * cos(a) + 0.01 * sin(a), y - 0.06 * sin(a) - 0.01 * cos(a));
    glVertex2d(x + 0.02 * sin(a), y - 0.02 * cos(a));
    glVertex2d(x + r * cos(a) + 0.003 * sin(a), y + r * sin(a) - 0.003 * cos(a));
    glVertex2d(x + r * cos(a) - 0.003 * sin(a), y + r * sin(a) + 0.003 * cos(a));
    glVertex2d(x - 0.02 * sin(a), y + 0.02 * cos(a));

    glEnd();
    glColor4dv(color);
}

// 秒針
void drawSecond(double x, double y, double a, double r) {
    GLdouble color[4];

    // 現在の色を取得
    glGetDoublev(GL_CURRENT_COLOR, color);

    drawPolygon(x, y, a, 0.022, 20);
    glBegin(GL_QUADS);

    glVertex2d(x - 0.15 * cos(a) - 0.005 * sin(a), y - 0.15 * sin(a) + 0.005 * cos(a));
    glVertex2d(x - 0.15 * cos(a) + 0.005 * sin(a), y - 0.15 * sin(a) - 0.005 * cos(a));
    glVertex2d(x + r * cos(a) + 0.005 * sin(a), y + r * sin(a) - 0.005 * cos(a));
    glVertex2d(x + r * cos(a) - 0.005 * sin(a), y + r * sin(a) + 0.005 * cos(a));

    glEnd();
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_STRIP);

    glVertex2d(x - 0.022 * cos(a) - 0.005 * sin(a), y - 0.022 * sin(a) + 0.005 * cos(a));
    glVertex2d(x - 0.15 * cos(a) - 0.005 * sin(a), y - 0.15 * sin(a) + 0.005 * cos(a));
    glVertex2d(x - 0.15 * cos(a) + 0.005 * sin(a), y - 0.15 * sin(a) - 0.005 * cos(a));
    glVertex2d(x - 0.022 * cos(a) + 0.005 * sin(a), y - 0.022 * sin(a) - 0.005 * cos(a));

    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2d(x + 0.022 * cos(a) - 0.005 * sin(a), y + 0.022 * sin(a) + 0.005 * cos(a));
    glVertex2d(x + r * cos(a) - 0.005 * sin(a), y + r * sin(a) + 0.005 * cos(a));
    glVertex2d(x + r * cos(a) + 0.005 * sin(a), y + r * sin(a) - 0.005 * cos(a));
    glVertex2d(x + 0.022 * cos(a) + 0.005 * sin(a), y + 0.022 * sin(a) - 0.005 * cos(a));

    glEnd();
    glColor4dv(color);
}

// 振り子
void drawPendulum(double x, double y, double a, double r) {
    int i;
    double w = M_PI / 25;
    GLdouble color[4];

    // 現在の色を取得
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 棒
    glBegin(GL_QUADS);

    glVertex2d(x - 0.1 * cos(a) - 0.015 * sin(a), y - 0.1 * sin(a) + 0.015 * cos(a));
    glVertex2d(x - 0.1 * cos(a) + 0.015 * sin(a), y - 0.1 * sin(a) - 0.015 * cos(a));
    glVertex2d(x + (r + 0.2) * cos(a) + 0.015 * sin(a), y + (r + 0.2) * sin(a) - 0.015 * cos(a));
    glVertex2d(x + (r + 0.2) * cos(a) - 0.015 * sin(a), y + (r + 0.2) * sin(a) + 0.015 * cos(a));

    glEnd();
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);

    glVertex2d(x - 0.1 * cos(a) - 0.015 * sin(a), y - 0.1 * sin(a) + 0.015 * cos(a));
    glVertex2d(x - 0.1 * cos(a) + 0.015 * sin(a), y - 0.1 * sin(a) - 0.015 * cos(a));
    glVertex2d(x + (r + 0.2) * cos(a) + 0.015 * sin(a), y + (r + 0.2) * sin(a) - 0.015 * cos(a));
    glVertex2d(x + (r + 0.2) * cos(a) - 0.015 * sin(a), y + (r + 0.2) * sin(a) + 0.015 * cos(a));

    glEnd();

    // 重り
    glColor4dv(color);
    drawPolygon(x + r * cos(a), y + r * sin(a), -a, 0.15, 50);

    // アンクル
    glBegin(GL_TRIANGLES);

    glVertex2d(x + 0.078 * sin(a + M_PI / 12) + 0.04 * cos(a), y - 0.078 * cos(a + M_PI / 12) + 0.04 * sin(a));
    glVertex2d(x + 0.015 * cos(a) + 0.07 * sin(a + M_PI / 12), y + 0.015 * sin(a) - 0.07 * cos(a + M_PI / 12));
    glVertex2d(x - 0.015 * cos(a) + 0.10 * sin(a + M_PI / 12), y - 0.015 * sin(a) - 0.10 * cos(a + M_PI / 12));

    glVertex2d(x - 0.078 * sin(a - M_PI / 12) + 0.04 * cos(a), y + 0.078 * cos(a - M_PI / 12) + 0.04 * sin(a));
    glVertex2d(x + 0.015 * cos(a) - 0.07 * sin(a - M_PI / 12), y + 0.015 * sin(a) + 0.07 * cos(a - M_PI / 12));
    glVertex2d(x - 0.015 * cos(a) - 0.10 * sin(a - M_PI / 12), y - 0.015 * sin(a) + 0.10 * cos(a - M_PI / 12));

    glEnd();
    glBegin(GL_QUAD_STRIP);

    glVertex2d(x + 0.015 * cos(a) + 0.07 * sin(a + M_PI / 12), y + 0.015 * sin(a) - 0.07 * cos(a + M_PI / 12));
    glVertex2d(x - 0.015 * cos(a) + 0.10 * sin(a + M_PI / 12), y - 0.015 * sin(a) - 0.10 * cos(a + M_PI / 12));
    glVertex2d(x + 0.015 * cos(a), y + 0.015 * sin(a));
    glVertex2d(x - 0.015 * cos(a), y - 0.015 * sin(a));
    glVertex2d(x + 0.015 * cos(a) - 0.07 * sin(a - M_PI / 12), y + 0.015 * sin(a) + 0.07 * cos(a - M_PI / 12));
    glVertex2d(x - 0.015 * cos(a) - 0.10 * sin(a - M_PI / 12), y - 0.015 * sin(a) + 0.10 * cos(a - M_PI / 12));

    glEnd();
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);

    glVertex2d(x + 0.078 * sin(a + M_PI / 12) + 0.04 * cos(a), y - 0.078 * cos(a + M_PI / 12) + 0.04 * sin(a));
    glVertex2d(x + 0.015 * cos(a) + 0.07 * sin(a + M_PI / 12), y + 0.015 * sin(a) - 0.07 * cos(a + M_PI / 12));
    glVertex2d(x + 0.015 * cos(a), y + 0.015 * sin(a));
    glVertex2d(x + 0.015 * cos(a) - 0.07 * sin(a - M_PI / 12), y + 0.015 * sin(a) + 0.07 * cos(a - M_PI / 12));
    glVertex2d(x - 0.078 * sin(a - M_PI / 12) + 0.04 * cos(a), y + 0.078 * cos(a - M_PI / 12) + 0.04 * sin(a));
    glVertex2d(x - 0.015 * cos(a) - 0.10 * sin(a - M_PI / 12), y - 0.015 * sin(a) + 0.10 * cos(a - M_PI / 12));
    glVertex2d(x - 0.015 * cos(a), y - 0.015 * sin(a));
    glVertex2d(x - 0.015 * cos(a) + 0.10 * sin(a + M_PI / 12), y - 0.015 * sin(a) - 0.10 * cos(a + M_PI / 12));

    glEnd();
    glColor4dv(color);
}

// 画像表示
void putSprite(GLuint num, double x, double y, double w, double h, pngInfo *info) {
    float color[4];

    // 現在の色を取得
    glGetFloatv(GL_CURRENT_COLOR, color);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, num);
    glColor4ub(255, 255, 255, 255);

    glBegin(GL_QUADS);

    glTexCoord2i(0, 0);
    glVertex2d(x, y + h);

    glTexCoord2i(0, 1);
    glVertex2d(x, y);

    glTexCoord2i(1, 1);
    glVertex2d(x + w, y);

    glTexCoord2i(1, 0);
    glVertex2d(x + w, y + h);

    glEnd();
    glColor3fv(color);
    glDisable(GL_TEXTURE_2D);
}
