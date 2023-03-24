/**
 * @file halfedge.hpp
 * @brief Definition of the Edge class template and its associated function templates.  
*/

#ifndef _HALFEDGE_H
#define _HALFEDGE_H

#include "../vertex/vertex.hpp"

template <typename T>
class Face;

/**
 * @brief Edge class template
 * 
 * This class represents a directed half-edge between two vertices. 
 * 
 * @tparam T The type of the coordinates of the points. 
*/
template <typename T>
class Edge {

public:
    
    /**
     * The twin half-edge between the same pair of vertices. 
    */
    Edge<T>* twin;
    
    /**
     * The starting vertex of the edge.
    */
    Vertex<T>* origin;
    
    /**
     * The face to the right of the edge.
    */
    Face<T>* right;    
    
    /**
     * The next edge in clockwise order in the same face. 
    */
    Edge<T>* next;     
    
    /**
     * The previous edge in clockwise order in the same face.
    */
    Edge<T>* prev;   

    /**
     * @brief The non-parameterized constructor for Edge class.
    */
    Edge() {
        twin = nullptr;
        origin = nullptr;
        right = nullptr;
        next = nullptr;
        prev = nullptr;
    }
};

#endif
