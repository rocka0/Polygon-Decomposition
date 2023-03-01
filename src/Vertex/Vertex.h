#include <iostream>

#include "../Point/Point.h"

#ifndef VERTEX_H
#define VERTEX_H

class Edge;

class Vertex {
public:
    Point p;
    Edge* incident;

    Vertex(Point p) {
        this->p = p;
        incident = NULL;
    }
};

#endif
