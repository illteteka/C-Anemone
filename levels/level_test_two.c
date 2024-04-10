#include "../include.h"

/*
	Canvas example room
*/

void levelTestTwoLevel()
{
	brushNew((int) SCREEN_WIDTH/2, (int) SCREEN_HEIGHT/2);
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
	brushUpdate(dt);

	if (square_key == _PRESS)
	{
		levelTestOneInit();
	}
}

void levelTestTwoDraw()
{
	brushDraw();
}