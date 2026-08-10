// include\sl\PageSet.inl

#include <cstddef>
#include <type_traits>

#include "sl\Assert.hpp"
#include "sl\PageSet.hpp"

namespace sl
{
    template<page_set_integral TValue, page_set_integral TIndex, size_t Size>
    PageSet<TValue, TIndex, Size>::PageSet(PageSet&& _other) noexcept :
        mValuePages(std::move(_other.mValuePages))
    {
    }
}

namespace sl
{
    template<page_set_integral TValue, page_set_integral TIndex, size_t Size>
    PageSet<TValue, TIndex, Size>& PageSet<TValue, TIndex, Size>::operator=(PageSet&& _other) noexcept
    {
        if (this != &_other)
            mValuePages = std::move(_other.mValuePages);

        return *this;
    }
}

namespace sl
{
    template<page_set_integral TValue, page_set_integral TIndex, size_t Size>
    TValue& PageSet<TValue, TIndex, Size>::at(TIndex _index) noexcept
    {
        SL_ASSERT(contains(_index));
        const size_t pindex = _index / Size;
        const size_t vindex = _index % Size;
        return mValuePages[pindex][vindex];
    }

    template<page_set_integral TValue, page_set_integral TIndex, size_t Size>
    const TValue& PageSet<TValue, TIndex, Size>::at(TIndex _index) const noexcept
    {
        SL_ASSERT(contains(_index));
        const size_t pindex = _index / Size;
        const size_t vindex = _index % Size;
        return mValuePages[pindex][vindex];
    }
}

namespace sl
{
    template<page_set_integral TValue, page_set_integral TIndex, size_t Size>
    bool PageSet<TValue, TIndex, Size>::contains(TIndex _index) const noexcept
    {
        const size_t pindex = _index / Size;
        const size_t vindex = _index % Size;
        return (pindex < mValuePages.size()) && (mValuePages[pindex][vindex] != TombstonePageSet<TValue>);
    }
}

namespace sl
{
    template<page_set_integral TValue, page_set_integral TIndex, size_t Size>
    bool PageSet<TValue, TIndex, Size>::emplace(TIndex _index, TValue _value)
    {
        if (contains(_index))
            return false;

        const size_t pindex = _key / Size;
        const size_t vindex = _key % Size;

        // Fill "skipped" empty values with tombstones
        const size_t size = mValuePages.size();
        if (pindex >= size)
        {
            mValuePages.resize(pindex + 1U);
            for (size_t i = size; i < mValuePages.size(); ++i)
                mValuePages[i].fill(TombstonePageSet<TValue>);
        }

        mValuePages[pindex][vindex] = _value;
        return true;
    }
}

namespace sl
{
    template<page_set_integral TValue, page_set_integral TIndex, size_t Size>
    void PageSet<TValue, TIndex, Size>::erase(TIndex _index) noexcept
    {
        if (contains(_index))
        {
            const size_t pindex = _key / Size;
            const size_t vindex = _key % Size;
            mValuePages[pindex][vindex] = TombstonePageSet<TValue>;
        }
    }
}

namespace sl
{
    template<page_set_integral TValue, page_set_integral TIndex, size_t Size>
    void PageSet<TValue, TIndex, Size>::clear() noexcept
    {
        mValuePages.clear();
    }
}
