// include/sl/Chrono.hpp

#pragma once

#include <chrono>

namespace sl
{
    using TimePoint = std::chrono::steady_clock::time_point;
}

namespace sl
{
    using Nanoseconds  = std::chrono::nanoseconds::period;
    using Microseconds = std::chrono::microseconds::period;
    using Milliseconds = std::chrono::milliseconds::period;
    using Seconds      = std::chrono::seconds::period;
    using Minutes      = std::chrono::minutes::period;
    using Hours        = std::chrono::hours::period;
    using Days         = std::chrono::days::period;
    using Weeks        = std::chrono::weeks::period;
    using Years        = std::chrono::years::period;
    using Months       = std::chrono::months::period;
}
