#include <math.h>

#include <GL/glut.h>
#include <GL/glpng.h>

#include "shape.h"

// 正多角形を描画
// x, y : 座標
// a : 角度
// r : 半径
// n : 角数
void drawPolygon(double x, double y, double a, double r, int n) {
    int i;
    GLdouble color[4];

    // 1ループあたりの角度
    double w = 2 * M_PI / n;

    // 現在の色を保存
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 塗りつぶし
    glBegin(GL_POLYGON);
    for (i = 0; i < n; i++)
        glVertex2d(x + r * sin(i * w + a), y + r * cos(i * w + a));
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < n; i++)
        glVertex2d(x + r * sin(i * w + a), y + r * cos(i * w + a));
    glEnd();

    // 色を元に戻す
    glColor4dv(color);
}

// 歯車を描画
// x, y : 座標
// a : 角度
// r : 半径
// l : 歯の長さ
// n : 歯数
void drawGear(double x, double y, double a, double r, double l, int n) {
    int i;
    GLdouble color[4];

    double rs = 0.045;    // 中心の円の半径
    double hf = r * 0.07; // 骨組みの幅

    // 1ループあたりの角度
    double w = M_PI / n;
    double wf = 2 * M_PI / 5;

    // 現在の色を保存
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 歯の内側の輪
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= n * 2; i++) {
        glVertex2d(x + (r - l * 1.5) * cos(i * w + a), y + (r - l * 1.5) * sin(i * w + a));
        glVertex2d(x + (r - l * 0.5) * cos(i * w + a), y + (r - l * 0.5) * sin(i * w + a));
    }
    glEnd();

    // 縁取り
    glColor4ub(0, 0, 0, 0);
    drawPolygon(x, y, a, r - l * 1.5, n * 2);

    // 中心の円
    glColor4dv(color);
    drawPolygon(x, y, a, rs, n * 2);

    // 骨組み
    glBegin(GL_QUADS);
    for (i = 0; i < 5; i++) {
        glVertex2d(x + hf * sin(i * wf + a), y - hf * cos(i * wf + a));
        glVertex2d(x - hf * sin(i * wf + a), y + hf * cos(i * wf + a));
        glVertex2d(x + (r - l) * cos(i * wf + a) - hf * sin(i * wf + a), y + (r - l) * sin(i * wf + a) + hf * cos(i * wf + a));
        glVertex2d(x + (r - l) * cos(i * wf + a) + hf * sin(i * wf + a), y + (r - l) * sin(i * wf + a) - hf * cos(i * wf + a));
    }
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    for (i = 0; i < 5; i++) {
        glVertex2d(x + rs * cos(i * wf + a - asin(hf / rs)), y + rs * sin(i * wf + a - asin(hf / rs)));
        glVertex2d(x + (r - l * 1.5) * cos(i * wf + a - asin(hf / (r - l * 1.5))), y + (r - l * 1.5) * sin(i * wf + a - asin(hf / (r - l * 1.5))));
        glVertex2d(x + rs * cos(i * wf + a + asin(hf / rs)), y + rs * sin(i * wf + a + asin(hf / rs)));
        glVertex2d(x + (r - l * 1.5) * cos(i * wf + a + asin(hf / (r - l * 1.5))), y + (r - l * 1.5) * sin(i * wf + a + asin(hf / (r - l * 1.5))));
    }
    glEnd();

    // 歯
    glColor4dv(color);
    glBegin(GL_QUADS);
    for (i = 0; i < n * 2; i += 2) {
        glVertex2d(x + (r - l * 0.5) * cos((i - 0.5) * w + a), y + (r - l * 0.5) * sin((i - 0.5) * w + a));
        glVertex2d(x + (r - l * 0.5) * cos((i + 0.5) * w + a), y + (r - l * 0.5) * sin((i + 0.5) * w + a));
        glVertex2d(x + (r - l * 0.5) * cos((i + 0.5) * w + a) + l * cos((i) * w + a), y + (r - l * 0.5) * sin((i + 0.5) * w + a) + l * sin((i) * w + a));
        glVertex2d(x + (r - l * 0.5) * cos((i - 0.5) * w + a) + l * cos((i) * w + a), y + (r - l * 0.5) * sin((i - 0.5) * w + a) + l * sin((i) * w + a));
    }
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < 2 * n; i++) {
        if (i % 2) {
            glVertex2d(x + (r - l * 0.5) * cos((i - 0.5) * w + a), y + (r - l * 0.5) * sin((i - 0.5) * w + a));
            glVertex2d(x + (r - l * 0.5) * cos((i + 0.5) * w + a), y + (r - l * 0.5) * sin((i + 0.5) * w + a));
        } else {
            glVertex2d(x + (r - l * 0.5) * cos((i - 0.5) * w + a) + l * cos((i) * w + a), y + (r - l * 0.5) * sin((i - 0.5) * w + a) + l * sin((i) * w + a));
            glVertex2d(x + (r - l * 0.5) * cos((i + 0.5) * w + a) + l * cos((i) * w + a), y + (r - l * 0.5) * sin((i + 0.5) * w + a) + l * sin((i) * w + a));
        }
    }
    glEnd();

    glColor4dv(color);
}

// カナを描画
// x, y : 座標
// a : 角度
// r : 半径
// l : 歯の長さ
// n : 歯数
void drawKana(double x, double y, double a, double r, double l, int n) {
    int i;
    GLdouble color[4];

    // 1ループあたりの角度
    double w = M_PI / n;

    // 現在の色を保存
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 円
    glBegin(GL_POLYGON);
    for (i = 0; i < n * 2; i++)
        glVertex2d(x + (r - l * 0.5) * sin(i * w + a), y + (r - l * 0.5) * cos(i * w + a));
    glEnd();

    // 歯
    glColor4dv(color);
    glBegin(GL_QUADS);
    for (i = 0; i < n * 2; i += 2) {
        glVertex2d(x + (r - l * 0.5) * cos((i - 0.5) * w + a), y + (r - l * 0.5) * sin((i - 0.5) * w + a));
        glVertex2d(x + (r - l * 0.5) * cos((i + 0.5) * w + a), y + (r - l * 0.5) * sin((i + 0.5) * w + a));
        glVertex2d(x + (r - l * 0.5) * cos((i + 0.5) * w + a) + l * cos((i) * w + a), y + (r - l * 0.5) * sin((i + 0.5) * w + a) + l * sin((i) * w + a));
        glVertex2d(x + (r - l * 0.5) * cos((i - 0.5) * w + a) + l * cos((i) * w + a), y + (r - l * 0.5) * sin((i - 0.5) * w + a) + l * sin((i) * w + a));
    }
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < 2 * n; i++) {
        if (i % 2) {
            glVertex2d(x + (r - l * 0.5) * cos((i - 0.5) * w + a), y + (r - l * 0.5) * sin((i - 0.5) * w + a));
            glVertex2d(x + (r - l * 0.5) * cos((i + 0.5) * w + a), y + (r - l * 0.5) * sin((i + 0.5) * w + a));
        } else {
            glVertex2d(x + (r - l * 0.5) * cos((i - 0.5) * w + a) + l * cos((i) * w + a), y + (r - l * 0.5) * sin((i - 0.5) * w + a) + l * sin((i) * w + a));
            glVertex2d(x + (r - l * 0.5) * cos((i + 0.5) * w + a) + l * cos((i) * w + a), y + (r - l * 0.5) * sin((i + 0.5) * w + a) + l * sin((i) * w + a));
        }
    }
    glEnd();

    glColor4dv(color);
}

// ガンギ車を描画
// x, y : 座標
// a : 角度
// r : 半径
// l : 歯の長さ
// n : 歯数
void drawGangi(double x, double y, double a, double r, double l, int n) {
    int i;
    GLdouble color[4];

    double rs = 0.045;    // 中心の円の半径
    double hf = r * 0.07; // 骨組みの幅

    // 1ループあたりの角度
    double w = -2 * M_PI / n;
    double wf = 2 * M_PI / 5;

    // アンクルと噛み合うように角度調整
    a += 0.03;

    // 現在の色を保存
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 歯の内側の輪
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= n; i++) {
        glVertex2d(x + (r - l) * cos(i * w + a), y + (r - l) * sin(i * w + a));
        glVertex2d(x + (r - l * 0.5) * cos(i * w + a), y + (r - l * 0.5) * sin(i * w + a));
    }
    glEnd();

    // 縁取り
    glColor4ub(0, 0, 0, 0);
    drawPolygon(x, y, a, r - l, n);

    // 中心の円
    glColor4dv(color);
    drawPolygon(x, y, a, rs, n);

    // 骨組み
    glBegin(GL_QUADS);
    for (i = 0; i < 5; i++) {
        glVertex2d(x + hf * sin(i * wf + a), y - hf * cos(i * wf + a));
        glVertex2d(x - hf * sin(i * wf + a), y + hf * cos(i * wf + a));
        glVertex2d(x + (r - l * 0.75) * cos(i * wf + a) - hf * sin(i * wf + a), y + (r - l * 0.75) * sin(i * wf + a) + hf * cos(i * wf + a));
        glVertex2d(x + (r - l * 0.75) * cos(i * wf + a) + hf * sin(i * wf + a), y + (r - l * 0.75) * sin(i * wf + a) - hf * cos(i * wf + a));
    }
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    for (i = 0; i < 5; i++) {
        glVertex2d(x + rs * cos(i * wf + a - asin(hf / rs)), y + rs * sin(i * wf + a - asin(hf / rs)));
        glVertex2d(x + (r - l) * cos(i * wf + a - asin(hf / (r - l))), y + (r - l) * sin(i * wf + a - asin(hf / (r - l))));
        glVertex2d(x + rs * cos(i * wf + a + asin(hf / rs)), y + rs * sin(i * wf + a + asin(hf / rs)));
        glVertex2d(x + (r - l) * cos(i * wf + a + asin(hf / (r - l))), y + (r - l) * sin(i * wf + a + asin(hf / (r - l))));
    }
    glEnd();

    // 歯
    glColor4dv(color);
    glBegin(GL_TRIANGLES);
    for (i = 0; i < n; i++) {
        glVertex2d(x + (r - l * 0.5) * cos(i * w + a), y + (r - l * 0.5) * sin(i * w + a));
        glVertex2d(x + (r + l * 0.5) * cos(i * w + a), y + (r + l * 0.5) * sin(i * w + a));
        glVertex2d(x + (r - l * 0.5) * cos((i + 1) * w + a), y + (r - l * 0.5) * sin((i + 1) * w + a));
    }
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < n; i++) {
        glVertex2d(x + (r - l * 0.5) * cos(i * w + a), y + (r - l * 0.5) * sin(i * w + a));
        glVertex2d(x + (r + l * 0.5) * cos(i * w + a), y + (r + l * 0.5) * sin(i * w + a));
    }
    glEnd();

    glColor4dv(color);
}

// 時針を描画
// x, y : 座標
// a : 角度
// r : 半径
void drawHour(double x, double y, double a, double r) {
    GLdouble color[4];

    double rr = 0.06; // 根本の半径
    double hr = 0.01; // 根本の幅
    double hc = 0.02; // 中心の幅
    double ht = 0.01; // 先端の幅

    // 現在の色を保存
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 塗りつぶし
    glBegin(GL_POLYGON);
    glVertex2d(x - rr * cos(a) - hr * sin(a), y - rr * sin(a) + hr * cos(a));
    glVertex2d(x - rr * cos(a) + hr * sin(a), y - rr * sin(a) - hr * cos(a));
    glVertex2d(x + hc * sin(a), y - hc * cos(a));
    glVertex2d(x + r * cos(a) + ht * sin(a), y + r * sin(a) - ht * cos(a));
    glVertex2d(x + r * cos(a) - ht * sin(a), y + r * sin(a) + ht * cos(a));
    glVertex2d(x - hc * sin(a), y + hc * cos(a));
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(x - rr * cos(a) - hr * sin(a), y - rr * sin(a) + hr * cos(a));
    glVertex2d(x - rr * cos(a) + hr * sin(a), y - rr * sin(a) - hr * cos(a));
    glVertex2d(x + hc * sin(a), y - hc * cos(a));
    glVertex2d(x + r * cos(a) + ht * sin(a), y + r * sin(a) - ht * cos(a));
    glVertex2d(x + r * cos(a) - ht * sin(a), y + r * sin(a) + ht * cos(a));
    glVertex2d(x - hc * sin(a), y + hc * cos(a));
    glEnd();

    glColor4dv(color);
}

// 分針を描画
// x, y : 座標
// a : 角度
// r : 半径
void drawMinute(double x, double y, double a, double r) {
    GLdouble color[4];

    double rr = 0.06; // 根本の半径
    double hr = 0.01; // 根本の幅
    double hc = 0.02; // 中心の幅
    double ht = 0.003; // 先端の幅

    // 現在の色を保存
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 塗りつぶし
    glBegin(GL_POLYGON);
    glVertex2d(x - rr * cos(a) - hr * sin(a), y - rr * sin(a) + hr * cos(a));
    glVertex2d(x - rr * cos(a) + hr * sin(a), y - rr * sin(a) - hr * cos(a));
    glVertex2d(x + hc * sin(a), y - hc * cos(a));
    glVertex2d(x + r * cos(a) + ht * sin(a), y + r * sin(a) - ht * cos(a));
    glVertex2d(x + r * cos(a) - ht * sin(a), y + r * sin(a) + ht * cos(a));
    glVertex2d(x - hc * sin(a), y + hc * cos(a));
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(x - rr * cos(a) - hr * sin(a), y - rr * sin(a) + hr * cos(a));
    glVertex2d(x - rr * cos(a) + hr * sin(a), y - rr * sin(a) - hr * cos(a));
    glVertex2d(x + hc * sin(a), y - hc * cos(a));
    glVertex2d(x + r * cos(a) + ht * sin(a), y + r * sin(a) - ht * cos(a));
    glVertex2d(x + r * cos(a) - ht * sin(a), y + r * sin(a) + ht * cos(a));
    glVertex2d(x - hc * sin(a), y + hc * cos(a));
    glEnd();

    glColor4dv(color);
}

// 秒針を描画
// x, y : 座標
// a : 角度
// r : 半径
void drawSecond(double x, double y, double a, double r) {
    GLdouble color[4];

    double rr = 0.15;  // 根本の半径
    double rc = 0.022; // 中心の円の半径
    double h = 0.005;  // 針の幅

    // 現在の色を保存
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 中心の円
    drawPolygon(x, y, a, rc, 20);

    // 塗りつぶし
    glBegin(GL_QUADS);
    glVertex2d(x - rr * cos(a) - h * sin(a), y - rr * sin(a) + h * cos(a));
    glVertex2d(x - rr * cos(a) + h * sin(a), y - rr * sin(a) - h * cos(a));
    glVertex2d(x + r * cos(a) + h * sin(a), y + r * sin(a) - h * cos(a));
    glVertex2d(x + r * cos(a) - h * sin(a), y + r * sin(a) + h * cos(a));
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2d(x - rc * cos(a - asin(h / rc)), y - rc * sin(a - asin(h / rc)));
    glVertex2d(x - rr * cos(a) - h * sin(a), y - rr * sin(a) + h * cos(a));
    glVertex2d(x - rr * cos(a) + h * sin(a), y - rr * sin(a) - h * cos(a));
    glVertex2d(x - rc * cos(a + asin(h / rc)), y - rc * sin(a + asin(h / rc)));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d(x + rc * cos(a - asin(h / rc)), y + rc * sin(a - asin(h / rc)));
    glVertex2d(x + r * cos(a) + h * sin(a), y + r * sin(a) - h * cos(a));
    glVertex2d(x + r * cos(a) - h * sin(a), y + r * sin(a) + h * cos(a));
    glVertex2d(x + rc * cos(a + asin(h / rc)), y + rc * sin(a + asin(h / rc)));
    glEnd();

    glColor4dv(color);
}

// 振り子を描画
// x, y : 座標
// a : 角度
// r : 半径
void drawPendulum(double x, double y, double a, double r) {
    GLdouble color[4];

    double rw = 0.15;      // 錘の半
    double rr = 0.1;       // 根本の半径
    double rs = r + 0.2;   // 棒の半径
    double hs = 0.015;     // 棒の幅
    double aa = M_PI / 12; // アンクルの角度
    double ha = 0.015;     // アンクルの幅
    double lt = 0.04;      // アンクルの先端の長さ
    double lu = 0.10;      // アンクル上部の長さ
    double lc = 0.079;     // アンクル中部の長さ
    double ld = 0.07;      // アンクル下部の長さ

    // 現在の色を保存
    glGetDoublev(GL_CURRENT_COLOR, color);

    // 棒
    glBegin(GL_QUADS);
    glVertex2d(x - rr * cos(a) - hs * sin(a), y - rr * sin(a) + hs * cos(a));
    glVertex2d(x - rr * cos(a) + hs * sin(a), y - rr * sin(a) - hs * cos(a));
    glVertex2d(x + rs * cos(a) + hs * sin(a), y + rs * sin(a) - hs * cos(a));
    glVertex2d(x + rs * cos(a) - hs * sin(a), y + rs * sin(a) + hs * cos(a));
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(x - rr * cos(a) - hs * sin(a), y - rr * sin(a) + hs * cos(a));
    glVertex2d(x - rr * cos(a) + hs * sin(a), y - rr * sin(a) - hs * cos(a));
    glVertex2d(x + rs * cos(a) + hs * sin(a), y + rs * sin(a) - hs * cos(a));
    glVertex2d(x + rs * cos(a) - hs * sin(a), y + rs * sin(a) + hs * cos(a));
    glEnd();

    // 重り
    glColor4dv(color);
    drawPolygon(x + r * cos(a), y + r * sin(a), -a, rw, 50);

    // アンクル
    glBegin(GL_TRIANGLES);
    glVertex2d(x + lt * cos(a) + lc * sin(a + aa), y + lt * sin(a) - lc * cos(a + aa));
    glVertex2d(x + ha * cos(a) + ld * sin(a + aa), y + ha * sin(a) - ld * cos(a + aa));
    glVertex2d(x - ha * cos(a) + lu * sin(a + aa), y - ha * sin(a) - lu * cos(a + aa));
    glVertex2d(x + lt * cos(a) - lc * sin(a - aa), y + lt * sin(a) + lc * cos(a - aa));
    glVertex2d(x + ha * cos(a) - ld * sin(a - aa), y + ha * sin(a) + ld * cos(a - aa));
    glVertex2d(x - ha * cos(a) - lu * sin(a - aa), y - ha * sin(a) + lu * cos(a - aa));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex2d(x + ha * cos(a) + ld * sin(a + aa), y + ha * sin(a) - ld * cos(a + aa));
    glVertex2d(x - ha * cos(a) + lu * sin(a + aa), y - ha * sin(a) - lu * cos(a + aa));
    glVertex2d(x + ha * cos(a), y + ha * sin(a));
    glVertex2d(x - ha * cos(a), y - ha * sin(a));
    glVertex2d(x + ha * cos(a) - ld * sin(a - aa), y + ha * sin(a) + ld * cos(a - aa));
    glVertex2d(x - ha * cos(a) - lu * sin(a - aa), y - ha * sin(a) + lu * cos(a - aa));
    glEnd();

    // 縁取り
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(x + lt * cos(a) + lc * sin(a + aa), y + lt * sin(a) - lc * cos(a + aa));
    glVertex2d(x + ha * cos(a) + ld * sin(a + aa), y + ha * sin(a) - ld * cos(a + aa));
    glVertex2d(x + ha * cos(a), y + ha * sin(a));
    glVertex2d(x + ha * cos(a) - ld * sin(a - aa), y + ha * sin(a) + ld * cos(a - aa));
    glVertex2d(x + lt * cos(a) - lc * sin(a - aa), y + lt * sin(a) + lc * cos(a - aa));
    glVertex2d(x - ha * cos(a) - lu * sin(a - aa), y - ha * sin(a) + lu * cos(a - aa));
    glVertex2d(x - ha * cos(a), y - ha * sin(a));
    glVertex2d(x - ha * cos(a) + lu * sin(a + aa), y - ha * sin(a) - lu * cos(a + aa));
    glEnd();

    glColor4dv(color);
}

// 画像を表示
// num : 画像の番号
// x, y : 座標
// w, h : サイズ
// pngInfo : 画像情報
void putSprite(GLuint num, double x, double y, double w, double h, pngInfo *info) {
    float color[4];

    // 現在の色を保存
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
