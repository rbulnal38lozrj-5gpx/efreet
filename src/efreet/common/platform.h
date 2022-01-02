#pragma once

// thanks to kohi grabbing his platform detection code
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define EFREET_PLATFORM_WINDOWS 1
    #ifndef _WIN64
        #error "We would like 64 bit please."
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    #define EFREET_PLATFORM_LINUX 1
    #if defined(__ANDROID__)
        #define EFREET_PLATFORM_ANDROID 1
    #endif
#elif defined(__unix__)
    #define EFREET_PLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
    #define EFREET_PLATFORM_POSIX 1
#elif__APPLE__
    #define EFREET_PLATFORM_APPLE 1
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
        #define EFREET_PLATFORM_IOS 1
        #define EFREET_PLATFORM_IOS_SIMULATOR 1
    #elif TARGET_OS_IPHONE
        #define EFREET_PLATFORM_IOS 1
    #elif TARGET_OS_MAC
    #else
        #error "Unknown Apple platform"
    #endif
#else
    #error "Unknown platform"
#endif