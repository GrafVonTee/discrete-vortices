#include <cmath>
#include <limits>
#include "Profile.h"

Profile::Profile(value_type x0, value_type y0, segment_number_type numberOfSegments) {
    m_x0 = x0;
    m_y0 = y0;
    m_numberOfSegments = numberOfSegments;
    m_curve.reserve(numberOfSegments);
}

void Profile::emplaceIntoCurve(Point newPoint) {
    if (m_curve.size() == m_numberOfSegments) {
        return;
    }

    m_curve.push_back(newPoint);
}

void Profile::calculateCharacteristics() {
    if (b_isCalculated) {
        return;
    }

    if (m_curve.size() != m_numberOfSegments) {
        m_middleCurve = Curve(m_numberOfSegments, Point { 0, 0 });
        m_chord = Curve(2, Point {0, 0});
        return;
    }

    m_middleCurve.reserve(m_curve.size() / 2);
    m_chord = Curve {
        Point { std::numeric_limits<value_type>::max(), 0 },
        Point { std::numeric_limits<value_type>::min(), 0 }
    };
    m_relativeThickness = 0;
    value_type epsilon = 1e-3;

    for (int i = 0; i < m_curve.size() / 2; ++i) {
        Point beginPoint(m_curve[i]), endPoint(m_curve[m_curve.size() - i - 1]);
        m_middleCurve.push_back((beginPoint + endPoint) / 2);
            
        value_type thicc = sqrtl(powl(beginPoint.x - endPoint.x, 2) + powl(beginPoint.y - endPoint.y, 2));
        m_relativeThickness = (m_relativeThickness > thicc) ? m_relativeThickness : thicc;
    }
    m_chord = Curve { m_middleCurve[0], m_middleCurve[m_middleCurve.size() - 1] };
    m_chordLength = sqrtl(powl(m_chord[0].x - m_chord[1].x, 2) + powl(m_chord[0].y - m_chord[1].y, 2));
    m_relativeThickness /= m_chordLength;
    b_isCalculated = true;
}

const Curve& Profile::getContour() {
    return m_curve;
}

const Curve& Profile::getMiddleLine() {
    calculateCharacteristics();
    return m_middleCurve;
}

const Curve& Profile::getChord() {
    calculateCharacteristics();
    return m_chord;
}

const value_type Profile::getRelativeThickness() {
    calculateCharacteristics();
    return m_relativeThickness;
}

const value_type Profile::getChordLength() {
    calculateCharacteristics();
    return m_chordLength;
}