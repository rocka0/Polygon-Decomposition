/**
 * @file dsu.h
 * @brief A Disjoint Set Union (DSU) data structure implementation for union-find operations.
 */

#ifndef _DSU_H
#define _DSU_H

#include <cassert>
#include <vector>

/**
 * @class DSU
 * @brief Disjoint Set Union (DSU) data structure for union-find operations.
 *
 * A class that implements the Disjoint Set Union (DSU) data structure for union-find operations.
 * It uses a vector to store the parent-or-size of each element in the set.
 * Negative values indicate the size of the set, while positive values indicate the parent of the element.
 */
class DSU {
public:
    /**
     * @brief Default constructor for DSU.
     *
     * Constructs a new empty DSU object.
     */
    DSU() : _n(0) {}

    /**
     * @brief Constructor for DSU.
     *
     * Constructs a new DSU object with `n` elements.
     *
     * @param n Number of elements in the DSU.
     */
    explicit DSU(int n) : _n(n), parent_or_size(n, -1) {}

    /**
     * @brief Merges two sets.
     *
     * Merges the sets containing elements `a` and `b`.
     * If `a` and `b` are already in the same set, returns the leader of the set.
     *
     * @param a First element.
     * @param b Second element.
     * @return Leader of the merged set.
     */
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

    /**
     * @brief Finds the leader of the set containing an element.
     *
     * Finds the leader of the set containing the element `a`.
     * If `a` is not in any set, returns `a`.
     *
     * @param a The element.
     * @return Leader of the set containing `a`.
     */
    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) {
            return a;
        }
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

private:
    int _n;                             ///< Number of elements in the DSU.
    std::vector<int> parent_or_size;    ///< Parent or size of each element in the DSU.
};

#endif
