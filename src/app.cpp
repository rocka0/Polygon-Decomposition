#include <cassert>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "boundingbox/boundingbox.hpp"
#include "debugging/print.hpp"
#include "diagonal/diagonal.hpp"
#include "pointset/pointset.hpp"

using namespace std;

typedef int ptype;
typedef Point<ptype> point;
typedef Polygon<ptype> polygon;
typedef polygon::vptr vptr;
typedef BoundingBox<ptype> boundingbox;
typedef PointSet<ptype> pointset;
typedef Diagonal<ptype> diagonal;

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

// returns pointer to vertex in P which is a notch inside the convex polygon enclosed by L
// returns P.end() if no such vertex exists
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

/*
Second half begins
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

struct LP_CMP {
    bool operator()(const point a, const point b) const {
        return a < b;
    }
};

void buildLP(map<diagonal, pair<int, int>> &LLE, map<point, vector<pair<int, point>>, LP_CMP> &LP) {
    for (auto &[diag, faces] : LLE) {
        LP[diag.u].push_back({faces.first, diag.v});
        LP[diag.u].push_back({faces.second, diag.v});
        LP[diag.v].push_back({faces.first, diag.u});
        LP[diag.v].push_back({faces.second, diag.u});
    }
}

int main() {
    cout << fixed << setprecision(14);

    int n;
    cin >> n;

    polygon input, inputCopy;
    for (int i = 0; i < n; ++i) {
        point p;
        cin >> p.x >> p.y;
        input.addVertex(p);
    }
    inputCopy = input;

    vector<polygon> decomposition;
    while (input.size() > 2) {
        decomposition.push_back(decompose(input));
    }
    cout << decomposition.size() << endl;
    for (auto &p : decomposition) {
        cout << p.size() << endl;
        for (auto it = p.begin(); it != p.end(); ++it) {
            cout << it->x << ' ' << it->y << endl;
        }
    }
    input = move(inputCopy);

    map<diagonal, pair<int, int>> LLE;
    buildLLE(input, decomposition, LLE);

    map<point, vector<pair<int, point>>, LP_CMP> LP;
    buildLP(LLE, LP);
}
