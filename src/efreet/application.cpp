#include "application.h"
#include <platform/window.h>

namespace efreet {

namespace {
    bool running_{ false };
} // namespace

bool init(const ApplicationConfig& config) {
    platform::window::create({ "Efreet", 100, 50, 500, 200 }); // TODO: use config for it

    running_ = true;

    return true;
}

void exec() {
    while (platform::window::exists()) {
        platform::window::processEvents();
    }
}

void cleanup() {
    platform::window::destroy();
}

} // namespace efreet