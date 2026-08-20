// include/sl/Hash.hpp

#pragma once

#include <concepts>
#include <cstddef>
#include <type_traits>

#include "sl\Define.hpp"
#include "sl\Type.hpp"

// https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key/12996028#12996028
// https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector/72073933#72073933
// https://stackoverflow.com/a/76076289

namespace sl
{
    SL_NODISCARD inline size_t HashCombine(size_t _seed, size_t _hash) noexcept
    {
        _hash = (_hash ^ (_hash >> 30U)) * 0xBF58476D1CE4E5B9;
        _hash = (_hash ^ (_hash >> 27U)) * 0x94D049BB133111EB;
        _hash = (_hash ^ (_hash >> 31U));
        return _seed ^ (_hash + 0x9E3779B9 + (_seed << 6U) + (_seed >> 2U));
    }
}

namespace sl
{
    template<typename T>
    struct HashAllTraits
    {
        using type = T;
    };

    template<typename T>
    struct HashAllTraits<Reference<T>>
    {
        using type = T;
    };
}

namespace sl
{
    template<typename TContainer>
    concept hash_all_container_type = std::is_class_v<TContainer> and requires(const TContainer& _Container) {
        { _Container.size() } -> std::convertible_to<size_t>;
    };
}

namespace sl
{
    template<hash_all_container_type TContainer>
    SL_NODISCARD inline size_t HashAll(const TContainer& _container) noexcept
    {
        //using TValue = std::remove_cv_t<typename HashAllTraits<typename TContainer::value_type>::type>;
        using TValue = typename HashAllTraits<typename TContainer::value_type>::type;

        Hash<TValue> hasher;

        size_t seed = _container.size();
        for (const TValue& value : _container)
            seed = HashCombine(seed, hasher(value));

        return seed;
    }
}

namespace sl
{
    template<typename TContainer>
    concept hash_all_byte_type = std::same_as<typename TContainer::value_type, Byte>;

    template<typename TContainer>
    concept hash_all_byte_container_type = (
        hash_all_container_type<TContainer> and hash_all_byte_type<TContainer> and requires(const TContainer& _Container) {
            { _Container.data() } -> std::convertible_to<const Byte*>;
        }
    );
}

namespace sl
{
    template<hash_all_byte_container_type TContainer>
    SL_NODISCARD inline size_t HashAll(const TContainer& _container) noexcept
    {
        // Apparent hash optimization for byte buffers
        return Hash<StringView>()(StringView(reinterpret_cast<const char*>(_container.data()), _container.size()));
    }
}
