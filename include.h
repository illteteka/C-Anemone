#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>

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

#include "instances.h"

#ifndef GLOBALS_H
#define GLOBALS_H

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define LEVEL_TEST_1 0
#define LEVEL_TEST_2 1

extern int LEVEL_SWITCH;
extern float sleep;
extern float cameraX;
extern float cameraY;
extern float cameraZoom;
void resetCamera();

#endif