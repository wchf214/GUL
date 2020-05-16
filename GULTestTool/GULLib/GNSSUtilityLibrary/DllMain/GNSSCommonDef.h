/** @file          GNSSCommonDef.h
 *  @brief         坐标类
 *  @details       所有坐标相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef GNSS_COMMON_DEF_H
#define GNSS_COMMON_DEF_H

#include <string>
#include "GNSSDataStruct.h"

namespace sixents
{
    namespace Math
    {
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (P)
#endif // !UNREFERENCED_PARAMETER

        // 枚举值定义
        /// 时间类型定义
        enum TIME_TYPE
        {
            TIME_TYPE_NONE = 0, ///< 不支持的时间类型
            UTC,      ///< UTC
            GPS,      ///< GPS
            GLONASS,  ///< 格洛纳斯
            GALILEO,  ///< 伽利略
            BDS       ///< 北斗
        };

        /// 坐标系统类型定义
        enum COORDINATE_SYS_TYPE
        {
            WGS84 = 1, ///< GPS坐标系
            PZ90,      ///< 格洛纳斯坐标系
            ITRF96,    ///< 伽利略坐标系
            CGCS2000   ///< 北斗坐标系
        };

        /// 坐标类型
        enum COORDINATE_TYPE
        {
            BLH = 1, ///< 大地坐标
            XYZ,     ///< 空间直角坐标系
            ENU      ///< 站心坐标
        };

        // 月份定义
        enum MONTH_TYPE
        {
            MONTH_TYPE_NONE = 0,          ///<  无效值
            DAY_IN_FEB = 28,              ///< 二月的天数，28天
            FEB_IN_CENTURY = 29,          ///< 闰年的二月天数，29天
            SMALL_MONTH = 30,             ///<  小月，指有30天的月份
            BIG_MONTH = 31                ///<  大月，指有31天的月份
        };

        enum MONTH_NAME
        {
            MONTH_JAN = 1,
            MONTH_FEB,    ///<  二月，需特殊处理
            MONTH_MAR,
            MONTH_APR,
            MONTH_MAY,
            MONTH_JUN,
            MONTH_JUL,
            MONTH_AUG,
            MONTH_SEP,
            MONTH_OCT,
            MONTH_NOV,
            MONTH_DEC
        };

        // 错误码定义
        static const INT32 RETURN_SUCCESS = 0;             ///< 成功
        static const INT32 RETURN_FAIL = -1;               ///< 失败
        static const INT32 RETURN_NULL_PTR = -2;           ///< 返回空指针
        static const INT32 RETURN_NEW_PTR_FAILED = -3;     ///< new指针失败
        static const INT32 RETURN_PTR_LENGTH_ERROR = -4;   ///< 指针长度不正确
        static const INT32 RETURN_TIME_TYPE_ERROR = -5;    ///< 时间类型错误
        static const INT32 RETURN_ERROR_WEEK = -6;         ///< 输入的周数据有误
        static const INT32 RETURN_ERROR_SEC = -7;          ///< 输入的秒数据有误
        static const INT32 RETURN_ERROR_STANDARDTIME = -8; ///< 输入的标准时间数据有误
        static const INT32 RETURN_ERROR_PARAMETER = -9;    ///< 参数错误

        const INT32 NUM_NEGATIVE_ONE = -1;
        const INT32 NUM_ZERO = 0;
        const INT32 NUM_ONE = 1;
        const INT32 NUM_TWO = 2;
        const INT32 NUM_THREE = 3;
        const INT32 NUM_FOUR = 4;
        const INT32 NUM_FIVE = 5;
        const INT32 NUM_SIX = 6;

        // 进制转换
        const INT32 BASE_60 = 60; ///< 60 进制,包含时间进制，角度进制

        // 时间模块常量定义
        const std::string DAY_INTERVAL = "-";      ///< 日期间隔符
        const std::string TIME_INTERVAL = ":";     ///< 时间间隔符、度分秒间隔符
        const std::string WEEK_SEC_INTERVAL = ","; ///< 周内秒间隔符

        const INT32 DAY_OF_YEAR[12] = {
            1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}; ///< 一年中，当前月距1月1号的天数

        const INT32
            DAY_IN_EACH_MON
                [48] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28, 31, 30, 31,
                        30, 31, 31, 30, 31, 30, 31, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31,
                        30, 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; ///< 四年（含一个闰年）内每个月的天数

        const static SStandardTime EPOCHT0 = {1970, 1, 1, 0, 0, 0, 0}; ///< 系统起算时间
        const static DOUBLE GPST0[] = {1980, 1, 6, 0, 0, 0};           ///< gps time reference
        const static DOUBLE GST0[] = {1999, 8, 22, 0, 0, 0};           ///< galileo system time reference
        const static DOUBLE BDT0[] = {2006, 1, 1, 0, 0, 0};            ///< beidou time reference

        const UINT64 EPOCH_TO_GPST0 = 315964800; ///< GPS零时距离系统零时的秒数
        const UINT64 EPOCH_TO_GALT0 = 935280000; ///< Galileo零时距离系统零时的秒数
        const UINT64 EPOCH_TO_BDT0 = 1136073600; ///< BDS零时距离系统零时的秒数

        const INT32 MONTH_IN_YEAR = 12;                               ///< 一年内的最大月数
        const INT32 DAY_IN_YEAR = 365;                                ///< 一年内的最大天数
        const INT32 DAY_IN_4YEAR = 1461;                              ///< 四年(含一个闰年)的总天数
        const INT32 MONTH_IN_4YRAR = 48;                              ///< 四年(含一个闰年)的总月数
        const INT32 CURRENT_MAX_YEAR = 2099;                          ///< 当前支持的最大年数
        const INT32 LEAP_YEAR_INTERVAL = 4;                           ///< 闰年间隔
        const UINT32 CENTURY_LEAP_YEAR = 400;                             ///< 世纪闰年
        const INT32 MAX_DAY_IN_MONTH = 31;                            ///< 一个月内最大的天数
        const INT32 MAX_HOUR_IN_DAY = 24;                             ///< 一天内最大的小时数
        const INT32 SEC_IN_DAY = MAX_HOUR_IN_DAY * BASE_60 * BASE_60; ///< 一天内的秒数 86400
        const INT32 SEC_IN_HALF_DAY = SEC_IN_DAY / 2;                 ///< 半天的时间 43200
        const INT32 DAY_IN_WEEK = 7;                                  ///< 一周内的天数
        const INT32 WEEK_SEC = DAY_IN_WEEK * SEC_IN_DAY;              ///< 一周内的秒数 604800

        // For Time Leap 跳秒值
        const INT32 WEEK_BETWEEN_GPS_GAL = 1024;          ///< GPS 与 Galileo 相差1024周
        const INT32 GPSWEEK_TO_BDSWEEK = 1356;            ///< GPS 与 BDS 相差1356周
        const INT32 THREE_HOUR = 3;                       ///< Glonass 与 UTC 之间的跳秒值
        const INT32 SEC_OF_3HOUR = 3 * BASE_60 * BASE_60; ///< 3小时对应的秒数
        const INT32 SEC_BETWEEN_GPS_BDS = 14;             ///< GPS 与 BDS 相差14s
        /// leap seconds (y,month,d,h,min,s,utc-gpst)
        const static INT32 GPS_LEAPSEC_INFO[65][7] = {{2017, 1, 1, 0, 0, 0, -18}, {2015, 7, 1, 0, 0, 0, -17},
                                                      {2012, 7, 1, 0, 0, 0, -16}, {2009, 1, 1, 0, 0, 0, -15},
                                                      {2006, 1, 1, 0, 0, 0, -14}, {1999, 1, 1, 0, 0, 0, -13},
                                                      {1997, 7, 1, 0, 0, 0, -12}, {1996, 1, 1, 0, 0, 0, -11},
                                                      {1994, 7, 1, 0, 0, 0, -10}, {1993, 7, 1, 0, 0, 0, -9},
                                                      {1992, 7, 1, 0, 0, 0, -8},  {1991, 1, 1, 0, 0, 0, -7},
                                                      {1990, 1, 1, 0, 0, 0, -6},  {1988, 1, 1, 0, 0, 0, -5},
                                                      {1985, 7, 1, 0, 0, 0, -4},  {1983, 7, 1, 0, 0, 0, -3},
                                                      {1982, 7, 1, 0, 0, 0, -2},  {1981, 7, 1, 0, 0, 0, -1},
                                                      {1980, 1, 6, 0, 0, 0, 0},   {0}};

        /// leap seconds (y,m,d,h,m,s,utc-gpst)
        const static INT32 BDS_LEAPSEC_INFO[65][7] = {{2017, 1, 1, 0, 0, 0, -4},
                                                      {2015, 7, 1, 0, 0, 0, -3},
                                                      {2012, 7, 1, 0, 0, 0, -2},
                                                      {2009, 1, 1, 0, 0, 0, -1},
                                                      {2006, 1, 1, 0, 0, 0, 0},
                                                      {0}};

        // 星历模块常量定义
        const INT32 FIFTEEN_MIN = 15;                           ///< 星历计算，15分钟
        const INT32 SEC_OF_FIFTEEN_MIN = FIFTEEN_MIN * BASE_60; ///< 15分钟对应的秒数

        const static DOUBLE J2_GLO = 1.0826257E-3; ///< 2nd zonal harmonic of geopot   ref [2]
        const static INT32 MAX_ITER_KEPLER = 30;   ///< max number of iteration of Kelpler
        const static DOUBLE RTOL_KEPLER = 1E-14;   ///< relative tolerance for Kepler equation
        const static DOUBLE RE_GLO = 6378136.0;    ///< radius of earth (m)            ref [2]

        const static DOUBLE GPS_GRAVITATION = 3.9860050E14;   ///< gravitational constant         ref [1]
        const static DOUBLE GLO_GRAVITATION = 3.9860044E14;   ///< gravitational constant         ref [2]
        const static DOUBLE GAL_GRAVITATION = 3.986004418E14; ///< earth gravitational constant   ref [7]
        const static DOUBLE BDS_GRAVITATION = 3.986004418E14; ///< earth gravitational constant   ref [9]

        const static DOUBLE GPS_ANGULAR_VELOCITY = 7.2921151467E-5;   ///< earth angular velocity (IS-GPS) (rad/s)
        const static DOUBLE GLO_ANGULAR_VELOCITY = 7.292115E-5;       ///< earth angular velocity (rad/s) ref [2]
        const static DOUBLE GAL_ANGULAR_VELOCITY = 7.2921151467E-5;   ///< earth angular velocity (rad/s) ref [7]
        const static DOUBLE BDS_ANGULAR_VELOCITY = 7.292115E-5;       ///< earth angular velocity (rad/s) ref [9]
        const static DOUBLE DOUBLE_ZONE_LITTLE = -1E9;                ///< DOUBLE值是否为0比较时的最小值
        const static DOUBLE DOUBLE_ZONE_BIG = 1E9;                    ///< DOUBLE值是否为0比较时的最大值
        const static DOUBLE GLO_EPHENERI_INTEGRATION_STEP_PRN = 1e-9; ///< GLONASS星历位置微分方程步长的精度
        const static INT32 GLO_EPHENERI_INTEGRATION_STEP = 60;        ///< glonass星历位置微分方程步长

        const static DOUBLE SIN_5 = -0.0871557427476582; ///< sin(-5.0 deg)
        const static DOUBLE COS_5 = 0.9961946980917456;  ///< cos(-5.0 deg)

        // 坐标模块常量定义
        const INT32 COORDINATE_ACCURACY = 4; ///< 空间直角坐标，以及大地坐标中高程的精确度
        const INT32 MSEC_ACCURACY = 3;       ///< 秒的精确度(精确到毫秒)
        const INT32 MATRIX_ACCURACY = 6;     ///< 矩阵中DOUBLE数据与角分秒格式中的秒的精确度
        const INT32 DEGREE_ACCURACY = 11;    ///< 大地坐标中经纬度与小数度的精确度(小数后11位)
        const std::string DEGREE_UNIT = "D"; ///< 小数度的单位
        const DOUBLE LAT_ACCURACY = 1.0e-11; ///< 计算大地纬度B时的精度

        const DOUBLE LONGITUDE_LOWER_LIMIT = -180; ///< 经度下限
        const DOUBLE LONGITUDE_UPPER_LIMIT = 180;  ///< 经度上限
        const DOUBLE LATITUDE_LOWER_LIMIT = -90;   ///< 纬度下限
        const DOUBLE LATITUDE_UPPER_LIMIT = 90;    ///< 纬度上限
        const DOUBLE LONGITUDE_DOUBLE_UPPER_LIMIT = 360;
        const DOUBLE ZERO_POINT_FIVE = 0.5;
        const DOUBLE ONE_POINT_FIVE = 1.5;

        // 地球的长半轴
        // WGS84参数
        const DOUBLE WGS84_EARTH_LONG_RADIUS = 6378137.0;     ///< WGS84长半轴
        const DOUBLE WGS84_EARTH_SHORT_RADIUS = 6356752.3142; ///< WGS84短半轴
        const DOUBLE WGS84_EARTH_OBLATEO = 1 / 298.257223563; ///< WGS84扁率
        const DOUBLE WGS84_FIRST_E2 = 0.00669437999013;       ///< WGS84第一偏心率的平方
        const DOUBLE WGS84_SECOND_E2 = 0.006739496742227;     ///< WGS84第二偏心率的平方

        // CGCS2000参数
        const DOUBLE CGCS2000_EARTH_LONG_RADIUS = 6378137.0;      ///< CGCS2000长半轴
        const DOUBLE CGCS2000_EARTH_SHORT_RADIUS = 6356752.31414; ///< CGCS2000短半轴
        const DOUBLE CGCS2000_EARTH_OBLATEO = 1 / 298.257222101;  ///< CGCS2000扁率
        const DOUBLE CGCS2000_FIRST_E2 = 0.00669438002290;        ///< CGCS2000第一偏心率的平方
        const DOUBLE CGCS2000_SECOND_E2 = 0.00673949677548;       ///< CGCS2000第二偏心率的平方

        // PZ90参数待定
        const DOUBLE PZ90_EARTH_LONG_RADIUS = 6378136.0;     ///< PZ90长半轴
        const DOUBLE PZ90_EARTH_OBLATEO = 1 / 298.257839303; ///< PZ90扁率

        // 角度模块常量定义
        const static DOUBLE PI = 3.1415926535897932; ///< pi值
        const static DOUBLE D2R = (PI / 180.0);      ///< deg to rad
        const static DOUBLE R2D = (180.0 / PI);      ///< rad to deg
        const UINT32 DEG_TO_SEC = 3600;              ///< 角度转秒
    }                                                // end namespace Math
} // end namespace sixents

#endif // !_GNSS_COMMON_DEF_H
