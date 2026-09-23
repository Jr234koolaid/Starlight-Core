// include/sl/utility/Log.hpp

#pragma once

#include <cstdint>
#include <format>

#include "sl/Type.hpp"

namespace sl::utility
{
    enum struct LogLevel : uint8_t { LOG_DEBUG, LOG_SUCCESS, LOG_WARNING, LOG_ERROR, LOG_FATAL, LOG_MESSAGE };
}

namespace sl::utility
{
    void LogMessage(LogLevel level, const String& message);
}

#if defined(_DEBUG)
    #define SL_LOG_DEBUG(_message_, ...) sl::utility::LogMessage(sl::utility::LogLevel::LOG_DEBUG, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#else
    #define SL_LOG_DEBUG(_message_, ...)
#endif

#define SL_LOG_SUCCESS(_message_, ...) sl::utility::LogMessage(sl::utility::LogLevel::LOG_SUCCESS, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#define SL_LOG_WARNING(_message_, ...) sl::utility::LogMessage(sl::utility::LogLevel::LOG_WARNING, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#define SL_LOG_ERROR(_message_, ...)   sl::utility::LogMessage(sl::utility::LogLevel::LOG_ERROR,   std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#define SL_LOG_FATAL(_message_, ...)   sl::utility::LogMessage(sl::utility::LogLevel::LOG_FATAL,   std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#define SL_LOG_MESSAGE(_message_, ...) sl::utility::LogMessage(sl::utility::LogLevel::LOG_MESSAGE, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
