/**@file             文件名
 *  @brief          项目简述
 *  @details       项目细节
 *  @author       作者
 *  @date          日期
 *  @version      版本
 *  @note          注解
 *  @copyright   版权
 */

#include "AppInterface.h"
#include "../Angle/CGNSSAngle.h"
#include "../Coordinate/CGNSSCoord.h"
#include "../DllMain/GNSSCommonDef.h"
#include "../Ephemeris/CGNSSEphemeris.h"
#include "../Time/TimeSys/IGNSSTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        // GUL_UC_001 GUL_UC_003 GUL_UC_004
        int CAppInterface::FormatWeekSecTime(
            const int week, const double sec, const int timeType, char* formatString, int& len)
        {
            /*do
            {
                CGNSSTime GNSSTime(week, sec);
                SGNSSTime sGnssTime = GNSSTime.GetGNSSTime();
                SStandardTime sStandardTime;
                GNSSTime.GNSSTimeToStandardTime(sGnssTime, sStandardTime, timeType);
                GNSSTime.StandardTimeToString(sStandardTime, formatString, len);
            } while (false);*/
            return RETURN_SUCCESS;
        }

        // GUL_UC_002
        int CAppInterface::FormatStandardTime(const int year,
                                              const int month,
                                              const int day,
                                              const int hour,
                                              const int minute,
                                              const double second,
                                              char* formatString,
                                              int& len)
        {
            /*do
            {
                CGNSSTime GNSSTime(year, month, day, hour, minute, second);
                SStandardTime sStandardTime = GNSSTime.GetStandardTime();
                GNSSTime.StandardTimeToString(sStandardTime, formatString, len);
            } while (false);*/
            return RETURN_SUCCESS;
        }

        // GUL_UC_005 GUL_UC_007 GUL_UC_008
        int CAppInterface::GNSSTimeToUTCTime(const int week,
                                             const double sec,
                                             const int timeType,
                                             int& year,
                                             int& month,
                                             int& day,
                                             int& hour,
                                             int& minute,
                                             double& second)
        {
            /*do
            {
                CGNSSTime GNSSTime(week, sec);
                SGNSSTime sGnssTime = GNSSTime.GetGNSSTime();
                SStandardTime sStandardTimeTime;
                GNSSTime.GNSSTimeToUTCTime(sGnssTime, sStandardTimeTime, timeType);
                year = sStandardTimeTime.m_year;
                month = sStandardTimeTime.m_month;
                day = sStandardTimeTime.m_day;
                hour = sStandardTimeTime.m_hour;
                minute = sStandardTimeTime.m_minute;
                second = sStandardTimeTime.m_second;
            } while (false);*/
            return RETURN_SUCCESS;
        }

        // GUL_UC_006
        int CAppInterface::GlonassTimeToUTCTime(const int gloYear,
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
            /*do
            {
                CGNSSTime GNSSTime(gloYear, gloMonth, gloDay, gloHour, gloMinute, gloSecond);
                SStandardTime srcGNSSTime = GNSSTime.GetStandardTime();
                SStandardTime tarGNSSTime;
                GNSSTime.GLOT2UTC(srcGNSSTime, tarGNSSTime);
                utcYear = tarGNSSTime.m_year;
                utcMonth = tarGNSSTime.m_month;
                utcDay = tarGNSSTime.m_day;
                utcHour = tarGNSSTime.m_hour;
                utcMinute = tarGNSSTime.m_minute;
                utcSecond = tarGNSSTime.m_second;
            } while (false);*/
            return RETURN_SUCCESS;
        }

        // GUL_UC_009 GUL_UC_011 GUL_UC_012
        int CAppInterface::UTCTimeToGNSSTime(const int year,
                                             const int month,
                                             const int day,
                                             const int hour,
                                             const int minute,
                                             const double second,
                                             const int timeType,
                                             int& week,
                                             double& sec)
        {
            /*do
            {
                CGNSSTime GNSSTime(year, month, day, hour, minute, second);
                SStandardTime sStandardTime = GNSSTime.GetStandardTime();
                SGNSSTime sGnssTime;
                GNSSTime.StandardTimeToGNSSTime(sStandardTime, sGnssTime, timeType);
                week = sGnssTime.m_week;
                sec = sGnssTime.m_secAndMsec;
            } while (false);*/
            return RETURN_SUCCESS;
        }

        int CAppInterface::UTCTimeToGNSSSecTime(const int year,
                                                const int month,
                                                const int day,
                                                const int hour,
                                                const int minute,
                                                const double second,
                                                const int timeType,
                                                double& sec)
        {
            return RETURN_SUCCESS;
        }

        int CAppInterface::WeekSecToSec(const int week, const double second, const int timeType, double& sec)
        {
            return RETURN_SUCCESS;
        }

        // GUL_UC_010
        int CAppInterface::UTCTimeToGlonassTime(const int utcYear,
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
            /*do
            {
                CGNSSTime GNSSTime(utcYear, utcMonth, utcDay, utcHour, utcMinute, utcSecond);
                SStandardTime srcGNSSTime = GNSSTime.GetStandardTime();
                SStandardTime tarGNSSTime;
                GNSSTime.UTC2GLOT(srcGNSSTime, tarGNSSTime);
                gloYear = tarGNSSTime.m_year;
                gloMonth = tarGNSSTime.m_month;
                gloDay = tarGNSSTime.m_day;
                gloHour = tarGNSSTime.m_hour;
                gloMinute = tarGNSSTime.m_minute;
                gloSecond = tarGNSSTime.m_second;
            } while (false);*/
            return RETURN_SUCCESS;
        }

        // GUL_UC_013  GUL_UC_015 GUL_UC_016  GUL_UC_018
        int CAppInterface::GNSSTimeConvert(const int srcWeek,
                                           const double srcSec,
                                           const int srcTimeType,
                                           int& destWeek,
                                           double& destSec,
                                           const int destTimeType)
        {
            /*do
            {
                CGNSSTime GNSSTime(srcWeek, srcSec, srcTimeType);
                SGNSSTime srcGNSSTime = GNSSTime.GetGNSSTime();
                SGNSSTime tarGNSSTime;
                GNSSTime.GNSSTimeConvert(srcGNSSTime, srcTimeType, tarGNSSTime, destTimeType);
                destWeek = tarGNSSTime.m_week;
                destSec = tarGNSSTime.m_secAndMsec;
            } while (false);*/
            return RETURN_SUCCESS;
        }

        // GUL_UC_014
        int CAppInterface::GlonassTimeToGPSTime(const int year,
                                                const int month,
                                                const int day,
                                                const int hour,
                                                const int minute,
                                                const double second,
                                                int& week,
                                                double& sec)
        {
            /*do
            {
                CGNSSTime GNSSTime(year, month, day, hour, minute, second);
                SStandardTime srcGNSSTime = GNSSTime.GetStandardTime();
                SStandardTime utcGnssTime;
                GNSSTime.GLOT2UTC(srcGNSSTime, utcGnssTime);
                SGNSSTime GPSTime;
                GNSSTime.UTC2GPST(utcGnssTime, GPSTime);
                week = GPSTime.m_week;
                sec = GPSTime.m_secAndMsec;
            } while (false);*/
            return RETURN_SUCCESS;
        }

        // GUL_UC_017
        int CAppInterface::GPSTimeToGlonassTime(
            const int week, const double second, int& year, int& month, int& day, int& hour, int& minute, double& sec)
        {
            /*do
            {
                CGNSSTime GNSSTime(week, second);
                SGNSSTime srcGNSSTime = GNSSTime.GetGNSSTime();
                SStandardTime utcGnssTime;
                GNSSTime.GPST2UTC(srcGNSSTime, utcGnssTime);
                SStandardTime gloTime;
                GNSSTime.UTC2GLOT(utcGnssTime, gloTime);
                year = gloTime.m_year;
                month = gloTime.m_month;
                day = gloTime.m_day;
                hour = gloTime.m_hour;
                minute = gloTime.m_minute;
                sec = gloTime.m_second;
            } while (false);*/
            return RETURN_SUCCESS;
        }

        int
        CAppInterface::XYZ2BLH(const double x, const double y, const double z, double& lon, double& lat, double& height)
        {
            return RETURN_SUCCESS;
        }

        int
        CAppInterface::BLH2XYZ(const double lon, const double lat, const double height, double& x, double& y, double& z)
        {
            return RETURN_SUCCESS;
        }

        int CAppInterface::XYZ2ENU(const double curX,
                                   const double curY,
                                   const double curZ,
                                   const double refX,
                                   const double refY,
                                   const double refZ,
                                   double& east,
                                   double& north,
                                   double& up)
        {
            return RETURN_SUCCESS;
        }

        int CAppInterface::ENU2XYZ(const double east,
                                   const double north,
                                   const double up,
                                   const double refX,
                                   const double refY,
                                   const double refZ,
                                   double& curX,
                                   double& curY,
                                   double& curZ)
        {
            return RETURN_SUCCESS;
        }

        int CAppInterface::CalcGlonassEphSatClock(const double& sec, const SGlonassEphemeris& ephObj, double& clockVal)
        {
            return RETURN_SUCCESS;
        }

        int CAppInterface::CalcEphSatClock(const double& sec, const SEphemeris& ephObj, double& clockVal)
        {
            return RETURN_SUCCESS;
        }

        int CAppInterface::CalcGlonassEphSatPos(
            const double sec, const SGlonassEphemeris& ephObj, double& x, double& y, double& z)
        {
            return RETURN_SUCCESS;
        }

        int CAppInterface::CalcEphSatPos(const double sec, const SEphemeris& ephObj, double& x, double& y, double& z)
        {
            return RETURN_SUCCESS;
        }

        int CAppInterface::FormatAngleByDegree(const double degree, char* formatString, int& len, const bool formatType)
        {
            if (nullptr != formatString)
            {
                formatString = nullptr;
            }

            CGNSSAngle angleObj(degree);
            int length = angleObj.GetLength(true);
            formatString = new char[length + 1];
            angleObj.ToDegString(formatString, length, formatType);
            return RETURN_SUCCESS;
        }

        int CAppInterface::FormatAngleByDMS(
            const int degree, const int minute, const double sec, char* formatString, int& len, const bool formatType)
        {
            if (nullptr != formatString)
            {
                formatString = nullptr;
            }

            CGNSSAngle angleObj(degree, minute, sec);
            int length = angleObj.GetLength(false);
            formatString = new char[length + 1];
            angleObj.ToDegString(formatString, length, formatType);
            return RETURN_SUCCESS;
        }

        int CAppInterface::Deg2Rad(const double degree, double& radian)
        {
            do
            {
                CGNSSAngle angleObj(degree);
                angleObj.DegToRad(degree, radian);
            } while (false);
            return RETURN_SUCCESS;
        }

        int CAppInterface::DMS2Rad(const int degree, const int minute, const double sec, double& radian)
        {
            do
            {
                double DegToRad = 0;
                CGNSSAngle angleObj(degree, minute, sec);
                angleObj.DMSToDeg(degree, minute, sec, DegToRad);
                angleObj.DegToRad(DegToRad, radian);
            } while (false);
            return RETURN_SUCCESS;
        }

        int CAppInterface::Rad2Deg(const double radian, double& degree)
        {
            do
            {
                CGNSSAngle angleObj(degree, false);
                angleObj.RadToDeg(radian, degree);
            } while (false);
            return RETURN_SUCCESS;
        }

        int CAppInterface::Rad2DMS(const double radian, int& degree, int& minute, double& sec)
        {
            do
            {
                double RadToDeg = 0;
                CGNSSAngle angleObj(radian, false);
                angleObj.RadToDeg(radian, RadToDeg);
                angleObj.DegToDMS(RadToDeg, degree, minute, sec);
            } while (false);
            return RETURN_SUCCESS;
        }
    } // namespace GNSSUtilityLib
} // namespace sixents