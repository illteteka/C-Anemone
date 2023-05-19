#include <SDL2/SDL.h>

#include "level_test_one.h"
#include "level_test_two.h"

#include "../objects/guy.h"
#include "../engine/input.h"
#include "../engine/gfx.h"
#include "../globals.h"
#include "../sds.h"
#include "../instances.h"

void levelTestOneLevel()
{
	guyNew(83, 99);
	guyNew(369, 93);
	guyNew(95, 219);
	guyNew(105, 243);
	guyNew(114, 257);
	guyNew(121, 265);
	guyNew(133, 279);
	guyNew(155, 292);
	guyNew(174, 307);
	guyNew(191, 310);
	guyNew(200, 312);
	guyNew(211, 316);
	guyNew(230, 316);
	guyNew(251, 313);
	guyNew(272, 308);
	guyNew(289, 301);
	guyNew(302, 294);
	guyNew(314, 287);
	guyNew(326, 273);
	guyNew(335, 257);
	guyNew(346, 239);
	guyNew(352, 227);
	guyNew(357, 215);
	guyNew(362, 204);
	guyNew(362, 204);
}

void levelTestOneInit()
{
	LEVEL_SWITCH = LEVEL_TEST_1;
	instancesInit();
	levelTestOneLevel();
	resetCamera();
}

void levelTestOneUpdate(float dt)
{
	guyUpdate(dt);

	// Simulate lag to test delta time
	if (triangle_key == _ON)
	{
		int lag = 0;
		while (lag < 10000)
		{
			sds ohno = sdsnew(",faweafwawfawfawfawf ");
			sdsfree(ohno);
			lag++;
		}
	}

	if (square_key == _PRESS)
	{
		levelTestTwoInit();
	}

	// Debug camera movement
	// if (triangle_key == _ON)
	// 	cameraY -= 1 * dt;

	// if (cross_key == _ON)
	// 	cameraY += 1 * dt;

	// if (square_key == _ON)
	// 	cameraX -= 1 * dt;

	// if (circle_key == _ON)
	// 	cameraX += 1 * dt;

	if (l_key == _PRESS)
		cameraZoom -= 0.1;

	if (r_key == _PRESS)
		cameraZoom += 0.1;
}

void levelTestOneDraw(SDL_Renderer *renderer)
{
	guyDraw(renderer);

	gfxSetColor(0,255,0);
	gfxTriangleRel(renderer, 379, 61, 453, 66, 381, 178);

	gfxSetColor(184,148,237);
	gfxLineRel(renderer, 99, 40, 94, 111);
}