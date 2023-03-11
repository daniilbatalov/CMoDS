#include "aux/math_aux.h"

namespace MathAux
{
    int euclidean_remainder(int a, int b)
    {
        int r = a % b;
        return r >= 0 ? r : r + std::abs(b);
    }
}
