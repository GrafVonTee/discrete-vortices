#define _USE_MATH_DEFINES

#include "ProfileGenerator.h"
#include <cmath>
#include <complex>

Profile ProfileGenerator::generateProfile(segment_number_type numberOfSegments) {
    Profile profile(m_x0, m_y0, numberOfSegments);

    Point vectorToX1 { 1 - m_x0, -m_y0};

    value_type dotProduct = vectorToX1.x;
    value_type determinant = sqrtl(powl(vectorToX1.x, 2) + powl(vectorToX1.y, 2));
    value_type startAngle = acosl(dotProduct / determinant);

    value_type upperThetaShift = (M_PI + startAngle * 2) / numberOfSegments * 2;
    value_type bottomThetaShift = (M_PI - startAngle * 2) / numberOfSegments * 2;
    value_type currentTheta = -startAngle;

    value_type arm = sqrtl(powl(1 - m_x0, 2) + powl(m_y0, 2));

    for (int i = 0; i < numberOfSegments; ++i) {
        value_type x1 = arm * cosl(currentTheta) + m_x0;
        value_type y1 = arm * sinl(currentTheta) + m_y0;

        std::complex<value_type> zCircle(x1, y1);
        std::complex<value_type> zCurve(std::complex<value_type>(1.0/2, 0) * (zCircle + std::complex<value_type>(1.0, 0) / zCircle));

        profile.emplaceIntoCurve(Point { zCurve.real(), zCurve.imag() });
        
        currentTheta -= (i <= numberOfSegments / 2) ? bottomThetaShift : upperThetaShift;
    }
    return profile;
}