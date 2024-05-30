#pragma once

#include <vector>
#include "Platform.h"
#include "Profile.h"
#include "Statistic.h"

std::vector<Platform> splitCurve(const Curve& curve, const int numberOfSegments);
void rotateCurve(std::vector<Platform>& platformCurve, const double angle);
void moveCurve(std::vector<Platform>& curve, const Point& chordBegin);

Eigen::VectorXd solveNoFlowCondition(const std::vector<Platform>& platformCurve, const Environment& env, bool isMiddleLine);
GeneralVariables proceedMdv(std::vector<Platform>& platformCurve, const Environment& env, bool isMiddleLine);

StatisticManager getFullAirflow(
    std::vector<Platform>& platformCurve,
    const Environment& env,
    const double angleShift,
    const double minAngle,
    const double maxAngle,
    Profile &profile,
    bool isMiddleLine);
