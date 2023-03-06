#ifndef _DIAGONAL_H
#define _DIAGONAL_H

#include "../polygon/polygon.hpp"

template <typename T>
class Diagonal {
public:
    Point<T> u;
    Point<T> v;

    Diagonal(Point<T> u, Point<T> v) {
        this->u = u;
        this->v = v;
        if (this->v < this->u) {
            std::swap(this->u, this->v);
        }
    }

    bool operator==(const Diagonal<T>& other) const {
        return (u == other.u) and (v == other.v);
    }

    bool operator<(const Diagonal<T>& other) const {
        return (u < other.u) or (u == other.u and v < other.v);
    }
};

#endif
