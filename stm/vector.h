#ifndef stm_vector_h
#define stm_vector_h

#include <cmath>
#include "debug.h"

namespace stm
{
	template<typename _TYPE>
	class dynamic_vector;

	template<typename _TYPE, typename Itr>
	class dynamic_vector_view;

	template<typename _VECTOR_TYPE>
	struct vector_iterator;

	template<typename _VECTOR_TYPE>
	struct vector_const_iterator;

	template<typename _TYPE, unsigned int _DIM>
	struct constexpr_vector;

	template<typename _TYPE, unsigned int _DIM, typename Itr>
	class vector_view;

	template<typename _TYPE, unsigned int _DIM>
	class vector
	{
	public:
		using ElemType = _TYPE;
		using iterator = vector_iterator<vector<_TYPE, _DIM>>;
		using const_iterator = vector_const_iterator<vector<_TYPE, _DIM>>;

		//Constructors
		constexpr vector() noexcept = default;
		constexpr vector(const vector& other) noexcept = default;
		constexpr vector(vector&&) noexcept = default;
		constexpr vector(const constexpr_vector<_TYPE, _DIM>& vector) noexcept;
		template <typename Itr>
		vector(const vector_view<_TYPE, _DIM, Itr>& vector_view) noexcept;
		template <typename Itr>
		vector(const Itr begin, const Itr end) noexcept;
		vector(const _TYPE& value) noexcept;
		vector(const _TYPE (&data)[_DIM]) noexcept;
		vector(const _TYPE* const data, const unsigned int offset) noexcept;
		vector(std::initializer_list<_TYPE> list) noexcept;
		~vector() = default;

		constexpr vector& operator=(const vector&) noexcept = default;
		constexpr vector& operator=(vector&&)      noexcept = default;
		vector& operator=(const dynamic_vector<_TYPE>& other);
		template <typename Itr>
		vector& operator=(const vector_view<_TYPE, _DIM, Itr>& other) noexcept;
		template <typename Itr>
		vector& operator=(const dynamic_vector_view<_TYPE, Itr>& other);

		//Unary Operators
		constexpr vector operator+() const noexcept { return *this; }

		vector operator-() const noexcept;

		constexpr _TYPE&       operator[](const unsigned int index)       noexcept { stm_assert(index < _DIM); return _data[index]; }
		constexpr const _TYPE& operator[](const unsigned int index) const noexcept { stm_assert(index < _DIM); return _data[index]; }

		//Casting
		template<unsigned int DIM>
		constexpr vector<_TYPE, DIM> ToVector() const noexcept {
			static_assert(DIM <= _DIM, "New vector is of greater dimensions");
			return DIM == _DIM ? *this : vector<_TYPE, DIM>(_data);
		}

		template<typename O_TYPE>
		vector<O_TYPE, _DIM> Cast() const noexcept;

		//Data manipulation functions
		template <typename _FUNCTION>
		vector& ApplyToVector(_FUNCTION&& func);

		vector& SetAll(const _TYPE& value) noexcept;

		//Binary Operators
		vector operator+(const vector& other) const noexcept;
		vector operator-(const vector& other) const noexcept;
		vector operator*(const vector& other) const noexcept;
		vector operator/(const vector& other) const noexcept;

		vector operator+(const _TYPE& other) const noexcept;
		vector operator-(const _TYPE& other) const noexcept;
		vector operator*(const _TYPE& other) const noexcept;
		vector operator/(const _TYPE& other) const noexcept;

		template <typename Itr>
		vector operator+(const vector_view<_TYPE, _DIM, Itr>& other) const noexcept;
		template <typename Itr>
		vector operator-(const vector_view<_TYPE, _DIM, Itr>& other) const noexcept;
		template <typename Itr>
		vector operator*(const vector_view<_TYPE, _DIM, Itr>& other) const noexcept;
		template <typename Itr>
		vector operator/(const vector_view<_TYPE, _DIM, Itr>& other) const noexcept;

		template <typename Itr>
		vector operator+(const dynamic_vector_view<_TYPE, Itr>& other) const;
		template <typename Itr>
		vector operator-(const dynamic_vector_view<_TYPE, Itr>& other) const;
		template <typename Itr>
		vector operator*(const dynamic_vector_view<_TYPE, Itr>& other) const;
		template <typename Itr>
		vector operator/(const dynamic_vector_view<_TYPE, Itr>& other) const;

		vector operator+(const dynamic_vector<_TYPE>& other) const;
		vector operator-(const dynamic_vector<_TYPE>& other) const;
		vector operator*(const dynamic_vector<_TYPE>& other) const;
		vector operator/(const dynamic_vector<_TYPE>& other) const;

		//Binary assigment operators
		vector& operator+=(const vector& other) noexcept;
		vector& operator-=(const vector& other) noexcept;
		vector& operator*=(const vector& other) noexcept;
		vector& operator/=(const vector& other) noexcept;

		vector& operator+=(const _TYPE& other) noexcept;
		vector& operator-=(const _TYPE& other) noexcept;
		vector& operator*=(const _TYPE& other) noexcept;
		vector& operator/=(const _TYPE& other) noexcept;

		template <typename Itr>
		vector& operator+=(const vector_view<_TYPE, _DIM, Itr>& other) noexcept;
		template <typename Itr>
		vector& operator-=(const vector_view<_TYPE, _DIM, Itr>& other) noexcept;
		template <typename Itr>
		vector& operator*=(const vector_view<_TYPE, _DIM, Itr>& other) noexcept;
		template <typename Itr>
		vector& operator/=(const vector_view<_TYPE, _DIM, Itr>& other) noexcept;

		template <typename Itr>
		vector& operator+=(const dynamic_vector_view<_TYPE, Itr>& other);
		template <typename Itr>
		vector& operator-=(const dynamic_vector_view<_TYPE, Itr>& other);
		template <typename Itr>
		vector& operator*=(const dynamic_vector_view<_TYPE, Itr>& other);
		template <typename Itr>
		vector& operator/=(const dynamic_vector_view<_TYPE, Itr>& other);

		vector& operator+=(const dynamic_vector<_TYPE>& other);
		vector& operator-=(const dynamic_vector<_TYPE>& other);
		vector& operator*=(const dynamic_vector<_TYPE>& other);
		vector& operator/=(const dynamic_vector<_TYPE>& other);

		//Data Info Functions
		static constexpr unsigned int container_size() noexcept { return _DIM; }

		constexpr _TYPE*       GetData()       noexcept { return _data; }
		constexpr const _TYPE* GetData() const noexcept { return _data; }
		constexpr auto&       GetArray()       noexcept { return _data; }
		constexpr const auto& GetArray() const noexcept { return _data; }
		constexpr unsigned int GetSize() const noexcept { return container_size(); }
		
		//Iterators
		
		constexpr iterator begin() noexcept { return iterator(_data); }
		constexpr iterator end()   noexcept { return iterator(_data + _DIM); }

		//Unwrapped Iterators (u stands for unwrapped)
		constexpr auto ubegin() noexcept { return begin().unwrap(); }
		constexpr auto uend()   noexcept { return end().unwrap(); }

		//Const iterators
		constexpr const_iterator cbegin() const noexcept { return const_iterator(_data); }
		constexpr const_iterator cend()   const noexcept { return const_iterator(_data + _DIM); }

		//Unwrapped const interators
		constexpr auto ucbegin() const noexcept { return cbegin().unwrap(); }
		constexpr auto ucend()   const noexcept { return cend().unwrap(); }

		constexpr vector_view<_TYPE, _DIM, const_iterator> GetView() const noexcept
		{ return vector_view<_TYPE, _DIM, const_iterator>(*this); }

		//Math functions
		_TYPE Magnitude() const noexcept
		{
			return std::sqrt(DotProduct(*this));
		}

		vector UnitVector() const noexcept
		{
			return (*this) / Magnitude();
		}

		_TYPE DotProduct(const vector& other) const noexcept;
		_TYPE DotProduct(const dynamic_vector<_TYPE>& other) const;
		template <typename Itr>
		_TYPE DotProduct(const vector_view<_TYPE, _DIM, Itr>& other) const noexcept;
		template <typename Itr>
		_TYPE DotProduct(const dynamic_vector_view<_TYPE, Itr>& other) const;

	private:
		_TYPE _data[_DIM] {};

	};

	template<typename _VECTOR_TYPE>
	struct vector_iterator
	{
		using _TYPE = typename std::remove_const<typename _VECTOR_TYPE::ElemType>::type;

		constexpr vector_iterator() noexcept = default;
		constexpr vector_iterator(const vector_iterator&) noexcept = default;
		constexpr vector_iterator(_TYPE* const ptr) noexcept :_ptr(ptr) {}

		constexpr vector_iterator& operator= (const vector_iterator&) noexcept = default;
		constexpr vector_iterator& operator++()    noexcept { return (++_ptr, *this); }
		constexpr vector_iterator  operator++(int) noexcept { return (++*this, *this - 1); }
		constexpr vector_iterator& operator--()    noexcept { return (--_ptr, *this); }
		constexpr vector_iterator  operator--(int) noexcept { return (--*this, *this + 1); }

		constexpr vector_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += offset, *this); }
		constexpr vector_iterator  operator+ (const uintptr_t offset) const noexcept { return vector_iterator(_ptr + offset); }
		constexpr vector_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= offset, *this); }
		constexpr vector_iterator  operator- (const uintptr_t offset) const noexcept { return vector_iterator(_ptr - offset); }

		constexpr uintptr_t operator-(const vector_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		constexpr bool operator==(const vector_iterator& other) const noexcept { return _ptr == other._ptr; }
		constexpr bool operator!=(const vector_iterator& other) const noexcept { return !(*this == other); }
		constexpr bool operator< (const vector_iterator& other) const noexcept { return _ptr < other._ptr; }
		constexpr bool operator> (const vector_iterator& other) const noexcept { return other._ptr < _ptr; }
		constexpr bool operator<=(const vector_iterator& other) const noexcept { return !(*this > other); }
		constexpr bool operator>=(const vector_iterator& other) const noexcept { return !(*this < other); }

		constexpr operator _TYPE* () noexcept { return _ptr; }
		constexpr _TYPE* unwrap() const noexcept { return _ptr; }

		constexpr _TYPE* operator->() noexcept { return _ptr; }
		constexpr _TYPE& operator[](const unsigned int index) { return *(_ptr + index); }
		constexpr _TYPE& operator*() { return *_ptr; }

	private:
		_TYPE* _ptr;
	};

	template<typename _VECTOR_TYPE>
	struct vector_const_iterator
	{
		using _TYPE = typename std::remove_const<typename _VECTOR_TYPE::ElemType>::type;
		
		constexpr vector_const_iterator() noexcept = default;
		constexpr vector_const_iterator(const vector_const_iterator&) noexcept = default;
		constexpr vector_const_iterator(const _TYPE* const ptr) noexcept :_ptr(ptr) {}

		constexpr vector_const_iterator& operator= (const vector_const_iterator&) noexcept = default;
		constexpr vector_const_iterator& operator++()    noexcept { return (++_ptr, *this); }
		constexpr vector_const_iterator  operator++(int) noexcept { return (++*this, *this - 1); }
		constexpr vector_const_iterator& operator--()    noexcept { return (--_ptr, *this); }
		constexpr vector_const_iterator  operator--(int) noexcept { return (--*this, *this + 1); }

		constexpr vector_const_iterator& operator+=(const uintptr_t offset)       noexcept { return (_ptr += offset, *this); }
		constexpr vector_const_iterator  operator+ (const uintptr_t offset) const noexcept { return vector_const_iterator(_ptr + offset); }
		constexpr vector_const_iterator& operator-=(const uintptr_t offset)       noexcept { return (_ptr -= offset, *this); }
		constexpr vector_const_iterator  operator- (const uintptr_t offset) const noexcept { return vector_const_iterator(_ptr - offset); }

		constexpr uintptr_t operator-(const vector_const_iterator& other) const noexcept { return (uintptr_t)_ptr - (uintptr_t)other._ptr; }

		constexpr bool operator==(const vector_const_iterator& other) const noexcept { return _ptr == other._ptr; }
		constexpr bool operator!=(const vector_const_iterator& other) const noexcept { return !(*this == other); }
		constexpr bool operator< (const vector_const_iterator& other) const noexcept { return _ptr < other._ptr; }
		constexpr bool operator> (const vector_const_iterator& other) const noexcept { return other._ptr < _ptr; }
		constexpr bool operator<=(const vector_const_iterator& other) const noexcept { return !(*this > other); }
		constexpr bool operator>=(const vector_const_iterator& other) const noexcept { return !(*this < other); }

		constexpr operator const _TYPE* () const noexcept { return _ptr; }
		constexpr const _TYPE* unwrap() const noexcept { return _ptr; }

		constexpr const _TYPE* operator->() const noexcept { return _ptr; }
		constexpr const _TYPE& operator[](unsigned int index) const { return *(_ptr + index); }
		constexpr const _TYPE& operator*() const { return *_ptr; }

	private:
		const _TYPE* _ptr;
	};

	template <typename _TYPE, unsigned int _DIM>
	struct constexpr_vector
	{
		constexpr constexpr_vector() noexcept = default;
		constexpr constexpr_vector(const _TYPE& value) noexcept;
		constexpr constexpr_vector(const _TYPE(&data)[_DIM]) noexcept;
		constexpr constexpr_vector(const constexpr_vector&) noexcept = default;
		//template <typename Itr>
		//constexpr constexpr_vector(const vector_view<_TYPE, _DIM, Itr>& view) noexcept;
		//constexpr constexpr_vector(std::initializer_list<_TYPE> list) noexcept;
		~constexpr_vector() = default;
		constexpr auto&      GetArray()        noexcept { return _data; }
		constexpr const auto& GetArray() const noexcept { return _data; }
	private:
		_TYPE _data[_DIM] {};
	};

	template<typename _VEC1, typename _VEC2>
	inline auto dotproduct(const _VEC1& vec1, const _VEC2& vec2) -> decltype(vec1.DotProduct(vec2)) { return vec1.DotProduct(vec2); }

	template<typename _VEC1, typename _VEC2>
	inline constexpr vector<typename _VEC1::ElemType, 3> crossproduct(const _VEC1& vec1, const _VEC2& vec2) noexcept
	{
		static_assert(std::is_same<typename _VEC1::ElemType, typename _VEC2::ElemType>{}, "Vectors are of different elemental types");
		return vector<typename _VEC1::ElemType, 3>(
			(vec1[1] * vec2[2]) - (vec1[2] * vec2[1]),
			(vec1[2] * vec2[0]) - (vec1[0] * vec2[2]),
			(vec1[0] * vec2[1]) - (vec1[1] * vec2[0]));
	}

    template<typename _VECTYPE>
    inline auto magnitude(const _VECTYPE& vec) -> decltype(vec.Magnitude()) { return vec.Magnitude(); }

    template<typename _VECTYPE>
    inline auto normalize(const _VECTYPE& vec) -> decltype(vec.UnitVector()) { return vec.UnitVector(); }

	template<typename _VECTYPE>
	auto pow(const _VECTYPE& vec, const unsigned int power) -> decltype(vec * vec);

	template<typename T, typename... Ts>
	inline vector<T, sizeof...(Ts) + 1> make_vector(T val, Ts... vals) noexcept
	{
		return vector<T, sizeof...(Ts) + 1>{ val, vals... };
	}
}

#include "vector.ipp"

#include "vector4.h"
#include "vector3.h"
#include "vector2.h"

#endif /* stm_vector_h */