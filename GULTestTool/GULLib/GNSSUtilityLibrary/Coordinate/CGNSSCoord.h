/**@file           CGNSSCoord
 *  @brief         坐标类
 *  @details       所有坐标相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _GNSS_COORDINATE_H
#define _GNSS_COORDINATE_H
#include <map>
#include "../DllMain/GNSSCommonDef.h"
#include "../DllMain/GNSSDataStruct.h"
namespace sixents
{
    namespace GNSSUtilityLib
    {
        class CGNSSCoord
        {
        public:
            // coordType is 1, xyz set to m_spaceCoord, and change value set to m_geoCoord
            // coordType is 2, xyz set to m_geoCoord, and change value set to m_spaceCoord
            // coordType is 3, xyz set to m_stationCoord
            CGNSSCoord(const DOUBLE x, const DOUBLE y, const DOUBLE z, const INT32 coordType);
            CGNSSCoord(const CGNSSCoord& coord);
            ~CGNSSCoord();

            void SetCoordData();

            void SetXYZ(const SXYZ& coord);
            SXYZ GetXYZ();

            void SetBLH(const SBLH& coord);
            SBLH GetBLH();

            void SetENU(const SENU& coord);
            SENU GetENU();
            // transfrom between XYZ and BLH, 处理内部成员变量
            INT32
            XYZ2BLH(const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lon, DOUBLE& lat, DOUBLE& height, INT32 i);
            INT32
            BLH2XYZ(const DOUBLE lon, const DOUBLE lat, const DOUBLE height, DOUBLE& x, DOUBLE& y, DOUBLE& z, INT32 i);
            // transform between XYZ and ENU
            INT32 XYZ2ENU(const DOUBLE origin_X,
                          const DOUBLE origin_Y,
                          const DOUBLE origin_Z,
                          const DOUBLE target_B,
                          const DOUBLE target_L,
                          const DOUBLE target_H,
                          DOUBLE& target_East,
                          DOUBLE& target_North,
                          DOUBLE& target_Up);

            INT32 ENU2XYZ(const DOUBLE origin_B,
                          const DOUBLE origin_L,
                          const double origin_H,
                          const DOUBLE target_East,
                          const DOUBLE target_North,
                          DOUBLE target_Up,
                          DOUBLE& target_X,
                          DOUBLE& target_Y,
                          DOUBLE& target_Z);

            void xyz2enu(const DOUBLE* pos, DOUBLE* E);

        private:
            SXYZ m_spaceCoord;
            SBLH m_geoCoord;
            SENU m_stationCoord;

            std::map<INT32, SCoordData> m_CoordData;
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents
#endif
