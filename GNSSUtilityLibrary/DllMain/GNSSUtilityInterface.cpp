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
#include "GNSSCommonDef.h"

 // 包含需要的内部头文件
#include "../Time/CGNSSTime.h"
#include "../Angle/CGNSSAngle.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        //GUL_UC_001- GUL_UC_004解决
        extern "C" DLL_API int STD_CALL FormatWeekSecTime(const int week, const double sec, const int satType, char* formatString, int& len)
        {
            do
            {
                CGNSSTime GNSSTime(week, sec);
                SGNSSTime sGnssTime = GNSSTime.GetGNSSTime();
                SStandardTime sStandardTime;
                GNSSTime.GNSSTimeToStandardTime(sGnssTime, sStandardTime, satType);
                GNSSTime.StandardToString(sStandardTime, formatString, len);
            } while (false);
            return 1;
        }

        extern "C" DLL_API int STD_CALL FormatStandardTime(const int year, const int month, const int day,
            const int hour, const int minute, const double second, char* formatString, int& len)
        {
            do
            {
                CGNSSTime GNSSTime(year, month, day, hour, minute, second);
                SStandardTime sStandardTime = GNSSTime.GetStandardTime();
                GNSSTime.StandardToString(sStandardTime, formatString, len);
            } while (false);
            return 1;
        }

        //GUL_UC_005-GUL_UC_008解决
        extern "C" DLL_API int STD_CALL GNSSTimeToUTCTime(const int week, const double sec, const int satType,
            int& year, int& month, int& day,
            int& hour, int& minute, double& second)
        {
            do
            {
                CGNSSTime GNSSTime(week, sec);
                SGNSSTime sGnssTime = GNSSTime.GetGNSSTime();
                SStandardTime sStandardTimeTime;
                GNSSTime.GNSSTimeToUTCTime(sGnssTime, sStandardTimeTime, satType);

                year = sStandardTimeTime.m_year;
                month = sStandardTimeTime.m_month;
                day = sStandardTimeTime.m_day;
                hour = sStandardTimeTime.m_hour;
                minute = sStandardTimeTime.m_minute;
                second = sStandardTimeTime.m_seconde;
            } while (false);
            return 1;
        }

        //GUL_UC_009-GUL_UC_012
        extern "C" DLL_API int STD_CALL UTCTimeToGNSSTime(const int year, const int month, const int day,
            const int hour, const int minute, const double second,
            const int satType, int& week, double& sec)
        {
            do
            {
                CGNSSTime GNSSTime(year, month, day, hour, minute, second);
                SStandardTime sStandardTime = GNSSTime.GetStandardTime();
                SGNSSTime sGnssTime;
                GNSSTime.StandardTimeToGNSSTime(sStandardTime, sGnssTime, satType);

                week = sGnssTime.m_week;
                sec = sGnssTime.m_secAndMsec;
            } while (false);
            return 1;
        }

        extern "C" DLL_API int STD_CALL GNSSTimeConvert(const int srcWeek, const double srcSec, const int srcSatType,
            int& destWeek, double& destSec, const int destSatType)
        {
            do
            {
                CGNSSTime GNSSTime(srcWeek, srcSec, srcSatType);
                SGNSSTime srcGnssTime = GNSSTime.GetGNSSTime();
                SGNSSTime tarGnssTime;
                GNSSTime.GNSSTimeConvert(srcGnssTime, srcSatType, tarGnssTime, destSatType);
                destWeek = tarGnssTime.m_week;
                destSec = tarGnssTime.m_secAndMsec;
            } while (false);
            return 1;
        }

        extern "C" DLL_API int STD_CALL XYZ2BLH(const double x, const double y, const double z,
            double& lon, double& lat, double& height)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL BLH2XYZ(const double lon, const double lat, const double height,
            double& x, double& y, double& z)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL XYZ2ENU(const double curX, const double curY, const double curZ,
            const double refX, const double refY, const double refZ,
            double& east, double& north, double& up)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL ENU2XYZ(const double east, const double north, const double up,
            const double refX, const double refY, const double refZ,
            double& curX, double& curY, double& curZ)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL CalcGlonassEphSatClock(const double& sec, const SGlonassEphemeris& ephObj, double& clockVal)
        {
            return 0;
        }
        extern "C"   DLL_API int STD_CALL CalcEphSatClock(const double& sec, const SEphemeris& ephObj, double& clockVal)
        {
            return 0;
        }
        // 计算位置
        // ephObj: 输入参数，星历数据
        // x,y,z: 输出参数，计算出来的位置值
        extern "C"   DLL_API int STD_CALL CalcGlonassEphSatPos(const double sec, const SGlonassEphemeris& ephObj, double& x, double& y, double& z)
        {
            return 0;
        }
        extern "C"   DLL_API int STD_CALL CalcEphSatPos(const double sec, const SEphemeris& ephObj, double& x, double& y, double& z)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL FormatAngleByDegree(const double degree, char* formatString, const bool formatType)
        {
            if (nullptr != formatString)
            {
                formatString = nullptr;
            }

            CGNSSAngle angleObj(degree);
            int length = angleObj.GetLength(true);
            formatString = new char[length + 1];
            angleObj.ToDegString(formatString, length, formatType);
            return 1;
        }

        extern "C" DLL_API int STD_CALL FormatAngleByDMS(const int degree, const int minute, const double sec,
            char* formatString, const bool formatType)
        {
            if (nullptr != formatString)
            {
                formatString = nullptr;
            }

            CGNSSAngle angleObj(degree, minute, sec);
            int length = angleObj.GetLength(false);
            formatString = new char[length + 1];
            angleObj.ToDegString(formatString, length, formatType);
            return 1;
        }

        extern "C" DLL_API int STD_CALL Deg2Rad(const double degree, double& radian)
        {
            do
            {
                CGNSSAngle angleObj(degree);
                angleObj.DegToRad(degree, radian);
            } while (false);
            return 1;
        }

        extern "C" DLL_API int STD_CALL DMS2Rad(const int degree, const int minute, const double sec, double& radian)
        {
            do
            {
                double DegToRad = 0;
                CGNSSAngle angleObj(degree, minute, sec);
                angleObj.DMSToDeg(degree, minute, sec, DegToRad);
                angleObj.DegToRad(DegToRad, radian);
            } while (false);
            return 1;
        }

        extern "C" DLL_API int STD_CALL Rad2Deg(const double radian, double& degree)
        {
            do
            {
                CGNSSAngle angleObj(degree, false);
                angleObj.RadToDeg(radian, degree);
            } while (false);
            return 1;
        }

        extern "C" DLL_API int STD_CALL Rad2DMS(const double radian, int& degree, int& minute, double& sec)
        {
            do
            {
                double RadToDeg = 0;
                CGNSSAngle angleObj(radian, false);
                angleObj.RadToDeg(radian, RadToDeg);
                angleObj.DegToDMS(RadToDeg, degree, minute, sec);
            } while (false);
            return 1;
        }
    }
}