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

        struct SCoordData
        {
            double a;
            double f;
        };

        // 错误码定义
        static const int RETURN_SUCCESS = 0;           // 成功
        static const int RETURN_FAIL = -1;                 //
        //static const int RETURN_PACKAGE_LENGHT_ERROR = -2; // 包长度错误
        //static const int RETURN_CRC_CHECK_FAILED = -3;     // CRC校验失败
        //static const int RETURN_STATION_CORRECT = -4;      // StatioinId校验失败
        //static const int RETURN_PERMISSION_ERROR = -5;     // 权限错误
        //static const int RETURN_UNSUPPORTED_RTCM_MSG = -6; // 暂不支持的协议
        //static const int RETURN_NOT_INITIALIZED = -7;      // 未初始化
        //static const int RETURN_INVALID_PARAMETER = -8;    // 无效参数

        // 常量定义
        // For Angle
        const static int ANGLE_LENGTH = 11;
        const static double GPST0[] = { 1980,1, 6,0,0,0 }; /* gps time reference */
        const static double GST0[] = { 1999,8,22,0,0,0 };  /* galileo system time reference */
        const static double BDT0[] = { 2006,1, 1,0,0,0 };  /* beidou time reference */
        const static double PI = 3.1415926535897932;  /* pi */
        const static double D2R = (PI / 180.0);          /* deg to rad */
        const static double R2D = (180.0 / PI);          /* rad to deg */

        static double leaps[65][7] = { /* leap seconds (y,m,d,h,m,s,utc-gpst) */
{2017,1,1,0,0,0,-18},
{2015,7,1,0,0,0,-17},
{2012,7,1,0,0,0,-16},
{2009,1,1,0,0,0,-15},
{2006,1,1,0,0,0,-14},
{1999,1,1,0,0,0,-13},
{1997,7,1,0,0,0,-12},
{1996,1,1,0,0,0,-11},
{1994,7,1,0,0,0,-10},
{1993,7,1,0,0,0, -9},
{1992,7,1,0,0,0, -8},
{1991,1,1,0,0,0, -7},
{1990,1,1,0,0,0, -6},
{1988,1,1,0,0,0, -5},
{1985,7,1,0,0,0, -4},
{1983,7,1,0,0,0, -3},
{1982,7,1,0,0,0, -2},
{1981,7,1,0,0,0, -1},
{0}
        };

#define SIN_5 -0.0871557427476582 /* sin(-5.0 deg) */
#define COS_5  0.9961946980917456 /* cos(-5.0 deg) */
#define RE_GLO   6378136.0        /* radius of earth (m)            ref [2] */
#define MU_GPS   3.9860050E14     /* gravitational constant         ref [1] */
#define MU_GLO   3.9860044E14     /* gravitational constant         ref [2] */
#define MU_GAL   3.986004418E14   /* earth gravitational constant   ref [7] */
#define MU_CMP   3.986004418E14   /* earth gravitational constant   ref [9] */
#define J2_GLO   1.0826257E-3     /* 2nd zonal harmonic of geopot   ref [2] */
#define OMGE_GLO 7.292115E-5      /* earth angular velocity (rad/s) ref [2] */
#define OMGE_GAL 7.2921151467E-5  /* earth angular velocity (rad/s) ref [7] */
#define OMGE_CMP 7.292115E-5      /* earth angular velocity (rad/s) ref [9] */
#define OMGE        7.2921151467E-5     /* earth angular velocity (IS-GPS) (rad/s) */
#define MAX_ITER_KEPLER 30        /* max number of iteration of Kelpler */
#define RTOL_KEPLER 1E-14         /* relative tolerance for Kepler equation */

#define SQR(x)   ((x)*(x))
#define RE_GLO   6378136.0        /* radius of earth (m)            ref [2] */
#define MU_GPS   3.9860050E14     /* gravitational constant         ref [1] */
#define MU_GLO   3.9860044E14     /* gravitational constant         ref [2] */
#define MU_GAL   3.986004418E14   /* earth gravitational constant   ref [7] */
#define MU_CMP   3.986004418E14   /* earth gravitational constant   ref [9] */
#define J2_GLO   1.0826257E-3     /* 2nd zonal harmonic of geopot   ref [2] */

#define OMGE_GLO 7.292115E-5      /* earth angular velocity (rad/s) ref [2] */
#define OMGE_GAL 7.2921151467E-5  /* earth angular velocity (rad/s) ref [7] */
#define OMGE_CMP 7.292115E-5      /* earth angular velocity (rad/s) ref [9] */

        const time_t EPOCH_TO_GPST0 = 315964800;
        const time_t EPOCH_TO_GALT0 = 935280000;
        const time_t EPOCH_TO_BDT0 = 1136073600;
        const time_t WEEKSEC = 604800;;
    } // end namespace GNSSUtilityLib
} // end namespace sixents

#endif