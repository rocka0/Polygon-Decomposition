/**
 * @file mesh.hpp
 * @brief Definition of the Mesh class template and its associated function templates  
 */

#ifndef _MESH_H
#define _MESH_H

#include <cassert>
#include <map>

#include "../face/face.hpp"

/**
 * @brief Mesh class template
 *
 * This class represents a Mesh, which is a subdivision of the 2D-plane, implemented using the DCEL data
 * structure. A Mesh object is composed of a list of vertices, half-edges and faces present in the mesh.
 * 
 * @tparam T The type of the coordinates of the points.
 */
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


/**
 * @brief Creates a new vertex.
 * 
 * This function creates a new vertex object corresponding to the given point object 
 * and adds it to the mesh.
 * 
 * @param p The corresponding point object  
 * 
 * @return A pointer to the vertex object newly created.
*/
template <typename T>
Vertex<T>* Mesh<T>::createVertex(Point<T> p) {
    Vertex<T>* v = new Vertex(p);
    v->id = vertices.size();
    lookup[p] = v->id;
    vertices.push_back(v);
    return v;
}


/**
 * @brief Creates a pair of half-edges.
 *
 * This function creates the half-edge and the corresponding twin edge between the given pair of vertices, 
 * and adds them to the mesh.
 *  
 * @param v1 A pointer to the start vertex of the new half-edge
 * @param v2 A pointer to the end vertex of the new half-edge.
 * 
 * @return A pointer to the half-edge from v1 to v2.
*/
template <typename T>
Edge<T>* Mesh<T>::createEdge(Vertex<T>* v1, Vertex<T>* v2) {
    Edge<T>* e1 = new Edge<T>();
    Edge<T>* e2 = new Edge<T>();

    e1->origin = v1;
    e2->origin = v2;

    if ((v1->incident) == nullptr) v1->incident = e1;

    if ((v2->incident) == nullptr) v2->incident = e2;

    e1->twin = e2;
    e2->twin = e1;

    edges.push_back(e1);
    edges.push_back(e2);
    return e1;
}


/**
 * @brief Adds a pair of half-edges to the currently forming face.
 * 
 * Adds the next pair of half-edges in clockwise order to the outer boundary of the currently forming
 * face, and updates the mesh.
 * 
 * @param e A pointer to the previous half-edge in the face.
 * @param v A pointer to the start vertex of the new half-edge. 
 *
 * @return A pointer to the newly formed half-edge. 
*/
template <typename T>
Edge<T>* Mesh<T>::addEdgeToFace(Edge<T>* e, Vertex<T>* v) {
    Edge<T>* edge = createEdge(e->twin->origin, v);
    edge->prev = e;
    e->next = edge;
    edge->twin->next = e->twin;
    e->twin->prev = edge->twin;
    return edge;
}


/**
 * @brief Creates a new face in the mesh.
 * 
 * This function creates a new face in the mesh from the given vector of points.
 * 
 * @param p A vector containing the clockwise listing of the points making the face.
 * 
 * @return A pointer to the newly created face.
*/
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


/**
 * @brief Lists all faces containing the given vertex. 
 *
 * @param v A pointer to the vertex object.
 * 
 * @return A vector of id's of all the faces containing the given vertex.  
*/
template <typename T>
std::vector<int> Mesh<T>::incidentFaces(Vertex<T>* v) {
    std::vector<int> inc(faces.size());
    Edge<T>* e = v->incident;

    assert(e != NULL);

    Face<T>* f = e->right;

    if (f != NULL) {
        int id = f->id;
        assert(id >= 0 && id < faces.size());
        inc[id] = 1;
    }

    e = e->twin->next;

    while (e != (v->incident)) {
        f = e->right;

        if (f) {
            int id = f->id;
            assert(id >= 0 && id < faces.size());
            inc[id] = 1;
        }

        e = e->twin->next;
    }

    return inc;
}


/**
 * @brief Splits a face.
 * 
 * This function splits the given face along the diagonal between the 2 given vertices. One of the faces
 * retains its id while the other is treated as a new face.
 * 
 * @param f A pointer to the face to be splitted.
 * @param v1 A pointer to the first vertex of the diagonal.
 * @param v2 A pointer to the second vertex of the diagonal.
 * 
 * @return A pointer to the face newly created.
*/
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


/**
 * @brief Decomposes the initial polygon.
 * 
 * This function decomposes the initial polygon along the given diagonals and updates the mesh with 
 * the decomposed polygons.
 * 
 * @param v A vector of pair of point objects, with each pair representing a diagonal.
*/
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
