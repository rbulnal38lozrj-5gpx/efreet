#pragma once

#include "basic_types.h"
#include <logger/logger.h>

#define EFREET_ASSERTIONS_ENABLED

#if defined(__clang__) || defined(__gcc__)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

#ifdef EFREET_ASSERTIONS_ENABLED
    #if _MSC_VER
        #include <intrin.h>
        #define debugBreak() __debugbreak()
    #else
        #define debugBreak() __builtin_trap()
    #endif

    #define E_ASSERT(expr) \
        { \
            if (expr) {} else { \
                efreet::logger::logAssertionFailure(#expr, __FILE__, __LINE__); \
                debugBreak(); \
            } \
        }

    #define E_ASSERT_EXT(expr, message) \
        { \
            if (expr) {} else { \
                efreet::logger::logAssertionExtFailure(#expr, message, __FILE__, __LINE__); \
                debugBreak(); \
            } \
        }

    #ifdef _DEBUG
        #define E_ASSERT_DEBUG(expr) \
        { \
            if (expr) {} else { \
                efreet::logger::logAssertionFailure(#expr, __FILE__, __LINE__); \
                debugBreak(); \
            } \
        }

        #define E_ASSERT_DEBUG_EXT(expr, message)  \
        { \
            if (expr) {} else { \
                efreet::logger::logAssertionExtFailure(#expr, message, __FILE__, __LINE__); \
                debugBreak(); \
            } \
        }

    #else
        #define E_ASSERT_DEBUG(expr)
        #define E_ASSERT_DEBUG_EXT(expr, message)
    #endif
#else
    #define E_ASSERT_EXT(expr, message)
    #define E_ASSERT(expr))
    #define E_ASSERT_DEBUG(expr)
    #define E_ASSERT_DEBUG_EXT(expr, message)
#endif
