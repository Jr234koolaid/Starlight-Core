// include/sl/core/win32/String.hpp

#pragma once

#include "sl/Platform.hpp"

#if defined(SL_PLATFORM_WINDOWS)

#include "sl/Attributes.hpp"
#include "sl/Optional.hpp"
#include "sl/String.hpp"

namespace sl::core
{
    SL_NODISCARD Optional<Wstring> MultiByteStringToWide(const String& string);
}

namespace sl::core
{
    SL_NODISCARD Optional<String> WideStringToMultiByte(const Wstring& string);
}
#endif