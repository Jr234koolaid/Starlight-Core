// include/sl/UnorderedSet.hpp

#pragma once

#include <unordered_set>

#include "sl/Functional.hpp"
#include "sl/Memory.hpp"

namespace sl
{
    template<typename T, class _Hasher = Hash<T>, class _Equal = Equal<T>, class _Allocator = DefaultAllocator<T>>
    using HashSet = std::unordered_set<T, _Hasher, _Equal, _Allocator>;
}
