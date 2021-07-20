#ifndef CELL_H
#define CELL_H
#include <set>
#include <random>
#include <SDL2/SDL.h>

std::set<int> getrandom(int num,int size);

class cell{
    public:
    int x,y,w,h;
    bool islei = false;
    bool isopen = false;
    bool isbiao = false;
    SDL_Rect rect = {x,y,w,h};
    SDL_Surface *sur = NULL;
    cell(int x,int y,int w,int h):x(x),y(y),w(w),h(h){};
    ~cell(){};
};
#endif