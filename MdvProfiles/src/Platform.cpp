#include "Platform.h"

Platform::Platform(const Point& begin, const Point& end) {
    m_begin = begin;
    m_end = end;
    m_deriv = Point { m_end.x - m_begin.x, m_end.y - m_begin.y };
    m_normal << -m_deriv.y, m_deriv.x; // normal vector outside the profile
}

Point Platform::getPointOnLine(const value_type x) const {
    return Point { x, (x - m_begin.x) * (m_end.y - m_begin.y) / (m_end.x - m_begin.x) };
}

void Platform::setCirculation(const value_type circulation, const Environment& env) {
    m_circulation = circulation;
    m_lift = -env.fluidDensity * env.fluidSpeed * circulation;
    m_pitchMoment = m_lift * getVortexPoint().x;
}

Point Platform::getVortexPoint(const value_type position) const {
    if ((position < 0) || (position > 1)) {
        return Point { 0, 0 };
    }

    value_type positionOnX = m_deriv.x * position + m_begin.x;
    return Point { positionOnX, getPointOnLine(positionOnX).y };
}

Point Platform::getControlPoint(const value_type position) const {
    if ((position < 0) || (position > 1)) {
        return Point { 0, 0 };
    }

    value_type positionOnX = m_deriv.x * position + m_begin.x;
    return Point { positionOnX, getPointOnLine(positionOnX).y };
}

void Platform::rotate(const value_type angle) {
    using Eigen::Vector2d;
    using Eigen::Matrix2d;

    Vector2d vecBegin(m_begin.x, m_begin.y), vecEnd(m_end.x, m_end.y);
    Matrix2d rotationMatrix {
        {cos(angle), -sin(angle)},
        {sin(angle), cos(angle)}
    };
    
    vecBegin = rotationMatrix * vecBegin;
    vecEnd = rotationMatrix * vecEnd;
    m_normal = rotationMatrix * m_normal;

    m_begin = Point { vecBegin(0), vecBegin(1) };
    m_end = Point { vecEnd(0), vecEnd(1) };
    m_deriv = Point { m_end.x - m_begin.x, m_end.y - m_begin.y };
}

value_type Platform::getLength() const {
    return sqrtl(powl(m_deriv.x, 2) + powl(m_deriv.y, 2));
}