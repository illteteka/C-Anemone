#include "../include.h"

/*
	Canvas example room
*/

SDL_Texture *level_test_two_local_canvas = NULL;

void levelTestTwoSetCanvasTexture(SDL_Texture *canvas)
{
	level_test_two_local_canvas = canvas;
}

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
	gfxDrawImage(level_test_two_local_canvas, 0, 0, 512, 512);
	brushDraw();
}