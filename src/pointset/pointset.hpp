#ifndef _POINTSET_H
#define _POINTSET_H

#include <set>

#include "../polygon/polygon.hpp"

template <typename T>
class PointSet {
    struct VertexPointerCmp {
        bool operator()(typename Polygon<T>::vptr a, typename Polygon<T>::vptr b) const {
            if (a->x < b->x) {
                return true;
            } else if (a->x > b->x) {
                return false;
            } else {
                return a->y < b->y;
            }
        }
    };

    std::set<typename Polygon<T>::vptr, VertexPointerCmp> points;

public:
    PointSet(Polygon<T> &P, std::list<typename Polygon<T>::vptr> &L) {
        typename Polygon<T>::vptr it = P.begin();
        while (it != P.end()) {
            points.insert(it);
            it = next(it);
        }

        for (auto &v : L) points.erase(v);
    }

    void erase(typename Polygon<T>::vptr v) {
        points.erase(v);
    }

    typename std::set<typename Polygon<T>::vptr, VertexPointerCmp>::iterator begin() {
        return points.begin();
    }

    typename std::set<typename Polygon<T>::vptr, VertexPointerCmp>::iterator end() {
        return points.end();
    }
};

#endif
