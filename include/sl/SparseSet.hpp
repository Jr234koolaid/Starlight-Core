// include/sl/SparseSet.hpp

#pragma once

#include <cstddef>
#include <limits>
#include <utility>
#include <type_traits>

#include "sl\Assert.hpp"
#include "sl\Define.hpp"
#include "sl\Trait.hpp"
#include "sl\Type.hpp"

namespace sl
{
    template<typename T>
    concept sparse_set_type = not std::is_const_v<T> and not std::is_reference_v<T>;
}

namespace sl
{
    template<typename T>
    concept sparse_set_value_type          = sparse_set_type<T> and std::is_integral_v<T> or std::is_class_v<T>;
    template<typename T>
    concept sparse_set_value_constructable = sparse_set_type<T> and std::is_default_constructible_v<T> and std::is_move_constructible_v<T>;
    template<typename T>
    concept sparse_set_value_assignable    = sparse_set_type<T> and std::is_move_assignable_v<T>;
    template<typename T>
    concept sparse_set_value               = sparse_set_value_type<T> and sparse_set_value_constructable<T> and sparse_set_value_assignable<T>;
}

namespace sl
{
    template<typename T>
    concept sparse_set_integral = sparse_set_value<T> and std::is_integral_v<T>;
}

namespace sl
{
    inline constexpr size_t SparseSetTombstone = std::numeric_limits<size_t>::max();
}

namespace sl
{
    template<sparse_set_type TValue, sparse_set_integral TIndex = size_t, size_t _PageSize = 256U>
    class SparseSet : public NonCopyable
    {
    public:
        SparseSet() = default;
       ~SparseSet() = default;
    public:
        SparseSet(SparseSet&& _other) noexcept:
            mSparse(std::move(_other.mSparse)),
            mDense (std::move(_other.mDense)),
            mValue (std::move(_other.mValue))
        {
        }
    public:
        SparseSet& operator=(SparseSet&& _other) noexcept
        {
            if (this != &_other)
            {
                mValue  = std::move(_other.mValue);
                mDense  = std::move(_other.mDense);
                mSparse = std::move(_other.mSparse);
            }
            return *this;
        }
    public:
        SL_NODISCARD Span<const TValue> values() const noexcept
        {
            return mValue;
        }

        SL_NODISCARD Span<const TIndex> indices() const noexcept
        {
            return mDense;
        }
    private:
        SL_NODISCARD size_t pindex(TIndex _index) const noexcept
        {
            return static_cast<size_t>(_index) / _PageSize;
        }

        SL_NODISCARD size_t sindex(TIndex _index) const noexcept
        {
            return static_cast<size_t>(_index) % _PageSize;
        }
    private:
        SL_NODISCARD size_t& index(TIndex _index) noexcept
        {
            const size_t pi = pindex(_index);
            const size_t si = sindex(_index);
            return index(pi, si);
        }

        SL_NODISCARD size_t& index(size_t _pindex, size_t _sindex) noexcept
        {
            return mSparse[_pindex][_sindex];
        }
    public:
        SL_NODISCARD TValue& at(TIndex _index) noexcept
        {
            const size_t pi = pindex(_index);
            const size_t si = sindex(_index);
            SL_ASSERT(contains(_index, pi, si), "SparseSet expects to contain a value at the given index: {}", _index);

            return mValue[index(pi, si)];
        }

        SL_NODISCARD const TValue& at(TIndex _index) const noexcept
        {
            const size_t pi = pindex(_index);
            const size_t si = sindex(_index);
            SL_ASSERT(contains(_index, pi, si), "SparseSet expects to contain a value at then given index: {}", _index);

            return mValue[index(pi, si)];
        }
    private:
        SL_NODISCARD bool contains(TIndex _index, size_t _pindex, size_t _sindex)
        {
            return contains(_pindex, _sindex) && (mDense[index(_pindex, _sindex)] == _index);
        }

        SL_NODISCARD bool contains(size_t _pindex, size_t _sindex)
        {
            return (_pindex < mSparse.size()) && (_sindex < mSparse[_pindex].size()) && (index(_pindex, _sindex) < mDense.size());
        }
    public:
        SL_NODISCARD bool contains(TIndex _index) const noexcept
        {
            const size_t pi = pindex(_index);
            const size_t si = sindex(_index);
            return contains(_index, pi, si);
        }
    public:
        template<class... UArgs>
        void emplace(TIndex _index, UArgs&&... _args)
        {
            const size_t pi = pindex(_index);
            const size_t si = sindex(_index);

            if (!contains(_index, pi, si))
            {
                const size_t pagesize = mSparse.size();
                if (pi >= pagesize)
                {
                    const size_t newsize = pi + 1U;

                    mSparse.resize(newsize);
                    for (size_t i = pagesize; i < newsize; ++i)
                        mSparse[i].fill(SparseSetTombstone);
                }

                mSparse[pi][si] = mDense.size();

                mDense.push_back(_index);

                mValue.emplace_back(std::forward<UArgs>(_args)...);
            }
        }

        void erase(TIndex _index) noexcept
        {
            const size_t pi = pindex(_index);
            const size_t si = sindex(_index);

            if (contains(_index, pi, si))
            {
                size_t& rindex = index(pi, si);

                const size_t lindex = mDense.size() - 1U;
                if (lindex != rindex)
                {
                    const TIndex last = mDense[lindex];

                    mDense[rindex] = last;
                    mValue[rindex] = std::move(mValue[lindex]);

                    index(last) = rindex;
                }

                mValue.pop_back();
                mDense.pop_back();

                rindex = SparseSetTombstone;
            }
        }
    public:
        void clear() noexcept
        {
            mValue.clear();
            mDense.clear();
            mSparse.clear();
        }
    private:
        Vector<Array<size_t, _PageSize>> mSparse;
        Vector<TIndex>                   mDense;
        Vector<TValue>                   mValue;
    };
}
