// include/sl/Enum.hpp

#pragma once

#include <type_traits>

#include "sl/Attributes.hpp"
#include "sl/TypeTraits.hpp"

namespace sl
{
    template<typename T>
    concept enumerable = std::is_enum_v<T>;
}

namespace sl
{
    template<enumerable _Enum>
    SL_NODISCARD inline constexpr decltype(auto) enum_cast(_Enum enumerable) noexcept { return static_cast<UnderlyingType<_Enum>>(enumerable); }
}
