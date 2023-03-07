#include <iostream>

#ifndef POINT_H
#define POINT_H

class Point {
public:
    int x;
    int y;

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Point() {
        x = 0;
        y = 0;
    }

    bool operator<(const Point &p) const {
        return x < p.x or (x == p.x and y < p.y);
    }
};

#endif
