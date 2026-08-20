// include/sl/Cast.hpp

#pragma once

#include <cctype>
#include <cstdint>
#include <type_traits>

#include "sl\Define.hpp"
#include "sl\Type.hpp"

namespace sl
{
    template<typename T> requires std::is_enum_v<T>
    SL_NODISCARD inline constexpr auto enum_cast(T _enum) noexcept
    {
        return static_cast<UnderlyingType<T>>(_enum);
    }
}

namespace sl
{
    template<typename T>
    SL_NODISCARD inline uintptr_t address_cast(const Unique<T>& _p) noexcept
    {
        return reinterpret_cast<uintptr_t>(_p.get());
    }

    template<typename T>
    SL_NODISCARD inline uintptr_t address_cast(const Shared<T>& _p) noexcept
    {
        return reinterpret_cast<uintptr_t>(_p.get());
    }

    SL_NODISCARD inline uintptr_t address_cast(const void* _p) noexcept
    {
        return reinterpret_cast<uintptr_t>(_p);
    }

    SL_NODISCARD inline void* address_cast(uintptr_t _p) noexcept
    {
        return reinterpret_cast<void*>(_p);
    }
}

namespace sl
{
    SL_NODISCARD inline char upper_cast(char _c)
    {
        return static_cast<char>(std::toupper(static_cast<unsigned char>(_c)));
    }

    SL_NODISCARD inline char lower_cast(char _c)
    {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(_c)));
    }
}
