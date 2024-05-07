#pragma once

#include <vector>
#include "Point.h"

using segment_number_type = long int;

using Curve = std::vector<Point>;

class Profile {
    value_type m_x0, m_y0; 
    segment_number_type m_numberOfSegments;
    Curve m_curve;
    Curve m_middleCurve;
    Curve m_chord;
    value_type m_relativeThickness;
    value_type m_chordLength;
    bool b_isCalculated = false;

    void calculateCharacteristics();

public:
    Profile(value_type x0, value_type y0, segment_number_type numberOfSegments);

    void emplaceIntoCurve(Point newPoint);

    const Curve& getContour();
    const Curve& getMiddleLine();
    const Curve& getChord();
    const value_type getChordLength();
    const value_type getRelativeThickness();

    const value_type getX0() { return m_x0; };
    const value_type getY0() { return m_y0; };
    const value_type getNumberOfSegments() { return m_numberOfSegments; }
};