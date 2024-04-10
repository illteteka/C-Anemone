#include "../include.h"

#define MAX_BRUSH 2

SDL_Texture *brush_local_canvas = NULL;
SDL_Texture* brush_guy_local_texture = NULL;

struct brush
{
	float x;
	float y;
	bool active;
};

int brushCount = 0;
struct brush brushData[MAX_BRUSH];

void brushGuySetTexture(SDL_Texture* texture)
{
	brush_guy_local_texture = texture;
}

void brushSetCanvasTexture(SDL_Texture *canvas)
{
	brush_local_canvas = canvas;
}

void brushInit()
{	
    brushCount = 0;
    memset(brushData, 0, sizeof(brushData));
}

int brushNew(float x, float y)
{
	struct brush tbl = {x, y, true};
	brushData[brushCount] = tbl;
	brushCount++;

	return brushCount - 1;
}

void brushUpdate(float dt)
{
	int i = 0;
	while (i < sizeof(brushData) / sizeof(brushData[0]))
	{
		if (brushData[i].active)
		{
			if (up_key == _ON)
				brushData[i].y -= 1 * dt;

			if (down_key == _ON)
				brushData[i].y += 1 * dt;

			if (left_key == _ON)
				brushData[i].x -= 1 * dt;

			if (right_key == _ON)
				brushData[i].x += 1 * dt;
		
			if (cross_key == _ON)
			{
				gfxSetCanvas(canvas_example);
				gfxDrawImage(brush_guy_local_texture, brushData[i].x, brushData[i].y, 32, 32);
				gfxResetCanvas();
			}

			if (triangle_key == _ON)
			{
				int xx = brushData[i].x;
				int yy = brushData[i].y;
				int ww = 16;
				int hh = 16;
				gfxEraseCanvas(canvas_example, canvas_eraser, xx, yy, ww, hh);
			}

		}

	    i++;
	}
}

void brushDraw()
{
	int brush_height = 10;
	int brush_window = 3;

	int i = 0;
	while (i < sizeof(brushData) / sizeof(brushData[0]))
	{
		if (brushData[i].active)
		{
			gfxSetColor(0, 0, 255, 255);
			gfxRectangle(brushData[i].x, brushData[i].y - brush_height - brush_window + 1, 1, brush_height);
			gfxRectangle(brushData[i].x, brushData[i].y + brush_window, 1, brush_height);
			gfxRectangle(brushData[i].x - brush_height - brush_window + 1, brushData[i].y, brush_height, 1);
			gfxRectangle(brushData[i].x + brush_window, brushData[i].y, brush_height, 1);
		}

	    i++;
	}
}