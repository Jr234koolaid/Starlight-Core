// include/sl/Enum.hpp

#pragma once

#include <type_traits>

#include "sl/Define.hpp"
#include "sl/Type.hpp"

namespace sl
{
    template<typename T> requires std::is_enum_v<T>
    SL_NODISCARD inline constexpr decltype(auto) enum_cast(T type) noexcept { return static_cast<UnderlyingType<T>>(type); }
}
