#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "draw.h"

SDL_Window* win = nullptr;
SDL_Renderer *rend = nullptr;
SDL_Rect rect = {0,0,450,640};
SDL_Event event;

bool init(int w=400,int h=300){
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("saolei",
               SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
               w,h,SDL_WINDOW_SHOWN);
    if(win == nullptr)
        return false;
    rend = SDL_CreateRenderer(win, -1,0);
    if(rend == nullptr)
        return false;
    SDL_SetRenderDrawColor(rend,255,255,255,255);
    SDL_RenderDrawRect(rend,&rect);
    SDL_RenderFillRect(rend,&rect);
    SDL_RenderPresent(rend);
    return true;
}

void quit(){
    //释放渲染器
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}


int main(int argc,char** argv){
    if(!init(450,640))
        return 1;
    while(1){
        draw(rend,&rect);
        if(SDL_PollEvent(&event))
            if(event.type == SDL_QUIT)
                break;
    }
    quit();
    return 0;
}