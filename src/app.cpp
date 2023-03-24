/**
 * @app.cpp
 * This file contains the implementation of the polygon decomposition algorithm.
 */
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "boundingbox/boundingbox.hpp"
#include "debugging/print.hpp"
#include "diagonal/diagonal.hpp"
#include "dsu/dsu.hpp"
#include "mesh/mesh.hpp"
#include "pointset/pointset.hpp"
#include "utils/orientation.hpp"

using namespace std;

///< Datatype of the coordinates of the point
typedef long double ptype;
typedef Point<ptype> point;
typedef Polygon<ptype> polygon;
typedef polygon::vptr vptr;
typedef BoundingBox<ptype> boundingbox;
typedef PointSet<ptype> pointset;
typedef Diagonal<ptype> diagonal;

/**
 * @brief Function to check if a vertex x of type vptr (vertex pointer) is inside
 * the list of vertices L
 * @param L List of vertex pointers
 * @param x Vertex pointer
 * @return `true` if `x` is inside `L`, otherwise `false`
 */
bool insideL(list<vptr> &L, vptr x) {
    for (auto it = L.begin(); it != L.end(); ++it) {
        vptr u = *it;
        vptr v;
        if (next(it) == L.end()) {
            v = *L.begin();
        } else {
            v = *next(it);
        }
        if (getOrientation(*u, *v, *x) == LEFT_TURN) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Returns pointer to vertex in P which is a notch inside the convex polygon enclosed by L
 * @param P Polygon
 * @param L List of vertices
 * @param R Bounding box
 * @param PS Point set
 * @return Pointer to the vertex in `P` which is a notch inside the convex polygon enclosed by `L`. If no such vertex exists, returns `P.end()`
 */
vptr getNotchInsideL(polygon &P, list<vptr> &L, boundingbox &R, pointset &PS) {
    for (auto it = PS.begin(); it != PS.end();) {
        vptr v = *it;
        if (!P.notch(v) or !R.inside(v) or !insideL(L, v)) {
            it = next(it);
            PS.erase(v);
        } else {
            return v;
        }
    }
    return P.end();
}

/**
 * @brief Builds the list of vertices L for the polygon P
 * @param P The polygon to be processed
 * @param start The pointer to the vertex at which to start the processing of the polygon P
 * @return The list of vertices L
 */
list<vptr> buildL(polygon &P, vptr start) {
    list<vptr> L;

    L.push_back(start);
    L.push_back(P.nextVertex(start));

    while (L.size() < P.size()) {
        vptr v_i = L.back();
        vptr v_i_plus_1 = P.nextVertex(v_i);
        vptr v_1 = *L.begin();
        vptr v_2 = P.nextVertex(v_1);

        // Case 1: v_{i-1} -> v_{i} -> v_{i+1} is > 180 degrees
        if (P.notch(v_i)) break;

        // Case 2: v_{i} -> v_{i+1} -> v_{1} is > 180 degrees
        if (getOrientation(*v_i, *v_i_plus_1, *v_1) == LEFT_TURN) break;

        // Case 3: v_{i+1} -> v_{1} -> v_{2} is > 180 degrees
        if (getOrientation(*v_i_plus_1, *v_1, *v_2) == LEFT_TURN) break;

        L.push_back(v_i_plus_1);
    }

    boundingbox R(L);
    pointset PS(P, L);
    vptr pivot = getNotchInsideL(P, L, R, PS);

    while (pivot != P.end()) {
        ORIENTATION bad = getOrientation(*L.front(), *pivot, *L.back());
        L.pop_back();
        while (L.size() > 2 and getOrientation(*L.front(), *pivot, *L.back()) == bad) {
            L.pop_back();
        }
        R = boundingbox(L);
        pivot = getNotchInsideL(P, L, R, PS);
    }

    return L;
}

/**
 * @brief Removes the edges defined by the vertices in L from the polygon P
 * @param P The polygon from which edges need to be removed
 * @param L The list of vertices representing the edges to be removed from P
 */
void eraseEdges(polygon &P, list<vptr> &L) {
    auto it = L.begin();
    for (int i = 0; i < static_cast<int>(L.size()) - 2; ++i) {
        it = next(it);
        P.removeVertex(*it);
    }
    vptr head = P.begin();
    while (head != L.back()) {
        head = P.nextVertex(head);
    }
    while (head != P.begin()) {
        P.addVertex(*P.begin());
        P.removeVertex(P.begin());
    }
}

/**
 * @brief Decomposes polygon P into 2 convex polygons
 * @param P The polygon to be decomposed
 * @return A polygon representing one of the two convex polygons after decomposition; P is the remaining polygon after the returned polygon is cut off
 */
polygon decompose(polygon &P) {
    if (P.size() <= 2) return P;

    list<vptr> L;
    vptr s = P.begin();

    while (L.size() < 3) {
        L = buildL(P, s);
        s = P.nextVertex(s);
    }

    polygon decomposition;
    for (auto &v : L) decomposition.addVertex(*v);
    eraseEdges(P, L);

    return decomposition;
}

/**
 * @brief Returns pointer to vertex in P which is a notch inside the convex polygon enclosed by L
 * @param P Polygon
 * @param L List of vertices
 * @param R Bounding box
 * @param PS Point set
 * @return Pointer to the vertex in `P` which is a notch inside the convex polygon enclosed by `L`. If no such vertex exists, returns `P.end()`
 */
bool belongsToPolygon(diagonal d, polygon &P) {
    for (auto it = P.begin(); it != P.end(); ++it) {
        diagonal edge{*it, *P.nextVertex(it)};
        if (d == edge) {
            return true;
        }
    }
    return false;
}

/**
 * Builds the LLE data structure according to the paper. The LLE stores the left and right faces of a diagonal.
 *
 * @param P             the polygon
 * @param decomposition the polygon's decomposition
 * @param LLE           the LLE data structure to be built
 */
void buildLLE(polygon &P, vector<polygon> &decomposition, map<diagonal, pair<int, int>> &LLE) {
    for (int i = 0; i < (int) decomposition.size(); ++i) {
        for (auto it = decomposition[i].begin(); it != decomposition[i].end(); ++it) {
            diagonal edge{*it, *decomposition[i].nextVertex(it)};
            if (!belongsToPolygon(edge, P)) {
                if (LLE.count(edge)) {
                    // second occurence of edge in LLE, update left face
                    LLE[edge].second = i;
                } else {
                    // first occurence of edge in LLE, update righ face
                    LLE[edge].first = i;
                }
            }
        }
    }
}

/**
 * @brief Comparator for sorting points in the LP data structure.
 */
struct LP_CMP {
    /**
     * @brief Compares two points.
     * @param a First point.
     * @param b Second point.
     * @return True if a < b, false otherwise.
     */
    bool operator()(const point a, const point b) const {
        return a < b;
    }
};

/**
 * @brief Builds the LP data structure.
 *
 * The LP data structure maps a point to its neighboring faces.
 *
 * @param LLE Map storing the left and right faces of each diagonal.
 * @param LP Map to be constructed.
 */
void buildLP(map<diagonal, pair<int, int>> &LLE, map<point, vector<pair<int, point>>, LP_CMP> &LP) {
    for (auto &[diag, faces] : LLE) {
        LP[diag.u].push_back({faces.first, diag.v});
        LP[diag.u].push_back({faces.second, diag.v});
        LP[diag.v].push_back({faces.first, diag.u});
        LP[diag.v].push_back({faces.second, diag.u});
    }
}

/**
 * @brief Check if a diagonal can be removed from the polygon without breaking the convexity of the decomposition.
 *
 * @param d The diagonal to be removed.
 * @param LP A map of point to all its neighbouring faces
 * @param P The polygon.
 * @param LLE A map containing the left and right faces of each diagonal.
 * @param decomposition The decomposition of the polygon.
 * @param unionFind A data structure to maintain the connected components of the decomposition.
 * @return True if the diagonal can be removed without breaking the convexity, false otherwise.
 */
bool canRemoveDiagonal(diagonal d, map<point, vector<pair<int, point>>, LP_CMP> &LP, polygon &P, map<diagonal, pair<int, int>> &LLE, vector<polygon> &decomposition, DSU &unionFind) {
    point u = d.u;
    point v = d.v;
    vptr uinP = P.find(u);
    vptr vinP = P.find(v);

    bool c1 = LP[u].size() > 2 and LP[v].size() > 2;
    bool c2 = LP[u].size() > 2 and !P.notch(vinP);
    bool c3 = LP[v].size() > 2 and !P.notch(uinP);
    bool c4 = !P.notch(uinP) and !P.notch(vinP);

    if (c1 or c2 or c3 or c4) {
        pair<int, int> faces = LLE[d];
        int LF = unionFind.leader(faces.first);
        int RF = unionFind.leader(faces.second);

        vptr uinRF, uinLF, vinRF, vinLF;
        uinRF = decomposition[RF].find(u);
        if (*decomposition[RF].nextVertex(uinRF) != v) {
            swap(LF, RF);
        }
        LLE[d] = {LF, RF};
        uinRF = decomposition[RF].find(u);
        uinLF = decomposition[LF].find(u);
        vinRF = decomposition[RF].find(v);
        vinLF = decomposition[LF].find(v);

        point prevU = *decomposition[RF].previousVertex(uinRF);
        point succU = *decomposition[LF].nextVertex(uinLF);
        point prevV = *decomposition[LF].previousVertex(vinLF);
        point succV = *decomposition[RF].nextVertex(vinRF);

        return getOrientation(prevU, u, succU) == RIGHT_TURN and getOrientation(prevV, v, succV) == RIGHT_TURN;
    } else {
        return false;
    }
}

/**
 * @brief Merge the two faces on either side of diagonal d.
 *
 * @param d Diagonal to be removed.
 * @param LLE Map containing the left and right faces of each diagonal.
 * @param decomposition Vector of polygons representing the decomposition.
 * @param unionFind A data structure to maintain the connected components of the decomposition.
 */
void merge(diagonal d, map<diagonal, pair<int, int>> &LLE, vector<polygon> &decomposition, DSU &unionFind) {
    pair<int, int> faces = LLE[d];
    int LF = unionFind.leader(faces.first);
    int RF = unionFind.leader(faces.second);

    vptr uinLF, vinRF;
    uinLF = decomposition[LF].find(d.u);
    vinRF = decomposition[RF].find(d.v);

    polygon merged;
    vptr vp = uinLF;
    while (*vp != d.v) {
        merged.addVertex(*vp);
        vp = decomposition[LF].nextVertex(vp);
    }
    vp = vinRF;
    while (*vp != d.u) {
        merged.addVertex(*vp);
        vp = decomposition[RF].nextVertex(vp);
    }

    unionFind.merge(LF, RF);
    if (unionFind.leader(LF) == LF) {
        decomposition[LF] = merged;
    } else {
        decomposition[RF] = merged;
    }
}

/**
 * @brief This function iterates over all diagonals in LLE and tries to merge them
 *
 * @param LP A map of point to all its neighbouring faces
 * @param P The polygon to be merged
 * @param LLE A map that stores the left and right faces of each diagonal
 * @param decomposition A vector of polygons that stores the decomposition of the polygon P
 * @param unionFind A data structure to maintain the connected components of the decomposition.
 */
void mergePolygons(map<point, vector<pair<int, point>>, LP_CMP> &LP, polygon &P, map<diagonal, pair<int, int>> &LLE, vector<polygon> &decomposition, DSU &unionFind) {
    for (auto &[diag, _] : LLE) {
        if (canRemoveDiagonal(diag, LP, P, LLE, decomposition, unionFind)) {
            merge(diag, LLE, decomposition, unionFind);
        }
    }
}

/**
 * @brief Outputs the decomposition to a file
 *
 * This function outputs the decomposition to a file so that it can be read by other sources.
 *
 * @param decomposition Vector of polygons representing the decomposition
 * @param fileName Name of the output file
 */
void outputDecomposition(vector<polygon> &decomposition, string fileName) {
    ofstream outputFile(fileName);
    outputFile << fixed << setprecision(14);
    outputFile << decomposition.size() << endl;
    for (auto &p : decomposition) {
        outputFile << p.size() << endl;
        for (auto it = p.begin(); it != p.end(); ++it) {
            outputFile << it->x << ' ' << it->y << endl;
        }
    }
    outputFile.close();
}

/**
 * @brief This function is used to extract the final diagonals which will be passed to the DCEL
 * which will use the diagonals to split faces and store the subdivision information
 *
 * @param LLE Map containing the diagonals and their adjacent faces
 * @param unionFind The data structure representing the sets of connected faces
 * @param finalDiagonals Vector to store the final diagonals
 */
void extractFinalDiagonals(map<diagonal, pair<int, int>> &LLE, DSU &unionFind, vector<pair<point, point>> &finalDiagonals) {
    for (auto &[diag, faces] : LLE) {
        if (unionFind.leader(faces.first) != unionFind.leader(faces.second)) {
            finalDiagonals.push_back({diag.u, diag.v});
        }
    }
}

/**
 * @brief Entry point of the program that computes the convex planar subdivision of a simple polygon
 *
 * @return int Exit status of the program
 */
int main() {
    int n;
    cin >> n;

    polygon input, inputCopy;
    vector<point> dcelInput(n);
    for (int i = 0; i < n; ++i) {
        point p;
        cin >> p.x >> p.y;
        input.addVertex(p);
        dcelInput[i] = p;
    }
    inputCopy = input;

    // Build initial face in DCEL
    Mesh<ptype> DCEL;
    DCEL.createFace(dcelInput);

    vector<polygon> decomposition;
    while (input.size() > 2) {
        decomposition.push_back(decompose(input));
    }
    outputDecomposition(decomposition, "before.txt");
    input = move(inputCopy);

    map<diagonal, pair<int, int>> LLE;
    buildLLE(input, decomposition, LLE);

    map<point, vector<pair<int, point>>, LP_CMP> LP;
    buildLP(LLE, LP);

    DSU unionFind(decomposition.size());

    mergePolygons(LP, input, LLE, decomposition, unionFind);

    vector<polygon> finalDecomposition;
    finalDecomposition.reserve(decomposition.size());
    for (int i = 0; i < (int) decomposition.size(); ++i) {
        if (unionFind.leader(i) == i) {
            finalDecomposition.push_back(decomposition[i]);
        }
    }
    outputDecomposition(finalDecomposition, "after.txt");

    vector<pair<point, point>> finalDiagonals;
    extractFinalDiagonals(LLE, unionFind, finalDiagonals);

    DCEL.decomposePolygon(finalDiagonals);
}
