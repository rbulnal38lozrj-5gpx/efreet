#include "application.h"

int main() {
    if (efreet::init({})) {
        efreet::exec();
    }
    efreet::cleanup();
    return 0;
}