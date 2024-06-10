#include <cmath>
#include <string>
#include <sstream>
#include "Mdv.h"
#include "Printing.h"

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

void moveCurve(std::vector<Platform>& curve, const Point& chordBegin) {
    for (auto& platform: curve) {
        platform.move(chordBegin);
    }
}

VectorXd solveNoFlowCondition(const std::vector<Platform>& platformCurve, const Environment& env) {
    int N = platformCurve.size();

    MatrixXd wMatrix(N, N);
    VectorXd bVector(N);
    Vector2d qSpeed { cos(env.attackAngle) * env.fluidSpeed, sin(env.attackAngle) * env.fluidSpeed };

    for (int k = 0; k < N; ++k) {
        Vector2d normal = platformCurve[k].getNormalVector();
        Point control = platformCurve[k].getControlPoint();

        bVector(k) = -qSpeed.dot(normal);

        for (int i = 0; i < N; ++i) {
            Point vortex = platformCurve[i].getVortexPoint();
            double radiusVector = pow(control.x - vortex.x, 2) + pow(control.y - vortex.y, 2);
            double coeff = (1.0 / 2.0 / M_PI / radiusVector);
            Eigen::Matrix<double, 2, 2> lumpedMatrix { {0, 1}, {-1, 0} };
            Vector2d diffVec { (control.x - vortex.x), (control.y - vortex.y) };

            Vector2d uwVector = coeff * lumpedMatrix * diffVec;

            wMatrix(k, i) = uwVector.dot(normal);
        }
    }

    return wMatrix.colPivHouseholderQr().solve(bVector);
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

Eigen::VectorXd solveNoFlowConditionVor2dc(const std::vector<Platform>& platformCurve, const Environment& env) {
    int N = platformCurve.size();

    MatrixXd wMatrix(N, N);
    VectorXd bVector(N);
    Vector2d qSpeed { cos(env.attackAngle) * env.fluidSpeed, sin(env.attackAngle) * env.fluidSpeed };

    for (int k = 0; k < N-1; ++k) {
        Vector2d normal = platformCurve[k].getNormalVector();
        Vector2d tangential = platformCurve[k].getTangentialVector();
        Point control = platformCurve[k].getMiddlePoint();

        bVector(k) = -qSpeed.dot(tangential);

        for (int i = 0; i < N; ++i) {
            Point begin, end;
            begin = platformCurve[i].getBeginPoint();
            end = platformCurve[i].getEndPoint();

            double up = (1.0 / 2.0 / M_PI) * (
                atan((control.y - end.y) / (control.x - end.x))
                - atan((control.y - begin.y) / (control.x - begin.x))
            );
            double wp = -1 * (1.0 / 4.0 / M_PI) * log(
                (pow(control.x - begin.x, 2) + pow(control.y - begin.y, 2))
                / (pow(control.x - end.x, 2) + pow(control.y - end.y, 2))
            );

            Vector2d uwp;
            if (i == k) {
                uwp << -0.5, 0;
            } else {
                uwp << up, wp;
            }

            Matrix2d toGlobal {
                {normal(1), normal(0)},
                {-normal(0), normal(1)}
            };

            Vector2d uwVector = toGlobal * uwp;

            wMatrix(k, i) = uwVector.dot(tangential);
        }
    }
    bVector(N-1) = 0;
    for (int i = 0; i < N; ++i) {
        wMatrix(N-1, i) = 0;
    }
    wMatrix(N-1, 0) = 1;
    wMatrix(N-1, N-1) = 1;

    // std::cout << wMatrix << std::endl << std::endl; 
    // char i;
    // std::cin >> i;

    return wMatrix.colPivHouseholderQr().solve(bVector);
}

GeneralVariables proceedVor2dc(std::vector<Platform>& platformCurve, const Environment& env) {
    VectorXd solution = solveNoFlowConditionVor2dc(platformCurve, env);
    GeneralVariables genVars { 0, 0, 0 };
    for (int i = 0; i < platformCurve.size(); ++i) {
        platformCurve[i].setCirculation(solution(i) * platformCurve[i].getLength(), env);

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

StatisticManager getFullAirflow(std::vector<Platform>& platformCurve,
                                const Environment& env,
                                const double angleShift,
                                const double minAngle,
                                const double maxAngle,
                                Profile &profile,
                                bool isMiddleLine) {

    StatisticManager manager;
    for (double curAngle = minAngle; curAngle <= maxAngle; curAngle += angleShift) {
        Statistic stat;
        stat.angle = curAngle;

        Environment newEnv = env;
        newEnv.attackAngle = curAngle;

        stat.genVars = (isMiddleLine) ? proceedMdv(platformCurve, newEnv) : proceedVor2dc(platformCurve, newEnv);
        stat.cY = stat.genVars.lift
            / env.fluidDensity
            / pow(newEnv.fluidSpeed, 2) * 2
            / profile.getChordLength();

        stat.mZ = stat.genVars.pitchMoment
            / env.fluidDensity
            / pow(newEnv.fluidSpeed, 2) * 2
            / pow(profile.getChordLength(), 2);

        manager.pushBack(stat);
    }

    return manager;
}