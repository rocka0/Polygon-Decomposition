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

   // Edge* addEdge(Vertex*, Vertex*);
    //Edge* addEdge(Edge*, Edge*);
    Edge* addEdgeToFace(Edge*, Vertex*);
    Face* createFace(vector<Point>);
    Face* split_face(Face*, Vertex*);

    Vertex* createVertex(Point p) {
        Vertex* v = new Vertex(p);
        vertices.push_back(v);
        return v;
    }

    Edge* createEdge(Vertex* v1, Vertex* v2) {
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
};

#endif
