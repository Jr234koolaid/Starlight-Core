// include/sl/Random.hpp

#pragma once

#include <concepts>
#include <random>

namespace sl
{
    template<std::integral _Integral = int32_t>
    using UniformIntDistribution = std::uniform_int_distribution<_Integral>;
}

namespace sl
{
    using RandomDevice      = std::random_device;
    using MersenneTwister32 = std::mt19937;
    using MersenneTwister64 = std::mt19937_64;
}
