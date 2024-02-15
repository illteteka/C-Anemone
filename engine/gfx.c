#include "../include.h"

#define FONT_W 8
#define FONT_H 18

int font_max = 96;
SDL_Rect* font_rect;
SDL_Texture* font_spr = NULL;
SDL_Renderer* local_renderer = NULL;

struct col
{
	int r;
	int g;
	int b;
	int a;
};

struct col gfxColor = {0, 0, 0, 255};

void gfxSetRenderer(SDL_Renderer *renderer)
{
	local_renderer = renderer;
}

void gfxFontSetTexture(SDL_Texture* texture)
{
	font_spr = texture;
}

SDL_Rect gfxFontGetRect(int tile)
{
	return font_rect[tile];
}

void gfxFontLoadRects(void)
{
	font_rect = malloc(font_max * sizeof(SDL_Rect));

	int i = 0;
	int j = 0;
	int k = 0;
	while (i < font_max)
	{
		if (j >= 8)
		{
			k++;
			j = 0;
		}

		font_rect[i].x = j * FONT_W;
		font_rect[i].y = k * FONT_H;
		font_rect[i].w = FONT_W;
		font_rect[i].h = FONT_H;

		j++;
		i++;
	}
}

void gfxFontFree(void)
{
	free(font_rect);
}

void gfxClear(void)
{
	SDL_SetRenderDrawColor(local_renderer, gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a);
	SDL_RenderClear(local_renderer);
}

void gfxSetCanvas(SDL_Texture *canvas)
{
	SDL_SetRenderTarget(local_renderer, canvas);
}

void gfxResetCanvas(void)
{
	SDL_SetRenderTarget(local_renderer, NULL);
}

void gfxSetColor(int r, int g, int b, int a)
{
	if (a != 255 || (gfxColor.a != 255 && a == 255))
	{
		SDL_SetTextureAlphaMod(font_spr, a);
	}

	gfxColor.r = r;
	gfxColor.g = g;
	gfxColor.b = b;
	gfxColor.a = a;
	SDL_SetTextureColorMod(font_spr,r,g,b);
}

int gfxGetColorR(void)
{
	return gfxColor.r;
}

int gfxGetColorG(void)
{
	return gfxColor.g;
}

int gfxGetColorB(void)
{
	return gfxColor.b;
}

int gfxGetColorA(void)
{
	return gfxColor.a;
}

void gfxRectangle(int x, int y, int w, int h)
{
	SDL_Rect temp_rect = {x * GLOBAL_SCALE, y * GLOBAL_SCALE, w * GLOBAL_SCALE, h * GLOBAL_SCALE};
	SDL_SetRenderDrawColor(local_renderer, gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a);
	SDL_RenderFillRect(local_renderer, &temp_rect);
}

void gfxRectangleRel(int x, int y, int w, int h)
{
	int xx = (int) ((x - cameraX) * cameraZoom);
	int yy = (int) ((y - cameraY) * cameraZoom);
	int ww = (int) (w * cameraZoom);
	int hh = (int) (h * cameraZoom);
	gfxRectangle(xx, yy, ww, hh);
}

void gfxTriangle(int x, int y, int x2, int y2, int x3, int y3)
{
	SDL_Vertex vertex_1 = {{x * GLOBAL_SCALE, y * GLOBAL_SCALE}, {gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a}, {1, 1}};
	SDL_Vertex vertex_2 = {{x2 * GLOBAL_SCALE, y2 * GLOBAL_SCALE}, {gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a}, {1, 1}};
	SDL_Vertex vertex_3 = {{x3 * GLOBAL_SCALE, y3 * GLOBAL_SCALE}, {gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a}, {1, 1}};

	SDL_Vertex vertices[] = {
	    vertex_1,
	    vertex_2,
	    vertex_3
	};

	SDL_RenderGeometry(local_renderer, NULL, vertices, 3, NULL, 0);
}

void gfxTriangleRel(int x, int y, int x2, int y2, int x3, int y3)
{
	int xx = (int) ((x - cameraX) * cameraZoom);
	int yy = (int) ((y - cameraY) * cameraZoom);
	int xx2 = (int) ((x2 - cameraX) * cameraZoom);
	int yy2 = (int) ((y2 - cameraY) * cameraZoom);
	int xx3 = (int) ((x3 - cameraX) * cameraZoom);
	int yy3 = (int) ((y3 - cameraY) * cameraZoom);
	gfxTriangle(xx, yy, xx2, yy2, xx3, yy3);
}

void gfxLine(int x, int y, int x2, int y2)
{
	SDL_SetRenderDrawColor(local_renderer, gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a);
	SDL_RenderDrawLine(local_renderer, x * GLOBAL_SCALE, y * GLOBAL_SCALE, x2 * GLOBAL_SCALE, y2 * GLOBAL_SCALE);
}

void gfxLineRel(int x, int y, int x2, int y2)
{
	int xx = (int) ((x - cameraX) * cameraZoom);
	int yy = (int) ((y - cameraY) * cameraZoom);
	int xx2 = (int) ((x2 - cameraX) * cameraZoom);
	int yy2 = (int) ((y2 - cameraY) * cameraZoom);
	gfxLine(xx, yy, xx2, yy2);
}

int gfxGetTextWidth(const char* str)
{
    return (int)(strlen(str) * FONT_W);
}

void gfxPrint(const char* str, int x, int y)
{
	int c = 0;
	while (str[c] != '\0')
	{
		gfxDrawRect(font_spr, gfxFontGetRect(((int) str[c]) - 32), (c*FONT_W) + x, y, FONT_W, FONT_H);
		c++;
	}
}

void gfxPrintf(const char* str, int x, int y, int limit, int align)
{
	int text_width = gfxGetTextWidth(str);
	int xc = ((limit / 2) - (text_width / 2));

	switch (align)
	{
		case ALIGN_RIGHT:
			gfxPrint(str, x + limit - text_width, y);
			break;
		case ALIGN_CENTER:
			gfxPrint(str, xc, y);
			break;
		default:
			gfxPrint(str, x, y);
			break;
	}
}

void gfxDrawImage(SDL_Texture *texture, int x, int y, int w, int h)
{
	SDL_Rect img_rect = {x * GLOBAL_SCALE, y * GLOBAL_SCALE, w * GLOBAL_SCALE, h * GLOBAL_SCALE};
	SDL_RenderCopy(local_renderer, texture, NULL, &img_rect);
}

void gfxDrawImageRel(SDL_Texture *texture, float x, float y, float w, float h)
{
	int xx = (int) ((x - cameraX) * cameraZoom);
	int yy = (int) ((y - cameraY) * cameraZoom);
	int ww = (int) (w * cameraZoom);
	int hh = (int) (h * cameraZoom);
	gfxDrawImage(texture, xx, yy, ww, hh);
}

void gfxDrawRect(SDL_Texture *texture, SDL_Rect rect, int x, int y, int w, int h)
{
	SDL_Rect img_rect = {x * GLOBAL_SCALE, y * GLOBAL_SCALE, w * GLOBAL_SCALE, h * GLOBAL_SCALE};
	SDL_RenderCopy(local_renderer, texture, &rect, &img_rect);
}

void gfxDrawRectScale(SDL_Texture *texture, SDL_Rect rect, int x, int y, int w, int h, int angle, float scale)
{
	int xx = (int) ((float) x * (float) GLOBAL_SCALE * scale);
	int yy = (int) ((float) y * (float) GLOBAL_SCALE * scale);
	int ww = (int) ((float) w * (float) GLOBAL_SCALE * scale);
	int hh = (int) ((float) h * (float) GLOBAL_SCALE * scale);
	SDL_Rect img_rect = {xx, yy, ww, hh};
	SDL_RenderCopyEx(local_renderer, texture, &rect, &img_rect, angle, NULL, SDL_FLIP_NONE);
}

void gfxDrawRectRel(SDL_Texture *texture, SDL_Rect rect, float x, float y, float w, float h)
{
	int xx = (int) ((x - cameraX) * cameraZoom);
	int yy = (int) ((y - cameraY) * cameraZoom);
	int ww = (int) (w * cameraZoom);
	int hh = (int) (h * cameraZoom);
	gfxDrawRect(texture, rect, xx, yy, ww, hh);
}

void gfxDrawRectangleThickRel(int x, int y, int w, int h, int t)
{
	gfxRectangleRel(x,y,w-t,t);
	gfxRectangleRel(x+t,y+h-t,w-t,t);
	gfxRectangleRel(x,y+t,t,h-t);
	gfxRectangleRel(x+w-t,y,t,h-t);
}

void gfxDrawRectangleThick(int x, int y, int w, int h, int t)
{
	gfxRectangle(x,y,w-t,t);
	gfxRectangle(x+t,y+h-t,w-t,t);
	gfxRectangle(x,y+t,t,h-t);
	gfxRectangle(x+w-t,y,t,h-t);
}
