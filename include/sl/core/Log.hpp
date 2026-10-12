// include/sl/core/Log.hpp

#pragma once

#include <cstdint>
#include <format>

#include "sl/String.hpp"
#include "sl/Traits.hpp"

namespace sl::core
{
    enum struct LogLevel : uint8_t { eDebug, eSuccess, eWarning, eError, eFatal, eMessage };
}

namespace sl::core
{
    class Log : private NonConstructable
    {
    public:
        static void Print(LogLevel level, const String& message);
    };
}

#if defined(_DEBUG)
    #define SL_LOG_DEBUG(_message_, ...) sl::core::Log::Print(sl::core::LogLevel::eDebug, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#else
    #define SL_LOG_DEBUG(_message_, ...)
#endif

#define SL_LOG_SUCCESS(_message_, ...) sl::core::Log::Print(sl::core::LogLevel::eSuccess, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#define SL_LOG_WARNING(_message_, ...) sl::core::Log::Print(sl::core::LogLevel::eWarning, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#define SL_LOG_ERROR(_message_, ...)   sl::core::Log::Print(sl::core::LogLevel::eError,   std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#define SL_LOG_FATAL(_message_, ...)   sl::core::Log::Print(sl::core::LogLevel::eFatal,   std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#define SL_LOG_MESSAGE(_message_, ...) sl::core::Log::Print(sl::core::LogLevel::eMessage, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
