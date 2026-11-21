// include/sl/core/BoundVector.hpp

#pragma once

#include <concepts>
#include <cstddef>
#include <optional>
#include <type_traits>
#include <utility>

#include "sl/Assert.hpp"
#include "sl/Attributes.hpp"
#include "sl/Functional.hpp"
#include "sl/Optional.hpp"
#include "sl/Traits.hpp"
#include "sl/Validate.hpp"
#include "sl/Vector.hpp"

namespace sl::core
{
    template<typename T>
    concept boundable = not std::is_const_v<T> and not std::is_function_v<T> and std::default_initializable<T>;
}

namespace sl::core
{
    template<boundable _Ty>
    using BoundableVector = Vector<_Ty>;
}

namespace sl::core
{
    template<boundable _Ty>
    using InBoundVectorIterator      = BoundableVector<_Ty>::iterator;
    template<boundable _Ty>
    using InBoundVectorConstIterator = BoundableVector<_Ty>::const_iterator;
}

namespace sl::core
{
    template<boundable _Ty>
    using InBoundVectorReverseIterator      = BoundableVector<_Ty>::reverse_iterator;
    template<boundable _Ty>
    using InBoundVectorConstReverseIterator = BoundableVector<_Ty>::const_reverse_iterator;
}

namespace sl::core
{
    template<boundable _Ty>
    class InBoundVector
    {
    public:
        using size_type       = size_t;
        using difference_type = ptrdiff_t;
        using value_type      = _Ty;
    public:
        using iterator       = InBoundVectorIterator<_Ty>;
        using const_iterator = InBoundVectorConstIterator<_Ty>;
    public:
        using reverse_iterator       = InBoundVectorReverseIterator<_Ty>;
        using const_reverse_iterator = InBoundVectorConstReverseIterator<_Ty>;
    public:
        constexpr  InBoundVector() = default;
        constexpr ~InBoundVector() = default;
    public:
        constexpr InBoundVector(size_t maxcapacity) {
            SL_ASSERT_IF(maxcapacity == 0U, "InBoundVector expects max capacity to be valid");
            mBoundables.reserve(maxcapacity);
        }
    public:
        constexpr InBoundVector(InBoundVector&& other) noexcept
        : mBoundables(std::move(other.mBoundables)) {
        }
    public:
        constexpr InBoundVector& operator=(InBoundVector&& other) noexcept {
            if (this != &other)
                mBoundables = std::move(other.mBoundables);

            return *this;
        }
    public:
        SL_NODISCARD constexpr _Ty& operator[](size_t index) noexcept {
            SL_ASSERT(index < mBoundables.size(), "InBoundVector expects index to be valid");
            return mBoundables[index];
        }

        SL_NODISCARD constexpr const _Ty& operator[](size_t index) const noexcept {
            SL_ASSERT(index < mBoundables.size(), "InBoundVector expects index to be valid");
            return mBoundables[index];
        }
    public:
        SL_NODISCARD constexpr size_t capacity() const noexcept {
            return mBoundables.capacity();
        }

        SL_NODISCARD constexpr size_t size() const noexcept {
            return mBoundables.size();
        }
    public:
        SL_NODISCARD constexpr bool empty() const noexcept {
            return mBoundables.empty();
        }
    public:
        SL_NODISCARD constexpr bool has_capacity() const noexcept {
            return mBoundables.size() < mBoundables.capacity();
        }
    public:
        SL_NODISCARD constexpr _Ty& at(size_t index) noexcept {
            SL_ASSERT(index < mBoundables.size(), "InBoundVector expects index to be valid");
            return mBoundables.at(index);
        }

        SL_NODISCARD constexpr const _Ty& at(size_t index) const noexcept {
            SL_ASSERT(index < mBoundables.size(), "InBoundVector expects index to be valid");
            return mBoundables.at(index);
        }
    public:
        template<class... _Args>
        SL_NODISCARD constexpr Optional<iterator> emplace(const_iterator iterator, _Args&&... args) {
            SL_VALIDATE(has_capacity(), std::nullopt, "InBoundVector expects to have capacity to emplace");
            return mBoundables.emplace(iterator, std::forward<_Args>(args)...);
        }
    public:
        template<class... _Args>
        SL_NODISCARD constexpr Optional<Reference<_Ty>> emplace_back(_Args&&... args) {
            SL_VALIDATE(has_capacity(), std::nullopt, "InBoundVector expects to have capacity to emplace back");
            return mBoundables.emplace_back(std::forward<_Args>(args)...);
        }
    public:
        constexpr void push_back(_Ty&& value) requires std::movable<_Ty> {
            SL_VALIDATE_VOID(has_capacity(), "InBoundVector expects to have capacity to push back");
            mBoundables.push_back(std::move(value));
        }

        constexpr void push_back(const _Ty& value) requires std::copyable<_Ty> {
            SL_VALIDATE_VOID(has_capacity(), "InBoundVector expects to have capacity to push back");
            mBoundables.push_back(value);
        }
    public:
        SL_NODISCARD constexpr Optional<iterator> insert(const_iterator iterator, _Ty&& value) requires std::movable<_Ty> {
            SL_VALIDATE(has_capacity(), std::nullopt, "InBoundVector expects to have capacity to insert");
            return mBoundables.insert(iterator, std::move(value));
        }

        SL_NODISCARD constexpr Optional<iterator> insert(const_iterator iterator, const _Ty& value) requires std::copyable<_Ty> {
            SL_VALIDATE(has_capacity(), std::nullopt, "InBoundVector expects to have capacity to insert");
            return mBoundables.insert(iterator, value);
        }
    public:
        constexpr void clear() noexcept {
            mBoundables.clear();
        }
    public:
        SL_NODISCARD constexpr iterator begin() noexcept {
            return mBoundables.begin();
        }

        SL_NODISCARD constexpr iterator end() noexcept {
            return mBoundables.end();
        }
    public:
        SL_NODISCARD constexpr const_iterator begin() const noexcept {
            return mBoundables.begin();
        }

        SL_NODISCARD constexpr const_iterator end() const noexcept {
            return mBoundables.end();
        }
    public:
        SL_NODISCARD constexpr reverse_iterator rbegin() noexcept {
            return mBoundables.rbegin();
        }

        SL_NODISCARD constexpr reverse_iterator rend() noexcept {
            return mBoundables.rend();
        }
    public:
        SL_NODISCARD constexpr const_reverse_iterator rbegin() const noexcept {
            return mBoundables.rbegin();
        }

        SL_NODISCARD constexpr const_reverse_iterator rend() const noexcept {
            return mBoundables.rend();
        }
    public:
        SL_NODISCARD constexpr const_iterator cbegin() const noexcept {
            return mBoundables.cbegin();
        }

        SL_NODISCARD constexpr const_iterator cend() const noexcept {
            return mBoundables.cend();
        }
    public:
        SL_NODISCARD constexpr const_reverse_iterator crbegin() const noexcept {
            return mBoundables.crbegin();
        }

        SL_NODISCARD constexpr const_reverse_iterator crend() const noexcept {
            return mBoundables.crend();
        }
    private:
        BoundableVector<_Ty> mBoundables;
    };
}
