#include <SDL2/SDL.h>

#ifndef OBJ_GUY_H
#define OBJ_GUY_H

void guyInit();
int guyNew(float x, float y);
void guyUpdate(float dt);
void guySetTexture(SDL_Texture* texture);
void guyDraw(SDL_Renderer *renderer);

#endif