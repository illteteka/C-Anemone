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

#include "engine/dev.h"
#include "engine/gfx.h"
#include "engine/input.h"
#include "engine/utils.h"
#include "engine/window.h"

#include "levels/level_test_one.h"
#include "levels/level_test_two.h"

#include "objects/guy.h"

#include "instances.h"
#include "globals.h"

float cameraX = 0.0;
float cameraY = 0.0;
float cameraZoom = 1.0;

float sleep = 0;

SDL_Window* win;
SDL_Renderer* renderer;

SDL_Texture* spr_sample_32;

int LEVEL_SWITCH = LEVEL_TEST_1;

int resetCamera()
{
	cameraX = 0.0;
	cameraY = 0.0;
	cameraZoom = 1.0;
}

int loadTextures(SDL_Renderer *renderer)
{
	spr_sample_32 = IMG_LoadTexture(renderer, "assets/basic.png");
	guySetTexture(spr_sample_32);
}

int destroyTextures()
{
	SDL_DestroyTexture(spr_sample_32);
}

int load()
{
	devInit();
	inputInit();
	windowInit();

	instancesInit(); // Needs to happen before loading a level

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

	inputUpdate(dt);

	if (sleep == 0)
		updateGame(dt);
	else
		sleep = fmax(sleep - dt, 0);

	return 1;
}

int drawGame(SDL_Renderer *renderer)
{
	if (LEVEL_SWITCH == LEVEL_TEST_1)
		levelTestOneDraw(renderer);
	else if (LEVEL_SWITCH == LEVEL_TEST_2)
		levelTestTwoDraw(renderer);

	return 1;
}

int draw(SDL_Renderer *renderer, TTF_Font *font, float fps)
{	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	
	drawGame(renderer);

	devDrawDebugMenu(renderer, font, fps);

	SDL_RenderPresent(renderer);
	
	return 1;
}

int main(int argc, char *argv[])
{
	load();

	TTF_Font *font = TTF_OpenFont("assets/font.ttf", 14);

	win = SDL_CreateWindow(
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
	SDL_RenderSetVSync(renderer, 1);

	loadTextures(renderer);

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

		update(dt);
		draw(renderer, font, fps);

		uint ticks_now = SDL_GetTicks();
		uint diff = ticks_now - prev_ticks;
		fps_counter += diff;
		prev_ticks = ticks_now;
		frames_drawn++;

		if(fps_counter >= 1000)
		{
			fps = (float)frames_drawn / (float)(fps_counter/1000.0f);
			frames_drawn = 0;
			fps_counter = 0;
		}
	}

	destroyTextures();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();

	return 0;
}