#pragma once

#include <common/common.h>

namespace efreet::platform::window {

struct WindowConfig {
    const char* title;
    i32 x; // TODO: replace with rect
    i32 y;
    i32 width{ 320 };
    i32 height{ 240 };
};

void destroy();
bool create(const WindowConfig& config);
void show();
void hide();
void processEvents();
bool exists();

// TODO: show hide minimize maximize resize fullsren etc

} // namespace efreet::platform::window