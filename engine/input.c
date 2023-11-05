#include "../include.h"

#if defined(__APPLE__) || defined(_WIN64) || defined(__linux__)
	int uu = 0;
	int dd = 0;
	int ll = 0;
	int rr = 0;
#else
	SceCtrlData pad;
#endif

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
int stick_h;
int stick_v;

void inputInit(void)
{
	#if defined(__APPLE__) || defined(_WIN64) || defined(__linux__)

	#else
		sceCtrlSetSamplingCycle(0);
		sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	#endif
}

int inputPullSwitch(bool a, int b, bool ignore)
{
	int output = b;

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

	return output;
}

void inputUpdate(void)
{
	#if defined(__APPLE__) || defined(_WIN64) || defined(__linux__)
		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		stick_h = 128;
		stick_v = 128;
		up_key = inputPullSwitch((keyboardState[SDL_SCANCODE_W]), up_key, false);
		down_key = inputPullSwitch((keyboardState[SDL_SCANCODE_S]), down_key, false);
		left_key = inputPullSwitch((keyboardState[SDL_SCANCODE_A]), left_key, false);
		right_key = inputPullSwitch((keyboardState[SDL_SCANCODE_D]), right_key, false);

		cross_key = inputPullSwitch((keyboardState[SDL_SCANCODE_K]), cross_key, false);
		circle_key = inputPullSwitch((keyboardState[SDL_SCANCODE_L]), circle_key, false);
		triangle_key = inputPullSwitch((keyboardState[SDL_SCANCODE_I]), triangle_key, false);
		square_key = inputPullSwitch((keyboardState[SDL_SCANCODE_J]), square_key, false);

		l_key = inputPullSwitch((keyboardState[SDL_SCANCODE_1]), l_key, false);
		r_key = inputPullSwitch((keyboardState[SDL_SCANCODE_2]), r_key, false);
		start_key = inputPullSwitch((keyboardState[SDL_SCANCODE_RETURN]), start_key, false);
		select_key = inputPullSwitch((keyboardState[SDL_SCANCODE_TAB]), select_key, false);
		
		if (keyboardState[SDL_SCANCODE_W] && keyboardState[SDL_SCANCODE_LCTRL])
		{
			SDL_Event quitEvent;
			quitEvent.type = SDL_QUIT;
			SDL_PushEvent(&quitEvent);
		}
	#else
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
	#endif	
}
