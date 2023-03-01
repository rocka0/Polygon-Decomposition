#ifndef _UTILS_ORIENTATION_H
#define _UTILS_ORIENTATION_H

#include "../point/point.hpp"

enum ORIENTATION { RIGHT_TURN = -1, COLLINEAR = 0, LEFT_TURN = +1 };

template <typename T>
ORIENTATION getOrientation(Point<T> a, Point<T> b, Point<T> c) {
    T cross = ((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x));
    // returns sign of cross
    if (cross > 0) {
        return LEFT_TURN;
    } else if (cross < 0) {
        return RIGHT_TURN;
    } else {
        return COLLINEAR;
    }
}

#endif
