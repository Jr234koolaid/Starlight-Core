// src/sl/String.cpp

#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN

    #include <Windows.h>

    #undef SUCCESS
    #undef WARNING
    #undef ERROR
    #undef FATAL
    #undef DEBUG
    #undef MESSAGE
#endif

#include <cstdint>

#include "sl/Check.hpp"
#include "sl/Define.hpp"
#include "sl/Type.hpp"
#include "sl/String.hpp"

namespace sl
{
#if defined(_WIN32)
    static Wstring Win32WidenString(StringView _string)
    {
        const int32_t convertsize = ::MultiByteToWideChar(CP_UTF8, 0x0, _string.data(), static_cast<int32_t>(_string.size()), nullptr, 0);
        SL_CHECK(convertsize != 0U, Wstring{ }, "Win32 String expects widened string convert size to be valid");

        Wstring wstring(convertsize, 0);

        const int32_t convertedsize = ::MultiByteToWideChar(CP_UTF8, 0x0, _string.data(), static_cast<int32_t>(_string.size()), wstring.data(), convertsize);
        SL_CHECK(convertsize == convertedsize, Wstring{ }, "Win32 String expects widened string converted size to match convert size");

        return wstring;
    }
#endif
}

namespace sl
{
    Wstring WidenString(StringView _string)
    {
#if defined(_WIN32)
    return Win32WidenString(_string);
#endif
    }
}
