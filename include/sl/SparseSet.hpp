// include\sl\SparseSet.hpp

#pragma once

#include <cstddef>
#include <type_traits>

#include "sl\Define.hpp"
#include "sl\PageSet.hpp"
#include "sl\Trait.hpp"
#include "sl\Type.hpp"

namespace sl
{
    template<typename T>
    concept sparse_set_type = std::is_object_v<T>;

    template<typename T>
    concept sparse_set_integral = std::is_integral_v<T>;
}

namespace sl
{
    template<sparse_set_type TValue>
    class ISparseSet : private NonCopyable
    {
    public:
        virtual ~ISparseSet() = default;

    public:
        virtual void erase(TValue) noexcept = 0;

    public:
        virtual void clear() noexcept = 0;
    };
}

namespace sl
{
    template<sparse_set_type TValue, sparse_set_integral TIndex = size_t>
    class SparseSet : public ISparseSet<TValue>
    {
    public:
        SparseSet() = default;
        SparseSet(SparseSet&& _other) noexcept;
       ~SparseSet() = default;

    public:
        SparseSet& operator=(SparseSet&& _other) noexcept;

    public:
        SL_NODISCARD TValue& at(TIndex _index) noexcept;
        SL_NODISCARD const TValue& at(TIndex _index) const noexcept;

    public:
        SL_NODISCARD bool contains(TIndex _index) const noexcept;

    public:
        template<class... UArgs>
        SL_NODISCARD bool emplace(TIndex _index, UArgs&&... _args);

    public:
        void erase(TIndex _index) noexcept override;

    public:
        void clear() noexcept override;

    private:
        PageSet<size_t, TIndex> mIndexToValueIndex;
        Vector<TIndex>          mIndices;
        Vector<TValue>          mValues;
    };
}

// Implementation:
#include "sl\SparseSet.inl"
