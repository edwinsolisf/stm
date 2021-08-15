#ifndef stm_matrix_operations_h
#define stm_matrix_operations_h

#include <cmath>

namespace stm
{
	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	class matrix;

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	struct constexpr_matrix;

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS, typename Itr>
	class matrix_view;

	template<typename _TYPE>
	class dynamic_matrix;

	template<typename _TYPE, typename Itr>
	class dynamic_matrix_view;

	template<typename _TYPE, unsigned int _SIZE>
	class vector;

	template<typename _TYPE>
	class dynamic_vector;

	template<typename _TYPE, unsigned int _DIM, typename Itr>
	class vector_view;

	template<typename _TYPE, typename Itr>
	class dynamic_vector_view;

	template <typename _ELEM_TYPE1, typename _ELEM_TYPE2>
	inline auto multiply(_ELEM_TYPE1&& this_elem, _ELEM_TYPE2&& other_elem) -> 
		decltype(std::forward<_ELEM_TYPE1>(this_elem).Multiply(std::forward<_ELEM_TYPE2>(other_elem)))
	{
		return std::forward<_ELEM_TYPE1>(this_elem).Multiply(std::forward<_ELEM_TYPE2>(other_elem));
	}

	template <typename _ELEM_TYPE1>
	inline auto transpose(_ELEM_TYPE1&& this_elem) ->
		decltype(std::forward<_ELEM_TYPE1>(this_elem).Transpose())
	{
		return std::forward<_ELEM_TYPE1>(this_elem).Transpose();
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS> pow(const matrix<_TYPE, _ROWS, _COLUMNS>& mat, const unsigned int power)
	{
		static_assert(_ROWS == _COLUMNS, "Error: non-square matrix");
		switch (power)
		{
		case 2:
			return multiply(mat, mat);
			break;
		case 3:
			return multiply(mat, multiply(mat, mat));
			break;
		default:
		{
			if (power % 2)
				return multiply(mat, multiply(pow(mat, power / 2), pow(mat, power / 2)));
			else
				return multiply(pow(mat, power / 2), pow(mat, power / 2));
			break;
		}
		}
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix_view<_TYPE, _COLUMNS, _ROWS, typename matrix<_TYPE, _ROWS, _COLUMNS>::column_const_iterator> transposeView(const matrix<_TYPE, _ROWS, _COLUMNS>& mat) noexcept
	{
		return mat.GetTranposeView();
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	_TYPE determinant(const matrix<_TYPE, _ROWS, _COLUMNS>& mat)
	{
		static_assert(_ROWS == _COLUMNS, "Error: non-square matrix");

		_TYPE sum = 0;
		for (unsigned int i = 0; i < _ROWS; ++i)
			sum += (i % 2) ? -(determinant(mat.Minor(0, i)) * mat[0][i]) : (determinant(mat.Minor(0, i)) * mat[0][i]);
		return sum;
	}
	
	template<typename _TYPE>
	constexpr inline _TYPE determinant(const matrix<_TYPE, 2, 2>& mat) noexcept
	{
		return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
	}

	template<typename _TYPE>
	inline matrix<_TYPE, 2, 2> sqrt(const matrix<_TYPE, 2, 2>& mat) noexcept
	{
		_TYPE temp = std::sqrt(determinant(mat));
		return matrix<_TYPE, 2, 2>(mat[0][0] + temp, mat[0][1], mat[1][0], mat[1][1] + temp) / (std::sqrt(temp + 2 * (mat[0][0] + mat[1][1])));
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS> inverse(const matrix<_TYPE, _ROWS, _COLUMNS>& mat)
	{
		static_assert(_ROWS == _COLUMNS, "Error: non-square matrix");
		matrix<_TYPE, _ROWS, _COLUMNS> temp;
		_TYPE det = 0;

		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int j = 0; j < _COLUMNS; ++j)
				temp[0][(i * _COLUMNS) + j] = (((i + j) % 2) ? -(determinant(mat.Minor(i, j))) : (determinant(mat.Minor(i, j))));
		}

		for (unsigned int k = 0; k < _COLUMNS; ++k)
			det += temp[0][k] * mat[0][k];

		return transpose(temp) / det;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS> cofactorMatrix(const matrix<_TYPE, _ROWS, _COLUMNS>& mat)
	{
		static_assert(_ROWS == _COLUMNS, "Error: non-square matrix");
		matrix<_TYPE, _ROWS, _COLUMNS> temp;

		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int j = 0; j < _COLUMNS; ++j)
				temp[0][(i * _COLUMNS) + j] = (((i + j) % 2) ? -(determinant(mat.Minor(i, j))) : (determinant(mat.Minor(i, j))));
		}
		return temp;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline matrix<_TYPE, _ROWS, _COLUMNS> adjugate(const matrix<_TYPE, _ROWS, _COLUMNS>& mat)
	{
		return transpose(cofactorMatrix(mat));
	}

	template<typename _TYPE, unsigned int _DIM>
	inline matrix<_TYPE, 1, _DIM> toRowMatrix(const vector<_TYPE, _DIM>& vec) noexcept
	{
		return matrix<_TYPE, 1, _DIM>(vec.GetArray());
	}

	template<typename _TYPE, unsigned int _DIM, typename Itr>
	inline matrix<_TYPE, 1, _DIM> toRowMatrix(const vector_view<_TYPE, _DIM, Itr>& vec) noexcept
	{
		return matrix<_TYPE, 1, _DIM>(vec.GetData(), 0);
	}

	template <typename _TYPE, unsigned int _DIM>
	//inline matrix_view<_TYPE, 1, _DIM, typename vector<_TYPE, _DIM>::const_iterator> toRowMatrixView(const vector<_TYPE, _DIM>& vec) noexcept
	inline matrix_view<_TYPE, 1, _DIM, typename matrix<_TYPE, 1, _DIM>::const_iterator> toRowMatrixView(const vector<_TYPE, _DIM>& vec) noexcept
	{
		return matrix_view<_TYPE, 1, _DIM, typename matrix<_TYPE, 1, _DIM>::const_iterator>(vec.GetArray());
	}

	template<typename _TYPE, unsigned int _DIM>
	inline matrix<_TYPE, _DIM, 1> toColumnMatrix(const vector<_TYPE, _DIM>& vec) noexcept
	{
		return matrix<_TYPE, _DIM, 1>(vec.GetArray());
	}

	template<typename _TYPE, unsigned int _DIM, typename Itr>
	inline matrix<_TYPE, _DIM, 1> toColumnMatrix(const vector_view<_TYPE, _DIM, Itr>& vec) noexcept
	{
		return matrix<_TYPE, _DIM, 1>(vec.GetData(), 0);
	}

	template <typename _TYPE, unsigned int _DIM>
	//inline matrix_view<_TYPE, _DIM, 1, typename vector<_TYPE, _DIM>::const_iterator> toColumnMatrixView(const vector<_TYPE, _DIM>& vec) noexcept
	inline matrix_view<_TYPE, _DIM, 1, typename matrix<_TYPE, _DIM, 1>::const_iterator> toColumnMatrixView(const vector<_TYPE, _DIM>& vec) noexcept
	{
		return matrix_view<_TYPE, _DIM, 1, typename matrix<_TYPE, _DIM, 1>::const_iterator>(vec.GetArray());
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline vector<_TYPE, _ROWS * _COLUMNS> toRowVector(const matrix<_TYPE, _ROWS, _COLUMNS>& mat) noexcept
	{
		return vector<_TYPE, _ROWS * _COLUMNS>(mat.GetArray());
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline vector_view<_TYPE, _ROWS* _COLUMNS, typename matrix<_TYPE, _ROWS, _COLUMNS>::row_const_iterator> toRowVectorView(const matrix<_TYPE, _ROWS, _COLUMNS>& mat) noexcept
	{
		return vector_view<_TYPE, _ROWS * _COLUMNS, typename matrix<_TYPE, _ROWS, _COLUMNS>::row_const_iterator>(mat.GetArray());
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline vector<_TYPE, _ROWS * _COLUMNS> toColumnVector(const matrix<_TYPE, _ROWS, _COLUMNS>& mat) noexcept
	{
		return vector<_TYPE, _ROWS * _COLUMNS>(mat.Transpose().GetArray());
	}

	template <typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline constexpr vector_view<_TYPE, _ROWS * _COLUMNS, typename matrix<_TYPE, _ROWS, _COLUMNS>::column_const_iterator> toColumnVectorView(const matrix<_TYPE, _ROWS, _COLUMNS>& mat) noexcept
	{
		return vector_view<_TYPE, _ROWS * _COLUMNS, typename matrix<_TYPE, _ROWS, _COLUMNS>::column_const_iterator>(mat.GetArray());
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	inline constexpr matrix<_TYPE, _ROWS, _COLUMNS> GetZeroMatrix() noexcept
	{
		return matrix<_TYPE, _ROWS, _COLUMNS>();
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS> GetIndentityMatrix() noexcept
	{
		static_assert(_ROWS == _COLUMNS, "Error: non-square matrix");
		matrix<_TYPE, _ROWS, _COLUMNS> mat;
		for (unsigned int i = 0; i < _ROWS; ++i)
			mat[i][i] = (_TYPE)1;
		return mat;
	}

	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	matrix<_TYPE, _ROWS, _COLUMNS> GetExchangeMatrix() noexcept
	{
		static_assert(_ROWS == _COLUMNS, "Error: non-square matrix");
		matrix<_TYPE, _ROWS, _COLUMNS> mat;
		for (unsigned int i = 0; i < _ROWS; ++i)
			mat[i][_ROWS - 1 - i] = (_TYPE)1;
		return mat;
	}

	template<typename _TYPE>
	dynamic_matrix<_TYPE> pow(const dynamic_matrix<_TYPE>& mat, const unsigned int power)
	{
		stm_assert(mat.GetRowSize() == mat.GetColumnSize());
		switch (power)
		{
		case 2:
			return multiply(mat, mat);
		case 3:
			return multiply(mat, multiply(mat, mat));
		default:
		{
			if (power % 2)
				return multiply(mat, multiply(pow(mat, power / 2), pow(mat, power / 2)));
			else
				return multiply(pow(mat, power / 2), pow(mat, power / 2));
		}
		}
	}

	template<typename _TYPE>
	matrix<_TYPE, 2, 2> sqrt(const dynamic_matrix<_TYPE>& mat)
	{
		stm_assert(mat.GetColumnSize() == 2 && mat.GetRowSize() == 2);
		_TYPE temp = std::sqrt(determinant(mat));
		return matrix<_TYPE, 2, 2>(mat[0][0] + temp, mat[0][1], mat[1][0], mat[1][1] + temp) / (std::sqrt(temp + 2 * (mat[0][0] + mat[1][1])));
	}	


	template<typename _TYPE>
	_TYPE determinant(const dynamic_matrix<_TYPE>& mat)
	{
		stm_assert(mat.GetRowSize() == mat.GetColumnSize());

		if (mat.GetRowSize() == 2)
			return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
		else
		{
			_TYPE sum = 0;
			for (unsigned int i = 0; i < mat.GetRowSize(); ++i)
				sum += (i % 2) ? -(determinant(mat.Minor(0, i)) * mat[0][i]) : (determinant(mat.Minor(0, i)) * mat[0][i]);
			return sum;
		}
	}

	template<typename _TYPE>
	dynamic_matrix<_TYPE> inverse(const dynamic_matrix<_TYPE>& mat)
	{
		stm_assert(mat.GetRowSize() == mat.GetColumnSize())
		dynamic_matrix<_TYPE> temp(mat.GetRowSize(), mat.GetColumnSize());
		_TYPE det = 0;

		for (unsigned int i = 0; i < mat.GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < mat.GetColumnSize(); ++j)
				temp[0][(i * mat.GetColumnSize()) + j] = (((i + j) % 2) ? -(determinant(mat.Minor(i, j))) : (determinant(mat.Minor(i, j))));
		}

		for (unsigned int k = 0; k < mat.GetColumnSize(); ++k)
			det += temp[k] * mat[0][k];

		return transpose(temp) / det;
	}

	template<typename _TYPE>
	dynamic_matrix<_TYPE> cofactorMatrix(const dynamic_matrix<_TYPE>& mat)
	{
		stm_assert(mat.GetRowSize() == mat.GetColumnSize());
		dynamic_matrix<_TYPE> temp(mat.GetRowSize(), mat.GetColumnSize());

		for (unsigned int i = 0; i < mat.GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < mat.GetColumnSize(); ++j)
			{
				temp[0][(i * mat.GetColumnSize()) + j] = (((i + j) % 2) ? -(determinant(mat.Minor(i, j))) : (determinant(mat.Minor(i, j))));
			}
		}
		return temp;
	}

	template<typename _TYPE>
	inline dynamic_matrix<_TYPE> adjugate(const dynamic_matrix<_TYPE>& mat) {
		return transpose(cofactorMatrix(mat));
	}

	template<typename _TYPE>
	inline dynamic_matrix<_TYPE> adjugate(dynamic_matrix<_TYPE>&& mat) {
		return transpose(cofactorMatrix(mat));
	}

	template<typename _TYPE>
	inline dynamic_matrix<_TYPE> toRowMatrix(const dynamic_vector<_TYPE>& vec) {
		return dynamic_matrix<_TYPE>(1, vec.GetSize(), vec.GetData());
	}

	template<typename _TYPE>
	inline dynamic_matrix<_TYPE> toRowMatrix(dynamic_vector<_TYPE>&& vec) {
		return dynamic_matrix<_TYPE>(vec.GetRefToPtrData(), 1, vec.GetSize());
	}

	template<typename _TYPE>
	inline dynamic_matrix<_TYPE> toColumnMatrix(const dynamic_vector<_TYPE>& vec) {
		return dynamic_matrix<_TYPE>(vec.GetSize(), 1, vec.GetData());
	}

	template<typename _TYPE>
	inline dynamic_matrix<_TYPE> toColumnMatrix(dynamic_vector<_TYPE>&& vec) {
		return dynamic_matrix<_TYPE>(vec.GetRefToPtrData(), vec.GetSize(), 1);
	}

	template<typename _TYPE>
	inline dynamic_vector<_TYPE> toRowVector(const dynamic_matrix<_TYPE>& mat) {
		return dynamic_vector<_TYPE>(mat.GetSize(), mat.GetData());
	}

	template<typename _TYPE>
	inline dynamic_vector<_TYPE> toRowVector(dynamic_matrix<_TYPE>&& mat) {
		return dynamic_vector<_TYPE>(mat.GetRefToPtrData(), mat.GetSize());
	}

	template<typename _TYPE>
	inline dynamic_vector<_TYPE> toColumnVector(const dynamic_matrix<_TYPE>& mat) {
		return dynamic_vector<_TYPE>(mat.GetSize(), mat.Transpose().GetData());
	}

	template<typename _TYPE>
	inline dynamic_vector<_TYPE> toColumnVector(dynamic_matrix<_TYPE>&& mat) {
		return dynamic_vector<_TYPE>(mat.Transpose().GetRefToPtrData(), mat.GetSize());
	}

	template<typename _TYPE>
	inline dynamic_matrix<_TYPE> GetZeroMatrix(const unsigned int dimensions) {
		return dynamic_matrix<_TYPE>(dimensions);
	}

	template<typename _TYPE>
	dynamic_matrix<_TYPE> GetIndentityMatrix(unsigned int dimensions)
	{
		dynamic_matrix<_TYPE> mat(dimensions);
		for (unsigned int i = 0; i < dimensions; ++i)
			mat[i][i] = (_TYPE)1;
		return mat;
	}

	template<typename _TYPE>
	dynamic_matrix<_TYPE> GetExchangeMatrix(unsigned int dimensions)
	{
		dynamic_matrix<_TYPE> mat(dimensions);
		for (unsigned int i = 0; i < dimensions; ++i)
			mat[i][dimensions - 1 - i] = (_TYPE)1;
		return mat;
	}
}

#endif /* stm_matrix_operations_h */