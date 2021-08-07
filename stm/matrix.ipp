#include <iostream>
#include <cstring>
#include <utility>

#include "stm_internal.h"
//#include "data_functions.h"

namespace stm
{
	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	constexpr matrix<_TYPE, _ROWS, _COLUMNS>::matrix(const constexpr_matrix<_TYPE, _ROWS, _COLUMNS>& matrix) noexcept
	{
		stm_internal::copy_array_data(matrix.GetArray(), GetArray());
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>::matrix(const _TYPE& value) noexcept
	{
		std::fill(ubegin(), uend(), value);
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>::matrix(const _TYPE (&data)[_ROWS * _COLUMNS]) noexcept
	{
		std::copy(data, data + container_size(), ubegin());
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>::matrix(const _TYPE* const data, const unsigned int offset) noexcept
	{
		std::copy(data + offset, data + offset + container_size(), ubegin());
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>::matrix(std::initializer_list<_TYPE> list) noexcept
	{
		stm_assert(list.size() == container_size());
		std::copy(list.begin(), list.end(), ubegin());
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>::matrix(std::initializer_list<std::initializer_list<_TYPE>> list) noexcept
	{
		stm_assert(list.size() == container_row_size() && list.begin()->size() == container_column_size());
		for (unsigned int i = 0; i < _ROWS; ++i)
			std::copy(list.begin()[i].begin(), list.begin()[i].end(), begin_row(i).unwrap());
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator=(const dynamic_matrix<_TYPE>& mat)
	{
		stm_assert(mat.GetRowSize() == container_row_size() && mat.GetColumnSize() == container_column_size());
		std::copy(mat.ubegin(), mat.uend(), ubegin());
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator-() const noexcept
	{
		matrix temp;
		for (unsigned int i = 0; i < GetSize(); ++i)
			temp._data[i] = -_data[i];
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator+(const matrix& other) const noexcept
	{
		return matrix(*this) += other;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator-(const matrix& other) const noexcept
	{
		return matrix(*this) -= other;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator*(const matrix& other) const noexcept
	{
		return matrix(*this) *= other;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator/(const matrix& other) const noexcept
	{
		return matrix(*this) /= other;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator+(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) const noexcept
	{
		return matrix(*this) += other;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator-(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) const noexcept
	{
		return matrix(*this) -= other;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator*(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) const noexcept
	{
		return matrix(*this) *= other;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator/(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) const noexcept
	{
		return matrix(*this) /= other;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator+(const _TYPE& other) const noexcept
	{
		return matrix(*this) += other;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator-(const _TYPE& other) const noexcept
	{
		return matrix(*this) -= other;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator*(const _TYPE& other) const noexcept
	{
		return matrix(*this) *= other;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator/(const _TYPE& other) const noexcept
	{
		return matrix(*this) /= other;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator+(const dynamic_matrix<_TYPE>& mat) const
	{
		stm_assert(mat.GetRowSize() == _ROWS && mat.GetColumnSize() == _COLUMNS);
		return matrix(*this) += mat;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator-(const dynamic_matrix<_TYPE>& mat) const
	{
		stm_assert(mat.GetRowSize() == _ROWS && mat.GetColumnSize() == _COLUMNS);
		return matrix(*this) -= mat;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator*(const dynamic_matrix<_TYPE>& mat) const
	{
		stm_assert(mat.GetRowSize() == _ROWS && mat.GetColumnSize() == _COLUMNS);
		return matrix(*this) *= mat;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator/(const dynamic_matrix<_TYPE>& mat) const
	{
		stm_assert(mat.GetRowSize() == _ROWS && mat.GetColumnSize() == _COLUMNS);
		return matrix(*this) /= mat;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator+(const dynamic_matrix_view<_TYPE, Itr>& other) const
	{
		stm_assert(other.GetRowSize() == container_row_size() && other.GetColumnSize() == container_column_size());
		return matrix(*this) += other;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator-(const dynamic_matrix_view<_TYPE, Itr>& other) const
	{
		stm_assert(other.GetRowSize() == container_row_size() && other.GetColumnSize() == container_column_size());
		return matrix(*this) -= other;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator*(const dynamic_matrix_view<_TYPE, Itr>& other) const
	{
		stm_assert(other.GetRowSize() == container_row_size() && other.GetColumnSize() == container_column_size());
		return matrix(*this) *= other;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	inline matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::operator/(const dynamic_matrix_view<_TYPE, Itr>& other) const
	{
		stm_assert(other.GetRowSize() == container_row_size() && other.GetColumnSize() == container_column_size());
		return matrix(*this) /= other;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator+=(const matrix& other) noexcept
	{
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] += other[0][i];
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator-=(const matrix& other) noexcept
	{
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] -= other[0][i];
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator*=(const matrix& other) noexcept
	{
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] *= other[0][i];
		return *this;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator+=(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) noexcept
	{
		for (unsigned int i = 0; i < container_row_size(); ++i)
		{
			for (unsigned int j = 0; j < container_column_size(); ++j)
				(*this)[i][j] += other[i][j];
		}
		return *this;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator-=(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) noexcept
	{
		for (unsigned int i = 0; i < container_row_size(); ++i)
		{
			for (unsigned int j = 0; j < container_column_size(); ++j)
				(*this)[i][j] -= other[i][j];
		}
		return *this;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator*=(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) noexcept
	{
		for (unsigned int i = 0; i < container_row_size(); ++i)
		{
			for (unsigned int j = 0; j < container_column_size(); ++j)
				(*this)[i][j] *= other[i][j];
		}
		return *this;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator/=(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) noexcept
	{
		for (unsigned int i = 0; i < container_row_size(); ++i)
		{
			for (unsigned int j = 0; j < container_column_size(); ++j)
				(*this)[i][j] /= other[i][j];
		}
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator/=(const matrix& other) noexcept
	{
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] /= other[0][i];
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator+=(const _TYPE& other) noexcept
	{
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] += other;
		return *this;
	}
	
	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator-=(const _TYPE& other) noexcept
	{
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] -= other;
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator*=(const _TYPE& other) noexcept
	{
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] *= other;
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator/=(const _TYPE& other) noexcept
	{
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] /= other;
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator+=(const dynamic_matrix<_TYPE>& mat)
	{
		stm_assert(mat.GetRowSize() == _ROWS && mat.GetColumnSize() == _COLUMNS);
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] += mat[0][i];
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator-=(const dynamic_matrix<_TYPE>& mat)
	{
		stm_assert(mat.GetRowSize() == _ROWS && mat.GetColumnSize() == _COLUMNS);
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] -= mat[0][i];
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator*=(const dynamic_matrix<_TYPE>& mat)
	{
		stm_assert(mat.GetRowSize() == _ROWS && mat.GetColumnSize() == _COLUMNS);
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] *= mat[0][i];
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator/=(const dynamic_matrix<_TYPE>& mat)
	{
		stm_assert(mat.GetRowSize() == _ROWS && mat.GetColumnSize() == _COLUMNS);
		for (unsigned int i = 0; i < container_size(); ++i)
			_data[i] /= mat[0][i];
		return *this;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator+=(const dynamic_matrix_view<_TYPE, Itr>& other)
	{
		stm_assert(other.GetRowSize() == container_row_size() && other.GetColumnSize() == container_column_size());
		for (unsigned int i = 0; i < container_row_size(); ++i)
		{
			for (unsigned int j = 0; j < container_column_size(); ++j)
				(*this)[i][j] += other[i][j];
		}
		return *this;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator-=(const dynamic_matrix_view<_TYPE, Itr>& other)
	{
		stm_assert(other.GetRowSize() == container_row_size() && other.GetColumnSize() == container_column_size());
		for (unsigned int i = 0; i < container_row_size(); ++i)
		{
			for (unsigned int j = 0; j < container_column_size(); ++j)
				(*this)[i][j] -= other[i][j];
		}
		return *this;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator*=(const dynamic_matrix_view<_TYPE, Itr>& other)
	{
		stm_assert(other.GetRowSize() == container_row_size() && other.GetColumnSize() == container_column_size());
		for (unsigned int i = 0; i < container_row_size(); ++i)
		{
			for (unsigned int j = 0; j < container_column_size(); ++j)
				(*this)[i][j] *= other[i][j];
		}
		return *this;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::operator/=(const dynamic_matrix_view<_TYPE, Itr>& other)
	{
		stm_assert(other.GetRowSize() == container_row_size() && other.GetColumnSize() == container_column_size());
		for (unsigned int i = 0; i < container_row_size(); ++i)
		{
			for (unsigned int j = 0; j < container_column_size(); ++j)
				(*this)[i][j] /= other[i][j];
		}
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS - 1, _COLUMNS - 1> matrix<_TYPE, _ROWS, _COLUMNS>::Minor(const unsigned int row, const unsigned int column) const
	{
		matrix<_TYPE, _ROWS - 1, _COLUMNS - 1> temp;
		unsigned int k = 0;

		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			if (i != row)
			{
				for (unsigned int j = 0; j < _COLUMNS; ++j)
				{
					if (j != column)
					{
						temp._data[k] = _data[(i * _COLUMNS) + j];
						++k;
					}
				}
			}
		}
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::Inverse() const
	{
		static_assert(_ROWS == _COLUMNS, "Error: non-square matrix");
		matrix temp;
		_TYPE determinant = 0;

		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int j = 0; j < _COLUMNS; ++j)
			{
				temp._data[(i * _COLUMNS) + j] = (((i + j) % 2) ? -(this->Minor(i, j).Determinant()) : (this->Minor(i, j).Determinant()));
			}
		}

		for (unsigned int k = 0; k < _COLUMNS; ++k)
			determinant += temp._data[k] * _data[k];

		return temp.Transpose() / determinant;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _COLUMNS, _ROWS> matrix<_TYPE, _ROWS, _COLUMNS>::Transpose() const noexcept
	{
		matrix<_TYPE, _COLUMNS, _ROWS> temp;
		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int j = 0; j < _COLUMNS; ++j)
				temp[0][i + (j * _ROWS)] = (*this)[i][j];
		}
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	template<unsigned int rows, unsigned columns>
	matrix<_TYPE, rows, columns> matrix<_TYPE, _ROWS, _COLUMNS>::SubMatrix(const unsigned int rowOffset, const unsigned int columnOffset) const
	{
		matrix temp;
		for (unsigned int i = rowOffset; i < rowOffset + rows; ++i)
			memcpy(temp._data[i - rowOffset], _data[(i * _COLUMNS) + columnOffset], columns * sizeof(_TYPE));
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	_TYPE matrix<_TYPE, _ROWS, _COLUMNS>::Determinant() const
	{
		static_assert(_ROWS == _COLUMNS, "Error: non-square matrix");

		_TYPE sum = 0;
		for (unsigned int i = 0; i < _ROWS; ++i)
			sum += (i % 2) ? -(Minor(0, i).Determinant() * _data[i]) : (Minor(0, i).Determinant() * _data[i]);
		return sum;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template<unsigned int O_COLUMNS>
	matrix<_TYPE, _ROWS, O_COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::Multiply(const matrix<_TYPE, _COLUMNS, O_COLUMNS>& other) const noexcept
	{
		matrix<_TYPE, _ROWS, O_COLUMNS> temp;
		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int k = 0; k < _COLUMNS; ++k)
			{
				for (unsigned int j = 0; j < O_COLUMNS; ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
		return temp;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	dynamic_matrix<_TYPE> matrix<_TYPE, _ROWS, _COLUMNS>::Multiply(const dynamic_matrix<_TYPE>& other) const
	{
		stm_assert(_COLUMNS == other.GetRowSize());
		dynamic_matrix<_TYPE> temp(_ROWS, other.GetColumnSize());
		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int k = 0; k < _COLUMNS; ++k)
			{
				for (unsigned int j = 0; j < other.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
		return temp;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <unsigned int O_COLUMNS, typename Itr>
	matrix<_TYPE, _ROWS, O_COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::Multiply(const matrix_view<_TYPE, _COLUMNS, O_COLUMNS, Itr>& other) const noexcept
	{
		matrix<_TYPE, _ROWS, O_COLUMNS> temp;
		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int k = 0; k < _COLUMNS; ++k)
			{
				for (unsigned int j = 0; j < O_COLUMNS; ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
		return temp;
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	dynamic_matrix<_TYPE> matrix<_TYPE, _ROWS, _COLUMNS>::Multiply(const dynamic_matrix_view<_TYPE, Itr>& other) const
	{
		stm_assert(_COLUMNS == other.GetRowSize());
		dynamic_matrix<_TYPE> temp(_ROWS, other.GetColumnSize());
		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int k = 0; k < _COLUMNS; ++k)
			{
				for (unsigned int j = 0; j < other.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	vector<_TYPE, _ROWS> matrix<_TYPE, _ROWS, _COLUMNS>::Multiply(const vector<_TYPE, _COLUMNS>& vec) const noexcept
	{
		vector<_TYPE, _ROWS> temp;
		for (unsigned int j = 0; j < _COLUMNS; ++j)
		{
			for (unsigned int i = 0; i < _ROWS; ++i)
				temp[i] += (*this)[i][j] * vec[j];
		}
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename Itr>
	vector<_TYPE, _ROWS> matrix<_TYPE, _ROWS, _COLUMNS>::Multiply(const vector_view<_TYPE, _COLUMNS, Itr>& vec) const noexcept
	{
		vector<_TYPE, _ROWS> temp;
		for (unsigned int j = 0; j < _COLUMNS; ++j)
		{
			for (unsigned int i = 0; i < _ROWS; ++i)
				temp[i] += (*this)[i][j] * vec[j];
		}
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	vector<_TYPE, _ROWS> matrix<_TYPE, _ROWS, _COLUMNS>::Multiply(const dynamic_vector<_TYPE>& vec) const noexcept
	{
		stm_assert(_COLUMNS == vec.GetSize());
		vector<_TYPE, _ROWS> temp;
		for (unsigned int j = 0; j < _COLUMNS; ++j)
		{
			for (unsigned int i = 0; i < _ROWS; ++i)
				temp[i] += (*this)[i][j] * vec[j];
		}
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	vector<_TYPE, _ROWS> matrix<_TYPE, _ROWS, _COLUMNS>::GetColumnVector(const unsigned int column) const noexcept
	{
		vector<_TYPE, _ROWS> temp;
		for (unsigned int i = 0; i < _ROWS; ++i)
			temp[i] = (*this)[i][column];
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::SetRowVector(const unsigned int row, const vector<_TYPE, _COLUMNS>& vec) noexcept
	{
		//memcpy(&_data[row * _COLUMNS], vec.GetData(), _COLUMNS * sizeof(_TYPE));
		return (std::copy(vec.ucbegin(), vec.ucend(), begin_row(row).unwrap()), *this);
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::SetRowVector(const unsigned int row, const dynamic_vector<_TYPE>& vec)
	{
		stm_assert(_COLUMNS == vec.GetSize());
		//memcpy(&_data[row * _COLUMNS], vec.GetData(), _COLUMNS * sizeof(_TYPE));
		return (std::copy(vec.ubegin(), vec.uend(), begin_row(row).unwrap()), *this);
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::SetColumnVector(const unsigned int column, const vector<_TYPE, _ROWS>& vec) noexcept
	{
		for (unsigned int i = 0; i < _ROWS; ++i)
			(*this)[i][column] = vec[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::SetColumnVector(const unsigned int column, const dynamic_vector<_TYPE>& vec)
	{
		stm_assert(_ROWS == vec.GetSize());
		for (unsigned int i = 0; i < _ROWS; ++i)
			(*this)[i][column] = vec[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::SetAll(const _TYPE& value) noexcept
	{
		return (std::fill(ubegin(), uend(), value), *this);
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::SetAllRows(const vector<_TYPE, _COLUMNS>& vec) noexcept
	{
		for (unsigned int i = 0; i < _ROWS; ++i)
			std::copy(vec.ucbegin(), vec.ucend(), begin_row(i).unwrap());
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::SetAllColumns(const vector<_TYPE, _ROWS>& vec) noexcept
	{
		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int j = 0; j < _COLUMNS; ++j)
				(*this)[i][j] = vec[i];
		}
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::SetAllRows(const dynamic_vector<_TYPE>& vec)
	{
		stm_assert(vec.GetSize() == _COLUMNS);
		for (unsigned int i = 0; i < _ROWS; ++i)
			std::copy(vec.ucbegin(), vec.ucend(), begin_row(i).unwrap());
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::SetAllColumns(const dynamic_vector<_TYPE>& vec)
	{
		stm_assert(vec.GetSize() == _ROWS);
		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int j = 0; j < _COLUMNS; ++j)
				(*this)[i][j] = vec[i];
		}
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename _FUNCTION>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::ApplyToMatrix(_FUNCTION&& func)
	{
		for (auto it = begin(); it != end(); ++it)
			*it = func(*it);
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename _FUNCTION>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::ApplyToRow(const unsigned int row, _FUNCTION&& func)
	{
		for (auto it = begin_row(row); it != end_row(row); ++it)
			*it = func(*it);
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template <typename _FUNCTION>
	matrix<_TYPE, _ROWS, _COLUMNS>& matrix<_TYPE, _ROWS, _COLUMNS>::ApplyToColumn(const unsigned int column, _FUNCTION&& func)
	{
		for (auto it = begin_column(column); it != end_column(column); ++it)
			*it = func(*it);
		return *this;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS> template<typename O_TYPE>
	matrix<O_TYPE, _ROWS, _COLUMNS> matrix<_TYPE, _ROWS, _COLUMNS>::Cast() const noexcept
	{
		matrix<O_TYPE, _ROWS, _COLUMNS> temp;
		for (unsigned int i = 0; i < GetSize(); ++i)
			temp._data[i] = O_TYPE(_data[i]);
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	constexpr constexpr_matrix<_TYPE, _ROWS, _COLUMNS>::constexpr_matrix(const _TYPE& value) noexcept
	{
		stm_internal::copy_value_data<_TYPE, _ROWS * _COLUMNS>(value, _data);
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	constexpr constexpr_matrix<_TYPE, _ROWS, _COLUMNS>::constexpr_matrix(const _TYPE (&data)[_ROWS * _COLUMNS]) noexcept
	{
		stm_internal::copy_array_data(data, _data);
	}

	//template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	//constexpr constexpr_matrix<_TYPE, _ROWS, _COLUMNS>::constexpr_matrix(std::initializer_list<_TYPE> list) noexcept
	//{
	//	stm_internal::copy_initializer_data(list, _data);
	//}

	//template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	//constexpr constexpr_matrix<_TYPE, _ROWS, _COLUMNS>::constexpr_matrix(std::initializer_list<std::initializer_list<_TYPE>> list) noexcept
	//{
	//	stm_internal::copy_double_initializer_data<_TYPE, _ROWS, _COLUMNS>(list, _data);
	//}
}