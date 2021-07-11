#ifndef NCARRAY_H
#define NCARRAY_H
#include <initializer_list>
template <typename _T>
class NcArray
{
  private:
	int m_row;
	int m_col;
	int m_size = 0;
	_T *m_ptr = nullptr;

  public:
	NcArray(const std::initializer_list<std::initializer_list<_T>> &list);
	NcArray(const int &r = 0, const int &c = 0);
	NcArray(const NcArray &array);
	_T operator()(const int &i, const int &j) const;
	_T *operator[](const int &i);
	bool operator==(const NcArray &array);
	NcArray operator=(const NcArray &array);
	NcArray operator+(const NcArray &array);
	NcArray operator-(const NcArray &array) const;
	NcArray operator-();
	NcArray operator*(const NcArray &array);
	NcArray operator/(const _T &e);
	friend NcArray operator*(const _T &e, const NcArray<_T> &array)
	{
		NcArray<_T> arr = array;
		for (int i = 0; i < arr.m_size; i++)
			arr.m_ptr[i] *= e;
		return arr;
	};
	NcArray operator+=(const NcArray &array);
	NcArray operator-=(const NcArray &array);
	NcArray operator*=(const NcArray &array);
	NcArray operator/=(const _T &e);
	NcArray T();
	int row() const
	{
		return m_row;
	};
	NcArray row(const int &r);
	int col() const
	{
		return m_col;
	};
	NcArray col(const int &c);
	void show();
	_T sum();
	NcArray row_sum();
	NcArray col_sum();
	NcArray rowSwap(const int &m1, const int &m2);
	bool isSquare() const;
	bool isSymmetry();
	~NcArray();
};

template <typename _T>
NcArray<_T> Mul(const NcArray<_T> &arr1, const NcArray<_T> &arr2);

template <typename _T>
NcArray<_T> abs(const NcArray<_T> &array);

template <typename _T>
void show(const NcArray<_T> &array);

template <typename _T>
_T max(const NcArray<_T> &array);

template <typename _T>
_T min(const NcArray<_T> &array);

template <typename _T>
NcArray<_T> eye(const int &s);

#include "NcArray.inl"

#endif
