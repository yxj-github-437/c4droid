#include "draw.h"
#include <SDL2/SDL.h>

void draw(SDL_Renderer* render,SDL_Rect* rect){
    int w = (rect->w)>(rect->h)?(rect->h):(rect->w);
    w /= 10;
    SDL_SetRenderDrawColor(render,0,0,0,255);
    for(int i=0;i<=10;i++)
    {
    SDL_RenderDrawLine(render,i*w,0,i*w,rect->w);
    SDL_RenderDrawLine(render,0,i*w,rect->w,i*w);
    }
    SDL_RenderPresent(render);   
}