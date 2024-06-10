#pragma once

#include <vector>
#include "Platform.h"
#include "Profile.h"
#include "Statistic.h"

std::vector<Platform> splitCurve(const Curve& curve, const int numberOfSegments);
void rotateCurve(std::vector<Platform>& platformCurve, const double angle);
void moveCurve(std::vector<Platform>& curve, const Point& chordBegin);

Eigen::VectorXd solveNoFlowCondition(const std::vector<Platform>& platformCurve, const Environment& env);
GeneralVariables proceedMdv(std::vector<Platform>& platformCurve, const Environment& env);

Eigen::VectorXd solveNoFlowConditionVor2dc(const std::vector<Platform>& platformCurve, const Environment& env);
GeneralVariables proceedVor2dc(std::vector<Platform>& platformCurve, const Environment& env);

StatisticManager getFullAirflow(
    std::vector<Platform>& platformCurve,
    const Environment& env,
    const double angleShift,
    const double minAngle,
    const double maxAngle,
    Profile &profile,
    bool isMiddleLine);
