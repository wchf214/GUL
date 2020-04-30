#include "AppInterface.h"
#include "../Angle/CGNSSAngle.h"
#include "../Coordinate/CGNSSCoord.h"
#include "../DllMain/GNSSCommonDef.h"
#include "../Ephemeris/CGNSSEphemeris.h"
#include "../Time/TimeCalc/CCalcTime.h"
#include "../Time/TimeSys/CTimeFactory.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        // GUL_UC_001 GUL_UC_003 GUL_UC_004
        INT32 CAppInterface::FormatWeekSecTime(
            const UINT64 week, const DOUBLE sec, const UINT32 timeType, CHAR* formatString, UINT32& len)
        {
            INT32 retNum = RETURN_FAIL;
            do
            {
                if (timeType <= 0)
                {
                    retNum = RETURN_TIME_TYPE_ERROR;
                    break;
                }
                IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
                if (timeObj == nullptr)
                {
                    retNum = RETURN_NEW_PTR_FAILED;
                    break;
                }
                SGNSSTime curTime = {week, sec, timeType};
                timeObj->SetTime(curTime);
                std::string timeStr("");
                timeObj->Format(timeStr);
                const UINT32 NULL_CHAR_LEN = 1;
                if (len != static_cast<UINT32>(timeStr.size()) + NULL_CHAR_LEN)
                {
                    len = static_cast<UINT32>(timeStr.size()) + NULL_CHAR_LEN;
                    retNum = RETURN_SUCCESS;
                    break;
                }
                if (formatString == nullptr)
                {
                    retNum = RETURN_NULL_PTR;
                    break;
                }
                memcpy_s(formatString, static_cast<rsize_t>(len), timeStr.c_str(), static_cast<rsize_t>(len));
                retNum = RETURN_SUCCESS;
            } while (false);
            return retNum;
        }

        // GUL_UC_002
        INT32 CAppInterface::FormatStandardTime(const UINT32 year,
                                                const UINT32 month,
                                                const UINT32 day,
                                                const UINT32 hour,
                                                const UINT32 minute,
                                                const DOUBLE second,
                                                CHAR* formatString,
                                                UINT32& len)
        {
            IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(UTC));
            if (timeObj == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            SStandardTime curTime = {year, month, day, hour, minute, second, UTC};
            timeObj->SetTime(curTime);
            std::string timeStr("");
            timeObj->Format(timeStr);
            const UINT32 NULL_CHAR_LEN = 1;
            if (len != static_cast<UINT32>(timeStr.size()) + NULL_CHAR_LEN)
            {
                len = static_cast<UINT32>(timeStr.size()) + NULL_CHAR_LEN;
                return RETURN_SUCCESS;
            }
            if (formatString == nullptr)
            {
                return RETURN_NULL_PTR;
            }
            memcpy_s(formatString, static_cast<rsize_t>(len), timeStr.c_str(), static_cast<rsize_t>(len));
            return RETURN_SUCCESS;
        }

        // GUL_UC_005 GUL_UC_007 GUL_UC_008
        INT32 CAppInterface::GNSSTimeToUTCTime(const UINT64 week,
                                               const DOUBLE sec,
                                               const UINT32 timeType,
                                               UINT32& year,
                                               UINT32& month,
                                               UINT32& day,
                                               UINT32& hour,
                                               UINT32& minute,
                                               DOUBLE& second)
        {
            SGNSSTime srcTimeData = {week, sec, timeType};
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
            year = destTimeData.m_year;
            month = destTimeData.m_month;
            day = destTimeData.m_day;
            hour = destTimeData.m_hour;
            minute = destTimeData.m_minute;
            second = destTimeData.m_second;
            return RETURN_SUCCESS;
        }

        // GUL_UC_006
        INT32 CAppInterface::GlonassTimeToUTCTime(const UINT32 gloYear,
                                                  const UINT32 gloMonth,
                                                  const UINT32 gloDay,
                                                  const UINT32 gloHour,
                                                  const UINT32 gloMinute,
                                                  const DOUBLE gloSecond,
                                                  UINT32& utcYear,
                                                  UINT32& utcMonth,
                                                  UINT32& utcDay,
                                                  UINT32& utcHour,
                                                  UINT32& utcMinute,
                                                  DOUBLE& utcSecond)
        {
            SStandardTime srcTimeData = {
                gloYear, gloMonth, gloDay, gloHour, gloMinute, gloSecond, static_cast<UINT32>(GLONASS)};
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
            utcYear = destTimeData.m_year;
            utcMonth = destTimeData.m_month;
            utcDay = destTimeData.m_day;
            utcHour = destTimeData.m_hour;
            utcMinute = destTimeData.m_minute;
            utcSecond = destTimeData.m_second;
            return RETURN_SUCCESS;
        }

        // GUL_UC_009 GUL_UC_011 GUL_UC_012
        INT32 CAppInterface::UTCTimeToGNSSTime(const UINT32 year,
                                               const UINT32 month,
                                               const UINT32 day,
                                               const UINT32 hour,
                                               const UINT32 minute,
                                               const DOUBLE second,
                                               const UINT32 timeType,
                                               UINT64& week,
                                               DOUBLE& sec)
        {
            DOUBLE tempSec = 0.0;
            UTCTimeToGNSSSecTime(year, month, day, hour, minute, second, timeType, tempSec);
            IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
            if (destTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            destTime->SetTime(tempSec);
            SGNSSTime destTimeData;
            destTime->GetTime(destTimeData);
            week = destTimeData.m_week;
            sec = destTimeData.m_secAndMsec;
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::UTCTimeToGNSSSecTime(const UINT32 year,
                                                  const UINT32 month,
                                                  const UINT32 day,
                                                  const UINT32 hour,
                                                  const UINT32 minute,
                                                  const DOUBLE second,
                                                  const UINT32 timeType,
                                                  DOUBLE& sec)
        {
            SStandardTime srcTimeData = {year, month, day, hour, minute, second, static_cast<UINT32>(UTC)};
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

        INT32 CAppInterface::WeekSecToSec(const UINT64 week, const DOUBLE second, const UINT32 timeType, DOUBLE& sec)
        {
            IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
            SGNSSTime timeData = {week, second, timeType};
            timeObj->SetTime(timeData);
            timeObj->GetTime(sec);
            return RETURN_SUCCESS;
        }

        // GUL_UC_010
        INT32 CAppInterface::UTCTimeToGlonassTime(const UINT32 utcYear,
                                                  const UINT32 utcMonth,
                                                  const UINT32 utcDay,
                                                  const UINT32 utcHour,
                                                  const UINT32 utcMinute,
                                                  const DOUBLE utcSecond,
                                                  UINT32& gloYear,
                                                  UINT32& gloMonth,
                                                  UINT32& gloDay,
                                                  UINT32& gloHour,
                                                  UINT32& gloMinute,
                                                  DOUBLE& gloSecond)
        {
            SStandardTime srcTimeData = {
                utcYear, utcMonth, utcDay, utcHour, utcMinute, utcSecond, static_cast<UINT32>(UTC)};
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
            gloYear = destTimeData.m_year;
            gloMonth = destTimeData.m_month;
            gloDay = destTimeData.m_day;
            gloHour = destTimeData.m_hour;
            gloMinute = destTimeData.m_minute;
            gloSecond = destTimeData.m_second;
            return RETURN_SUCCESS;
        }

        // GUL_UC_013  GUL_UC_015 GUL_UC_016  GUL_UC_018
        INT32 CAppInterface::GNSSTimeConvert(const UINT64 srcWeek,
                                             const DOUBLE srcSec,
                                             const UINT32 srcTimeType,
                                             UINT64& destWeek,
                                             DOUBLE& destSec,
                                             const UINT32 destTimeType)
        {
            SGNSSTime srcTimeData = {srcWeek, srcSec, srcTimeType};
            IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(srcTimeType));
            if (srcTime == nullptr)
            {
                return RETURN_NEW_PTR_FAILED;
            }
            srcTime->SetTime(srcTimeData);
            DOUBLE curSec = 0.0;
            srcTime->GetTime(curSec);
            DOUBLE retSec = CCalcTime::TimeConvert(
                curSec, static_cast<TIME_TYPE>(srcTimeType), static_cast<TIME_TYPE>(destTimeType));
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
        INT32 CAppInterface::GlonassTimeToGPSTime(const UINT32 year,
                                                  const UINT32 month,
                                                  const UINT32 day,
                                                  const UINT32 hour,
                                                  const UINT32 minute,
                                                  const DOUBLE second,
                                                  UINT64& week,
                                                  DOUBLE& sec)
        {
            SStandardTime srcTimeData = {year, month, day, hour, minute, second, static_cast<UINT32>(GLONASS)};
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
        INT32 CAppInterface::GPSTimeToGlonassTime(const UINT64 week,
                                                  const DOUBLE second,
                                                  UINT32& year,
                                                  UINT32& month,
                                                  UINT32& day,
                                                  UINT32& hour,
                                                  UINT32& minute,
                                                  DOUBLE& sec)
        {
            SGNSSTime srcTimeData = {week, second, static_cast<UINT32>(GPS)};
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
            year = destTimeData.m_year;
            month = destTimeData.m_month;
            day = destTimeData.m_day;
            hour = destTimeData.m_hour;
            minute = destTimeData.m_minute;
            sec = destTimeData.m_second;
            return RETURN_SUCCESS;
        }

        INT32
        CAppInterface::XYZ2BLH(const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lon, DOUBLE& lat, DOUBLE& height)
        {
            CGNSSCoord coord(x, y, z, 2);
            coord.XYZ2BLH(x, y, z, lon, lat, height, 1);
            return RETURN_SUCCESS;
        }

        INT32
        CAppInterface::BLH2XYZ(const DOUBLE lon, const DOUBLE lat, const DOUBLE height, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            CGNSSCoord coord(lon, lat, height, 2);
            coord.BLH2XYZ(lon, lat, height, x, y, z, 1);
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
            CGNSSCoord coord(curX, curY, curZ, 1);
            coord.XYZ2ENU(curX, curY, curZ, refX, refY, refZ, east, north, up);
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
            CGNSSCoord coord(curX, curY, curZ, 1);
            coord.ENU2XYZ(east, north, up, refX, refY, refZ, curX, curY, curZ);
            return RETURN_SUCCESS;
        }

        INT32
        CAppInterface::CalcGlonassEphSatClock(const DOUBLE& sec, const SGlonassEphemeris& ephObj, DOUBLE& clockVal)
        {
            CGNSSEphemeris gloGNSSEphemeris(ephObj);
            gloGNSSEphemeris.CalcGloEphSatClock(sec, ephObj, clockVal);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::CalcEphSatClock(const DOUBLE& sec, const SEphemeris& ephObj, DOUBLE& clockVal)
        {
            CGNSSEphemeris gnssEphemeris(ephObj);
            gnssEphemeris.CalcEphSatClock(sec, ephObj, clockVal);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::CalcGlonassEphSatPos(
            const DOUBLE sec, const SGlonassEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            CGNSSEphemeris gloGNSSEphemeris(ephObj);
            gloGNSSEphemeris.CalcGloEphSatPos(sec, ephObj, x, y, z);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::CalcEphSatPos(const DOUBLE sec, const SEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            CGNSSEphemeris gnssEphemeris(ephObj);
            gnssEphemeris.CalcEphSatPos(sec, ephObj, x, y, z);
            return RETURN_SUCCESS;
        }

        INT32
        CAppInterface::FormatAngleByDegree(const DOUBLE degree,
                                           CHAR* formatString,
                                           UINT32& len,
                                           const BOOL_T formatType)
        {
            if (nullptr != formatString)
            {
                formatString = nullptr;
            }

            CGNSSAngle angleObj(degree);
            UINT32 length = angleObj.GetLength(true);
            formatString = new CHAR[length + 1];
            angleObj.ToDegString(formatString, length, formatType);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::FormatAngleByDMS(const INT32 degree,
                                              const INT32 minute,
                                              const DOUBLE sec,
                                              CHAR* formatString,
                                              UINT32& len,
                                              const BOOL_T formatType)
        {
            if (nullptr != formatString)
            {
                formatString = nullptr;
            }

            CGNSSAngle angleObj(degree, minute, sec);
            UINT32 length = angleObj.GetLength(false);
            formatString = new CHAR[length + 1];
            angleObj.ToDegString(formatString, length, formatType);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::Deg2Rad(const DOUBLE degree, DOUBLE& radian)
        {
            CGNSSAngle angleObj(degree);
            radian = angleObj.GetRad();
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
            CGNSSAngle angleObj(radian, false);
            degree = angleObj.GetDeg();
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
