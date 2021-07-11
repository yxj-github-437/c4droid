#ifndef NCARRAY_INL
#define NCARRAY_INL
#include "NcArray.h"
#include <iostream>
#include <cmath>
template <typename _T>
NcArray<_T>::NcArray(const std::initializer_list<std::initializer_list<_T>> &list)
{
	m_row = list.size();
	m_col = list.begin()->size();
	for (auto i : list)
		if (i.size() != m_col)
			throw;
	m_size = m_row * m_col;
	m_ptr = new _T[m_size];
	int size = 0;
	for (auto i : list)
		for (auto j : i)
		{
			m_ptr[size] = j;
			size++;
		}
}

template <typename _T>
NcArray<_T>::NcArray(const int &r, const int &c) : m_row(r), m_col(c), m_size(c * r)
{
	m_ptr = new _T[m_size];
	for (int i = 0; i < m_size; i++)
		m_ptr[i] = 0;
}

template <typename _T>
NcArray<_T>::NcArray(const NcArray &array)
{
	m_row = array.m_row;
	m_col = array.m_col;
	m_size = m_row * m_col;
	m_ptr = new _T[m_size];
	for (int i = 0; i < m_size; i++)
		m_ptr[i] = array.m_ptr[i];
}

template <typename _T>
_T NcArray<_T>::operator()(const int &i, const int &j) const
{
	if (i < m_row && j < m_col && i >= 0 && j >= 0)
		return m_ptr[i * m_col + j];
	else
		throw;
}

template <typename _T>
_T *NcArray<_T>::operator[](const int &i)
{
	if (i >= m_row && i < 0)
		throw;
	else
		return m_ptr + i * m_col;
}

template <typename _T>
bool NcArray<_T>::operator==(const NcArray &array)
{
	if (m_row == array.m_row && m_col == array.m_col)
	{
		for (int i = 0; i < m_size; i++)
			if (m_ptr[i] != array.m_ptr[i])
				return false;
		return true;
	}
	return false;
}

template <typename _T>
NcArray<_T> NcArray<_T>::T()
{
	NcArray<_T> array(m_col, m_row);
	for (int i = 0; i < array.m_row; i++)
		for (int j = 0; j < array.m_col; j++)
			array[i][j] = (*this)(j, i);
	return array;
}

template <typename _T>
NcArray<_T> NcArray<_T>::operator=(const NcArray &array)
{
	m_row = array.m_row;
	m_col = array.m_col;
	m_size = array.m_size;
	for (int i = 0; i < m_size; i++)
		m_ptr[i] = array.m_ptr[i];
	return *this;
}

template <typename _T>
NcArray<_T> NcArray<_T>::operator+(const NcArray &array)
{
	if (m_row == array.m_row && m_col == array.m_col)
	{
		NcArray<_T> arr = *this;
		for (int i = 0; i < m_size; i++)
			arr.m_ptr[i] += m_ptr[i];
		return arr;
	}
	else
		throw;
}

template <typename _T>
NcArray<_T> NcArray<_T>::operator-(const NcArray &array) const
{
	if (m_row == array.m_row && m_col == array.m_col)
	{
		NcArray<_T> arr = *this;
		for (int i = 0; i < m_size; i++)
			arr.m_ptr[i] -= array.m_ptr[i];
		return arr;
	}
	else
		throw;
}

template <typename _T>
NcArray<_T> NcArray<_T>::operator-()
{
	NcArray<_T> arr = *this;
	for (int i = 0; i < m_size; i++)
		arr.m_ptr[i] = -this->m_ptr[i];
	return arr;
}

template <typename _T>
NcArray<_T> NcArray<_T>::operator*(const NcArray &array)
{
	if (m_col == array.m_row)
	{
		NcArray<_T> arr(m_row, array.m_col);
		_T r = 0;
		for (int i = 0; i < arr.m_row; i++)
			for (int j = 0; j < arr.m_col; j++)
			{
				for (int k = 0; k < m_col; k++)
					r += m_ptr[i * m_col + k] * array.m_ptr[k * array.m_col + j];
				arr[i][j] = r;
				r = 0;
			}
		return arr;
	}
	else
		throw;
}

template <typename _T>
NcArray<_T> NcArray<_T>::operator/(const _T &e)
{
	NcArray<_T> arr = *this;
	for (int i = 0; i < arr.m_size; i++)
		arr.m_ptr[i] /= e;
	return arr;
}

template <typename _T>
NcArray<_T> NcArray<_T>::operator+=(const NcArray &array)
{
	if (m_row == array.m_row && m_col == array.m_col)
	{
		for (int i = 0; i < m_size; i++)
			m_ptr[i] += array.m_ptr[i];
		return *this;
	}
	else
		throw;
}

template <typename _T>
NcArray<_T> NcArray<_T>::operator-=(const NcArray &array)
{
	if (m_row == array.m_row && m_col == array.m_col)
	{
		for (int i = 0; i < m_size; i++)
			m_ptr[i] -= array.m_ptr[i];
		return *this;
	}
	else
		throw;
}

template <typename _T>
NcArray<_T> NcArray<_T>::operator*=(const NcArray &array)
{
	if (m_col == array.m_row)
	{
		*this = (*this) * array;
		return *this;
	}
	else
		throw;
}

template <typename _T>
NcArray<_T> NcArray<_T>::operator/=(const _T &e)
{
	for (int i = 0; i < m_size; i++)
		m_ptr[i] /= e;
	return *this;
}

template <typename _T>
NcArray<_T>::~NcArray()
{
	if (m_ptr != nullptr)
	{
		delete[] m_ptr;
		m_ptr = nullptr;
	}
}

template <typename _T>
NcArray<_T> NcArray<_T>::row(const int &r)
{
	NcArray<_T> arr(1, m_col);
	for (int i = 0; i < m_col; i++)
		arr.m_ptr[i] = (*this)(r, i);
	return arr;
}

template <typename _T>
NcArray<_T> NcArray<_T>::col(const int &c)
{
	NcArray<_T> arr(m_row, 1);
	for (int i = 0; i < m_row; i++)
		arr.m_ptr[i] = (*this)(i, c);
	return arr;
}

template <typename _T>
void NcArray<_T>::show()
{
	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
		{
			if (i == 0 && j == 0)
				std::cout << "[";
			if (i != 0 && j == 0)
				std::cout << " ";
			if (j == 0)
				std::cout << "[";
			if (fabs((*this)(i, j)) < 1e-8)
				std::cout << 0;
			else
				std::cout << (*this)(i, j);
			if (j != m_col - 1)
				std::cout << "\t";
			if (j == m_col - 1)
			{
				if (i == m_row - 1)
					std::cout << "]]\n";
				else
					std::cout << "]\n";
			}
		}
}

template <typename _T>
_T NcArray<_T>::sum()
{
	_T sum = 0;
	for (int i = 0; i < m_size; i++)
		sum += m_ptr[i];
	return sum;
}

template <typename _T>
NcArray<_T> NcArray<_T>::row_sum()
{
	NcArray<_T> arr(m_row, 1);
	for (int i = 0; i < m_row; i++)
		for (int j = 0; j < m_col; j++)
			arr[i][0] += (*this)(i, j);
	return arr;
}

template <typename _T>
NcArray<_T> NcArray<_T>::col_sum()
{
	NcArray<_T> arr(1, m_col);
	for (int i = 0; i < m_col; i++)
		for (int j = 0; j < m_row; j++)
			arr[0][i] += (*this)(j, i);
	return arr;
}

template <typename _T>
NcArray<_T> NcArray<_T>::rowSwap(const int &m1, const int &m2)
{
	if (m1 < m_row && m2 < m_row && m1 >= 0 && m2 >= 0)
	{
		_T temp[m_col];
		for (int i = 0; i < m_col; i++)
			temp[i] = (*this)(m1, i);
		for (int i = 0; i < m_col; i++)
			(*this)[m1][i] = (*this)(m2, i);
		for (int i = 0; i < m_col; i++)
			(*this)[m2][i] = temp[i];
		return *this;
	}
	else
		throw;
}

template <typename _T>
bool NcArray<_T>::isSquare() const
{
	if (m_row == m_col)
		return true;
	else
		return false;
}

template <typename _T>
bool NcArray<_T>::isSymmetry()
{
	if (this->isSquare() == true)
	{
		for (int i = 0; i < m_row; i++)
			for (int j = 0; j < i; j++)
				if ((*this)(i, j) != (*this)(j, i))
					return false;
		return true;
	}
	else
		return false;
}

template <typename _T>
NcArray<_T> Mul(const NcArray<_T> &arr1, const NcArray<_T> &arr2)
{
	if (arr1.row() == arr2.row() && arr1.col() == arr2.col())
	{
		NcArray<_T> arr = arr1;
		int r = arr.row();
		int c = arr.col();
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				arr[i][j] *= arr2(i, j);
		return arr;
	}
	else
		throw;
}

template <typename _T>
NcArray<_T> abs(const NcArray<_T> &array)
{
	NcArray<_T> arr = array;
	int r = array.row();
	int c = array.col();
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			arr[i][j] = fabs(arr(i, j));
	return arr;
}

template <typename _T>
void show(const NcArray<_T> &array)
{
	int r = array.row();
	int c = array.col();
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			if (i == 0 && j == 0)
				std::cout << "[";
			if (i != 0 && j == 0)
				std::cout << " ";
			if (j == 0)
				std::cout << "[";
			if (fabs(array(i, j)) < 1e-8)
				std::cout << 0;
			else
				std::cout << array(i, j);
			if (j != c - 1)
				std::cout << "\t";
			if (j == c - 1)
			{
				if (i == r - 1)
					std::cout << "]]\n";
				else
					std::cout << "]\n";
			}
		}
}

template <typename _T>
_T max(const NcArray<_T> &array)
{
	_T max = array(0, 0);
	int r = array.row();
	int c = array.col();
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			if (array(i, j) > max)
				max = array(i, j);
	return max;
}

template <typename _T>
_T min(const NcArray<_T> &array)
{
	_T min = array(0, 0);
	int r = array.row();
	int c = array.col();
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			if (array(i, j) < min)
				min = array(i, j);
	return min;
}

template <typename _T>
NcArray<_T> eye(const int &s)
{
	NcArray<_T> arr(s, s);
	for (int i = 0; i < s; i++)
		arr[i][i] = 1;
	return arr;
}

#endif
