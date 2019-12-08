#ifndef CLOCK_H
#define CLOCK_H

void Display(void);
void Reshape(int w, int h);
void Timer(int value);

extern long double t;
extern GLuint dial_img;
extern pngInfo dial_info;

#endif
