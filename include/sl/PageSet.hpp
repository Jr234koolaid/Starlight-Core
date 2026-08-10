// include\sl\PageSet.hpp

#pragma once

#include <cstddef>
#include <limits>
#include <type_traits>

#include "sl\Define.hpp"
#include "sl\Trait.hpp"
#include "sl\Type.hpp"

namespace sl
{
    template<typename T>
    concept page_set_integral = std::is_integral_v<T>;
}

namespace sl
{
    template<page_set_integral TValue>
    inline constexpr TValue TombstonePageSet = std::numeric_limits<TValue>::max();
}

namespace sl
{
    template<page_set_integral TValue, page_set_integral TIndex = TValue, size_t Size = 256U>
    class PageSet : private NonCopyable
    {
    public:
        PageSet() = default;
        PageSet(PageSet&& _other) noexcept;
       ~PageSet() = default;

    public:
        PageSet& operator=(PageSet&& _other) noexcept;

    public:
        SL_NODISCARD TValue& at(TIndex _index) noexcept;
        SL_NODISCARD const TValue& at(TIndex _index) const noexcept;

    public:
        SL_NODISCARD bool contains(TIndex _index) const noexcept;

    public:
        SL_NODISCARD bool emplace(TIndex _index, TValue _value);

    public:
        void erase(TIndex _index) noexcept;

    public:
        void clear() noexcept;

    private:
        Vector<Array<TValue, Size>> mValuePages;
    };
}

// Implementation:
#include "sl\PageSet.inl"
