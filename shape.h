#ifndef SHAPE_H
#define SHAPE_H

void drawPolygon(double x, double y, double a, double r, int n);
void drawGear(double x, double y, double a, double r, double l, int n);
void drawKana(double x, double y, double a, double r, double l, int n);
void drawGangi(double x, double y, double a, double r, double l, int n);
void drawHour(double x, double y, double a, double r);
void drawMinute(double x, double y, double a, double r);
void drawSecond(double x, double y, double a, double r);
void drawPendulum(double x, double y, double a, double r);
void putSprite(GLuint num, double x, double y, double w, double h, pngInfo *info);

#endif
