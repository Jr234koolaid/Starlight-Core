// include/sl/Alias.hpp

#pragma once

#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>

#include "sl/Assert.hpp"
#include "sl/Define.hpp"

namespace sl
{
    template<class T>
    concept alias_type = std::is_object_v<T> and not std::is_function_v<T>;
}

namespace sl
{
    template<alias_type T>
    class Alias
    {
    public:
        constexpr Alias(nullptr_t) noexcept
        {
        }

        constexpr Alias(T& ref) noexcept :
            mPtr(&ref)
        {
        }

        template<alias_type U> requires std::is_convertible_v<U*, T*>
        constexpr Alias(const Alias<U>& alias) noexcept :
            mPtr(alias.mPtr)
        {
        }
    public:
        constexpr Alias()  = default;
        constexpr ~Alias() = default;
    public:
        constexpr Alias(Alias&& other) noexcept :
            mPtr(std::exchange(other.mPtr, nullptr))
        {
        }

        constexpr Alias(const Alias& other) noexcept :
            mPtr(other.mPtr)
        {
        }
    public:
        SL_NODISCARD constexpr operator bool() const noexcept
        {
            return mPtr != nullptr;
        }

        SL_NODISCARD constexpr operator T&() const noexcept
        {
            SL_ASSERT(mPtr, "Alias pointer-to-object is null");
            return *mPtr;
        }
    public:
        constexpr Alias& operator=(Alias&& other) noexcept
        {
            if (this != &other)
                mPtr = std::exchange(other.mPtr, nullptr);

            return *this;
        }

        constexpr Alias& operator=(const Alias& other) noexcept
        {
            if (this != &other)
                mPtr = other.mPtr;

            return *this;
        }
    public:
        SL_NODISCARD constexpr T* operator->() const noexcept
        {
            SL_ASSERT(mPtr, "Alias pointer-to-object is null");
            return mPtr;
        }
    public:
        SL_NODISCARD constexpr T& get() const noexcept
        {
            SL_ASSERT(mPtr, "Alias pointer-to-object is null");
            return *mPtr;
        }
    private:
        T* mPtr = nullptr;
    };
}

namespace sl
{
    template<alias_type T>
    Alias(T&) -> Alias<T>;
}

namespace std
{
    template<class T>
    struct hash<sl::Alias<T>>
    {
        SL_NODISCARD static constexpr size_t operator()(const sl::Alias<T>& alias) noexcept { return hash<T>()(alias.get()); }
    };
}
