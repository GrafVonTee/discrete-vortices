#pragma once

#include <vector>

using value_type = long double;
using segment_number_type = long int;

struct Point {
    value_type x, y;

    Point operator+(Point const& other);
    Point operator/(value_type scalar);
};

using Curve = std::vector<Point>;

class Profile {
    segment_number_type numberOfSegments;
    Curve curve;
    Curve middleCurve;
    Curve chord;
    value_type relativeThickness;
    bool calculated = false;

    void calculateCharacteristics();

public:
    Profile(segment_number_type numberOfSegments_);

    void emplaceIntoCurve(Point newPoint);
    Curve getMiddleLine();
    Curve getChord();
    value_type getRelativeThickness();
};