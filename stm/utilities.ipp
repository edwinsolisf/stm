#include <string>

namespace stm
{
	template<typename _TYPE, unsigned int _ROWS, unsigned int _COLUMNS>
	static void Print(const matrix<_TYPE, _ROWS, _COLUMNS>& mat)
	{
		std::cout << "[ ";
		for (unsigned int i = 0; i < _ROWS; ++i)
		{
			for (unsigned int j = 0; j < _COLUMNS; ++j)
				std::cout << std::to_string(mat[i][j]) << (((i != _ROWS - 1) || (j != _COLUMNS - 1)) ? " , " : " ");
			if (i != _ROWS - 1)
				std::cout << std::endl << "  ";
			else
				std::cout << "]" << std::endl;
		}
	}

	template<typename _TYPE>
	static void Print(const dynamic_matrix<_TYPE>& mat)
	{
		std::cout << "[ ";
		for (unsigned int i = 0; i < mat.GetRowSize(); ++i)
		{
			for (unsigned int j = 0; j < mat.GetColumnSize(); ++j)
				std::cout << std::to_string(mat[i][j]) << (((i != mat.GetRowSize() - 1) || (j != mat.GetColumnSize() - 1)) ? " , " : " ");
			if (i != mat.GetRowSize() - 1)
				std::cout << std::endl << "  ";
			else
				std::cout << "]" << std::endl;
		}
	}

	template<typename _TYPE, unsigned int _DIM>
	static void Print(const vector<_TYPE, _DIM>& vec)
	{
		std::cout << "[ ";
		for (unsigned int i = 0; i < _DIM; ++i)
			std::cout << std::to_string(vec[i]) << ((i < _DIM - 1) ? " , " : " ");
		std::cout << "]" << std::endl;
	}

	template<typename _TYPE>
	static void Print(const dynamic_vector<_TYPE>& vec)
	{
		std::cout << "[ ";
		for (unsigned int i = 0; i < vec.GetSize(); ++i)
			std::cout << std::to_string(vec[i]) << ((i < vec.GetSize() - 1) ? " , " : " ");
		std::cout << "]" << std::endl;
	}

	//TODO Optimize to O(log n)1
	template<typename _TYPE, unsigned int _DIM>
	_TYPE getEntriesSum(const stm::vector<_TYPE, _DIM>& vec)
	{
		_TYPE out = 0;

		for (unsigned int i = 0; i < _DIM; ++i)
			out += vec[i];

		return out;
	}
}