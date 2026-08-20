// include/sl/Integral.hpp

#pragma once

#include <type_traits>

#include "sl\Define.hpp"

namespace sl
{
    template<typename T> requires std::is_integral_v<T>
    SL_NODISCARD inline constexpr T inc(T& _val, T _inc) noexcept
    {
        T ret = _val;
        _val += _inc;
        return ret;
    }

    template<typename T> requires std::is_integral_v<T>
    SL_NODISCARD inline constexpr T dec(T& _val, T _dec) noexcept
    {
        T ret = _val;
        _val -= _dec;
        return ret;
    }
}
