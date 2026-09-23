// include/sl/Character.hpp

#pragma once

#include <cctype>

#include "sl/Define.hpp"

namespace sl
{
    SL_NODISCARD inline char upper_cast(char c) { return static_cast<char>(std::toupper(static_cast<unsigned char>(c))); }
    SL_NODISCARD inline char lower_cast(char c) { return static_cast<char>(std::tolower(static_cast<unsigned char>(c))); }
}
