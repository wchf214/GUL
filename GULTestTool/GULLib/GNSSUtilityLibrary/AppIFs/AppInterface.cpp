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
#include "../Time/TimeSys/CTimeFactory.h"
#include "../Time/TimeClac/CCalcTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        // GUL_UC_001 GUL_UC_003 GUL_UC_004
        INT32 CAppInterface::FormatWeekSecTime(
            const INT64 week, const DOUBLE sec, const INT32 timeType, CHAR* formatString, INT32& len)
        {
            if (timeType <= 0)
            {
                return RETURN_TIME_TYPE_ERROR;
            }
            IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
            if (timeObj == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            SGNSSTime curTime = {week, sec, static_cast<UINT32>(timeType)};
            timeObj->SetTime(curTime);
            std::string timeStr("");
            timeObj->Format(timeStr);
            const INT32 nullCharLen = 1;
            if (len != static_cast<INT32>(timeStr.size()) + nullCharLen) {
                len = static_cast<INT32>(timeStr.size()) + nullCharLen;
                return RETURN_PTR_LENGTH_ERROR;
            }
            memcpy_s(formatString, static_cast<rsize_t>(len), timeStr.c_str(), static_cast<rsize_t>(len));
            return RETURN_SUCCESS;
        }

        // GUL_UC_002
        INT32 CAppInterface::FormatStandardTime(const INT32 year,
                                              const INT32 month,
                                              const INT32 day,
                                              const INT32 hour,
                                              const INT32 minute,
                                              const DOUBLE second,
                                              CHAR* formatString,
                                              INT32& len)
        {
            IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(UTC));
            if (timeObj == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            SStandardTime curTime = {static_cast<UINT32>(year), static_cast<UINT32>(month), static_cast<UINT32>(day),
                                     static_cast<UINT32>(hour), static_cast<UINT32>(minute), second,
                                     static_cast<UINT32>(UTC)};
            timeObj->SetTime(curTime);
            std::string timeStr("");
            timeObj->Format(timeStr);
            const INT32 nullCharLen = 1;
            if (len != static_cast<INT32>(timeStr.size()) + nullCharLen) {
                len = static_cast<INT32>(timeStr.size()) + nullCharLen;
                return RETURN_PTR_LENGTH_ERROR;
            }
            memcpy_s(formatString, static_cast<rsize_t>(len), timeStr.c_str(), static_cast<rsize_t>(len));
            return RETURN_SUCCESS;
        }

        // GUL_UC_005 GUL_UC_007 GUL_UC_008
        INT32 CAppInterface::GNSSTimeToUTCTime(const INT64 week,
                                             const DOUBLE sec,
                                             const INT32 timeType,
                                             INT32& year,
                                             INT32& month,
                                             INT32& day,
                                             INT32& hour,
                                             INT32& minute,
                                             DOUBLE& second)
        {
            SGNSSTime srcTimeData = {week, sec, static_cast<UINT32>(timeType)};
            IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
            if (srcTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            srcTime->SetTime(srcTimeData);
            DOUBLE curSec = 0.0;
            srcTime->GetTime(curSec);
            DOUBLE retSec = CCalcTime::TimeConvert(curSec, static_cast<TIME_TYPE>(timeType), UTC);
            IGNSSTime* destTime = CTimeFactory::CreateTimeObj(UTC);
            if (destTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            destTime->SetTime(retSec);
            SStandardTime destTimeData;
            destTime->GetTime(destTimeData);
            year = static_cast<INT32>(destTimeData.m_year);
            month = static_cast<INT32>(destTimeData.m_month);
            day = static_cast<INT32>(destTimeData.m_day);
            hour = static_cast<INT32>(destTimeData.m_hour);
            minute = static_cast<INT32>(destTimeData.m_minute);
            second = destTimeData.m_second;
            return RETURN_SUCCESS;
        }

        // GUL_UC_006
        INT32 CAppInterface::GlonassTimeToUTCTime(const INT32 gloYear,
                                                const INT32 gloMonth,
                                                const INT32 gloDay,
                                                const INT32 gloHour,
                                                const INT32 gloMinute,
                                                const DOUBLE gloSecond,
                                                INT32& utcYear,
                                                INT32& utcMonth,
                                                INT32& utcDay,
                                                INT32& utcHour,
                                                INT32& utcMinute,
                                                DOUBLE& utcSecond)
        {
            SStandardTime srcTimeData = {static_cast<UINT32>(gloYear), static_cast<UINT32>(gloMonth),
                                         static_cast<UINT32>(gloDay), static_cast<UINT32>(gloHour),
                                         static_cast<UINT32>(gloMinute), gloSecond,
                                         static_cast<UINT32>(GLONASS)};
            IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(GLONASS);
            if (srcTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            srcTime->SetTime(srcTimeData);
            DOUBLE curSec = 0.0;
            srcTime->GetTime(curSec);
            DOUBLE retSec = CCalcTime::TimeConvert(curSec, GLONASS, UTC);
            IGNSSTime* destTime = CTimeFactory::CreateTimeObj(UTC);
            if (destTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            destTime->SetTime(retSec);
            SStandardTime destTimeData;
            destTime->GetTime(destTimeData);
            utcYear = static_cast<INT32>(destTimeData.m_year);
            utcMonth = static_cast<INT32>(destTimeData.m_month);
            utcDay = static_cast<INT32>(destTimeData.m_day);
            utcHour = static_cast<INT32>(destTimeData.m_hour);
            utcMinute = static_cast<INT32>(destTimeData.m_minute);
            utcSecond = destTimeData.m_second;
            return RETURN_SUCCESS;
        }

        // GUL_UC_009 GUL_UC_011 GUL_UC_012
        INT32 CAppInterface::UTCTimeToGNSSTime(const INT32 year,
                                             const INT32 month,
                                             const INT32 day,
                                             const INT32 hour,
                                             const INT32 minute,
                                             const DOUBLE second,
                                             const INT32 timeType,
                                             INT64& week,
                                             DOUBLE& sec)
        {
            SStandardTime srcTimeData = {static_cast<UINT32>(year), static_cast<UINT32>(month),
                                         static_cast<UINT32>(day), static_cast<UINT32>(hour),
                                         static_cast<UINT32>(minute), second,
                                         static_cast<UINT32>(UTC)};
            IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(UTC);
            if (srcTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            srcTime->SetTime(srcTimeData);
            DOUBLE curSec = 0.0;
            srcTime->GetTime(curSec);
            DOUBLE retSec = CCalcTime::TimeConvert(curSec, UTC, static_cast<TIME_TYPE>(timeType));
            IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
            if (destTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            destTime->SetTime(retSec);
            SGNSSTime destTimeData;
            destTime->GetTime(destTimeData);
            week = static_cast<INT32>(destTimeData.m_week);
            sec = destTimeData.m_secAndMsec;
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::UTCTimeToGNSSSecTime(const INT32 year,
                                                const INT32 month,
                                                const INT32 day,
                                                const INT32 hour,
                                                const INT32 minute,
                                                const DOUBLE second,
                                                const INT32 timeType,
                                                DOUBLE& sec)
        {
            SStandardTime srcTimeData = {static_cast<UINT32>(year), static_cast<UINT32>(month),
                                         static_cast<UINT32>(day), static_cast<UINT32>(hour),
                                         static_cast<UINT32>(minute), second,
                                         static_cast<UINT32>(UTC)};
            IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(UTC);
            if (srcTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            srcTime->SetTime(srcTimeData);
            DOUBLE curSec = 0.0;
            srcTime->GetTime(curSec);
            DOUBLE retSec = CCalcTime::TimeConvert(curSec, UTC, static_cast<TIME_TYPE>(timeType));
            IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
            if (destTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            destTime->SetTime(retSec);
            destTime->GetTime(sec);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::WeekSecToSec(const INT64 week, const DOUBLE second, const INT32 timeType, DOUBLE& sec)
        {
            IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
            SGNSSTime timeData = {week, second, static_cast<UINT32>(timeType)};
            timeObj->SetTime(timeData);
            timeObj->GetTime(sec);
            return RETURN_SUCCESS;
        }

        // GUL_UC_010
        INT32 CAppInterface::UTCTimeToGlonassTime(const INT32 utcYear,
                                                const INT32 utcMonth,
                                                const INT32 utcDay,
                                                const INT32 utcHour,
                                                const INT32 utcMinute,
                                                const DOUBLE utcSecond,
                                                INT32 &gloYear,
                                                INT32 &gloMonth,
                                                INT32 &gloDay,
                                                INT32 &gloHour,
                                                INT32 &gloMinute,
                                                DOUBLE &gloSecond)
        {
            SStandardTime srcTimeData = {static_cast<UINT32>(utcYear), static_cast<UINT32>(utcMonth),
                                         static_cast<UINT32>(utcDay), static_cast<UINT32>(utcHour),
                                         static_cast<UINT32>(utcMinute), utcSecond,
                                         static_cast<UINT32>(UTC)};
            IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(UTC);
            if (srcTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            srcTime->SetTime(srcTimeData);
            DOUBLE curSec = 0.0;
            srcTime->GetTime(curSec);
            DOUBLE retSec = CCalcTime::TimeConvert(curSec, UTC, GLONASS);
            IGNSSTime* destTime = CTimeFactory::CreateTimeObj(GLONASS);
            if (destTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            destTime->SetTime(retSec);
            SStandardTime destTimeData;
            destTime->GetTime(destTimeData);
            gloYear = static_cast<INT32>(destTimeData.m_year);
            gloMonth = static_cast<INT32>(destTimeData.m_month);
            gloDay = static_cast<INT32>(destTimeData.m_day);
            gloHour = static_cast<INT32>(destTimeData.m_hour);
            gloMinute = static_cast<INT32>(destTimeData.m_minute);
            gloSecond = destTimeData.m_second;
            return RETURN_SUCCESS;
        }

        // GUL_UC_013  GUL_UC_015 GUL_UC_016  GUL_UC_018
        INT32 CAppInterface::GNSSTimeConvert(const INT64 srcWeek,
                                           const DOUBLE srcSec,
                                           const INT32 srcTimeType,
                                           INT64& destWeek,
                                           DOUBLE& destSec,
                                           const INT32 destTimeType)
        {
            SGNSSTime srcTimeData = {srcWeek, srcSec, static_cast<UINT32>(srcTimeType)};
            IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(srcTimeType));
            if (srcTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            srcTime->SetTime(srcTimeData);
            DOUBLE curSec = 0.0;
            srcTime->GetTime(curSec);
            DOUBLE retSec = CCalcTime::TimeConvert(curSec, static_cast<TIME_TYPE>(srcTimeType),
                                                   static_cast<TIME_TYPE>(destTimeType));
            IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(destTimeType));
            if (destTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            destTime->SetTime(retSec);
            SGNSSTime destTimeData;
            destTime->GetTime(destTimeData);
            destWeek = destTimeData.m_week;
            destSec = destTimeData.m_secAndMsec;
            return RETURN_SUCCESS;
        }

        // GUL_UC_014
        INT32 CAppInterface::GlonassTimeToGPSTime(const INT32 year,
                                                const INT32 month,
                                                const INT32 day,
                                                const INT32 hour,
                                                const INT32 minute,
                                                const DOUBLE second,
                                                INT64& week,
                                                DOUBLE& sec)
        {
            SStandardTime srcTimeData = {static_cast<UINT32>(year), static_cast<UINT32>(month),
                                     static_cast<UINT32>(day), static_cast<UINT32>(hour),
                                     static_cast<UINT32>(minute), second,
                                     static_cast<UINT32>(GLONASS)};
            IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(GLONASS);
            if (srcTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            srcTime->SetTime(srcTimeData);
            DOUBLE curSec = 0.0;
            srcTime->GetTime(curSec);
            DOUBLE retSec = CCalcTime::TimeConvert(curSec, GLONASS, GPS);
            IGNSSTime* destTime = CTimeFactory::CreateTimeObj(GPS);
            if (destTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            destTime->SetTime(retSec);
            SGNSSTime destTimeData;
            destTime->GetTime(destTimeData);
            week = destTimeData.m_week;
            sec = destTimeData.m_secAndMsec;
            return RETURN_SUCCESS;
        }

        // GUL_UC_017
        INT32 CAppInterface::GPSTimeToGlonassTime(
            const INT64 week, const DOUBLE second, INT32& year, INT32& month, INT32& day, INT32& hour, INT32& minute, DOUBLE& sec)
        {
            SGNSSTime srcTimeData = {week, sec, static_cast<UINT32>(GPS)};
            IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(GPS);
            if (srcTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            srcTime->SetTime(srcTimeData);
            DOUBLE curSec = 0.0;
            srcTime->GetTime(curSec);
            DOUBLE retSec = CCalcTime::TimeConvert(curSec, GPS, GLONASS);
            IGNSSTime* destTime = CTimeFactory::CreateTimeObj(GLONASS);
            if (destTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            destTime->SetTime(retSec);
            SStandardTime destTimeData;
            destTime->GetTime(destTimeData);
            year = static_cast<INT32>(destTimeData.m_year);
            month = static_cast<INT32>(destTimeData.m_month);
            day = static_cast<INT32>(destTimeData.m_day);
            hour = static_cast<INT32>(destTimeData.m_hour);
            minute = static_cast<INT32>(destTimeData.m_minute);
            sec = destTimeData.m_second;
            return RETURN_SUCCESS;
        }

        int
        CAppInterface::XYZ2BLH(const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lon, DOUBLE& lat, DOUBLE& height)
        {
            return RETURN_SUCCESS;
        }

        int
        CAppInterface::BLH2XYZ(const DOUBLE lon, const DOUBLE lat, const DOUBLE height, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::XYZ2ENU(const DOUBLE curX,
                                   const DOUBLE curY,
                                   const DOUBLE curZ,
                                   const DOUBLE refX,
                                   const DOUBLE refY,
                                   const DOUBLE refZ,
                                   DOUBLE& east,
                                   DOUBLE& north,
                                   DOUBLE& up)
        {
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::ENU2XYZ(const DOUBLE east,
                                   const DOUBLE north,
                                   const DOUBLE up,
                                   const DOUBLE refX,
                                   const DOUBLE refY,
                                   const DOUBLE refZ,
                                   DOUBLE& curX,
                                   DOUBLE& curY,
                                   DOUBLE& curZ)
        {
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::CalcGlonassEphSatClock(const DOUBLE& sec, const SGlonassEphemeris& ephObj, DOUBLE& clockVal)
        {
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::CalcEphSatClock(const DOUBLE& sec, const SEphemeris& ephObj, DOUBLE& clockVal)
        {
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::CalcGlonassEphSatPos(
            const DOUBLE sec, const SGlonassEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::CalcEphSatPos(const DOUBLE sec, const SEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::FormatAngleByDegree(const DOUBLE degree, char* formatString, int& len, const bool formatType)
        {
            if (nullptr != formatString)
            {
                formatString = nullptr;
            }

            CGNSSAngle angleObj(degree);
            INT32 length = angleObj.GetLength(true);
            formatString = new char[length + 1];
            angleObj.ToDegString(formatString, length, formatType);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::FormatAngleByDMS(
            const INT32 degree, const INT32 minute, const DOUBLE sec, char* formatString, int& len, const bool formatType)
        {
            if (nullptr != formatString)
            {
                formatString = nullptr;
            }

            CGNSSAngle angleObj(degree, minute, sec);
            INT32 length = angleObj.GetLength(false);
            formatString = new char[length + 1];
            angleObj.ToDegString(formatString, length, formatType);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::Deg2Rad(const DOUBLE degree, DOUBLE& radian)
        {
            do
            {
                CGNSSAngle angleObj(degree);
                angleObj.DegToRad(degree, radian);
            } while (false);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::DMS2Rad(const INT32 degree, const INT32 minute, const DOUBLE sec, DOUBLE& radian)
        {
            do
            {
                DOUBLE DegToRad = 0;
                CGNSSAngle angleObj(degree, minute, sec);
                angleObj.DMSToDeg(degree, minute, sec, DegToRad);
                angleObj.DegToRad(DegToRad, radian);
            } while (false);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::Rad2Deg(const DOUBLE radian, DOUBLE& degree)
        {
            do
            {
                CGNSSAngle angleObj(degree, false);
                angleObj.RadToDeg(radian, degree);
            } while (false);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::Rad2DMS(const DOUBLE radian, int& degree, int& minute, DOUBLE& sec)
        {
            do
            {
                DOUBLE RadToDeg = 0;
                CGNSSAngle angleObj(radian, false);
                angleObj.RadToDeg(radian, RadToDeg);
                angleObj.DegToDMS(RadToDeg, degree, minute, sec);
            } while (false);
            return RETURN_SUCCESS;
        }
    } // namespace GNSSUtilityLib
} // namespace sixents