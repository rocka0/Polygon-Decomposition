#ifndef _BOUNDING_BOX_H
#define _BOUNDING_BOX_H

#include "../polygon/polygon.hpp"

template <typename T>
class BoundingBox {
    T xmin;
    T xmax;
    T ymin;
    T ymax;

public:
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

    bool inside(typename Polygon<T>::vptr v) {
        return xmin <= v->x and v->x <= xmax and ymin <= v->y and v->y <= ymax;
    }
};

#endif
