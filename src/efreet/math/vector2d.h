#pragma once

namespace efreet::math {

template <class T>
union Vector2d {
    T v[2]{};
    union {
        struct {
            T x;
            T y;
        };
        T xy[2];
    };
    union {
        struct {
            T w;
            T h;
        };
        T wh[2];
    };
};

} // namespace efreet::math