#ifndef _POLYGON_H
#define _POLYGON_H

#include <list>

#include "../utils/orientation.hpp"

template <typename T>
class Polygon {
    // vertices implicitly stored in Clockwise order
    std::list<Point<T>> vertices;

public:
    typedef typename std::list<Point<T>>::iterator vptr;

    size_t size() {
        return vertices.size();
    }

    void addVertex(Point<T> p) {
        vertices.push_back(p);
    }

    void removeVertex(vptr v) {
        vertices.erase(v);
    }

    vptr begin() {
        return vertices.begin();
    }

    vptr end() {
        return vertices.end();
    }

    vptr nextVertex(vptr v) {
        if (v == prev(vertices.end())) {
            return vertices.begin();
        }
        return next(v);
    }

    vptr previousVertex(vptr v) {
        if (v == vertices.begin()) {
            return prev(vertices.end());
        }
        return prev(v);
    }

    bool notch(vptr v) {
        return getOrientation(*previousVertex(v), *v, *nextVertex(v)) == LEFT_TURN;
    }
};

#endif
