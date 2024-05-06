#include <cmath>
#include <limits>
#include "Profile.h"

Profile::Profile(value_type newX0, value_type newY0, segment_number_type numberOfSegments_) {
    x0 = newX0;
    y0 = newY0;
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

    for (int i = 0; i < curve.size() / 2; ++i) {
        Point beginPoint(curve[i]), endPoint(curve[curve.size() - i - 1]);
        middleCurve.push_back((beginPoint + endPoint) / 2);
            
        if (fabsl(beginPoint.x - endPoint.x) < epsilon) {
            value_type thicc = fabsl(beginPoint.y - endPoint.y);
            relativeThickness = (relativeThickness > thicc) ? relativeThickness : thicc;
        }
    }
    chord = Curve { middleCurve[0], middleCurve[middleCurve.size() - 1] };
    calculated = true;
}

const Curve& Profile::getContour() {
    return curve;
}

const Curve& Profile::getMiddleLine() {
    calculateCharacteristics();
    return middleCurve;
}

const Curve& Profile::getChord() {
    calculateCharacteristics();
    return chord;
}

const value_type Profile::getRelativeThickness() {
    calculateCharacteristics();
    return relativeThickness;
}