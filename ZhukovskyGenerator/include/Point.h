#pragma once

using value_type = long double;

struct Point {
    value_type x, y;

    Point operator+(Point const& other);
    Point operator/(value_type scalar);
    Point operator-(Point const& other);
};