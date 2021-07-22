#include "draw.h"

int w = 0;

cell cell[100];

void Init()
{
	for (int i = 0; i < 100; ++i)
		cell[i].init(i);
	auto s = getrandom(15, 100);
  for (const int i:s)
		cell[i].islei = true;
}

void drawgrid(SDL_Renderer * render, SDL_Rect * rect)
{
	w = (rect->w) > (rect->h) ? (rect->h) : (rect->w);
	w /= 10;
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	for (int i = 0; i <= 10; i++)
	{
		SDL_RenderDrawLine(render, i * w + 5, H, i * w + 5, H + rect->w);
		SDL_RenderDrawLine(render, 5, H + i * w, rect->w + 5, H + i * w);
	}
}

void draw(SDL_Renderer * render)
{
	SDL_SetRenderDrawColor(render, 192, 192, 192, 255);
	for (int i = 0; i < 100; ++i)
	{
		if (cell[i].isopen == false)
		{
			if (cell[i].isbiao == false)
			{
				SDL_Rect rect1 = { (i % 10) * w + 5 + 1, (i / 10) * w + H + 1, w - 2, w - 2 };
				SDL_RenderFillRect(render, &rect1);
			}
			else
			{
				SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
				SDL_Rect rect1 = { (i % 10) * w + 5 + 1, (i / 10) * w + H + 1, w - 2, w - 2 };
				SDL_RenderFillRect(render, &rect1);
				SDL_SetRenderDrawColor(render, 192, 192, 192, 255);
			}
		}
	}
}

void drawbackground(SDL_Window * win, SDL_Renderer * render)
{
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	SDL_Rect rect = { 0, 0, w, h };
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_RenderFillRect(render, &rect);
}

void setopen(int i)
{
	if (i >= 0 && i < 100)
		if (cell[i].isbiao == false)
			cell[i].isopen = true;
}

void setbiao(int i)
{
	if (i >= 0 && i < 100)
		if (cell[i].isopen == false)
			cell[i].isbiao = !cell[i].isbiao;
}

int getnum(int i)
{
	int sum = 0;
	return sum;
}
