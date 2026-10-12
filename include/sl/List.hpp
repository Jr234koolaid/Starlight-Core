// include/sl/List.hpp

#pragma once

#include <list>

#include "sl/Memory.hpp"

namespace sl
{
    template<typename T, class _Allocator = DefaultAllocator<T>>
    using List = std::list<T, _Allocator>;
}
