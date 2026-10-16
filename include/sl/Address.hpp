// include/sl/Address.hpp

#pragma once

#include <cstdint>

#include "sl/Attributes.hpp"
#include "sl/Memory.hpp"

namespace sl
{
    template<typename T>
    SL_NODISCARD inline decltype(auto) address_cast(const UniquePointer<T>& pointer) noexcept { return reinterpret_cast<uintptr_t>(pointer.get()); }
    template<typename T>
    SL_NODISCARD inline decltype(auto) address_cast(const SharedPointer<T>& pointer) noexcept { return reinterpret_cast<uintptr_t>(pointer.get()); }
}

namespace sl
{
    SL_NODISCARD inline decltype(auto) address_cast(const void* pointer) noexcept { return reinterpret_cast<uintptr_t>(pointer); }
    SL_NODISCARD inline decltype(auto) address_cast(  uintptr_t address) noexcept { return reinterpret_cast<    void*>(address); }
}
