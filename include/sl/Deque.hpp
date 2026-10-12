// include/sl/Deque.hpp

#pragma once

#include <deque>

#include "sl/Memory.hpp"

namespace sl
{
    template<typename T, class _Allocator = DefaultAllocator<T>>
    using Deque = std::deque<T, _Allocator>;
}
