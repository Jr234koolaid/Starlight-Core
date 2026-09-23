// src/sl/utility/MultiByteString.cpp

#include <cstdint>

#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

#include "sl/Assert.hpp"
#include "sl/Check.hpp"
#include "sl/Define.hpp"
#include "sl/Type.hpp"
#include "sl/utility/MultiByteString.hpp"

namespace sl::utility
{
#if defined(_WIN32)
    static Wstring Win32MultiByteStringWiden(StringView string)
    {
        const int32_t convertsize = ::MultiByteToWideChar(CP_UTF8, 0x0, string.data(), static_cast<int32_t>(string.size()), nullptr, 0);
        SL_CHECK(convertsize != 0U, Wstring{ }, "Win32 MultiByteString expects widened string convert size to be valid");

        Wstring buffer(convertsize, L'\0');

        const int32_t convertedsize = ::MultiByteToWideChar(CP_UTF8, 0x0, string.data(), static_cast<int32_t>(string.size()), buffer.data(), convertsize);
        SL_CHECK(convertsize == convertedsize, Wstring{ }, "Win32 MultiByteString expects widened string converted size to match convert size");

        return buffer;
    }
#endif
}

namespace sl::utility
{
    Wstring MultiByteStringWiden(StringView string)
    {
        SL_ASSERT(!string.empty(), "MultiByteString string is expected to be valid");
#if defined(_WIN32)
        return Win32MultiByteStringWiden(string);
#endif
    }
}
