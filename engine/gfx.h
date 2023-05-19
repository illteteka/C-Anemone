#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../sds.h"

#ifndef GFX_H
#define GFX_H

int gfxSetColor(int r, int g, int b);
int gfxRectangle(SDL_Renderer *renderer, int x, int y, int w, int h);
int gfxTriangle();
int gfxLine();
int gfxGetTextWidth(SDL_Renderer *renderer, TTF_Font *font, sds str);
int gfxPrint(SDL_Renderer *renderer, TTF_Font *font, sds str, int x, int y);
int gfxPrintRel(SDL_Renderer *renderer, TTF_Font *font, sds str, float x, float y, float scale);
int gfxPrintf();
int gfxDrawImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);
int gfxDrawImageRel(SDL_Renderer *renderer, SDL_Texture *texture, float x, float y, float w, float h);

#endif