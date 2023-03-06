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

    vector<Vertex*> listVertices() {
        vector<Vertex*> v;
        Edge* edge = incident;
        v.push_back(edge->origin);
        edge = edge->next;

        while (edge != (incident)) {
            v.push_back(edge->origin);
            edge = edge->next;
        }

        return v;
    }
};

#endif
