// include\sl\Cast.hpp

#pragma once

#include <cctype>
#include <cstdint>
#include <type_traits>

#include "sl\Define.hpp"
#include "sl\Type.hpp"

namespace sl
{
    template<typename T> requires std::is_enum_v<T>
    inline SL_NODISCARD constexpr auto enum_cast(T _enum) noexcept { return static_cast<UnderlyingType<T>>(_enum); }
}

namespace sl
{
    template<typename T>
    inline SL_NODISCARD auto address_cast(const Unique<T>& _p) noexcept { return reinterpret_cast<uintptr_t>(_p.get()); }
    template<typename T>
    inline SL_NODISCARD auto address_cast(const Shared<T>& _p) noexcept { return reinterpret_cast<uintptr_t>(_p.get()); }
}

namespace sl
{
    inline SL_NODISCARD auto address_cast(const void* _p) noexcept { return reinterpret_cast<uintptr_t>(_p); }
    inline SL_NODISCARD auto address_cast(uintptr_t _p) noexcept { return reinterpret_cast<void*>(_p); }
}

namespace sl
{
    inline SL_NODISCARD auto upper_cast(char _c) { return static_cast<char>(std::toupper(static_cast<unsigned char>(_c))); }
    inline SL_NODISCARD auto lower_cast(char _c) { return static_cast<char>(std::tolower(static_cast<unsigned char>(_c))); }
}
