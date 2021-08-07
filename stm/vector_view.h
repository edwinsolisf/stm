#ifndef stm_vector_view_h
#define stm_vector_view_h

#include "vector.h"
#include "dynamic_vector.h"

namespace stm
{
	template <typename _T, unsigned int _DIM, typename Itr>
	class vector_view
	{
	public:
		using ElemType = _T;
		using const_iterator = Itr;

		constexpr vector_view() = delete;
		constexpr vector_view(const vector_view&) noexcept = default;
		explicit constexpr vector_view(const vector<_T, _DIM>& vec) noexcept;
		constexpr vector_view(const _T (&data)[_DIM]) noexcept;
		
		vector_view(vector<_T, _DIM>&&) = delete;

		vector_view& operator=(const vector_view&) = delete;

		template <typename Iter>
		vector<_T, _DIM> operator+(const vector_view<_T, _DIM, Iter>& other) const noexcept;
		template <typename Iter>
		vector<_T, _DIM> operator-(const vector_view<_T, _DIM, Iter>& other) const noexcept;
		template <typename Iter>
		vector<_T, _DIM> operator*(const vector_view<_T, _DIM, Iter>& other) const noexcept;
		template <typename Iter>
		vector<_T, _DIM> operator/(const vector_view<_T, _DIM, Iter>& other) const noexcept;

		vector<_T, _DIM> operator+(const vector<_T, _DIM>& other) const noexcept;
		vector<_T, _DIM> operator-(const vector<_T, _DIM>& other) const noexcept;
		vector<_T, _DIM> operator*(const vector<_T, _DIM>& other) const noexcept;
		vector<_T, _DIM> operator/(const vector<_T, _DIM>& other) const noexcept;

		vector<_T, _DIM> operator+(const _T& other) const noexcept;
		vector<_T, _DIM> operator-(const _T& other) const noexcept;
		vector<_T, _DIM> operator*(const _T& other) const noexcept;
		vector<_T, _DIM> operator/(const _T& other) const noexcept;

		vector<_T, _DIM> operator+(const dynamic_vector<_T>& other) const;
		vector<_T, _DIM> operator-(const dynamic_vector<_T>& other) const;
		vector<_T, _DIM> operator*(const dynamic_vector<_T>& other) const;
		vector<_T, _DIM> operator/(const dynamic_vector<_T>& other) const;

		template <typename Iter>
		vector<_T, _DIM> operator+(const dynamic_vector_view<_T, Iter>& other) const;
		template <typename Iter>
		vector<_T, _DIM> operator-(const dynamic_vector_view<_T, Iter>& other) const;
		template <typename Iter>
		vector<_T, _DIM> operator*(const dynamic_vector_view<_T, Iter>& other) const;
		template <typename Iter>
		vector<_T, _DIM> operator/(const dynamic_vector_view<_T, Iter>& other) const;

		constexpr const _T& operator[](const unsigned int index) const noexcept { stm_assert(index < _DIM); return begin()[index]; }

		constexpr const _T* GetData() const noexcept { return _data; }
		constexpr unsigned int GetSize() const noexcept { return _DIM; }

		vector<_T, _DIM> GetVector() const noexcept { return vector<_T, _DIM>(GetData(), 0); }

		constexpr const_iterator begin() const noexcept { return cbegin(); }
		constexpr const_iterator end()   const noexcept { return cend(); }

		constexpr const_iterator cbegin() const noexcept { return const_iterator(_data); }
		constexpr const_iterator cend()   const noexcept { return const_iterator(_data) + _DIM; }

		_T Magnitude() const noexcept
		{
			return ::sqrt(DotProduct(*this));
		}

		vector<_T, _DIM> UnitVector() const noexcept
		{
			return (*this) / Magnitude();
		}

		template <typename Iter>
		_T DotProduct(const vector_view<_T, _DIM, Iter>& other)             const noexcept;
		_T DotProduct(const vector<_T, _DIM>& other)        const noexcept;
		_T DotProduct(const dynamic_vector<_T>& other)      const;
		template <typename Iter>
		_T DotProduct(const dynamic_vector_view<_T, Iter>& other) const;

	private:
		//const _T (&_data)[_DIM];
		const const_iterator _data;
	};

	template <typename _T, typename Itr>
	class dynamic_vector_view
	{
	public:
		using ElemType = _T;
		using const_iterator = Itr;

		dynamic_vector_view() noexcept;
		dynamic_vector_view(const dynamic_vector_view&) noexcept = default;

		explicit dynamic_vector_view(const dynamic_vector<_T>& vec);
		dynamic_vector_view(dynamic_vector<_T>&&) = delete;

		template <unsigned int _DIM>
		explicit dynamic_vector_view(const vector<_T, _DIM>&) noexcept;

		template <unsigned int _DIM>
		dynamic_vector_view(vector<_T, _DIM>&&) = delete;
		
		template <unsigned int _DIM, typename Iter>
		dynamic_vector_view(const vector_view<_T, _DIM, Iter>&) noexcept;

		dynamic_vector_view(const Itr begin, const Itr end) noexcept;

		dynamic_vector_view& operator=(const dynamic_vector_view&) = delete;

		template <typename Iter>
		dynamic_vector<_T> operator+(const dynamic_vector_view<_T, Iter>& other) const;
		template <typename Iter>
		dynamic_vector<_T> operator-(const dynamic_vector_view<_T, Iter>& other) const;
		template <typename Iter>
		dynamic_vector<_T> operator*(const dynamic_vector_view<_T, Iter>& other) const;
		template <typename Iter>
		dynamic_vector<_T> operator/(const dynamic_vector_view<_T, Iter>& other) const;

		dynamic_vector<_T> operator+(const dynamic_vector<_T>& other) const;
		dynamic_vector<_T> operator-(const dynamic_vector<_T>& other) const;
		dynamic_vector<_T> operator*(const dynamic_vector<_T>& other) const;
		dynamic_vector<_T> operator/(const dynamic_vector<_T>& other) const;

		dynamic_vector<_T> operator+(dynamic_vector<_T>&& other) const;
		dynamic_vector<_T> operator-(dynamic_vector<_T>&& other) const;
		dynamic_vector<_T> operator*(dynamic_vector<_T>&& other) const;
		dynamic_vector<_T> operator/(dynamic_vector<_T>&& other) const;

		dynamic_vector<_T> operator+(const _T& other) const noexcept;
		dynamic_vector<_T> operator-(const _T& other) const noexcept;
		dynamic_vector<_T> operator*(const _T& other) const noexcept;
		dynamic_vector<_T> operator/(const _T& other) const noexcept;

		template <unsigned int _DIM, typename Iter>
		vector<_T, _DIM> operator+(const vector_view<_T, _DIM, Iter>& other) const noexcept;
		template <unsigned int _DIM, typename Iter>
		vector<_T, _DIM> operator-(const vector_view<_T, _DIM, Iter>& other) const noexcept;
		template <unsigned int _DIM, typename Iter>
		vector<_T, _DIM> operator*(const vector_view<_T, _DIM, Iter>& other) const noexcept;
		template <unsigned int _DIM, typename Iter>
		vector<_T, _DIM> operator/(const vector_view<_T, _DIM, Iter>& other) const noexcept;

		template <unsigned int _DIM>
		vector<_T, _DIM> operator+(const vector<_T, _DIM>& other) const noexcept;
		template <unsigned int _DIM>
		vector<_T, _DIM> operator-(const vector<_T, _DIM>& other) const noexcept;
		template <unsigned int _DIM>
		vector<_T, _DIM> operator*(const vector<_T, _DIM>& other) const noexcept;
		template <unsigned int _DIM>
		vector<_T, _DIM> operator/(const vector<_T, _DIM>& other) const noexcept;


		constexpr const _T& operator[](const unsigned int index) const noexcept { stm_assert(index < _size || _data != nullptr); return _data[index]; }

		constexpr const _T* GetData() const noexcept { return _data; }
		constexpr unsigned int GetSize() const noexcept { return _size; }

		dynamic_vector<_T> GetVector() const { return dynamic_vector<_T>(_size, _data); }

		constexpr const_iterator begin() const noexcept { return cbegin(); }
		constexpr const_iterator end()   const noexcept { return cend(); }

		constexpr const_iterator cbegin() const noexcept { return _data; }
		constexpr const_iterator cend()   const noexcept { return cbegin() + _size; }

		_T Magnitude() const noexcept
		{
			return ::sqrt(DotProduct(*this));
		}

		dynamic_vector<_T> UnitVector() const noexcept
		{
			return (*this) / Magnitude();
		}

		template<unsigned int _DIM>
		_T DotProduct(const vector<_T, _DIM>& other)      const noexcept;

		template<unsigned int _DIM, typename Iter>
		_T DotProduct(const vector_view<_T, _DIM, Iter>& other) const noexcept;

		_T DotProduct(const dynamic_vector<_T>& other)      const;
		template <typename Iter>
		_T DotProduct(const dynamic_vector_view<_T, Iter>& other)     const;

	private:
		const _T* const _data;
		//const Itr _data;
		const unsigned int _size;
	};
}

#include "vector_view.ipp"

#endif /* stm_vector_view_h */
