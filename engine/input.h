#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#define _OFF 0
#define _ON 1
#define _PRESS 2
#define _RELEASE 3

extern int up_key;
extern int down_key;
extern int left_key;
extern int right_key;
extern int cross_key;
extern int circle_key;
extern int triangle_key;
extern int square_key;
extern int l_key;
extern int r_key;
extern int start_key;
extern int select_key;
extern double stick_h;
extern double stick_v;
int inputInit();
int inputPullSwitch(bool a, int b, bool ignore);
int inputUpdate();

#endif