#ifndef _DSU_H
#define _DSU_H

#include <cassert>
#include <vector>

class DSU {
public:
    DSU() : _n(0) {}

    explicit DSU(int n) : _n(n), parent_or_size(n, -1) {}

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) {
            return x;
        }
        if (-parent_or_size[x] < -parent_or_size[y]) {
            std::swap(x, y);
        }
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        return x;
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) {
            return a;
        }
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

private:
    int _n;
    std::vector<int> parent_or_size;
};

#endif
