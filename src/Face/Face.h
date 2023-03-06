#include <iostream>
#include <vector>

#include "../HalfEdge/HalfEdge.h"
#include "../Vertex/Vertex.h"

using namespace std;

#ifndef FACE_H
#define FACE_H

class Face {
public:
    Edge* incident;
    vector<Vertex*> get_vertices(Face* f);

    Face(Edge* e) {
        e->right = this;
        incident = e;
        setFace();
    }

    void setFace() {
        Edge* edge = incident->next;

        while (edge != incident) {
            edge->right = this;
            edge = edge->next;
        }
    }
};

#endif
