#include "../include.h"

#define MAX_GUY 32

SDL_Texture* guy_local_texture = NULL;

struct guy
{
	float x;
	float y;
	bool active;
};

int guyCount = 0;
struct guy guyData[MAX_GUY];

void guySetTexture(SDL_Texture* texture)
{
	guy_local_texture = texture;
}

void guyInit()
{
    guyCount = 0;
    memset(guyData, 0, sizeof(guyData));
}

int guyNew(float x, float y)
{
	struct guy tbl = {x, y, true};
	guyData[guyCount] = tbl;
	guyCount++;

	return guyCount - 1;
}

void guyUpdate(float dt)
{
	int i = 0;
	while (i < sizeof(guyData) / sizeof(guyData[0]))
	{
		if (guyData[i].active)
		{
			if (up_key == _ON)
				guyData[i].y -= 1 * dt;

			if (down_key == _ON)
				guyData[i].y += 1 * dt;

			if (left_key == _ON)
				guyData[i].x -= 1 * dt;

			if (right_key == _ON)
				guyData[i].x += 1 * dt;
		}

	    i++;
	}
}

void guyDraw()
{
	int i = 0;
	while (i < sizeof(guyData) / sizeof(guyData[0]))
	{
		if (guyData[i].active)
			gfxDrawImageRel(guy_local_texture, guyData[i].x, guyData[i].y, 32, 32);

	    i++;
	}
}