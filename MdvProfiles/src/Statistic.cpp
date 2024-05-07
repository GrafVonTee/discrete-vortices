#include <cmath>
#include "Statistic.h"

void StatisticManager::checkAngles(const Statistic& stat) {
    if (m_vector.size() > 1) {
        if ((stat.genVars.lift * m_vector[m_vector.size() - 2].genVars.lift < 0)
        && (m_zeroLiftAngle == -5)) {
            m_zeroLiftAngle = stat.angle;
        }

        if ((stat.genVars.lift < m_vector[m_vector.size() - 2].genVars.lift)
        && (m_criticalAngle == -5)
        && (stat.angle >= m_zeroLiftAngle)) {
            m_criticalAngle = stat.angle;
        }

        double da = stat.angle - m_vector[m_vector.size() - 2].angle;
        double dcY = (stat.cY - m_vector[m_vector.size() - 2].cY) / da;
        double dmZ = (stat.mZ - m_vector[m_vector.size() - 2].mZ) / da;

        if (!b_derivativeFound) {            
            if ((fabs(dcY - m_dcY) < 1e-5)
             && (fabs(dmZ - m_dmZ) < 1e-5)) {
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