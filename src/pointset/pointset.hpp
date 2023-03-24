/**
 * @file pointset.hpp
 * @brief Definition of the PointSet class template and its associated function templates.
 */

#ifndef _POINTSET_H
#define _POINTSET_H

#include <set>

#include "../polygon/polygon.hpp"

/**
 * @brief PointSet class template.
 *
 * This class represents a set of points. It is implemented as a set of pointers to the vertices of a polygon.
 * When constructed, it takes a reference to a polygon and a list of vertex pointers to exclude from the set.
 *
 * @tparam T The type of the coordinates of the points.
 */
template <typename T>
class PointSet {
    /**
     * @brief Comparison function object for vertex pointers.
     *
     * This is a strict weak ordering function object that compares two vertex pointers based on the order
     * induced by the "<" operator applied to their corresponding points.
     */
    struct VertexPointerCmp {
        bool operator()(typename Polygon<T>::vptr a, typename Polygon<T>::vptr b) const {
            return *a < *b;
        }
    };

    std::set<typename Polygon<T>::vptr, VertexPointerCmp> points; /**< The set of vertex pointers. */

public:
    /**
     * @brief Constructs a PointSet.
     *
     * This constructor takes a reference to a polygon and a list of vertex pointers to exclude from the set.
     *
     * @param P The polygon.
     * @param L The list of vertex pointers to exclude.
     */
    PointSet(Polygon<T> &P, std::list<typename Polygon<T>::vptr> &L) {
        typename Polygon<T>::vptr it = P.begin();
        while (it != P.end()) {
            points.insert(it);
            it = next(it);
        }

        for (auto &v : L) points.erase(v);
    }

    /**
     * @brief Erases a vertex from the set.
     *
     * This function erases a vertex from the set.
     *
     * @param v The vertex pointer to erase.
     */
    void erase(typename Polygon<T>::vptr v) {
        points.erase(v);
    }

    /**
     * @brief Returns an iterator to the beginning of the set.
     *
     * This function returns an iterator to the beginning of the set.
     *
     * @return An iterator to the beginning of the set.
     */
    typename std::set<typename Polygon<T>::vptr, VertexPointerCmp>::iterator begin() {
        return points.begin();
    }

    /**
     * @brief Returns an iterator to the end of the set.
     *
     * This function returns an iterator to the end of the set.
     *
     * @return An iterator to the end of the set.
     */
    typename std::set<typename Polygon<T>::vptr, VertexPointerCmp>::iterator end() {
        return points.end();
    }
};

#endif
