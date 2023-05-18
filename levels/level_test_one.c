#include <SDL2/SDL.h>

#include "level_test_one.h"

#include "../objects/guy.h"
#include "../engine/input.h"
#include "../globals.h"
#include "../sds.h"

int levelTestOneLevel()
{
	guyNew(0.0, 0.0);
	guyNew(10.0, 10.0);
	guyNew(20.0, 20.0);
	guyNew(30.0, 30.0);
	return 0;
}

int levelTestOneInit()
{

	return 0;
}

int levelTestOneUpdate(float dt)
{
	// input test
	if (up_key == _ON)
		y -= 1 * dt;

	if (down_key == _ON)
		y += 1 * dt;

	if (left_key == _ON)
		x -= 1 * dt;

	if (right_key == _ON)
		x += 1 * dt;

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

	return 1;
}

int levelTestOneDraw(SDL_Renderer *renderer)
{
	guyDraw(renderer);
	return 0;
}