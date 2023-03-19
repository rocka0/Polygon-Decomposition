/**
 * @file orientation.hpp
 * @brief Provides functions to determine the orientation of three 2D points.
 */

#ifndef _UTILS_ORIENTATION_H
#define _UTILS_ORIENTATION_H

#include "../point/point.hpp"

/**
 * @brief Enumeration to represent the orientation of three points.
 */
enum ORIENTATION {
    RIGHT_TURN = -1,    ///< The points make a right turn.
    COLLINEAR = 0,      ///< The points are collinear.
    LEFT_TURN = +1      ///< The points make a left turn.
};

/**
 * @brief Determines the orientation of three 2D points.
 * @tparam T The datatype of the point coordinates.
 * @param a The first point.
 * @param b The second point.
 * @param c The third point.
 * @return The orientation of the points, represented by the ORIENTATION enumeration.
 */
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
