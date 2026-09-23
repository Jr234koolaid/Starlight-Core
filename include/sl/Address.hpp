// include/sl/Address.hpp

#pragma once

#include <cstdint>

#include "sl/Define.hpp"
#include "sl/Type.hpp"

namespace sl
{
    template<typename T>
    SL_NODISCARD inline uintptr_t address_cast(const UniquePtr<T>& ptr) noexcept { return reinterpret_cast<uintptr_t>(ptr.get()); }
    template<typename T>
    SL_NODISCARD inline uintptr_t address_cast(const SharedPtr<T>& ptr) noexcept { return reinterpret_cast<uintptr_t>(ptr.get()); }
}

namespace sl
{
    SL_NODISCARD inline uintptr_t address_cast(const void* ptr) noexcept { return reinterpret_cast<uintptr_t>(ptr); }
}

namespace sl
{
    SL_NODISCARD inline void* address_cast(uintptr_t address) noexcept { return reinterpret_cast<void*>(address); }
}
