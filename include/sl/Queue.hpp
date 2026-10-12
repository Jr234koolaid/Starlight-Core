// include/sl/Queue.hpp

#pragma once

#include <queue>

#include "sl/Deque.hpp"
#include "sl/Functional.hpp"
#include "sl/Vector.hpp"

namespace sl
{
    template<typename T, class _Container = Deque<T>>
    using Queue         = std::queue<T, _Container>;
    template<typename T, class _Container = Vector<T>, class _Compare = Less<typename _Container::value_type>>
    using PriorityQueue = std::priority_queue<T, _Container, _Compare>;
}
