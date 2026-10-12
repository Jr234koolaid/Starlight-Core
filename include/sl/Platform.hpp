// include/sl/Platform.hpp

#pragma once

#if defined(_WIN32)
    #if defined(_WIN64)
        #define SL_PLATFORM_WINDOWS
        
        #define WIN32_LEAN_AND_MEAN
        #ifndef NOMINMAX
            #define NOMINMAX
        #endif
    #else
        #error Starlight does not support the x86 windows platform.
    #endif
#elif defined(__linux__)
    #define SL_PLATFORM_LINUX
#elif defined(__APPLE__) || defined(__MACH__)
    #define SL_PLATFORM_MAC
#elif defined(__ANDROID__)
	#define SL_PLATFORM_ANDROID
#else
    #error Starlight does not support this platform.
#endif
