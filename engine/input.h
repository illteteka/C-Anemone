#ifndef INPUT_H
#define INPUT_H

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
extern int stick_h;
extern int stick_v;
void inputInit(void);
int inputPullSwitch(bool a, int b, bool ignore);
void inputUpdate(void);

#endif
