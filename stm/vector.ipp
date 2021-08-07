#include <iostream>
#include <cstring>
#include <utility>

#include "stm_internal.h"

namespace stm
{
	template<typename _TYPE, unsigned int _DIM>
	constexpr vector<_TYPE, _DIM>::vector(const constexpr_vector<_TYPE, _DIM>& vector) noexcept
	{
		stm_internal::copy_array_data(vector.GetArray(), GetArray());
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>::vector(const vector_view<_TYPE, _DIM, Itr>& vector_view) noexcept
	{
		std::copy(vector_view.cbegin(), vector_view.cend(), ubegin());
	}

	template<typename _TYPE, unsigned int _DIM> template<typename Itr>
	vector<_TYPE, _DIM>::vector(const Itr begin, const Itr end) noexcept
	{
		stm_assert((end - begin) == _DIM);
		std::copy(begin, end, ubegin());
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>::vector(const _TYPE& value) noexcept
	{
		std::fill(ubegin(), uend(), value);
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>::vector(const _TYPE (&data)[_DIM]) noexcept
	{
		std::copy(data, data + container_size(), ubegin());
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>::vector(const _TYPE* const data, const unsigned int offset) noexcept
	{
		std::copy(data + offset, data + offset + container_size(), ubegin());
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>::vector(std::initializer_list<_TYPE> list) noexcept
	{
		stm_assert(list.size() == container_size());
		std::copy(list.begin(), list.end(), ubegin());
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator=(const dynamic_vector<_TYPE>& vec)
	{
		stm_assert(container_size() == vec.GetSize());
		std::copy(vec.ubegin(), vec.uend(), ubegin());
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator=(const vector_view<_TYPE, _DIM, Itr>& other) noexcept
	{
		if (GetData() == other.GetData()) { return *this; }
		std::copy(other.cbegin(), other.cend(), ubegin());
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator=(const dynamic_vector_view<_TYPE, Itr>& other)
	{
		if (GetData() == other.GetData() && GetSize() == other.GetSize()) { return *this; }
		stm_assert(GetSize() == other.GetSize());
		std::copy(other.cbegin(), other.cend(), ubegin());
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator-() const noexcept
	{
		vector temp;
		for (unsigned int i = 0; i < _DIM; ++i)
			temp._data[i] = -_data[i];
		return temp;
	}

	template<typename _TYPE, unsigned int _DIM> template<typename O_TYPE>
	vector<O_TYPE, _DIM> vector<_TYPE, _DIM>::Cast() const  noexcept
	{
		vector<O_TYPE, _DIM> temp;
		for (unsigned int i = 0; i < _DIM; ++i)
			temp[i] = O_TYPE(_data[i]);
		return temp;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename _FUNCTION>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::ApplyToVector(_FUNCTION&& func)
	{
		//for (unsigned int i = 0; i < _DIM; ++i)
		//	_data[i] = func(_data[i]);
		for (auto it = begin(); it != end(); ++it)
			*it = func(*it);
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::SetAll(const _TYPE& value) noexcept
	{
		return (std::fill(ubegin(), uend(), value), *this);
	}
	
	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator+(const vector& other) const noexcept
	{
		return vector(*this) += other;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator-(const vector& other) const noexcept
	{
		return vector(*this) -= other;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator*(const vector& other) const noexcept
	{
		return vector(*this) *= other;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator/(const vector& other) const noexcept
	{
		return vector(*this) / other;
	}
	
	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator+(const vector_view<_TYPE, _DIM, Itr>& other) const noexcept
	{
		return vector(*this) += other;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator-(const vector_view<_TYPE, _DIM, Itr>& other) const noexcept
	{
		return vector(*this) -= other;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator*(const vector_view<_TYPE, _DIM, Itr>& other) const noexcept
	{
		return vector(*this) *= other;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator/(const vector_view<_TYPE, _DIM, Itr>& other) const noexcept
	{
		return vector(*this) /= other;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator+(const _TYPE& other) const noexcept
	{
		return vector(*this) += other;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator-(const _TYPE& other) const noexcept
	{
		return vector(*this) -= other;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator*(const _TYPE& other) const noexcept
	{
		return vector(*this) *= other;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator/(const _TYPE& other) const noexcept
	{
		return vector(*this) /= other;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator+(const dynamic_vector<_TYPE>& vec) const
	{
		stm_assert(_DIM == vec.GetSize());
		return vector(*this) += vec;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator-(const dynamic_vector<_TYPE>& vec) const
	{
		stm_assert(_DIM == vec.GetSize());
		return vector(*this) -= vec;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator*(const dynamic_vector<_TYPE>& vec) const
	{
		stm_assert(_DIM == vec.GetSize());
		vector temp;
		return vector(*this) *= vec;
	}

	template<typename _TYPE, unsigned int _DIM>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator/(const dynamic_vector<_TYPE>& vec) const
	{
		stm_assert(_DIM == vec.GetSize());
		return vector(*this) /= vec;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator+(const dynamic_vector_view<_TYPE, Itr>& other) const
	{
		return vector(*this) += other;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator-(const dynamic_vector_view<_TYPE, Itr>& other) const
	{
		return vector(*this) -= other;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator*(const dynamic_vector_view<_TYPE, Itr>& other) const
	{
		return vector(*this) *= other;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	inline vector<_TYPE, _DIM> vector<_TYPE, _DIM>::operator/(const dynamic_vector_view<_TYPE, Itr>& other) const
	{
		return vector(*this) /= other;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator+=(const vector& other) noexcept
	{
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] += other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator-=(const vector& other) noexcept
	{
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] -= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator*=(const vector& other) noexcept
	{
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] *= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator/=(const vector& other) noexcept
	{
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] /= other[i];
		return *this;
	}


	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator+=(const _TYPE& other) noexcept
	{
		_TYPE temp[_DIM];
		for (unsigned int i = 0; i < _DIM; ++i)
		{
			temp[i] = _data[i] + other;
			_data[i] = temp[i];
		}
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator-=(const _TYPE& other) noexcept
	{
		_TYPE temp[_DIM];
		for (unsigned int i = 0; i < _DIM; ++i)
		{
			temp[i] = _data[i] - other;
			_data[i] = temp[i];
		}
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator*=(const _TYPE& other) noexcept
	{
		_TYPE temp[_DIM];
		for (unsigned int i = 0; i < _DIM; ++i)
		{
			temp[i] = _data[i] * other;
			_data[i] = temp[i];
		}
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator/=(const _TYPE& other) noexcept
	{
		_TYPE temp[_DIM];
		for (unsigned int i = 0; i < _DIM; ++i)
		{
			temp[i] = _data[i] / other;
			_data[i] = temp[i];
		}
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator+=(const dynamic_vector<_TYPE>& other)
	{
		stm_assert(other.GetSize() == GetSize());
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] += other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator-=(const dynamic_vector<_TYPE>& other)
	{
		stm_assert(other.GetSize() == GetSize());
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] -= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator*=(const dynamic_vector<_TYPE>& other)
	{
		stm_assert(other.GetSize() == GetSize());
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] *= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator/=(const dynamic_vector<_TYPE>& other)
	{
		stm_assert(other.GetSize() == GetSize());
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] /= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator+=(const vector_view<_TYPE, _DIM, Itr>& other) noexcept
	{
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] += other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator-=(const vector_view<_TYPE, _DIM, Itr>& other) noexcept
	{
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] -= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator*=(const vector_view<_TYPE, _DIM, Itr>& other) noexcept
	{
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] *= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator/=(const vector_view<_TYPE, _DIM, Itr>& other) noexcept
	{
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] /= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator+=(const dynamic_vector_view<_TYPE, Itr>& other)
	{
		stm_assert(other.GetSize() == GetSize());
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] += other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator-=(const dynamic_vector_view<_TYPE, Itr>& other)
	{
		stm_assert(other.GetSize() == GetSize());
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] -= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator*=(const dynamic_vector_view<_TYPE, Itr>& other)
	{
		stm_assert(other.GetSize() == GetSize());
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] *= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	vector<_TYPE, _DIM>& vector<_TYPE, _DIM>::operator/=(const dynamic_vector_view<_TYPE, Itr>& other)
	{
		stm_assert(other.GetSize() == GetSize());
		for (unsigned int i = 0; i < _DIM; ++i)
			_data[i] /= other[i];
		return *this;
	}

	template<typename _TYPE, unsigned int _DIM>
	_TYPE vector<_TYPE, _DIM>::DotProduct(const vector& other) const noexcept
	{
		_TYPE sum = 0;
		for (unsigned int i = 0; i < _DIM; ++i)
			sum += _data[i] * other[i];
		return sum;
	}

	template<typename _TYPE, unsigned int _DIM>
	_TYPE vector<_TYPE, _DIM>::DotProduct(const dynamic_vector<_TYPE>& vec) const
	{
		stm_assert(vec.GetSize() == _DIM)
		_TYPE sum = 0;
		for (unsigned int i = 0; i < _DIM; ++i)
			sum += _data[i] * vec[i];
		return sum;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	_TYPE vector<_TYPE, _DIM>::DotProduct(const vector_view<_TYPE, _DIM, Itr>& other) const noexcept
	{
		_TYPE sum = 0;
		for (unsigned int i = 0; i < _DIM; ++i)
			sum += _data[i] * other[i];
		return sum;
	}

	template<typename _TYPE, unsigned int _DIM> template <typename Itr>
	_TYPE vector<_TYPE, _DIM>::DotProduct(const dynamic_vector_view<_TYPE, Itr>& other) const
	{
		stm_assert(other.GetSize() == GetSize());
		_TYPE sum = 0;
		for (unsigned int i = 0; i < _DIM; ++i)
			sum += _data[i] * other[i];
		return sum;
	}

	template<typename _TYPE, unsigned int _DIM>
	constexpr constexpr_vector<_TYPE, _DIM>::constexpr_vector(const _TYPE& value) noexcept
	{
		stm_internal::copy_value_data(value, _data);
	}

	template<typename _TYPE, unsigned int _DIM>
	constexpr constexpr_vector<_TYPE, _DIM>::constexpr_vector(const _TYPE (&data)[_DIM]) noexcept
	{
		stm_internal::copy_array_data(data, _data);
	}

	template<typename _VECTYPE>
	auto pow(const _VECTYPE& vec, const unsigned int power) -> decltype(vec * vec)
	{
		auto out = vec * vec;
		unsigned int i = 2;
		while (i * 2 < power)
		{
			out *= out;
			i *= 2;
		}
		for (unsigned int j = i; j < power; ++j)
			out *= vec;
		return out;
	}
}