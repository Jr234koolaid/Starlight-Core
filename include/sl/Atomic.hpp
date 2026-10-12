// include/sl/Atomic.hpp

#pragma once

#include <atomic>

namespace sl
{
    template<typename T>
    using Atomic = std::atomic<T>;
}
