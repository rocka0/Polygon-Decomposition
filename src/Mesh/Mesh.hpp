#include <cassert>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

#include "../Face/Face.hpp"
#include "../HalfEdge/HalfEdge.hpp"
#include "../Vertex/Vertex.hpp"

#ifndef MESH_H
#define MESH_H

class Mesh {
public:
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    vector<Face*> faces;
    map<Point, int> lookup;

    Edge* addEdgeToFace(Edge*, Vertex*);
    Face* createFace(vector<Point>);
    Face* splitFace(Face*, Vertex*, Vertex*);
    Vertex* createVertex(Point);
    Edge* createEdge(Vertex*, Vertex*);
    void decomposePolygon(vector<pair<Point, Point>>);
    vector<int> incidentFaces(Vertex*);
};

Vertex* Mesh::createVertex(Point p) {
    Vertex* v = new Vertex(p);
    v->id = vertices.size();
    lookup[p] = v->id;
    vertices.push_back(v);
    return v;
}

Edge* Mesh::createEdge(Vertex* v1, Vertex* v2) {
    Edge* e1 = new Edge();
    Edge* e2 = new Edge();

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

Edge* Mesh::addEdgeToFace(Edge* e, Vertex* v) {
    Edge* edge = createEdge(e->twin->origin, v);
    edge->prev = e;
    e->next = edge;
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
    f->id = faces.size();
    faces.push_back(f);
    return f;
}

vector<int> Mesh::incidentFaces(Vertex* v) {
    vector<int> inc(faces.size());
    Edge* e = v->incident;

    if (e == NULL) cout << v->id << "\n";

    assert(e != NULL);

    Face* f = e->right;

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
    f->incident = edge;

    Face* face = new Face(edge->twin);
    face->id = faces.size();
    faces.push_back(face);
    return face;
}

void Mesh::decomposePolygon(vector<pair<Point, Point>> v) {
    for (auto p : v) {
        Vertex* v1 = vertices[lookup[p.first]];
        Vertex* v2 = vertices[lookup[p.second]];
        Face* face;

        vector<int> f1 = incidentFaces(v1);
        vector<int> f2 = incidentFaces(v2);

        int c = 0;

        for (int i = 0; i < f1.size(); i++) {
            if (f1[i] * f2[i]) {
                c++;
                face = faces[i];
            }
        }

        assert(c == 1);
        splitFace(face, v1, v2);
        cout << faces.size() << "\n";
    }
}

#endif
