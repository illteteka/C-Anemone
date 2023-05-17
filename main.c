#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "sds.h"

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#include "engine/ctrl.h"
#include "engine/dev.h"
#include "engine/gfx.h"
#include "engine/input.h"
#include "engine/ui.h"
#include "engine/utils.h"
#include "engine/video.h"
#include "engine/window.h"

#include "levels/level_test_one.h"
#include "levels/level_test_two.h"

#include "objects/blueguy.h"
#include "objects/guy.h"

#include "instances.h"
#include "globals.h"

/*
	i want to know how to arbitrarily add text
	i want better file management
	anemone port
	audio?
	savedata?
*/

// todo remove
float x = 0;
float y = 0;

int LEVEL_SWITCH = LEVEL_TEST_1;
float sleep = 0;

int load()
{
	devInit();
	ctrlInit();
	inputInit();
	windowInit();
	uiInit();
	videoInit();

	instancesLoad(); // Needs to happen before loading a level

	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneInit();
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoInit();

	return 1;
}

int updateGame(float dt)
{
	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneUpdate(dt);
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoUpdate(dt);

	return 1;
}

int update(float dt)
{
	devUpdateDebugMenu(dt);

	if (sleep == 0)
		updateGame(dt);
	else
		sleep = fmax(sleep - dt, 0);

	return 1;
}

int drawGame()
{
	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneDraw();
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoDraw();

	return 1;
}

int draw()
{
	windowDraw();

	// Always run this last
	devDrawDebugMenu();
	
	return 1;
}

int main(int argc, char *argv[])
{
	load();

	SDL_Window *win = SDL_CreateWindow(
	"window",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED,
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
	0);

	if (!win)
	{
		printf("Window could not be created!\n"
		"SDL_Error: %s\n",
		SDL_GetError());
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, 0);
	TTF_Font *font = TTF_OpenFont("assets/font.ttf", 14);

	// Set the text and background color
	SDL_Color text_color = {0x00, 0x00, 0x00, 0xff};

	SDL_Rect text_rect;
	SDL_Surface *surface = TTF_RenderText_Blended(font, "hello world", text_color);
	SDL_Texture *spr_hello = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Texture *spr_sample_32 = IMG_LoadTexture(renderer, "assets/basic.png");

	// Get text dimensions
	text_rect.w = surface->w;
	text_rect.h = surface->h;
	text_rect.x = (SCREEN_WIDTH - text_rect.w) / 2;
	text_rect.y = text_rect.h + 30;

	SDL_Rect sample_32 = {32, 32, 32, 32};
	SDL_Rect live_string_rect = {64, 64, 32, 32};

	SDL_FreeSurface(surface);

	int frames_drawn = 0;
	uint fps_counter = 0;
	float fps = 0.0f;
	uint prev_ticks = SDL_GetTicks();

	int running = 1;
	SDL_Event e;
	while (running)
	{
		float dt = 59.0f/fmax(fps,1.0f);
		if (dt > 10)
		{
			dt = 1;
		}

		if (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					running = 0;
					break;
			}
		}

		inputUpdate();

		update(dt);

		sample_32.x = (int) x;
		sample_32.y = (int) y;

		text_rect.x = stick_h;
		text_rect.y = stick_v;

		sds mystring = sdsempty();
		sds mystring2 = sdsnew(", ");
		sds num = sdscatfmt(sdsempty(),"%i", stick_h);
		sds num2 = sdscatfmt(sdsempty(),"%i", stick_v);
		sds num3 = sdscatfmt(sdsempty(),"%i", (int) fps);
		mystring = sdscat(mystring, num);
		mystring = sdscat(mystring, mystring2);
		mystring = sdscat(mystring, num2);
		mystring = sdscat(mystring, mystring2);
		mystring = sdscat(mystring, num3);

		SDL_Surface *spr_live_surf = TTF_RenderText_Blended(font, mystring, text_color);
		SDL_Texture *spr_live_text = SDL_CreateTextureFromSurface(renderer, spr_live_surf);
		live_string_rect.w = (spr_live_surf->w);
		live_string_rect.h = spr_live_surf->h;

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
		
		sdsfree(num);
		sdsfree(num2);
		sdsfree(num3);
		
		sdsfree(mystring);
		sdsfree(mystring2);

		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
		SDL_RenderCopy(renderer, spr_sample_32, NULL, &sample_32);
		SDL_RenderCopy(renderer, spr_hello, NULL, &text_rect);
		SDL_RenderCopy(renderer, spr_live_text, NULL, &live_string_rect);
		SDL_RenderPresent(renderer);

		SDL_FreeSurface(spr_live_surf);
		SDL_DestroyTexture(spr_live_text);

		uint ticks_now = SDL_GetTicks();
		uint diff = ticks_now - prev_ticks;
		fps_counter += diff;
		prev_ticks = ticks_now;
		frames_drawn++;

		if(fps_counter >= 1000) {
			fps = (float)frames_drawn / (float)(fps_counter/1000.0f);
			frames_drawn = 0;
			fps_counter = 0;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_DestroyTexture(spr_hello);
	SDL_DestroyTexture(spr_sample_32);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();

	return 0;
}