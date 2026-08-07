// include\sl\Check.hpp

#pragma once

#include <exception>

#include "sl\Assert.hpp"
#include "sl\Define.hpp"
#include "sl\Log.hpp"

#if defined(_DEBUG)
    #define SL_CHECK(_expression_, _return_, ...)   SL_ASSERT(_expression_ __VA_OPT__(, ) __VA_ARGS__)
    #define SL_CHECK_VOID(_expression_, ...)        SL_ASSERT(_expression_ __VA_OPT__(, ) __VA_ARGS__)
    #define SL_CHECK_BREAK(_expression_, ...)       SL_ASSERT(_expression_ __VA_OPT__(, ) __VA_ARGS__)
    #define SL_CHECK_CONTINUE(_expression_, ...)    SL_ASSERT(_expression_ __VA_OPT__(, ) __VA_ARGS__)
    #define SL_CHECK_CONSTRUCTOR(_expression_, ...) SL_ASSERT(_expression_ __VA_OPT__(, ) __VA_ARGS__)
#else
    #define SL_CHECK(_expression_, _return_, ...)   \
        if (!(_expression_)) SL_UNLIKELY {          \
            SL_ERROR("" __VA_ARGS__);               \
            return _return_;                        \
        } ((void)0)
    #define SL_CHECK_VOID(_expression_, ...)        \
        if (!(_expression_)) SL_UNLIKELY {          \
            SL_ERROR("" __VA_ARGS__);               \
            return;                                 \
        } ((void)0)
    #define SL_CHECK_BREAK(_expression_, ...)       \
        if (!(_expression_)) SL_UNLIKELY {          \
            SL_ERROR("" __VA_ARGS__);               \
            break;                                  \
        } ((void)0)
    #define SL_CHECK_CONTINUE(_expression_, ...)    \
        if (!(_expression_)) SL_UNLIKELY {          \
            SL_ERROR("" __VA_ARGS__);               \
            continue;                               \
        } ((void)0)
    #define SL_CHECK_CONSTRUCTOR(_expression_, ...) \
        if (!(_expression_)) SL_UNLIKELY {          \
            SL_FATAL("" __VA_ARGS__);               \
            std::terminate();                       \
        } ((void)0)
#endif
