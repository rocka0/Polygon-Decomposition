/**
 * @file boundingbox.hpp
 * @brief Defines the BoundingBox class for a polygon in 2D.
 */

#ifndef _BOUNDING_BOX_H
#define _BOUNDING_BOX_H

#include "../polygon/polygon.hpp"

/**
 * @brief The BoundingBox class represents the minimum bounding box of a polygon in 2D.
 * @tparam T The type of the coordinates of the polygon.
 */
template <typename T>
class BoundingBox {
    T xmin; /**< The minimum x-coordinate of the bounding box. */
    T xmax; /**< The maximum x-coordinate of the bounding box. */
    T ymin; /**< The minimum y-coordinate of the bounding box. */
    T ymax; /**< The maximum y-coordinate of the bounding box. */

public:
    /**
     * @brief Constructs a BoundingBox object for a given polygon.
     * @param L A list of vertex pointers of the polygon.
     */
    BoundingBox(std::list<typename Polygon<T>::vptr> &L) {
        auto it = L.begin();
        xmin = xmax = (*it)->x;
        ymin = ymax = (*it)->y;
        it = next(it);
        while (it != L.end()) {
            xmin = std::min(xmin, (*it)->x);
            xmax = std::max(xmax, (*it)->x);
            ymin = std::min(ymin, (*it)->y);
            ymax = std::max(ymax, (*it)->y);
            it = next(it);
        }
    }

    /**
     * @brief Determines if a given vertex is inside the bounding box.
     * @param v A vertex pointer.
     * @return true if the vertex is inside the bounding box, false otherwise.
     */
    bool inside(typename Polygon<T>::vptr v) {
        return xmin <= v->x and v->x <= xmax and ymin <= v->y and v->y <= ymax;
    }
};

#endif
