#pragma once

#include <Eigen/Dense>
#include "Point.h"
#include "Environment.h"

class Platform {
    Point m_begin, m_end;
    Point m_deriv;
    Eigen::Vector2d m_normal;

    value_type m_circulation;
    value_type m_lift;
    value_type m_pitchMoment;
    value_type m_pressure;

public:
    Platform() = default;
    Platform(const Point& begin, const Point& end);

    Point getPointOnLine(const value_type x) const;
    Eigen::Vector2d getNormalVector() const { return m_normal; }

    std::vector<Point> getLine() const;
    
    void setCirculation(const value_type circulation, const Environment& env);
    value_type getCirculation() const { return m_circulation; }
    value_type getLift() const { return m_lift; }
    value_type getPitchMoment() const { return m_pitchMoment; }
    value_type getPressure() const { return m_pressure; }
    value_type getLength() const;
    
    Point getVortexPoint(const value_type position = 1.0/4.0) const;
    Point getControlPoint(const value_type position = 3.0/4.0) const;
    Point getMiddlePoint() const;

    void rotate(const value_type angle);
    void move(const Point& toStart);
};