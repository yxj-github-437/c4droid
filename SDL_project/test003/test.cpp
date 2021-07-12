#include <SDL2/SDL.h>

const int FRAMERATE = 1;

void draw(SDL_Window * win, SDL_Surface * sur, int x)
{
	//SDL_FillRect(sur, NULL, SDL_MapRGB(sur->format, 255, 255, 255));
	//SDL_UpdateWindowSurface(win);
	SDL_Rect rect = { x, 0, 50, 50 };
	SDL_FillRect(sur, &rect, SDL_MapRGB(sur->format, 255, 0, 0));
	SDL_UpdateWindowSurface(win);
}

SDL_Window *win = NULL;
SDL_Surface *sur = NULL;
int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	win =
		SDL_CreateWindow("SDL_test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
						 SDL_WINDOW_SHOWN);
	if (!win)
		return -1;
	sur = SDL_GetWindowSurface(win);
	if (!sur)
		return -2;
	int x = 0;
	SDL_FillRect(sur,NULL,SDL_MapRGB(sur->format,255,255,255));
	SDL_UpdateWindowSurface(win);
	while (x <= 1e3)
	{
		uint32_t begin = SDL_GetTicks();
		SDL_Event event;
		draw(win, sur, x++);
		if (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				break;
		uint32_t end = SDL_GetTicks();
		uint32_t time = end - begin;
		uint32_t rate = 100/ FRAMERATE;
		int32_t delay = rate - time;
		SDL_Delay(delay);
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
