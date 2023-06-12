#include "../include.h"

bool devDebugWindow = false;
char fps_string[8] = "";

void devInit()
{
	devDebugWindow = false;
}

void devUpdateDebugMenu(float dt)
{
	if (select_key == _PRESS)
		devDebugWindow = !devDebugWindow;
}

void devDrawDebugMenu(float fps)
{
	if (devDebugWindow)
	{
		snprintf(fps_string, sizeof(fps_string), "fps: %i", (int)fps);

		gfxSetColor(0, 0, 255);
		gfxRectangle(0,0,72,32);
		gfxSetColor(255, 255, 255);
		gfxPrint(fps_string, 8, 8);
	}
}