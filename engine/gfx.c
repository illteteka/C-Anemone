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
};

struct col gfxColor = {0, 0, 0};

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

void gfxFontLoadRects()
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

void gfxFontFree()
{
	free(font_rect);
}

void gfxSetColor(int r, int g, int b)
{
	gfxColor.r = r;
	gfxColor.g = g;
	gfxColor.b = b;
	SDL_SetTextureColorMod(font_spr,r,g,b);
}

int gfxGetColorR()
{
	return gfxColor.r;
}

int gfxGetColorG()
{
	return gfxColor.g;
}

int gfxGetColorB()
{
	return gfxColor.b;
}

void gfxRectangle(int x, int y, int w, int h)
{
	SDL_Rect temp_rect = {x, y, w, h};
	SDL_SetRenderDrawColor(local_renderer, gfxColor.r, gfxColor.g, gfxColor.b, 255);
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
	SDL_Vertex vertex_1 = {{x, y}, {gfxColor.r, gfxColor.g, gfxColor.b, 255}, {1, 1}};
	SDL_Vertex vertex_2 = {{x2, y2}, {gfxColor.r, gfxColor.g, gfxColor.b, 255}, {1, 1}};
	SDL_Vertex vertex_3 = {{x3, y3}, {gfxColor.r, gfxColor.g, gfxColor.b, 255}, {1, 1}};

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
	SDL_SetRenderDrawColor(local_renderer, gfxColor.r, gfxColor.g, gfxColor.b, 255);
	SDL_RenderDrawLine(local_renderer, x, y, x2, y2);
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
	return strlen(str) * FONT_W;
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

	switch (align)
	{
		case ALIGN_RIGHT:
			gfxPrint(str, x + limit - text_width, y);
			break;
		case ALIGN_CENTER:
			int xc = ((SCREEN_WIDTH / 2) - (text_width / 2));
			gfxPrint(str, xc, y);
			break;
		default:
			gfxPrint(str, x, y);
			break;
	}
}

void gfxDrawImage(SDL_Texture *texture, int x, int y, int w, int h)
{
	SDL_Rect img_rect = {x, y, w, h};
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
	SDL_Rect img_rect = {x, y, w, h};
	SDL_RenderCopy(local_renderer, texture, &rect, &img_rect);
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