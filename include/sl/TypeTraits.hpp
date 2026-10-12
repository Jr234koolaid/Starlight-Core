// include/sl/TypeTraits.hpp

#pragma once

#include <type_traits>

namespace sl
{
    template<typename T>
    using UnderlyingType = std::underlying_type_t<T>;
}

namespace sl
{
    template<typename T, T _Val>
    using IntegralConstant = std::integral_constant<T, _Val>;
}

namespace sl
{
    using Truable  = std::true_type;
    using Falsable = std::false_type;
}
