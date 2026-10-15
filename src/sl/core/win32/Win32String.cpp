// src/sl/core/win32/String.cpp

#include "sl/Platform.hpp"

#if defined(SL_PLATFORM_WINDOWS)

#include <cstdint>
#include <optional>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "sl/Assert.hpp"
#include "sl/Attributes.hpp"
#include "sl/Check.hpp"
#include "sl/Optional.hpp"
#include "sl/String.hpp"
#include "sl/core/win32/String.hpp"

namespace sl::core
{
    static Optional<Wstring> MultiByteStringToWide(const String& string)
    {
        SL_ASSERT(!string.empty(), "Win32 expects multi-byte string to be valid");

        const int32_t charactercount = ::MultiByteToWideChar(CP_UTF8, 0x0, string.data(), static_cast<int32_t>(string.size()), nullptr, 0);
        SL_CHECK(charactercount != 0, std::nullopt, "Win32 expects converted wide string character count to be valid");

        Wstring buffer(charactercount, L'\0');

        const int32_t size = ::MultiByteToWideChar(CP_UTF8, 0x0, string.data(), static_cast<int32_t>(string.size()), buffer.data(), charactercount);
        SL_CHECK(size == charactercount, std::nullopt, "Win32 expects converted wide string size to match character count");

        return buffer;
    }
}

namespace sl::core
{
    static Optional<String> WideStringToMultiByte(const Wstring& string)
    {
        SL_ASSERT(!string.empty(), "Win32 expects wide string to be valid");

        const int32_t bytecount = ::WideCharToMultiByte(CP_UTF8, 0x0, string.data(), static_cast<int32_t>(string.size()), nullptr, 0, nullptr, nullptr);
        SL_CHECK(bytecount != 0, std::nullopt, "Win32 MultiByteString expects converted string byte count to be valid");

        String buffer(bytecount, '\0');

        const int32_t size = ::WideCharToMultiByte(CP_UTF8, 0x0, string.data(), static_cast<int32_t>(string.size()), buffer.data(), bytecount, nullptr, nullptr);
        SL_CHECK(size == bytecount, std::nullopt, "Win32 MultiByteString expects converted string size to match byte count");

        return buffer;
    }
}
#endif