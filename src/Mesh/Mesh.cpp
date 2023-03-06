#include "Mesh.h"

// Edge* Mesh::addEdge(Vertex* v1, Vertex* v2)
//{
//    Edge* edge = new Edge();
//
//    if (!(v1->incident))
//        v1->incident = edge;
//
//    edge->origin = v1;
//    edges.push_back(edge);
//    return edge;
//}

// Edge* Mesh::addEdge(Edge* e1, Edge* e2)
//{
//    Edge* edge = new Edge();
//    edge->origin = e1->twin->origin;
//    edge->next = e2;
//    edge->prev = e1;
//    edge->right = e1->right;
//    edges.push_back(edge);
//    return edge;
//}

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
