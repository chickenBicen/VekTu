#include "../include/Vector2.hpp"
#include <cmath>

float
Vector2::length () const
{
    return std::sqrt (x * x + y * y);
}
