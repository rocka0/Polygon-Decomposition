/**
 * @file vertex.hpp
 * @brief Definition of the Vertex class template and its associated function templates  
*/

#ifndef _VERTEX_H
#define _VERTEX_H

#include "../point/point.hpp"

template <typename T>
class Edge;

/**
 * @brief Vertex class template
 * 
 * This class represents a Vertex in the Mesh.
 * 
 * @tparam T The type of the coordinates of the points. 
*/
template <typename T>
class Vertex {
public:

    /**
     * The point object associated with the vertex. 
    */
    Point<T> p;

    /**
     * One of the half-edges with the vertex as origin.
    */
    Edge<T>* incident;
    
    /**
     * An integer id to uniquely identify each vertex. It is the index of the vertex object in the 
     * vertex list of the Mesh object.
    */
    int id;

    /**
     * @brief Paramterized constructor of Vertex class
     * @param x The point object associated with the vertex.  
    */
    Vertex(Point<T> x) {
        p = x;
        incident = nullptr;
        id = -1;
    }
};

#endif
