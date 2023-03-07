#include <iostream>

#include "../Point/Point.hpp"

#ifndef VERTEX_H
#define VERTEX_H

class Edge;

class Vertex {
public:
    Point p;
    Edge* incident;
    int id;

    Vertex(Point x) {
        p = x;
        incident = NULL;
        id = -1;
    }
};

#endif
