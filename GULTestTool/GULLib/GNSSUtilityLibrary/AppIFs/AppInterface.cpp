#include "AppInterface.h"
#include "../Angle/CGNSSAngle.h"
#include "../Coordinate/CGNSSCoord.h"
#include "../DllMain/GNSSCommonDef.h"
#include "../Ephemeris/CGNSSEphemeris.h"
#include "../Time/TimeCalc/CCalcTime.h"
#include "../Time/TimeSys/CTimeFactory.h"

namespace sixents
{
    namespace Math
    {
        // GUL_UC_001 GUL_UC_003 GUL_UC_004
        INT32 CAppInterface::FormatWeekSecTime(
            const UINT64 week, const DOUBLE sec, const UINT32 timeType, CHAR* formatString, UINT32& len)
        {
            INT32 retVal = RETURN_FAIL;
            do
            {
                if (sec < 0 || sec >= WEEK_SEC)
                {
                    retVal = RETURN_ERROR_PARAMETER;
                    break;
                }

                if (timeType != GPS || timeType != BDS || timeType != GALILEO)
                {
                    retVal = RETURN_TIME_TYPE_ERROR;
                    break;
                }

                IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
                if (timeObj == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }

                SGNSSTime curTime = {week, sec, timeType};
                timeObj->SetTime(curTime);
                std::string timeStr("");
                timeObj->Format(timeStr);
                const UINT32 NULL_CHAR_LEN = 1;
                // 指针长度不匹配时，返回指针长度
                if (len != static_cast<UINT32>(timeStr.size()) + NULL_CHAR_LEN)
                {
                    len = static_cast<UINT32>(timeStr.size()) + NULL_CHAR_LEN;
                    retVal = RETURN_SUCCESS;
                    break;
                }

                if (formatString == nullptr)
                {
                    retVal = RETURN_NULL_PTR;
                    break;
                }

                memcpy_s(formatString, static_cast<rsize_t>(len), timeStr.c_str(), static_cast<rsize_t>(len));
                retVal = RETURN_SUCCESS;
            } while (false);
            return retVal;
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
            INT32 retVal = RETURN_FAIL;
            do
            {
                if ((month <= 0 || month > MONTH_IN_YEAR) || (day <= 0 || day > MAX_DAY_IN_MONTH)
                    || (hour < 0 || hour >= MAX_HOUR_IN_DAY) || (minute < 0 || minute >= BASE_60)
                    || (second < 0 || second > BASE_60))
                {
                    retVal = RETURN_ERROR_STANDARDTIME;
                    break;
                }

                // todo:缺闰月判断

                IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(UTC));
                if (timeObj == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }

                SStandardTime curTime = {year, month, day, hour, minute, second, UTC};
                timeObj->SetTime(curTime);
                std::string timeStr("");
                timeObj->Format(timeStr);
                const INT32 NULL_CHAR_LEN = 1;
                if (len != static_cast<INT32>(timeStr.size()) + NULL_CHAR_LEN)
                {
                    len = static_cast<INT32>(timeStr.size()) + NULL_CHAR_LEN;
                    retVal = RETURN_SUCCESS;
                    break;
                }

                if (formatString == nullptr)
                {
                    retVal = RETURN_NULL_PTR;
                    break;
                }
                memcpy_s(formatString, static_cast<rsize_t>(len), timeStr.c_str(), static_cast<rsize_t>(len));
                retVal = RETURN_SUCCESS;
            } while (false);
            return retVal;
        }

        // GUL_UC_006
        INT32 CAppInterface::StandardTimeConvert(const UINT32 srcYear,
                                                 const UINT32 srcMonth,
                                                 const UINT32 srcDay,
                                                 const UINT32 srcHour,
                                                 const UINT32 srcMinute,
                                                 const DOUBLE srcSecond,
                                                 const UINT32 srcTimeType,
                                                 const UINT32 destTimeType,
                                                 UINT32& destYear,
                                                 UINT32& destMonth,
                                                 UINT32& destDay,
                                                 UINT32& destHour,
                                                 UINT32& destMinute,
                                                 DOUBLE& destSecond)
        {
            INT32 retVal = RETURN_FAIL;
            do
            {
                if ((srcMonth <= 0 || srcMonth > MONTH_IN_YEAR) || (srcDay <= 0 || srcDay > MAX_DAY_IN_MONTH)
                    || (srcHour < 0 || srcHour >= MAX_HOUR_IN_DAY) || (srcMinute < 0 || srcMinute >= BASE_60)
                    || (srcSecond < 0 || srcSecond > BASE_60))
                {
                    retVal = RETURN_ERROR_STANDARDTIME;
                    break;
                }

                // todo:缺闰月判断

                SStandardTime srcTimeData = {srcYear, srcMonth, srcDay, srcHour, srcMinute, srcSecond, srcTimeType};
                IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(srcTimeType));
                if (srcTime == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }
                srcTime->SetTime(srcTimeData);
                DOUBLE curSec = 0.0;
                srcTime->GetTime(curSec);
                DOUBLE retSec = CCalcTime::TimeConvert(
                    curSec, static_cast<TIME_TYPE>(srcTimeType), static_cast<TIME_TYPE>(destTimeType));
                IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(destTimeType));
                if (destTime == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }
                destTime->SetTime(retSec);
                SStandardTime destTimeData;
                destTime->GetTime(destTimeData);
                destYear = destTimeData.m_year;
                destMonth = destTimeData.m_month;
                destDay = destTimeData.m_day;
                destHour = destTimeData.m_hour;
                destMinute = destTimeData.m_minute;
                destSecond = destTimeData.m_second;
                retVal = RETURN_SUCCESS;
            } while (false);
            return retVal;
        }

        // GUL_UC_005 GUL_UC_007 GUL_UC_008
        INT32 CAppInterface::GNSSTimeToStandardTime(const UINT64 week,
                                                    const DOUBLE second,
                                                    const UINT32 gnssTimeType,
                                                    const UINT32 standardTimeType,
                                                    UINT32& year,
                                                    UINT32& month,
                                                    UINT32& day,
                                                    UINT32& hour,
                                                    UINT32& minute,
                                                    DOUBLE& sec)
        {
            INT32 retVal = RETURN_FAIL;
            do
            {
                if (sec < 0 || sec >= WEEK_SEC)
                {
                    retVal = RETURN_ERROR_PARAMETER;
                    break;
                }

                SGNSSTime srcTimeData = {week, second, gnssTimeType};
                IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(gnssTimeType));
                if (srcTime == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }
                srcTime->SetTime(srcTimeData);
                DOUBLE curSec = 0.0;
                srcTime->GetTime(curSec);
                DOUBLE retSec = CCalcTime::TimeConvert(
                    curSec, static_cast<TIME_TYPE>(gnssTimeType), static_cast<TIME_TYPE>(standardTimeType));
                IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(standardTimeType));
                if (destTime == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
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
                retVal = RETURN_SUCCESS;
            } while (false);
            return retVal;
        }

        // GUL_UC_009 GUL_UC_011 GUL_UC_012
        INT32 CAppInterface::StandardTimeToGNSSTime(const UINT32 year,
                                                    const UINT32 month,
                                                    const UINT32 day,
                                                    const UINT32 hour,
                                                    const UINT32 minute,
                                                    const DOUBLE second,
                                                    const UINT32 gnssTimeType,
                                                    const UINT32 standardTimeType,
                                                    UINT64& week,
                                                    DOUBLE& sec)
        {
            INT32 retVal = RETURN_FAIL;
            do
            {
                if ((month <= 0 || month > MONTH_IN_YEAR) || (day <= 0 || day > MAX_DAY_IN_MONTH)
                    || (hour < 0 || hour >= MAX_HOUR_IN_DAY) || (minute < 0 || minute >= BASE_60)
                    || (second < 0 || second > BASE_60))
                {
                    retVal = RETURN_ERROR_STANDARDTIME;
                    break;
                }
                SStandardTime srcTimeData = {year, month, day, hour, minute, second, standardTimeType};
                IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(standardTimeType));
                if (srcTime == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }
                srcTime->SetTime(srcTimeData);
                DOUBLE curSec = 0.0;
                srcTime->GetTime(curSec);
                DOUBLE retSec = CCalcTime::TimeConvert(
                    curSec, static_cast<TIME_TYPE>(standardTimeType), static_cast<TIME_TYPE>(gnssTimeType));
                IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(gnssTimeType));
                if (destTime == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }
                destTime->SetTime(retSec);
                SGNSSTime destTimeData;
                destTime->GetTime(destTimeData);
                week = destTimeData.m_week;
                sec = destTimeData.m_secAndMsec;
                retVal = RETURN_SUCCESS;
            } while (false);
            return retVal;
        }

        // GUL_UC_013  GUL_UC_015 GUL_UC_016  GUL_UC_018
        INT32 CAppInterface::GNSSTimeConvert(const UINT64 srcWeek,
                                             const DOUBLE srcSec,
                                             const UINT32 srcTimeType,
                                             UINT64& destWeek,
                                             DOUBLE& destSec,
                                             const UINT32 destTimeType)
        {
            if (srcSec < 0 || srcSec > WEEK_SEC)
            {
                return RETURN_ERROR_PARAMETER;
            }

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
            if (destWeek < 0 || destSec < 0)
            {
                return RETURN_ERROR_PARAMETER;
            }
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::WeekSecToSec(const UINT64 week, const DOUBLE second, const UINT32 timeType, DOUBLE& sec)
        {
            if (week < 0 || second < 0 || second > WEEK_SEC)
            {
                return RETURN_ERROR_PARAMETER;
            }

            IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
            SGNSSTime timeData = {week, second, timeType};
            timeObj->SetTime(timeData);
            timeObj->GetTime(sec);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::StandardTimeToSec(const UINT32 year,
                                               const UINT32 month,
                                               const UINT32 day,
                                               const UINT32 hour,
                                               const UINT32 minute,
                                               const DOUBLE second,
                                               const UINT32 timeType,
                                               DOUBLE& sec)
        {
            if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31 || hour < 0 || hour > 24 || minute < 0
                || minute > 60 || second < 0 || second > 60)
            {
                return RETURN_ERROR_STANDARDTIME;
            }
            IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
            SStandardTime timeData = {year, month, day, hour, minute, second, timeType};
            sec = timeObj->StandTimeToSec(timeData);
            return RETURN_SUCCESS;
        }

        INT32
        CAppInterface::XYZ2BLH(const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lon, DOUBLE& lat, DOUBLE& height)
        {
            CGNSSCoordinate coord(x, y, z, XYZ);
            coord.XYZ2BLH(x, y, z, lon, lat, height, WGS84);
            return RETURN_SUCCESS;
        }

        INT32
        CAppInterface::BLH2XYZ(const DOUBLE lon, const DOUBLE lat, const DOUBLE height, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            //经度超限-180~180
            if (lon > LONGITUDE_UPPER_LIMIT || lon < LONGITUDE_LOWER_LIMIT)
            {
                return RETURN_ERROR_PARAMETER;
            }
            //纬度超限-90~90
            if (lat > LATITUDE_UPPER_LIMIT || lat < LATITUDE_LOWER_LIMIT)
            {
                return RETURN_ERROR_PARAMETER;
            }
            CGNSSCoordinate coordinate(lon, lat, height, BLH);
            coordinate.BLH2XYZ(lon, lat, height, x, y, z, WGS84);
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
            CGNSSCoordinate coord(curX, curY, curZ, XYZ);
            coord.XYZ2ENU(curX, curY, curZ, refX, refY, refZ, east, north, up, WGS84);
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
            CGNSSCoordinate coord(curX, curY, curZ, XYZ);
            coord.ENU2XYZ(east, north, up, refX, refY, refZ, curX, curY, curZ, WGS84);
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
                                              const UINT32 minute,
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

        INT32 CAppInterface::DMS2Rad(const INT32 degree, const UINT32 minute, const DOUBLE sec, DOUBLE& radian)
        {
            DOUBLE DegToRad = 0;
            CGNSSAngle angleObj(degree, minute, sec);
            angleObj.DMSToDeg(degree, minute, sec, DegToRad);
            angleObj.DegToRad(DegToRad, radian);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::Rad2Deg(const DOUBLE radian, DOUBLE& degree)
        {
            CGNSSAngle angleObj(radian, false);
            degree = angleObj.GetDeg();
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::Rad2DMS(const DOUBLE radian, INT32& degree, UINT32& minute, DOUBLE& sec)
        {
            DOUBLE RadToDeg = 0;
            CGNSSAngle angleObj(radian, false);
            angleObj.RadToDeg(radian, RadToDeg);
            angleObj.DegToDMS(RadToDeg, degree, minute, sec);
            return RETURN_SUCCESS;
        }
    } // namespace Math
} // namespace sixents