#include <SDL2/SDL.h>

#include "level_test_one.h"
#include "level_test_two.h"

#include "../objects/guy.h"
#include "../engine/input.h"
#include "../globals.h"
#include "../sds.h"
#include "../instances.h"

int levelTestTwoLevel()
{

	guyNew(32, 32);
	guyNew(64, 64);

	return 0;
}

int levelTestTwoInit()
{
	LEVEL_SWITCH = LEVEL_TEST_2;
	instancesInit();
	levelTestTwoLevel();
	resetCamera();

	return 0;
}

int levelTestTwoUpdate(float dt)
{
	guyUpdate(dt);

	if (square_key == _PRESS)
	{
		levelTestOneInit();
	}

	return 1;
}

int levelTestTwoDraw(SDL_Renderer *renderer)
{
	guyDraw(renderer);

	return 0;
}