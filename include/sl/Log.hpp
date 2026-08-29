// include/sl/Log.hpp

#pragma once

#include <cstdint>
#include <format>

#include "sl/Type.hpp"

namespace sl
{
    enum struct LogLevel : uint8_t { MESSAGE, DEBUG, SUCCESS, WARNING, ERROR, FATAL };
}

namespace sl
{
    void Log(LogLevel _level, const String& _fmessage);
}

#if defined(_DEBUG)
    #define SL_MESSAGE(_message_, ...) sl::Log(sl::LogLevel::MESSAGE, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
    #define SL_DEBUG(_message_, ...)   sl::Log(sl::LogLevel::DEBUG, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
    #define SL_SUCCESS(_message_, ...) sl::Log(sl::LogLevel::SUCCESS, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#else
    #define SL_MESSAGE(_message_, ...)
    #define SL_DEBUG(_message_, ...)
    #define SL_SUCCESS(_message_, ...)
#endif

#define SL_WARN(_message_, ...)  sl::Log(sl::LogLevel::WARNING, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#define SL_ERROR(_message_, ...) sl::Log(sl::LogLevel::ERROR, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
#define SL_FATAL(_message_, ...) sl::Log(sl::LogLevel::FATAL, std::format(_message_ __VA_OPT__(,) __VA_ARGS__))
