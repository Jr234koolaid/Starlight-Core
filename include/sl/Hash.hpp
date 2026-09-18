// include/sl/Hash.hpp

#pragma once

#include <concepts>
#include <cstddef>
#include <functional>
#include <ranges>

#include "sl/Define.hpp"
#include "sl/Type.hpp"

// https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key/12996028#12996028
// https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector/72073933#72073933
// https://stackoverflow.com/a/76076289

// This might be against the standard
namespace std
{
    template<class T>
    struct hash<sl::Reference<T>>
    {
        SL_NODISCARD size_t operator()(const sl::Reference<T>& t) const noexcept { return hash<T>()(t); }
    };
}

namespace sl
{
    SL_NODISCARD inline size_t HashCombine(size_t seed, size_t hash) noexcept
    {
        hash = (hash ^ (hash >> 30U)) * 0xBF58476D1CE4E5B9;
        hash = (hash ^ (hash >> 27U)) * 0x94D049BB133111EB;
        hash = (hash ^ (hash >> 31U));
        return seed ^ (hash + 0x9E3779B9 + (seed << 6U) + (seed >> 2U));
    }
}

namespace sl
{
    template<std::ranges::range TContainer>
    SL_NODISCARD inline size_t HashAll(const TContainer& container) noexcept
    {
        Hash<typename TContainer::value_type> hasher;

        size_t seed = container.size();
        for (const auto& value : container)
            seed = HashCombine(seed, hasher(value));

        return seed;
    }
}

namespace sl
{
    template<std::ranges::range TContainer> requires std::same_as<typename TContainer::value_type, Byte>
    SL_NODISCARD inline size_t HashAll(const TContainer& container) noexcept
    {
        // Apparent hash optimization for byte buffers
        return Hash<StringView>()(StringView(reinterpret_cast<const char*>(container.data()), container.size()));
    }
}
