#include <SDL2/SDL.h>

#include "level_test_one.h"
#include "level_test_two.h"

#include "../objects/guy.h"
#include "../engine/input.h"
#include "../globals.h"
#include "../sds.h"
#include "../instances.h"

void levelTestTwoLevel()
{
	guyNew(32, 32);
	guyNew(64, 64);
}

void levelTestTwoInit()
{
	LEVEL_SWITCH = LEVEL_TEST_2;
	instancesInit();
	levelTestTwoLevel();
	resetCamera();
}

void levelTestTwoUpdate(float dt)
{
	guyUpdate(dt);

	if (square_key == _PRESS)
	{
		levelTestOneInit();
	}
}

void levelTestTwoDraw(SDL_Renderer *renderer)
{
	guyDraw(renderer);
}