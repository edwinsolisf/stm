#ifndef stm_vector_4_h
#define stm_vector_4_h

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
	class vector<_TYPE, 4>
	{
	public:
		struct
		{
			union
			{
				_TYPE _data[4] {};
				struct
				{
					_TYPE x, y, z, w;
				};
			};
		};
		using ElemType = _TYPE;
		using iterator = vector_iterator<vector<_TYPE, 4>>;
		using const_iterator = vector_const_iterator<vector<_TYPE, 4>>;

		//Constructors
		constexpr vector() noexcept = default;

		constexpr vector(const _TYPE (&data)[4]) noexcept
			:_data(data)
		{
		}

		constexpr vector(const _TYPE* data, const unsigned int offset) noexcept
			:x(data[offset]), y(data[offset + 1]), z(data[offset + 2]), w(data[offset + 3])
		{
		}

		constexpr vector(const _TYPE& value) noexcept
			:w(value), x(value), y(value), z(value)
		{
		}

		constexpr vector(const _TYPE& _x, const _TYPE& _y, const _TYPE& _z, const _TYPE& _w) noexcept
			:x(_x), y(_y), z(_z), w(_w)
		{
		}

		template <typename Itr>
		constexpr vector(const vector_view<_TYPE, 4, Itr>& vector_view) noexcept
			:x(vector_view[0]), y(vector_view[1]), z(vector_view[2]), w(vector_view[3])
		{
		}

		template <typename Itr>
		constexpr vector(const Itr begin, const Itr end)
			:x(begin[0]), y(begin[1]), z(begin[2]), w(begin[3])
		{
			stm_assert((end - begin) / sizeof(_TYPE) == GetSize());
		}

		constexpr vector(const vector&) noexcept = default;
		constexpr vector(vector&&)      noexcept = default;
		~vector() = default;

		//Assigment Operator
		constexpr vector& operator=(const vector&) noexcept = default;
		constexpr vector& operator=(vector&&)      noexcept = default;

		template <typename Itr>
		constexpr vector& operator=(const vector_view<_TYPE, 4, Itr>& other) noexcept
		{
			return (x = other[0], y = other[1], z = other[2], w = other[3], *this);
		}

		template <typename Itr>
		vector& operator=(const dynamic_vector_view<_TYPE, Itr>& other)
		{
			stm_assert(GetSize() == other.GetSize());
			return (x = other[0], y = other[1], z = other[2], w = other[3], *this);
		}

		vector& operator=(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(4 == vec.GetSize());
			return (x = vec[0], y = vec[1], z = vec[2], w = vec[3], *this);
		}

		//Unary Operators
		constexpr vector operator+() const noexcept
		{
			return *this;
		}

		constexpr vector operator-() const noexcept
		{
			return vector(-x, -y, -z, -w);
		}

		constexpr _TYPE&       operator[](const unsigned int index)       noexcept { stm_assert(index < 4); return _data[index]; }
		constexpr const _TYPE& operator[](const unsigned int index) const noexcept { stm_assert(index < 4); return _data[index]; }

		//Casting
		template<unsigned int DIM>
		constexpr vector<_TYPE, DIM> ToVector() const noexcept
		{
			static_assert(DIM <= 4, "New vector is of greater dimensions");
			return vector<_TYPE, DIM>(_data);
		}

		template<typename O_TYPE>
		constexpr vector<O_TYPE, 4> Cast() const noexcept
		{
			return vector<O_TYPE, 4>((O_TYPE)x, (O_TYPE)y, (O_TYPE)z, (O_TYPE)w);
		}

		//Data manipulation functions
		template <typename _FUNCTION>
		vector& ApplyToVector(_FUNCTION&& func)
		{
			return (x = func(x), y = func(y), z = func(z), w = func(w), *this);
		}

		vector& SetAll(const _TYPE& value) noexcept
		{
			return (x = value, y = value, z = value, w = value, *this);
		}

		//Binary Operators
		constexpr vector operator+(const vector& other) const noexcept
		{
			return vector(x + other.x, y + other.y, z + other.z, w + other.w);
		}

		constexpr vector operator-(const vector& other) const noexcept
		{
			return vector(x - other.x, y - other.y, z - other.z, w - other.w);
		}

		constexpr vector operator*(const vector& other) const noexcept
		{
			return vector(x * other.x, y * other.y, z * other.z, w * other.w);
		}

		constexpr vector operator/(const vector& other) const noexcept
		{
			return vector(x / other.x, y / other.y, z / other.z, w / other.w);
		}

		template <typename Itr>
		constexpr vector operator+(const vector_view<_TYPE, 4, Itr>& other) const noexcept
		{
			return vector(*this) += other;
		}

		template <typename Itr>
		constexpr vector operator-(const vector_view<_TYPE, 4, Itr>& other) const noexcept
		{
			return vector(*this) -= other;
		}

		template <typename Itr>
		constexpr vector operator*(const vector_view<_TYPE, 4, Itr>& other) const noexcept
		{
			return vector(*this) *= other;
		}

		template <typename Itr>
		constexpr vector operator/(const vector_view<_TYPE, 4, Itr>& other) const noexcept
		{
			return vector(*this) /= other;
		}

		constexpr vector operator+(const _TYPE& other) const noexcept
		{
			return vector(x + other, y + other, z + other, w + other);
		}

		constexpr vector operator-(const _TYPE& other) const noexcept
		{
			return vector(x - other, y - other, z - other, w - other);
		}

		constexpr vector operator*(const _TYPE& other) const noexcept
		{
			return vector(x * other, y * other, z * other, w * other);
		}

		constexpr vector operator/(const _TYPE& other) const noexcept
		{
			return vector(x / other, y / other, z / other, w / other);
		}

		vector operator+(const dynamic_vector<_TYPE>& vec) const
		{
			stm_assert(4 == vec.GetSize());
			return vector(x + vec[0], y + vec[1], z + vec[2], w + vec[3]);
		}

		vector operator-(const dynamic_vector<_TYPE>& vec) const
		{
			stm_assert(4 == vec.GetSize());
			return vector(x - vec[0], y - vec[1], z - vec[2], w - vec[3]);
		}

		vector operator*(const dynamic_vector<_TYPE>& vec) const
		{
			stm_assert(4 == vec.GetSize());
			return vector(x * vec[0], y * vec[1], z * vec[2], w * vec[3]);
		}

		vector operator/(const dynamic_vector<_TYPE>& vec) const
		{
			stm_assert(4 == vec.GetSize());
			return vector(x / vec[0], y / vec[1], z / vec[2], w / vec[3]);
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
		constexpr vector& operator+=(const vector& other) noexcept
		{
			return (x += other[0], y += other[1], z += other[2], w += other[3], *this);
		}

		constexpr vector& operator-=(const vector& other) noexcept
		{
			return (x -= other[0], y -= other[1], z -= other[2], w -= other[3], *this);
		}

		constexpr vector& operator*=(const vector& other) noexcept
		{
			return (x *= other[0], y *= other[1], z *= other[2], w *= other[3], *this);
		}

		constexpr vector& operator/=(const vector& other) noexcept
		{
			return (x /= other[0], y /= other[1], z /= other[2], w /= other[3], *this);
		}

		template <typename Itr>
		constexpr vector& operator+=(const vector_view<_TYPE, 4, Itr>& other) noexcept
		{
			return (x += other[0], y += other[1], z += other[2], w += other[3], *this);
		}

		template <typename Itr>
		constexpr vector& operator-=(const vector_view<_TYPE, 4, Itr>& other) noexcept
		{
			return (x -= other[0], y -= other[1], z -= other[2], w -= other[3], *this);
		}

		template <typename Itr>
		constexpr vector& operator*=(const vector_view<_TYPE, 4, Itr>& other) noexcept
		{
			return (x *= other[0], y *= other[1], z *= other[2], w *= other[3], *this);
		}

		template <typename Itr>
		constexpr vector& operator/=(const vector_view<_TYPE, 4, Itr>& other) noexcept
		{
			return (x /= other[0], y /= other[1], z /= other[2], w /= other[3], *this);
		}

		vector& operator+=(const _TYPE& value) noexcept
		{
			return (x += value, y += value, z += value, w += value, *this);
		}

		vector& operator-=(const _TYPE& value) noexcept
		{
			return (x -= value, y -= value, z -= value, w -= value, *this);
		}

		vector& operator*=(const _TYPE& value) noexcept
		{
			return (x *= value, y *= value, z *= value, w *= value, *this);
		}

		vector& operator/=(const _TYPE& value) noexcept
		{
			return (x /= value, y /= value, z /= value, w /= value, *this);
		}

		vector& operator+=(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(GetSize() == vec.GetSize())
			return (x += vec[0], y += vec[1], z += vec[2], w += vec[3], *this);
		}

		vector& operator-=(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(GetSize() == vec.GetSize())
			return (x -= vec[0], y -= vec[1], z -= vec[2], w -= vec[3], *this);
		}

		vector& operator*=(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(GetSize() == vec.GetSize())
			return (x *= vec[0], y *= vec[1], z *= vec[2], w *= vec[3], *this);
		}

		vector& operator/=(const dynamic_vector<_TYPE>& vec)
		{
			stm_assert(GetSize() == vec.GetSize())
			return (x /= vec[0], y /= vec[1], z /= vec[2], w /= vec[3], *this);
		}

		template <typename Itr>
		vector& operator+=(const dynamic_vector_view<_TYPE, Itr>& other)
		{
			stm_assert(GetSize() == other.GetSize());
			return (x += other[0], y += other[1], z += other[2], w += other[3], *this);
		}

		template <typename Itr>
		vector& operator-=(const dynamic_vector_view<_TYPE, Itr>& other)
		{
			stm_assert(GetSize() == other.GetSize());
			return (x -= other[0], y -= other[1], z -= other[2], w -= other[3], *this);
		}

		template <typename Itr>
		vector& operator*=(const dynamic_vector_view<_TYPE, Itr>& other)
		{
			stm_assert(GetSize() == other.GetSize());
			return (x *= other[0], y *= other[1], z *= other[2], w *= other[3], *this);
		}

		template <typename Itr>
		vector& operator/=(const dynamic_vector_view<_TYPE, Itr>& other)
		{
			stm_assert(GetSize() == other.GetSize());
			return (x /= other[0], y /= other[1], z /= other[2], w /= other[3], *this);
		}

		//Data Info Functions
		static constexpr unsigned int container_size() noexcept { return 4; }

		constexpr _TYPE*       GetData()       noexcept { return _data; }
		constexpr const _TYPE* GetData() const noexcept { return _data; }
		constexpr auto&       GetArray()       noexcept { return _data; }
		constexpr const auto& GetArray() const noexcept { return _data; }
		constexpr unsigned int GetSize() const noexcept { return container_size(); }

		constexpr vector_view<_TYPE, 4, const_iterator> GetView() const noexcept { return vector_view<_TYPE, 4, const_iterator>(*this); }

		//Iterators
		constexpr iterator begin() noexcept { return iterator(_data); }
		constexpr iterator end()   noexcept { return iterator(_data + 4); }

		//Unwrapped Iterators (u stands for unwrapped)
		constexpr auto ubegin() noexcept { return begin().unwrap(); }
		constexpr auto uend()   noexcept { return end().unwrap(); }

		//Const iterators
		constexpr const_iterator cbegin() const noexcept { return const_iterator(_data); }
		constexpr const_iterator cend()   const noexcept { return const_iterator(_data + 4); }

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
			return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
		}

		template <typename Itr>
		constexpr _TYPE DotProduct(const vector_view<_TYPE, 4, Itr>& other) const noexcept
		{
			return (x * other[0]) + (y * other[1]) + (z * other[2]) + (w * other[3]);
		}

		_TYPE DotProduct(const dynamic_vector<_TYPE>& other) const
		{
			stm_assert(other.GetSize() == GetSize());
			return (x * other[0]) + (y * other[1]) + (z * other[2]) + (w * other[3]);
		}

		template <typename Itr>
		_TYPE DotProduct(const dynamic_vector_view<_TYPE, Itr>& other) const
		{
			stm_assert(other.GetSize() == GetSize());
			return (x * other[0]) + (y * other[1]) + (z * other[2]) + (w * other[3]);
		}

	};

	typedef vector<int, 4>		vec4i;
	typedef vector<float, 4>	vec4f;
}

#endif /* stm_vector_4_h */
