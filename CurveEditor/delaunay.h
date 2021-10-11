#ifndef DELAUNAY_H
#define DELAUNAY_H

#include "vec.h"
#include "edge.h"
#include "triangle.h"

#include <iostream>
#include <vector>
#include <algorithm>

/*
    Триангуляция Делоне
    Алгоритм Бауэра-Ватсона
    https://en.wikipedia.org/wiki/Bowyer%E2%80%93Watson_algorithm
*/

struct Delaunay
{
    // Рамка триангуляции
    double minX;
    double minY;
    double maxX;
    double maxY;

        const std::vector<Triangle>& triangulate(std::vector<Vector2> &vertices)
        {
            _triangles.clear();
            _edges.clear();

            // Determinate the super triangle
            minX = vertices[0].x;
            minY = vertices[0].y;
            maxX = minX;
            maxY = minY;

            for(std::size_t i = 0; i < vertices.size(); ++i)
            {
                if (vertices[i].x < minX) minX = vertices[i].x;
                if (vertices[i].y < minY) minY = vertices[i].y;
                if (vertices[i].x > maxX) maxX = vertices[i].x;
                if (vertices[i].y > maxY) maxY = vertices[i].y;
            }

            const double dx = maxX - minX;
            const double dy = maxY - minY;
            const double deltaMax = std::max(dx, dy);
            const double midx = (minX + maxX)/2;
            const double midy = (minY + maxY)/2;

            const Vector2 p1(midx - 20 * deltaMax, midy - deltaMax);
            const Vector2 p2(midx, midy + 20 * deltaMax);
            const Vector2 p3(midx + 20 * deltaMax, midy - deltaMax);

            //std::cout << "Super triangle " << std::endl << Triangle(p1, p2, p3) << std::endl;

            // Create a list of triangles, and add the supertriangle in it
            _triangles.push_back(Triangle(p1, p2, p3));

            for(auto p = begin(vertices); p != end(vertices); p++)
            {
                //std::cout << "Traitement du point " << *p << std::endl;
                //std::cout << "_triangles contains " << _triangles.size() << " elements" << std::endl;

                std::vector<Edge> polygon;

                for(auto & t : _triangles)
                {
                    //std::cout << "Processing " << std::endl << *t << std::endl;

                    if(t.circumCircleContains(*p))
                    {
                        //std::cout << "Pushing bad triangle " << *t << std::endl;
                        t.isBad = true;
                        polygon.push_back(t.e1);
                        polygon.push_back(t.e2);
                        polygon.push_back(t.e3);
                    }
                    else
                    {
                        //std::cout << " does not contains " << *p << " in his circum center" << std::endl;
                    }
                }

                _triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [](Triangle &t){
                    return t.isBad;
                }), end(_triangles));

                for(auto e1 = begin(polygon); e1 != end(polygon); ++e1)
                {
                    for(auto e2 = e1 + 1; e2 != end(polygon); ++e2)
                    {
                        if(almost_equal(*e1, *e2))
                        {
                            e1->isBad = true;
                            e2->isBad = true;
                        }
                    }
                }

                polygon.erase(std::remove_if(begin(polygon), end(polygon), [](Edge &e){
                    return e.isBad;
                }), end(polygon));

                for(auto const &e : polygon)
                    _triangles.push_back(Triangle(e.p1, e.p2, *p));

            }

            _triangles.erase(std::remove_if(begin(_triangles), end(_triangles), [p1, p2, p3](Triangle &t){
                return t.containsVertex(p1) || t.containsVertex(p2) || t.containsVertex(p3);
            }), end(_triangles));

            for(auto const &t : _triangles)
            {
                _edges.push_back(t.e1);
                _edges.push_back(t.e2);
                _edges.push_back(t.e3);
            }

            return _triangles;
        }

        std::vector<Triangle>& getTriangles(){ return _triangles; }
        std::vector<Edge>& getEdges(){ return _edges; }

        const std::vector<Triangle>& getTriangles() const { return _triangles; }
        const std::vector<Edge>& getEdges() const { return _edges; }

    private:
        std::vector<Triangle> _triangles;
        std::vector<Edge> _edges;
};

#endif // DELAUNAY_H
