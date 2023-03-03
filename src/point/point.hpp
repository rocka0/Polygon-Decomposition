#ifndef _POINT_H
#define _POINT_H

template <typename T>
class Point {
public:
    T x;
    T y;

    Point() {}

    Point(T x, T y) : x(x), y(y) {}
};

#endif
