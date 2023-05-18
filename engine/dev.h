#ifndef DEV_H
#define DEV_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int devInit();
int devUpdateDebugMenu(float dt);
int devDrawDebugMenu(SDL_Renderer *renderer, TTF_Font *font, float fps);

#endif