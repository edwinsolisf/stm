#ifndef stm_quaternion_h
#define stm_quaternion_h

#include <iostream>
#include <math.h>
#include "vector.h"

namespace stm
{
	template<typename _TYPE>
	class quaternion
	{
	public:
		struct
		{
			union
			{
                _TYPE _data[4] {};
				struct
				{
					_TYPE r, i, j, k;
				};
			};
		};

        constexpr quaternion() = default;
        
		constexpr quaternion(const _TYPE* const data) noexcept
			:r(_data[0]), i(_data[1]), j(_data[2]), k(_data[3])
		{
		}

        constexpr quaternion(const _TYPE& value) noexcept
            :r(value), i(value), j(value), k(value)
        {
        }
        
        constexpr quaternion(const _TYPE& scalar, const vector<_TYPE, 3>& vector) noexcept
            :r(scalar), i(vector.x), j(vector.y), k(vector.z)
        {
            
        }
        
        constexpr quaternion(const vector<_TYPE, 4>& values) noexcept
            :r(values[0]), i(values[1]), j(values[2]), k(values[3])
        {
        }
        
		constexpr quaternion(const _TYPE& rPart, const _TYPE& iPart, const _TYPE& jPart, const _TYPE& kPart) noexcept
			:r(rPart), i(iPart), j(jPart), k(kPart)
		{
		}

		constexpr quaternion operator+(const quaternion& other) const noexcept
		{
			return quaternion(r + other.r, i + other.i, j + other.j, k + other.k);
		}

		constexpr quaternion operator-(const quaternion& other) const noexcept
		{
			return quaternion(r - other.r, i - other.i, j - other.j, k - other.k);
		}

		constexpr quaternion operator*(const quaternion& other) const noexcept
		{
			return quaternion((r * other.r) - (i * other.i) - (j * other.j) - (k * other.k),
                              (r * other.i) + (i * other.r) + (j * other.k) - (k * other.j),
                              (r * other.j) - (i * other.k) + (j * other.r) + (k * other.i),
                              (r * other.k) + (i * other.j) - (j * other.i) + (k * other.r));
		}
        
        constexpr quaternion operator/(const quaternion& other) const noexcept
        {
            return Reciprocal() * other;
        }
        
        constexpr quaternion operator+(const _TYPE& other) const noexcept
        {
            return quaternion(r + other, i, j, k);
        }
        
        constexpr quaternion operator-(const _TYPE& other) const noexcept
        {
            return quaternion(r - other, i, j, k);
        }
        
        constexpr quaternion operator*(const _TYPE& other) const noexcept
        {
            return quaternion(r * other, i * other, j * other, k * other);
        }
        
        constexpr quaternion operator/(const _TYPE& other) const noexcept
        {
            return quaternion(r / other, i / other, j / other, k / other);
        }
        
		constexpr quaternion Conjugate() const noexcept
		{
			return quaternion(r, -i, -j, -k);
		}

		inline _TYPE Magnitude() const noexcept
		{
			return sqrtf((r * r) + (i * i) + (j * j) + (k * k));
		}
        
        inline quaternion Reciprocal() const noexcept
        {
            return Conjugate() / Magnitude();
        }
        
        inline quaternion Versor() const noexcept
        {
            return (*this) / Magnitude();
        }
        
        constexpr _TYPE RealPart() const noexcept
        {
            return r;
        }
        
        constexpr vector<_TYPE, 3> VectorPart() const noexcept
        {
            return vector<_TYPE, 3>(&_data[1], 0);
        }
        
        constexpr vector<_TYPE, 4> ToVector() const noexcept
        {
            return vector<_TYPE, 4>(_data);
        }
	};

    typedef quaternion<float> quatf;
    typedef quaternion<int>   quati;
}
#endif