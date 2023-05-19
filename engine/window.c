#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "window.h"

void windowInit()
{
	// Function implementation
	// Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL2 could not be initialized!\n"
		"SDL2 Error: %s\n",
		SDL_GetError());
	}

	// Initialize SDL2_ttf
	if (TTF_Init() < 0)
	{
		printf("SDL2_ttf could not be initialized!\n"
		"SDL2_ttf Error: %s\n",
		SDL_GetError());
	}
}