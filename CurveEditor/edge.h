#ifndef EDGE_H
#define EDGE_H

#include "vec.h"
#include <iostream>

struct Edge
{
        Edge(const Vector2 &p1, const Vector2 &p2) : p1(p1), p2(p2), isBad(false) {}
        Edge(const Edge &e) : p1(e.p1), p2(e.p2), isBad(false) {}

        Vector2 p1;
        Vector2 p2;

        bool isBad;
};

inline std::ostream &operator << (std::ostream &str, Edge const &e){
    return str << "Edge " << e.p1 << ", " << e.p2;
}

inline bool almost_equal (const Edge & e1, const Edge & e2){
    return	(almost_equal(e1.p1, e2.p1) && almost_equal(e1.p2, e2.p2)) ||
            (almost_equal(e1.p1, e2.p2) && almost_equal(e1.p2, e2.p1));
}

#endif // EDGE_H
