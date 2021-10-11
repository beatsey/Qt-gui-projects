#ifndef VECTOR2_H
#define VECTOR2_H

#include <QPoint>
#include <QtMath>

//#include <iostream>

#include "numeric.h"

struct Vector2{
    union {
        struct { double x,y; };
        double elem[2];
    };
    Vector2(double a=0,double b=0):x(a),y(b){}
    Vector2(const QPoint&a):x(a.x()),y(a.y()){}

    double squareDist(const Vector2&vec) const{
        double dx=x-vec.x,
               dy=y-vec.y;
        return dx*dx+dy*dy;
    }
    void operator+=(const Vector2&vec){
        x+=vec.x;
        y+=vec.y;
    }
    void operator-=(const Vector2&vec){
        x-=vec.x;
        y-=vec.y;
    }
    void operator*=(double alpha){
        x*=alpha;
        y*=alpha;
    }
    void operator/=(double alpha){
        x/=alpha;
        y/=alpha;
    }

    const Vector2 operator+(const Vector2&vec)const{
        return Vector2(x+vec.x,y+vec.y);
    }

    const Vector2 operator-(const Vector2&vec)const{
        return Vector2(x-vec.x,y-vec.y);
    }

    operator QPoint(){
        return QPoint(static_cast<int>(x),static_cast<int>(y));
    }

    // Векторное произведение
    double cross(const Vector2&a) const {
       return x * a.y - a.x * y;
    }

    // Векторное произведение
    double len() const {
       return qSqrt(x * x + y * y);
    }

    double len2() const {
        return x * x + y * y;
    }


    void normalize(){
       double length=len();
       x=x/length;
       y=y/length;
    }

    void neg(){
        x=-x;
        y=-y;
    }

};
/*
std::ostream &operator << (std::ostream &str, Vector2 const &point){
    return str << "Point x: " << point.x << " y: " << point.y;
}

typename std::enable_if<!std::numeric_limits<double>::is_integer, bool>::type
    almost_equal(const Vector2& v1, const Vector2& v2, int ulp=2){
    return almost_equal(v1.x, v2.x, ulp) && almost_equal(v1.y, v2.y, ulp);
}
*/
inline Vector2 operator*(const Vector2& vec, int alpha){
    return Vector2(vec.x*alpha,vec.y*alpha);
}
inline Vector2 operator*(int alpha, const Vector2& vec){
  return Vector2(vec.x*alpha,vec.y*alpha);
}
inline Vector2 operator*(const Vector2& vec, double alpha){
    return Vector2(vec.x*alpha,vec.y*alpha);
}
inline Vector2 operator*(double alpha, const Vector2& vec){
  return Vector2(vec.x*alpha,vec.y*alpha);
}

#endif // VECTOR2_H
