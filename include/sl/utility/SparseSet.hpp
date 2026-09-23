// include/sl/utility/SparseSet.hpp

#pragma once

#include <concepts>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <utility>

#include "sl/Assert.hpp"
#include "sl/Define.hpp"
#include "sl/Trait.hpp"
#include "sl/Type.hpp"

namespace sl::utility
{
    template<class T>
    concept sparse_set_type = std::is_object_v<T> and not std::is_const_v<T>;
}

namespace sl::utility
{
    template<class TValue>
    concept sparse_set_value_class    = sparse_set_type<TValue> and std::is_class_v<TValue> and std::default_initializable<TValue> and std::movable<TValue>;
    template<class TValue>
    concept sparse_set_value_integral = sparse_set_type<TValue> and std::integral<TValue>;
    template<class TValue>
    concept sparse_set_value          = sparse_set_value_class<TValue> or sparse_set_value_integral<TValue>;
}

namespace sl::utility
{
    template<class TIndex>
    concept sparse_set_index = sparse_set_type<TIndex> and std::unsigned_integral<TIndex> and not std::same_as<TIndex, bool>;
}

namespace sl::utility
{
    template<class>
    struct SparseSetValueIsUniquePtr : public Falsable { };
    template<class TValue, class TDeleter>
    struct SparseSetValueIsUniquePtr<UniquePtr<TValue, TDeleter>> : public Truable { };
}

namespace sl::utility
{
    template<class TValue>
    concept sparse_set_unique_ptr_value      = sparse_set_value<TValue> and SparseSetValueIsUniquePtr<TValue>::value;
    template<class TValue, class TTo>
    concept sparse_set_unique_ptr_constraint = sparse_set_unique_ptr_value<TValue> and sparse_set_value<TTo> and std::convertible_to<UniquePtr<TTo>, TValue>;
}

namespace sl::utility
{
    template<class>
    struct SparseSetValueIsSharedPtr : public Falsable { };
    template<class TValue>
    struct SparseSetValueIsSharedPtr<SharedPtr<TValue>> : public Truable { };
}

namespace sl::utility
{
    template<typename TValue>
    concept sparse_set_shared_ptr_value      = sparse_set_value<TValue> and SparseSetValueIsSharedPtr<TValue>::value;
    template<typename TValue, typename TTo>
    concept sparse_set_shared_ptr_constraint = sparse_set_shared_ptr_value<TValue> and sparse_set_value<TTo> and std::convertible_to<SharedPtr<TTo>, TValue>;
}

namespace sl::utility
{
    template<typename TValue>
    concept sparse_set_smart_ptr_value      = sparse_set_unique_ptr_value<TValue> or sparse_set_shared_ptr_value<TValue>;
    template<typename TValue, typename TTo>
    concept sparse_set_smart_ptr_constraint = sparse_set_unique_ptr_constraint<TValue, TTo> or sparse_set_shared_ptr_constraint<TValue, TTo>;
}

namespace sl::utility
{
    template<sparse_set_smart_ptr_value TValue>
    using SparseSetValueElementType = typename TValue::element_type;
}

namespace sl::utility
{
    inline constexpr size_t SparseSetTombstone = NumericLimits<size_t>::max();
}

namespace sl::utility
{
    template<sparse_set_type TValue, sparse_set_index TIndex = size_t, size_t _PageSize = 256U>
    class SparseSet : public NonCopyable
    {
    public:
        constexpr SparseSet()  = default;
        constexpr ~SparseSet() = default;
    public:
        constexpr SparseSet(SparseSet&& other) noexcept:
            mSparse(std::move(other.mSparse)),
            mDense (std::move(other.mDense)),
            mValue (std::move(other.mValue))
        {
        }
    public:
        constexpr SparseSet& operator=(SparseSet&& other) noexcept
        {
            if (this != &other)
            {
                mValue  = std::move(other.mValue);
                mDense  = std::move(other.mDense);
                mSparse = std::move(other.mSparse);
            }
            return *this;
        }
    public:
        SL_NODISCARD constexpr Span<TValue> values() noexcept
        {
            return mValue;
        }

        SL_NODISCARD constexpr Span<const TValue> values() const noexcept
        {
            return mValue;
        }
    public:
        SL_NODISCARD constexpr Span<const TIndex> indices() const noexcept
        {
            return mDense;
        }
    private:
        SL_NODISCARD constexpr size_t pIndex(TIndex index) const noexcept
        {
            return static_cast<size_t>(index) / _PageSize;
        }

        SL_NODISCARD constexpr size_t sIndex(TIndex index) const noexcept
        {
            return static_cast<size_t>(index) % _PageSize;
        }
    public:
        SL_NODISCARD constexpr TValue& at(TIndex index) noexcept
        {
            const size_t pindex = pIndex(index);
            const size_t sindex = sIndex(index);
            SL_ASSERT(contains(index, pindex, sindex), "SparseSet expects to contain a value at the given index: '{}'", index);

            return mValue[mSparse[pindex][sindex]];
        }

        SL_NODISCARD constexpr const TValue& at(TIndex index) const noexcept
        {
            const size_t pindex = pIndex(index);
            const size_t sindex = sIndex(index);
            SL_ASSERT(contains(index, pindex, sindex), "SparseSet expects to contain a value at then given index: '{}'", index);

            return mValue[mSparse[pindex][sindex]];
        }
    private:
        SL_NODISCARD constexpr bool contains(size_t pindex, size_t sindex)
        {
            return (pindex < mSparse.size()) && (sindex < mSparse[pindex].size()) && (mSparse[pindex][sindex] < mDense.size());
        }

        SL_NODISCARD constexpr bool contains(TIndex index, size_t pindex, size_t sindex)
        {
            return contains(pindex, sindex) && (mDense[mSparse[pindex][sindex]] == index);
        }
    public:
        SL_NODISCARD constexpr bool contains(TIndex index) const noexcept
        {
            return contains(index, pIndex(index), sIndex(index));
        }
    private:
        constexpr void grow(size_t pindex)
        {
            if (const size_t pagesize = mSparse.size(); pindex >= pagesize)
            {
                const size_t newsize = pindex + 1U;
                mSparse.resize(newsize);

                for (size_t i = pagesize; i < newsize; ++i)
                    mSparse[i].fill(SparseSetTombstone);
            }
        }
    private:
        template<class... UArgs>
        constexpr void append(UArgs&&... args)
        {
            if constexpr (sparse_set_unique_ptr_value<TValue>)
                mValue.emplace_back(std::make_unique<SparseSetValueElementType<TValue>>(std::forward<UArgs>(args)...));
            else if constexpr (sparse_set_shared_ptr_value<TValue>)
                mValue.emplace_back(std::make_shared<SparseSetValueElementType<TValue>>(std::forward<UArgs>(args)...));
            else
                mValue.emplace_back(std::forward<UArgs>(args)...);
        }
    public:
        template<class... UArgs>
        constexpr void emplace(TIndex index, UArgs&&... args)
        {
            const size_t pindex = pIndex(index);
            const size_t sindex = sIndex(index);

            if (!contains(index, pindex, sindex))
            {
                grow(pindex);

                mSparse[pindex][sindex] = mDense.size();

                mDense.push_back(index);

                append(std::forward<UArgs>(args)...);
            }
        }
    private:
        template<typename UTo, class... UArgs> requires sparse_set_smart_ptr_constraint<TValue, UTo>
        constexpr void append(UArgs&&... args)
        {
            if constexpr (sparse_set_unique_ptr_value<TValue>)
                mValue.emplace_back(std::make_unique<UTo>(std::forward<UArgs>(args)...));
            else if constexpr (sparse_set_shared_ptr_value<TValue>)
                mValue.emplace_back(std::make_shared<UTo>(std::forward<UArgs>(args)...));
            else
                static_assert(false, "SparseSet smart pointer append cannot append non-smart pointer type");
        }
    public:
        template<typename UTo, class... UArgs> requires sparse_set_smart_ptr_constraint<TValue, UTo>
        constexpr void emplace(TIndex index, UArgs&&... args)
        {
            const size_t pindex = pIndex(index);
            const size_t sindex = sIndex(index);

            if (!contains(index, pindex, sindex))
            {
                grow(pindex);

                mSparse[pindex][sindex] = mDense.size();

                mDense.push_back(index);

                append<UTo>(std::forward<UArgs>(args)...);
            }
        }
    public:
        constexpr void erase(TIndex index) noexcept
        {
            const size_t pindex = pIndex(index);
            const size_t sindex = sIndex(index);

            if (contains(index, pindex, sindex))
            {
                size_t& rindex = mSparse[pindex][sindex];

                if (const size_t lindex = mDense.size() - 1U; lindex != rindex)
                {
                    const TIndex last = mDense[lindex];

                    mDense[rindex] = last;
                    mValue[rindex] = std::move(mValue[lindex]);

                    const size_t lpindex = pIndex(last);
                    const size_t lsindex = sIndex(last);
                    mSparse[lpindex][lsindex] = rindex;
                }

                mValue.pop_back();
                mDense.pop_back();

                rindex = SparseSetTombstone;
            }
        }
    public:
        constexpr void clear() noexcept
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
