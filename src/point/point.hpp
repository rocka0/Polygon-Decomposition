#ifndef _POINT_H
#define _POINT_H

template <typename T>
class Point {
public:
    T x;
    T y;

    Point() {}

    Point(T x, T y) : x(x), y(y) {}

    bool operator==(const Point<T>& other) const {
        return x == other.x and y == other.y;
    }

    bool operator<(const Point<T>& other) const {
        return (x < other.x) or ((x == other.x) and (y < other.y));
    }
};

#endif
