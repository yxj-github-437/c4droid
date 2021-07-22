#ifndef CELL_H
#define CELL_H

#include <set>
#include <random>
#include <ctime>
#include <SDL2/SDL.h>

std::set < int >getrandom(int num, int size);

class cell
{
  public:
	int id;
	bool islei = false;
	bool isopen = false;
	bool isbiao = false;
	  cell()
	{
	};
	~cell()
	{
	};
	void init(int Id)
	{
		id = Id;
	};
};
#endif
