#include <cmath>
#include <limits>
#include "profile.h"

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

Profile::Profile(segment_number_type numberOfSegments_) {
    numberOfSegments = numberOfSegments_;
    curve.reserve(numberOfSegments);
}

void Profile::emplaceIntoCurve(Point newPoint) {
    if (curve.size() == numberOfSegments) {
        return;
    }

    curve.push_back(newPoint);
}

void Profile::calculateCharacteristics() {
    if (calculated) {
        return;
    }

    if (curve.size() != numberOfSegments) {
        middleCurve = Curve(numberOfSegments, Point { 0, 0 });
        chord = Curve(2, Point {0, 0});
        return;
    }

    middleCurve.reserve(curve.size() / 2);
    chord = Curve {
        Point { std::numeric_limits<value_type>::max(), 0 },
        Point { std::numeric_limits<value_type>::min(), 0 }
    };
    relativeThickness = 0;
    value_type epsilon = 1e-3;

    for (int i = 0; i < middleCurve.size(); ++i) {
        Point beginPoint(curve[i]), endPoint(curve[curve.size() - i - 1]);
        middleCurve[i] = (beginPoint + endPoint) / 2;
        
        if (chord[0].x > beginPoint.x) {
            chord[0] = beginPoint;
        } else if (chord[0].x > endPoint.x) {
            chord[0] = endPoint;
        }
        
        if (chord[1].x < beginPoint.x) {
            chord[1] = beginPoint;
        } else if (chord[1].x < endPoint.x) {
            chord[1] = endPoint;
        }
            
        if (fabsl(beginPoint.x - endPoint.x) < epsilon) {
            value_type thicc = fabsl(beginPoint.y - endPoint.y);
            relativeThickness = (relativeThickness > thicc) ? relativeThickness : thicc;
        }
    }
    calculated = true;
}

Curve Profile::getMiddleLine() {
    calculateCharacteristics();
    return middleCurve;
}

Curve Profile::getChord() {
    calculateCharacteristics();
    return chord;
}

value_type Profile::getRelativeThickness() {
    calculateCharacteristics();
    return relativeThickness;
}