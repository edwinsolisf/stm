#include <iostream>
#include <cstring>
#include <utility>

namespace stm
{
	template<typename _T>
	dynamic_vector<_T>::dynamic_vector(const unsigned int dimensions)
		:_data(new _T[dimensions]{}), _dimensions(dimensions)
	{
		stm_assert(dimensions != 0);
	}

	template<typename _T>
	dynamic_vector<_T>::dynamic_vector(const unsigned int dimensions, const _T* const data)
		:_data(new _T[dimensions]), _dimensions(dimensions)
	{
		stm_assert(dimensions != 0);
		std::copy(data, data + dimensions, ubegin());
		//memcpy(_data, data, _dimensions * sizeof(_T));
	}

	template<typename _T>
	dynamic_vector<_T>::dynamic_vector(const unsigned int dimensions, const _T& value)
		:_data(new _T[dimensions]), _dimensions(dimensions)
	{
		stm_assert(dimensions != 0);
		std::fill(ubegin(), uend(), value);
	}

	template<typename _T>
	dynamic_vector<_T>::dynamic_vector(const unsigned int dimensions, std::initializer_list<_T> list)
		:_data(new _T[dimensions]), _dimensions(dimensions)
	{
		stm_assert(list.size() == _dimensions);
		std::copy(list.begin(), list.end(), ubegin());
	}

	template<typename _T>
	dynamic_vector<_T>::dynamic_vector(const dynamic_vector& other)
		:_data(new _T[other._dimensions]), _dimensions(other._dimensions)
	{
		std::copy(other.ucbegin(), other.ucend(), ubegin());
		//memcpy(_data, other._data, _dimensions * sizeof(_T));
	}

	template<typename _T>
	dynamic_vector<_T>::dynamic_vector(dynamic_vector&& other) noexcept
		:_data(std::exchange(other._data, nullptr)), _dimensions(std::exchange(other._dimensions, 0))
	{
	}

	template<typename _T>
	dynamic_vector<_T>::dynamic_vector(_T*& data, const unsigned int dimensions)
		:_data(std::exchange(data, nullptr)), _dimensions(dimensions)
	{
		stm_assert(_data != nullptr);
	}

	template <typename _T> template <typename Itr>
	dynamic_vector<_T>::dynamic_vector(const dynamic_vector_view<_T, Itr>& other)
		:_data(new _T[other.GetSize()]), _dimensions(other.GetSize())
	{
		stm_assert(other.GetSize() != 0 && other.GetData() != nullptr);
		std::copy(other.cbegin(), other.cend(), ubegin());
	}


	template<typename _T> template<unsigned int _DIM>
	dynamic_vector<_T>::dynamic_vector(const vector<_T, _DIM>& static_vector)
		: _data(new _T[_DIM]), _dimensions(_DIM)
	{
		std::copy(static_vector.ucbegin(), static_vector.ucend(), ubegin());
		//memcpy(_data, static_vector.GetData(), dimensions * sizeof(_T));
	}

	template <typename _T> template <unsigned int _DIM, typename Itr>
	dynamic_vector<_T>::dynamic_vector(const vector_view<_T, _DIM, Itr>& other)
		:_data(new _T[_DIM]), _dimensions(_DIM)
	{
		std::copy(other.cbegin(), other.cend(), ubegin());
	}

	template<typename _T>
	dynamic_vector<_T>::~dynamic_vector()
	{
		delete[] _data;
	}

	template<typename _T>
	dynamic_vector<_T>& dynamic_vector<_T>::operator=(const dynamic_vector& other)
	{
		if (this == &other) { return *this; }
		if (_dimensions >= other._dimensions)
			std::copy(other.ucbegin(), other.ucend(), ubegin());
			//memcpy(_data, other._data, _dimensions * sizeof(_T));
		else
		{
			_T* newData = new _T[other._dimensions];
			std::copy(other.ucbegin(), other.ucend(), newData);
			//memcpy(newData, other._data, other._dimensions * sizeof(_T));
			delete[] _data;
			_data = newData;
		}
		_dimensions = other._dimensions;

		return *this;
	}

	template<typename _T>
	dynamic_vector<_T>& dynamic_vector<_T>::operator=(dynamic_vector&& other) noexcept
	{
		if (this == &other) { return *this; }
		std::swap(_data, other._data);
		std::swap(_dimensions, other._dimensions);

		return *this;
	}

	template <typename _T> template <typename Itr>
	dynamic_vector<_T>& dynamic_vector<_T>::operator=(const dynamic_vector_view<_T, Itr>& other)
	{
		if (this->GetData() == other.GetData() && GetSize() == other.GetSize()) { return *this; }
		if (_dimensions >= other.GetSize())
			std::copy(other.cbegin(), other.cend(), ubegin());
		else
		{
			_T* newData = new _T[other.GetSize()];
			std::copy(other.cbegin(), other.cend(), newData);
			delete[] _data;
			_data = newData;
		}
		_dimensions = other.GetSize();
		return *this;
	}

	template<typename _T>
	dynamic_vector<_T> dynamic_vector<_T>::operator-() const&
	{
		dynamic_vector temp(_dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			temp[i] = -_data[i];
		return temp;
	}

	template<typename _T>
	dynamic_vector<_T>&& dynamic_vector<_T>::operator-() &&
	{
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] = -_data[i];
		return std::move(*this);
	}

	template<typename _T>
	bool dynamic_vector<_T>::Resize(const unsigned int dimensions)
	{
		stm_assert(dimensions != 0);
		if (dimensions > GetSize())
		{
			_T* newData = new _T[dimensions];
			//memcpy(newData, _data, _dimensions * sizeof(_T));
			std::copy(ucbegin(), ucend(), newData);
			delete[] _data;
			_data = newData;
			_dimensions = dimensions;
			return true;
		}
		return false;
	}

	template<typename _T>
	inline dynamic_vector<_T>& dynamic_vector<_T>::SetAll(const _T& value) & noexcept
	{
		return (std::fill(ubegin(), uend(), value), *this);
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::SetAll(const _T& value) && noexcept
	{
		return (std::fill(ubegin(), uend(), value), std::move(*this));
	}

	template<typename _T> template <typename _FUNCTION>
	dynamic_vector<_T>& dynamic_vector<_T>::ApplyToVector(_FUNCTION&& func) &
	{
		for (auto it = begin(); it != end(); ++it)
			*it = func(*it);
		return *this;
	}

	template<typename _T> template <typename _FUNCTION>
	dynamic_vector<_T>&& dynamic_vector<_T>::ApplyToVector(_FUNCTION&& func) &&
	{
		for (auto it = begin(); it != end(); ++it)
			*it = func(*it);
		return std::move(*this);
	}

	template<typename _T>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator+(const dynamic_vector& other) const&
	{
		return dynamic_vector(*this) += other;
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator+(const dynamic_vector& other) &&
	{
		return std::move(*this += other);
	}

	template<typename _T>
	dynamic_vector<_T>&& dynamic_vector<_T>::operator+(dynamic_vector&& other) const&
	{
		stm_assert(_dimensions == other._dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			other[i] = _data[i] + other[i];
		return std::move(other);
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator+(dynamic_vector&& other)&&
	{
		return std::move(*this += other);
	}

	template<typename _T>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator-(const dynamic_vector& other) const&
	{
		return dynamic_vector(*this) -= other;
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator-(const dynamic_vector& other) &&
	{
		return std::move(*this -= other);
	}

	template<typename _T>
	dynamic_vector<_T>&& dynamic_vector<_T>::operator-(dynamic_vector&& other) const&
	{
		stm_assert(_dimensions == other._dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			other[i] = _data[i] - other[i];
		return std::move(other);
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator-(dynamic_vector&& other) &&
	{
		return std::move(*this -= other);
	}

	template<typename _T>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator*(const dynamic_vector& other) const&
	{
		return dynamic_vector(*this) *= other;
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator*(const dynamic_vector& other) &&
	{
		return std::move(*this *= other);
	}

	template<typename _T>
	dynamic_vector<_T>&& dynamic_vector<_T>::operator*(dynamic_vector&& other) const&
	{
		stm_assert(_dimensions == other._dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			other[i] = _data[i] * other[i];
		return std::move(other);
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator*(dynamic_vector&& other) &&
	{
		return std::move(*this *= other);
	}

	template<typename _T>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator/(const dynamic_vector& other) const&
	{
		return dynamic_vector(*this) /= other;
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator/(const dynamic_vector& other)&&
	{
		return std::move(*this /= other);
	}

	template<typename _T>
	dynamic_vector<_T>&& dynamic_vector<_T>::operator/(dynamic_vector&& other) const&
	{
		stm_assert(_dimensions == other._dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			other[i] = _data[i] / other[i];
		return std::move(other);
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator/(dynamic_vector&& other) &&
	{
		return std::move(*this /= other);
	}

	template <typename _T> template <typename Itr>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator+(const dynamic_vector_view<_T, Itr>& other) const&
	{
		return dynamic_vector(*this) += other;
	}

	template <typename _T> template <typename Itr>
	dynamic_vector<_T>&& dynamic_vector<_T>::operator+(const dynamic_vector_view<_T, Itr>& other) &&
	{
		stm_assert(GetSize() == other.GetSize());
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] += other[i];
		return std::move(*this);
	}

	template <typename _T> template <typename Itr>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator-(const dynamic_vector_view<_T, Itr>& other) const&
	{
		return dynamic_vector(*this) -= other;
	}

	template <typename _T> template <typename Itr>
	dynamic_vector<_T>&& dynamic_vector<_T>::operator-(const dynamic_vector_view<_T, Itr>& other) &&
	{
		stm_assert(GetSize() == other.GetSize());
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] -= other[i];
		return std::move(*this);
	}

	template <typename _T> template <typename Itr>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator*(const dynamic_vector_view<_T, Itr>& other) const&
	{
		return dynamic_vector(*this) *= other;
	}

	template <typename _T> template <typename Itr>
	dynamic_vector<_T>&& dynamic_vector<_T>::operator*(const dynamic_vector_view<_T, Itr>& other) &&
	{
		stm_assert(GetSize() == other.GetSize());
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] *= other[i];
		return std::move(*this);
	}

	template <typename _T> template <typename Itr>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator/(const dynamic_vector_view<_T, Itr>& other) const&
	{
		return dynamic_vector(*this) /= other;
	}

	template <typename _T> template <typename Itr>
	dynamic_vector<_T>&& dynamic_vector<_T>::operator/(const dynamic_vector_view<_T, Itr>& other) &&
	{
		stm_assert(GetSize() == other.GetSize());
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] /= other[i];
		return std::move(*this);
	}

	template<typename _T> template<unsigned int dimensions>
	inline vector<_T, dimensions> dynamic_vector<_T>::operator+(const vector<_T, dimensions>& static_vector) const noexcept
	{
		return static_vector + *this;
	}

	template<typename _T> template<unsigned int dimensions>
	inline vector<_T, dimensions> dynamic_vector<_T>::operator-(const vector<_T, dimensions>& static_vector) const noexcept
	{
		return vector<_T, dimensions>(_data, 0) -= static_vector;
	}

	template<typename _T> template<unsigned int dimensions>
	inline vector<_T, dimensions> dynamic_vector<_T>::operator*(const vector<_T, dimensions>& static_vector) const noexcept
	{
		return static_vector * *this;
	}

	template<typename _T> template<unsigned int dimensions>
	inline vector<_T, dimensions> dynamic_vector<_T>::operator/(const vector<_T, dimensions>& static_vector) const noexcept
	{
		return vector<_T, dimensions>(_data, 0) /= static_vector;
	}

	template<typename _T> template<unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> dynamic_vector<_T>::operator+(const vector_view<_T, _DIM, Itr>& other) const noexcept
	{
		return vector<_T, _DIM>(_data, 0) += other;
	}

	template<typename _T> template<unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> dynamic_vector<_T>::operator-(const vector_view<_T, _DIM, Itr>& other) const noexcept
	{
		return vector<_T, _DIM>(_data, 0) -= other;
	}

	template<typename _T> template<unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> dynamic_vector<_T>::operator*(const vector_view<_T, _DIM, Itr>& other) const noexcept
	{
		return vector<_T, _DIM>(_data, 0) *= other;
	}

	template<typename _T> template<unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> dynamic_vector<_T>::operator/(const vector_view<_T, _DIM, Itr>& other) const noexcept
	{
		return vector<_T, _DIM>(_data, 0) /= other;
	}

	template<typename _T>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator+(const _T& value) const&
	{
		return dynamic_vector(*this) += value;
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator+(const _T& value)&&
	{
		return std::move(*this += value);
	}

	template<typename _T>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator-(const _T& value) const&
	{
		return dynamic_vector(*this) -= value;
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator-(const _T& value) &&
	{
		return std::move(*this -= value);
	}

	template<typename _T>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator*(const _T& value) const&
	{
		return dynamic_vector(*this) *= value;
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator*(const _T& value)&&
	{
		return std::move(*this *= value);
	}

	template<typename _T>
	inline dynamic_vector<_T> dynamic_vector<_T>::operator/(const _T& value) const&
	{
		return dynamic_vector(*this) /= value;
	}

	template<typename _T>
	inline dynamic_vector<_T>&& dynamic_vector<_T>::operator/(const _T& value)&&
	{
		return std::move(*this /= value);
	}

	template<typename _T>
	dynamic_vector<_T>& dynamic_vector<_T>::operator+=(const dynamic_vector& other)
	{
		stm_assert(_dimensions == other._dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] += other[i];
		return *this;
	}

	template<typename _T>
	dynamic_vector<_T>& dynamic_vector<_T>::operator-=(const dynamic_vector& other)
	{
		stm_assert(_dimensions == other._dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] -= other[i];
		return *this;
	}

	template<typename _T>
	dynamic_vector<_T>& dynamic_vector<_T>::operator*=(const dynamic_vector& other)
	{
		stm_assert(_dimensions == other._dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] *= other[i];
		return *this;
	}

	template<typename _T>
	dynamic_vector<_T>& dynamic_vector<_T>::operator/=(const dynamic_vector& other)
	{
		stm_assert(_dimensions == other._dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] /= other[i];
		return *this;
	}
	
	template<typename _T> template<typename Itr>
	dynamic_vector<_T>& dynamic_vector<_T>::operator+=(const dynamic_vector_view<_T, Itr>& other)
	{
		stm_assert(GetSize() == other.GetSize());
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] += other[i];
		return *this;
	}

	template<typename _T> template<typename Itr>
	dynamic_vector<_T>& dynamic_vector<_T>::operator-=(const dynamic_vector_view<_T, Itr>& other)
	{
		stm_assert(GetSize() == other.GetSize());
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] -= other[i];
		return *this;
	}

	template<typename _T> template<typename Itr>
	dynamic_vector<_T>& dynamic_vector<_T>::operator*=(const dynamic_vector_view<_T, Itr>& other)
	{
		stm_assert(GetSize() == other.GetSize());
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] *= other[i];
		return *this;
	}
	
	template<typename _T> template<typename Itr>
	dynamic_vector<_T>& dynamic_vector<_T>::operator/=(const dynamic_vector_view<_T, Itr>& other)
	{
		stm_assert(GetSize() == other.GetSize());
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] /= other[i];
		return *this;
	}

	template<typename _T> template<unsigned int dimensions>
	dynamic_vector<_T>& dynamic_vector<_T>::operator+=(const vector<_T, dimensions>& static_vector) noexcept
	{
		stm_assert(_dimensions == dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] += static_vector[i];
		return *this;
	}

	template<typename _T> template<unsigned int dimensions>
	dynamic_vector<_T>& dynamic_vector<_T>::operator-=(const vector<_T, dimensions>& static_vector) noexcept
	{
		stm_assert(_dimensions == dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] -= static_vector[i];
		return *this;
	}

	template<typename _T> template<unsigned int dimensions>
	dynamic_vector<_T>& dynamic_vector<_T>::operator*=(const vector<_T, dimensions>& static_vector) noexcept
	{
		stm_assert(_dimensions == dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] *= static_vector[i];
		return *this;
	}

	template<typename _T> template<unsigned int dimensions>
	dynamic_vector<_T>& dynamic_vector<_T>::operator/=(const vector<_T, dimensions>& static_vector) noexcept
	{
		stm_assert(_dimensions == dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] /= static_vector[i];
		return *this;
	}

	template<typename _T>
	dynamic_vector<_T>& dynamic_vector<_T>::operator+=(const _T& value) noexcept
	{
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] += value;
		return *this;
	}

	template<typename _T>
	dynamic_vector<_T>& dynamic_vector<_T>::operator-=(const _T& value) noexcept
	{
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] -= value;
		return *this;
	}

	template<typename _T>
	dynamic_vector<_T>& dynamic_vector<_T>::operator*=(const _T& value) noexcept
	{
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] *= value;
		return *this;
	}

	template<typename _T>
	dynamic_vector<_T>& dynamic_vector<_T>::operator/=(const _T& value) noexcept
	{
		for (unsigned int i = 0; i < _dimensions; ++i)
			_data[i] /= value;
		return *this;
	}

	template<typename _T> template<typename O_TYPE>
	dynamic_vector<O_TYPE> dynamic_vector<_T>::Cast() const
	{
		dynamic_vector<O_TYPE> temp(_dimensions);
		for (unsigned int i = 0; i < _dimensions; ++i)
			temp[i] = O_TYPE(_data[i]);
		return temp;
	}

	template<typename _T>
	_T dynamic_vector<_T>::DotProduct(const dynamic_vector& other) const
	{
		stm_assert(_dimensions == other._dimensions)
			_T sum = 0;
		for (unsigned int i = 0; i < _dimensions; ++i)
			sum += _data[i] * other[i];
		return sum;
	}

	template<typename _T> template<unsigned int dimensions>
	_T dynamic_vector<_T>::DotProduct(const vector<_T, dimensions>& other) const noexcept
	{
		stm_assert(_dimensions == dimensions);
		_T sum = 0;
		for (unsigned int i = 0; i < _dimensions; ++i)
			sum += _data[i] * other[i];
		return sum;
	}
}
