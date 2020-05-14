#include "AppInterface.h"
#include <cstring>
#include <fstream>
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

                if (timeType != GPS && timeType != BDS && timeType != GALILEO)
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

                memcpy(formatString, timeStr.c_str(), static_cast<size_t>(len));
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
                if ((month == 0 || month > MONTH_IN_YEAR) || (day == 0 || day > MAX_DAY_IN_MONTH)
                    || (hour >= MAX_HOUR_IN_DAY) || (minute >= BASE_60) || (second < 0 || second > BASE_60))
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
                const UINT32 NULL_CHAR_LEN = 1;
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
                memcpy(formatString, timeStr.c_str(), static_cast<size_t>(len));
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
                // srcTimeType, destTimeType,判断
                if ((srcMonth == 0 || srcMonth > MONTH_IN_YEAR) || (srcDay == 0 || srcDay > MAX_DAY_IN_MONTH)
                    || (srcHour >= MAX_HOUR_IN_DAY) || (srcMinute >= BASE_60) || (srcSecond < 0 || srcSecond > BASE_60))
                {
                    retVal = RETURN_ERROR_STANDARDTIME;
                    break;
                }

                if (srcTimeType != UTC && srcTimeType != GLONASS)
                {
                    retVal = RETURN_TIME_TYPE_ERROR;
                    break;
                }

                if (destTimeType != UTC && destTimeType != GLONASS)
                {
                    retVal = RETURN_TIME_TYPE_ERROR;
                    break;
                }

                if (srcTimeType == destTimeType)
                {
                    retVal = RETURN_TIME_TYPE_ERROR;
                    break;
                }

                // todo:缺闰月判断

                SStandardTime srcTimeData = {srcYear, srcMonth, srcDay, srcHour, srcMinute, srcSecond, srcTimeType};
                IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(srcTimeType));
                IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(destTimeType));
                if (srcTime == nullptr || destTime == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }
                srcTime->SetTime(srcTimeData);
                DOUBLE curSec = 0.0;
                srcTime->GetTime(curSec);
                DOUBLE retSec = CCalcTime::TimeConvert(
                    curSec, static_cast<TIME_TYPE>(srcTimeType), static_cast<TIME_TYPE>(destTimeType));

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
                // srcTimeType, destTimeType,判断
                if (second < 0 || second >= WEEK_SEC)
                {
                    retVal = RETURN_ERROR_PARAMETER;
                    break;
                }

                if (gnssTimeType != GPS && gnssTimeType != GALILEO && gnssTimeType != BDS)
                {
                    retVal = RETURN_TIME_TYPE_ERROR;
                    break;
                }

                if (standardTimeType != UTC && standardTimeType != GLONASS)
                {
                    retVal = RETURN_TIME_TYPE_ERROR;
                    break;
                }

                SGNSSTime srcTimeData = {week, second, gnssTimeType};
                IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(gnssTimeType));
                IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(standardTimeType));

                if (srcTime == nullptr || destTime == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }
                srcTime->SetTime(srcTimeData);
                DOUBLE curSec = 0.0;
                srcTime->GetTime(curSec);
                DOUBLE retSec = CCalcTime::TimeConvert(
                    curSec, static_cast<TIME_TYPE>(gnssTimeType), static_cast<TIME_TYPE>(standardTimeType));

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
                                                    const UINT32 standardTimeType,
                                                    const UINT32 gnssTimeType,
                                                    UINT64& week,
                                                    DOUBLE& sec)
        {
            INT32 retVal = RETURN_FAIL;
            do
            {
                // srcTimeType, destTimeType,判断
                if ((month == 0 || month > MONTH_IN_YEAR) || (day == 0 || day > MAX_DAY_IN_MONTH)
                    || (hour >= MAX_HOUR_IN_DAY) || (minute >= BASE_60) || (second < 0 || second > BASE_60))
                {
                    retVal = RETURN_ERROR_STANDARDTIME;
                    break;
                }

                if (standardTimeType != UTC && standardTimeType != GLONASS)
                {
                    retVal = RETURN_TIME_TYPE_ERROR;
                    break;
                }

                if (gnssTimeType != GPS && gnssTimeType != GALILEO && gnssTimeType != BDS)
                {
                    retVal = RETURN_TIME_TYPE_ERROR;
                    break;
                }

                SStandardTime srcTimeData = {year, month, day, hour, minute, second, standardTimeType};
                IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(standardTimeType));
                IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(gnssTimeType));

                if (srcTime == nullptr || destTime == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }
                srcTime->SetTime(srcTimeData);
                DOUBLE curSec = 0.0;
                srcTime->GetTime(curSec);
                DOUBLE retSec = CCalcTime::TimeConvert(
                    curSec, static_cast<TIME_TYPE>(standardTimeType), static_cast<TIME_TYPE>(gnssTimeType));

                // retSec <0判断

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
                                             const UINT32 destTimeType,
                                             UINT64& destWeek,
                                             DOUBLE& destSec)
        {
            INT32 retVal = RETURN_FAIL;
            do
            {
                if (srcSec < 0 || srcSec >= WEEK_SEC)
                {
                    retVal = RETURN_ERROR_PARAMETER;
                    break;
                }

                if (srcTimeType != GPS && srcTimeType != GALILEO && srcTimeType != BDS)
                {
                    retVal = RETURN_TIME_TYPE_ERROR;
                    break;
                }
                if (destTimeType != GPS && destTimeType != GALILEO && destTimeType != BDS)
                {
                    retVal = RETURN_TIME_TYPE_ERROR;
                    break;
                }

                SGNSSTime srcTimeData = {srcWeek, srcSec, srcTimeType};
                IGNSSTime* srcTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(srcTimeType));

                IGNSSTime* destTime = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(destTimeType));
                if (srcTime == nullptr || destTime == nullptr)
                {
                    retVal = RETURN_NEW_PTR_FAILED;
                    break;
                }
                srcTime->SetTime(srcTimeData);
                DOUBLE curSec = 0.0;
                srcTime->GetTime(curSec);
                DOUBLE retSec = CCalcTime::TimeConvert(
                    curSec, static_cast<TIME_TYPE>(srcTimeType), static_cast<TIME_TYPE>(destTimeType));

                destTime->SetTime(retSec);
                SGNSSTime destTimeData;
                destTime->GetTime(destTimeData);
                if (destTimeData.m_week < 0 || destTimeData.m_secAndMsec < 0)
                {
                    retVal = RETURN_ERROR_PARAMETER;
                    break;
                }
                destWeek = destTimeData.m_week;
                destSec = destTimeData.m_secAndMsec;
                retVal = RETURN_SUCCESS;
            } while (false);
            return retVal;
        }

        INT32 CAppInterface::WeekSecToSec(const UINT64 week, const DOUBLE second, const UINT32 timeType, DOUBLE& sec)
        {
            INT32 retVal = RETURN_FAIL;
            do
            {
                if (second < 0 || second >= WEEK_SEC)
                {
                    retVal = RETURN_ERROR_PARAMETER;
                    break;
                }

                IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
                SGNSSTime timeData = {week, second, timeType};
                timeObj->SetTime(timeData);
                timeObj->GetTime(sec);
                retVal = RETURN_SUCCESS;
            } while (false);
            return retVal;
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
                IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(static_cast<TIME_TYPE>(timeType));
                SStandardTime timeData = {year, month, day, hour, minute, second, timeType};
                sec = timeObj->StandTimeToSec(timeData);
                retVal = RETURN_SUCCESS;
            } while (false);
            return retVal;
        }

        INT32
        CAppInterface::XYZ2BLH(const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lat, DOUBLE& lon, DOUBLE& height)
        {
            CGNSSCoordinate coordinate;
            coordinate.XYZ2BLH(x, y, z, lat, lon, height);
            return RETURN_SUCCESS;
        }

        INT32
        CAppInterface::BLH2XYZ(const DOUBLE lat, const DOUBLE lon, const DOUBLE height, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            //纬度超限-90~90 经度超限-180~180
            if (lat > LATITUDE_UPPER_LIMIT || lat < LATITUDE_LOWER_LIMIT || lon > LONGITUDE_UPPER_LIMIT
                || lon < LONGITUDE_LOWER_LIMIT)
            {
                return RETURN_ERROR_PARAMETER;
            }

            CGNSSCoordinate coordinate;
            coordinate.BLH2XYZ(lat, lon, height, x, y, z);
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
            CGNSSCoordinate coordinate;
            coordinate.XYZ2ENU(curX, curY, curZ, refX, refY, refZ, east, north, up);
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
            CGNSSCoordinate coordinate;
            coordinate.ENU2XYZ(east, north, up, refX, refY, refZ, curX, curY, curZ);
            return RETURN_SUCCESS;
        }

        INT32
        CAppInterface::CalcGlonassEphSatClock(const DOUBLE& sec, const SGlonassEphemeris& ephObj, DOUBLE& clockVal)
        {
            CGNSSEphemeris gloGNSSEphemeris;
            gloGNSSEphemeris.CalcGloEphSatClock(sec, ephObj, clockVal);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::CalcEphSatClock(const DOUBLE& sec, const SEphemeris& ephObj, DOUBLE& clockVal)
        {
            CGNSSEphemeris gnssEphemeris;
            gnssEphemeris.CalcEphSatClock(sec, ephObj, clockVal);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::CalcGlonassEphSatPos(
            const DOUBLE sec, const SGlonassEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            CGNSSEphemeris gloGNSSEphemeris;
            gloGNSSEphemeris.CalcGloEphSatPos(sec, ephObj, x, y, z);
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::CalcEphSatPos(const DOUBLE sec, const SEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            CGNSSEphemeris gnssEphemeris;
            gnssEphemeris.CalcEphSatPos(sec, ephObj, x, y, z);
            return RETURN_SUCCESS;
        }

        INT32
        CAppInterface::FormatAngleByDegree(const DOUBLE degree,
                                           CHAR* formatString,
                                           UINT32& len,
                                           const BOOL_T formatType)
        {
            INT32 retVal = RETURN_FAIL;
            do
            {
                std::string result = "";
                CGNSSAngle angleObj(degree);
                angleObj.DegToString(result, formatType);

                const UINT32 NULL_CHAR_LEN = 1;
                if (len != static_cast<UINT32>(result.size()) + NULL_CHAR_LEN)
                {
                    len = static_cast<UINT32>(result.size()) + NULL_CHAR_LEN;
                    retVal = RETURN_SUCCESS;
                    break;
                }

                if (formatString == nullptr)
                {
                    retVal = RETURN_NULL_PTR;
                    break;
                }

                memcpy(formatString, result.c_str(), static_cast<size_t>(len));
                retVal = RETURN_SUCCESS;
            } while (false);
            return retVal;
        }

        INT32 CAppInterface::FormatAngleByDMS(const INT32 degree,
                                              const UINT32 minute,
                                              const DOUBLE sec,
                                              CHAR* formatString,
                                              UINT32& len,
                                              const BOOL_T formatType)
        {
            INT32 retVal = RETURN_FAIL;
            do
            {
                if (sec < 0.0)
                {
                    retVal = RETURN_ERROR_PARAMETER;
                    break;
                }
                std::string result = "";
                CGNSSAngle angleObj(degree, minute, sec);
                angleObj.DegToString(result, formatType);

                const UINT32 NULL_CHAR_LEN = 1;
                if (len != static_cast<UINT32>(result.size()) + NULL_CHAR_LEN)
                {
                    len = static_cast<UINT32>(result.size()) + NULL_CHAR_LEN;
                    retVal = RETURN_SUCCESS;
                    break;
                }

                if (formatString == nullptr)
                {
                    retVal = RETURN_NULL_PTR;
                    break;
                }

                memcpy(formatString, result.c_str(), static_cast<size_t>(len));
                retVal = RETURN_SUCCESS;
            } while (false);
            return retVal;
        }

        INT32 CAppInterface::Deg2Rad(const DOUBLE degree, DOUBLE& radian)
        {
            radian = degree * D2R;
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::DMS2Rad(const INT32 degree, const UINT32 minute, const DOUBLE sec, DOUBLE& radian)
        {
            INT32 iRet = RETURN_FAIL;
            do
            {
                if (minute < 0 || minute >= BASE_60 || sec < 0 || sec >= BASE_60)
                {
                    iRet = RETURN_ERROR_PARAMETER;
                    break;
                }
                CGNSSAngle dms(degree, minute, sec);
                CAppInterface::Deg2Rad(dms.GetDeg(), radian);
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        INT32 CAppInterface::Rad2Deg(const DOUBLE radian, DOUBLE& degree)
        {
            degree = radian * R2D;
            return RETURN_SUCCESS;
        }

        INT32 CAppInterface::Rad2DMS(const DOUBLE radian, INT32& degree, UINT32& minute, DOUBLE& sec)
        {
            CGNSSAngle degreeObj(radian * R2D);
            degree = degreeObj.GetDMS().m_degree;
            minute = degreeObj.GetDMS().m_minute;
            sec = degreeObj.GetDMS().m_second;
            return RETURN_SUCCESS;
        }
    } // namespace Math
} // namespace sixents
