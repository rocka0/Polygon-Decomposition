/**
 * @file face.hpp
 * @brief Definition of the Face class template and its associated function templates. 
*/
#ifndef _FACE_H
#define _FACE_H

#include <vector>

#include "../halfedge/halfedge.hpp"

/**
 * @brief Face class template
 * 
 * This class represents a face in the Mesh.
 * 
 * @tparam T The type of coordinates of the points.     
*/
template <typename T>
class Face {
public:
    /**
     * One of the edges on the boundary of the face.
    */
    Edge<T>* incident;

    /**
     * An integer id to uniquely identify each face. It is the index of the face object in the face
     * list of the Mesh. 
    */
    int id;

    /**
     * @brief The parameterized constructor for the Face class.
     * 
     * @param e The incident edge of the face.
    */
    Face(Edge<T>* e) {
        e->right = this;
        incident = e;
        setFace();
        id = -1;
    }

    /**
     * @brief Couples each edge to its corresponding face.
     * 
     * Iterates through each edge on the boundary of the face and sets the right face of each edge 
     * as the current face.
    */
    void setFace() {
        Edge<T>* edge = incident->next;

        while (edge != incident) {
            edge->right = this;
            edge = edge->next;
        }
    }

    /**
     * @brief Lists all vertices in the face.
     * 
     * @return A vector of Vertex pointers corresponding to the vertices in the face. 
    */
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
