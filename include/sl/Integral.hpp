// include\sl\Integral.hpp

#pragma once

#include <type_traits>

#include "sl\Define.hpp"

namespace sl
{
    template<typename T> requires std::is_integral_v<T>
    inline SL_NODISCARD constexpr T inc(T& _val, T _inc) noexcept
    {
        T ret = _val;
        _val += _inc;
        return ret;
    }

    template<typename T> requires std::is_integral_v<T>
    inline SL_NODISCARD constexpr T dec(T& _val, T _dec) noexcept
    {
        T ret = _val;
        _val -= _dec;
        return ret;
    }
}
