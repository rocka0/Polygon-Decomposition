#include <iostream>
#include <vector>

#include "../Face/Face.h"
#include "../HalfEdge/HalfEdge.h"
#include "../Vertex/Vertex.h"

#ifndef MESH_H
#define MESH_H

class Mesh {
public:
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    vector<Face*> faces;
};

#endif
