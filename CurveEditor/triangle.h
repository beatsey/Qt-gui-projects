#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "edge.h"
#include "numeric.h"

struct Triangle
{
        Triangle(const Vector2 &_p1, const Vector2 &_p2, const Vector2 &_p3)
        :	p1(_p1), p2(_p2), p3(_p3),
            e1(_p1, _p2), e2(_p2, _p3), e3(_p3, _p1), isBad(false),colored(false)
        {}

        bool containsVertex(const Vector2 &v) const
        {
            // return p1 == v || p2 == v || p3 == v;
            return almost_equal(p1, v) || almost_equal(p2, v) || almost_equal(p3, v);
        }

        bool circumCircleContains(const Vector2 &v) const
        {
            const double ab = p1.len2();
            const double cd = p2.len2();
            const double ef = p3.len2();

            const double circum_x = (ab * (p3.y - p2.y) + cd * (p1.y - p3.y) + ef * (p2.y - p1.y)) / (p1.x * (p3.y - p2.y) + p2.x * (p1.y - p3.y) + p3.x * (p2.y - p1.y));
            const double circum_y = (ab * (p3.x - p2.x) + cd * (p1.x - p3.x) + ef * (p2.x - p1.x)) / (p1.y * (p3.x - p2.x) + p2.y * (p1.x - p3.x) + p3.y * (p2.x - p1.x));

            const Vector2 circum((circum_x)/2, (circum_y)/2);
            const double circum_radius = p1.squareDist(circum);
            const double dist = v.squareDist(circum);
            return dist <= circum_radius;
        }

        Vector2 p1;
        Vector2 p2;
        Vector2 p3;
        Edge e1;
        Edge e2;
        Edge e3;
        bool isBad;
        bool colored;
};
inline bool almost_equal(const Triangle &t1, Triangle const &t2)
{
    return	(almost_equal(t1.p1 , t2.p1) || almost_equal(t1.p1 , t2.p2) || almost_equal(t1.p1 , t2.p3)) &&
            (almost_equal(t1.p2 , t2.p1) || almost_equal(t1.p2 , t2.p2) || almost_equal(t1.p2 , t2.p3)) &&
            (almost_equal(t1.p3 , t2.p1) || almost_equal(t1.p3 , t2.p2) || almost_equal(t1.p3 , t2.p3));
}


#endif // TRIANGLE_H
