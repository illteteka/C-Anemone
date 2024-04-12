#include "../include.h"

#define FONT_W 8
#define FONT_H 18

#define FONT_MAX 96

SDL_Rect* font_rect;
SDL_Texture* font_spr = NULL;

struct col
{
	int r;
	int g;
	int b;
	int a;
};

struct col gfxColor = {0, 0, 0, 255};

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
	font_rect = malloc(FONT_MAX * sizeof(SDL_Rect));

	int i = 0;
	int j = 0;
	int k = 0;
	while (i < FONT_MAX)
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
	SDL_SetRenderDrawColor(renderer, gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a);
	SDL_RenderClear(renderer);
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
	SDL_Rect temp_rect = {x, y, w, h};
	SDL_SetRenderDrawColor(renderer, gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a);
	SDL_RenderFillRect(renderer, &temp_rect);
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
	SDL_Vertex vertex_1 = {{x, y}, {gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a}, {1, 1}};
	SDL_Vertex vertex_2 = {{x2, y2}, {gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a}, {1, 1}};
	SDL_Vertex vertex_3 = {{x3, y3}, {gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a}, {1, 1}};

	SDL_Vertex vertices[] = {
	    vertex_1,
	    vertex_2,
	    vertex_3
	};

	SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
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
	SDL_SetRenderDrawColor(renderer, gfxColor.r, gfxColor.g, gfxColor.b, gfxColor.a);
	SDL_RenderDrawLine(renderer, x, y, x2, y2);
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
	SDL_Rect img_rect = {x, y, w, h};
	SDL_RenderCopy(renderer, texture, NULL, &img_rect);
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
	SDL_RenderCopy(renderer, texture, &rect, &img_rect);
}

void gfxDrawRectScale(SDL_Texture *texture, SDL_Rect rect, int x, int y, int w, int h, int angle, float scale)
{
	int xx = (int) ((float) x * scale);
	int yy = (int) ((float) y * scale);
	int ww = (int) ((float) w * scale);
	int hh = (int) ((float) h * scale);
	SDL_Rect img_rect = {xx, yy, ww, hh};
	SDL_RenderCopyEx(renderer, texture, &rect, &img_rect, angle, NULL, SDL_FLIP_NONE);
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

void gfxNewCanvas(SDL_Texture *texture)
{
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
}

void gfxDrawCanvas(SDL_Texture *texture, float x, float y, bool visible)
{
	if (visible)
	{
		SDL_SetTextureColorMod(texture, gfxColor.r, gfxColor.g, gfxColor.b);
		SDL_SetTextureAlphaMod(texture, gfxColor.a);
		SDL_Rect temp_rect = {(int) x, (int) y, CANVAS_SIZE, CANVAS_SIZE};
		SDL_RenderCopy(renderer, texture, NULL, &temp_rect);
	}
	else
	{
		SDL_SetTextureAlphaMod(texture, 0);
		SDL_Rect temp_rect = {1, 1, 1, 1};
		SDL_RenderCopy(renderer, texture, NULL, &temp_rect);
	}
}

void gfxEraseCanvas(SDL_Texture *texture, SDL_Texture *eraser, int x, int y, int w, int h)
{
	// Clamp x and y so we don't have an invalid rect
	int xx = fmax(fmin(x, CANVAS_SIZE), 0);
	int yy = fmax(fmin(y, CANVAS_SIZE), 0);
	int ww = w;
	int hh = h;

	SDL_Rect temp_rect = {0, 0, CANVAS_SIZE, CANVAS_SIZE};
	SDL_Rect temp_top = {0, 0, CANVAS_SIZE, yy};
	SDL_Rect temp_bottom = {0, yy + hh, CANVAS_SIZE, CANVAS_SIZE - yy - hh};
	SDL_Rect temp_left = {0, yy, xx, hh};
	SDL_Rect temp_right = {xx + ww, yy, CANVAS_SIZE - xx - ww, hh};

	// Show the eraser
	SDL_SetTextureAlphaMod(eraser, 255);
	SDL_SetRenderTarget(renderer, eraser);

	// Clear the eraser
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	
	// Copy from the canvas everywhere where we don't want to erase
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderCopy(renderer, texture, &temp_top, &temp_top);
	SDL_RenderCopy(renderer, texture, &temp_bottom, &temp_bottom);
	SDL_RenderCopy(renderer, texture, &temp_left, &temp_left);
	SDL_RenderCopy(renderer, texture, &temp_right, &temp_right);

	// Clear the canvas
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	
	// Copy the eraser to the canvas
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderCopy(renderer, eraser, &temp_rect, &temp_rect);
	SDL_SetRenderTarget(renderer, NULL);

	// Hide the eraser
	SDL_SetTextureAlphaMod(eraser,0);
	SDL_SetRenderTarget(renderer, NULL);
}

void gfxSetCanvas(SDL_Texture *texture)
{
	SDL_SetRenderTarget(renderer, texture);
}

void gfxResetCanvas(void)
{
	SDL_SetRenderTarget(renderer, NULL);
}