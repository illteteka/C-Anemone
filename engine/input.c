#include <pspctrl.h>
#include <stdbool.h>
#include "input.h"

SceCtrlData pad;

int up_key = _OFF;
int down_key = _OFF;
int left_key = _OFF;
int right_key = _OFF;
int cross_key = _OFF;
int circle_key = _OFF;
int triangle_key = _OFF;
int square_key = _OFF;
int l_key = _OFF;
int r_key = _OFF;
int start_key = _OFF;
int select_key = _OFF;
double stick_h;
double stick_v;

// -- Used when pausing the game
// input.throw_away = false
// input.throw_away_timer = 0

int inputInit()
{
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
}

int inputPullSwitch(bool a, int b, bool ignore)
{
	int output = b;

	//if (!ignore) // (input.throw_away && !ignore)
	//	output = _OFF;
	//else
	//{
	// Main input code
	if (a==true)
	{
		if (b == _OFF || b == _RELEASE)
			output = _PRESS;
		else if (b == _PRESS)
			output = _ON;
	}
	else
	{
		if (b == _ON || b == _PRESS)
			output = _RELEASE;
		else if (b == _RELEASE)
			output = _OFF;
	}
	// End main input code	
	//}

	return output;
}

int inputUpdate()
{
	sceCtrlReadBufferPositive(&pad, 1);

	stick_h = pad.Lx;
	stick_v = pad.Ly;

	up_key = inputPullSwitch((pad.Buttons & PSP_CTRL_UP), up_key, false);
	down_key = inputPullSwitch((pad.Buttons & PSP_CTRL_DOWN), down_key, false);
	left_key = inputPullSwitch((pad.Buttons & PSP_CTRL_LEFT), left_key, false);
	right_key = inputPullSwitch((pad.Buttons & PSP_CTRL_RIGHT), right_key, false);
	cross_key = inputPullSwitch((pad.Buttons & PSP_CTRL_CROSS), cross_key, false);
	circle_key = inputPullSwitch((pad.Buttons & PSP_CTRL_CIRCLE), circle_key, false);
	triangle_key = inputPullSwitch((pad.Buttons & PSP_CTRL_TRIANGLE), triangle_key, false);
	square_key = inputPullSwitch((pad.Buttons & PSP_CTRL_SQUARE), square_key, false);
	l_key = inputPullSwitch((pad.Buttons & PSP_CTRL_LTRIGGER), l_key, false);
	r_key = inputPullSwitch((pad.Buttons & PSP_CTRL_RTRIGGER), r_key, false);
	start_key = inputPullSwitch((pad.Buttons & PSP_CTRL_START), start_key, false);
	select_key = inputPullSwitch((pad.Buttons & PSP_CTRL_SELECT), select_key, false);

	return 1;
}