#ifndef _DIAGONAL_H
#define _DIAGONAL_H

#include "../polygon/polygon.hpp"

template <typename T>
class Diagonal {
public:
    typename Polygon<T>::vptr u;
    typename Polygon<T>::vptr v;

    Diagonal(typename Polygon<T>::vptr u, typename Polygon<T>::vptr v) {
        this->u = u;
        this->v = v;
        if (*(this->v) < *(this->u)) {
            swap(this->u, this->v);
        }
    }

    bool operator==(const Diagonal<T>& other) const {
        return (*u == *(other.u)) and (*v == *(other.v));
    }

    bool operator<(const Diagonal<T>& other) const {
        return (*u < *other.u) or (*u == *(other.u) and (*v < *(other.v)));
    }
};

#endif
