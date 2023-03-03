#ifndef _DEBUG_H
#define _DEBUG_H

#include <iostream>
#include <list>

#include "../point/point.hpp"
#include "../pointset/pointset.hpp"
#include "../polygon/polygon.hpp"

template <typename T>
void print(Point<T> &p) {
    std::cout << "(" << p.x << ',' << p.y << ')';
}

template <typename T>
void print(Polygon<T> &p) {
    for (typename Polygon<T>::vptr it = p.begin(); it != p.end(); ++it) {
        print(*it);
        std::cout << " -> ";
    }
    print(*p.begin());
    std::cout << std::endl;
}

template <typename T>
void print(std::list<typename Polygon<T>::vptr> &l) {
    for (auto &v : l) {
        print(*v);
        std::cout << " -> ";
    }
    std::cout << std::endl;
}

template <typename T>
void print(PointSet<T> &ps) {
    for (auto it = ps.begin(); it != ps.end(); ++it) {
        print(**it);
        std::cout << std::endl;
    }
}

#endif
