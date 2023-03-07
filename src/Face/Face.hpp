#include <iostream>
#include <vector>

#include "../HalfEdge/HalfEdge.hpp"
#include "../Vertex/Vertex.hpp"

using namespace std;

#ifndef FACE_H
#define FACE_H

class Face {
public:
    Edge* incident;
    int id;

    Face(Edge* e) {
        e->right = this;
        incident = e;
        setFace();
        id = -1;
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
