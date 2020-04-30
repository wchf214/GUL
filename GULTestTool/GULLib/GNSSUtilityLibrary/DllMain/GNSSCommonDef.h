/** @file          GNSSCommonDef.h
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

#include <string>
#include "GNSSDataStruct.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (P)
#endif // !UNREFERENCED_PARAMETER

        // 枚举值定义
        // 时间类型定义
        enum TIME_TYPE
        {
            NONE = 0, // 不支持的时间类型
            UTC = 1,  // UTC
            GPS,      // GPS
            GLONASS,  // 格洛纳斯
            GALILEO,  // 伽利略
            BDS       // 北斗
        };

        // 坐标系统类型定义
        enum COORDINATE_SYS_TYPE
        {
            WGS84 = 1, // GPS坐标系
            PZ90,      // 格洛纳斯坐标系
            ITRF96,    // 伽利略坐标系
            CGCS2000   // 北斗坐标系
        };

        // 坐标类型
        enum COORDINATE_TYPE
        {
            XYZ = 1, // 空间直角坐标系
            BLH,     // 大地坐标
            ENU      // 站心坐标
        };

        // 错误码定义
        static const INT32 RETURN_SUCCESS = 0;           // 成功
        static const INT32 RETURN_FAIL = -1;             // 失败
        static const INT32 RETURN_NEW_PTR_FAILED = -2;   // new指针失败
        static const INT32 RETURN_TIME_TYPE_ERROR = -3;  // 时间类型错误
        static const INT32 RETURN_PTR_LENGTH_ERROR = -4; // 指针长度不正确
        static const INT32 RETURN_NULL_PTR = -5;

        // 常量定义
        // For Accuracy
        const int COORDINATE_ACCURACY = 9; // 空间直角坐标，以及大地坐标中高程的精确度
        const int BLH_ACCURACY = 11;       // 大地坐标中经纬度的精确度
        const int MSEC_ACCURACY = 3;       // 秒的精确度(精确到毫秒)
        const int MATRIX_ACCURACY = 6; // 矩阵中double数据的精确度(角分秒格式中的秒，精确度也是6)
        const int DEGREE_ACCURACY = 9; // 小数度的精确度(小数后9位)
        const double LAT_ACCURACY = 1.0e-08; // 计算大地纬度B时的精度
        // For Time
        const std::string DAY_INTERVAL = "-";      /* 日期间隔符 */
        const std::string TIME_INTERVAL = ":";     /* 时间间隔符 */
        const std::string WEEK_SEC_INTERVAL = ","; /* 周内秒间隔符 */

        const INT32 DAY_OF_YEAR[12] = {
            1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}; /* 一年中，当前月距1月1号的天数*/
        const int
            DAY_IN_EACH_MON[48] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28, 31, 30, 31,
                                   30, 31, 31, 30, 31, 30, 31, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31,
                                   30, 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; /* # of days in a month */
        const static SStandardTime EPOCHT0 = {1970, 1, 1, 0, 0, 0, 0};
        const static DOUBLE GPST0[] = {1980, 1, 6, 0, 0, 0}; /* gps time reference */
        const static DOUBLE GST0[] = {1999, 8, 22, 0, 0, 0}; /* galileo system time reference */
        const static DOUBLE BDT0[] = {2006, 1, 1, 0, 0, 0};  /* beidou time reference */

        const UINT64 EPOCH_TO_GPST0 = 315964800; // GPS
        const UINT64 EPOCH_TO_GALT0 = 935280000; // Galileo
        const UINT64 EPOCH_TO_BDT0 = 1136073600; // BDS

        const INT32 BASE_60 = 60;                        // 60 进制, ，时间进制
        const INT32 SEC_IN_DAY = 24 * 60 * 60;           // 一天内的秒数 86400
        const INT32 DAY_IN_WEEK = 7;                     // 一周内的天数
        const INT32 WEEK_SEC = DAY_IN_WEEK * SEC_IN_DAY; // 一周内的秒数 604800

        const INT32 MONTH_IN_YEAR = 12;      // 一年内的月数
        const INT32 DAY_IN_YEAR = 365;       // 一年内的天数
        const INT32 DAY_IN_4YEAR = 1461;     // 四年(含一个闰年)的总天数
        const INT32 MONTH_IN_4YRAR = 48;     // 四年(含一个闰年)的总月数
        const INT32 CURRENT_MAX_YEAR = 2099; // 当前支持的最大天数
        const INT32 LEAP_YEAR_INTERVAL = 4;  // 闰年间隔
        // For Time Leap 跳秒值
        const INT32 WEEK_BETWEEN_GPS_GAL = 1024;          // GPS 与 Galileo 相差1024周
        const INT32 GPSWEEK_TO_BDSWEEK = 1356;            // GPS 与 BDS 相差1356周
        const INT32 THREE_HOUR = 3;                       // Glonass 与 UTC 之间的跳秒值
        const INT32 SEC_OF_3HOUR = 3 * BASE_60 * BASE_60; // 3小时对应的秒数
        const INT32 SEC_BETWEEN_GPS_BDS = 14;             // GPS 与 BDS 相差14s
        /* leap seconds (y,month,d,h,min,s,utc-gpst) */
        const static DOUBLE GPS_LEAPSEC_INFO[65][7] = {{2017, 1, 1, 0, 0, 0, -18}, {2015, 7, 1, 0, 0, 0, -17},
                                                       {2012, 7, 1, 0, 0, 0, -16}, {2009, 1, 1, 0, 0, 0, -15},
                                                       {2006, 1, 1, 0, 0, 0, -14}, {1999, 1, 1, 0, 0, 0, -13},
                                                       {1997, 7, 1, 0, 0, 0, -12}, {1996, 1, 1, 0, 0, 0, -11},
                                                       {1994, 7, 1, 0, 0, 0, -10}, {1993, 7, 1, 0, 0, 0, -9},
                                                       {1992, 7, 1, 0, 0, 0, -8},  {1991, 1, 1, 0, 0, 0, -7},
                                                       {1990, 1, 1, 0, 0, 0, -6},  {1988, 1, 1, 0, 0, 0, -5},
                                                       {1985, 7, 1, 0, 0, 0, -4},  {1983, 7, 1, 0, 0, 0, -3},
                                                       {1982, 7, 1, 0, 0, 0, -2},  {1981, 7, 1, 0, 0, 0, -1},
                                                       {1980, 1, 6, 0, 0, 0, 0},   {0}};

        /* leap seconds (y,m,d,h,m,s,utc-gpst) */
        const static DOUBLE BDS_LEAPSEC_INFO[65][7] = {{2017, 1, 1, 0, 0, 0, -4},
                                                       {2015, 7, 1, 0, 0, 0, -3},
                                                       {2012, 7, 1, 0, 0, 0, -2},
                                                       {2009, 1, 1, 0, 0, 0, -1},
                                                       {2006, 1, 1, 0, 0, 0, 0},
                                                       {0}};

        // For Angle
        const static INT32 ANGLE_LENGTH = 11;
        const static DOUBLE PI = 3.1415926535897932;     /* pi */
        const static DOUBLE D2R = (PI / 180.0);          /* deg to rad */
        const static DOUBLE R2D = (180.0 / PI);          /* rad to deg */
        const static DOUBLE SIN_5 = -0.0871557427476582; /* sin(-5.0 deg) */
        const static DOUBLE COS_5 = 0.9961946980917456;  /* cos(-5.0 deg) */
        const INT32 DEG_TO_SEC = 3600;                   /* 角度转秒 */

        const static DOUBLE J2_GLO = 1.0826257E-3; /* 2nd zonal harmonic of geopot   ref [2] */
        const static INT32 MAX_ITER_KEPLER = 30;   /* max number of iteration of Kelpler */
        const static DOUBLE RTOL_KEPLER = 1E-14;   /* relative tolerance for Kepler equation */
        const static DOUBLE RE_GLO = 6378136.0;    /* radius of earth (m)            ref [2] */

        const static DOUBLE GPS_GRAVITATION = 3.9860050E14;   /* gravitational constant         ref [1] */
        const static DOUBLE GLO_GRAVITATION = 3.9860044E14;   /* gravitational constant         ref [2] */
        const static DOUBLE GAL_GRAVITATION = 3.986004418E14; /* earth gravitational constant   ref [7] */
        const static DOUBLE BDS_GRAVITATION = 3.986004418E14; /* earth gravitational constant   ref [9] */

        const static DOUBLE GPS_ANGULAR_VELOCITY = 7.2921151467E-5; /* earth angular velocity (IS-GPS) (rad/s) */
        const static DOUBLE GLO_ANGULAR_VELOCITY = 7.292115E-5;     /* earth angular velocity (rad/s) ref [2] */
        const static DOUBLE GAL_ANGULAR_VELOCITY = 7.2921151467E-5; /* earth angular velocity (rad/s) ref [7] */
        const static DOUBLE BDS_ANGULAR_VELOCITY = 7.292115E-5;     /* earth angular velocity (rad/s) ref [9] */
        const static DOUBLE DOUBLE_ZONE_LITTLE = -1E9;
        const static DOUBLE DOUBLE_ZONE_BIG = 1E9;

        const INT32 NUM_ONE = 1;
        const INT32 NUM_SIX = 6;
        const INT32 FIFTEEN_MIN_TO_SEC = 15;

        const DOUBLE EARTH_OBLATEO_CGCS = 1 / 298.257222101;  // cgcs2000 扁率
        const DOUBLE EARTH_OBLATEO_WGS84 = 1 / 298.257223563; // WGS84、itrf96 扁率
        const DOUBLE EARTH_OBLATEO_PZ90 = 1 / 298.257839303;  // PZ90 扁率

        const DOUBLE EARTH_LONG_RADIUS = 6378137.0; // 除pz90外的长半轴 /* earth semimajor axis (WGS84) (m) */
        const DOUBLE EARTH_LONG_RADIUS_PZ90 = 6378136.0; // pz90的 长半轴
        const DOUBLE EARTH_SHORT_RADIUS = EARTH_LONG_RADIUS - EARTH_OBLATEO_WGS84 * EARTH_LONG_RADIUS; //短半径
        const DOUBLE E2 = (EARTH_LONG_RADIUS * EARTH_LONG_RADIUS - EARTH_SHORT_RADIUS * EARTH_SHORT_RADIUS)
                          / (EARTH_LONG_RADIUS * EARTH_LONG_RADIUS); // e为第一偏心率
        const SCoordData WGS84_DATA = {EARTH_LONG_RADIUS, EARTH_OBLATEO_WGS84};
        const SCoordData PZ90_DATA = {EARTH_LONG_RADIUS_PZ90, EARTH_OBLATEO_PZ90};
        const SCoordData ITRF96_DATA = {EARTH_LONG_RADIUS, EARTH_OBLATEO_WGS84};
        const SCoordData CGCS2000_DATA = {EARTH_LONG_RADIUS, EARTH_OBLATEO_CGCS};
    } // end namespace GNSSUtilityLib
} // end namespace sixents

#endif // !_GNSS_COMMON_DEF_H