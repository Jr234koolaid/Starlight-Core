// include/sl/UnorderedMap.hpp

#pragma once

#include <unordered_map>

#include "sl/Functional.hpp"
#include "sl/Memory.hpp"
#include "sl/Utility.hpp"

namespace sl
{
    template<class _Key, typename T, class _Hasher = Hash<_Key>, class _Equal = Equal<_Key>, class _Allocator = DefaultAllocator<Pair<const _Key, T>>>
    using HashMap      = std::unordered_map<_Key, T, _Hasher, _Equal, _Allocator>;
    template<class _Key, typename T, class _Hasher = Hash<_Key>, class _Equal = Equal<_Key>, class _Allocator = DefaultAllocator<Pair<const _Key, T>>>
    using HashMultiMap = std::unordered_multimap<_Key, T, _Hasher, _Equal, _Allocator>;
}
