#ifndef NUMERIC_H
#define NUMERIC_H

#include <cmath>
#include <limits>
#include <iostream>

/**
 * @brief use of machine epsilon to compare floating-point values for equality
 * http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
 */
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    almost_equal(T x, T y, int ulp=2)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x-y) <= std::numeric_limits<T>::epsilon() * std::abs(x+y) * ulp
    // unless the result is subnormal
        || std::abs(x-y) < std::numeric_limits<T>::min();
}
#endif // NUMERIC_H
