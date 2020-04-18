/**@file           CGNSSCoord
 *  @brief         坐标类
 *  @details       所有坐标相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _GNSS_COMMON_DEF_H
#define _GNSS_COMMON_DEF_H

namespace sixents
{
    namespace GNSSUtilityLib
    {
        // 枚举值定义
        enum SAT_SYS_TYPE
        {
            GPS = 1,  // GPS
            GLONASS,  // 格洛纳斯
            GALILEO,  // 伽利略
            BDS       // 北斗
        };

        enum COORDINATE_SYS_TYPE
        {
            WGS84 = 1, // GPS坐标系
            PZ90,      // 格洛纳斯坐标系
            ITRF96,    // 伽利略坐标系
            CGCS2000   // 北斗坐标系
        };

        enum COORDINATE_TYPE
        {
            XYZ = 1,  // 空间直角坐标系
            BLH,      // 大地坐标
            ENU       // 站心坐标
        };
        // 错误码定义

        // 常量定义
        const static double gpst0[] = { 1980,1, 6,0,0,0 }; /* gps time reference */
        const static double gst0[] = { 1999,8,22,0,0,0 };  /* galileo system time reference */
        const static double bdt0[] = { 2006,1, 1,0,0,0 };  /* beidou time reference */
        const static double PI = 3.1415926535897932;  /* pi */
        const static double D2R = (PI / 180.0);          /* deg to rad */
        const static double R2D = (180.0 / PI);          /* rad to deg */

    } // end namespace GNSSUtilityLib
} // end namespace sixents

#endif