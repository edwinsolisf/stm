#ifndef stm_dynamic_vector_h
#define stm_dynamic_vector_h

#include "debug.h"

namespace stm
{
	template<typename _TYPE, unsigned int _DIM>
	class vector;

	template<typename _TYPE, unsigned int _DIM, typename Itr>
	class vector_view;

	template<typename _VECTOR_TYPE>
	struct dynamic_vector_iterator;

	template<typename _VECTOR_TYPE>
	struct dynamic_vector_const_iterator;

	template<typename _T, typename Itr>
	class dynamic_vector_view;

	template<typename _T>
	class dynamic_vector
	{
	public:
		using ElemType = _T;
		using iterator = dynamic_vector_iterator<dynamic_vector<_T>>;
		using const_iterator = dynamic_vector_const_iterator<dynamic_vector<_T>>;

		//Constructors
		dynamic_vector(const unsigned int dimensions);
		dynamic_vector(const unsigned int dimensions, const _T* const data);
		dynamic_vector(const unsigned int dimensions, const _T& value);
		dynamic_vector(const unsigned int dimensions, std::initializer_list<_T> list);
		dynamic_vector(const dynamic_vector& other);
		dynamic_vector(dynamic_vector&& other) noexcept;
		dynamic_vector(_T*& data, const unsigned int dimensions);
		template <typename Itr>
		dynamic_vector(const dynamic_vector_view<_T, Itr>&);

		template<unsigned int dimensions>
		explicit dynamic_vector(const vector<_T, dimensions>& static_vector);

		template<unsigned int dimensions, typename Itr>
		explicit dynamic_vector(const vector_view<_T, dimensions, Itr>&);

		//Destructors
		~dynamic_vector();

		//Assignment operators
		dynamic_vector& operator=(const dynamic_vector& other);
		dynamic_vector& operator=(dynamic_vector&& other) noexcept;
		template <typename Itr>
		dynamic_vector& operator=(const dynamic_vector_view<_T, Itr>& other);

		//Unary operators
		dynamic_vector   operator+() const& noexcept { return *this; }
		dynamic_vector&& operator+() &&     noexcept { return std::move(*this); }

		dynamic_vector operator-() const&;
		dynamic_vector&& operator-() &&;

		_T&       operator[](const unsigned int index)       noexcept { stm_assert(index < _dimensions); return _data[index]; }
		const _T& operator[](const unsigned int index) const noexcept { stm_assert(index < _dimensions); return _data[index]; }

		//Data Manipulation Functions
		bool Resize(const unsigned int dimensions);

		dynamic_vector&  SetAll(const _T& value) &  noexcept;
		dynamic_vector&& SetAll(const _T& value) && noexcept;

		template <typename _FUNCTION>
		dynamic_vector&  ApplyToVector(_FUNCTION&& func) &;
		
		template <typename _FUNCTION>
		dynamic_vector&& ApplyToVector(_FUNCTION&& func) &&;

		//Binary Operators
		dynamic_vector   operator+(const dynamic_vector& other) const&;
		dynamic_vector&& operator+(const dynamic_vector& other) &&;
		dynamic_vector&& operator+(dynamic_vector&& other) const&;
		dynamic_vector&& operator+(dynamic_vector&& other) &&;

		dynamic_vector   operator-(const dynamic_vector& other) const&;
		dynamic_vector&& operator-(const dynamic_vector& other) &&;
		dynamic_vector&& operator-(dynamic_vector&& other) const&;
		dynamic_vector&& operator-(dynamic_vector&& other)&&;

		dynamic_vector   operator*(const dynamic_vector& other) const&;
		dynamic_vector&& operator*(const dynamic_vector& other) &&;
		dynamic_vector&& operator*(dynamic_vector&& other) const&;
		dynamic_vector&& operator*(dynamic_vector&& other) &&;

		dynamic_vector   operator/(const dynamic_vector& other) const&;
		dynamic_vector&& operator/(const dynamic_vector& other) &&;
		dynamic_vector&& operator/(dynamic_vector&& other) const&;
		dynamic_vector&& operator/(dynamic_vector&& other) &&;
		
		template <typename Itr>
		dynamic_vector   operator+(const dynamic_vector_view<_T, Itr>& value) const&;
		template <typename Itr>
		dynamic_vector&& operator+(const dynamic_vector_view<_T, Itr>& value) &&;
		template <typename Itr>
		dynamic_vector   operator-(const dynamic_vector_view<_T, Itr>& value) const&;
		template <typename Itr>
		dynamic_vector&& operator-(const dynamic_vector_view<_T, Itr>& value) &&;
		template <typename Itr>
		dynamic_vector   operator*(const dynamic_vector_view<_T, Itr>& value) const&;
		template <typename Itr>
		dynamic_vector&& operator*(const dynamic_vector_view<_T, Itr>& value) &&;
		template <typename Itr>
		dynamic_vector   operator/(const dynamic_vector_view<_T, Itr>& value) const&;
		template <typename Itr>
		dynamic_vector&& operator/(const dynamic_vector_view<_T, Itr>& value) &&;

		template<unsigned int dimensions>
		vector<_T, dimensions> operator+(const vector<_T, dimensions>& static_vector) const noexcept;
		template<unsigned int dimensions>
		vector<_T, dimensions> operator-(const vector<_T, dimensions>& static_vector) const noexcept;
		template<unsigned int dimensions>
		vector<_T, dimensions> operator*(const vector<_T, dimensions>& static_vector) const noexcept;
		template<unsigned int dimensions>
		vector<_T, dimensions> operator/(const vector<_T, dimensions>& static_vector) const noexcept;

		template<unsigned int _DIM, typename Itr>
		vector<_T, _DIM> operator+(const vector_view<_T, _DIM, Itr>& other) const noexcept;
		template<unsigned int _DIM, typename Itr>
		vector<_T, _DIM> operator-(const vector_view<_T, _DIM, Itr>& other) const noexcept;
		template<unsigned int _DIM, typename Itr>
		vector<_T, _DIM> operator*(const vector_view<_T, _DIM, Itr>& other) const noexcept;
		template<unsigned int _DIM, typename Itr>
		vector<_T, _DIM> operator/(const vector_view<_T, _DIM, Itr>& other) const noexcept;

		dynamic_vector   operator+(const _T& value) const&;
		dynamic_vector&& operator+(const _T& value) &&;

		dynamic_vector   operator-(const _T& value) const&;
		dynamic_vector&& operator-(const _T& value) &&;

		dynamic_vector   operator*(const _T& value) const&;
		dynamic_vector&& operator*(const _T& value) &&;

		dynamic_vector   operator/(const _T& value) const&;
		dynamic_vector&& operator/(const _T& value) &&;


		//Binary Assigment Operators
		dynamic_vector& operator+=(const dynamic_vector& other);
		dynamic_vector& operator-=(const dynamic_vector& other);
		dynamic_vector& operator*=(const dynamic_vector& other);
		dynamic_vector& operator/=(const dynamic_vector& other);

		template<typename Itr>
		dynamic_vector& operator+=(const dynamic_vector_view<_T, Itr>& other);
		template<typename Itr>
		dynamic_vector& operator-=(const dynamic_vector_view<_T, Itr>& other);
		template<typename Itr>
		dynamic_vector& operator*=(const dynamic_vector_view<_T, Itr>& other);
		template<typename Itr>
		dynamic_vector& operator/=(const dynamic_vector_view<_T, Itr>& other);

		template<unsigned int dimensions>
		dynamic_vector& operator+=(const vector<_T, dimensions>& static_vector) noexcept;

		template<unsigned int dimensions>
		dynamic_vector& operator-=(const vector<_T, dimensions>& static_vector) noexcept;

		template<unsigned int dimensions>
		dynamic_vector& operator*=(const vector<_T, dimensions>& static_vector) noexcept;

		template<unsigned int dimensions>
		dynamic_vector& operator/=(const vector<_T, dimensions>& static_vector) noexcept;

		template <unsigned int _DIM, typename Itr>
		dynamic_vector& operator+=(const vector_view<_T, _DIM, Itr>& other) noexcept;
		template <unsigned int _DIM, typename Itr>
		dynamic_vector& operator-=(const vector_view<_T, _DIM, Itr>& other) noexcept;
		template <unsigned int _DIM, typename Itr>
		dynamic_vector& operator*=(const vector_view<_T, _DIM, Itr>& other) noexcept;
		template <unsigned int _DIM, typename Itr>
		dynamic_vector& operator/=(const vector_view<_T, _DIM, Itr>& other) noexcept;

		dynamic_vector& operator+=(const _T& value) noexcept;
		dynamic_vector& operator-=(const _T& value) noexcept;
		dynamic_vector& operator*=(const _T& value) noexcept;
		dynamic_vector& operator/=(const _T& value) noexcept;

		//Casting
		template<typename O_TYPE>
		dynamic_vector<O_TYPE> Cast() const;

		//Data Info Functions
		_T*       GetData()       noexcept { return _data; }
		const _T* GetData() const noexcept { return _data; }
		
		_T*& 			 GetRefToPtrData()       noexcept { return _data; }
		const _T* const& GetRefToPtrData() const noexcept { return _data; }

		unsigned int GetSize() const noexcept { return _dimensions; }

		dynamic_vector_view<_T, const_iterator> GetView() const { return dynamic_vector_view<_T, const_iterator>(cbegin(), cend()); }
		
		//Iterators
		iterator begin() noexcept { return iterator(_data); }
		iterator end()   noexcept { return iterator(_data + _dimensions); }
		
		//Unwrapped iterators
		auto ubegin() noexcept { return begin().unwrap(); }
		auto uend()   noexcept { return end().unwrap(); }

		//Const iterators
		const_iterator cbegin() const noexcept { return const_iterator(_data); }
		const_iterator cend()   const noexcept { return const_iterator(_data + _dimensions); }

		//Unwrapped const iterators
		auto ucbegin() const noexcept { return cbegin().unwrap(); }
		auto ucend()   const noexcept { return cend().unwrap(); }

		//Math Functions
		_T Magnitude() const { return sqrt(DotProduct(*this)); }

		dynamic_vector UnitVector() const& { return (*this) / Magnitude(); }
		dynamic_vector&& UnitVector()  &&  { return std::move((*this) / Magnitude()); }

		_T DotProduct(const dynamic_vector& other) const;

		template<unsigned int dimensions>
		_T DotProduct(const vector<_T, dimensions>& other) const noexcept;

		vector<_T, 3> CrossProduct(const dynamic_vector<_T>& vec)
		{ 
			stm_assert(_dimensions == 3 && vec.GetSize() == 3);
			return vector<_T, 3>((_data[1] * vec[2]) - (_data[2] * vec[1]),
								 (_data[2] * vec[0]) - (_data[0] * vec[2]),
								 (_data[0] * vec[1]) - (_data[1] * vec[0]));
		}

		vector<_T, 3> CrossProduct(const vector<_T, 3>& vec) noexcept
		{
			stm_assert(_dimensions == 3 && vec.GetSize() == 3);
			return vector<_T, 3>((_data[1] * vec[2]) - (_data[2] * vec[1]),
							     (_data[2] * vec[0]) - (_data[0] * vec[2]),
								 (_data[0] * vec[1]) - (_data[1] * vec[0]));
		}

	private:
		_T* _data;
		unsigned int _dimensions;
	};

	template<typename _VECTOR_TYPE>
	struct dynamic_vector_iterator
	{
		using _TYPE = typename std::remove_const<typename _VECTOR_TYPE::ElemType>::type;
		dynamic_vector_iterator() noexcept = default;
		dynamic_vector_iterator(const dynamic_vector_iterator&) noexcept = default;
		dynamic_vector_iterator(_TYPE* const ptr) noexcept :_ptr(ptr) {}

		dynamic_vector_iterator& operator= (const dynamic_vector_iterator&) noexcept = default;
		dynamic_vector_iterator& operator++()    noexcept { return (++_ptr, *this); }
		dynamic_vector_iterator  operator++(int) noexcept { return (++*this, *this - 1); }
		dynamic_vector_iterator& operator--()    noexcept { return (--_ptr, *this); }
		dynamic_vector_iterator  operator--(int) noexcept { return (--*this, *this + 1); }

		dynamic_vector_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += offset, *this); }
		dynamic_vector_iterator  operator+ (const uintptr_t offset) const noexcept { return dynamic_vector_iterator(_ptr + offset); }
		dynamic_vector_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= offset, *this); }
		dynamic_vector_iterator  operator- (const uintptr_t offset) const noexcept { return dynamic_vector_iterator(_ptr - offset); }

		uintptr_t operator-(const dynamic_vector_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		bool operator==(const dynamic_vector_iterator& other) const noexcept { return _ptr == other._ptr; }
		bool operator!=(const dynamic_vector_iterator& other) const noexcept { return !(*this == other); }
		bool operator< (const dynamic_vector_iterator& other) const noexcept { return _ptr < other._ptr; }
		bool operator> (const dynamic_vector_iterator& other) const noexcept { return other._ptr < _ptr; }
		bool operator<=(const dynamic_vector_iterator& other) const noexcept { return !(*this > other); }
		bool operator>=(const dynamic_vector_iterator& other) const noexcept { return !(*this < other); }

		operator _TYPE* () noexcept { return _ptr; }
		_TYPE* unwrap() const noexcept { return _ptr; }

		_TYPE* operator->() noexcept { return _ptr; }
		_TYPE& operator[](const unsigned int index) { return *(_ptr + index); }
		_TYPE& operator*() { return *_ptr; }

	private:
		_TYPE* _ptr;
	};

	template<typename _VECTOR_TYPE>
	struct dynamic_vector_const_iterator
	{
		using _TYPE = typename std::remove_const<typename _VECTOR_TYPE::ElemType>::type;
		
		dynamic_vector_const_iterator() noexcept = default;
		dynamic_vector_const_iterator(const dynamic_vector_const_iterator&) noexcept = default;
		dynamic_vector_const_iterator(const _TYPE* const ptr) noexcept :_ptr(ptr) {}

		dynamic_vector_const_iterator& operator=(const dynamic_vector_const_iterator&) noexcept = default;
		dynamic_vector_const_iterator& operator++()    noexcept { return (++_ptr, *this); }
		dynamic_vector_const_iterator  operator++(int) noexcept { return (++*this, *this - 1); }
		dynamic_vector_const_iterator& operator--()    noexcept { return (--_ptr, *this); }
		dynamic_vector_const_iterator  operator--(int) noexcept { return (--*this, *this + 1); }

		dynamic_vector_const_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += offset, *this); }
		dynamic_vector_const_iterator  operator+ (const uintptr_t offset) const noexcept { return dynamic_vector_const_iterator(_ptr + offset); }
		dynamic_vector_const_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= offset, *this); }
		dynamic_vector_const_iterator  operator- (const uintptr_t offset) const noexcept { return dynamic_vector_const_iterator(_ptr - offset); }

		constexpr uintptr_t operator-(const dynamic_vector_const_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		bool operator==(const dynamic_vector_const_iterator& other) const noexcept { return _ptr == other._ptr; }
		bool operator!=(const dynamic_vector_const_iterator& other) const noexcept { return !(*this == other); }
		bool operator< (const dynamic_vector_const_iterator& other) const noexcept { return _ptr < other._ptr; }
		bool operator> (const dynamic_vector_const_iterator& other) const noexcept { return other._ptr < _ptr; }
		bool operator<=(const dynamic_vector_const_iterator& other) const noexcept { return !(*this > other); }
		bool operator>=(const dynamic_vector_const_iterator& other) const noexcept { return !(*this < other); }

		operator const _TYPE* () const noexcept { return _ptr; }
		const _TYPE* unwrap() const noexcept { return _ptr; }

		const _TYPE* operator->() const noexcept { return _ptr; }
		const _TYPE& operator[](unsigned int index) const { return *(_ptr + index); }
		const _TYPE& operator*() const { return *_ptr; }

	private:
		const _TYPE* _ptr;
	};

	template <typename _TYPE>
	inline dynamic_vector<_TYPE> normalize(dynamic_vector<_TYPE>&& vec) { return std::move(vec.UnitVector()); }

	typedef dynamic_vector<float> vec_f;
	typedef dynamic_vector<int> vec_i;
}

#include "dynamic_vector.ipp"

#endif /* stm_dynamic_vector_h */
