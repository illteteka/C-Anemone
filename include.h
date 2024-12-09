#include <SDL2/SDL.h>

#ifdef __APPLE__
	#include <SDL2_image/SDL_image.h>
	#define GLOBAL_SCALE 4
#elif defined(__linux__)
	#include <SDL2/SDL_image.h>
	#define GLOBAL_SCALE 4
#elif defined(_WIN64)
	#include <SDL2/SDL_image.h>
	#define GLOBAL_SCALE 2
#else
	#include <SDL2/SDL_image.h>

	#include <pspkernel.h>
	#include <pspdebug.h>
	#include <pspctrl.h>

	#define GLOBAL_SCALE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "engine/dev.h"
#include "engine/gfx.h"
#include "engine/input.h"
#include "engine/utils.h"

#include "levels/level_test_one.h"
#include "levels/level_test_two.h"

#include "objects/guy.h"
#include "objects/brush.h"

#include "instances.h"

#ifndef GLOBALS_H
#define GLOBALS_H

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define LEVEL_TEST_1 0
#define LEVEL_TEST_2 1

#define CANVAS_SIZE 512

extern int LEVEL_SWITCH;
extern float rest;
extern float cameraX;
extern float cameraY;
extern float cameraZoom;
void resetCamera(void);

extern SDL_Renderer* renderer;
extern SDL_Texture* canvas_example;
extern SDL_Texture* canvas_eraser;

#ifdef __PSP__

#else
	extern SDL_Texture* canvas_scale;
#endif

#endif
