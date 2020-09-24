#include "vec.h"
std::ostream &operator << (std::ostream &str, Vector2 const &point){
    return str << "Point x: " << point.x << " y: " << point.y;
}

bool almost_equal(const Vector2& v1, const Vector2& v2, int ulp){
    return almost_equal(v1.x, v2.x, ulp) && almost_equal(v1.y, v2.y, ulp);
}
