/**@file             文件名
 *  @brief          项目简述
 *  @details       项目细节
 *  @author       作者
 *  @date          日期
 *  @version      版本
 *  @note          注解
 *  @copyright   版权
 */

#define DLL_EXPORT

#include "GNSSUtilityInterface.h"
#include "../AppIFs/AppInterface.h"
#include "GNSSCommonDef.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        // GUL_UC_001 GUL_UC_003 GUL_UC_004
        extern "C" DLL_API int STD_CALL
        FormatWeekSecTime(const int week, const double sec, const int timeType, char* formatString, int& len)
        {
            return CAppInterface::FormatWeekSecTime(static_cast<INT64>(week), sec, timeType, formatString, len);
        }

        // GUL_UC_002
        extern "C" DLL_API int STD_CALL FormatStandardTime(const int year,
                                                           const int month,
                                                           const int day,
                                                           const int hour,
                                                           const int minute,
                                                           const double second,
                                                           char* formatString,
                                                           int& len)
        {
            return CAppInterface::FormatStandardTime(year, month, day, hour, minute, second, formatString, len);
        }

        // GUL_UC_005 GUL_UC_007 GUL_UC_008
        extern "C" DLL_API int STD_CALL GNSSTimeToUTCTime(const int week,
                                                          const double sec,
                                                          const int timeType,
                                                          int& year,
                                                          int& month,
                                                          int& day,
                                                          int& hour,
                                                          int& minute,
                                                          double& second)
        {
            return CAppInterface::GNSSTimeToUTCTime(week, sec, timeType, year, month, day, hour, minute, second);
        }

        // GUL_UC_006
        extern "C" DLL_API int STD_CALL GlonassTimeToUTCTime(const int gloYear,
                                                             const int gloMonth,
                                                             const int gloDay,
                                                             const int gloHour,
                                                             const int gloMinute,
                                                             const double gloSecond,
                                                             int& utcYear,
                                                             int& utcMonth,
                                                             int& utcDay,
                                                             int& utcHour,
                                                             int& utcMinute,
                                                             double& utcSecond)
        {
            return CAppInterface::GlonassTimeToUTCTime(gloYear,
                                                       gloMonth,
                                                       gloDay,
                                                       gloHour,
                                                       gloMinute,
                                                       gloSecond,
                                                       utcYear,
                                                       utcMonth,
                                                       utcDay,
                                                       utcHour,
                                                       utcMinute,
                                                       utcSecond);
        }

        // GUL_UC_009 GUL_UC_011 GUL_UC_012
        extern "C" DLL_API int STD_CALL UTCTimeToGNSSTime(const int year,
                                                          const int month,
                                                          const int day,
                                                          const int hour,
                                                          const int minute,
                                                          const double second,
                                                          const int timeType,
                                                          int& week,
                                                          double& sec)
        {
            INT64 weekNum = 0;
            int ret = CAppInterface::UTCTimeToGNSSTime(year, month, day, hour, minute, second,
                                                    timeType, weekNum, sec);
            week = static_cast<int>(weekNum);
            return ret;
        }

        extern "C" DLL_API int STD_CALL UTCTimeToGNSSSecTime(const int year,
                                                             const int month,
                                                             const int day,
                                                             const int hour,
                                                             const int minute,
                                                             const double second,
                                                             const int timeType,
                                                             double& sec)
        {
            return CAppInterface::UTCTimeToGNSSSecTime(year, month, day, hour, minute, second, timeType, sec);
        }

        extern "C" int STD_CALL WeekSecToSec(const int week, const double second, const int timeType, double& sec)
        {
            return CAppInterface::WeekSecToSec(week, second, timeType, sec);
        }

        // GUL_UC_010
        extern "C" DLL_API int STD_CALL UTCTimeToGlonassTime(const int utcYear,
                                                             const int utcMonth,
                                                             const int utcDay,
                                                             const int utcHour,
                                                             const int utcMinute,
                                                             const double utcSecond,
                                                             int& gloYear,
                                                             int& gloMonth,
                                                             int& gloDay,
                                                             int& gloHour,
                                                             int& gloMinute,
                                                             double& gloSecond)
        {
            return CAppInterface::UTCTimeToGlonassTime(utcYear,
                                                       utcMonth,
                                                       utcDay,
                                                       utcHour,
                                                       utcMinute,
                                                       utcSecond,
                                                       gloYear,
                                                       gloMonth,
                                                       gloDay,
                                                       gloHour,
                                                       gloMinute,
                                                       gloSecond);
        }

        // GUL_UC_013  GUL_UC_015 GUL_UC_016  GUL_UC_018
        extern "C" DLL_API int STD_CALL GNSSTimeConvert(const int srcWeek,
                                                        const double srcSec,
                                                        const int srcTimeType,
                                                        int& destWeek,
                                                        double& destSec,
                                                        const int destTimeType)
        {
            INT64 temp = 0;
            int ret = CAppInterface::GNSSTimeConvert(srcWeek, srcSec, srcTimeType, temp, destSec, destTimeType);
            destWeek = static_cast<int>(temp);
            return ret;
        }

        // GUL_UC_014
        extern "C" DLL_API int STD_CALL GlonassTimeToGPSTime(const int year,
                                                             const int month,
                                                             const int day,
                                                             const int hour,
                                                             const int minute,
                                                             const double second,
                                                             int& week,
                                                             double& sec)
        {
            INT64 temp = 0;
            int ret = CAppInterface::GlonassTimeToGPSTime(year, month, day, hour, minute, second, temp, sec);
            week = static_cast<int>(temp);
            return ret;
        }

        // GUL_UC_017
        extern "C" DLL_API int STD_CALL GPSTimeToGlonassTime(
            const int week, const double second, int& year, int& month, int& day, int& hour, int& minute, double& sec)
        {
            return CAppInterface::GPSTimeToGlonassTime(week, second, year, month, day, hour, minute, sec);
        }

        extern "C" DLL_API int STD_CALL
        XYZ2BLH(const double x, const double y, const double z, double& lon, double& lat, double& height)
        {
            return CAppInterface::XYZ2BLH(x, y, z, lon, lat, height);
        }

        extern "C" DLL_API int STD_CALL
        BLH2XYZ(const double lon, const double lat, const double height, double& x, double& y, double& z)
        {
            return CAppInterface::BLH2XYZ(lon, lat, height, x, y, z);
        }

        extern "C" DLL_API int STD_CALL XYZ2ENU(const double curX,
                                                const double curY,
                                                const double curZ,
                                                const double refX,
                                                const double refY,
                                                const double refZ,
                                                double& east,
                                                double& north,
                                                double& up)
        {
            return CAppInterface::XYZ2ENU(curX, curY, curZ, refX, refY, refZ, east, north, up);
        }

        extern "C" DLL_API int STD_CALL ENU2XYZ(const double east,
                                                const double north,
                                                const double up,
                                                const double refX,
                                                const double refY,
                                                const double refZ,
                                                double& curX,
                                                double& curY,
                                                double& curZ)
        {
            return CAppInterface::ENU2XYZ(east, north, up, refX, refY, refZ, curX, curY, curZ);
        }

        extern "C" DLL_API int STD_CALL CalcGlonassEphSatClock(const double& sec,
                                                               const SGlonassEphemeris& ephObj,
                                                               double& clockVal)
        {
            return CAppInterface::CalcGlonassEphSatClock(sec, ephObj, clockVal);
        }

        extern "C" DLL_API int STD_CALL CalcEphSatClock(const double& sec, const SEphemeris& ephObj, double& clockVal)
        {
            return CAppInterface::CalcEphSatClock(sec, ephObj, clockVal);
        }

        extern "C" DLL_API int STD_CALL
        CalcGlonassEphSatPos(const double sec, const SGlonassEphemeris& ephObj, double& x, double& y, double& z)
        {
            return CAppInterface::CalcGlonassEphSatPos(sec, ephObj, x, y, z);
        }

        extern "C" DLL_API int STD_CALL
        CalcEphSatPos(const double sec, const SEphemeris& ephObj, double& x, double& y, double& z)
        {
            return CAppInterface::CalcEphSatPos(sec, ephObj, x, y, z);
        }

        extern "C" DLL_API int STD_CALL FormatAngleByDegree(const double degree,
                                                            char* formatString,
                                                            int& len,
                                                            const bool formatType)
        {
            return CAppInterface::FormatAngleByDegree(degree, formatString, len, formatType);
        }

        extern "C" DLL_API int STD_CALL FormatAngleByDMS(
            const int degree, const int minute, const double sec, char* formatString, int& len, const bool formatType)
        {
            return CAppInterface::FormatAngleByDMS(degree, minute, sec, formatString, len, formatType);
        }

        extern "C" DLL_API int STD_CALL Deg2Rad(const double degree, double& radian)
        {
            return CAppInterface::Deg2Rad(degree, radian);
        }

        extern "C" DLL_API int STD_CALL DMS2Rad(const int degree, const int minute, const double sec, double& radian)
        {
            return CAppInterface::DMS2Rad(degree, minute, sec, radian);
        }

        extern "C" DLL_API int STD_CALL Rad2Deg(const double radian, double& degree)
        {
            return CAppInterface::Rad2Deg(radian, degree);
        }

        extern "C" DLL_API int STD_CALL Rad2DMS(const double radian, int& degree, int& minute, double& sec)
        {
            return CAppInterface::Rad2DMS(radian, degree, minute, sec);
        }
    } // namespace GNSSUtilityLib
} // namespace sixents