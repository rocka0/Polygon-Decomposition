/**
 * @file diagonal.hpp
 * @brief Definition of the Diagonal class.
 */

#ifndef _DIAGONAL_H
#define _DIAGONAL_H

#include "../polygon/polygon.hpp"

/**
 * @class Diagonal
 * @brief A class representing a diagonal of a polygon.
 * @tparam T The type of the diagonal's endpoints.
 */
template <typename T>
class Diagonal {
public:
    /**
     * @brief The first endpoint of the diagonal.
     */
    Point<T> u;

    /**
     * @brief The second endpoint of the diagonal.
     */
    Point<T> v;

    /**
     * @brief Parameterized constructor.
     * @param u The first endpoint of the diagonal.
     * @param v The second endpoint of the diagonal.
     */
    Diagonal(Point<T> u, Point<T> v) {
        this->u = u;
        this->v = v;
        if (this->v < this->u) {
            std::swap(this->u, this->v);
        }
    }

    /**
     * @brief Equality comparison operator.
     * @param other The other diagonal to compare to.
     * @return True if the two diagonals have the same endpoints, false otherwise.
     */
    bool operator==(const Diagonal<T>& other) const {
        return (u == other.u) and (v == other.v);
    }

    /**
     * @brief Less-than comparison operator.
     * @param other The other diagonal to compare to.
     * @return True if this diagonal is "less than" the other diagonal according to the ordering
     * (u, v), false otherwise.
     */
    bool operator<(const Diagonal<T>& other) const {
        return (u < other.u) or (u == other.u and v < other.v);
    }
};

#endif
