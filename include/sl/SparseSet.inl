// include\sl\SparseSet.inl

#include <cstddef>
#include <type_traits>

#include "sl\Assert.hpp"
#include "sl\SparseSet.hpp"

namespace sl
{
    template<sparse_set_type TValue, sparse_set_integral TIndex>
    SparseSet<TValue, TIndex>::SparseSet(SparseSet&& _other) noexcept :
        mIndexToValueIndex(std::move(_other.mIndexToValueIndex)),
        mIndices          (std::move(_other.mIndices)),
        mValues           (std::move(_other.mValues))
    {
    }
}

namespace sl
{
    template<sparse_set_type TValue, sparse_set_integral TIndex>
    SparseSet<TValue, TIndex>& SparseSet<TValue, TIndex>::operator=(SparseSet&& _other) noexcept
    {
        if (this != &_other)
        {
            mValues            = std::move(_other.mValues);
            mIndices           = std::move(_other.mIndices);
            mIndexToValueIndex = std::move(_other.mIndexToValueIndex);
        }
        return *this;
    }
}

namespace sl
{
    template<sparse_set_type TValue, sparse_set_integral TIndex>
    TValue& SparseSet<TValue, TIndex>::at(TIndex _index) noexcept
    {
        SL_ASSERT(contains(_index));
        return mValues[mIndexToValueIndex.at(_index)];
    }

    template<sparse_set_type TValue, sparse_set_integral TIndex>
    const TValue& SparseSet<TValue, TIndex>::at(TIndex _index) const noexcept
    {
        SL_ASSERT(contains(_index));
        return mValues[mIndexToValueIndex.at(_index)];
    }
}

namespace sl
{
    template<sparse_set_type TValue, sparse_set_integral TIndex>
    bool SparseSet<TValue, TIndex>::contains(TIndex _index) const noexcept
    {
        if (mIndexToValueIndex.contains(_index))
        {
            const size_t index = mIndexToValueIndex.at(_index);
            if (index < mIndices.size())
                return mIndices[index] == _index;
        }
        return false;
    }
}

namespace sl
{
    template<sparse_set_type TValue, sparse_set_integral TIndex>
    template<class... UArgs>
    bool SparseSet<TValue, TIndex>::emplace(TIndex _index, UArgs&&... _args)
    {
        if (!mIndexToValueIndex.emplace(_index, mKeys.size()))
            return false;

        mIndices.push_back(_index);
        
        mValues.emplace_back(std::forward<UArgs>(_args)...);
        return true;
    }
}

namespace sl
{
    template<sparse_set_type TValue, sparse_set_integral TIndex>
    void SparseSet<TValue, TIndex>::erase(TIndex _index) noexcept
    {
        if (contains(_index))
        {
            const size_t rindex = mIndexToValueIndex.at(_index);
            const size_t lindex = mIndices.size() - 1U;

            if (lindex != rindex)
            {
                size_t& sindex = mIndexToValueIndex.at(mIndices[lindex]);

                mValues[rindex]  = std::move(mValues[sindex]);
                mIndices[rindex] = mIndices[sindex];

                sindex = rindex;
            }

            mValues.pop_back();
            mIndices.pop_back();
            mIndexToValueIndex.erase(_index);
        }
    }
}

namespace sl
{
    template<sparse_set_type TValue, sparse_set_integral TIndex>
    void SparseSet<TValue, TIndex>::clear() noexcept
    {
        mValues.clear();
        mIndices.clear();
        mIndexToValueIndex.clear();
    }
}
