#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../globals.h"

#include "guy.h"

#define MAX_GUY 8

bool guyLoadOnce = false;
SDL_Rect guy_rect = {32, 32, 32, 32};
SDL_Texture* spr_sample_32;

struct guy
{
	float x;
	float y;
	bool active;
};

int guyCount = 0;
struct guy guyData[MAX_GUY];

int guyInit(SDL_Renderer *renderer)
{
	if (guyLoadOnce == false)
	{
		spr_sample_32 = IMG_LoadTexture(renderer, "assets/basic.png");
		guyLoadOnce = true;
	}

    guyCount = 0;
    memset(guyData, 0, sizeof(guyData));

    return 0;
}

int guyNew(float x, float y)
{
	struct guy tbl = {x, y, true};
	guyData[guyCount] = tbl;
	guyCount++;

	return guyCount - 1;
}

int guyDraw(SDL_Renderer *renderer)
{
	int i = 0;
	while (i < sizeof(guyData) / sizeof(guyData[0]))
	{
		if (guyData[i].active)
		{
			guy_rect.x = (int) guyData[i].x + (int) x;
	    	guy_rect.y = (int) guyData[i].y + (int) y;
	    	SDL_RenderCopy(renderer, spr_sample_32, NULL, &guy_rect);
		}

	    i++;
	}

	return 0;
}

int guyDestroy()
{
	SDL_DestroyTexture(spr_sample_32);
	return 0;
}