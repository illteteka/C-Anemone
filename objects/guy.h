#include <SDL2/SDL.h>

#ifndef OBJ_GUY_H
#define OBJ_GUY_H

int guyInit(SDL_Renderer *renderer);
int guyNew(float x, float y);
int guyDraw(SDL_Renderer *renderer);
int guyDestroy();

#endif