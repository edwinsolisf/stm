namespace stm
{
    template <typename _T, unsigned int _DIM, typename Itr>
	constexpr vector_view<_T, _DIM, Itr>::vector_view(const vector<_T, _DIM>& vec) noexcept
		:_data(vec.GetArray())
	{
	}

    template <typename _T, unsigned int _DIM, typename Itr>
    constexpr vector_view<_T, _DIM, Itr>::vector_view(const _T (&data)[_DIM]) noexcept
        :_data(data)
    {
    }

    template <typename _T, unsigned int _DIM, typename Itr> template <typename Iter>
    inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator+(const vector_view<_T, _DIM, Iter>& other) const noexcept
    {
        return vector<_T,_DIM>(*this) += other;
    }

    template <typename _T, unsigned int _DIM, typename Itr> template <typename Iter>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator-(const vector_view<_T, _DIM, Iter>& other) const noexcept
    {
        return vector<_T,_DIM>(*this) -= other;
    }
	
    template <typename _T, unsigned int _DIM, typename Itr> template <typename Iter>
    inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator*(const vector_view<_T, _DIM, Iter>& other) const noexcept
    {
        return vector<_T,_DIM>(*this) *= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr> template <typename Iter>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator/(const vector_view<_T, _DIM, Iter>& other) const noexcept
    {
        return vector<_T,_DIM>(*this) /= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator+(const vector<_T, _DIM>& other) const noexcept
    {
        return vector<_T, _DIM>(*this) += other;
    }
	
    template <typename _T, unsigned int _DIM, typename Itr>
    inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator-(const vector<_T, _DIM>& other) const noexcept
    {
        return vector<_T, _DIM>(*this) -= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator*(const vector<_T, _DIM>& other) const noexcept
    {
        return vector<_T, _DIM>(*this) *= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator/(const vector<_T, _DIM>& other) const noexcept
    {
        return vector<_T, _DIM>(*this) /= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator+(const _T& other) const noexcept
    {
        return vector<_T,_DIM>(*this) += other;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator-(const _T& other) const noexcept
    {
        return vector<_T,_DIM>(*this) -= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator*(const _T& other) const noexcept
    {
        return vector<_T,_DIM>(*this) *= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator/(const _T& other) const noexcept
    {
        return vector<_T,_DIM>(*this) /= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator+(const dynamic_vector<_T>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(*this) += other;
    }
    
    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator-(const dynamic_vector<_T>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(*this) -= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator*(const dynamic_vector<_T>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(*this) *= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator/(const dynamic_vector<_T>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(*this) /= other;
    }
	
    template <typename _T, unsigned int _DIM, typename Itr> template<typename Iter>
    inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator+(const dynamic_vector_view<_T, Iter>& other) const
    {
        return vector<_T,_DIM>(*this) += other;
    }

    template <typename _T, unsigned int _DIM, typename Itr> template<typename Iter>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator-(const dynamic_vector_view<_T, Iter>& other) const
    {
        return vector<_T,_DIM>(*this) -= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr> template<typename Iter>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator*(const dynamic_vector_view<_T, Iter>& other) const
    {
        return vector<_T,_DIM>(*this) *= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr> template<typename Iter>
	inline vector<_T, _DIM> vector_view<_T, _DIM, Itr>::operator/(const dynamic_vector_view<_T, Iter>& other) const
    {
        return vector<_T,_DIM>(*this) /= other;
    }

    template <typename _T, unsigned int _DIM, typename Itr> template <typename Iter>
    _T vector_view<_T, _DIM, Itr>::DotProduct(const vector_view<_T, _DIM, Iter>& other) const noexcept
    {
        _T sum = 0;
        for (unsigned int i = 0; i < _DIM; ++i)
            sum += _data[i] * other[i];
        return sum;
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline _T vector_view<_T, _DIM, Itr>::DotProduct(const vector<_T, _DIM>& other) const noexcept
    {
        return other.DotProduct(*this);
    }

    template <typename _T, unsigned int _DIM, typename Itr>
	inline _T vector_view<_T, _DIM, Itr>::DotProduct(const dynamic_vector<_T>& other) const
    {
        return other.DotProduct(*this);
    }

    template <typename _T, unsigned int _DIM, typename Itr> template <typename Iter>
    _T vector_view<_T, _DIM, Itr>::DotProduct(const dynamic_vector_view<_T, Iter>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        _T sum = 0;
        for (unsigned int i = 0; i < _DIM; ++i)
            sum += _data[i] * other[i];
        return sum;
    }

    template <typename _T, typename Itr>
    dynamic_vector_view<_T, Itr>::dynamic_vector_view() noexcept
		:_data(nullptr), _size(0)
	{
	}

    template <typename _T, typename Itr>
	dynamic_vector_view<_T, Itr>::dynamic_vector_view(const dynamic_vector<_T>& vec)
		:_data(vec.GetData()), _size(vec.GetSize())
	{
	}

    template <typename _T, typename Itr> template <unsigned int _DIM>
	dynamic_vector_view<_T, Itr>::dynamic_vector_view(const vector<_T, _DIM>& vec) noexcept
        :_data(vec.GetData()), _size(_DIM)
    {
    }

    template <typename _T, typename Itr> template <unsigned int _DIM, typename Iter>
    dynamic_vector_view<_T, Itr>::dynamic_vector_view(const vector_view<_T, _DIM, Iter>& view) noexcept
        :_data(view.GetData()), _size(_DIM)
    {
    }

    template <typename _T, typename Itr>
	dynamic_vector_view<_T, Itr>::dynamic_vector_view(const Itr begin, const Itr end) noexcept
		:_data(begin), _size((end - begin)/sizeof(_T))
	{
		stm_assert((const _T*)begin != nullptr || (const _T*)end != nullptr);
	}

    template <typename _T, typename Itr> template <typename Iter>
    inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator+(const dynamic_vector_view<_T, Iter>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return dynamic_vector<_T>(*this) += other;
    }

    template <typename _T, typename Itr> template <typename Iter>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator-(const dynamic_vector_view<_T, Iter>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return dynamic_vector<_T>(*this) -= other;
    }

    template <typename _T, typename Itr> template <typename Iter>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator*(const dynamic_vector_view<_T, Iter>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return dynamic_vector<_T>(*this) *= other;
    }

    template <typename _T, typename Itr> template <typename Iter>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator/(const dynamic_vector_view<_T, Iter>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return dynamic_vector<_T>(*this) /= other;
    }

    template <typename _T, typename Itr>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator+(const dynamic_vector<_T>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return dynamic_vector<_T>(*this) += other;
    }

    template <typename _T, typename Itr>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator-(const dynamic_vector<_T>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return dynamic_vector<_T>(*this) -= other;
    }

    template <typename _T, typename Itr>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator*(const dynamic_vector<_T>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return dynamic_vector<_T>(*this) *= other;
    }

    template <typename _T, typename Itr>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator/(const dynamic_vector<_T>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        return dynamic_vector<_T>(*this) /= other;
    }

    template <typename _T, typename Itr>
    dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator+(dynamic_vector<_T>&& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        for (unsigned int i = 0; i < _size; ++i)
            other[i] = (*this)[i] + other[i];
        return std::move(other);
    }

    template <typename _T, typename Itr>
	dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator-(dynamic_vector<_T>&& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        for (unsigned int i = 0; i < _size; ++i)
            other[i] = (*this)[i] - other[i];
        return std::move(other);
    }

    template <typename _T, typename Itr>
	dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator*(dynamic_vector<_T>&& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        for (unsigned int i = 0; i < _size; ++i)
            other[i] = (*this)[i] * other[i];
        return std::move(other);
    }

    template <typename _T, typename Itr>
	dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator/(dynamic_vector<_T>&& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        for (unsigned int i = 0; i < _size; ++i)
            other[i] = (*this)[i] / other[i];
        return std::move(other);
    }

    template <typename _T, typename Itr>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator+(const _T& other) const noexcept
    {
        return dynamic_vector<_T>(*this) += other;
    }

    template <typename _T, typename Itr>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator-(const _T& other) const noexcept
    {
        return dynamic_vector<_T>(*this) -= other;
    }

    template <typename _T, typename Itr>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator*(const _T& other) const noexcept
    {
        return dynamic_vector<_T>(*this) *= other;
    }

    template <typename _T, typename Itr>
	inline dynamic_vector<_T> dynamic_vector_view<_T, Itr>::operator/(const _T& other) const noexcept
    {
        return dynamic_vector<_T>(*this) /= other;
    }

    template <typename _T, typename Itr> template <unsigned int _DIM, typename Iter>
	inline vector<_T, _DIM> dynamic_vector_view<_T, Itr>::operator+(const vector_view<_T, _DIM, Iter>& other) const noexcept
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(cbegin(), cend()) += other;
    }

    template <typename _T, typename Itr> template <unsigned int _DIM, typename Iter>
	inline vector<_T, _DIM> dynamic_vector_view<_T, Itr>::operator-(const vector_view<_T, _DIM, Iter>& other) const noexcept
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(cbegin(), cend()) -= other;
    }

    template <typename _T, typename Itr> template <unsigned int _DIM, typename Iter>
	inline vector<_T, _DIM> dynamic_vector_view<_T, Itr>::operator*(const vector_view<_T, _DIM, Iter>& other) const noexcept
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(cbegin(), cend()) *= other;
    }

    template <typename _T, typename Itr> template <unsigned int _DIM, typename Iter>
	inline vector<_T, _DIM> dynamic_vector_view<_T, Itr>::operator/(const vector_view<_T, _DIM, Iter>& other) const noexcept
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(cbegin(), cend()) /= other;
    }

    template <typename _T, typename Itr> template <unsigned int _DIM>
	inline vector<_T, _DIM> dynamic_vector_view<_T, Itr>::operator+(const vector<_T, _DIM>& other) const noexcept
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(cbegin(), cend()) += other;
    }

    template <typename _T, typename Itr> template <unsigned int _DIM>
	inline vector<_T, _DIM> dynamic_vector_view<_T, Itr>::operator-(const vector<_T, _DIM>& other) const noexcept
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(cbegin(), cend()) -= other;
    }

    template <typename _T, typename Itr> template <unsigned int _DIM>
	inline vector<_T, _DIM> dynamic_vector_view<_T, Itr>::operator*(const vector<_T, _DIM>& other) const noexcept
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(cbegin(), cend()) *= other;
    }

    template <typename _T, typename Itr> template <unsigned int _DIM>
	inline vector<_T, _DIM> dynamic_vector_view<_T, Itr>::operator/(const vector<_T, _DIM>& other) const noexcept
    {
        stm_assert(GetSize() == other.GetSize());
        return vector<_T, _DIM>(cbegin(), cend()) /= other;
    }

    template <typename _T, typename Itr> template <unsigned int _DIM>
	inline _T dynamic_vector_view<_T, Itr>::DotProduct(const vector<_T, _DIM>& other) const noexcept
    {
        return other.DotProduct(*this);
    }
	
    template <typename _T, typename Itr> template <unsigned int _DIM, typename Iter>
	inline _T dynamic_vector_view<_T, Itr>::DotProduct(const vector_view<_T, _DIM, Iter>& other) const noexcept
    {
        return other.DotProduct(*this);
    }
    
    template <typename _T, typename Itr>
	inline _T dynamic_vector_view<_T, Itr>::DotProduct(const dynamic_vector<_T>& other) const
    {
        return other.DotProduct(*this);
    }
    
    template <typename _T, typename Itr> template <typename Iter>
	_T dynamic_vector_view<_T, Itr>::DotProduct(const dynamic_vector_view<_T, Iter>& other) const
    {
        stm_assert(GetSize() == other.GetSize());
        _T sum = 0;
        for (unsigned int i = 0; i < _size; ++i)
            sum += _data[i] * other[i];
        return sum;
    }
}