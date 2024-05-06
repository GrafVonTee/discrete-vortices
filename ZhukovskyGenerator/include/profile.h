#pragma once

#include <vector>
#include "Point.h"

using segment_number_type = long int;

using Curve = std::vector<Point>;

class Profile {
    value_type x0, y0; 
    segment_number_type numberOfSegments;
    Curve curve;
    Curve middleCurve;
    Curve chord;
    value_type relativeThickness;
    bool calculated = false;

    void calculateCharacteristics();

public:
    Profile(value_type newX0, value_type newY0, segment_number_type numberOfSegments_);

    void emplaceIntoCurve(Point newPoint);

    const Curve& getContour();
    const Curve& getMiddleLine();
    const Curve& getChord();
    const value_type getRelativeThickness();

    const value_type getX0() { return x0; };
    const value_type getY0() { return y0; };
    const value_type getNumberOfSegments() { return numberOfSegments; }
};