#ifndef GFX_H
#define GFX_H

#define ALIGN_LEFT 0
#define ALIGN_CENTER 1
#define ALIGN_RIGHT 2

void gfxFontSetTexture(SDL_Texture* texture);
void gfxFontLoadRects(void);
void gfxFontFree(void);
void gfxSetColor(int r, int g, int b, int a);
int gfxGetColorR(void);
int gfxGetColorG(void);
int gfxGetColorB(void);
int gfxGetColorA(void);
void gfxRectangle(int x, int y, int w, int h);
void gfxRectangleRel(int x, int y, int w, int h);
void gfxTriangle(int x, int y, int x2, int y2, int x3, int y3);
void gfxTriangleRel(int x, int y, int x2, int y2, int x3, int y3);
void gfxLine(int x, int y, int x2, int y2);
void gfxLineRel(int x, int y, int x2, int y2);
int gfxGetTextWidth(const char* str);
void gfxPrint(const char* str, int x, int y);
void gfxPrintf(const char* str, int x, int y, int limit, int align);
void gfxDrawImage(SDL_Texture *texture, int x, int y, int w, int h);
void gfxDrawImageRel(SDL_Texture *texture, float x, float y, float w, float h);
void gfxDrawRect(SDL_Texture *texture, SDL_Rect rect, int x, int y, int w, int h);
void gfxDrawRectScale(SDL_Texture *texture, SDL_Rect rect, int x, int y, int w, int h, int angle, float scale);
void gfxDrawRectRel(SDL_Texture *texture, SDL_Rect rect, float x, float y, float w, float h);
void gfxDrawRectangleThickRel(int x, int y, int w, int h, int t);
void gfxDrawRectangleThick(int x, int y, int w, int h, int t);
void gfxSetCanvas(SDL_Texture *canvas);
void gfxResetCanvas(void);
void gfxClear(void);

#endif
