#include <iostream>

#include "../Vertex/Vertex.h"

#ifndef HALFEDGE_H
#define HALFEDGE_H

class Face;

class Edge {
    // These are directed edges

public:
    Edge* twin;
    Vertex* origin;
    Face* right;    // not left beacuse CW orientation
    Edge* next;     // in CW order
    Edge* prev;     // in CW order
};

#endif
