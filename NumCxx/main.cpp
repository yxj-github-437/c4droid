#include "NcArray/NcArray.h"
#include "linalg/linalg.h"
#include <iostream>
int main(int argc, char **argv)
{
	NcArray<double> a =
		{{1, 2, 3, 4},
		 {2, -3, 4, 2},
		 {1, 3, 3, 4},
		 {1, 4, 5, -6}};
	auto b = abs(a.T());
	auto c = b.T();
	auto d = eye<double>(4);
	NcArray<double> e =
		{{1, 2, -2, 3},
		 {4, -3, 3, 12},
		 {3, -1, 1, 9}};
	show(b * c);
	std::cout << std::endl;
	std::cout << (b * d).isSymmetry() << std::endl;
	std::cout << std::endl;
	std::cout << Mul(a, c).isSquare() << std::endl;
	std::cout << std::endl;
	show(b.row(0));
	std::cout << std::endl;
	show(a.row_sum());
	std::cout << std::endl;
	a.rowSwap(0, 1);
	a /= 2;
	show(a / 2);
	std::cout << std::endl;
	show(d * c);
	std::cout << std::endl
			  << max(b)
			  << std::endl;
	std::cout << std::endl;
	show(linalg::inv(a));
	std::cout << std::endl;
	std::cout << linalg::det(b) << std::endl;
	std::cout << linalg::rank(e)<<std::endl;
	return 0;
}
