/**
 * @file point.hpp
 * @brief A 2D Point class with X and Y coordinates.
 */

#ifndef _POINT_H
#define _POINT_H

/**
 * @brief A 2D Point class.
 *
 * @tparam T The datatype of the X and Y coordinates.
 */
template <typename T>
class Point {
public:
    T x;    ///< X Coordinate of point
    T y;    ///< Y Coordinate of point

    /**
     * @brief Default constructor for Point.
     */
    Point() {}

    /**
     * @brief Parameterized constructor for Point.
     * @param x Value to set as X coordinate.
     * @param y Value to set as Y coordinate.
     */
    Point(T x, T y) : x(x), y(y) {}

    /**
     * @brief Equality operator for Point.
     * @param other Point object to compare with.
     * @return true if both points are equal, false otherwise.
     */
    bool operator==(const Point<T>& other) const {
        return x == other.x and y == other.y;
    }

    /**
     * @brief Inequality operator for Point.
     * @param other Point object to compare with.
     * @return true if both points are not equal, false otherwise.
     */
    bool operator!=(const Point<T>& other) const {
        return !operator==(other);
    }

    /**
     * @brief Less than operator for Point.
     * @param other Point object to compare with.
     * @return true if this point is less than the other point, false otherwise.
     */
    bool operator<(const Point<T>& other) const {
        return (x < other.x) or ((x == other.x) and (y < other.y));
    }
};

#endif
