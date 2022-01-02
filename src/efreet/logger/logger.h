#pragma once

#include <common/common.h>

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

namespace efreet::logger {

enum class Level: u8 {
    FATAL,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE
};

void log(Level level, const char* message, ...);
void logAssertionFailure(const char* expression, const char* file, i32 line);
void logAssertionExtFailure(const char* expression, const char* message, const char* file, i32 line);

} // namespace efreet::logger

#define E_FATAL(message, ...) efreet::logger::log(efreet::logger::Level::FATAL, message, ##__VA_ARGS__)

#define E_ERROR(message, ...) efreet::logger::log(efreet::logger::Level::ERROR, message, ##__VA_ARGS__)

#if LOG_WARN_ENABLED == 1
    #define E_WARN(message, ...) efreet::logger::log(efreet::logger::Level::WARN, message, ##__VA_ARGS__)
#else
    #define E_WARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
    #define E_INFO(message, ...) efreet::logger::log(efreet::logger::Level::INFO, message, ##__VA_ARGS__)
#else
    #define E_INFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
    #define E_DEBUG(message, ...) efreet::logger::log(efreet::logger::Level::DEBUG, message, ##__VA_ARGS__)
#else
    #define E_DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
    #define E_TRACE(message, ...) efreet::logger::log(efreet::logger::Level::TRACE, message, ##__VA_ARGS__)
#else
    #define E_TRACE(message, ...)
#endif