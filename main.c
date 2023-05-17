#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#include "engine/video.h"
#include "engine/input.h"

/*
	i want to know how to arbitrarily add text
	i want better file management
	anemone port
	audio?
	savedata?
*/

int main(int argc, char *argv[])
{
	videoInit();
	inputInit();

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

	int running = 1;
	SDL_Event e;
	while (running)
	{
		char live_string[] = "----------------";

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

		// input test
		if (up_key == _ON)
			sample_32.y-=1;

		if (down_key == _ON)
			sample_32.y+=1;

		if (left_key == _ON)
			sample_32.x-=1;

		if (right_key == _ON)
			sample_32.x+=1;

		text_rect.x = (int) (stick_h);
		text_rect.y = (int) (stick_v);

		SDL_Surface *spr_live_surf = TTF_RenderText_Blended(font, live_string, text_color);
		SDL_Texture *spr_live_text = SDL_CreateTextureFromSurface(renderer, spr_live_surf);
		live_string_rect.w = (spr_live_surf->w);
		live_string_rect.h = spr_live_surf->h;

		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
		SDL_RenderCopy(renderer, spr_sample_32, NULL, &sample_32);
		SDL_RenderCopy(renderer, spr_hello, NULL, &text_rect);
		SDL_RenderCopy(renderer, spr_live_text, NULL, &live_string_rect);
		SDL_RenderPresent(renderer);

		SDL_FreeSurface(spr_live_surf);
		SDL_DestroyTexture(spr_live_text);
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