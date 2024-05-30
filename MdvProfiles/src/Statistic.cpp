#include <cmath>
#include "Statistic.h"

void StatisticManager::checkAngles(const Statistic& stat) {
    if (m_vector.size() > 2) {
        if (((stat.genVars.lift > 0) && (m_vector[m_vector.size() - 2].genVars.lift < 0))
        && (m_zeroLiftAngle == -5)) {
            m_zeroLiftAngle = stat.angle;
        }

        if ((stat.genVars.lift < m_vector[m_vector.size() - 2].genVars.lift)
        && (m_criticalAngle == -5)
        && (stat.angle >= m_zeroLiftAngle)
        && (m_zeroLiftAngle != -5)) {
            m_criticalAngle = stat.angle;
        }

        double da = stat.angle - m_vector[m_vector.size() - 2].angle;
        double dcY = (stat.cY - m_vector[m_vector.size() - 2].cY) / da;
        double dmZ = (stat.mZ - m_vector[m_vector.size() - 2].mZ) / da;
        double ddcY = (dcY - (m_vector[m_vector.size() - 2].cY - m_vector[m_vector.size() - 3].cY) / da) / da;

        if (!b_derivativeFound) {            
            if ((m_zeroLiftAngle != -5)
                && (ddcY < 0)
                && (dcY > 0)) {
                b_derivativeFound = true;
            }
            m_dcY = dcY;
            m_dmZ = dmZ;
        }
    }
}

void StatisticManager::pushBack(const Statistic& stat) {
    m_vector.push_back(stat);
    checkAngles(stat);
}