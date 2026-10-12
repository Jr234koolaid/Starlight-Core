// include/sl/Tuple.hpp

#pragma once

#include <tuple>

namespace sl
{
    template<typename T, typename... Us>
    using Tuple = std::tuple<T, Us...>;
}
