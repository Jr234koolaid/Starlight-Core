// src/sl/core/MultiByteString.cpp

#include "sl/Platform.hpp"

#include <cstdint>
#include <optional>

#if defined(SL_PLATFORM_WINDOWS)
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#elif defined(SL_PLATFORM_LINUX)
#elif defined(SL_PLATFORM_MAC)
#elif defined(SL_PLATFORM_ANDROID)
#endif

#include "sl/Assert.hpp"
#include "sl/Attributes.hpp"
#include "sl/Optional.hpp"
#include "sl/String.hpp"
#include "sl/Validate.hpp"
#include "sl/core/MultiByteString.hpp"

#if defined(SL_PLATFORM_WINDOWS)
namespace sl::core
{
    Optional<Wstring> MultiByteStringToWideString(const String& string) {
        SL_ASSERT_IF(string.empty(), "Win32 expects multi-byte string to be valid");

        const int32_t charactercount = ::MultiByteToWideChar(CP_UTF8, 0x0, string.data(), static_cast<int32_t>(string.size()), nullptr, 0);
        SL_VALIDATE(charactercount != 0, std::nullopt, "Win32 expects converted wide string character count to be valid");

        Wstring buffer(charactercount, L'\0');

        const int32_t size = ::MultiByteToWideChar(CP_UTF8, 0x0, string.data(), static_cast<int32_t>(string.size()), buffer.data(), charactercount);
        SL_VALIDATE(size == charactercount, std::nullopt, "Win32 expects converted wide string size to match character count");

        return buffer;
    }
}
#elif defined(SL_PLATFORM_LINUX)
namespace sl::core
{
    Optional<Wstring> MultiByteStringToWideString(const String& string) {
        return std::nullopt;
    }
}
#elif defined(SL_PLATFORM_MAC)
namespace sl::core
{
    Optional<Wstring> MultiByteStringToWideString(const String& string) {
        return std::nullopt;
    }
}
#elif defined(SL_PLATFORM_ANDROID)
namespace sl::core
{
    Optional<Wstring> MultiByteStringToWideString(const String& string) {
        return std::nullopt;
    }
}
#endif

#if defined(SL_PLATFORM_WINDOWS)
namespace sl::core
{
    Optional<String> WideStringToMultiByteString(const Wstring& wstring) {
        SL_ASSERT_IF(wstring.empty(), "Win32 expects wide string to be valid");

        const int32_t bytecount = ::WideCharToMultiByte(CP_UTF8, 0x0, wstring.data(), static_cast<int32_t>(wstring.size()), nullptr, 0, nullptr, nullptr);
        SL_VALIDATE(bytecount != 0, std::nullopt, "Win32 MultiByteString expects converted string byte count to be valid");

        String buffer(bytecount, '\0');

        const int32_t size = ::WideCharToMultiByte(CP_UTF8, 0x0, wstring.data(), static_cast<int32_t>(wstring.size()), buffer.data(), bytecount, nullptr, nullptr);
        SL_VALIDATE(size == bytecount, std::nullopt, "Win32 MultiByteString expects converted string size to match byte count");

        return buffer;
    }
}
#elif defined(SL_PLATFORM_LINUX)
namespace sl::core
{
    Optional<String> WideStringToMultiByteString(const Wstring& wstring) {
        return std::nullopt;
    }
}
#elif defined(SL_PLATFORM_MAC)
namespace sl::core
{
    Optional<String> WideStringToMultiByteString(const Wstring& wstring) {
        return std::nullopt;
    }
}
#elif defined(SL_PLATFORM_ANDROID)
namespace sl::core
{
    Optional<String> WideStringToMultiByteString(const Wstring& wstring) {
        return std::nullopt;
    }
}
#endif
