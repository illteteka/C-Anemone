#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../sds.h"
#include "../globals.h"

#include "gfx.h"

struct col
{
	int r;
	int g;
	int b;
};

struct col gfxColor = {0, 0, 0};

int gfxSetColor(int r, int g, int b)
{
	gfxColor.r = r;
	gfxColor.g = g;
	gfxColor.b = b;
	return 0;
}

int gfxRectangle(SDL_Renderer *renderer, int x, int y, int w, int h)
{
	SDL_Rect temp_rect = {x, y, w, h};
	SDL_SetRenderDrawColor(renderer, gfxColor.r, gfxColor.g, gfxColor.b, 255);
	SDL_RenderFillRect(renderer, &temp_rect);
	return 0;
}

int gfxTriangle()
{
	return 0;
}

int gfxLine()
{
	return 0;
}

int gfxGetTextWidth(SDL_Renderer *renderer, TTF_Font *font, sds str)
{
	SDL_Rect text_rect = {0, 0, 32, 32};
	SDL_Color text_color = {0, 0, 0, 255};

	SDL_Surface *surf_text = TTF_RenderText_Blended(font, str, text_color);
	SDL_Texture *text_fps = SDL_CreateTextureFromSurface(renderer, surf_text);
	text_rect.w = (surf_text->w);

	SDL_FreeSurface(surf_text);
	SDL_DestroyTexture(text_fps);

	return text_rect.w;
}

int gfxPrintParent(SDL_Renderer *renderer, TTF_Font *font, sds str, int x, int y, float scale)
{
	SDL_Rect text_rect = {x, y, 32, 32};
	SDL_Color text_color = {gfxColor.r, gfxColor.g, gfxColor.b, 255};

	SDL_Surface *surf_text = TTF_RenderText_Blended(font, str, text_color);
	SDL_Texture *text_fps = SDL_CreateTextureFromSurface(renderer, surf_text);
	text_rect.w = (int) ((surf_text->w) * scale);
	text_rect.h = (int) ((surf_text->h) * scale);

	SDL_RenderCopy(renderer, text_fps, NULL, &text_rect);

	sdsfree(str);
	SDL_FreeSurface(surf_text);
	SDL_DestroyTexture(text_fps);

	return 0;
}

int gfxPrint(SDL_Renderer *renderer, TTF_Font *font, sds str, int x, int y)
{
	gfxPrintParent(renderer, font, str, x, y, 1);
	return 0;
}

int gfxPrintRel(SDL_Renderer *renderer, TTF_Font *font, sds str, float x, float y, float scale)
{
	int xx = (int) ((x - cameraX) * cameraZoom);
	int yy = (int) ((y - cameraY) * cameraZoom);
	gfxPrintParent(renderer, font, str, xx, yy, scale);

	return 0;
}

int gfxPrintf()
{
	return 0;
}

int gfxDrawImage(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h)
{
	SDL_Rect img_rect = {x, y, w, h};
	SDL_RenderCopy(renderer, texture, NULL, &img_rect);
	return 0;
}

int gfxDrawImageRel(SDL_Renderer *renderer, SDL_Texture *texture, float x, float y, float w, float h)
{
	int xx = (int) ((x - cameraX) * cameraZoom);
	int yy = (int) ((y - cameraY) * cameraZoom);
	int ww = (int) (w * cameraZoom);
	int hh = (int) (h * cameraZoom);
	gfxDrawImage(renderer, texture, xx, yy, ww, hh);
	return 0;
}