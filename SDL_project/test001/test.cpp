#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_thread.h"
// 窗口指针
SDL_Window *win = nullptr;
// 定义一个刷屏表面
SDL_Surface *sur = nullptr;
// 初始化
int init()
{
	// 初始化所有子系统成功返回0
	SDL_Init(SDL_INIT_EVERYTHING);
	// 创建窗口
	win = SDL_CreateWindow(
	// 标题
	"我的SDL示例",
	// 居中
	SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
	// 宽高
	200, 300,
	// 状态
	SDL_WINDOW_SHOWN);
	if (win == nullptr)
		return -1;
	// 获取w的表面
	sur = SDL_GetWindowSurface(win);
	if (sur == nullptr)
		return -2;
	return 0;
}

int main(int argc, char **argv)
{
	if (init() != 0)
		return -1;
	SDL_Event event;
	int keypress = 0;
	for (int i = 0; !keypress; i++)
	{
		int R = 0, G = 0, B = 0;
		switch (i % 3)
		{
		case 0:
			R = 255;
			G = 0;
			B = 0;
			break;
		case 1:
			R = 0;
			G = 255;
			B = 0;
			break;
		case 2:
			R = 0;
			G = 0;
			B = 255;
			break;
		}
		// 填充窗口
		SDL_FillRect(sur, nullptr, SDL_MapRGB(sur->format, R, G, B));
		// 更新窗口
		SDL_UpdateWindowSurface(win);
		SDL_Delay(2000);
		while (SDL_PollEvent(&event))
			switch (event.type)
			{
			case SDL_QUIT:
				keypress = 1;
				break;
			case SDL_FINGERUP:
				keypress = 1;
				break;
			}
	}
	// 清理
	SDL_FreeSurface(sur);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
