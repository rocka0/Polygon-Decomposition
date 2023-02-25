#include <utility>
#include <vector>

using namespace std;

#ifndef DCEL_H
#define DCEL_H

class Point {
    int x;
    int y;
};

class Edge;

class Vertex {
public:
    int id;
    Point p;
    Edge* incident;
};

class Face;

class Edge {
public:
    Edge* twin;
    Vertex* origin;
    Face* right;    // not left beacuse CW orientation
    Edge* next;     // in CW order
    Edge* prev;     // in CW order

    pair<Vertex, Vertex> get_endpoints(Edge* e);
};

class Face {
public:
    Edge* incident;

    Face* create_face(vector<Point> v);
    void split_face(Face* f, Vertex* end);
    vector<Vertex*> get_vertices(Face* f);
};

class Dcel {
public:
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    vector<Face*> faces;
};

#endif
