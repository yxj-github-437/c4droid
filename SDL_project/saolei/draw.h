#ifndef DRAW_H
#define DRAW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "cell.h"

const int H = 300;

void draw(SDL_Renderer * render);
void drawgrid(SDL_Renderer * render, SDL_Rect * rect);
void drawbackground(SDL_Window * win, SDL_Renderer * render);
void Init();
void setopen(int i);
void setbiao(int i);
int getnum(int);
#endif
