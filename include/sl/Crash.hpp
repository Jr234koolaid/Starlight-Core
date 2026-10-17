// include/sl/Crash.hpp

#pragma once

#include <utility>

#include "sl/Attributes.hpp"
#include "sl/core/Log.hpp"

#define SL_CRASH(...)                 \
    {                                 \
        SL_LOG_FATAL("" __VA_ARGS__); \
        std::unreachable();           \
    } ((void)0)
#define SL_CRASH_IF(_condition_, ...) \
    if (!(_condition_)) SL_UNLIKELY { \
        SL_LOG_FATAL("" __VA_ARGS__); \
        std::unreachable();           \
    } ((void)0)
