#include "dev.h"
#include "input.h"
#include "gfx.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "../sds.h"
#include "../globals.h"

bool devDebugWindow = false;

int devInit()
{
	devDebugWindow = true;
	return 0;
}

int devUpdateDebugMenu(float dt)
{
	if (select_key == _PRESS)
		devDebugWindow = !devDebugWindow;

	return 0;
}

int devDrawDebugMenu(SDL_Renderer *renderer, TTF_Font *font, float fps)
{
	if (devDebugWindow)
	{
		sds fps_string = sdscatfmt(sdsempty(),"fps: %i", (int) fps);

		gfxSetColor(0, 0, 255);
		gfxRectangle(renderer,0,0,72,32);
		gfxSetColor(255, 255, 255);
		gfxPrint(renderer, font, fps_string, 8, 8);
	}

	return 0;
}