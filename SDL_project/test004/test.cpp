#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window *win = nullptr;
SDL_Surface *sur = nullptr;
SDL_Surface *imgsur =IMG_Load("1.jpg");
int w=imgsur->w;
int h=imgsur->h;
int init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	// 创建窗口
	win = SDL_CreateWindow(
	// 标题
	"我的SDL示例",
	// 居中
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	// 宽高
	w,h,
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
	SDL_Rect rect = {0,0,w,h};
	// 更新窗口
	SDL_UpdateWindowSurface(win);
	SDL_BlitSurface(imgsur,&rect,sur,&rect);
	SDL_UpdateWindowSurface(win);
	SDL_Delay(5000);
	// 清理
	SDL_FreeSurface(sur);
	SDL_FreeSurface(imgsur);
	SDL_DestroyWindow(win);
	// 退出
	SDL_Quit();
	return 0;
}
