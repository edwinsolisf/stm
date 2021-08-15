#ifndef stm_vector_2_h
#define stm_vector_2_h

#include "debug.h"
#include <cmath>

namespace stm
{
	template<typename _TYPE, unsigned int _DIM>
	class vector;

	template<typename _TYPE>
	class dynamic_vector;

	template<typename _TYPE, unsigned int _DIM, typename Itr>
	class vector_view;

	template<typename _TYPE, typename Itr>
	class dynamic_vector_view;

	template<typename _VECTOR_TYPE>
	struct vector_iterator;

	template<typename _VECTOR_TYPE>
	struct vector_const_iterator;

	template<typename _TYPE>
	class vector<_TYPE, 2>
	{
	public:
		struct
		{
			union
			{
				_TYPE _data[2] {};
				struct
				{
					_TYPE x, y;
				};
			};
		};
		using ElemType = _TYPE;
		using iterator = vector_iterator<vector<_TYPE, 2>>;
		using const_iterator = vector_const_iterator<vector<_TYPE, 2>>;

		//Constructors
		constexpr vector() noexcept = default;

		constexpr vector(const _TYPE (&data)[2]) noexcept
			:_data(data)
		{
		}

		constexpr vector(const _TYPE* data, const unsigned int offset) noexcept
			: x(data[offset]), y(data[offset + 1])
		{
		}

		constexpr vector(const _TYPE& _x, const _TYPE& _y) noexcept
			:x(_x), y(_y)
		{
		}

		constexpr vector(const _TYPE& value) noexcept
			:x(value), y(value)
		{
		}

		template <typename Itr>
		constexpr vector(const vector_view<_TYPE, 2, Itr>& vector_view) noexcept
			:x(vector_view[0]), y(vector_view[1])
		{
		}

		constexpr vector(const vector&) noexcept = default;
		constexpr vector(vector&&)      noexcept = default;
		~vector() = default;

		//Assigment Operator
		constexpr vector& operator=(const vector&) noexcept = default;
		constexpr vector& operator=(vector&&)      noexcept = default;

		template <typename Itr>
		constexpr vector& operator=(const vector_view<_TYPE, 2, Itr>& other) noexcept
		{
			return (x = other[0], y = other[1], *this);
		}

		template <typename Itr>
		vector& operator=(const dynamic_vector_view<_TYPE, Itr>& other)
		{
			stm_assert(GetSize() == other.GetSize());
			return (x = other[0], y = other[1], *this);
		}

		vector& operator=(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(2 == vec.GetSize());
			return (x = vec[0], y = vec[1], *this);
		}

		//Unary Operators
		constexpr vector operator+() const noexcept
		{
			return *this;
		}

		constexpr vector operator-() const noexcept
		{
			return vector(-x, -y);
		}

		constexpr _TYPE&       operator[](const unsigned int index)       noexcept { stm_assert(index < 2); return _data[index]; }
		constexpr const _TYPE& operator[](const unsigned int index) const noexcept { stm_assert(index < 2); return _data[index]; }

		template<typename O_TYPE>
		constexpr vector<O_TYPE, 2> Cast() const noexcept
		{
			return vector<O_TYPE, 2>((O_TYPE)x, (O_TYPE)y);
		}

		//Data manipulation functions
		template <typename _FUNCTION>
		vector& ApplyToVector(_FUNCTION&& func)
		{
			return (x = func(x), y = func(y), *this);
		}

		vector& SetAll(const _TYPE& value) noexcept
		{
			return (x = value, y = value, *this);
		}

		//Binary Operators
		constexpr vector operator+(const vector& other) const noexcept
		{
			return vector(x + other.x, y + other.y);
		}

		constexpr vector operator-(const vector& other) const noexcept
		{
			return vector(x - other.x, y - other.y);
		}

		constexpr vector operator*(const vector& other) const noexcept
		{
			return vector(x * other.x, y * other.y);
		}

		constexpr vector operator/(const vector& other) const noexcept
		{
			return vector(x / other.x, y / other.y);
		}

		template <typename Itr>
		constexpr vector operator+(const vector_view<_TYPE, 2, Itr>& other) const noexcept
		{
			return vector(*this) += other;
		}

		template <typename Itr>
		constexpr vector operator-(const vector_view<_TYPE, 2, Itr>& other) const noexcept
		{
			return vector(*this) -= other;
		}

		template <typename Itr>
		constexpr vector operator*(const vector_view<_TYPE, 2, Itr>& other) const noexcept
		{
			return vector(*this) *= other;
		}

		template <typename Itr>
		constexpr vector operator/(const vector_view<_TYPE, 2, Itr>& other) const noexcept
		{
			return vector(*this) /= other;
		}

		constexpr vector operator+(const _TYPE& other) const noexcept
		{
			return vector(x + other, y + other);
		}

		constexpr vector operator-(const _TYPE& other) const noexcept
		{
			return vector(x - other, y - other);
		}

		constexpr vector operator*(const _TYPE& other) const noexcept
		{
			return vector(x * other, y * other);
		}

		constexpr vector operator/(const _TYPE& other) const noexcept
		{
			return vector(x / other, y / other);
		}

		vector operator+(const dynamic_vector<_TYPE>& vec) const
		{
			stm_assert(2 == vec.GetSize());
			return vector(x + vec[0], y + vec[1]);
		}

		vector operator-(const dynamic_vector<_TYPE>& vec) const
		{
			stm_assert(2 == vec.GetSize());
			return vector(x - vec[0], y - vec[1]);
		}

		vector operator*(const dynamic_vector<_TYPE>& vec) const
		{
			stm_assert(2 == vec.GetSize());
			return vector(x * vec[0], y * vec[1]);
		}

		vector operator/(const dynamic_vector<_TYPE>& vec) const
		{
			stm_assert(2 == vec.GetSize());
			return vector(x / vec[0], y / vec[1]);
		}
		
		template <typename Itr>
		vector operator+(const dynamic_vector_view<_TYPE, Itr>& other) const
		{
			return vector(*this) += other;
		}

		template <typename Itr>
		vector operator-(const dynamic_vector_view<_TYPE, Itr>& other) const
		{
			return vector(*this) -= other;
		}

		template <typename Itr>
		vector operator*(const dynamic_vector_view<_TYPE, Itr>& other) const
		{
			return vector(*this) *= other;
		}

		template <typename Itr>
		vector operator/(const dynamic_vector_view<_TYPE, Itr>& other) const
		{
			return vector(*this) /= other;
		}

		//Binary assigment operators
		vector& operator+=(const vector& other) noexcept
		{
			return (x += other[0], y += other[1], *this);
		}

		vector& operator-=(const vector& other) noexcept
		{
			return (x -= other[0], y -= other[1], *this);
		}

		vector& operator*=(const vector& other) noexcept
		{
			return (x *= other[0], y *= other[1], *this);
		}

		vector& operator/=(const vector& other) noexcept
		{
			return (x/= other[0], y /= other[1], *this);
		}

		template <typename Itr>
		constexpr vector& operator+=(const vector_view<_TYPE, 2, Itr>& other) noexcept
		{
			return (x += other[0], y += other[1], *this);
		}

		template <typename Itr>
		constexpr vector& operator-=(const vector_view<_TYPE, 2, Itr>& other) noexcept
		{
			return (x -= other[0], y -= other[1], *this);
		}

		template <typename Itr>
		constexpr vector& operator*=(const vector_view<_TYPE, 2, Itr>& other) noexcept
		{
			return (x *= other[0], y *= other[1], *this);
		}

		template <typename Itr>
		constexpr vector& operator/=(const vector_view<_TYPE, 2, Itr>& other) noexcept
		{
			return (x /= other[0], y /= other[1], *this);
		}

		constexpr vector& operator+=(const _TYPE& value) noexcept
		{
			return (x += value, y += value, *this);
		}

		constexpr vector& operator-=(const _TYPE& value) noexcept
		{
			return (x -= value, y -= value, *this);
		}

		constexpr vector& operator*=(const _TYPE& value) noexcept
		{
			return (x *= value, y *= value, *this);
		}

		constexpr vector& operator/=(const _TYPE& value) noexcept
		{
			return (x /= value, y /= value, *this);
		}

		vector& operator+=(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(GetSize() == vec.GetSize())
			return (x += vec[0], y += vec[1], *this);
		}

		vector& operator-=(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(GetSize() == vec.GetSize())
			return (x -= vec[0], y -= vec[1], *this);
		}

		vector& operator*=(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(GetSize() == vec.GetSize())
			return (x *= vec[0], y *= vec[1], *this);
		}

		vector& operator/=(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(GetSize() == vec.GetSize())
			return (x /= vec[0], y /= vec[1], *this);
		}

		template <typename Itr>
		vector& operator+=(const dynamic_vector_view<_TYPE, Itr>& other)
		{
			stm_assert(GetSize() == other.GetSize());
			return (x += other[0], y += other[1], *this);
		}

		template <typename Itr>
		vector& operator-=(const dynamic_vector_view<_TYPE, Itr>& other)
		{
			stm_assert(GetSize() == other.GetSize());
			return (x -= other[0], y -= other[1], *this);
		}

		template <typename Itr>
		vector& operator*=(const dynamic_vector_view<_TYPE, Itr>& other)
		{
			stm_assert(GetSize() == other.GetSize());
			return (x *= other[0], y *= other[1], *this);
		}

		template <typename Itr>
		vector& operator/=(const dynamic_vector_view<_TYPE, Itr>& other)
		{
			stm_assert(GetSize() == other.GetSize());
			return (x /= other[0], y /= other[1], *this);
		}

		//Data Info Functions
		static constexpr unsigned int container_size() noexcept { return 2; }

		constexpr _TYPE*       GetData()       noexcept { return _data; }
		constexpr const _TYPE* GetData() const noexcept { return _data; }
		constexpr auto&       GetArray()       noexcept { return _data; }
		constexpr const auto& GetArray() const noexcept { return _data; }
		constexpr unsigned int GetSize() const noexcept { return container_size(); }

		constexpr vector_view<_TYPE, 2, const_iterator> GetView() const noexcept { return vector_view<_TYPE, 2, const_iterator>(*this); }

		//Iterators
		constexpr iterator begin() noexcept { return iterator(_data); }
		constexpr iterator end()   noexcept { return iterator(_data + 2); }

		//Unwrapped Iterators (u stands for unwrapped)
		constexpr auto ubegin() noexcept { return begin().unwrap(); }
		constexpr auto uend()   noexcept { return end().unwrap(); }

		//Const iterators
		constexpr const_iterator cbegin() const noexcept { return const_iterator(_data); }
		constexpr const_iterator cend()   const noexcept { return const_iterator(_data + 2); }

		//Unwrapped const iterators
		constexpr auto ucbegin() const noexcept { return cbegin().unwrap(); }
		constexpr auto ucend()   const noexcept { return cend().unwrap(); }

		//Math functions
		_TYPE Magnitude() const noexcept
		{
			return std::sqrt(DotProduct(*this));
		}

		vector UnitVector() const noexcept
		{
			return (*this) / Magnitude();
		}

		constexpr _TYPE DotProduct(const vector& other) const noexcept
		{
			return (x * other.x) + (y * other.y);
		}

		template <typename Itr>
		constexpr _TYPE DotProduct(const vector_view<_TYPE, 2, Itr>& other) const noexcept
		{
			return (x * other[0]) + (y * other[1]);
		}

		_TYPE DotProduct(const dynamic_vector<_TYPE>& other) const
		{
			stm_assert(other.GetSize() == GetSize());
			return (x * other[0]) + (y * other[1]);
		}

		template <typename Itr>
		_TYPE DotProduct(const dynamic_vector_view<_TYPE, Itr>& other) const
		{
			stm_assert(other.GetSize() == GetSize());
			return (x * other[0]) + (y * other[1]);
		}

		constexpr vector<_TYPE, 3> CrossProduct(const vector& other) const noexcept
		{
			return vector(0, 0, (x * other.y) - (y * other.x));
		}

		template <typename Itr>
		constexpr vector<_TYPE, 3> CrossProduct(const vector_view<_TYPE, 2, Itr>& other) const noexcept
		{
			return vector(0, 0, (x * other[1]) - (y * other[0]));
		}

		vector<_TYPE, 3> CrossProduct(const dynamic_vector<_TYPE>& other) const
		{
			stm_assert(other.GetSize() == GetSize());
			return vector(0, 0, (x * other[1]) - (y * other[0]));
		}

		template <typename Itr>
		vector<_TYPE, 3> CrossProduct(const dynamic_vector_view<_TYPE, Itr>& other) const
		{
			stm_assert(other.GetSize() == GetSize());
			return vector(0, 0, (x * other[1]) - (y * other[0]));
		}
	};

	typedef vector<int, 2>		vec2i;
	typedef vector<float, 2>	vec2f;
}

#endif /* stm_vector_2_h */
