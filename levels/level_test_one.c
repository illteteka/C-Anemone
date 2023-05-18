#include <SDL2/SDL.h>

#include "level_test_one.h"

#include "../objects/guy.h"
#include "../engine/input.h"
#include "../globals.h"
#include "../sds.h"
#include "../instances.h"

int levelTestOneLevel()
{
	guyNew(0.0, 0.0);
	guyNew(0.0, 32.0);
	guyNew(0.0, 64.0);
	guyNew(0.0, 96.0);

	return 0;
}

int levelTestOneInit()
{
	LEVEL_SWITCH = LEVEL_TEST_1;
	instancesInit();
	levelTestOneLevel();
	resetCamera();

	return 0;
}

int levelTestOneUpdate(float dt)
{
	guyUpdate(dt);

	// Simulate lag to test delta time
	// if (triangle_key == _ON)
	// {
	// 	int lag = 0;
	// 	while (lag < 10000)
	// 	{
	// 		sds ohno = sdsnew(",faweafwawfawfawfawf ");
	// 		sdsfree(ohno);
	// 		lag++;
	// 	}
	// }

	// Debug camera movement
	// if (triangle_key == _ON)
	// 	cameraY -= 1 * dt;

	// if (cross_key == _ON)
	// 	cameraY += 1 * dt;

	// if (square_key == _ON)
	// 	cameraX -= 1 * dt;

	// if (circle_key == _ON)
	// 	cameraX += 1 * dt;

	// if (l_key == _PRESS)
	// 	cameraZoom -= 0.1;

	// if (r_key == _PRESS)
	// 	cameraZoom += 0.1;


	return 1;
}

int levelTestOneDraw(SDL_Renderer *renderer)
{
	guyDraw(renderer);

	return 0;
}