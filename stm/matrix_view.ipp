namespace stm
{
    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    constexpr matrix_view<T, ROWS, COLUMNS, Itr>::matrix_view(const matrix<T, ROWS, COLUMNS>& mat) noexcept
        :_iter(mat.cbegin())
    {
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    constexpr matrix_view<T, ROWS, COLUMNS, Itr>::matrix_view(const T (&data)[ROWS * COLUMNS]) noexcept
        :_iter(data)
    {
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator+(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) += other;
    }
    
    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator-(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) -= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator*(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) *= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator/(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) /= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator+(const matrix<T, ROWS, COLUMNS>& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) += other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator-(const matrix<T, ROWS, COLUMNS>& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) -= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator*(const matrix<T, ROWS, COLUMNS>& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) *= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator/(const matrix<T, ROWS, COLUMNS>& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) /= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator+(const dynamic_matrix<T>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(*this) += other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator-(const dynamic_matrix<T>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(*this) -= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator*(const dynamic_matrix<T>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(*this) *= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator/(const dynamic_matrix<T>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(*this) /= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator+(const dynamic_matrix_view<T, Iter>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(*this) += other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator-(const dynamic_matrix_view<T, Iter>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(*this) -= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator*(const dynamic_matrix_view<T, Iter>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(*this) *= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    inline matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator/(const dynamic_matrix_view<T, Iter>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(*this) /= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator+(const T& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) += other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator-(const T& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) -= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator*(const T& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) *= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    matrix<T, ROWS, COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::operator/(const T& other) const noexcept
    {
        return matrix<T, ROWS, COLUMNS>(*this) /= other;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <unsigned int O_COLUMNS, typename Iter>
    matrix<T, ROWS, O_COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::Multiply(const matrix_view<T, COLUMNS, O_COLUMNS, Iter>& other) const noexcept
    {
        matrix<T, ROWS, O_COLUMNS> temp;
		for (unsigned int i = 0; i < ROWS; ++i)
		{
			for (unsigned int k = 0; k < COLUMNS; ++k)
			{
				for (unsigned int j = 0; j < O_COLUMNS; ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
		return temp;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <unsigned int O_COLUMNS>
    matrix<T, ROWS, O_COLUMNS> matrix_view<T, ROWS, COLUMNS, Itr>::Multiply(const matrix<T, COLUMNS, O_COLUMNS>& other) const noexcept
    {
        matrix<T, ROWS, O_COLUMNS> temp;
		for (unsigned int i = 0; i < ROWS; ++i)
		{
			for (unsigned int k = 0; k < COLUMNS; ++k)
			{
				for (unsigned int j = 0; j < O_COLUMNS; ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
        return temp;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    dynamic_matrix<T> matrix_view<T, ROWS, COLUMNS, Itr>::Multiply(const dynamic_matrix_view<T, Iter>& other) const
    {
        stm_assert(GetColumnSize() == other.GetRowSize());
		dynamic_matrix<T> temp(other.GetColumnSize(), GetRowSize());

		for (unsigned int i = 0; i < GetRowSize(); ++i)
		{
			for (unsigned int k = 0; k < GetColumnSize(); ++k)
			{
				for (unsigned int j = 0; j < other.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
        return temp;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    dynamic_matrix<T> matrix_view<T, ROWS, COLUMNS, Itr>::Multiply(const dynamic_matrix<T>& other) const
    {
        stm_assert(GetColumnSize() == other.GetRowSize());
		dynamic_matrix<T> temp(other.GetColumnSize(), GetRowSize());
		for (unsigned int i = 0; i < GetRowSize(); ++i)
		{
			for (unsigned int k = 0; k < GetColumnSize(); ++k)
			{
				for (unsigned int j = 0; j < other.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
        return temp;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    vector<T, ROWS> matrix_view<T, ROWS, COLUMNS, Itr>::Multiply(const vector_view<T, COLUMNS, Iter>& other) const noexcept
    {
        vector<T, ROWS> temp;
		for (unsigned int j = 0; j < COLUMNS; ++j)
		{
			for (unsigned int i = 0; i < ROWS; ++i)
				temp[i] += (*this)[i][j] * other[j];
		}
		return temp;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    vector<T, ROWS> matrix_view<T, ROWS, COLUMNS, Itr>::Multiply(const vector<T, COLUMNS>& other) const noexcept
    {
        vector<T, ROWS> temp;
		for (unsigned int j = 0; j < COLUMNS; ++j)
		{
			for (unsigned int i = 0; i < ROWS; ++i)
				temp[i] += (*this)[i][j] * other[j];
		}
		return temp;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr> template <typename Iter>
    vector<T, ROWS> matrix_view<T, ROWS, COLUMNS, Itr>::Multiply(const dynamic_vector_view<T, Iter>& other) const
    {
        stm_assert(GetColumnSize() == other.GetSize());
        vector<T, ROWS> temp;
		for (unsigned int j = 0; j < COLUMNS; ++j)
		{
			for (unsigned int i = 0; i < ROWS; ++i)
				temp[i] += (*this)[i][j] * other[j];
		}
		return temp;
    }

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    vector<T, ROWS> matrix_view<T, ROWS, COLUMNS, Itr>::Multiply(const dynamic_vector<T>& other) const
    {
        stm_assert(GetColumnSize() == other.GetSize());
        vector<T, ROWS> temp;
		for (unsigned int j = 0; j < COLUMNS; ++j)
		{
			for (unsigned int i = 0; i < ROWS; ++i)
				temp[i] += (*this)[i][j] * other[j];
		}
		return temp;
    }

    template <typename T, typename Itr>
    dynamic_matrix_view<T, Itr>::dynamic_matrix_view() noexcept
        :_iter(nullptr, 0, 0), _rows(0), _columns(0)
    {
    }

    template <typename T, typename Itr>
    dynamic_matrix_view<T, Itr>::dynamic_matrix_view(const dynamic_matrix<T>& matrix)
        :_iter(matrix.GetData(), matrix.GetRowSize(), matrix.GetColumnSize()), _rows(matrix.GetRowSize()), _columns(matrix.GetColumnSize())
    {
    }

    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS>
    dynamic_matrix_view<T, Itr>::dynamic_matrix_view(const matrix<T, ROWS, COLUMNS>&  matrix) noexcept
        :_iter(matrix.GetArray(), matrix.GetRowSize(), matrix.GetColumnSize()), _rows(matrix.GetRowSize()), _columns(matrix.GetColumnSize())
    {
    }

    template <typename T, typename Itr>
    dynamic_matrix_view<T, Itr>::dynamic_matrix_view(const Itr iterator, const unsigned int rows, const unsigned int columns)
        :_iter(iterator), _rows(rows), _columns(columns)
    {
    }
        
    template <typename T, typename Itr> template <typename Iter>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator+(const dynamic_matrix_view<T, Iter>& other) const
    {
        return dynamic_matrix<T>(*this) += other;
    }

    template <typename T, typename Itr> template <typename Iter>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator-(const dynamic_matrix_view<T, Iter>& other) const
    {
        return dynamic_matrix<T>(*this) -= other;
    }

    template <typename T, typename Itr> template <typename Iter>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator*(const dynamic_matrix_view<T, Iter>& other) const
    {
        return dynamic_matrix<T>(*this) *= other;
    }

    template <typename T, typename Itr> template <typename Iter>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator/(const dynamic_matrix_view<T, Iter>& other) const
    {
        return dynamic_matrix<T>(*this) /= other;
    }

    template <typename T, typename Itr>   
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator+(const dynamic_matrix<T>& other) const
    {
        return dynamic_matrix<T>(*this) += other;
    }

    template <typename T, typename Itr>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator-(const dynamic_matrix<T>& other) const
    {
        return dynamic_matrix<T>(*this) -= other;
    }

    template <typename T, typename Itr>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator*(const dynamic_matrix<T>& other) const
    {
        return dynamic_matrix<T>(*this) *= other;
    }

    template <typename T, typename Itr>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator/(const dynamic_matrix<T>& other) const
    {
        return dynamic_matrix<T>(*this) /= other;
    }
        
    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS>
    inline matrix<T, ROWS, COLUMNS> dynamic_matrix_view<T, Itr>::operator+(const matrix<T, ROWS, COLUMNS>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(cbegin(), cend()) += other;
    }

    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS>
    inline matrix<T, ROWS, COLUMNS> dynamic_matrix_view<T, Itr>::operator-(const matrix<T, ROWS, COLUMNS>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(cbegin(), cend()) -= other;
    }

    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS>
    inline matrix<T, ROWS, COLUMNS> dynamic_matrix_view<T, Itr>::operator*(const matrix<T, ROWS, COLUMNS>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(cbegin(), cend()) *= other;
    }

    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS>
    inline matrix<T, ROWS, COLUMNS> dynamic_matrix_view<T, Itr>::operator/(const matrix<T, ROWS, COLUMNS>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(cbegin(), cend()) /= other;
    }

    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS, typename Iter>
    inline matrix<T, ROWS, COLUMNS> dynamic_matrix_view<T, Itr>::operator+(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(cbegin(), cend()) += other;
    }

    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS, typename Iter>
    inline matrix<T, ROWS, COLUMNS> dynamic_matrix_view<T, Itr>::operator-(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(cbegin(), cend()) -= other;
    }

    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS, typename Iter>
    inline matrix<T, ROWS, COLUMNS> dynamic_matrix_view<T, Itr>::operator*(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(cbegin(), cend()) *= other;
    }

    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS, typename Iter>
    inline matrix<T, ROWS, COLUMNS> dynamic_matrix_view<T, Itr>::operator/(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const
    {
        return matrix<T, ROWS, COLUMNS>(cbegin(), cend()) /= other;
    }

    template <typename T, typename Itr>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator+(const T& other) const
    {
        return dynamic_matrix<T>(*this) += other;
    }

    template <typename T, typename Itr>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator-(const T& other) const
    {
        return dynamic_matrix<T>(*this) -= other;
    }

    template <typename T, typename Itr>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator*(const T& other) const
    {
        return dynamic_matrix<T>(*this) *= other;
    }

    template <typename T, typename Itr>
    inline dynamic_matrix<T> dynamic_matrix_view<T, Itr>::operator/(const T& other) const
    {
        return dynamic_matrix<T>(*this) /= other;
    }

    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS, typename Iter>
    dynamic_matrix<T> dynamic_matrix_view<T, Itr>::Multiply(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const
    {
        stm_assert(GetColumnSize() == other.GetRowSize());
		dynamic_matrix<T> temp(other.GetColumnSize(), GetRowSize());

		for (unsigned int i = 0; i < GetRowSize(); ++i)
		{
			for (unsigned int k = 0; k < GetColumnSize(); ++k)
			{
				for (unsigned int j = 0; j < other.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
        return temp;
    }

    template <typename T, typename Itr> template <unsigned int ROWS, unsigned int COLUMNS>
    dynamic_matrix<T> dynamic_matrix_view<T, Itr>::Multiply(const matrix<T, ROWS, COLUMNS>& other) const
    {
        stm_assert(GetColumnSize() == other.GetRowSize());
		dynamic_matrix<T> temp(other.GetColumnSize(), GetRowSize());

		for (unsigned int i = 0; i < GetRowSize(); ++i)
		{
			for (unsigned int k = 0; k < GetColumnSize(); ++k)
			{
				for (unsigned int j = 0; j < other.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
        return temp;
    }

    template <typename T, typename Itr> template <typename Iter>
    dynamic_matrix<T> dynamic_matrix_view<T, Itr>::Multiply(const dynamic_matrix_view<T, Iter>& other) const
    {
        stm_assert(GetColumnSize() == other.GetRowSize());
		dynamic_matrix<T> temp(other.GetColumnSize(), GetRowSize());

		for (unsigned int i = 0; i < GetRowSize(); ++i)
		{
			for (unsigned int k = 0; k < GetColumnSize(); ++k)
			{
				for (unsigned int j = 0; j < other.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
        return temp;
    }

    template <typename T, typename Itr>
    dynamic_matrix<T> dynamic_matrix_view<T, Itr>::Multiply(const dynamic_matrix<T>& other) const
    {
        stm_assert(GetColumnSize() == other.GetRowSize());
		dynamic_matrix<T> temp(other.GetColumnSize(), GetRowSize());

		for (unsigned int i = 0; i < GetRowSize(); ++i)
		{
			for (unsigned int k = 0; k < GetColumnSize(); ++k)
			{
				for (unsigned int j = 0; j < other.GetColumnSize(); ++j)
				{
					temp[i][j] += (*this)[i][k] * other[k][j];
				}
			}
		}
        return temp;
    }

    template <typename T, typename Itr> template <unsigned int DIM, typename Iter>
    dynamic_vector<T> dynamic_matrix_view<T, Itr>::Multiply(const vector_view<T, DIM, Iter>& other) const
    {
        stm_assert(GetColumnSize() == other.GetSize());
        dynamic_vector<T> temp(GetRowSize());
		for (unsigned int j = 0; j < GetColumnSize(); ++j)
		{
			for (unsigned int i = 0; i < GetRowSize(); ++i)
				temp[i] += (*this)[i][j] * other[j];
		}
		return temp;
    }

    template <typename T, typename Itr> template <unsigned int DIM, typename Iter>
    dynamic_vector<T> dynamic_matrix_view<T, Itr>::Multiply(const vector<T, DIM>& other) const
    {
        stm_assert(GetColumnSize() == other.GetSize());
        dynamic_vector<T> temp(GetRowSize());
		for (unsigned int j = 0; j < GetColumnSize(); ++j)
		{
			for (unsigned int i = 0; i < GetRowSize(); ++i)
				temp[i] += (*this)[i][j] * other[j];
		}
		return temp;
    }

    template <typename T, typename Itr> template <typename Iter>
    dynamic_vector<T> dynamic_matrix_view<T, Itr>::Multiply(const dynamic_vector_view<T, Iter>& other) const
    {
        stm_assert(GetColumnSize() == other.GetSize());
        dynamic_vector<T> temp(GetRowSize());
		for (unsigned int j = 0; j < GetColumnSize(); ++j)
		{
			for (unsigned int i = 0; i < GetRowSize(); ++i)
				temp[i] += (*this)[i][j] * other[j];
		}
		return temp;
    }

    template <typename T, typename Itr>
    dynamic_vector<T> dynamic_matrix_view<T, Itr>::Multiply(const dynamic_vector<T>& other) const
    {
        stm_assert(GetColumnSize() == other.GetSize());
        dynamic_vector<T> temp(GetRowSize());
		for (unsigned int j = 0; j < GetColumnSize(); ++j)
		{
			for (unsigned int i = 0; i < GetRowSize(); ++i)
				temp[i] += (*this)[i][j] * other[j];
		}
		return temp;
    }
}