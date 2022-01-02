#include "logger.h"
#include <platform/console.h>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

namespace efreet::logger {

void log(Level level, const char* message, ...) {
    static const char* logLevelStrings[6] = { "F", "E", "W", "I", "D", "T" };

    const auto isError = level < Level::WARN;

    // TODO: rework this mess
    const i32 messageLength = 32000;

    char outBuffer[messageLength];
    ::memset(outBuffer, 0, sizeof(outBuffer)); // TODO: use custom?

    // __builtin_va_list argPtr; // TODO: CLANG at some point please check it compiles with clang and commented line should b helpful for clang
    ::va_list argPtr;
    va_start(argPtr, message);
    ::vsnprintf(outBuffer, 32000, message, argPtr); // TODO: use custom ?
    va_end(argPtr);

    char outBuffer2[messageLength];
    ::sprintf(outBuffer2, "%s: %s\n", logLevelStrings[static_cast<u8>(level)], outBuffer); // TODO: use custom?

    if (isError) {
        platform::console::logError(outBuffer2, static_cast<u8>(level));
    } else {
        platform::console::log(outBuffer2, static_cast<u8>(level));
    }
}

void logAssertionFailure(const char* expression, const char* file, i32 line) {
    E_FATAL("Assertion failure: (%s), in file: %s, line: %d", expression, file, line);
}

void logAssertionExtFailure(const char* expression, const char* message, const char* file, i32 line) {
    E_FATAL("Assertion failure: (%s), message: %s, in file: %s, line: %d", expression, message, file, line);
}

} // namespace efreet::logger
