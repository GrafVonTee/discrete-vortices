#pragma once

#include <vector>
#include "Platform.h"
#include "Profile.h"
#include "Statistic.h"

std::vector<Platform> splitCurve(const Curve& curve, const int numberOfSegments);
Eigen::VectorXd solveNoFlowCondition(const std::vector<Platform>& platformCurve, const Environment& env);
GeneralVariables proceedMdv(std::vector<Platform>& platformCurve, const Environment& env);

void rotateCurve(std::vector<Platform>& platformCurve, const double angle);

StatisticManager getFullAirflow(
    std::vector<Platform>& platformCurve,
    const Environment& env,
    const double angleShift,
    const double minAngle,
    const double maxAngle,
    const double chordLength);
