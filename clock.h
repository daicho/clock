#ifndef CLOCK_H
#define CLOCK_H

void Display(void);
void Reshape(int, int);
void Timer(int);

extern long double t;
extern long double st;
extern GLuint dial_img;
extern pngInfo dial_info;

#endif
