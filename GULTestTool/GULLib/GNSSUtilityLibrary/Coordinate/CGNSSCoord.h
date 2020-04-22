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

#include "../DllMain/GNSSDataStruct.h"
#include "../DllMain/GNSSCommonDef.h"
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
            CGNSSCoord(const double x, const double y, const double z, const int coordType);
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
            int XYZ2BLH(const double x, const double y, const double z,
                double& lon, double& lat, double& height, int i);
            int BLH2XYZ(const double lon, const double lat, const double height,
                double& x, double& y, double& z, int i);
            // transform between XYZ and ENU
            int XYZ2ENU(const double origin_X, const double origin_Y, const double origin_Z,
                const double target_B, const double target_L, const double target_H,
                double& target_East, double& target_North, double& target_Up);

            int ENU2XYZ(const double origin_B, const double origin_L, const double origin_H,
                const double target_East, const double target_North, double target_Up,
                double& target_X, double& target_Y, double& target_Z);

            void xyz2enu(const double *pos, double *E);

        private:
            SXYZ m_spaceCoord;
            SBLH m_geoCoord;
            SENU m_stationCoord;

            std::map<int, SCoordData> m_CoordData;
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents
#endif
