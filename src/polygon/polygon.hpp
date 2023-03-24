/**
 * @file polygon.hpp
 * @brief Defines a 2D polygon class with methods for manipulating its vertices.
 */

#ifndef _POLYGON_H
#define _POLYGON_H

#include <list>

#include "../utils/orientation.hpp"

/**
 * @brief A 2D polygon class.
 * @tparam T The datatype of the polygon's point coordinates.
 */
template <typename T>
class Polygon {
    std::list<Point<T>> vertices;    ///< The list of vertices in the polygon, implicitly stored in clockwise order.

public:
    typedef typename std::list<Point<T>>::iterator vptr;    ///< An iterator for iterating over the polygon's vertices.

    /**
     * @brief Returns the number of vertices in the polygon.
     * @return The number of vertices in the polygon.
     */
    size_t size() {
        return vertices.size();
    }

    /**
     * @brief Adds a vertex to the polygon.
     * @param p The point to add as a vertex.
     */
    void addVertex(Point<T> p) {
        vertices.push_back(p);
    }

    /**
     * @brief Removes a vertex from the polygon.
     * @param v An iterator pointing to the vertex to remove.
     */
    void removeVertex(vptr v) {
        vertices.erase(v);
    }

    /**
     * @brief Finds an iterator pointing to the first occurrence of a point in the polygon's vertex list.
     * @param p The point to search for.
     * @return An iterator pointing to the vertex containing the point, or end() if the point is not found.
     */
    vptr find(Point<T> &p) {
        vptr it = vertices.begin();
        while (it != vertices.end()) {
            if (*it == p) return it;
            ++it;
        }
        return it;
    }

    /**
     * @brief Returns an iterator pointing to the first vertex in the polygon.
     * @return An iterator pointing to the first vertex in the polygon.
     */
    vptr begin() {
        return vertices.begin();
    }

    /**
     * @brief Returns an iterator pointing to the position one past the last vertex in the polygon.
     * @return An iterator pointing to the position one past the last vertex in the polygon.
     */
    vptr end() {
        return vertices.end();
    }

    /**
     * @brief Returns an iterator pointing to the next vertex in the polygon.
     * @param v An iterator pointing to the current vertex.
     * @return An iterator pointing to the next vertex in the polygon.
     */
    vptr nextVertex(vptr v) {
        if (v == prev(vertices.end())) {
            return vertices.begin();
        }
        return next(v);
    }

    /**
     * @brief Returns an iterator pointing to the previous vertex in the polygon.
     * @param v An iterator pointing to the current vertex.
     * @return An iterator pointing to the previous vertex in the polygon.
     */
    vptr previousVertex(vptr v) {
        if (v == vertices.begin()) {
            return prev(vertices.end());
        }
        return prev(v);
    }

    /**
     * @brief Determines whether a vertex forms a notch in the polygon.
     * @param v An iterator pointing to the vertex to check.
     * @return True if the vertex forms a notch, false otherwise.
     */
    bool notch(vptr v) {
        return getOrientation(*previousVertex(v), *v, *nextVertex(v)) == LEFT_TURN;
    }
};

#endif
