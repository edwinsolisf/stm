#ifndef dynamic_matrix_h
#define dynamic_matrix_h

#include "debug.h"

namespace stm
{
	template <typename T, typename Itr>
	class dynamic_matrix_view;

	template<typename T>
	class dynamic_vector;

	template <typename T, typename Itr>
	class dynamic_vector_view;

	template<typename T, unsigned int ROWS, unsigned int COLUMNS>
	class matrix;

	template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
	class matrix_view;

	template<typename T, unsigned int DIM>
	class vector;

	template <typename T, unsigned int DIM, typename Itr>
	class vector_view;

	template<typename _MATRIX_TYPE>
	struct dynamic_matrix_iterator;

	template<typename _MATRIX_TYPE>
	struct dynamic_matrix_const_iterator;

	template<typename _MATRIX_TYPE>
	struct dynamic_matrix_column_iterator;

	template<typename _MATRIX_TYPE>
	struct dynamic_matrix_column_const_iterator;

	template<typename _T>
	class dynamic_matrix
	{
	public:
		using ElemType = _T;
		using iterator = dynamic_matrix_iterator<dynamic_matrix<_T>>;
		using const_iterator = dynamic_matrix_const_iterator<dynamic_matrix<_T>>;
		using row_iterator = dynamic_matrix_iterator<dynamic_matrix<_T>>;
		using row_const_iterator = dynamic_matrix_const_iterator<dynamic_matrix<_T>>;
		using column_iterator = dynamic_matrix_column_iterator<dynamic_matrix<_T>>;
		using column_const_iterator = dynamic_matrix_column_const_iterator<dynamic_matrix<_T>>;

		//Constructors
		dynamic_matrix(const unsigned int rows, const unsigned int columns);
		dynamic_matrix(const unsigned int rows, const unsigned int columns, const _T* const data);
		dynamic_matrix(const unsigned int rows, const unsigned int columns, const _T& value);
		dynamic_matrix(const unsigned int rows, const unsigned int columns, std::initializer_list<_T> list);
		dynamic_matrix(const unsigned int rows, const unsigned int columns, std::initializer_list<std::initializer_list<_T>> list);
		dynamic_matrix(const dynamic_matrix& other);
		dynamic_matrix(dynamic_matrix&& other) noexcept;
		dynamic_matrix(_T*& data, const unsigned int rows, const unsigned int columns);
		template <typename Itr>
		dynamic_matrix(const dynamic_matrix_view<_T, Itr>& view);

		template<unsigned int rows, unsigned int columns>
		explicit dynamic_matrix(const matrix<_T, rows, columns>& static_matrix);

		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		explicit dynamic_matrix(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& static_matrix);

		//Destructor
		~dynamic_matrix();

		//Assigment Operators
		dynamic_matrix& operator=(const dynamic_matrix& other);
		dynamic_matrix& operator=(dynamic_matrix&& other) noexcept;
		template <typename Itr>
		dynamic_matrix& operator=(const dynamic_matrix_view<_T, Itr>& other);

		template<unsigned int rows, unsigned int columns>
		dynamic_matrix& operator=(const matrix<_T, rows, columns>& other);
		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		dynamic_matrix& operator=(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& other);

		//Unary Operators
		_T*       operator[](unsigned int index)       noexcept { stm_assert(index < _rows); return &_data[index * _columns]; }
		const _T* operator[](unsigned int index) const noexcept { stm_assert(index < _rows); return &_data[index * _columns]; }

		dynamic_matrix   operator+() const& noexcept { return *this; }
		dynamic_matrix&& operator+() &&     noexcept { return std::move(*this); }

		dynamic_matrix   operator-() const&;
		dynamic_matrix&& operator-() &&;

		//Binary Operators
		dynamic_matrix   operator+(const dynamic_matrix& other) const&;
		dynamic_matrix&& operator+(const dynamic_matrix& other) &&;
		dynamic_matrix&& operator+(dynamic_matrix&& other) const&;
		dynamic_matrix&& operator+(dynamic_matrix&& other) &&;

		dynamic_matrix   operator-(const dynamic_matrix& other) const&;
		dynamic_matrix&& operator-(const dynamic_matrix& other) &&;
		dynamic_matrix&& operator-(dynamic_matrix&& other) const&;
		dynamic_matrix&& operator-(dynamic_matrix&& other) &&;

		dynamic_matrix   operator*(const dynamic_matrix& other) const&;
		dynamic_matrix&& operator*(const dynamic_matrix& other) &&;
		dynamic_matrix&& operator*(dynamic_matrix&& other) const&;
		dynamic_matrix&& operator*(dynamic_matrix&& other) &&;

		dynamic_matrix   operator/(const dynamic_matrix& other) const&;
		dynamic_matrix&& operator/(const dynamic_matrix& other) &&;
		dynamic_matrix&& operator/(dynamic_matrix&& other) const&;
		dynamic_matrix&& operator/(dynamic_matrix&& other) &&;

		template <typename Itr>
		dynamic_matrix   operator+(const dynamic_matrix_view<_T, Itr>& other) const&;
		template <typename Itr>
		dynamic_matrix&& operator+(const dynamic_matrix_view<_T, Itr>& other) &&;
		template <typename Itr>
		dynamic_matrix   operator-(const dynamic_matrix_view<_T, Itr>& other) const&;
		template <typename Itr>
		dynamic_matrix&& operator-(const dynamic_matrix_view<_T, Itr>& other) &&;
		template <typename Itr>
		dynamic_matrix   operator*(const dynamic_matrix_view<_T, Itr>& other) const&;
		template <typename Itr>
		dynamic_matrix&& operator*(const dynamic_matrix_view<_T, Itr>& other) &&;
		template <typename Itr>
		dynamic_matrix   operator/(const dynamic_matrix_view<_T, Itr>& other) const&;
		template <typename Itr>
		dynamic_matrix&& operator/(const dynamic_matrix_view<_T, Itr>& other) &&;
		
		template<unsigned int rows, unsigned int columns>
		matrix<_T, rows, columns> operator+(const matrix<_T, rows, columns>& static_matrix) const noexcept;

		template<unsigned int rows, unsigned int columns>
		matrix<_T, rows, columns> operator-(const matrix<_T, rows, columns>& static_matrix) const noexcept;

		template<unsigned int rows, unsigned int columns>
		matrix<_T, rows, columns> operator*(const matrix<_T, rows, columns>& static_matrix) const noexcept;

		template<unsigned int rows, unsigned int columns>
		matrix<_T, rows, columns> operator/(const matrix<_T, rows, columns>& static_matrix) const noexcept;


		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		matrix<_T, _ROWS, _COLUMNS> operator+(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& static_matrix) const noexcept;
		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		matrix<_T, _ROWS, _COLUMNS> operator-(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& static_matrix) const noexcept;
		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		matrix<_T, _ROWS, _COLUMNS> operator*(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& static_matrix) const noexcept;
		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		matrix<_T, _ROWS, _COLUMNS> operator/(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& static_matrix) const noexcept;

		dynamic_matrix   operator+(const _T& value) const&;
		dynamic_matrix&& operator+(const _T& value) &&;

		dynamic_matrix   operator-(const _T& value) const&;
		dynamic_matrix&& operator-(const _T& value) &&;

		dynamic_matrix   operator*(const _T& value) const&;
		dynamic_matrix&& operator*(const _T& value) &&;

		dynamic_matrix   operator/(const _T& value) const&;
		dynamic_matrix&& operator/(const _T& value) &&;


		//Binary-assigment operators
		dynamic_matrix& operator+=(const dynamic_matrix& other);
		dynamic_matrix& operator-=(const dynamic_matrix& other);
		dynamic_matrix& operator*=(const dynamic_matrix& other);
		dynamic_matrix& operator/=(const dynamic_matrix& other);

		template <typename Itr>
		dynamic_matrix& operator+=(const dynamic_matrix_view<_T, Itr>& other);
		template <typename Itr>
		dynamic_matrix& operator-=(const dynamic_matrix_view<_T, Itr>& other);
		template <typename Itr>
		dynamic_matrix& operator*=(const dynamic_matrix_view<_T, Itr>& other);
		template <typename Itr>
		dynamic_matrix& operator/=(const dynamic_matrix_view<_T, Itr>& other);

		template<unsigned int rows, unsigned int columns>
		dynamic_matrix& operator+=(const matrix<_T, rows, columns>& static_matrix) noexcept;

		template<unsigned int rows, unsigned int columns>
		dynamic_matrix& operator-=(const matrix<_T, rows, columns>& static_matrix) noexcept;

		template<unsigned int rows, unsigned int columns>
		dynamic_matrix& operator*=(const matrix<_T, rows, columns>& static_matrix) noexcept;

		template<unsigned int rows, unsigned int columns>
		dynamic_matrix& operator/=(const matrix<_T, rows, columns>& static_matrix) noexcept;


		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		dynamic_matrix& operator+=(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& other) noexcept;
		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		dynamic_matrix& operator-=(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& other) noexcept;
		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		dynamic_matrix& operator*=(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& other) noexcept;
		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		dynamic_matrix& operator/=(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& other) noexcept;

		dynamic_matrix& operator+=(const _T& value) noexcept;
		dynamic_matrix& operator-=(const _T& value) noexcept;
		dynamic_matrix& operator*=(const _T& value) noexcept;
		dynamic_matrix& operator/=(const _T& value) noexcept;


		dynamic_matrix Minor(const unsigned int row, const unsigned int column) const;

		dynamic_matrix Inverse() const;
		
		dynamic_matrix   Transpose() const&;
		dynamic_matrix&& Transpose() &&;

		dynamic_matrix SubMatrix(const unsigned int rowSize, const unsigned int columnSize, const unsigned int rowOffset, const unsigned int columnOffset) const;

		_T Determinant() const;

		dynamic_matrix Multiply(const dynamic_matrix& mat) const;
		template <typename Itr>
		dynamic_matrix Multiply(const dynamic_matrix_view<_T, Itr>& other) const;

		template<unsigned int rows, unsigned int columns>
		dynamic_matrix Multiply(const matrix<_T, rows, columns>& static_matrix) const;
		template <unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
		dynamic_matrix Multiply(const matrix_view<_T, _ROWS, _COLUMNS, Itr>& other) const;

		dynamic_vector<_T> Multiply(const dynamic_vector<_T>& vec) const;
		template <typename Itr>
		dynamic_vector<_T> Multiply(const dynamic_vector_view<_T, Itr>& vec) const;

		template<unsigned int columns>
		dynamic_vector<_T> Multiply(const vector<_T, columns>& vec) const;
		template<unsigned int COLUMNS, typename Itr>
		dynamic_vector<_T> Multiply(const vector_view<_T, COLUMNS, Itr>& vec) const;

		//Vector Getters and Setters
		dynamic_vector<_T> GetRowVector   (const unsigned int row)    const { return dynamic_vector<_T>(_columns, &_data[row * _columns]); }
		dynamic_vector<_T> GetColumnVector(const unsigned int column) const;

		dynamic_vector_view<_T, row_const_iterator> GetRowView(const unsigned int row) const
		{ return dynamic_vector_view<_T, row_const_iterator>(cbegin_row(row), cend_row()); }

		dynamic_vector_view<_T, column_const_iterator> GetColumnView(const unsigned int column) const
		{ return dynamic_vector_view<_T, column_const_iterator>(cbegin_column(column), cend_column(column)); }

		dynamic_matrix_view<_T, const_iterator> GetView() const { return dynamic_matrix_view<_T, const_iterator>(*this); }
		dynamic_matrix_view<_T, column_const_iterator> GetTransposeView() const { return dynamic_matrix_view<_T, column_const_iterator>(cbegin_column(0), _columns, _rows); }
		
		dynamic_matrix& SetRowVector(const unsigned int row, const dynamic_vector<_T>& vec);
		dynamic_matrix& SetColumnVector(const unsigned int column, const dynamic_vector<_T>& vec);
		template<typename Itr>
		dynamic_matrix& SetRowVector(const unsigned int row, const dynamic_vector_view<_T, Itr>& vec);
		template<typename Itr>
		dynamic_matrix& SetColumnVector(const unsigned int column, const dynamic_vector_view<_T, Itr>& vec);

		template<unsigned int columns>
		dynamic_matrix& SetRowVector(const unsigned int row, const vector<_T, columns>& vec) noexcept;
		template<unsigned int rows>
		dynamic_matrix& SetColumnVector(const unsigned int column, const vector<_T, rows>& vec) noexcept;

		template <unsigned int _COLUMNS, typename Itr>
		dynamic_matrix& SetRowVector(const unsigned int row, const vector_view<_T, _COLUMNS, Itr>& vec) noexcept;
		template <unsigned int _ROWS, typename Itr>
		dynamic_matrix& SetColumnVector(const unsigned int column, const vector_view<_T, _ROWS, Itr>& vec) noexcept;

		dynamic_matrix& SetAll(const _T& value) noexcept;

		dynamic_matrix& SetAllRows(const dynamic_vector<_T>& vec);
		template<typename Itr>
		dynamic_matrix& SetAllRows(const dynamic_vector_view<_T, Itr>& vec);

		dynamic_matrix& SetAllColumns(const dynamic_vector<_T>& vec);
		template<typename Itr>
		dynamic_matrix& SetAllColumns(const dynamic_vector_view<_T, Itr>& vec);

		template<unsigned int columns>
		dynamic_matrix& SetAllRows(const vector<_T, columns>& vec) noexcept;
		template <unsigned int _COLUMNS, typename Itr>
		dynamic_matrix& SetAllRows(const vector_view<_T, _COLUMNS, Itr>& vec) noexcept;

		template<unsigned int rows>
		dynamic_matrix& SetAllColumns(const vector<_T, rows>& vec) noexcept;
		template <unsigned int _ROWS, typename Itr>
		dynamic_matrix& SetAllColumns(const vector_view<_T, _ROWS, Itr>& vec) noexcept;

		//Data manipulation functions
		bool Resize(const unsigned int rows, const unsigned int columns);

		template <typename _FUNCTION>
		dynamic_matrix&  ApplyToMatrix(_FUNCTION&& func) &;

		template <typename _FUNCTION>
		dynamic_matrix&& ApplyToMatrix(_FUNCTION&& func) &&;

		template <typename _FUNCTION>
		dynamic_matrix&  ApplyToRow(const unsigned int row, _FUNCTION&& func) &;

		template <typename _FUNCTION>
		dynamic_matrix&& ApplyToRow(const unsigned int row, _FUNCTION&& func) &&;

		template <typename _FUNCTION>
		dynamic_matrix&  ApplyToColumn(const unsigned int column, _FUNCTION&& func) &;

		template <typename _FUNCTION>
		dynamic_matrix&& ApplyToColumn(const unsigned int column, _FUNCTION&& func) &&;

		//Casting
		template<typename O_TYPE>
		dynamic_matrix<O_TYPE> Cast() const;

		//Data Info Functions
		_T*       GetData() noexcept       { return _data; }
		const _T* GetData() const noexcept { return _data; }

		_T*&             GetRefToPtrData()       noexcept { return _data; }
		const _T* const& GetRefToPtrData() const noexcept { return _data; }

		unsigned int GetRowSize()    const noexcept { return _rows; }
		unsigned int GetColumnSize() const noexcept { return _columns; }
		unsigned int GetSize()       const noexcept { return _rows * _columns; }

		//Iterator
		iterator begin() noexcept { return iterator(_data, _rows, _columns); }
		iterator end  () noexcept { return iterator(_data + GetSize(), _rows, _columns); }

		auto ubegin() noexcept { return begin().unwrap(); }
		auto uend  () noexcept { return end().unwrap(); }

		//Const iterator
		const_iterator cbegin() const noexcept { return const_iterator(_data, _rows, _columns); }
		const_iterator cend  () const noexcept { return const_iterator(_data + GetSize(), _rows, _columns); }

		auto ucbegin() const noexcept { return cbegin().unwrap(); }
		auto ucend  () const noexcept { return cend().unwrap(); }

		//Row iterator
		row_iterator begin_row(const unsigned int row) noexcept { return row_iterator(&_data[row * _columns], _rows, _columns); }
		row_iterator end_row  (const unsigned int row) noexcept { return row_iterator(&_data[(row + 1) * _columns], _rows, _columns); }

		//Row const iterator
		row_iterator cbegin_row(const unsigned int row) const noexcept { return row_const_iterator(&_data[row * _columns], _rows, _columns); }
		row_iterator cend_row  (const unsigned int row) const noexcept { return row_const_iterator(&_data[(row + 1) * _columns], _rows, _columns); }

		//Column iterator
		column_iterator begin_column(const unsigned int column) noexcept { return column_iterator(&_data[column], _rows, _columns); }
		column_iterator end_column  (const unsigned int column) noexcept { return column_iterator(&_data[column + GetSize()], _columns); }

		//Column const iterator
		column_const_iterator cbegin_column(const unsigned int column) const noexcept { return column_const_iterator(&_data[column], _rows, _columns); }
		column_const_iterator cend_column  (const unsigned int column) const noexcept { return column_const_iterator(&_data[column + GetSize()], _rows, _columns); }

		friend dynamic_vector<_T>;
	private:
		_T* _data;
		unsigned int _rows, _columns;	
	};

	template<typename MATRIX_TYPE>
	struct dynamic_matrix_iterator
	{
		using _TYPE = typename MATRIX_TYPE::ElemType;
		using ComplementIter = typename MATRIX_TYPE::column_iterator;

		dynamic_matrix_iterator() noexcept = default;
		dynamic_matrix_iterator(const dynamic_matrix_iterator&) noexcept = default;
		dynamic_matrix_iterator(_TYPE* const ptr, const size_t rows, const size_t columns) noexcept :_ptr(ptr), _rows(rows), _columns(columns) {}

		dynamic_matrix_iterator& operator=(const dynamic_matrix_iterator&) noexcept = default;
		dynamic_matrix_iterator& operator++()    noexcept { return (++_ptr, *this); }
		dynamic_matrix_iterator  operator++(int) noexcept { return (++*this, *this - 1); }
		dynamic_matrix_iterator& operator--()    noexcept { return (--_ptr, *this); }
		dynamic_matrix_iterator  operator--(int) noexcept { return (--*this, *this + 1); }

		dynamic_matrix_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += offset, *this); }
		dynamic_matrix_iterator  operator+ (const uintptr_t offset) const noexcept { return dynamic_matrix_iterator(_ptr + offset, _rows, _columns); }
		dynamic_matrix_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= offset, *this); }
		dynamic_matrix_iterator  operator- (const uintptr_t offset) const noexcept { return dynamic_matrix_iterator(_ptr - offset, _rows, _columns); }

		uintptr_t operator-(const dynamic_matrix_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		bool operator==(const dynamic_matrix_iterator& other) const noexcept { return _ptr == other._ptr; }
		bool operator!=(const dynamic_matrix_iterator& other) const noexcept { return !(*this == other); }
		bool operator< (const dynamic_matrix_iterator& other) const noexcept { return _ptr < other._ptr; }
		bool operator> (const dynamic_matrix_iterator& other) const noexcept { return other._ptr < _ptr; }
		bool operator<=(const dynamic_matrix_iterator& other) const noexcept { return !(*this > other); }
		bool operator>=(const dynamic_matrix_iterator& other) const noexcept { return !(*this < other); }

		operator _TYPE* () noexcept { return _ptr; }
		_TYPE* unwrap() const noexcept { return _ptr; }

		constexpr uint32_t step() const noexcept { return 1; }
		ComplementIter complIter() const noexcept { ComplementIter(_ptr, _rows, _columns); }
		dynamic_matrix_iterator toRow(const unsigned int row) const noexcept { return dynamic_matrix_iterator(_ptr + (row * _columns), _rows, _columns); }
		dynamic_matrix_iterator toColumn(const unsigned int column) const noexcept { return dynamic_matrix_iterator(_ptr + column, _rows, _columns); }
		dynamic_matrix_iterator toEnd() const noexcept { return dynamic_matrix_iterator(_ptr + _rows * _columns, _rows, _columns); }
		size_t GetRowSize() const noexcept { return _rows; }
		size_t GetColumnSize() const noexcept { return _columns; }

		_TYPE* operator->() noexcept { return _ptr; }
		_TYPE& operator[](const unsigned int index) { return *(_ptr + index); }
		_TYPE& operator*() { return *_ptr; }

	private:
		_TYPE* _ptr;
		const size_t _rows;
		const size_t _columns;
	};

		template<typename MATRIX_TYPE>
	struct dynamic_matrix_const_iterator
	{
		using _TYPE = typename MATRIX_TYPE::ElemType;
		using ComplementIter = typename MATRIX_TYPE::column_const_iterator;

		dynamic_matrix_const_iterator() noexcept = default;
		dynamic_matrix_const_iterator(const dynamic_matrix_const_iterator&) noexcept = default;
		dynamic_matrix_const_iterator(const _TYPE* const ptr, const size_t rows, const size_t columns) noexcept :_ptr(ptr) ,_rows(rows), _columns(columns) {}

		dynamic_matrix_const_iterator& operator=(const dynamic_matrix_const_iterator&) noexcept = default;
		dynamic_matrix_const_iterator& operator++()    noexcept { return (++_ptr, *this); }
		dynamic_matrix_const_iterator  operator++(int) noexcept { return (++*this, *this - 1); }
		dynamic_matrix_const_iterator& operator--()    noexcept { return (--_ptr, *this); }
		dynamic_matrix_const_iterator  operator--(int) noexcept { return (--*this, *this + 1); }

		dynamic_matrix_const_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += offset, *this); }
		dynamic_matrix_const_iterator  operator+ (const uintptr_t offset) const noexcept { return dynamic_matrix_const_iterator(_ptr + offset, _rows, _columns); }
		dynamic_matrix_const_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= offset, *this); }
		dynamic_matrix_const_iterator  operator- (const uintptr_t offset) const noexcept { return dynamic_matrix_const_iterator(_ptr - offset, _rows, _columns); }

		uintptr_t operator-(const dynamic_matrix_const_iterator& other) const noexcept{ return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		bool operator==(const dynamic_matrix_const_iterator& other) const noexcept { return _ptr == other._ptr; }
		bool operator!=(const dynamic_matrix_const_iterator& other) const noexcept { return !(*this == other); }
		bool operator< (const dynamic_matrix_const_iterator& other) const noexcept { return _ptr < other._ptr; }
		bool operator> (const dynamic_matrix_const_iterator& other) const noexcept { return other._ptr < _ptr; }
		bool operator<=(const dynamic_matrix_const_iterator& other) const noexcept { return !(*this > other); }
		bool operator>=(const dynamic_matrix_const_iterator& other) const noexcept { return !(*this < other); }

		operator const _TYPE* () const noexcept { return _ptr; }
		const _TYPE* unwrap() const noexcept { return _ptr; }

		constexpr uint32_t step() const noexcept { return 1; }
		ComplementIter complIter() const noexcept { return ComplementIter(_ptr, _rows, _columns); }
		dynamic_matrix_const_iterator toRow(const unsigned int row) const noexcept { return dynamic_matrix_const_iterator(_ptr + (row * _columns), _rows, _columns); }
		dynamic_matrix_const_iterator toColumn(const unsigned int column) const noexcept { return dynamic_matrix_const_iterator(_ptr + column, _rows, _columns); }
		dynamic_matrix_const_iterator toEnd() const noexcept { return dynamic_matrix_const_iterator(_ptr + _rows * _columns, _rows, _columns); }
		size_t GetRowSize() const noexcept { return _rows; }
		size_t GetColumnSize() const noexcept { return _columns; }

		const _TYPE* operator->() const noexcept { return _ptr; }
		const _TYPE& operator[](const unsigned int index) const { return *(_ptr + index); }
		const _TYPE& operator*() const { return *_ptr; }

	private:
		const _TYPE* _ptr;
		const size_t _rows;
		const size_t _columns;
	};

	template<typename MATRIX_TYPE>
	struct dynamic_matrix_column_iterator
	{
		using _TYPE = typename MATRIX_TYPE::ElemType;
		using ComplementIter = typename MATRIX_TYPE::iterator;

		dynamic_matrix_column_iterator() noexcept = default;
		dynamic_matrix_column_iterator(const dynamic_matrix_column_iterator&) noexcept = default;
		dynamic_matrix_column_iterator(_TYPE* const ptr, const size_t rows, const size_t columns) noexcept :_ptr(ptr), _rows(rows), _columns(columns) {}

		dynamic_matrix_column_iterator& operator= (const dynamic_matrix_column_iterator&) noexcept = default;
		dynamic_matrix_column_iterator& operator++()    noexcept { return (_ptr += _columns, *this); }
		dynamic_matrix_column_iterator  operator++(int) noexcept { return (++*this, *this - 1); }
		dynamic_matrix_column_iterator& operator--()    noexcept { return (_ptr -= _columns, *this); }
		dynamic_matrix_column_iterator  operator--(int) noexcept { return (--*this, *this + 1); }

		dynamic_matrix_column_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += (offset * _columns), *this); }
		dynamic_matrix_column_iterator  operator+ (const uintptr_t offset) const noexcept { return dynamic_matrix_column_iterator(_ptr + (offset * _columns), _rows, _columns); }
		dynamic_matrix_column_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= (offset * _columns), *this); }
		dynamic_matrix_column_iterator  operator- (const uintptr_t offset) const noexcept { return dynamic_matrix_column_iterator(_ptr - (offset * _columns), _rows, _columns); }

		uintptr_t operator-(const dynamic_matrix_column_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		bool operator==(const dynamic_matrix_column_iterator& other) const noexcept { return _ptr == other._ptr; }
		bool operator!=(const dynamic_matrix_column_iterator& other) const noexcept { return !(*this == other); }
		bool operator< (const dynamic_matrix_column_iterator& other) const noexcept { return _ptr < other._ptr; }
		bool operator> (const dynamic_matrix_column_iterator& other) const noexcept { return other._ptr < _ptr; }
		bool operator<=(const dynamic_matrix_column_iterator& other) const noexcept { return !(*this > other); }
		bool operator>=(const dynamic_matrix_column_iterator& other) const noexcept { return !(*this < other); }

		operator _TYPE* () const noexcept { return _ptr; }
		_TYPE* unwrap() const noexcept { return _ptr; }

		uint32_t step() const noexcept { return _columns; }
		ComplementIter complIter() const noexcept { return ComplementIter(_ptr, _rows, _columns); }
		dynamic_matrix_column_iterator toRow(const unsigned int row) const noexcept { return dynamic_matrix_column_iterator(_ptr + (row * _columns), _rows, _columns); }
		dynamic_matrix_column_iterator toColumn(const unsigned int column) const noexcept { return dynamic_matrix_column_iterator(_ptr + column, _rows, _columns); }
		dynamic_matrix_column_iterator toEnd() const noexcept { return dynamic_matrix_column_iterator(_ptr + _rows * _columns, _rows, _columns); }
		size_t GetRowSize() const noexcept { return _rows; }
		size_t GetColumnSize() const noexcept { return _columns; }

		_TYPE* operator->() noexcept { return _ptr; }
		_TYPE& operator[](const unsigned int index) { return *(_ptr + (index * _columns)); }
		_TYPE& operator*() { return *_ptr; }

	private:
		_TYPE* _ptr;
		const size_t _rows;
		const size_t _columns;
	};

	template<typename MATRIX_TYPE>
	struct dynamic_matrix_column_const_iterator
	{
		using _TYPE = typename MATRIX_TYPE::ElemType;
		using ComplementIter = typename MATRIX_TYPE::column_iterator;

		dynamic_matrix_column_const_iterator() noexcept = default;
		dynamic_matrix_column_const_iterator(const dynamic_matrix_column_const_iterator&) noexcept = default;
		dynamic_matrix_column_const_iterator(const _TYPE* const ptr, const size_t rows, const size_t columns) noexcept :_ptr(ptr), _rows(rows), _columns(columns) {}

		dynamic_matrix_column_const_iterator& operator=(const dynamic_matrix_column_const_iterator&) noexcept = default;
		dynamic_matrix_column_const_iterator& operator++()    noexcept { return (_ptr += _columns, *this); }
		dynamic_matrix_column_const_iterator  operator++(int) noexcept { return (++*this, *this - 1); }
		dynamic_matrix_column_const_iterator& operator--()    noexcept { return (_ptr -= _columns, *this); }
		dynamic_matrix_column_const_iterator  operator--(int) noexcept { return (--*this, *this + 1); }

		dynamic_matrix_column_const_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += (offset * _columns), *this); }
		dynamic_matrix_column_const_iterator  operator+ (const uintptr_t offset) const noexcept { return dynamic_matrix_column_const_iterator(_ptr + (offset * _columns), _rows, _columns); }
		dynamic_matrix_column_const_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= (offset * _columns), *this); }
		dynamic_matrix_column_const_iterator  operator- (const uintptr_t offset) const noexcept { return dynamic_matrix_column_const_iterator(_ptr - (offset * _columns), _rows, _columns); }

		constexpr uintptr_t operator-(const dynamic_matrix_column_const_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		bool operator==(const dynamic_matrix_column_const_iterator& other) const noexcept { return _ptr == other._ptr; }
		bool operator!=(const dynamic_matrix_column_const_iterator& other) const noexcept { return !(*this == other); }
		bool operator< (const dynamic_matrix_column_const_iterator& other) const noexcept { return _ptr < other._ptr; }
		bool operator> (const dynamic_matrix_column_const_iterator& other) const noexcept { return other._ptr < _ptr; }
		bool operator>=(const dynamic_matrix_column_const_iterator& other) const noexcept { return !(*this < other); }
		bool operator<=(const dynamic_matrix_column_const_iterator& other) const noexcept { return !(*this > other); }

		operator const _TYPE* () const noexcept { return _ptr; }
		const _TYPE* unwrap() const noexcept { return _ptr; }

		uint32_t step() const noexcept { return _columns; }
		ComplementIter complIter() const noexcept { return ComplementIter(_ptr, _rows, _columns); }
		dynamic_matrix_column_const_iterator toRow(const unsigned int row) const noexcept { return dynamic_matrix_column_const_iterator(_ptr + (row * _columns), _rows, _columns); }
		dynamic_matrix_column_const_iterator toColumn(const unsigned int column) const noexcept { return dynamic_matrix_column_const_iterator(_ptr + column, _rows, _columns); }
		dynamic_matrix_column_const_iterator toEnd() const noexcept { return dynamic_matrix_column_const_iterator(_ptr + _rows * _columns, _rows, _columns); }
		size_t GetRowSize() const noexcept { return _rows; }
		size_t GetColumnSize() const noexcept { return _columns; }

		const _TYPE* operator->() const noexcept { return _ptr; }
		const _TYPE& operator[](const unsigned int index) const { return *(_ptr + (index * _columns)); }
		const _TYPE& operator*() const { return *_ptr; }

	private:
		const _TYPE* _ptr;
		const size_t _rows;
		const size_t _columns;
	};

	using mat_i = dynamic_matrix<int>;
	using mat_f = dynamic_matrix<float>;
}

#include "dynamic_matrix.ipp"
#include "matrix_operations.h"

#endif /* stm_dynamic_matrix_h */