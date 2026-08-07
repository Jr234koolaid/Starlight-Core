// include\sl\Alias.hpp

#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>

#include "sl\Check.hpp"
#include "sl\Define.hpp"

namespace sl
{
    template<typename T>
    concept alias_type = std::is_object_v<T> and not std::is_function_v<T>;
}

namespace sl
{
    template<alias_type T>
    class Alias
    {
    public:
        Alias(nullptr_t) noexcept
        {
        }

        Alias(T& _t) noexcept :
            mT(&_t)
        {
        }

        template<alias_type U> requires std::is_convertible_v<U*, T*>
        Alias(const Alias<U>& _other) noexcept :
            mT(_other.mT)
        {
        }

    public:
        Alias() = default;

    public:
        SL_NODISCARD operator T&() const noexcept
        {
            SL_ASSERT(mT, "Alias pointer-to-object is null");
            return *mT;
        }

        SL_NODISCARD operator bool() const noexcept
        {
            return mT != nullptr;
        }

    public:
        SL_NODISCARD T* operator->() const noexcept
        {
            SL_ASSERT(mT, "Alias pointer-to-object is null");
            return mT;
        }

    public:
        SL_NODISCARD T& get() const noexcept
        {
            SL_ASSERT(mT, "Alias pointer-to-object is null");
            return *mT;
        }

    private:
        T* mT = nullptr;
    };
}

namespace sl
{
    template<alias_type T>
    Alias(T&) -> Alias<T>;
}
