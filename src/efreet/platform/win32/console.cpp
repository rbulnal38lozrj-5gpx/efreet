#include "../console.h"

#ifdef EFREET_PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace efreet::platform::console {

void log(const char* message, u8 level) {
    // TODO: better color handling
    E_ASSERT(level < 6);
    static const u8 levelColors[6] = { 71, 116, 6, 2, 113, 8 };
    auto consoleHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
    E_ASSERT(consoleHandle != nullptr);
    const auto setConsoleTextAttributeResult = ::SetConsoleTextAttribute(consoleHandle, levelColors[level]);
    E_ASSERT(setConsoleTextAttributeResult != 0);
    ::OutputDebugStringA(message);
    const auto messageLength = static_cast<::DWORD>(::strlen(message));
    ::LPDWORD bytesWritten = nullptr;
    const auto writeResult = ::WriteConsoleA(consoleHandle, message, messageLength, bytesWritten, nullptr);
    E_ASSERT(writeResult != 0);
    // FIXME: prevent color leaking after any assertion
}

void logError(const char* message, u8 level) {
    // TODO: better color handling
    E_ASSERT(level < 6);
    static const u8 levelColors[6] = { 71, 116, 6, 2, 113, 8 };
    auto consoleHandle = ::GetStdHandle(STD_ERROR_HANDLE);
    E_ASSERT(consoleHandle != nullptr);
    const auto setConsoleTextAttributeResult = ::SetConsoleTextAttribute(consoleHandle, levelColors[level]);
    E_ASSERT(setConsoleTextAttributeResult != 0);
    ::OutputDebugStringA(message);
    const auto messageLength = static_cast<::DWORD>(::strlen(message));
    ::LPDWORD bytesWritten = nullptr;
    const auto writeResult = ::WriteConsoleA(consoleHandle, message, messageLength, bytesWritten, nullptr);
    E_ASSERT(writeResult != 0);
    // FIXME: prevent color leaking after any assertion
}

} // namespace efreet::platform::console

#endif