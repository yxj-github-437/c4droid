#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Window *win = nullptr;
SDL_Surface *sur = nullptr;
int init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	// 创建窗口
	win = SDL_CreateWindow(
							  // 标题
							  "我的SDL示例",
							  // 居中
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
	// 填充窗口
	SDL_FillRect(sur, nullptr, SDL_MapRGB(sur->format, 255, 255, 255));
	// 更新窗口
	SDL_UpdateWindowSurface(win);
	SDL_Delay(5000);
	// 清理
	SDL_FreeSurface(sur);
	SDL_DestroyWindow(win);
	// 退出
	SDL_Quit();
	return 0;
}
