// include/sl/Stack.hpp

#pragma once

#include <stack>

#include "sl/Deque.hpp"

namespace sl
{
    template<typename T, class _Container = Deque<T>>
    using Stack = std::stack<T, _Container>;
}
