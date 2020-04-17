#include "CGNSSEphemeris.h"

#include <ctime>

namespace sixents
{
    namespace GNSSUtilityLib
    {
        int CGNSSEphemeris::CalcEphSatClock(const SEpochSatObs& obsObj, const SEphemeris& ephObj, double& clockVal)
        {
            do
            {
                double t = obsObj.m_ui32GnssEpochTime - ephObj.m_ui32Toc;
                for (int i = 0; i < 2; i++)
                {
                    t -= ephObj.m_dbAf0 + ephObj.m_dbAf1 * t + ephObj.m_dbAf2 * t * t;
                }
                clockVal = ephObj.m_dbAf0 + ephObj.m_dbAf0 * t + ephObj.m_dbAf0 * t * t;
            } while (false);
            return 1;
        }

        int CGNSSEphemeris::CalcEphSatPos(const SEpochSatObs& obsObj, const SEphemeris& ephObj, SXYZ& coord)
        {
            return 1;
        }

        // Glonass Clock and Position
        int CGNSSEphemeris::CalcGloEphSatClock(const SEpochSatObs& obsObj, const SGlonassEphemeris& ephObj, double& clockVal)
        {
            ////double t = obsObj.m_ui32GnssEpochTime -

            //    for (int i = 0; i < 2; i++)
            //    {
            //        t -= -ephObj.m_dbTnTb + ephObj.m_dbGammaTb * t;
            //    }
            //return -ephObj.m_dbTnTb + ephObj.m_dbGammaTb * t;
            return 1;
        }
        int CGNSSEphemeris::CalcGloEphSatPos(const SEpochSatObs& obsObj, const SGlonassEphemeris& ephObj, SXYZ& coord)
        {
            return 1;
        }
    }
}