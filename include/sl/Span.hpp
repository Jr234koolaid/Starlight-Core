// include/sl/Span.hpp

#pragma once

#include <span>

namespace sl
{
    template<typename T, size_t _Extent = std::dynamic_extent>
    using Span = std::span<T, _Extent>;
}
