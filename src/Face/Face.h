#include <iostream>
#include <vector>

#include "../HalfEdge/HalfEdge.h"
#include "../Vertex/Vertex.h"

#ifndef FACE_H
#define FACE_H

class Face {
public:
    Edge* incident;

    Face* create_face(vector<Point> v);
    void split_face(Face* f, Vertex* end);
    vector<Vertex*> get_vertices(Face* f);
};

#endif
