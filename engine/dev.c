#include "dev.h"
#include "input.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "../sds.h"

bool devDebugWindow = false;
SDL_Rect dev_rect = {0,0,72,32};
SDL_Rect fps_rect = {8, 8, 32, 32};

// todo
SDL_Color text_color = {0xff, 0xff, 0xff, 0xff};

int devInit()
{
	devDebugWindow = true;
	return 0;
}

int devUpdateDebugMenu(float dt)
{
	if (select_key == _PRESS)
		devDebugWindow = !devDebugWindow;

	return 0;
}

int devDrawDebugMenu(SDL_Renderer *renderer, TTF_Font *font, float fps)
{
	if (devDebugWindow)
	{
		// todo refactor
		
		sds fps_string = sdscatfmt(sdsempty(),"fps: %i", (int) fps);

		SDL_Surface *surf_text = TTF_RenderText_Blended(font, fps_string, text_color);
		SDL_Texture *text_fps = SDL_CreateTextureFromSurface(renderer, surf_text);
		fps_rect.w = surf_text->w;
		fps_rect.h = surf_text->h;

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
		SDL_RenderFillRect(renderer, &dev_rect);
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderCopy(renderer, text_fps, NULL, &fps_rect);

		sdsfree(fps_string);
		SDL_FreeSurface(surf_text);
		SDL_DestroyTexture(text_fps);
	}

	return 0;
}