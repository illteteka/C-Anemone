#ifndef OBJ_GUY_H
#define OBJ_GUY_H

void guyInit();
int guyNew(float x, float y);
void guySetTexture(SDL_Texture* texture);
void guyUpdate(float dt);
void guyDraw();

#endif