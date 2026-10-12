// include/sl/ForwardList.hpp

#pragma once

#include <forward_list>

#include "sl/Memory.hpp"

namespace sl
{
    template<typename T, class _Allocator = DefaultAllocator<T>>
    using ForwardList = std::forward_list<T, _Allocator>;
}
