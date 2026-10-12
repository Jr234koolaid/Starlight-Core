// include/sl/Vector.hpp

#pragma once

#include <vector>

#include "sl/Memory.hpp"

namespace sl
{
    template<typename T, class _Allocator = DefaultAllocator<T>>
    using Vector = std::vector<T, _Allocator>;
}
