#ifndef VEC_H
#define VEC_H

#include "numeric.h"
#include <QPoint>

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

    operator QPoint() const{
        return QPoint(static_cast<int>(x),static_cast<int>(y));
    }

    // Векторное произведение
    double cross(const Vector2&a) const {
       return x * a.y - a.x * y;
    }

    // Векторное произведение
    double len() const {
       return sqrt(x * x + y * y);
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
std::ostream &operator << (std::ostream &str, Vector2 const &point);

bool almost_equal(const Vector2& v1, const Vector2& v2, int ulp=2);

inline Vector2 operator*(const Vector2& vec, int alpha){
    return Vector2(vec.x*alpha,vec.y*alpha);
}
inline Vector2 operator*(int alpha, const Vector2& vec){
  return Vector2(vec.x*alpha,vec.y*alpha);
}
inline Vector2 operator*(const Vector2& vec, double alpha){
    return Vector2(vec.x*alpha,vec.y*alpha);
}
inline Vector2 operator/(const Vector2& vec, double alpha){
    return Vector2(vec.x/alpha,vec.y/alpha);
}
inline Vector2 operator*(double alpha, const Vector2& vec){
  return Vector2(vec.x*alpha,vec.y*alpha);
}

#endif // VEC_H
