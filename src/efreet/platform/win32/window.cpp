#include "../window.h"

#ifdef EFREET_PLATFORM_WINDOWS

#include <math/math.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>


// thanks to kohi
namespace efreet::platform::window {

namespace {

::HINSTANCE instance_{ nullptr };
::HWND windowHandle_{ nullptr };

static ::LRESULT CALLBACK windowEventProcessor(::HWND windowHandle, u32 event, ::WPARAM wParam, ::LPARAM lParam) {
    switch (event) {
        case WM_ERASEBKGND:
            // Notify the OS that erasing will be handled by the application to prevent flicker.
            return 1;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        case WM_CLOSE:
            destroy();
            return 0;
        case WM_SIZE: {
            // Get the updated size.
            //  RECT r;
            // GetClientRect(hwnd, &r);
            // u32 width = r.right - r.left;
            // u32 height = r.bottom - r.top;

            // TODO: do window resize.
        } break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            E_TRACE("Key Event %u, %u", event, static_cast<u16>(wParam));
            const auto pressed = (event == WM_KEYDOWN || event == WM_SYSKEYDOWN);
            const auto key = static_cast<u16>(wParam);
        } break;
        case WM_MOUSEMOVE: {
            E_TRACE("Mouse Move Event %ux%u", GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            const math::v2i pos{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        } break;
        case WM_MOUSEWHEEL: {
            E_TRACE("Mouse Wheel Event %u", GET_WHEEL_DELTA_WPARAM(wParam));
            i32 zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
            if (zDelta != 0) {
                zDelta = (zDelta < 0) ? -1 : 1;
            }
        } break;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP: {
            E_TRACE("Mouse Left Button Event %u", event);
            const auto pressed = (event == WM_LBUTTONDOWN || event == WM_RBUTTONDOWN || event == WM_MBUTTONDOWN);
        } break;
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP: {
            E_TRACE("Mouse Middle Button Event %u", event);
            const auto pressed = (event == WM_LBUTTONDOWN || event == WM_RBUTTONDOWN || event == WM_MBUTTONDOWN);
        } break;
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP: {
            E_TRACE("Mouse Right Button Event %u", event);
            const auto pressed = (event == WM_LBUTTONDOWN || event == WM_RBUTTONDOWN || event == WM_MBUTTONDOWN);
        } break;
    }
    return ::DefWindowProcA(windowHandle, event, wParam, lParam);
}

} // namespace

void destroy() {
    if (windowHandle_) {
        ::DestroyWindow(windowHandle_);
        windowHandle_ = nullptr;
    }
}

bool create(const WindowConfig& config) {
    E_ASSERT(::GetLastError() == 0);

    ::WNDCLASSA windowClass = {};
    windowClass.style = CS_DBLCLKS;
    windowClass.lpfnWndProc = windowEventProcessor;
    windowClass.hInstance = instance_;
    windowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.lpszClassName = "EfreetWindowClass";
    E_ASSERT(::GetLastError() == 0);

    if (!::RegisterClassA(&windowClass)) {
        const auto error = ::GetLastError();
        E_FATAL("Window registration failed. Last error: %d", error);
        ::MessageBoxA(nullptr, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    E_ASSERT(::GetLastError() == 0);

    const u32 clientX = config.x;
    const u32 clientY = config.y;
    const u32 clientWidth = config.width;
    const u32 clientHeight = config.height;

    u32 windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    const u32 windowStyleEx = WS_EX_APPWINDOW;

    windowStyle |= WS_MAXIMIZEBOX;
    windowStyle |= WS_MINIMIZEBOX;
    windowStyle |= WS_THICKFRAME;

    ::RECT borderRect = { 0, 0, 0, 0 };
    if (!::AdjustWindowRectEx(&borderRect, windowStyle, 0, windowStyleEx)) {
        const auto error = ::GetLastError();
        E_FATAL("Adjust window rect failed. Last error: %d", error);
        ::MessageBoxA(nullptr, "Adjust window rect failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    E_ASSERT(::GetLastError() == 0);

    const u32 windowX = clientX + borderRect.left;
    const u32 windowY = clientY + borderRect.top;
    const u32 windowWidth = clientWidth + borderRect.right - borderRect.left;
    const u32 windowHeight = clientHeight + borderRect.bottom - borderRect.top;

    windowHandle_ = ::CreateWindowExA(
        windowStyleEx,
        windowClass.lpszClassName,
        config.title,
        windowStyle,
        windowX, windowY, windowWidth, windowHeight,
        nullptr, nullptr, instance_, nullptr);
    E_ASSERT(::GetLastError() == 0);
    if (windowHandle_ == nullptr) {
        const auto error = ::GetLastError();
        E_FATAL("Window creation failed. Last error: %d", error);
        ::MessageBoxA(nullptr, "Window creation failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    bool shouldActivate = 1;
    const i32 showWindowCommandFlags = shouldActivate ? SW_SHOW : SW_SHOWNOACTIVATE;
    ::ShowWindow(windowHandle_, showWindowCommandFlags);
    E_ASSERT(::GetLastError() == 0);

    return true;
}

void show() {
    ::ShowWindow(windowHandle_, SW_SHOW);
}

void hide() {
    ::ShowWindow(windowHandle_, SW_HIDE);
}

void processEvents() {
    ::MSG message;
    while (::PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&message);
        ::DispatchMessageA(&message);
    }
}

bool exists() {
    return windowHandle_ != nullptr;
}

} // namespace efreet::platform::window

#endif