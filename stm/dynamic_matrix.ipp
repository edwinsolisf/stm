#include <iostream>
#include <cstring>
#include <utility>

namespace stm
{
	template<typename _T>
	dynamic_matrix<_T>::dynamic_matrix(const unsigned int rows, const unsigned int columns)
		:_data(new _T[rows * columns]{}), _rows(rows), _columns(columns)
	{
		stm_assert(rows != 0 && columns != 0);
	}

	template<typename _T>
	dynamic_matrix<_T>::dynamic_matrix(const unsigned int rows, const unsigned int columns, const _T* const data)
		:_data(new _T[rows * columns]), _rows(rows), _columns(columns)
	{
		stm_assert(rows != 0 && columns != 0);
		std::copy(data, data + rows * columns, ubegin());
		//memcpy(_data, data, _rows * _columns * sizeof(_T));
	}

	template<typename _T>
	dynamic_matrix<_T>::dynamic_matrix(const unsigned int rows, const unsigned int columns, const _T& value)
		:_data(new _T[rows * columns]), _rows(rows), _columns(columns)
	{
		stm_assert(rows != 0 && columns != 0);
		std::fill(ubegin(), uend(), value);
		//std::fill_n(_data, _rows * _columns, value);
	}

	template<typename _T>
	dynamic_matrix<_T>::dynamic_matrix(const unsigned int rows, const unsigned int columns, std::initializer_list<_T> list)
		:_data(new _T[rows * columns]), _rows(rows), _columns(columns)
	{
		stm_assert(rows != 0 && columns != 0 && list.size() == (rows * columns));
		std::copy(list.begin(), list.end(), ubegin());
		//std::copy(list.begin(), list.end(), _data);
	}

	template<typename _T>
	dynamic_matrix<_T>::dynamic_matrix(const unsigned int rows, const unsigned int columns, std::initializer_list<std::initializer_list<_T>> list)
		:_data(new _T[rows * columns]), _rows(rows), _columns(columns)
	{
		stm_assert(rows != 0 && columns != 0 && list.size() == rows && list.begin()->size() == columns);
		for (unsigned int i = 0; i < rows; ++i)
			std::copy(list.begin()[i].begin(), list.begin()[i].end(), begin_row(i).unwrap());
		//for (unsigned int i = 0; i < rows; ++i)
		//	std::copy(list.begin()[i].begin(), list.begin()[i].end(), &_data[i * columns]);
	}

	template<typename _T>
	dynamic_matrix<_T>::dynamic_matrix(const dynamic_matrix& other)
		:_data(new _T[other._rows * other._columns]), _rows(other._rows), _columns(other._columns)
	{
		std::copy(other.ucbegin(), other.ucend(), ubegin());
		//memcpy(_data, other._data, _rows * _columns * sizeof(_T));
	}

	template<typename _T>
	dynamic_matrix<_T>::~dynamic_matrix()
	{
		delete[] _data;
	}

	template<typename _T>
	dynamic_matrix<_T>::dynamic_matrix(dynamic_matrix&& other) noexcept
		:_data(std::exchange(other._data, nullptr)), _rows(std::exchange(other._rows, 0)), _columns(std::exchange(other._columns, 0))
	{
	}

	template<typename _T>
	dynamic_matrix<_T>::dynamic_matrix(_T*& data, const unsigned int rows, const unsigned int columns)
		:_data(std::exchange(data, nullptr)), _rows(rows), _columns(columns)
	{
		stm_assert(_data != nullptr);
	}

	template <typename _T> template <typename Itr>
	dynamic_matrix<_T>::dynamic_matrix(const dynamic_matrix_view<_T, Itr>& view)
		:_data(new _T[view.GetSize()]), _rows(view.GetRowSize()), _columns(view.GetColumnSize())
	{
		for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _columns; ++j)
				(*this)[i][j] = view[i][j];
		}
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	dynamic_matrix<_T>::dynamic_matrix(const matrix<_T, rows, columns>& static_matrix)
		: _data(new _T[rows * columns]), _rows(rows), _columns(columns)
	{
		std::copy(static_matrix.ucbegin(), static_matrix.ucend(), ubegin());
		//memcpy(_data, static_matrix.GetData(), _rows * _columns * sizeof(_T));
	}

	template <typename _T> template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
	dynamic_matrix<_T>::dynamic_matrix(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& static_matrix)
		:_data(new _T[_ROWS * _COLUMNS]), _rows(_ROWS), _columns(_COLUMNS)
	{
		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int j = 0; j < _COLUMNS; ++j)
				(*this)[i][j] = static_matrix[i][j];
		}
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator=(const dynamic_matrix& other)
	{
		if (this == &other) { return *this; }
		if ((_rows * _columns) >= other.GetSize())
			std::copy(other.ucbegin(), other.ucend(), ubegin());
			//memcpy(_data, other._data, _rows * _columns * sizeof(_T));
		else
		{
			_T* newData = new _T[other.GetSize()];
			std::copy(other.ucbegin(), other.ucend(), newData);
			//memcpy(newData, other._data, other.GetSize() * sizeof(_T));
			delete[] _data;
			_data = newData;
		}
		_rows = other._rows;
		_columns = other._columns;

		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator=(dynamic_matrix&& other) noexcept
	{
		if (this == &other) { return *this; }
		std::swap(_data, other._data);
		std::swap(_rows, other._rows);
		std::swap(_columns, other._columns);

		return *this;
	}

	template <typename _T> template <typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator=(const dynamic_matrix_view<_T, Itr>& other)
	{
		if (_data == other.GetData()) { return *this; }
		_rows = other.GetRowSize();
		_columns = other.GetColumnSize();
		if ((_rows * _columns) >= other.GetSize())
			std::copy(other.ucbegin(), other.ucend(), ubegin());
		else
		{
			_T* newData = new _T[other.GetSize()];
			//std::copy(other.ucbegin(), other.ucend(), newData);
			for (unsigned int i = 0; i < _rows; ++i)
			{
				for (unsigned int j = 0; j < _columns; ++j)
					newData[i * _columns + j] = other[i][j];
			}
			delete[] _data;
			_data = newData;
		}

		return *this;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator=(const matrix<_T, rows, columns>& mat)
	{
		stm_assert(_rows == rows && _columns == _columns);
		std::copy(mat.ucbegin(), mat.ucend(), ubegin());
		//memcpy(_data, mat.GetData(), _rows * _columns * sizeof(_T));
		return *this;
	}

	template <typename _T> template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator=(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& other)
	{
		stm_assert(_rows = _ROWS && _columns == _COLUMNS);
		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int j = 0; j < _COLUMNS; ++j)
				(*this)[i][j] = other[i][j];
		}
		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T> dynamic_matrix<_T>::operator-() const&
	{
		dynamic_matrix temp(_rows, _columns, _data);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			temp._data[i] = -_data[i];
		return temp;
	}

	template<typename _T>
	dynamic_matrix<_T>&& dynamic_matrix<_T>::operator-() &&
	{
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] = -_data[i];
		return std::move(*this);
	}

	template<typename _T>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator+(const dynamic_matrix& other) const&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return dynamic_matrix(*this) += other;
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator+(const dynamic_matrix& other) &&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return std::move(*this += other);
	}

	template<typename _T>
	dynamic_matrix<_T>&& dynamic_matrix<_T>::operator+(dynamic_matrix&& other) const&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			other._data[i] += _data[i];
		return std::move(other);
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator+(dynamic_matrix&& other) &&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return std::move(*this += other);
	}

	template<typename _T>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator-(const dynamic_matrix& other) const&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return dynamic_matrix(*this) -= other;
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator-(const dynamic_matrix& other) &&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return std::move(*this -= other);
	}

	template<typename _T>
	dynamic_matrix<_T>&& dynamic_matrix<_T>::operator-(dynamic_matrix&& other) const&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			other._data[i] = _data[i] - other._data;
		return std::move(other);
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator-(dynamic_matrix&& other)&&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return std::move(*this -= other);
	}

	template<typename _T>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator*(const dynamic_matrix& other) const&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return dynamic_matrix(*this) *= other;
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator*(const dynamic_matrix& other) &&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] *= other._data[i];
		return std::move(*this);
	}

	template<typename _T>
	dynamic_matrix<_T>&& dynamic_matrix<_T>::operator*(dynamic_matrix&& other) const&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			other._data[i] *= _data[i];
		return std::move(other);
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator*(dynamic_matrix&& other) &&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return std::move(*this *= other);
	}


	template<typename _T>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator/(const dynamic_matrix& other) const&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return dynamic_matrix(*this) /= other;
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator/(const dynamic_matrix& other) &&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return std::move(*this /= other);
	}

	template<typename _T>
	dynamic_matrix<_T>&& dynamic_matrix<_T>::operator/(dynamic_matrix&& other) const&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			other._data[i] = _data[i] / other._data;
		return std::move(other);
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator/(dynamic_matrix&& other) &&
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		return std::move(*this /= other);
	}

	template <typename _T> template <typename Itr>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator+(const dynamic_matrix_view<_T, Itr>& other) const&
	{
		stm_assert(_rows == other.GetRowSize() && _columns == other.GetColumnSize());
		return dynamic_matrix(*this) += other;
	}

	template <typename _T> template <typename Itr>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator+(const dynamic_matrix_view<_T, Itr>& other)&&
	{
		stm_assert(_rows == other.GetRowSize() && _columns == other.GetColumnSize());
		return std::move(*this += other);
	}

	template <typename _T> template <typename Itr>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator-(const dynamic_matrix_view<_T, Itr>& other) const&
	{
		stm_assert(_rows == other.GetRowSize() && _columns == other.GetColumnSize());
		return dynamic_matrix(*this) -= other;
	}

	template <typename _T> template <typename Itr>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator-(const dynamic_matrix_view<_T, Itr>& other)&&
	{
		stm_assert(_rows == other.GetRowSize() && _columns == other.GetColumnSize());
		return std::move(*this -= other);
	}

	template <typename _T> template <typename Itr>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator*(const dynamic_matrix_view<_T, Itr>& other) const&
	{
		stm_assert(_rows == other.GetRowSize() && _columns == other.GetColumnSize());
		return dynamic_matrix(*this) *= other;
	}

	template <typename _T> template <typename Itr>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator*(const dynamic_matrix_view<_T, Itr>& other)&&
	{
		stm_assert(_rows == other.GetRowSize() && _columns == other.GetColumnSize());
		return std::move(*this *= other);
	}

	template <typename _T> template <typename Itr>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator/(const dynamic_matrix_view<_T, Itr>& other) const&
	{
		stm_assert(_rows == other.GetRowSize() && _columns == other.GetColumnSize());
		return dynamic_matrix(*this) /= other;
	}

	template <typename _T> template <typename Itr>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator/(const dynamic_matrix_view<_T, Itr>& other)&&
	{
		stm_assert(_rows == other.GetRowSize() && _columns == other.GetColumnSize());
		return std::move(*this /= other);
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	inline matrix<_T, rows, columns> dynamic_matrix<_T>::operator+(const matrix<_T, rows, columns>& static_matrix) const noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		return matrix<_T, rows, columns>(_data, 0) += static_matrix;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	inline matrix<_T, rows, columns> dynamic_matrix<_T>::operator-(const matrix<_T, rows, columns>& static_matrix) const noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		return matrix<_T, rows, columns>(_data, 0) -= static_matrix;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	inline matrix<_T, rows, columns> dynamic_matrix<_T>::operator*(const matrix<_T, rows, columns>& static_matrix) const noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		return matrix<_T, rows, columns>(_data, 0) *= static_matrix;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	inline matrix<_T, rows, columns> dynamic_matrix<_T>::operator/(const matrix<_T, rows, columns>& static_matrix) const noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		return matrix<_T, rows, columns>(_data, 0) /= static_matrix;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns, typename Itr>
	inline matrix<_T, rows, columns> dynamic_matrix<_T>::operator+(const matrix_view<_T, rows, columns, Itr>& static_matrix) const noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		return matrix<_T, rows, columns>(_data, 0) += static_matrix;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns, typename Itr>
	inline matrix<_T, rows, columns> dynamic_matrix<_T>::operator-(const matrix_view<_T, rows, columns, Itr>& static_matrix) const noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		return matrix<_T, rows, columns>(_data, 0) -= static_matrix;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns, typename Itr>
	inline matrix<_T, rows, columns> dynamic_matrix<_T>::operator*(const matrix_view<_T, rows, columns, Itr>& static_matrix) const noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		return matrix<_T, rows, columns>(_data, 0) *= static_matrix;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns, typename Itr>
	inline matrix<_T, rows, columns> dynamic_matrix<_T>::operator/(const matrix_view<_T, rows, columns, Itr>& static_matrix) const noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		return matrix<_T, rows, columns>(_data, 0) /= static_matrix;
	}

	template<typename _T>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator+(const _T& value) const&
	{
		return dynamic_matrix(*this) += value;
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator+(const _T& value)&&
	{
		return std::move(*this += value);
	}

	template<typename _T>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator-(const _T& value) const&
	{
		return dynamic_matrix(*this) -= value;
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator-(const _T& value)&&
	{
		return std::move(*this -= value);
	}

	template<typename _T>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator*(const _T& value) const&
	{
		return dynamic_matrix(*this) *= value;
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator*(const _T& value)&&
	{
		return std::move(*this *= value);
	}

	template<typename _T>
	inline dynamic_matrix<_T> dynamic_matrix<_T>::operator/(const _T& value) const&
	{
		return dynamic_matrix(*this) /= value;
	}

	template<typename _T>
	inline dynamic_matrix<_T>&& dynamic_matrix<_T>::operator/(const _T& value)&&
	{
		return std::move(*this /= value);
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator+=(const dynamic_matrix& other)
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] += other._data[i];
		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator-=(const dynamic_matrix& other)
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] -= other._data[i];
		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator*=(const dynamic_matrix& other)
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] *= other._data[i];
		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator/=(const dynamic_matrix& other)
	{
		stm_assert(_rows == other._rows && _columns == other._columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] /= other._data[i];
		return *this;
	}

	template <typename _T> template <typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator+=(const dynamic_matrix_view<_T, Itr>& other)
	{
		stm_assert(GetRowSize() == other.GetRowSize() && GetColumnSize() == other.GetColumnSize());
		for (unsigned int i = 0; i < GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < GetColumnSize(); ++j)
			{
				(*this)[i][j] += other[i][j];
			}
		}
		return *this;
	}

	template <typename _T> template <typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator-=(const dynamic_matrix_view<_T, Itr>& other)
	{
		stm_assert(GetRowSize() == other.GetRowSize() && GetColumnSize() == other.GetColumnSize());
		for (unsigned int i = 0; i < GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < GetColumnSize(); ++j)
			{
				(*this)[i][j] -= other[i][j];
			}
		}
		return *this;
	}

	template <typename _T> template <typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator*=(const dynamic_matrix_view<_T, Itr>& other)
	{
		stm_assert(GetRowSize() == other.GetRowSize() && GetColumnSize() == other.GetColumnSize());
		for (unsigned int i = 0; i < GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < GetColumnSize(); ++j)
			{
				(*this)[i][j] *= other[i][j];
			}
		}
		return *this;
	}

	template <typename _T> template <typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator/=(const dynamic_matrix_view<_T, Itr>& other)
	{
		stm_assert(GetRowSize() == other.GetRowSize() && GetColumnSize() == other.GetColumnSize());
		for (unsigned int i = 0; i < GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < GetColumnSize(); ++j)
			{
				(*this)[i][j] /= other[i][j];
			}
		}
		return *this;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator+=(const matrix<_T, rows, columns>& static_matrix) noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] += static_matrix[0][i];
		return *this;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator-=(const matrix<_T, rows, columns>& static_matrix) noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] -= static_matrix[0][i];
		return *this;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator*=(const matrix<_T, rows, columns>& static_matrix) noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] *= static_matrix[0][i];
		return *this;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator/=(const matrix<_T, rows, columns>& static_matrix) noexcept
	{
		stm_assert(_rows == rows && _columns == columns);
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] /= static_matrix[0][i];
		return *this;
	}

	template <typename _T> template <unsigned int rows, unsigned int columns, typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator+=(const matrix_view<_T, rows, columns, Itr>& other) noexcept
	{
		stm_assert(GetRowSize() == other.GetRowSize() && GetColumnSize() == other.GetColumnSize());
		for (unsigned int i = 0; i < other.GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < other.GetColumnSize(); ++i)
			{
				(*this)[i][j] += other[i][j];
			}
		}
		return *this;
	}

	template <typename _T> template <unsigned int rows, unsigned int columns, typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator-=(const matrix_view<_T, rows, columns, Itr>& other) noexcept
	{
		stm_assert(GetRowSize() == other.GetRowSize() && GetColumnSize() == other.GetColumnSize());
		for (unsigned int i = 0; i < other.GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < other.GetColumnSize(); ++i)
			{
				(*this)[i][j] -= other[i][j];
			}
		}
		return *this;
	}

	template <typename _T> template <unsigned int rows, unsigned int columns, typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator*=(const matrix_view<_T, rows, columns, Itr>& other) noexcept
	{
		stm_assert(GetRowSize() == other.GetRowSize() && GetColumnSize() == other.GetColumnSize());
		for (unsigned int i = 0; i < other.GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < other.GetColumnSize(); ++i)
			{
				(*this)[i][j] *= other[i][j];
			}
		}
		return *this;
	}

	template <typename _T> template <unsigned int rows, unsigned int columns, typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator/=(const matrix_view<_T, rows, columns, Itr>& other) noexcept
	{
		stm_assert(GetRowSize() == other.GetRowSize() && GetColumnSize() == other.GetColumnSize());
		for (unsigned int i = 0; i < other.GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < other.GetColumnSize(); ++i)
			{
				(*this)[i][j] /= other[i][j];
			}
		}
		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator+=(const _T& value) noexcept
	{
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] += value;
		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator-=(const _T& value) noexcept
	{
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] -= value;
		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator*=(const _T& value) noexcept
	{
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] *= value;
		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::operator/=(const _T& value) noexcept
	{
		for (unsigned int i = 0; i < _rows * _columns; ++i)
			_data[i] /= value;
		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T> dynamic_matrix<_T>::Minor(const unsigned int row, const unsigned int column) const
	{
		stm_assert(row < _rows&& column < _columns);
		dynamic_matrix temp(_rows - 1, _columns - 1);
		unsigned int k = 0;

		for (unsigned int i = 0; i < _rows; ++i)
		{
			if (i != row)
			{
				for (unsigned int j = 0; j < _columns; ++j)
				{
					if (j != column)
					{
						temp._data[k] = _data[(i * _columns) + j];
						++k;
					}
				}
			}
		}
		return temp;
	}

	template<typename _T>
	dynamic_matrix<_T> dynamic_matrix<_T>::Inverse() const
	{
		dynamic_matrix temp(_rows, _columns);
		_T determinant = 0;
		for (unsigned int i = 0; i < _rows; ++i)
		{
			for (unsigned int j = 0; j < _columns; ++j)
			{
				temp._data[(i * _columns) + j] = (((i + j) % 2) ? -(this->Minor(i, j).Determinant()) : (this->Minor(i, j).Determinant()));
			}
		}

		for (unsigned int k = 0; k < _columns; ++k)
			determinant += temp._data[k] * _data[k];

		return temp.Transpose() / determinant;
	}

	template<typename _T>
	dynamic_matrix<_T> dynamic_matrix<_T>::Transpose() const&
	{
		dynamic_matrix temp(_columns, _rows);
		for (unsigned int i = 0; i < _rows; ++i)
		{
			for (unsigned int j = 0; j < _columns; ++j)
				temp._data[i + (j * _rows)] = (*this)[i][j];
		}
		return temp;
	}

	template<typename _T>
	dynamic_matrix<_T>&& dynamic_matrix<_T>::Transpose() &&
	{
		for (unsigned int i = 0; i < _rows - 1; ++i)
		{
			for (unsigned int j = i + 1; j < _columns; ++j)
				std::swap(_data[i + (j * _rows)], _data[(i * _columns) + j]);
		}
		return std::move(*this);
	}

	template<typename _T>
	dynamic_matrix<_T> dynamic_matrix<_T>::SubMatrix(
		const unsigned int rowSize, const unsigned int columnSize, const unsigned int rowOffset, const unsigned int columnOffset) const
	{
		dynamic_matrix temp(rowSize, columnSize);
		for (unsigned int i = rowOffset; i < rowOffset + rowSize; ++i)
			memcpy(temp._data[i - rowOffset], _data[(i * _columns) + columnOffset], columnSize * sizeof(_T));
		return temp;
	}

	template<typename _T>
	_T dynamic_matrix<_T>::Determinant() const
	{
		stm_assert(_rows == _columns);
		if (_rows == 2)
			return (_data[0] * _data[3]) - (_data[1] * _data[2]);
		else
		{
			_T sum = 0;
			for (unsigned int i = 0; i < _rows; ++i)
				sum += (i % 2) ? -(Minor(0, i).Determinant() * _data[i]) : (Minor(0, i).Determinant() * _data[i]);
			return sum;
		}
	}

	template<typename _T>
	dynamic_matrix<_T> dynamic_matrix<_T>::Multiply(const dynamic_matrix& mat) const
	{
		stm_assert(_columns == mat.GetRowSize());
		dynamic_matrix temp(_rows, mat.GetColumnSize());
		for (unsigned int i = 0; i < _rows; ++i)
		{
			for (unsigned int k = 0; k < _columns; ++k)
			{
				for (unsigned int j = 0; j < mat.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * mat[k][j];
				}
			}
		}
		return temp;
	}

	template <typename _T> template <typename Itr>
	dynamic_matrix<_T> dynamic_matrix<_T>::Multiply(const dynamic_matrix_view<_T, Itr>& other) const
	{
		stm_assert(_columns == other.GetRowSize());
		dynamic_matrix temp(_rows, other.GetColumnSize());
		for (unsigned int i = 0; i < _rows; ++i)
		{
			for (unsigned int k = 0; k < _columns; ++k)
			{
				for (unsigned int j = 0; j < other.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
		return temp;
	}

	template<typename _T> template<unsigned int rows, unsigned int columns>
	dynamic_matrix<_T> dynamic_matrix<_T>::Multiply(const matrix<_T, rows, columns>& static_matrix) const
	{
		stm_assert(_columns == static_matrix.GetRowSize());
		dynamic_matrix<_T> temp(static_matrix.GetColumnSize(), _rows);

		for (unsigned int i = 0; i < _rows; ++i)
		{
			for (unsigned int k = 0; k < _columns; ++k)
			{
				for (unsigned int j = 0; j < static_matrix.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * static_matrix[k][j];
				}
			}
		}
		return temp;
	}

	template <typename _T> template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
	dynamic_matrix<_T> dynamic_matrix<_T>::Multiply(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& other) const
	{
		stm_assert(_columns == _ROWS);
		dynamic_matrix<_T> temp(_COLUMNS, _rows);

		for (unsigned int i = 0; i < _rows; ++i)
		{
			for (unsigned int k = 0; k < _columns; ++k)
			{
				for (unsigned int j = 0; j < _COLUMNS; ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
		return temp;
	}

	template<typename _T>
	dynamic_vector<_T> dynamic_matrix<_T>::Multiply(const dynamic_vector<_T>& vec) const
	{
		stm_assert(vec.GetSize() == _columns);

		dynamic_vector<_T> temp(_rows);
		for (unsigned int j = 0; j < _columns; ++j)
		{
			for (unsigned int i = 0; i < _rows; ++i)
				temp[i] += (*this)[i][j] * vec[j];
		}
		return temp;
	}

	template <typename _T> template <typename Itr>
	dynamic_vector<_T> dynamic_matrix<_T>::Multiply(const dynamic_vector_view<_T, Itr>& vec) const
	{
		stm_assert(vec.GetSize() == _columns);

		dynamic_vector<_T> temp(_rows);
		for (unsigned int j = 0; j < _columns; ++j)
		{
			for (unsigned int i = 0; i < _rows; ++i)
				temp[i] += (*this)[i][j] * vec[j];
		}
		return temp;
	}

	template<typename _T>template<unsigned int columns>
	dynamic_vector<_T> dynamic_matrix<_T>::Multiply(const vector<_T, columns>& vec) const
	{
		stm_assert(columns == _columns);

		dynamic_vector<_T> temp(_rows);
		for (unsigned int j = 0; j < _columns; ++j)
		{
			for (unsigned int i = 0; i < _rows; ++i)
				temp[i] += (*this)[i][j] * vec[j];
		}
		return temp;
	}

	template <typename _T> template <unsigned int COLUMNS, typename Itr>
	dynamic_vector<_T> dynamic_matrix<_T>::Multiply(const vector_view<_T, COLUMNS, Itr>& vec) const
	{
		stm_assert(COLUMNS == _columns);

		dynamic_vector<_T> temp(_rows);
		for (unsigned int j = 0; j < COLUMNS; ++j)
		{
			for (unsigned int i = 0; i < _rows; ++i)
				temp[i] += (*this)[i][j] * vec[j];
		}
		return temp;
	}

	template<typename _T>
	dynamic_vector<_T> dynamic_matrix<_T>::GetColumnVector(const unsigned int column) const
	{
		dynamic_vector<_T> temp(_rows);
		for (unsigned int i = 0; i < _rows; ++i)
			temp[i] = (*this)[i][column];
		return temp;
	}

	template<typename _T>
	inline dynamic_matrix<_T>& dynamic_matrix<_T>::SetRowVector(const unsigned int row, const dynamic_vector<_T>& vec)
	{
		stm_assert(vec.GetSize() == _columns);	
		//memcpy(&_data[row * _columns], vec.GetData(), _columns * sizeof(_T));
		return (std::copy(vec.ucbegin(), vec.ucend(), begin_row(row).unwrap()), *this);
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetColumnVector(const unsigned int column, const dynamic_vector<_T>& vec)
	{
		stm_assert(vec.GetSize() == _rows);
		for (unsigned int i = 0; i < _rows; ++i)
			(*this)[i][column] = vec[i];
		return *this;
	}

	template <typename _T> template<typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetRowVector(const unsigned int row, const dynamic_vector_view<_T, Itr>& vec)
	{
		stm_assert(_columns == vec.GetSize());
		for (unsigned int i = 0; i < _columns; ++i)
			(*this)[row][i] = vec[i];
		return *this;
	}

	template <typename _T> template<typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetColumnVector(const unsigned int column, const dynamic_vector_view<_T, Itr>& vec)
	{
		stm_assert(_rows == vec.GetSize());
		for (unsigned int i = 0; i < _rows; ++i)
			(*this)[i][column] = vec[i];
		return *this;
	}

	template<typename _T> template<unsigned int columns>
	inline dynamic_matrix<_T>& dynamic_matrix<_T>::SetRowVector(const unsigned int row, const vector<_T, columns>& vec) noexcept
	{
		stm_assert(columns == _columns);
		//memcpy(&_data[row * _columns], vec.GetData(), _columns * sizeof(_T));
		return (std::copy(vec.ucbegin(), vec.ucend(), begin_row(row).unwrap()), *this);
	}

	template<typename _T> template<unsigned int rows>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetColumnVector(const unsigned int column, const vector<_T, rows>& vec) noexcept
	{
		stm_assert(rows == _rows);
		for (unsigned int i = 0; i < _rows; ++i)
			(*this)[i][column] = vec[i];
		return *this;
	}

	template <typename _T> template <unsigned int _COLUMNS, typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetRowVector(const unsigned int row, const vector_view<_T, _COLUMNS, Itr>& vec) noexcept
	{
		stm_assert(_columns == _COLUMNS);
		for (unsigned int i = 0; i < _COLUMNS; ++i)
			(*this)[row][i] = vec[i];
		return *this;
	}

	template<typename _T> template <unsigned int _ROWS, typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetColumnVector(const unsigned int column, const vector_view<_T, _ROWS, Itr>& vec) noexcept
	{
		stm_assert(_rows == _ROWS);
		for (unsigned int i = 0; i < _ROWS; ++i)
			(*this)[i][column] = vec[i];
		return *this;
	}
	
	template<typename _T>
	inline dynamic_matrix<_T>& dynamic_matrix<_T>::SetAll(const _T& value) noexcept
	{
		return (std::fill(ubegin(), uend(), value), *this);
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetAllRows(const dynamic_vector<_T>& vec)
	{
		stm_assert(vec.GetSize() == _columns);
		std::copy(vec.ucbegin(), vec.ucend(), begin_row(0));
		for (unsigned int j = 1; j < _rows; ++j)
			std::copy(cbegin_row(0), cend_row(0), begin_row(j));
		return *this;
	}

	template <typename _T> template<typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetAllRows(const dynamic_vector_view<_T, Itr>& vec)
	{
		stm_assert(vec.GetSize() == _columns);
		for (unsigned int i = 0; i < _columns; ++i)
			(*this)[0][i] = vec[i];
		for (unsigned int j = 1; j < _rows; ++j)
			std::copy(cbegin_row(0), cend_row(0), begin_row(j));
		return *this;
	}

	template<typename _T>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetAllColumns(const dynamic_vector<_T>& vec)
	{
		stm_assert(vec.GetSize() == _rows);
		for (unsigned int i = 0; i < _rows; ++i)
			std::fill(begin_row(i), end_row(i), vec[i]);
		return *this;
	}

	template <typename _T> template<typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetAllColumns(const dynamic_vector_view<_T, Itr>& vec)
	{
		stm_assert(vec.GetSize() == _rows);
		for (unsigned int i = 0; i < _rows; ++i)
			std::fill(begin_row(i), end_row(i), vec[i]);
		return *this;
	}

	template<typename _T> template<unsigned int columns>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetAllRows(const vector<_T, columns>& vec) noexcept
	{
		stm_assert(vec.GetSize() == _columns);
		std::copy(vec.ucbegin(), vec.ucend(), begin_row(0));
		for (unsigned int j = 1; j < _rows; ++j)
			std::copy(cbegin_row(0), cend_row(0), begin_row(j));
		return *this;
	}

	template <typename _T> template <unsigned int COLUMNS, typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetAllRows(const vector_view<_T, COLUMNS, Itr>& vec) noexcept
	{
		stm_assert(vec.GetSize() == _columns);
		std::copy(vec.ucbegin(), vec.ucend(), begin_row(0));
		for (unsigned int j = 1; j < _rows; ++j)
			std::copy(cbegin_row(0), cend_row(0), begin_row(j));
		return *this;
	}

	template<typename _T> template<unsigned int rows>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetAllColumns(const vector<_T, rows>& vec) noexcept
	{
		stm_assert(vec.GetSize() == _rows);
		for (unsigned int i = 0; i < rows; ++i)
			std::fill(begin_row(i), end_row(i), vec[i]);
		return *this;
	}

	template <typename _T> template <unsigned int ROWS, typename Itr>
	dynamic_matrix<_T>& dynamic_matrix<_T>::SetAllColumns(const vector_view<_T, ROWS, Itr>& vec) noexcept
	{
		stm_assert(vec.GetSize() == _rows);
		for (unsigned int i = 0; i < ROWS; ++i)
			std::fill(begin_row(i), end_row(i), vec[i]);
		return *this;
	}

	template<typename _T>
	bool dynamic_matrix<_T>::Resize(const unsigned int rows, const unsigned int columns)
	{
		stm_assert(rows != 0 && columns != 0);
		if (rows * columns > GetSize())
		{
			_T* newData = new _T[rows * columns];
			//memcpy(newData, _data, rows * columns * sizeof(_T));
			std::copy(ucbegin(), ucend(), newData);
			delete[] _data;
			_data = newData;
			_rows = rows;
			_columns = columns;
			return true;
		}
		return false;
	}

	template<typename _T> template <typename _FUNCTION>
	dynamic_matrix<_T>& dynamic_matrix<_T>::ApplyToMatrix(_FUNCTION&& func)&
	{
		//for (unsigned int i = 0; i < GetSize(); ++i)
		//	_data[i] = func(_data[i]);
		for (auto it = begin(); it != end(); ++it)
			*it = func(*it);
		return *this;
	}

	template<typename _T> template <typename _FUNCTION>
	dynamic_matrix<_T>& dynamic_matrix<_T>::ApplyToRow(const unsigned int row, _FUNCTION&& func)&
	{
		//for (unsigned int i = 0; i < _columns; ++i)
		//	_data[(row * _columns) + i] = func(_data[(row * _columns) + i]);
		for (auto it = begin_row(row); it != end_row(row); ++it)
			*it = func(*it);
		return *this;
	}

	template<typename _T> template <typename _FUNCTION>
	dynamic_matrix<_T>& dynamic_matrix<_T>::ApplyToColumn(const unsigned int column, _FUNCTION&& func)&
	{
		//for (unsigned int i = 0; i < _rows; ++i)
		//	(*this)[i][column] = func((*this)[i][column]);
		for (auto it = begin_column(column); it != end_column(column); ++it)
			*it = func(*it);
		return *this;
	}

	template<typename _T> template <typename _FUNCTION>
	dynamic_matrix<_T>&& dynamic_matrix<_T>::ApplyToMatrix(_FUNCTION&& func) &&
	{
		//for (unsigned int i = 0; i < GetSize(); ++i)
		//	_data[i] = func(_data[i]);
		for (auto it = begin(); it != end(); ++it)
			*it = func(*it);
		return std::move(*this);
	}

	template<typename _T> template <typename _FUNCTION>
	dynamic_matrix<_T>&& dynamic_matrix<_T>::ApplyToRow(const unsigned int row, _FUNCTION&& func) &&
	{
		//for (unsigned int i = 0; i < _columns; ++i)
		//	_data[(row * _columns) + i] = func(_data[(row * _columns) + i]);
		for (auto it = begin_row(row); it != end_row(row); ++it)
			*it = func(*it);
		return std::move(*this);
	}

	template<typename _T> template <typename _FUNCTION>
	dynamic_matrix<_T>&& dynamic_matrix<_T>::ApplyToColumn(const unsigned int column, _FUNCTION&& func) &&
	{
		//for (unsigned int i = 0; i < _rows; ++i)
		//	(*this)[i][column] = func((*this)[i][column]);
		for (auto it = begin_column(column); it != end_column(column); ++it)
			*it = func(*it);
		return std::move(*this);
	}

	template<typename _T> template<typename O_TYPE>
	dynamic_matrix<O_TYPE> dynamic_matrix<_T>::Cast() const
	{
		dynamic_matrix<O_TYPE> temp(_rows, _columns);
		for (unsigned int i = 0; i < GetSize(); ++i)
			temp[0][i] = O_TYPE(_data[i]);
		return temp;
	}
}
