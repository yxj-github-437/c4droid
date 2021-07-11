#ifndef LINALG_H
#define LINALG_H
#include "../NcArray/NcArray.h"
namespace linalg
{
template <typename _T>
NcArray<_T> solve(const NcArray<_T> &array, const NcArray<_T> &b)
{
}

template <typename _T>
_T det(const NcArray<_T> &array)
{
	int r = array.row();
	NcArray<_T> arr = array;
	_T p = 0;
	_T max = 0;
	_T det = 1;
	int c = r;
	int max_r = 0;
	if (arr.isSquare() == true)
	{
		for (int i = 0; i < r; i++)
		{
			if (arr(i, i) == 0)
			{
				max_r = i;
				for (int j = i; j < c; j++)
					if (fabs(arr(j, i)) > max)
					{
						max_r = j;
						max = arr(j, i);
					}
				max = 0;
				arr.rowSwap(i, max_r);
				det *= -1;
			}
			if (arr(i, i) != 0)
				for (int j = i + 1; j < r; j++)
				{
					p = arr(j, i) / arr(i, i);
					for (int k = 0; k < c; k++)
					{
						arr[j][k] -= p * arr(i, k);
					}
				}
		}
		for (int i = 0; i < r; i++)
			det *= arr(i, i);
		return det;
	}
	else
		throw;
}

template <typename _T>
NcArray<_T> jacobi(const NcArray<_T> &a, const NcArray<_T> &b, const _T &e = 1e-10)
{
	if (a.isSquare() == true && a.row() == b.row())
	{
		int r = a.row();
		int c = r;
		int b_row = b.row();
		int b_col = b.col();
		int n = 0;
		_T rr = 0;
		NcArray<_T> x0(b_row, b_col);
		NcArray<_T> x1 = x0;
		while (1)
		{
			for (int k = 0; k < b_col; k++)
				for (int i = 0; i < b_row; i++)
				{
					for (int j = 0; j < c; j++)
						if (j != i)
							rr += a(i, j) * x0(j, k);
					x1[i][k] = (b(i, k) - rr) / a(i, i);
					rr = 0;
				}
			if (max(abs(x1 - x0)) < e)
				break;
			x0 = x1;
			n++;
			if (n > 200)
				throw;
		}
		return x1;
	}
	else
		throw;
};

template <typename _T>
NcArray<_T> guassSeidel(const NcArray<_T> &a, const NcArray<_T> &b, const double &e = 1e-10)
{
	int r = a.row();
	int c = r;
	int b_row = b.row();
	int b_col = b.col();
	if (a.isSquare() == true && r == b_row)
	{
		int n = 0;
		_T rr = 0;
		_T pp = 0;
		NcArray<_T> x0(b_row, b_col);
		NcArray<_T> x1 = x0;
		while (1)
		{
			for (int k = 0; k < b_col; k++)
				for (int i = 0; i < b_row; i++)
				{
					for (int j = 0; j < i; j++)
						rr += a(i, j) * x1(j, k);
					for (int j = i + 1; j < c; j++)
						pp += a(i, j) * x0(j, k);
					x1[i][k] = (b(i, k) - rr - pp) / a(i, i);
					rr = 0;
					pp = 0;
				}
			if (max(abs(x1 - x0)) < e)
				break;
			x0 = x1;
			n++;
			if (n > 200)
				throw;
		}
		return x1;
	}
	else
		throw;
};

template <typename _T>
NcArray<_T> inv(const NcArray<_T> &array)
{
	int r = array.row();
	NcArray<_T> arr = array;
	NcArray<_T> e = eye<_T>(r);
	NcArray<_T> x(r, r);
	_T p = 0;
	_T max = 0;
	int c = r;
	int max_r = 0;
	if (arr.isSquare() == true)
	{
		for (int i = 0; i < r; i++)
		{
			if (arr(i, i) == 0)
			{
				max_r = i;
				for (int j = i; j < c; j++)
					if (fabs(arr(j, i)) > max)
					{
						max_r = j;
						max = arr(j, i);
					}
				max = 0;
				arr.rowSwap(i, max_r);
			}
			if (arr(i, i) != 0)
				for (int j = i + 1; j < r; j++)
				{
					p = arr(j, i) / arr(i, i);
					for (int k = 0; k < c; k++)
					{
						arr[j][k] -= p * arr(i, k);
						e[j][k] -= p * e(i, k);
					}
				}
		}
		for (int i = 0; i < r; i++)
			if (arr(i, i) == 0)
				throw;
		for (int k = 0; k < c; k++)
		{
			x[r - 1][k] = e(r - 1, k) / arr(r - 1, r - 1);
			for (int i = r - 2; i >= 0; i--)
			{
				p = 0;
				for (int j = i + 1; j < r; j++)
					p += arr(i, j) * x(j, k);
				x[i][k] = (e(i, k) - p) / arr(i, i);
			}
		}
		return x;
	}
	else
		throw;
}

template <typename _T>
int rank(const NcArray<_T> &array)
{
	int r = array.row();
	NcArray<_T> arr = array;
	_T p = 0;
	_T max = 0;
	int rank = 0;
	int c = array.col();
	int max_r = 0;
	int min = r < c ? r : c;
	int k = 0;
	for (int i = 0; i < r; i++)
	{
		if (i < min)
		{
			if (arr(i, i) == 0)
			{
				max_r = i;
				for (int j = i; j < r; j++)
					if (fabs(arr(j, i)) > max)
					{
						max_r = j;
						max = arr(j, i);
					}
				max = 0;
				arr.rowSwap(i, max_r);
			}
			if (arr(i, i) != 0)
				for (int j = i + 1; j < r; j++)
				{
					p = arr(j, i) / arr(i, i);
					for (int k = 0; k < c; k++)
					{
						arr[j][k] -= p * arr(i, k);
					}
				}
		}
	}
	for (int i = 0; i < min; i++)
	{
		for (int j = 0; j < c; j++)
			if (arr(i, j) != 0)
				k++;
		if (k > 0)
			rank++;
		k = 0;
	}
	return rank;
}
}
#endif