#pragma once

namespace efreet {

struct ApplicationConfig {

};

bool init(const ApplicationConfig& config);
void exec();
void cleanup();

} // namespace efreet