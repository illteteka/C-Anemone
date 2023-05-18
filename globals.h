#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#ifndef GLOBALS_H
#define GLOBALS_H

#define LEVEL_TEST_1 0
#define LEVEL_TEST_2 1
extern int LEVEL_SWITCH;
extern bool DEBUG_MODE;
extern float sleep;
extern float cameraX;
extern float cameraY;
extern float cameraZoom;
int resetCamera();

#endif