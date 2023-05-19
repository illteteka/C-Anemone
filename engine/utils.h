#include "../sds.h"

#ifndef UTILS_H
#define UTILS_H

int CheckCollision(float x1,float y1,float w1,float h1, float x2,float y2,float w2,float h2);
int getSquare(int n);
void reverseString(sds str);
float lengthdir_x(float length, float dir);
float lengthdir_y(float length, float dir);
float point_direction(float x1, float y1, float x2, float y2);
int sign(int x);
float clamp(float x, float min, float max);
float lerp(float a, float b, float amount);
void hsl(int h, int s, int l, int a, int *rgb);

#endif