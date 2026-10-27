// include/sl/Alias.hpp

#pragma once

#include <cstddef>
#include <functional>
#include <type_traits>
#include <utility>

#include "sl/Assert.hpp"
#include "sl/Attributes.hpp"

namespace sl
{
    template<class _Ty>
    concept referenceable = std::is_object_v<_Ty> and not std::is_function_v<_Ty>;
}

namespace sl
{
    template<referenceable _Ty>
    class Alias
    {
    public:
        using type = _Ty;
    public:
        constexpr  Alias() = default;
        constexpr ~Alias() = default;
    public:
        constexpr Alias(nullptr_t) noexcept {
        }

        constexpr Alias(_Ty& reference) noexcept
        : mPointer(&reference) {
        }
    public:
        template<referenceable _Uty> requires std::is_convertible_v<_Uty*, _Ty*>
        constexpr Alias(const Alias<_Uty>& other) noexcept
        : mPointer(other.mPointer) {
        }
    public:
        constexpr Alias(Alias&& other) noexcept
        : mPointer(std::exchange(other.mPointer, nullptr)) {
        }

        constexpr Alias(const Alias& other) noexcept
        : mPointer(other.mPointer) {
        }
    public:
        SL_NODISCARD constexpr operator bool() const noexcept {
            return mPointer != nullptr;
        }

        SL_NODISCARD constexpr operator _Ty&() const noexcept {
            SL_ASSERT_IF_NOT(mPointer, "Alias pointer-to-object is null");
            return *mPointer;
        }
    public:
        constexpr Alias& operator=(Alias&& other) noexcept {
            if (this != &other)
                mPointer = std::exchange(other.mPointer, nullptr);

            return *this;
        }

        constexpr Alias& operator=(const Alias& other) noexcept {
            if (this != &other)
                mPointer = other.mPointer;

            return *this;
        }
    public:
        SL_NODISCARD constexpr _Ty* operator->() const noexcept {
            SL_ASSERT_IF_NOT(mPointer, "Alias pointer-to-object is null");
            return mPointer;
        }
    public:
        SL_NODISCARD constexpr _Ty& get() const noexcept {
            SL_ASSERT_IF_NOT(mPointer, "Alias pointer-to-object is null");
            return *mPointer;
        }
    private:
        _Ty* mPointer = nullptr;
    };
}

namespace sl
{
    template<referenceable _Ty>
    Alias(_Ty&) -> Alias<_Ty>;
}

namespace std
{
    template<sl::referenceable _Ty>
    struct hash<sl::Alias<_Ty>>
    {
        SL_NODISCARD static constexpr size_t operator()(const sl::Alias<_Ty>& alias) noexcept { return hash<_Ty>()(alias.get()); }
    };
}
