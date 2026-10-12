// include/sl/Functional.hpp

#pragma once

#include <functional>

namespace sl
{
    template<typename T>
    using Hash = std::hash<T>;
}

namespace sl
{
    template<typename T>
    using Reference = std::reference_wrapper<T>;
}

namespace sl
{
    template<class _Func>
    using Function = std::function<_Func>;
}

namespace sl
{
    template<typename T = void>
    using Equal        = std::equal_to<T>;
    template<typename T = void>
    using NotEqual     = std::not_equal_to<T>;
    template<typename T = void>
    using Greater      = std::greater<T>;
    template<typename T = void>
    using GreaterEqual = std::greater_equal<T>;
    template<typename T = void>
    using Less         = std::less<T>;
    template<typename T = void>
    using LessEqual    = std::less_equal<T>;
}
