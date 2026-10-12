// include/sl/Crash.hpp

#pragma once

#include <format>
#include <utility>

#include "sl/core/Log.hpp"

#define SL_CRASH(...)                     \
    {                                     \
        __VA_OPT__(                       \
            SL_LOG_FATAL("" __VA_ARGS__); \
        )                                 \
        std::unreachable();               \
    } ((void)0)
