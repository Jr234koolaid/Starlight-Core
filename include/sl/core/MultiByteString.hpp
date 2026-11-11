// include/sl/core/MultiByteString.hpp

#pragma once

#include "sl/Attributes.hpp"
#include "sl/Optional.hpp"
#include "sl/String.hpp"

namespace sl::core
{
    SL_NODISCARD Optional<Wstring> MultiByteStringToWideString(const String& string);
}

namespace sl::core
{
    SL_NODISCARD Optional<String> WideStringToMultiByteString(const Wstring& wstring);
}
