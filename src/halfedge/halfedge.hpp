#ifndef _HALFEDGE_H
#define _HALFEDGE_H

#include "../vertex/vertex.hpp"

template <typename T>
class Face;

template <typename T>
class Edge {
    // These are directed edges

public:
    Edge<T>* twin;
    Vertex<T>* origin;
    Face<T>* right;    // not left beacuse CW orientation
    Edge<T>* next;     // in CW order
    Edge<T>* prev;     // in CW order

    Edge() {
        twin = nullptr;
        origin = nullptr;
        right = nullptr;
        next = nullptr;
        prev = nullptr;
    }
};

#endif
