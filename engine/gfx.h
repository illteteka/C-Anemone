#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../sds.h"

#ifndef GFX_H
#define GFX_H

#define ALIGN_LEFT 0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT 2

void gfxSetColor(int r, int g, int b);
void gfxRectangle(SDL_Renderer *renderer, int x, int y, int w, int h);
void gfxRectangleRel(SDL_Renderer *renderer, int x, int y, int w, int h);
void gfxTriangle(SDL_Renderer *renderer, int x, int y, int x2, int y2, int x3, int y3);
void gfxTriangleRel(SDL_Renderer *renderer, int x, int y, int x2, int y2, int x3, int y3);
void gfxLine(SDL_Renderer *renderer, int x, int y, int x2, int y2);
void gfxLineRel(SDL_Renderer *renderer, int x, int y, int x2, int y2);
int gfxGetTextWidth(SDL_Renderer *renderer, TTF_Font *font, sds str);
void gfxPrint(SDL_Renderer *renderer, TTF_Font *font, sds str, int x, int y);
void gfxPrintRel(SDL_Renderer *renderer, TTF_Font *font, sds str, float x, float y, float scale);
void gfxPrintf(SDL_Renderer *renderer, TTF_Font *font, sds str, int x, int y, int limit, int align);
void gfxPrintfRel(SDL_Renderer *renderer, TTF_Font *font, sds str, float x, float y, int limit, int align, float scale);
void gfxDrawImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);
void gfxDrawImageRel(SDL_Renderer *renderer, SDL_Texture *texture, float x, float y, float w, float h);

#endif