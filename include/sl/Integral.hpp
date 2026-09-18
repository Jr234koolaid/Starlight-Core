// include/sl/Integral.hpp

#pragma once

#include <concepts>

#include "sl/Define.hpp"

namespace sl
{
    template<std::integral _Integral>
    SL_NODISCARD inline constexpr _Integral inc(_Integral* val, _Integral inc) noexcept
    {
        _Integral ret = val;
        (*val) += inc;
        return ret;
    }

    template<std::integral _Integral>
    SL_NODISCARD inline constexpr _Integral dec(_Integral* val, _Integral dec) noexcept
    {
        _Integral ret = val;
        (*val) -= dec;
        return ret;
    }
}
