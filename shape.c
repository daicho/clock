#include <math.h>

#include <GL/glut.h>
#include <GL/glpng.h>

#include "shape.h"

// 正円を描画
void drawCircle(double x, double y, double r, int n) {
    int i;

    glBegin(GL_LINE_LOOP);

    for (i = 0; i < n; i++) {
        glVertex2d(x + r * sin(2 * M_PI * i / n), y + r * cos(2 * M_PI * i / n));
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
        glVertex2d(x + 0.045 * sin(i * w + a), y + 0.045 * cos(i * w + a));
    }

    glEnd();

    // 歯
    glColor3fv(color);
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
    drawCircle(x, y, 0.045, n * 2);
    drawCircle(x, y, r - l * 1.5, n * 2);
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
        glVertex2d(x + 0.045 * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + 0.045 * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l * 1.5) * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + (r - l * 1.5) * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
        glVertex2d(x + 0.045 * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + 0.045 * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l * 1.5) * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + (r - l * 1.5) * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
    }

    glEnd();
    glColor3fv(color);
}

// カナ(小さい歯車)
void drawKana(double x, double y, double a, double r, double l, int n) {
    int i;
    double w = M_PI / n;
    GLfloat color[4];

    // 現在の色を取得
    glGetFloatv(GL_CURRENT_COLOR, color);

    // 円
    glBegin(GL_POLYGON);

    for (i = 0; i < n * 2; i++) {
        glVertex2d(x + (r - l / 2) * sin(i * w + a), y + (r - l / 2) * cos(i * w + a));
    }

    glEnd();

    // 歯
    glColor3fv(color);
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
    glColor3fv(color);
}

// ガンギ車 
void drawGangi(double x, double y, double a, double r, double l, int n) {
    int i;
    double w = -2 * M_PI / n;
    double ws = 2 * M_PI / 5;
    GLfloat color[4];

    // 現在の色を取得
    glGetFloatv(GL_CURRENT_COLOR, color);

    // 円
    glBegin(GL_QUAD_STRIP);

    for (i = 0; i <= n; i++) {
        glVertex2d(x + (r - l * 1.5) * cos(i * w + a), y + (r - l * 1.5) * sin(i * w + a));
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
    }

    glEnd();
    glBegin(GL_POLYGON);

    for (i = 0; i < n * 2; i++) {
        glVertex2d(x + 0.045 * sin(i * w + a), y + 0.045 * cos(i * w + a));
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
    drawCircle(x, y, 0.045, n * 2);
    drawCircle(x, y, r - l * 1.5, n);
    glBegin(GL_LINE_LOOP);

    for (i = 0; i < n; i++) {
        glVertex2d(x + (r - l / 2) * cos(i * w + a), y + (r - l / 2) * sin(i * w + a));
        glVertex2d(x + (r + l / 2) * cos(i * w + a), y + (r + l / 2) * sin(i * w + a));
    }

    glEnd();

    // 骨組み
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
        glVertex2d(x + 0.045 * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + 0.045 * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l * 1.5) * cos(i * ws + a) + r * 0.07 * sin(i * ws + a), y + (r - l * 1.5) * sin(i * ws + a) - r * 0.07 * cos(i * ws + a));
        glVertex2d(x + 0.045 * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + 0.045 * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
        glVertex2d(x + (r - l * 1.5) * cos(i * ws + a) - r * 0.07 * sin(i * ws + a), y + (r - l * 1.5) * sin(i * ws + a) + r * 0.07 * cos(i * ws + a));
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
    drawCircle(x + (r + 0.15) * cos(a), y + (r + 0.15) * sin(a), 0.15, 100);

    // アンクル
    glBegin(GL_LINE_STRIP);
    glVertex2d(x + 0.08 * sin(a - 3 * M_PI / 20), y + 0.08 * cos(a - 3 * M_PI / 20));
    glVertex2d(x - 0.08 * sin(a + 3 * M_PI / 20), y - 0.08 * cos(a + 3 * M_PI / 20));

    //glVertex2d(x - 0.08 * sin(a) + 0.02 * cos(a), y + 0.08 * cos(a) + 0.02 * sin(a));
    //glVertex2d(x - 0.08 * sin(a), y + 0.08 * cos(a));
    //glVertex2d(x + 0.08 * sin(a), y - 0.08 * cos(a));
    //glVertex2d(x + 0.08 * sin(a) + 0.02 * cos(a), y - 0.08 * cos(a) + 0.02 * sin(a));
    glEnd();
}
