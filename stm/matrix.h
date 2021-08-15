#ifndef stm_matrix_h
#define stm_matrix_h

#include "debug.h"

namespace stm
{
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

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	class matrix
	{
	public:
		using ElemType = _TYPE;
		using iterator = matrix_iterator<matrix<_TYPE, _ROWS, _COLUMNS>>;
		using const_iterator = matrix_const_iterator<matrix<_TYPE, _ROWS, _COLUMNS>>;
		using row_iterator = iterator;//matrix_row_iterator<matrix<_TYPE, _ROWS, _COLUMNS>>;
		using row_const_iterator = const_iterator;// matrix_row_const_iterator<matrix<_TYPE, _ROWS, _COLUMNS>>;
		using column_iterator = matrix_column_iterator<matrix<_TYPE, _ROWS, _COLUMNS>>;
		using column_const_iterator = matrix_column_const_iterator<matrix<_TYPE, _ROWS, _COLUMNS>>;

		//Constructors
		constexpr matrix() noexcept = default;
		constexpr matrix(const matrix&) noexcept = default;
		constexpr matrix(matrix&&) noexcept = default;
		constexpr matrix(const constexpr_matrix<_TYPE, _ROWS, _COLUMNS>& matrix) noexcept;
		matrix(const _TYPE& value) noexcept;
		matrix(const _TYPE(&data)[_ROWS * _COLUMNS]) noexcept;
		matrix(const _TYPE* const data, const unsigned int offset) noexcept;
		template <typename Itr>
		matrix(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& view) noexcept;
		matrix(std::initializer_list<_TYPE> list) noexcept;
		matrix(std::initializer_list<std::initializer_list<_TYPE>> list) noexcept;
		~matrix() = default;

		//Assigment Operators
		constexpr matrix& operator=(const matrix&) noexcept = default;
		constexpr matrix& operator=(matrix&&) noexcept = default;
		template <typename Itr>
		matrix& operator=(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) noexcept;
		matrix& operator=(const dynamic_matrix<_TYPE>& mat);
		template <typename Itr>
		matrix& operator=(const dynamic_matrix_view<_TYPE, Itr>& other);

		//Unary Operators
		constexpr _TYPE* operator[](const unsigned int index)       noexcept { stm_assert(index < _ROWS); return &_data[index * _COLUMNS]; }
		constexpr const _TYPE* operator[](const unsigned int index) const noexcept { stm_assert(index < _ROWS); return &_data[index * _COLUMNS]; }

		constexpr matrix operator+() const noexcept { return *this; }

		matrix operator-() const noexcept;

		//Binary Operators
		matrix operator+(const matrix& other) const noexcept;
		matrix operator-(const matrix& other) const noexcept;
		matrix operator*(const matrix& other) const noexcept;
		matrix operator/(const matrix& other) const noexcept;

		template <typename Itr>
		matrix operator+(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) const noexcept;
		template <typename Itr>
		matrix operator-(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) const noexcept;
		template <typename Itr>
		matrix operator*(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) const noexcept;
		template <typename Itr>
		matrix operator/(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) const noexcept;

		matrix operator+(const _TYPE& other) const noexcept;
		matrix operator-(const _TYPE& other) const noexcept;
		matrix operator*(const _TYPE& other) const noexcept;
		matrix operator/(const _TYPE& other) const noexcept;

		matrix operator+(const dynamic_matrix<_TYPE>& mat) const;
		matrix operator-(const dynamic_matrix<_TYPE>& mat) const;
		matrix operator*(const dynamic_matrix<_TYPE>& mat) const;
		matrix operator/(const dynamic_matrix<_TYPE>& mat) const;

		template <typename Itr>
		matrix operator+(const dynamic_matrix_view<_TYPE, Itr>& other) const;
		template <typename Itr>
		matrix operator-(const dynamic_matrix_view<_TYPE, Itr>& other) const;
		template <typename Itr>
		matrix operator*(const dynamic_matrix_view<_TYPE, Itr>& other) const;
		template <typename Itr>
		matrix operator/(const dynamic_matrix_view<_TYPE, Itr>& other) const;

		//Binary-Assigment Operators
		matrix& operator+=(const matrix& other) noexcept;
		matrix& operator-=(const matrix& other) noexcept;
		matrix& operator*=(const matrix& other) noexcept;
		matrix& operator/=(const matrix& other) noexcept;

		template <typename Itr>
		matrix& operator+=(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) noexcept;
		template <typename Itr>
		matrix& operator-=(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) noexcept;
		template <typename Itr>
		matrix& operator*=(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) noexcept;
		template <typename Itr>
		matrix& operator/=(const matrix_view<_TYPE, _ROWS, _COLUMNS, Itr>& other) noexcept;

		matrix& operator+=(const _TYPE& other) noexcept;
		matrix& operator-=(const _TYPE& other) noexcept;
		matrix& operator*=(const _TYPE& other) noexcept;
		matrix& operator/=(const _TYPE& other) noexcept;

		matrix& operator+=(const dynamic_matrix<_TYPE>& mat);
		matrix& operator-=(const dynamic_matrix<_TYPE>& mat);
		matrix& operator*=(const dynamic_matrix<_TYPE>& mat);
		matrix& operator/=(const dynamic_matrix<_TYPE>& mat);

		template <typename Itr>
		matrix& operator+=(const dynamic_matrix_view<_TYPE, Itr>& other);
		template <typename Itr>
		matrix& operator-=(const dynamic_matrix_view<_TYPE, Itr>& other);
		template <typename Itr>
		matrix& operator*=(const dynamic_matrix_view<_TYPE, Itr>& other);
		template <typename Itr>
		matrix& operator/=(const dynamic_matrix_view<_TYPE, Itr>& other);

		//Math functions
		matrix<_TYPE, _ROWS - 1, _COLUMNS - 1> Minor(const unsigned int row, const unsigned int column) const;

		matrix Inverse() const;

		matrix<_TYPE, _COLUMNS, _ROWS> Transpose() const noexcept;

		template<unsigned int rows, unsigned columns>
		matrix<_TYPE, rows, columns> SubMatrix(const unsigned int rowOffset, const unsigned int columnOffset) const;

		_TYPE Determinant() const;

		template<unsigned int O_COLUMNS>
		matrix<_TYPE, _ROWS, O_COLUMNS> Multiply(const matrix<_TYPE, _COLUMNS, O_COLUMNS>& other) const noexcept;
		dynamic_matrix<_TYPE> Multiply(const dynamic_matrix<_TYPE>& other) const;
		template <unsigned int O_COLUMNS, typename Itr>
		matrix<_TYPE, _ROWS, O_COLUMNS> Multiply(const matrix_view<_TYPE, _COLUMNS, O_COLUMNS, Itr>& other) const noexcept;
		template <typename Itr>
		dynamic_matrix<_TYPE> Multiply(const dynamic_matrix_view<_TYPE, Itr>& other) const;

		vector<_TYPE, _ROWS> Multiply(const vector<_TYPE, _COLUMNS>& vec) const noexcept;
		template <typename Itr>
		vector<_TYPE, _ROWS> Multiply(const vector_view<_TYPE, _COLUMNS, Itr>& vec) const noexcept;

		vector<_TYPE, _ROWS> Multiply(const dynamic_vector<_TYPE>& vec) const noexcept;
		template <typename Itr>
		vector<_TYPE, _ROWS> Multiply(const dynamic_vector_view<_TYPE, Itr>& vec) const noexcept;

		//Vector Getters and Setters
		vector<_TYPE, _COLUMNS> GetRowVector(const unsigned int row)    const noexcept { return vector<_TYPE, _COLUMNS>(cbegin_row(row).unwrap(), 0); }
		vector<_TYPE, _ROWS>    GetColumnVector(const unsigned int column) const noexcept;

		vector_view<_TYPE, _COLUMNS, row_const_iterator> GetRowView(const unsigned int row) const noexcept
		{
			return vector_view<_TYPE, _COLUMNS, row_const_iterator>(*(const _TYPE(*)[_COLUMNS])(cbegin_row(row).unwrap()));
		}

		vector_view<_TYPE, _ROWS, column_const_iterator> GetColumnView(const unsigned int column) const noexcept
		{
			return vector_view<_TYPE, _ROWS, column_const_iterator>(*(const _TYPE(*)[_COLUMNS])(cbegin_column(column)));
		}

		matrix_view<_TYPE, _ROWS, _COLUMNS, const_iterator> GetView() const noexcept
		{
			return matrix_view<_TYPE, _ROWS, _COLUMNS, const_iterator>(*this);
		}

		matrix_view<_TYPE, _COLUMNS, _ROWS, column_const_iterator> GetTransposeView() const noexcept
		{
			return matrix_view<_TYPE, _COLUMNS, _ROWS, column_const_iterator>(GetArray());
		}

		matrix& SetRowVector(const unsigned int row, const vector<_TYPE, _COLUMNS>& vec) noexcept;
		matrix& SetRowVector(const unsigned int row, const dynamic_vector<_TYPE>& vec);
		template <typename Itr>
		matrix& SetRowVector(const unsigned int row, const vector_view<_TYPE, _COLUMNS, Itr>& vec) noexcept;
		template <typename Itr>
		matrix& SetRowVector(const unsigned int row, const dynamic_vector_view<_TYPE, Itr>& vec) noexcept;

		matrix& SetColumnVector(const unsigned int column, const vector<_TYPE, _ROWS>& vec) noexcept;
		matrix& SetColumnVector(const unsigned int column, const dynamic_vector<_TYPE>& vec);
		template <typename Itr>
		matrix& SetColumnVector(const unsigned int column, const vector_view<_TYPE, _ROWS, Itr>& vec) noexcept;
		template <typename Itr>
		matrix& SetColumnVector(const unsigned int column, const dynamic_vector_view<_TYPE, Itr>& vec) noexcept;

		matrix& SetAll(const _TYPE& value) noexcept;

		matrix& SetAllRows(const vector<_TYPE, _COLUMNS>& vec) noexcept;
		matrix& SetAllColumns(const vector<_TYPE, _ROWS>& vec)    noexcept;
		template <typename Itr>
		matrix& SetAllRows(const vector_view<_TYPE, _COLUMNS, Itr>& vec) noexcept;
		template <typename Itr>
		matrix& SetAllColumns(const vector_view<_TYPE, _ROWS, Itr>& vec)    noexcept;

		matrix& SetAllRows(const dynamic_vector<_TYPE>& vec);
		matrix& SetAllColumns(const dynamic_vector<_TYPE>& vec);
		template <typename Itr>
		matrix& SetAllRows(const dynamic_vector_view<_TYPE, Itr>& vec);
		template <typename Itr>
		matrix& SetAllColumns(const dynamic_vector_view<_TYPE, Itr>& vec);

		//Data manipulation functions
		template <typename _FUNCTION>
		matrix& ApplyToMatrix(_FUNCTION&& func);

		template <typename _FUNCTION>
		matrix& ApplyToRow(const unsigned int row, _FUNCTION&& func);

		template <typename _FUNCTION>
		matrix& ApplyToColumn(const unsigned int column, _FUNCTION&& func);

		//Casting
		template<typename O_TYPE>
		matrix<O_TYPE, _ROWS, _COLUMNS> Cast() const noexcept;

		//Data Info Functions
		static constexpr unsigned int container_row_size()    noexcept { return _ROWS; }
		static constexpr unsigned int container_column_size() noexcept { return _COLUMNS; }
		static constexpr unsigned int container_size()        noexcept { return container_row_size() * container_column_size(); }

		constexpr _TYPE* GetData()        noexcept { return _data; }
		constexpr const _TYPE* GetData()  const noexcept { return _data; }
		constexpr auto& GetArray()       noexcept { return _data; }
		constexpr const auto& GetArray() const noexcept { return _data; }

		constexpr unsigned int GetRowSize()    const noexcept { return container_row_size(); }
		constexpr unsigned int GetColumnSize() const noexcept { return container_column_size(); }
		constexpr unsigned int GetSize()       const noexcept { return container_size(); }

		//Iterators
		constexpr iterator begin() noexcept { return iterator(_data); }
		constexpr iterator end()   noexcept { return iterator(_data + GetSize()); }

		//Unwrapped Iterators (u stands for unwrapped)
		constexpr auto ubegin() noexcept { return begin().unwrap(); }
		constexpr auto uend()   noexcept { return end().unwrap(); }

		//Const iterators
		constexpr const_iterator cbegin() const noexcept { return const_iterator(_data); }
		constexpr const_iterator cend()   const noexcept { return const_iterator(_data + GetSize()); }

		//Unwrapped const iterators
		constexpr auto ucbegin() const noexcept { return cbegin().unwrap(); }
		constexpr auto ucend()   const noexcept { return cend().unwrap(); }

		//Row iterators
		constexpr row_iterator begin_row(const unsigned int row) noexcept { return row_iterator(&_data[row * _COLUMNS]); }
		constexpr row_iterator end_row(const unsigned int row) noexcept { return row_iterator(&_data[(row + 1) * _COLUMNS]); }

		//Row const iterators
		constexpr row_const_iterator cbegin_row(const unsigned int row) const noexcept { return row_const_iterator(&_data[row * _COLUMNS]); }
		constexpr row_const_iterator cend_row(const unsigned int row) const noexcept { return row_const_iterator(&_data[(row + 1) * _COLUMNS]); }

		//Column iterators
		constexpr column_iterator begin_column(const unsigned int column) noexcept { return column_iterator(&_data[column]); }
		constexpr column_iterator end_column(const unsigned int column) noexcept { return column_iterator(&_data[column + _COLUMNS * _ROWS]); }

		//Column const iterators
		constexpr column_const_iterator cbegin_column(const unsigned int column) const noexcept { return column_const_iterator(&_data[column]); }
		constexpr column_const_iterator cend_column(const unsigned int column) const noexcept { return column_const_iterator(&_data[column + _COLUMNS * _ROWS]); }
	private:
		_TYPE _data[_ROWS * _COLUMNS]{};

	};

	//Constexpr matrix initializer
	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	struct constexpr_matrix
	{
		constexpr constexpr_matrix() noexcept = default;
		constexpr constexpr_matrix(const _TYPE& value) noexcept;
		constexpr constexpr_matrix(const _TYPE(&data)[_ROWS * _COLUMNS]) noexcept;
		//constexpr constexpr_matrix(std::initializer_list<_TYPE> list) noexcept;
		//constexpr constexpr_matrix(std::initializer_list<std::initializer_list<_TYPE>> list) noexcept;

		constexpr auto& GetArray()       noexcept { return _data; }
		constexpr const auto& GetArray() const noexcept { return _data; }
	private:
		_TYPE _data[_ROWS * _COLUMNS]{};
	};

	template<typename MATRIX_TYPE>
	struct matrix_iterator
	{
		using _TYPE = typename MATRIX_TYPE::ElemType;
		static constexpr const unsigned int _COLUMNS = MATRIX_TYPE::container_column_size();
		static constexpr const unsigned int _ROWS = MATRIX_TYPE::container_row_size();
		using ComplementIter = typename MATRIX_TYPE::column_iterator;

		constexpr matrix_iterator() noexcept = default;
		constexpr matrix_iterator(const matrix_iterator&) noexcept = default;
		constexpr matrix_iterator(_TYPE* const ptr) noexcept :_ptr(ptr) {}

		constexpr matrix_iterator& operator=(const matrix_iterator&) noexcept = default;
		constexpr matrix_iterator& operator++()    noexcept { return (++_ptr, *this); }
		constexpr matrix_iterator  operator++(int) noexcept { return (++ * this, *this - 1); }
		constexpr matrix_iterator& operator--()    noexcept { return (--_ptr, *this); }
		constexpr matrix_iterator  operator--(int) noexcept { return (-- * this, *this + 1); }

		constexpr matrix_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += offset, *this); }
		constexpr matrix_iterator  operator+ (const uintptr_t offset) const noexcept { return matrix_iterator(_ptr + offset); }
		constexpr matrix_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= offset, *this); }
		constexpr matrix_iterator  operator- (const uintptr_t offset) const noexcept { return matrix_iterator(_ptr - offset); }

		constexpr uintptr_t operator-(const matrix_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		constexpr bool operator==(const matrix_iterator& other) const noexcept { return _ptr == other._ptr; }
		constexpr bool operator!=(const matrix_iterator& other) const noexcept { return !(*this == other); }
		constexpr bool operator< (const matrix_iterator& other) const noexcept { return _ptr < other._ptr; }
		constexpr bool operator> (const matrix_iterator& other) const noexcept { return other._ptr < _ptr; }
		constexpr bool operator<=(const matrix_iterator& other) const noexcept { return !(*this > other); }
		constexpr bool operator>=(const matrix_iterator& other) const noexcept { return !(*this < other); }

		constexpr operator _TYPE* () noexcept { return _ptr; }
		constexpr _TYPE* unwrap() const noexcept { return _ptr; }

		constexpr uint32_t step() const noexcept { return 1; }
		constexpr ComplementIter complIter() const noexcept { return ComplementIter(_ptr); }
		constexpr matrix_iterator toRow(const unsigned int row) const noexcept { return matrix_iterator(_ptr + (row * _COLUMNS)); }
		constexpr matrix_iterator toColumn(const unsigned int column) const noexcept { return matrix_iterator(_ptr + column); }
		constexpr matrix_iterator toEnd() const noexcept { return matrix_iterator(_ptr + _ROWS * _COLUMNS); }

		constexpr _TYPE* operator->() noexcept { return _ptr; }
		constexpr _TYPE& operator[](const unsigned int index) { return *(_ptr + index); }
		constexpr _TYPE& operator*() { return *_ptr; }

	private:
		_TYPE* _ptr;
	};

	template<typename MATRIX_TYPE>
	struct matrix_const_iterator
	{
		using _TYPE = typename MATRIX_TYPE::ElemType;
		static constexpr const unsigned int _COLUMNS = MATRIX_TYPE::container_column_size();
		static constexpr const unsigned int _ROWS = MATRIX_TYPE::container_row_size();
		using ComplementIter = typename MATRIX_TYPE::column_const_iterator;

		constexpr matrix_const_iterator() noexcept = default;
		constexpr matrix_const_iterator(const matrix_const_iterator&) noexcept = default;
		constexpr matrix_const_iterator(const _TYPE* const ptr) noexcept :_ptr(ptr) {}

		constexpr matrix_const_iterator& operator=(const matrix_const_iterator&) noexcept = default;
		constexpr matrix_const_iterator& operator++()    noexcept { return (++_ptr, *this); }
		constexpr matrix_const_iterator  operator++(int) noexcept { return (++ * this, *this - 1); }
		constexpr matrix_const_iterator& operator--()    noexcept { return (--_ptr, *this); }
		constexpr matrix_const_iterator  operator--(int) noexcept { return (-- * this, *this + 1); }

		constexpr matrix_const_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += offset, *this); }
		constexpr matrix_const_iterator  operator+ (const uintptr_t offset) const noexcept { return matrix_const_iterator(_ptr + offset); }
		constexpr matrix_const_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= offset, *this); }
		constexpr matrix_const_iterator  operator- (const uintptr_t offset) const noexcept { return matrix_const_iterator(_ptr - offset); }

		constexpr uintptr_t operator-(const matrix_const_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		constexpr bool operator==(const matrix_const_iterator& other) const noexcept { return _ptr == other._ptr; }
		constexpr bool operator!=(const matrix_const_iterator& other) const noexcept { return !(*this == other); }
		constexpr bool operator< (const matrix_const_iterator& other) const noexcept { return _ptr < other._ptr; }
		constexpr bool operator> (const matrix_const_iterator& other) const noexcept { return other._ptr < _ptr; }
		constexpr bool operator<=(const matrix_const_iterator& other) const noexcept { return !(*this > other); }
		constexpr bool operator>=(const matrix_const_iterator& other) const noexcept { return !(*this < other); }

		constexpr operator const _TYPE* () const noexcept { return _ptr; }
		constexpr const _TYPE* unwrap() const noexcept { return _ptr; }

		constexpr uint32_t step() const noexcept { return 1; }
		constexpr ComplementIter complIter() const noexcept { return ComplementIter(_ptr); }
		constexpr matrix_const_iterator toRow(const unsigned int row) const noexcept { return matrix_const_iterator(_ptr + (row * _COLUMNS)); }
		constexpr matrix_const_iterator toColumn(const unsigned int column) const noexcept { return matrix_const_iterator(_ptr + column); }
		constexpr matrix_const_iterator toEnd() const noexcept { return matrix_const_iterator(_ptr + _ROWS * _COLUMNS); }

		constexpr const _TYPE* operator->() const noexcept { return _ptr; }
		constexpr const _TYPE& operator[](const unsigned int index) const { return *(_ptr + index); }
		constexpr const _TYPE& operator*() const { return *_ptr; }

	private:
		const _TYPE* _ptr;
	};

	template<typename MATRIX_TYPE>
	struct matrix_column_iterator
	{
		using _TYPE = typename MATRIX_TYPE::ElemType;
		using ComplementIter = typename MATRIX_TYPE::iterator;
		static constexpr const unsigned int _COLUMNS = MATRIX_TYPE::container_column_size();
		static constexpr const unsigned int _ROWS = MATRIX_TYPE::container_row_size();

		constexpr matrix_column_iterator() noexcept = default;
		constexpr matrix_column_iterator(const matrix_column_iterator&) noexcept = default;
		constexpr matrix_column_iterator(_TYPE* const ptr) noexcept :_ptr(ptr) {}

		constexpr matrix_column_iterator& operator= (const matrix_column_iterator&) noexcept = default;
		constexpr matrix_column_iterator& operator++()    noexcept { return (_ptr += _COLUMNS, *this); }
		constexpr matrix_column_iterator  operator++(int) noexcept { return (++ * this, *this - 1); }
		constexpr matrix_column_iterator& operator--()    noexcept { return (_ptr -= _COLUMNS, *this); }
		constexpr matrix_column_iterator  operator--(int) noexcept { return (-- * this, *this + 1); }

		constexpr matrix_column_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += (offset * _COLUMNS), *this); }
		constexpr matrix_column_iterator  operator+ (const uintptr_t offset) const noexcept { return matrix_column_iterator(_ptr + (offset * _COLUMNS)); }
		constexpr matrix_column_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= (offset * _COLUMNS), *this); }
		constexpr matrix_column_iterator  operator- (const uintptr_t offset) const noexcept { return matrix_column_iterator(_ptr - (offset * _COLUMNS)); }

		constexpr uintptr_t operator-(const matrix_column_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		constexpr bool operator==(const matrix_column_iterator& other) const noexcept { return _ptr == other._ptr; }
		constexpr bool operator!=(const matrix_column_iterator& other) const noexcept { return !(*this == other); }
		constexpr bool operator< (const matrix_column_iterator& other) const noexcept { return _ptr < other._ptr; }
		constexpr bool operator> (const matrix_column_iterator& other) const noexcept { return other._ptr < _ptr; }
		constexpr bool operator<=(const matrix_column_iterator& other) const noexcept { return !(*this > other); }
		constexpr bool operator>=(const matrix_column_iterator& other) const noexcept { return !(*this < other); }

		constexpr operator _TYPE* () const noexcept { return _ptr; }
		constexpr _TYPE* unwrap() const noexcept { return _ptr; }

		constexpr uint32_t step() const noexcept { return _COLUMNS; }
		constexpr ComplementIter complIter() const noexcept { return ComplementIter(_ptr); }
		constexpr matrix_column_iterator toRow(const unsigned int row) const noexcept { return matrix_column_iterator(_ptr + (row * _COLUMNS)); }
		constexpr matrix_column_iterator toColumn(const unsigned int column) const noexcept { return matrix_column_iterator(_ptr + column); }
		constexpr matrix_column_iterator toEnd() const noexcept { return matrix_column_iterator(_ptr + _ROWS * _COLUMNS); }

		constexpr _TYPE* operator->() noexcept { return _ptr; }
		constexpr _TYPE& operator[](const unsigned int index) { return *(_ptr + (index * _COLUMNS)); }
		constexpr _TYPE& operator*() { return *_ptr; }

	private:
		_TYPE* _ptr;
	};

	template<typename MATRIX_TYPE>
	struct matrix_column_const_iterator
	{
		using _TYPE = typename MATRIX_TYPE::ElemType;
		using ComplementIter = typename MATRIX_TYPE::const_iterator;
		static constexpr const unsigned int _COLUMNS = MATRIX_TYPE::container_column_size();
		static constexpr const unsigned int _ROWS = MATRIX_TYPE::container_row_size();

		constexpr matrix_column_const_iterator() noexcept = default;
		constexpr matrix_column_const_iterator(const matrix_column_const_iterator&) noexcept = default;
		constexpr matrix_column_const_iterator(const _TYPE* const ptr) noexcept :_ptr(ptr) {}

		constexpr matrix_column_const_iterator& operator=(const matrix_column_const_iterator&) noexcept = default;
		constexpr matrix_column_const_iterator& operator++()    noexcept { return (_ptr += _COLUMNS, *this); }
		constexpr matrix_column_const_iterator  operator++(int) noexcept { return (++ * this, *this - 1); }
		constexpr matrix_column_const_iterator& operator--()    noexcept { return (_ptr -= _COLUMNS, *this); }
		constexpr matrix_column_const_iterator  operator--(int) noexcept { return (-- * this, *this + 1); }

		constexpr matrix_column_const_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += (offset * _COLUMNS), *this); }
		constexpr matrix_column_const_iterator operator+  (const uintptr_t offset) const noexcept { return matrix_column_const_iterator(_ptr + (offset * _COLUMNS)); }
		constexpr matrix_column_const_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= (offset * _COLUMNS), *this); }
		constexpr matrix_column_const_iterator  operator- (const uintptr_t offset) const noexcept { return matrix_column_const_iterator(_ptr - (offset * _COLUMNS)); }

		constexpr uintptr_t operator-(const matrix_column_const_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		constexpr bool operator==(const matrix_column_const_iterator& other) const noexcept { return _ptr == other._ptr; }
		constexpr bool operator!=(const matrix_column_const_iterator& other) const noexcept { return !(*this == other); }
		constexpr bool operator< (const matrix_column_const_iterator& other) const noexcept { return _ptr < other._ptr; }
		constexpr bool operator> (const matrix_column_const_iterator& other) const noexcept { return other._ptr < _ptr; }
		constexpr bool operator<=(const matrix_column_const_iterator& other) const noexcept { return !(*this > other); }
		constexpr bool operator>=(const matrix_column_const_iterator& other) const noexcept { return !(*this < other); }

		constexpr operator const _TYPE* () const noexcept { return _ptr; }
		constexpr const _TYPE* unwrap() const noexcept { return _ptr; }

		constexpr uint32_t step() const noexcept { return _COLUMNS; }
		constexpr ComplementIter complIter() const noexcept { return ComplementIter(_ptr); }
		constexpr matrix_column_const_iterator toRow(const unsigned int row) const noexcept { return matrix_column_const_iterator(_ptr + (row * _COLUMNS)); }
		constexpr matrix_column_const_iterator toColumn(const unsigned int column) const noexcept { return matrix_column_const_iterator(_ptr + column); }
		constexpr matrix_column_const_iterator toEnd() const noexcept { return matrix_column_const_iterator(_ptr + _ROWS * _COLUMNS); }

		constexpr const _TYPE* operator->() const noexcept { return _ptr; }
		constexpr const _TYPE& operator[](const unsigned int index) const { return *(_ptr + (index * _COLUMNS)); }
		constexpr const _TYPE& operator*() const { return *_ptr; }

	private:
		const _TYPE* _ptr;
	};

	template <std::size_t ROWS, std::size_t COLUMNS, typename T, typename... Ts>
	inline matrix<T, ROWS, COLUMNS> make_matrix(T val, Ts... vals) noexcept
	{
		static_assert((sizeof...(Ts) + 1) == (ROWS * COLUMNS), "Error argument mismatch");
		return matrix<T, ROWS, COLUMNS>{ val, vals... };
	}

	using mat3i = matrix<int, 3, 3>;
	using mat3f = matrix<float, 3, 3>;
	using mat4i = matrix<int, 4, 4>;
	using mat4f = matrix<float, 4, 4>;
}

#include "matrix.ipp"
#include "matrix2x2.h"
#include "matrix_operations.h"

const stm::mat3i identity_mat3i = stm::GetIndentityMatrix<int  , 3, 3>();
const stm::mat3f identity_mat3f = stm::GetIndentityMatrix<float, 3, 3>();
const stm::mat4i identity_mat4i = stm::GetIndentityMatrix<int  , 4, 4>();
const stm::mat4f identity_mat4f = stm::GetIndentityMatrix<float, 4, 4>();

#endif /* stm_matrix_h */