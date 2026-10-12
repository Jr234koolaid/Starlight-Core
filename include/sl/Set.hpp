// include/sl/Set.hpp

#pragma once

#include <set>

#include "sl/Functional.hpp"
#include "sl/Memory.hpp"

namespace sl
{
    template<typename T, class _Compare = Less<T>, class _Allocator = DefaultAllocator<T>>
    using Set = std::set<T, _Compare, _Allocator>;
}
