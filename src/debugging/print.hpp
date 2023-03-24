/**
 * @file debug.h
 * @brief Debugging utility functions.
 */

#ifndef _DEBUG_H
#define _DEBUG_H

#include <iostream>
#include <list>

#include "../diagonal/diagonal.hpp"
#include "../point/point.hpp"
#include "../pointset/pointset.hpp"
#include "../polygon/polygon.hpp"

/**
 * @brief Prints the coordinates of a point.
 *
 * @tparam T Type of the point's coordinates.
 * @param p The point to print.
 */
template <typename T>
void print(Point<T> p) {
    std::cout << "(" << p.x << ',' << p.y << ')';
}

/**
 * @brief Prints the vertices of a polygon.
 *
 * @tparam T Type of the polygon's vertices.
 * @param p The polygon to print.
 */
template <typename T>
void print(Polygon<T> p) {
    for (typename Polygon<T>::vptr it = p.begin(); it != p.end(); ++it) {
        print(*it);
        std::cout << " -> ";
    }
    print(*p.begin());
    std::cout << std::endl;
}

/**
 * @brief Prints a list of polygon vertices.
 *
 * @tparam T Type of the polygon vertices.
 * @param l The list of vertices to print.
 */
template <typename T>
void print(std::list<typename Polygon<T>::vptr> l) {
    for (auto &v : l) {
        print(*v);
        std::cout << " -> ";
    }
    std::cout << std::endl;
}

/**
 * @brief Prints the points in a point set.
 *
 * @tparam T Type of the point set's points.
 * @param ps The point set to print.
 */
template <typename T>
void print(PointSet<T> ps) {
    for (auto it = ps.begin(); it != ps.end(); ++it) {
        print(**it);
        std::cout << std::endl;
    }
}

/**
 * @brief Prints the endpoints of a diagonal.
 *
 * @tparam T Type of the diagonal endpoints.
 * @param d The diagonal to print.
 */
template <typename T>
void print(Diagonal<T> d) {
    std::cout << "Diagonal: ";
    print(d.u);
    std::cout << " -> ";
    print(d.v);
    std::cout << std::endl;
}

#endif
