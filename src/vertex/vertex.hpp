#ifndef _VERTEX_H
#define _VERTEX_H

#include "../point/point.hpp"

template <typename T>
class Edge;

template <typename T>
class Vertex {
public:
    Point<T> p;
    Edge<T>* incident;
    int id;

    Vertex(Point<T> x) {
        p = x;
        incident = nullptr;
        id = -1;
    }
};

#endif
