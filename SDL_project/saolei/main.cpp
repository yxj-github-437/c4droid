#include <SDL2/SDL.h>
#include "draw.h"

SDL_Window *win = nullptr;
SDL_Renderer *rend = nullptr;
SDL_Rect rect={0,0,0,0};

int flag = 0;					// 0表示翻开,1表示标记
const int flagwidth = 100;
SDL_Event event;
bool init(int w = 400, int h = 300)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	win =
		SDL_CreateWindow("saolei", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
						 SDL_WINDOW_SHOWN);
	if (win == nullptr)
		return false;
	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (rend == nullptr)
		return false;
	SDL_GetWindowSize(win,&w,&h);
	rect.w=w-10;
	rect.h=h;
	return true;
}

void close()
{
	// 释放渲染器
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void drawflag()
{
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	SDL_Rect rect = { 0, w + H + 100, w, flagwidth };
	if (flag == 0)
		SDL_SetRenderDrawColor(rend, 192, 192, 192, 255);
	else if (flag == 1)
		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	SDL_RenderFillRect(rend, &rect);
}

int main(int argc, char **argv)
{
	if (!init())
		return 1;
	double Tx = 0, Ty = 0;
	int w, h;
	int i;
	SDL_GetWindowSize(win, &w, &h);
	w /= 10;
	Init();
	while (1)
	{
		SDL_RenderClear(rend);
		drawbackground(win, rend);
		drawgrid(rend, &rect);
		drawflag();
		draw(rend);
		SDL_RenderPresent(rend);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break;
			else if (event.type == SDL_FINGERUP)
			{
				Tx = event.tfinger.x;
				Ty = event.tfinger.y;
				int x = Tx * w * 10;
				int y = Ty * h;
				if (x >= 0 && x <= w * 10 && y >= w * 10 + H + 100
					&& y <= w * 10 + H + 100 + flagwidth)
				{
					flag = !flag;
				}
				else
				{
					i = (x - 5) / w + (y - H) / w * 10;
					if (flag == 0)
						setopen(i);
					if (flag == 1)
						setbiao(i);
				}
			}
		}
	}
	close();
	return 0;
}
