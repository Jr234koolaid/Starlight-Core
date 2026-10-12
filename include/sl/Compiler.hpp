// include/sl/Compiler.hpp

#pragma once

#if defined(_MSC_VER)
    #define SL_COMPILER_MSVC
#elif defined(__clang__)
    #define SL_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
    #define SL_COMPILER_GCC
#else
    #error Starlight does not support this compiler.
#endif
