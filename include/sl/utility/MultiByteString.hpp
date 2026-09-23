// include/sl/utility/MultiByteString.hpp

#pragma once

#include "sl/Define.hpp"
#include "sl/Type.hpp"

namespace sl::utility
{
    SL_NODISCARD Wstring MultiByteStringWiden(StringView string);
}
