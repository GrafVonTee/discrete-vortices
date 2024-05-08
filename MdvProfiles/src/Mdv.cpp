#include <cmath>
#include "Mdv.h"

using Eigen::Vector2d;
using Eigen::VectorXd;
using Eigen::Matrix2d;
using Eigen::MatrixXd;

std::vector<Platform> splitCurve(const Curve& curve, const int numberOfSegments) {
    if (numberOfSegments <= 0) {
        return std::vector<Platform>();
    }

    std::vector<Platform> platformCurve(numberOfSegments);
    value_type indexShift = curve.size() * 1.0 / numberOfSegments;
    value_type currentFloatIndex = 0;
    for (int i = 0; i < numberOfSegments - 1; ++i) {
        Point begin(curve[(int) currentFloatIndex]), end(curve[(int)(currentFloatIndex + indexShift)]);
        platformCurve[i] = Platform(begin, end);
        currentFloatIndex += indexShift;
    }
    platformCurve[numberOfSegments - 1] = Platform(curve[(int) currentFloatIndex], curve[curve.size() - 1]);
    return platformCurve;
}

VectorXd solveNoFlowCondition(const std::vector<Platform>& platformCurve, const Environment& env) {
    int N = platformCurve.size();
    MatrixXd wMatrix(N, N);
    VectorXd bVector(N);

    for (int k = 0; k < N; ++k) {
        Vector2d normal = platformCurve[k].getNormalVector();
        double xCos = normal.dot(Vector2d(1, 0)) / normal.norm();
        double yCos = normal.dot(Vector2d(0, 1)) / normal.norm();

        Point control = platformCurve[k].getControlPoint();

        bVector(k) = -env.fluidSpeed * xCos;

        for (int i = 0; i < N; ++i) {
            Point vortex = platformCurve[i].getVortexPoint();

            double xV = (1.0 / 2.0 / M_PI)
                * (control.y - vortex.y)
                / (pow(control.x - vortex.x, 2) + pow(control.y - vortex.y, 2));
            double yV = (1.0 / 2.0 / M_PI)
                * (control.x - vortex.x)
                / (pow(control.x - vortex.x, 2) + pow(control.y - vortex.y, 2));

            wMatrix(k, i) = xV * xCos + yV * yCos;
        }
    }

    return wMatrix.completeOrthogonalDecomposition().solve(bVector);
}

GeneralVariables proceedMdv(std::vector<Platform>& platformCurve, const Environment& env) {
    VectorXd solution = solveNoFlowCondition(platformCurve, env);
    GeneralVariables genVars { 0, 0, 0 };
    for (int i = 0; i < platformCurve.size(); ++i) {
        platformCurve[i].setCirculation(solution(i), env);

        genVars.circulation += platformCurve[i].getCirculation();
        genVars.lift += platformCurve[i].getLift();
        genVars.pitchMoment += platformCurve[i].getPitchMoment();
    }
    return genVars;
}

void rotateCurve(std::vector<Platform>& platformCurve, const double angle) {
    for (auto& platform: platformCurve) {
        platform.rotate(angle);
    }
}

StatisticManager getFullAirflow(
    std::vector<Platform>& platformCurve,
    const Environment& env,
    const double angleShift,
    const double minAngle,
    const double maxAngle,
    const double chordLength) {

    StatisticManager manager;
    for (double curAngle = minAngle; curAngle <= maxAngle; curAngle += angleShift) {
        Statistic stat;
        stat.angle = curAngle;
        
        rotateCurve(platformCurve, curAngle);
        stat.genVars = proceedMdv(platformCurve, env);
        stat.cY = stat.genVars.lift
            / env.fluidDensity
            / pow(env.fluidSpeed, 2) * 2;
        stat.mZ = stat.genVars.pitchMoment
            / env.fluidDensity
            / pow(env.fluidSpeed, 2) * 2
            / chordLength;

        manager.pushBack(stat);
        rotateCurve(platformCurve, -curAngle);
    }

    return manager;
}