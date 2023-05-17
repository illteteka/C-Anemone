#include "level_test_one.h"

#include "../engine/input.h"
#include "../globals.h"

int levelTestOneLevel()
{
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

	return 1;
}

int levelTestOneDraw()
{
	return 0;
}