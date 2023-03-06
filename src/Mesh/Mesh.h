#include <iostream>
#include <vector>
using namespace std;

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

    Edge* addEdgeToFace(Edge*, Vertex*);
    Face* createFace(vector<Point>);
    Face* splitFace(Face*, Vertex*, Vertex*);
    Vertex* createVertex(Point);
    Edge* createEdge(Vertex*, Vertex*);
};

Vertex* Mesh::createVertex(Point p) {
    Vertex* v = new Vertex(p);
    vertices.push_back(v);
    return v;
}

Edge* Mesh::createEdge(Vertex* v1, Vertex* v2) {
    Edge* e1 = new Edge();
    Edge* e2 = new Edge();

    e1->origin = v1;
    e2->origin = v2;
    e1->twin = e2;
    e2->twin = e1;

    edges.push_back(e1);
    edges.push_back(e2);
    return e1;
}

Edge* Mesh::addEdgeToFace(Edge* e, Vertex* v) {
    Edge* edge = createEdge(e->twin->origin, v);
    edge->prev = e;
    e->next = edge;
    edge->origin->incident = edge;
    edge->twin->next = e->twin;
    e->twin->prev = edge->twin;
    return edge;
}

Face* Mesh::createFace(vector<Point> p) {
    Vertex* v1 = createVertex(p[0]);
    Vertex* v2 = createVertex(p[1]);
    Edge* start = createEdge(v1, v2);
    Edge* e = start;

    int n = p.size();

    for (int i = 2; i < n; i++) {
        Vertex* v = createVertex(p[i]);
        e = addEdgeToFace(e, v);
    }

    Edge* close = addEdgeToFace(e, v1);
    close->next = start;
    start->prev = close;
    start->twin->next = close->twin;
    start->twin->prev = close->twin;

    Face* f = new Face(start);
    faces.push_back(f);
    return f;
}

Face* Mesh::splitFace(Face* f, Vertex* v1, Vertex* v2) {
    Edge* e = f->incident;
    Edge *e1, *e2;

    while (true) {
        if (e->origin == v1) e1 = e->prev;

        if (e->origin == v2) e2 = e;

        e = e->next;

        if (e == f->incident) break;
    }

    Edge* edge = createEdge(v1, v2);

    edge->next = e2;
    e2->prev->next = edge->twin;
    edge->twin->prev = e2->prev;
    e2->prev = edge;
    edge->twin->next = e1->next;
    e1->next->prev = edge->twin;
    e1->next = edge;
    edge->prev = e1;

    edge->right = f;

    Face* face = new Face(edge->twin);
    faces.push_back(face);
    return face;
}

#endif
