#ifndef stm_matrix_view_h
#define stm_matrix_view_h

#include "matrix.h"
#include "dynamic_matrix.h"

namespace stm
{
    template <typename T, typename Itr>
    class dynamic_matrix_view;

    template <typename T, unsigned int ROWS, unsigned int COLUMNS, typename Itr>
    class matrix_view
    {
    public:
        using ElemType = T;
        using const_iterator = Itr;

        constexpr matrix_view() = delete;
        constexpr matrix_view(const matrix_view&) noexcept = default;
        constexpr explicit matrix_view(const matrix<T, ROWS, COLUMNS>& mat) noexcept;
        constexpr matrix_view(const T (&data)[ROWS * COLUMNS]) noexcept;

        matrix_view(matrix<T, ROWS, COLUMNS>&&) = delete;
        matrix_view& operator=(const matrix_view&) = delete;

        template <typename Iter>
        matrix<T, ROWS, COLUMNS> operator+(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const noexcept;
        template <typename Iter>
        matrix<T, ROWS, COLUMNS> operator-(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const noexcept;
        template <typename Iter>
        matrix<T, ROWS, COLUMNS> operator*(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const noexcept;
        template <typename Iter>
        matrix<T, ROWS, COLUMNS> operator/(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const noexcept;

        matrix<T, ROWS, COLUMNS> operator+(const matrix<T, ROWS, COLUMNS>& other) const noexcept;
        matrix<T, ROWS, COLUMNS> operator-(const matrix<T, ROWS, COLUMNS>& other) const noexcept;
        matrix<T, ROWS, COLUMNS> operator*(const matrix<T, ROWS, COLUMNS>& other) const noexcept;
        matrix<T, ROWS, COLUMNS> operator/(const matrix<T, ROWS, COLUMNS>& other) const noexcept;

        matrix<T, ROWS, COLUMNS> operator+(const dynamic_matrix<T>& other) const;
        matrix<T, ROWS, COLUMNS> operator-(const dynamic_matrix<T>& other) const;
        matrix<T, ROWS, COLUMNS> operator*(const dynamic_matrix<T>& other) const;
        matrix<T, ROWS, COLUMNS> operator/(const dynamic_matrix<T>& other) const;

        template <typename Iter>
        matrix<T, ROWS, COLUMNS> operator+(const dynamic_matrix_view<T, Iter>& other) const;
        template <typename Iter>
        matrix<T, ROWS, COLUMNS> operator-(const dynamic_matrix_view<T, Iter>& other) const;
        template <typename Iter>
        matrix<T, ROWS, COLUMNS> operator*(const dynamic_matrix_view<T, Iter>& other) const;
        template <typename Iter>
        matrix<T, ROWS, COLUMNS> operator/(const dynamic_matrix_view<T, Iter>& other) const;

        matrix<T, ROWS, COLUMNS> operator+(const T& other) const noexcept;
        matrix<T, ROWS, COLUMNS> operator-(const T& other) const noexcept;
        matrix<T, ROWS, COLUMNS> operator*(const T& other) const noexcept;
        matrix<T, ROWS, COLUMNS> operator/(const T& other) const noexcept;

        constexpr const_iterator operator[](const unsigned int index) const noexcept { return cbegin_row(index); }

        static constexpr unsigned int container_row_size() noexcept { return ROWS; }
        static constexpr unsigned int container_column_size() noexcept { return COLUMNS; }
        static constexpr unsigned int container_size() noexcept { return container_row_size() * container_column_size(); }
        constexpr unsigned int GetSize() const noexcept { return container_size(); }
        constexpr unsigned int GetRowSize() const noexcept { return container_row_size(); }
        constexpr unsigned int GetColumnSize() const noexcept { return container_column_size(); }

        constexpr const_iterator cbegin() const noexcept { return _iter; }
        constexpr const_iterator cend() const noexcept { return _iter.toEnd(); }

        constexpr const_iterator begin() const noexcept { return cbegin(); }
        constexpr const_iterator end() const noexcept { return cend(); }

        constexpr const_iterator cbegin_row(const unsigned int row) const noexcept { return &_iter.unwrap()[row * _iter.step()/GetColumnSize()];}
        constexpr const_iterator cend_row(const unsigned int row) const noexcept { return &_iter.unwrap()[(row + 1) * _iter.step()/GetColumnSize()];; }

        //constexpr auto cbegin_column(const unsigned int column) const noexcept { return _iter.complIter(&_iter.unwrap()[column * _iter.step()]); }
        //constexpr auto cend_column(const unsigned int column) const noexcept { return _iter.complIter(&_iter.unwrap()[(column + 1) * _iter.step()]); }

        template <unsigned int O_COLUMNS, typename Iter>
        matrix<T, ROWS, O_COLUMNS> Multiply(const matrix_view<T, COLUMNS, O_COLUMNS, Iter>& other) const noexcept;
        template <unsigned int O_COLUMNS>
        matrix<T, ROWS, O_COLUMNS> Multiply(const matrix<T, COLUMNS, O_COLUMNS>& other) const noexcept;
        template <typename Iter>
        dynamic_matrix<T> Multiply(const dynamic_matrix_view<T, Iter>& other) const;
        dynamic_matrix<T> Multiply(const dynamic_matrix<T>& other) const;

        template <typename Iter>
        vector<T, ROWS> Multiply(const vector_view<T, COLUMNS, Iter>& other) const noexcept;
        vector<T, ROWS> Multiply(const vector<T, COLUMNS>& other) const noexcept;

        template <typename Iter>
        vector<T, ROWS> Multiply(const dynamic_vector_view<T, Iter>& other) const;
        vector<T, ROWS> Multiply(const dynamic_vector<T>& other) const;

    private:
        //const T* const _data;
        const Itr _iter;
    };

    template <typename T, typename Itr>
    class dynamic_matrix_view
    {
    public:
        using ElemType = T;
        using const_iterator = Itr;

        dynamic_matrix_view() noexcept;
        dynamic_matrix_view(const dynamic_matrix_view&) noexcept = default;
        dynamic_matrix_view(const Itr iterator, const unsigned int rows, const unsigned int columns);
        explicit dynamic_matrix_view(const dynamic_matrix<T>& vec);
        dynamic_matrix_view(dynamic_matrix<T>&&) = delete;
        template <unsigned int ROWS, unsigned int COLUMNS>
        explicit dynamic_matrix_view(const matrix<T, ROWS, COLUMNS>&  matrix) noexcept;
        
        dynamic_matrix_view& operator=(const dynamic_matrix_view&) = delete;

        template <typename Iter>
        dynamic_matrix<T> operator+(const dynamic_matrix_view<T, Iter>& other) const;
        template <typename Iter>
        dynamic_matrix<T> operator-(const dynamic_matrix_view<T, Iter>& other) const;
        template <typename Iter>
        dynamic_matrix<T> operator*(const dynamic_matrix_view<T, Iter>& other) const;
        template <typename Iter>
        dynamic_matrix<T> operator/(const dynamic_matrix_view<T, Iter>& other) const;
        
        dynamic_matrix<T> operator+(const dynamic_matrix<T>& other) const;
        dynamic_matrix<T> operator-(const dynamic_matrix<T>& other) const;
        dynamic_matrix<T> operator*(const dynamic_matrix<T>& other) const;
        dynamic_matrix<T> operator/(const dynamic_matrix<T>& other) const;
        
        template <unsigned int ROWS, unsigned int COLUMNS>
        matrix<T, ROWS, COLUMNS> operator+(const matrix<T, ROWS, COLUMNS>& other) const;
        template <unsigned int ROWS, unsigned int COLUMNS>
        matrix<T, ROWS, COLUMNS> operator-(const matrix<T, ROWS, COLUMNS>& other) const;
        template <unsigned int ROWS, unsigned int COLUMNS>
        matrix<T, ROWS, COLUMNS> operator*(const matrix<T, ROWS, COLUMNS>& other) const;
        template <unsigned int ROWS, unsigned int COLUMNS>
        matrix<T, ROWS, COLUMNS> operator/(const matrix<T, ROWS, COLUMNS>& other) const;

        template <unsigned int ROWS, unsigned int COLUMNS, typename Iter>
        matrix<T, ROWS, COLUMNS> operator+(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const;
        template <unsigned int ROWS, unsigned int COLUMNS, typename Iter>
        matrix<T, ROWS, COLUMNS> operator-(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const;
        template <unsigned int ROWS, unsigned int COLUMNS, typename Iter>
        matrix<T, ROWS, COLUMNS> operator*(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const;
        template <unsigned int ROWS, unsigned int COLUMNS, typename Iter>
        matrix<T, ROWS, COLUMNS> operator/(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const;

        dynamic_matrix<T> operator+(const T& other) const;
        dynamic_matrix<T> operator-(const T& other) const;
        dynamic_matrix<T> operator*(const T& other) const;
        dynamic_matrix<T> operator/(const T& other) const;

        const_iterator operator[](const unsigned int index) const noexcept { return cbegin_row(index); }

        unsigned int GetRowSize() const noexcept { return _rows; }
        unsigned int GetColumnSize() const noexcept { return _columns; }
        unsigned int GetSize() const noexcept { return _rows * _columns; }

        const_iterator cbegin() const noexcept { return _iter; }
        const_iterator cend() const noexcept { return _iter.toEnd(); }

        const_iterator begin() const noexcept { return cbegin(); }
        const_iterator end() const noexcept { return cend(); }

        const_iterator cbegin_row(const unsigned int row) const noexcept { return const_iterator(&_iter.unwrap()[row * _iter.step()/GetColumnSize()], _rows, _columns);}
        const_iterator cend_row(const unsigned int row) const noexcept { return const_iterator(&_iter.unwrap()[(row + 1) * _iter.step()/GetColumnSize()], _rows, _columns); }

        //auto cbegin_column(const unsigned int column) const noexcept { return decltype(_iter.complIter()){&_iter.unwrap()[column * _iter.step()], _rows, _columns }; }
        //auto cend_column(const unsigned int column) const noexcept { return decltype(_iter.complIter()){&_iter.unwrap()[(column + 1) * _iter.step()], _rows, _columns }; }

        template <unsigned int ROWS, unsigned int COLUMNS, typename Iter>
        dynamic_matrix<T> Multiply(const matrix_view<T, ROWS, COLUMNS, Iter>& other) const;
        template <unsigned int ROWS, unsigned int COLUMNS>
        dynamic_matrix<T> Multiply(const matrix<T, ROWS, COLUMNS>& other) const;
        template <typename Iter>
        dynamic_matrix<T> Multiply(const dynamic_matrix_view<T, Iter>& other) const;
        dynamic_matrix<T> Multiply(const dynamic_matrix<T>& other) const;

        template <unsigned int DIM, typename Iter>
        dynamic_vector<T> Multiply(const vector_view<T, DIM, Iter>& other) const;
        template <unsigned int DIM, typename Iter>
        dynamic_vector<T> Multiply(const vector<T, DIM>& other) const;

        template <typename Iter>
        dynamic_vector<T> Multiply(const dynamic_vector_view<T, Iter>& other) const;
        dynamic_vector<T> Multiply(const dynamic_vector<T>& other) const;

    private:
        const Itr _iter;
        const size_t _rows;
        const size_t _columns;
    };
}

#include "matrix_view.ipp"

#endif /* stm_matrix_view_h */