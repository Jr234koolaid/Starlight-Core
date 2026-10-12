// include/sl/Map.hpp

#pragma once

#include <map>

#include "sl/Functional.hpp"
#include "sl/Memory.hpp"
#include "sl/Utility.hpp"

namespace sl
{
    template<class _Key, typename T, class _Compare = Less<_Key>, class _Allocator = DefaultAllocator<Pair<const _Key, T>>>
    using Map      = std::map<_Key, T, _Compare, _Allocator>;
    template<class _Key, typename T, class _Compare = Less<_Key>, class _Allocator = DefaultAllocator<Pair<const _Key, T>>>
    using MultiMap = std::multimap<_Key, T, _Compare, _Allocator>;
}
