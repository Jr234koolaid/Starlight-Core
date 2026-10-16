// include/sl/Character.hpp

#pragma once

#include <cctype>

#include "sl/Attributes.hpp"

namespace sl
{
    SL_NODISCARD inline decltype(auto) upper_cast(char character) { return static_cast<char>(std::toupper(static_cast<unsigned char>(character))); }
    SL_NODISCARD inline decltype(auto) lower_cast(char character) { return static_cast<char>(std::tolower(static_cast<unsigned char>(character))); }
}
