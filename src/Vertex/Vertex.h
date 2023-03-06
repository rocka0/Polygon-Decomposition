#include <iostream>

#include "../Point/Point.h"

#ifndef VERTEX_H
#define VERTEX_H

class Edge;

class Vertex {
public:
    Point p;
    Edge* incident;

    Vertex(Point x) {
        p = x;
        incident = NULL;
    }
};

#endif
