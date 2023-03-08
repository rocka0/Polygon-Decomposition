#ifndef _MESH_H
#define _MESH_H

#include <cassert>
#include <map>

#include "../face/face.hpp"

template <typename T>
class Mesh {
public:
    std::vector<Vertex<T>*> vertices;
    std::vector<Edge<T>*> edges;
    std::vector<Face<T>*> faces;
    std::map<Point<T>, int> lookup;

    Edge<T>* addEdgeToFace(Edge<T>*, Vertex<T>*);
    Face<T>* createFace(std::vector<Point<T>>);
    Face<T>* splitFace(Face<T>*, Vertex<T>*, Vertex<T>*);
    Vertex<T>* createVertex(Point<T>);
    Edge<T>* createEdge(Vertex<T>*, Vertex<T>*);
    void decomposePolygon(std::vector<std::pair<Point<T>, Point<T>>>);
    std::vector<int> incidentFaces(Vertex<T>*);
};

template <typename T>
Vertex<T>* Mesh<T>::createVertex(Point<T> p) {
    Vertex<T>* v = new Vertex(p);
    v->id = vertices.size();
    lookup[p] = v->id;
    vertices.push_back(v);
    return v;
}

template <typename T>
Edge<T>* Mesh<T>::createEdge(Vertex<T>* v1, Vertex<T>* v2) {
    Edge<T>* e1 = new Edge<T>();
    Edge<T>* e2 = new Edge<T>();

    e1->origin = v1;
    e2->origin = v2;

    if ((v1->incident) == NULL) v1->incident = e1;

    if ((v2->incident) == NULL) v2->incident = e2;

    e1->twin = e2;
    e2->twin = e1;

    edges.push_back(e1);
    edges.push_back(e2);
    return e1;
}

template <typename T>
Edge<T>* Mesh<T>::addEdgeToFace(Edge<T>* e, Vertex<T>* v) {
    Edge<T>* edge = createEdge(e->twin->origin, v);
    edge->prev = e;
    e->next = edge;
    edge->twin->next = e->twin;
    e->twin->prev = edge->twin;
    return edge;
}

template <typename T>
Face<T>* Mesh<T>::createFace(std::vector<Point<T>> p) {
    Vertex<T>* v1 = createVertex(p[0]);
    Vertex<T>* v2 = createVertex(p[1]);
    Edge<T>* start = createEdge(v1, v2);
    Edge<T>* e = start;

    int n = p.size();

    for (int i = 2; i < n; i++) {
        Vertex<T>* v = createVertex(p[i]);
        e = addEdgeToFace(e, v);
    }

    Edge<T>* close = addEdgeToFace(e, v1);
    close->next = start;
    start->prev = close;
    start->twin->next = close->twin;
    start->twin->prev = close->twin;

    Face<T>* f = new Face(start);
    f->id = faces.size();
    faces.push_back(f);
    return f;
}

template <typename T>
std::vector<int> Mesh<T>::incidentFaces(Vertex<T>* v) {
    std::vector<int> inc(faces.size());
    Edge<T>* e = v->incident;

    assert(e != NULL);

    Face<T>* f = e->right;

    if (f != NULL) {
        int id = f->id;
        // cout<<id<<" is id\n";
        assert(id >= 0 && id < faces.size());
        inc[id] = 1;
    }

    e = e->twin->next;
    int x = 0;

    while (e != (v->incident)) {
        x++;
        assert(x < 100);
        f = e->right;

        if (f) {
            int id = f->id;
            // cout<<id<<" is id\n";
            assert(id >= 0 && id < faces.size());
            inc[id] = 1;
        }

        e = e->twin->next;
    }

    return inc;
}

template <typename T>
Face<T>* Mesh<T>::splitFace(Face<T>* f, Vertex<T>* v1, Vertex<T>* v2) {
    Edge<T>* e = f->incident;
    Edge<T>*e1, *e2;

    while (true) {
        if (e->origin == v1) e1 = e->prev;

        if (e->origin == v2) e2 = e;

        e = e->next;

        if (e == f->incident) break;
    }

    Edge<T>* edge = createEdge(v1, v2);

    edge->next = e2;
    e2->prev->next = edge->twin;
    edge->twin->prev = e2->prev;
    e2->prev = edge;
    edge->twin->next = e1->next;
    e1->next->prev = edge->twin;
    e1->next = edge;
    edge->prev = e1;

    edge->right = f;
    f->incident = edge;

    Face<T>* face = new Face(edge->twin);
    face->id = faces.size();
    faces.push_back(face);
    return face;
}

template <typename T>
void Mesh<T>::decomposePolygon(std::vector<std::pair<Point<T>, Point<T>>> v) {
    for (auto p : v) {
        Vertex<T>* v1 = vertices[lookup[p.first]];
        Vertex<T>* v2 = vertices[lookup[p.second]];
        Face<T>* face;

        std::vector<int> f1 = incidentFaces(v1);
        std::vector<int> f2 = incidentFaces(v2);

        int c = 0;

        for (int i = 0; i < f1.size(); i++) {
            if (f1[i] * f2[i]) {
                c++;
                face = faces[i];
            }
        }

        assert(c == 1);
        splitFace(face, v1, v2);
    }
}

#endif
