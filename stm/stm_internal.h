#ifndef stm_stm_internal_h
#define stm_stm_internal_h

namespace stm_internal
{
    template<typename _TYPE, unsigned int _N>
    inline static constexpr _TYPE copy_array_data(const _TYPE(&source)[_N], _TYPE(&destination)[_N], const unsigned int index = 0)
    {
        return index < _N ? (destination[index] = source[index], copy_array_data(source, destination, index + 1)) : source[0];
    }

    template<typename _TYPE,  unsigned int  _R, unsigned int _C>
    inline static constexpr _TYPE copy_double_initializer_data(std::initializer_list<std::initializer_list<_TYPE>> list, _TYPE (&destination)[_R * _C], const unsigned int index1 = 0, const unsigned int index2 = 0)
    {
        return index1 < _R ? (index2 < _C ? (destination[index1 * _C + index2] = list.begin()[index1].begin()[index2], copy_double_initializer_data<_TYPE, _R, _C>(list, destination, index1, index2 + 1)) : copy_double_initializer_data<_TYPE, _R, _C>(list, destination, index1 + 1, 0)) : (list.begin()[0])[0];
    }

    template<typename _TYPE, unsigned int _N>
    inline static constexpr _TYPE copy_value_data(const _TYPE& value, _TYPE(&destination)[_N], const unsigned int index = 0)
    {
        return index < _N ? (destination[index] = value, copy_value_data(value, destination, index + 1)) : value;
    }


    template<typename _TYPE, unsigned int _N>
    inline static constexpr _TYPE copy_initializer_data(std::initializer_list<_TYPE> list, _TYPE(&destination)[_N], const unsigned int index = 0)
    {
        return index < _N ? (destination[index] = list[index], copy_initializer_data(list, destination, index + 1)) : list[0];
    }
}

#endif /* stm_stm_internal_h */