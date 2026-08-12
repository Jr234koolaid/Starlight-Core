// include\sl\Define.hpp

#pragma once

#if defined(_WIN64) || defined(_WIN32)
    #define SL_OS_WINDOWS
#elif defined(__linux__)
    #define SL_OS_LINUX
#elif defined(__APPLE__)
    #define SL_OS_MAC
#endif

#if defined(_MSC_VER)
    #define SL_COMPILER_MSVC
#elif defined(__clang__)
    #define SL_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
    #define SL_COMPILER_GCC
#endif

#if defined(SL_COMPILER_MSVC)
    #define SL_NODISCARD [[nodiscard]]
#elif defined(SL_COMPILER_CLANG)
    #define SL_NODISCARD [[nodiscard]]
#else
    #define SL_NODISCARD
#endif

#if defined(SL_COMPILER_MSVC)
    #define SL_NO_RETURN [[noreturn]]
    #define SL_UNUSED    [[maybe_unused]]
#elif defined(SL_COMPILER_CLANG)
    #define SL_NO_RETURN [[noreturn]]
    #define SL_UNUSED    [[maybe_unused]]
#else
    #define SL_NO_RETURN
    #define SL_UNUSED
#endif

#if defined(SL_COMPILER_MSVC)
    //#define SL_ASSUME(_expr_) [[assume(_expr)]]
    #define SL_LIKELY	      [[likely]]
    #define SL_UNLIKELY       [[unlikely]]
    #define SL_FALLTHROUGH    [[fallthrough]]
#elif defined(SL_COMPILER_CLANG)
    //#define SL_ASSUME(_expr_) [[assume(_expr)]]
    #define SL_LIKELY	      [[likely]]
    #define SL_UNLIKELY       [[unlikely]]
    #define SL_FALLTHROUGH    [[fallthrough]]
#else
    //#define SL_ASSUME(_expr_)
    #define SL_LIKELY
    #define SL_UNLIKELY
    #define SL_FALLTHROUGH
#endif
