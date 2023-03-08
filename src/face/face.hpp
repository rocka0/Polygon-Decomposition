#ifndef _FACE_H
#define _FACE_H

#include <vector>

#include "../halfedge/halfedge.hpp"

template <typename T>
class Face {
public:
    Edge<T>* incident;
    int id;

    Face(Edge<T>* e) {
        e->right = this;
        incident = e;
        setFace();
        id = -1;
    }

    void setFace() {
        Edge<T>* edge = incident->next;

        while (edge != incident) {
            edge->right = this;
            edge = edge->next;
        }
    }

    std::vector<Vertex<T>*> listVertices() {
        std::vector<Vertex<T>*> v;
        Edge<T>* edge = incident;
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
