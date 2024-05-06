#define _USE_MATH_DEFINES

#include "ProfileGenerator.h"
#include <cmath>

Profile ProfileGenerator::generateProfile(segment_number_type numberOfSegments) {
    Profile profile(x0, y0, numberOfSegments);
    value_type thetaShift = 2 * M_PI / numberOfSegments;
    value_type arm = sqrtl(powl(1 - x0, 2) + powl(y0, 2));

    for (int i = 0; i < numberOfSegments; ++i) {
        value_type x1 = arm * cosl(thetaShift * i) + x0;
        value_type y1 = arm * sinl(thetaShift * i) + y0;

        value_type xCurve = (x1 * (powl(x1, 2) + powl(y1, 2) + 1)) / (powl(x1, 2) + powl(y1, 2));
        value_type yCurve = (y1 * (powl(x1, 2) + powl(y1, 2) - 1)) / (powl(x1, 2) + powl(y1, 2));

        profile.emplaceIntoCurve(Point { xCurve, yCurve });
    }
    return profile;
}