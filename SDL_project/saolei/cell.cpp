#include "cell.h"
std::set < int >getrandom(int num, int size)
{
	std::set < int >s;
	std::default_random_engine random(time(nullptr));
	std::uniform_int_distribution < int >dis(0, size-1);
	while (s.size() < num)
	{
		s.insert(dis(random));
	}
	return s;
}
