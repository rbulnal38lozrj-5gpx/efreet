#pragma once

#include <common/common.h>

namespace efreet::platform::console {

void log(const char* message, u8 level);
void logError(const char* message, u8 level);

} // namespace efreet::platform::console