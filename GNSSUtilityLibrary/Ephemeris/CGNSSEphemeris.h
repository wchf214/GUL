/**@file           CGNSSEphemeris
 *  @brief         星历类
 *  @details       所有星历相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _GNSS_EPHEMERIS_H
#define _GNSS_EPHEMERIS_H

#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        class CGNSSEphemeris
        {
        public:
            explicit CGNSSEphemeris(const SEphemeris& ephObj);
            explicit CGNSSEphemeris(const SGlonassEphemeris& ephObj);
            CGNSSEphemeris(const CGNSSEphemeris& ephObj);
            ~CGNSSEphemeris();

            SEphemeris GetEph();
            SGlonassEphemeris GetGloEph();

            // Clock and Position except Glonass
            int CalcEphSatClock(const SEpochSatObs& obsObj, const SEphemeris& ephObj, double& clockVal);
            int CalcEphSatPos(const SEpochSatObs& obsObj, const SEphemeris& ephObj, SXYZ& coord);

            // Glonass Clock and Position
            int CalcGloEphSatClock(const SEpochSatObs& obsObj, const SGlonassEphemeris& ephObj, double& clockVal);
            int CalcGloEphSatPos(const SEpochSatObs& obsObj, const SGlonassEphemeris& ephObj, SXYZ& coord);
        private:
            SEphemeris m_ephObj;
            SGlonassEphemeris m_gloEphObj;
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents
#endif