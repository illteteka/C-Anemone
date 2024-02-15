#ifndef OBJ_BRUSH_H
#define OBJ_BRUSH_H

void brushInit();
int brushNew(float x, float y);
void brushSetCanvasTexture(SDL_Texture *canvas);
void brushGuySetTexture(SDL_Texture* texture);
void brushUpdate(float dt);
void brushDraw();

#endif