#ifndef stm_matrix_2x2_h
#define stm_matrix_2x2_h

#include "debug.h"

namespace stm
{
	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	class matrix;

	template <typename _MATRIX_TYPE>
	struct matrix_iterator;

	template <typename _MATRIX_TYPE>
	struct matrix_const_iterator;

	template<typename _MATRIX_TYPE>
	struct matrix_column_iterator;

	template<typename _MATRIX_TYPE>
	struct matrix_column_const_iterator;

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	struct constexpr_matrix;

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
	class matrix_view;

	template<typename _TYPE>
	class dynamic_matrix;

	template<typename _TYPE, typename Itr>
	class dynamic_matrix_view;

	template<typename _TYPE, unsigned int _SIZE>
	class vector;

	template<typename _TYPE>
	class dynamic_vector;

	template<typename _TYPE, unsigned int _DIM, typename Itr>
	class vector_view;

	template<typename _TYPE, typename Itr>
	class dynamic_vector_view;

	template<typename _TYPE>
	class matrix<_TYPE, 2, 2>
	{
	private:
		union
		{
			_TYPE _data[4] {};
			struct
			{
				_TYPE x, y, z, w;
			};
		};

	public:
		using ElemType = _TYPE;
		using iterator = matrix_iterator<matrix<_TYPE, 2, 2>>;
		using const_iterator = matrix_const_iterator<matrix<_TYPE, 2, 2>>;
		using row_iterator = iterator;
		using row_const_iterator = const_iterator;
		using column_iterator = matrix_column_iterator<matrix<_TYPE, 2, 2>>;
		using column_const_iterator = matrix_column_const_iterator<matrix<_TYPE, 2, 2>>;

		//Constructors
		constexpr matrix() noexcept = default;

		constexpr matrix(const _TYPE& value) noexcept
			:x(value), y(value), z(value), w(value)
		{
		}

		constexpr matrix(const _TYPE& val_00, const _TYPE& val_01, const _TYPE& val_10, const _TYPE& val_11) noexcept
			:x(val_00), y(val_01), z(val_10), w(val_11)
		{
		}

		constexpr matrix(const _TYPE (&data)[4]) noexcept
			:_data(data)
		{
		}

		constexpr matrix(const _TYPE* data, const unsigned int offset) noexcept
			: x(data[offset]), y(data[1 + offset]), z(data[2 + offset]), w(data[3 + offset])
		{
		}

		constexpr matrix(const matrix&) noexcept = default;
		constexpr matrix(matrix&&)      noexcept = default;
		~matrix() = default;

		//Assigment Operator
		constexpr matrix& operator=(const matrix&) noexcept = default;
		constexpr matrix& operator=(matrix &&)     noexcept = default;

		matrix& operator=(const dynamic_matrix<_TYPE>& mat)
		{
			stm_assert(mat.GetColumnSize() == 2 && mat.GetRowSize() == 2);
			memcpy(_data, mat.GetData(), 4 * sizeof(_TYPE));
			return *this;
		}

		//Unary Operators
		constexpr _TYPE*       operator[](const unsigned int index)       noexcept { stm_assert(index < 2); return &_data[index * 2]; }
		constexpr const _TYPE* operator[](const unsigned int index) const noexcept { stm_assert(index < 2); return &_data[index * 2]; }

		constexpr matrix operator+() const noexcept
		{
			return *this;
		}

		constexpr matrix operator-() const noexcept
		{
			return matrix(-_data[0], -_data[1], -_data[2], -_data[3]);
		}

		//Binary Operators
		constexpr matrix operator+(const matrix& other) const noexcept
		{
			return matrix(*this) += other;
		}

		constexpr matrix operator-(const matrix& other) const noexcept
		{
			return matrix(*this) -= other;
		}

		constexpr matrix operator*(const matrix& other) const noexcept
		{
			return matrix(*this) *= other;
		}

		constexpr matrix operator/(const matrix& other) const noexcept
		{
			return matrix(*this) /= other;
		}

		constexpr matrix operator+(const _TYPE& other) const noexcept
		{
			return matrix(*this) += other;
		}

		constexpr matrix operator-(const _TYPE& other) const noexcept
		{
			return matrix(*this) -= other;
		}

		constexpr matrix operator*(const _TYPE& other) const noexcept
		{
			return matrix(*this) *= other;
		}

		constexpr matrix operator/(const _TYPE& other) const noexcept
		{
			return matrix(*this) /= other;
		}

		matrix operator+(const dynamic_matrix<_TYPE>& mat) const
		{
			stm_assert(mat.GetColumnSize() == 2 && mat.GetRowSize() == 2);
			return matrix(*this) += mat;
		}

		matrix operator-(const dynamic_matrix<_TYPE>& mat) const
		{
			stm_assert(mat.GetColumnSize() == 2 && mat.GetRowSize() == 2);
			return matrix(*this) -= mat;
		}

		matrix operator*(const dynamic_matrix<_TYPE>& mat) const
		{
			stm_assert(mat.GetColumnSize() == 2 && mat.GetRowSize() == 2);
			return matrix(*this) *= mat;
		}

		matrix operator/(const dynamic_matrix<_TYPE>& mat) const
		{
			stm_assert(mat.GetColumnSize() == 2 && mat.GetRowSize() == 2);
			return matrix(*this) /= mat;
		}

		//Binary-Assigment Operators
		constexpr matrix& operator+=(const matrix& other) noexcept
		{
			return (x += other.x, y += other.y, z += other.z, w += other.w, *this);
		}

		constexpr matrix& operator-=(const matrix& other) noexcept
		{
			return (x -= other.x, y -= other.y, z -= other.z, w -= other.w, *this);
		}

		constexpr matrix& operator*=(const matrix& other) noexcept
		{
			return (x *= other.x, y *= other.y, z *= other.z, w *= other.w, *this);
		}

		constexpr matrix& operator/=(const matrix& other) noexcept
		{
			return (x /= other.x, y /= other.y, z /= other.z, w /= other.w, *this);
		}

		constexpr matrix& operator+=(const _TYPE& value) noexcept
		{
			return (x += value, y += value, z += value, w += value, *this);
		}

		constexpr matrix& operator-=(const _TYPE& value) noexcept
		{
			return (x -= value, y -= value, z -= value, w -= value, *this);
		}

		constexpr matrix& operator*=(const _TYPE& value) noexcept
		{
			return (x *= value, y *= value, z *= value, w *= value, *this);
		}

		constexpr matrix& operator/=(const _TYPE& value) noexcept
		{
			return (x /= value, y /= value, z /= value, w /= value, *this);
		}

		matrix& operator+=(const dynamic_matrix<_TYPE>& mat)
		{
			stm_assert(mat.GetColumnSize() == 2 && mat.GetRowSize() == 2);
			return (x += mat[0][0], y += mat[0][1], z += mat[1][0], w += mat[1][1], *this);
		}

		matrix& operator-=(const dynamic_matrix<_TYPE>& mat)
		{
			stm_assert(mat.GetColumnSize() == 2 && mat.GetRowSize() == 2);
			return (x -= mat[0][0], y -= mat[0][1], z -= mat[1][0], w -= mat[1][1], *this);
		}

		matrix& operator*=(const dynamic_matrix<_TYPE>& mat)
		{
			stm_assert(mat.GetColumnSize() == 2 && mat.GetRowSize() == 2);
			return (x *= mat[0][0], y *= mat[0][1], z *= mat[1][0], w *= mat[1][1], *this);
		}

		matrix& operator/=(const dynamic_matrix<_TYPE>& mat)
		{
			stm_assert(mat.GetColumnSize() == 2 && mat.GetRowSize() == 2);
			return (x /= mat[0][0], y /= mat[0][1], z /= mat[1][0], w /= mat[1][1], *this);
		}

		//Math functions
		constexpr matrix Inverse() const noexcept
		{
			return matrix(_data[3], -_data[1], -_data[2], _data[0]) / Determinant();
		}

		constexpr matrix Transpose() const noexcept
		{
			return matrix(_data[0], _data[2], _data[1], _data[3]);
		}

		template<unsigned int O_COLUMNS>
		matrix<_TYPE, 2, O_COLUMNS> Multiply(const matrix<_TYPE, 2, O_COLUMNS>& mat) const
		{
			matrix<_TYPE, 2, O_COLUMNS> temp;
			for (unsigned int i = 0; i < 2; ++i)
			{
				for (unsigned int j = 0; j < O_COLUMNS; ++j)
				{
					_TYPE sum = 0;
					for (unsigned int k = 0; k < 2; ++k)
						sum += (*this)[i][k] * mat[k][j];
					temp._data[(i * O_COLUMNS) + j] = sum;
				}
			}
			return temp;
		}

		constexpr matrix Mulitply(const matrix& mat) const noexcept
		{
			return matrix(x * mat.x + y * mat.z,
						  x * mat.y + y * mat.w,
						  z * mat.x + w * mat.z,
						  z * mat.y + w * mat.w);
		}

		constexpr vector<_TYPE, 2> Multiply(const vector<_TYPE, 2>& vec) noexcept
		{
			return vector<_TYPE, 2>(vec[0] * x + vec[1] * y, vec[0] * z + vec[1] * w);
		}

		vector<_TYPE, 2> Multiply(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(vec.GetSize() == 2);
			vector<_TYPE, 2> temp;
			for (unsigned int i = 0; i < 2; ++i)
			{
				for (unsigned int j = 0; j < 2; ++j)
					temp[i] += vec[j] * (*this)[i][j];
			}
			return temp;
		}

		constexpr _TYPE Determinant() const noexcept
		{
			return (_data[0] * _data[3]) - (_data[1] * _data[2]);
		}

		//Vector Getters and Setters
		constexpr vector<_TYPE, 2> GetRowVector   (const unsigned int row)    const noexcept { return vector<_TYPE, 2>(&_data[row * 2]); }
		constexpr vector<_TYPE, 2> GetColumnVector(const unsigned int column) const noexcept { return vector<_TYPE, 2>((*this)[0][column], (*this)[1][column]); }

		constexpr vector_view<_TYPE, 2, row_const_iterator> GetRowView(const unsigned int row) const noexcept
		{ return vector_view<_TYPE, 2, row_const_iterator>(cbegin_row(row), cend_row(row)); }

		constexpr vector_view<_TYPE, 2, column_const_iterator> GetColumnView(const unsigned int column) const noexcept
		{ return vector_view<_TYPE, 2, column_const_iterator>(cbegin_column(column), cend_column(column)); }

		constexpr matrix_view<_TYPE, 2, 2, const_iterator> GetView() const noexcept
		{ return matrix_view<_TYPE, 2, 2, const_iterator>(*this); }

		constexpr matrix_view<_TYPE, 2, 2, column_const_iterator> GetTranposeView() const noexcept
		{ return matrix_view<_TYPE, 2, 2, column_const_iterator>(*this); }

		matrix& SetRowVector(const unsigned int row, const vector<_TYPE, 2>& vec) noexcept
		{
			_data[row * 2] = vec[0]; _data[row * 2 + 1] = vec[1];
			return *this;
		}

		matrix& SetRowVector(const unsigned int row, const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(vec.GetSize() == 2);
			_data[row * 2] = vec[0]; _data[row * 2 + 1] = vec[1];
			return *this;
		}

		template <typename Itr>
		matrix& SetRowVector(const unsigned int row, const vector_view<_TYPE, 2, Itr>& vec) noexcept;
		template <typename Itr>
		matrix& SetRowVector(const unsigned int row, const dynamic_vector_view<_TYPE, Itr>& vec) noexcept;

		matrix& SetColumnVector(const unsigned int column, const vector<_TYPE, 2>& vec) noexcept
		{
			_data[column] = vec[0]; _data[column + 2];
			return *this;
		}

		matrix& SetColumnVector(const unsigned int column, const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(vec.GetSize() == 2);
			_data[column] = vec[0]; _data[column + 2];
			return *this;
		}

		template <typename Itr>
		matrix& SetColumnVector(const unsigned int column, const vector_view<_TYPE, 2, Itr>& vec) noexcept;
		template <typename Itr>
		matrix& SetColumnVector(const unsigned int column, const dynamic_vector_view<_TYPE, Itr>& vec) noexcept;

		constexpr matrix& SetAll(const _TYPE& value) noexcept { return (x = value, y = value, z = value, w = value, *this);}

		constexpr matrix& SetAllRows(const vector<_TYPE, 2>& vec) noexcept
		{
			return (x = vec[0], y = vec[1], z = vec[0], w = vec[1], *this);
		}

		constexpr matrix& SetAllColumns(const vector<_TYPE, 2>& vec) noexcept
		{
			return (x = vec[0], y = vec[0], z = vec[1], w = vec[1], *this);
		}

		matrix& SetAllRows(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(vec.GetSize() == 2);
			return (x = vec[0], y = vec[1], z = vec[0], w = vec[1], *this);
		}

		matrix& SetAllColumns(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(vec.GetSize() == w);
			return (x = vec[0], y = vec[0], z = vec[1], w = vec[1], *this);
		}

		template <typename Itr>
		matrix& SetAllRows   (const vector_view<_TYPE, 2, Itr>& vec) noexcept;
		template <typename Itr>
		matrix& SetAllColumns(const vector_view<_TYPE, 2, Itr>& vec)    noexcept;

		template <typename Itr>
		matrix& SetAllRows   (const dynamic_vector_view<_TYPE, Itr>& vec);
		template <typename Itr>
		matrix& SetAllColumns(const dynamic_vector_view<_TYPE, Itr>& vec);


		//Data manipulation functions
		template <typename _FUNCTION>
		matrix& ApplyToMatrix(_FUNCTION&& func)
		{
			return (x = func(x), y = func(y), z = func(z), w = func(w), *this);
		}

		template <typename _FUNCTION>
		matrix& ApplyToRow(const unsigned int row, _FUNCTION&& func)
		{
			return (_data[row * 2] = func(_data[row]),
					_data[row * 2 + 1] = func(_data[row * 2 + 1]),
					*this);
		}

		template <typename _FUNCTION>
		matrix& ApplyToColumn(const unsigned int column, _FUNCTION&& func)
		{
			return (_data[column] = func(_data[column]),
					_data[column + 2] = func(_data[column + 2]),
					*this);
		}

		//Casting
		template<typename O_TYPE>
		constexpr matrix<O_TYPE, 2, 2> Cast() const noexcept
		{
			return matrix<O_TYPE, 2, 2>((O_TYPE)x, (O_TYPE)y, (O_TYPE)z, (O_TYPE)w);
		}

		//Data Info Functions
		static constexpr unsigned int container_row_size()    noexcept{ return 2; }
		static constexpr unsigned int container_column_size() noexcept { return 2; }
		static constexpr unsigned int container_size()        noexcept { return container_row_size() * container_column_size(); }

		constexpr _TYPE*       GetData()       noexcept { return _data; }
		constexpr const _TYPE* GetData() const noexcept { return _data; }
		constexpr auto&       GetArray()       noexcept { return _data; }
		constexpr const auto& GetArray() const noexcept { return _data; }

		constexpr unsigned int GetRowSize()    const noexcept { return container_row_size(); }
		constexpr unsigned int GetColumnSize() const noexcept { return container_column_size(); }
		constexpr unsigned int GetSize()       const noexcept { return container_size(); }

		//Iterators
		constexpr iterator begin() noexcept { return iterator(_data); }
		constexpr iterator end()   noexcept { return iterator(&_data[4]); }
		
		//Unwrapped iterators (u stands for unwrapped)
		constexpr auto ubegin() noexcept { return begin().unwrap(); }
		constexpr auto uend()   noexcept { return end().unwrap(); }

		//Const iterators
		constexpr const_iterator cbegin() const noexcept { return const_iterator(_data); }
		constexpr const_iterator cend()   const noexcept { return const_iterator(&_data[4]); }

		//Unwrapped const iterators
		constexpr auto ucbegin() const noexcept { return cbegin().unwrap(); }
		constexpr auto ucend()   const noexcept { return cend().unwrap(); }

		//Row iterators
		constexpr row_iterator begin_row(const unsigned int row) noexcept { return row_iterator(&_data[row * 2]); }
		constexpr row_iterator end_row  (const unsigned int row) noexcept { return row_iterator(&_data[(row + 1) * 2]); }

		//Row const iterators
		constexpr row_const_iterator cbegin_row(const unsigned int row) const noexcept { return row_const_iterator(&_data[row * 2]); }
		constexpr row_const_iterator cend_row  (const unsigned int row) const noexcept { return row_const_iterator(&_data[(row + 1) * 2]); }
		
		//Column iterators
		constexpr column_iterator begin_column(const unsigned int column) noexcept { return column_iterator(&_data[column]); }
		constexpr column_iterator end_column  (const unsigned int column) noexcept { return column_iterator(&_data[column + 4]); }

		//Column const iterators
		constexpr column_const_iterator cbegin_column(const unsigned int column) const noexcept{ return column_const_iterator(&_data[column]); }
		constexpr column_const_iterator cend_column  (const unsigned int column) const noexcept { return column_const_iterator(&_data[column + 4]); }
	};

	using mat2i = matrix<int, 2, 2>;
	using mat2f = matrix<float, 2, 2>;

	constexpr const mat2i identity_mat2i(1, 0, 0, 1);
	constexpr const mat2f identity_mat2f(1.f, 0.f, 0.f, 1.f);
}

#endif /* stm_matrix_2x2_h */