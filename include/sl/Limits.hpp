// include/sl/Limits.hpp

#pragma once

#include <concepts>
#include <limits>

namespace sl
{
    template<std::integral _Integral>
    using NumericLimits = std::numeric_limits<_Integral>;
}
