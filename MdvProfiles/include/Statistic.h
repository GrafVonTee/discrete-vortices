#pragma once

#include "GeneralVariables.h"
#include <vector>

struct Statistic {
    GeneralVariables genVars;
    double angle;
    double cY;
    double mZ;
};

class StatisticManager {
    std::vector<Statistic> m_vector;
    double m_zeroLiftAngle = -5; // just a magic number
    double m_criticalAngle = -5;
    double m_dcY = -100;
    double m_dmZ = -100;
    double b_derivativeFound = false;

    void checkAngles(const Statistic& stat);
public:
    void pushBack(const Statistic& stat);

    double getZeroLiftAngle() const { return m_zeroLiftAngle; };
    double getCriticalAngle() const { return m_criticalAngle; };
    double getDerivativeCy() const { return m_dcY; }
    double getDerivativeMz() const { return m_dmZ; }
    std::vector<Statistic> getStatistics() const { return m_vector; }
};