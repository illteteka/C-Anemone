#include "../include.h"

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

void levelTestTwoDraw()
{
	guyDraw();
}