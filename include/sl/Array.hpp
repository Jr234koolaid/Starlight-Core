// include/sl/Array.hpp

#pragma once

#include <array>
#include <cstddef>

namespace sl
{
    template<typename T, size_t _Size>
    using Array = std::array<T, _Size>;
}
