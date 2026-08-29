// include/sl/Integral.hpp

#pragma once

#include <concepts>
#include <type_traits>

#include "sl/Define.hpp"

namespace sl
{
    template<std::integral _Integral>
    SL_NODISCARD inline constexpr _Integral inc(_Integral& _val, _Integral _inc) noexcept
    {
        _Integral ret = _val;
        _val += _inc;
        return ret;
    }

    template<std::integral _Integral>
    SL_NODISCARD inline constexpr _Integral dec(_Integral& _val, _Integral _dec) noexcept
    {
        _Integral ret = _val;
        _val -= _dec;
        return ret;
    }
}
