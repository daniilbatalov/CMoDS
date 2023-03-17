#ifndef MATH_AUX_H
#define MATH_AUX_H

#include <cmath>

namespace MathAux
{
template<typename T>
T euclidean_remainder(T a, T b)
{
    T r = a % b;
    using std::abs;
    return r >= 0 ? r : r + abs(b);
}
}

#endif  // MATH_AUX_H
