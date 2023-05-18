#include <SDL2/SDL.h>

#ifndef OBJ_GUY_H
#define OBJ_GUY_H

int guyInit();
int guyNew(float x, float y);
int guyUpdate(float dt);
int guySetTexture(SDL_Texture* texture);
int guyDraw(SDL_Renderer *renderer);

#endif