#ifndef stm_complex_h
#define stm_complex_h

#include <iostream>
#include <math.h>
#include <cmath>

namespace stm
{
	template<typename _TYPE>
	class complex
	{
	public:
		struct
		{
			union
			{
				_TYPE data[2] {};
				struct
				{
					_TYPE r, i;
				};
			};
		};

		constexpr complex() noexcept = default;

		constexpr complex(const _TYPE& rPart, const _TYPE& iPart) noexcept
			:r(rPart), i(iPart)
		{
		}

		constexpr complex(const _TYPE* const data) noexcept
			:r(data[0]), i(data[1])
		{
		}

		constexpr complex operator+(const complex& other) const noexcept
		{
			return complex(r + other.r, i + other.i);
		}

		constexpr complex operator+(const complex& other) const noexcept
		{
			return complex(r + other.r, i + other.i);
		}

		constexpr complex operator-(const complex& other) const noexcept
		{
			return complex(r - other.r, i - other.i);
		}

		constexpr complex operator+(const _TYPE& other) const noexcept
		{
			return complex(r + other, i);
		}

		constexpr complex operator-(const _TYPE& other) const noexcept
		{
			return complex(r - other, i);
		}

		constexpr complex operator*(const _TYPE& other) const noexcept
		{
			return complex(r * other, i * other);
		}

		constexpr complex operator/(const _TYPE& other) const noexcept
		{
			return complex(r / other, i / other);
		}

		constexpr complex operator*(const complex& other) const noexcept
		{
			return complex((r * other.r) - (i * other.i), (i * other.r) + (r * other.i));
		}

		constexpr complex operator/(const complex& other) const noexcept
		{
			return (*this) * other.Conjugate() / other.dot(other);
		}

		constexpr complex Conjugate() const noexcept
		{
			return complex(r, -i);
		}

		constexpr _TYPE dot(const complex& other) const noexcept
		{
			return r * other.r + i * other.i;
		}

		_TYPE Magnitude() const noexcept
		{
			return sqrt((r * r) + (i * i));
		}

		_TYPE Direction() const noexcept
		{
			return (i > 0 && r < 0) ? (atan(1) * 2 + atan(i / r)) : atan(i / r);
		}
	};
}
#endif /* stm_complex_h */