#include "Point.h"

Point Point::operator+(Point const& other) {
    Point result;
    result.x = x + other.x;
    result.y = y + other.y;
    return result;
}

Point Point::operator/(value_type scalar) {
    Point result;
    result.x = x / scalar;
    result.y = y / scalar;
    return result;
}