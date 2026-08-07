// include\sl\Assert.hpp

#pragma once

#if defined(_DEBUG)
    #include <format>
    #include <source_location>
    
    #include "sl\Define.hpp"
    #include "sl\Log.hpp"

    #if defined(SL_COMPILER_CLANG)
        #define SL_DEBUG_BREAK()
    #elif defined(SL_COMPILER_GCC)
        #define SL_DEBUG_BREAK()
    #elif defined(SL_COMPILER_MSVC)
        #include <intrin.h>
        #define SL_DEBUG_BREAK() __debugbreak()
    #endif
    
    #define SL_ASSERT(_condition_, ...)                                                                \
        if (!(_condition_)) SL_UNLIKELY {                                                              \
            const auto __sl_assert_location__ = std::source_location::current();                       \
            SL_FATAL(                                                                                  \
                "Assertion failed!\n  in {}\n  in {}\n  on line {}, column {}" __VA_OPT__("\n\n  {}"), \
                __sl_assert_location__.file_name(),                                                    \
                __sl_assert_location__.function_name(),                                                \
                __sl_assert_location__.line(),                                                         \
                __sl_assert_location__.column()                                                        \
                __VA_OPT__(, std::format(__VA_ARGS__))                                                 \
            );                                                                                         \
            SL_DEBUG_BREAK();                                                                          \
        } ((void)0)
#else
    #define SL_ASSERT(_condition_, ...)
#endif