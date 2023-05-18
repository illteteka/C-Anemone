#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../globals.h"
#include "../engine/input.h"

#include "guy.h"

#define MAX_GUY 8

SDL_Rect guy_rect = {32, 32, 32, 32};
SDL_Texture* guy_local_texture = NULL;

struct guy
{
	float x;
	float y;
	bool active;
};

int guyCount = 0;
struct guy guyData[MAX_GUY];

int guyInit()
{
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

int guyUpdate(float dt)
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

int guySetTexture(SDL_Texture* texture)
{
	guy_local_texture = texture;
}

// todo fix
int drawSimple(SDL_Renderer *renderer, SDL_Rect rect, SDL_Texture *texture, float x, float y)
{
	rect.x = (int) ((x - cameraX) * cameraZoom);
	rect.y = (int) ((y - cameraY) * cameraZoom);
	int w = rect.w;
	int h = rect.h;
	rect.w = (int) (w * cameraZoom);
	rect.h = (int) (h * cameraZoom);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	rect.w = w;
	rect.h = h;
	return 0;
}

int guyDraw(SDL_Renderer *renderer)
{
	int i = 0;
	while (i < sizeof(guyData) / sizeof(guyData[0]))
	{
		if (guyData[i].active)
			drawSimple(renderer, guy_rect, guy_local_texture, guyData[i].x, guyData[i].y);

	    i++;
	}

	return 0;
}