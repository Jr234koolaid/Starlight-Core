// include/sl/SparseSet.hpp

#pragma once

#include <concepts>
#include <cstddef>
#include <limits>
#include <utility>
#include <type_traits>

#include "sl/Assert.hpp"
#include "sl/Define.hpp"
#include "sl/Trait.hpp"
#include "sl/Type.hpp"

namespace sl
{
    template<typename T>
    concept sparse_set_type = std::is_object_v<T> and not std::is_const_v<T>;
}

namespace sl
{
    template<typename TValue>
    concept sparse_set_value_class    = sparse_set_type<TValue> and std::is_class_v<TValue> and std::default_initializable<TValue> and std::movable<TValue>;
    template<typename TValue>
    concept sparse_set_value_integral = sparse_set_type<TValue> and std::integral<TValue>;
    template<typename TValue>
    concept sparse_set_value          = sparse_set_value_class<TValue> or sparse_set_value_integral<TValue>;
}

namespace sl
{
    template<typename TIndex>
    concept sparse_set_index = sparse_set_type<TIndex> and std::unsigned_integral<TIndex> and not std::same_as<TIndex, bool>;
}

namespace sl
{
    template<typename>
    struct SparseSetValueIsUniquePtr : public std::false_type { };

    template<typename TValue, typename TDeleter>
    struct SparseSetValueIsUniquePtr<UniquePtr<TValue, TDeleter>> : public std::true_type { };
}

namespace sl
{
    template<typename TValue>
    concept sparse_set_unique_ptr_value      = sparse_set_value<TValue> and SparseSetValueIsUniquePtr<TValue>::value;
    template<typename TValue, typename TTo>
    concept sparse_set_unique_ptr_constraint = sparse_set_unique_ptr_value<TValue> and sparse_set_value<TTo> and std::convertible_to<UniquePtr<TTo>, TValue>;
}

namespace sl
{
    template<typename>
    struct SparseSetValueIsSharedPtr : public std::false_type { };

    template<typename TValue>
    struct SparseSetValueIsSharedPtr<SharedPtr<TValue>> : public std::true_type { };
}

namespace sl
{
    template<typename TValue>
    concept sparse_set_shared_ptr_value      = sparse_set_value<TValue> and SparseSetValueIsSharedPtr<TValue>::value;
    template<typename TValue, typename TTo>
    concept sparse_set_shared_ptr_constraint = sparse_set_shared_ptr_value<TValue> and sparse_set_value<TTo> and std::convertible_to<SharedPtr<TTo>, TValue>;
}

namespace sl
{
    template<typename TValue>
    concept sparse_set_smart_ptr_value      = sparse_set_unique_ptr_value<TValue> or sparse_set_shared_ptr_value<TValue>;
    template<typename TValue, typename TTo>
    concept sparse_set_smart_ptr_constraint = sparse_set_unique_ptr_constraint<TValue, TTo> or sparse_set_shared_ptr_constraint<TValue, TTo>;
}

namespace sl
{
    template<sparse_set_smart_ptr_value TValue>
    using SparseSetValueElementType = typename TValue::element_type;
}

namespace sl
{
    inline constexpr size_t SparseSetTombstone = NumericLimits<size_t>::max();
}

namespace sl
{
    template<sparse_set_type TValue, sparse_set_index TIndex = size_t, size_t _PageSize = 256U>
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
    private:
        void grow(size_t _pindex)
        {
            if (const size_t pagesize = mSparse.size(); _pindex >= pagesize)
            {
                const size_t newsize = _pindex + 1U;
                mSparse.resize(newsize);
                for (size_t i = pagesize; i < newsize; ++i)
                    mSparse[i].fill(SparseSetTombstone);
            }
        }
    private:
        template<class... UArgs>
        void append(UArgs&&... _args)
        {
            if constexpr (sparse_set_unique_ptr_value<TValue>)
                mValue.emplace_back(std::make_unique<SparseSetValueElementType<TValue>>(std::forward<UArgs>(_args)...));
            else if constexpr (sparse_set_shared_ptr_value<TValue>)
                mValue.emplace_back(std::make_shared<SparseSetValueElementType<TValue>>(std::forward<UArgs>(_args)...));
            else
                mValue.emplace_back(std::forward<UArgs>(_args)...);
        }
    public:
        template<class... UArgs>
        void emplace(TIndex _index, UArgs&&... _args)
        {
            const size_t pi = pindex(_index);
            const size_t si = sindex(_index);
            if (!contains(_index, pi, si))
            {
                grow(pi);

                mSparse[pi][si] = mDense.size();

                mDense.push_back(_index);

                append(std::forward<UArgs>(_args)...);
            }
        }
    private:
        template<typename UTo, class... UArgs> requires sparse_set_smart_ptr_constraint<TValue, UTo>
        void append(UArgs&&... _args)
        {
            if constexpr (sparse_set_unique_ptr_value<TValue>)
                mValue.emplace_back(std::make_unique<UTo>(std::forward<UArgs>(_args)...));
            else if constexpr (sparse_set_shared_ptr_value<TValue>)
                mValue.emplace_back(std::make_shared<UTo>(std::forward<UArgs>(_args)...));
            else
                static_assert(false, "SparseSet smart pointer append cannot append non-smart pointer type");
        }
    public:
        template<typename UTo, class... UArgs> requires sparse_set_smart_ptr_constraint<TValue, UTo>
        void emplace(TIndex _index, UArgs&&... _args)
        {
            const size_t pi = pindex(_index);
            const size_t si = sindex(_index);
            if (!contains(_index, pi, si))
            {
                grow(pi);

                mSparse[pi][si] = mDense.size();

                mDense.push_back(_index);

                append<UTo>(std::forward<UArgs>(_args)...);
            }
        }
    public:
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
