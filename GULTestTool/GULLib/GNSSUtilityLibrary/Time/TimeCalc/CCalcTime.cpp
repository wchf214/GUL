#include "CCalcTime.h"
#include <cmath>
#include "../TimeSys/CTimeFactory.h"

namespace sixents
{
    namespace Math
    {
        DOUBLE CCalcTime::TimeConvert(const DOUBLE srcSec, const TIME_TYPE srcTimeType, const TIME_TYPE destTimeType)
        {
            // UTC与其它时间互转
            DOUBLE retTime = 0.0;
            if (srcTimeType == GPS && destTimeType == UTC)
            { // GPS 转 UTC
                retTime = GPSTUTCConvert(srcSec, true);
            }
            else if (srcTimeType == GLONASS && destTimeType == UTC)
            { // GLONASS 转 UTC
                retTime = GLOTUTCConvert(srcSec, true);
            }
            else if (srcTimeType == GALILEO && destTimeType == UTC)
            { // GALILEO 转 UTC
                retTime = GSTUTCConvert(srcSec, true);
            }
            else if (srcTimeType == BDS && destTimeType == UTC)
            { // BDS 转 UTC
                retTime = BDTUTCConvert(srcSec, true);
            }

            else if (srcTimeType == UTC && destTimeType == GPS)
            { // UTC 转 GPS
                retTime = GPSTUTCConvert(srcSec, false);
            }
            else if (srcTimeType == UTC && destTimeType == GLONASS)
            { // UTC 转 GLONASS
                retTime = GLOTUTCConvert(srcSec, false);
            }
            else if (srcTimeType == UTC && destTimeType == GALILEO)
            { // UTC 转 GALILEO
                retTime = GSTUTCConvert(srcSec, false);
            }
            else if (srcTimeType == UTC && destTimeType == BDS)
            { // UTC 转 BDS
                retTime = BDTUTCConvert(srcSec, false);
            }

            else if (srcTimeType == GLONASS && destTimeType == GPS)
            { // GLONASS 转 GPS
                retTime = GLOTGPSTConvert(srcSec, true);
            }
            else if (srcTimeType == GALILEO && destTimeType == GPS)
            { // GALILEO 转 GPS
                retTime = GSTGPSTConvert(srcSec, true);
            }
            else if (srcTimeType == BDS && destTimeType == GPS)
            { // BDS 转 GPS
                retTime = BDTGPSTConvert(srcSec, true);
            }

            else if (srcTimeType == GPS && destTimeType == GLONASS)
            { // GPS 转 GLONASS
                retTime = GLOTGPSTConvert(srcSec, false);
            }
            else if (srcTimeType == GPS && destTimeType == GALILEO)
            { // GPS 转 GALILEO
                retTime = GSTGPSTConvert(srcSec, false);
            }
            else if (srcTimeType == GPS && destTimeType == BDS)
            { // GPS 转 BDS
                retTime = BDTGPSTConvert(srcSec, false);
            }
            return retTime;
        }

        DOUBLE CCalcTime::GPSTUTCConvert(const DOUBLE srcTime, const BOOL_T isUtc)
        {
            DOUBLE retTime = 0.0;
            INT64 retTimeSec = 0;
            const DOUBLE timeMSec = srcTime - static_cast<DOUBLE>(floor(srcTime));
            for (INT32 i = 0; GPS_LEAPSEC_INFO[i][0] > 0; ++i)
            {
                //依次加入不同的跳秒信息
                if (!isUtc)
                { // UTC to GPS
                    retTimeSec = static_cast<INT64>(srcTime) - static_cast<INT64>(GPS_LEAPSEC_INFO[i][NUM_SIX]);
                }
                else
                { // GPS to UTC
                    retTimeSec = static_cast<INT64>(srcTime) + static_cast<INT64>(GPS_LEAPSEC_INFO[i][NUM_SIX]);
                }

                const UINT32 year = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][0]);
                const UINT32 month = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][NUM_ONE]);
                const UINT32 day = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][NUM_TWO]);
                const UINT32 hour = 0;
                const UINT32 min = 0;
                const DOUBLE sec = 0.0;
                SStandardTime leapTime = {year, month, day, hour, min, sec, UTC};
                const DOUBLE leapTimeSec = IGNSSTime::StandTimeToSec(leapTime);
                if (static_cast<DOUBLE>(retTimeSec) - leapTimeSec >= 0.0) // 如果差大于等于0则表示为当前时间
                {
                    retTime = static_cast<DOUBLE>(retTimeSec) + timeMSec;
                    break;
                }
            }
            return retTime;
        }

        DOUBLE CCalcTime::GLOTUTCConvert(const DOUBLE srcTime, const BOOL_T isUtc)
        {
            DOUBLE retTime = 0.0;
            if (!isUtc)
            { // UTC to Glonass
                retTime = srcTime + static_cast<DOUBLE>(SEC_OF_3HOUR);
            }
            else
            { // Glonass to UTC
                retTime = srcTime - static_cast<DOUBLE>(SEC_OF_3HOUR);
            }
            return retTime;
        }

        DOUBLE CCalcTime::GSTUTCConvert(const DOUBLE srcTime, const BOOL_T isUtc)
        {
            DOUBLE retTime = 0.0;
            INT32 retTimeSec = 0;
            const DOUBLE timeMSec = srcTime - static_cast<DOUBLE>(floor(srcTime));
            for (INT32 i = 0; GPS_LEAPSEC_INFO[i][0] > 0; ++i)
            {
                //依次加入不同的跳秒信息
                if (!isUtc)
                { // UTC to Galileo
                    retTimeSec = static_cast<INT32>(srcTime) - static_cast<INT32>(GPS_LEAPSEC_INFO[i][NUM_SIX]);
                }
                else
                { // Galileo to UTC
                    retTimeSec = static_cast<INT32>(srcTime) + static_cast<INT32>(GPS_LEAPSEC_INFO[i][NUM_SIX]);
                }

                const UINT32 year = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][0]);
                const UINT32 month = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][NUM_ONE]);
                const UINT32 day = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][NUM_TWO]);
                const UINT32 hour = 0;
                const UINT32 min = 0;
                const DOUBLE sec = 0.0;
                SStandardTime leapTime = {year, month, day, hour, min, sec, UTC};
                DOUBLE leapTimeSec = IGNSSTime::StandTimeToSec(leapTime);
                if (static_cast<DOUBLE>(retTimeSec) - leapTimeSec >= 0.0) // 如果差大于等于0则表示为当前时间
                {
                    retTime = static_cast<DOUBLE>(retTimeSec) + timeMSec;
                    break;
                }
            }
            return retTime;
        }

        DOUBLE CCalcTime::BDTUTCConvert(const DOUBLE srcTime, const BOOL_T isUtc)
        {
            DOUBLE retTime = 0.0;
            INT32 retTimeSec = 0;
            const DOUBLE timeMSec = srcTime - static_cast<DOUBLE>(floor(srcTime));
            for (INT32 i = 0; BDS_LEAPSEC_INFO[i][0] > 0; ++i)
            {
                if (!isUtc)
                { // UTC to BDS
                    retTimeSec = static_cast<INT32>(srcTime) - static_cast<INT32>(BDS_LEAPSEC_INFO[i][NUM_SIX]);
                }
                else
                { // BDS to UTC
                    retTimeSec = static_cast<INT32>(srcTime) + static_cast<INT32>(BDS_LEAPSEC_INFO[i][NUM_SIX]);
                }

                const UINT32 year = static_cast<UINT32>(BDS_LEAPSEC_INFO[i][0]);
                const UINT32 month = static_cast<UINT32>(BDS_LEAPSEC_INFO[i][NUM_ONE]);
                const UINT32 day = static_cast<UINT32>(BDS_LEAPSEC_INFO[i][NUM_TWO]);
                const UINT32 hour = 0;
                const UINT32 min = 0;
                const DOUBLE sec = 0.0;
                SStandardTime leapTime = {year, month, day, hour, min, sec, UTC};
                DOUBLE leapTimeSec = IGNSSTime::StandTimeToSec(leapTime);
                if (static_cast<DOUBLE>(retTimeSec) - leapTimeSec >= 0.0)
                {
                    retTime = static_cast<DOUBLE>(retTimeSec) + timeMSec;
                    break;
                }
            }
            return retTime;
        }

        DOUBLE CCalcTime::BDTGPSTConvert(const DOUBLE srcTime, const BOOL_T isGps)
        {
            DOUBLE retTime = 0.0;
            if (!isGps)
            { // GPS To BDS
                retTime = srcTime - SEC_BETWEEN_GPS_BDS;
            }
            else
            { // BDS To GPS
                retTime = srcTime + SEC_BETWEEN_GPS_BDS;
            }
            return retTime;
        }

        DOUBLE CCalcTime::GLOTGPSTConvert(const DOUBLE srcTime, const BOOL_T isGps)
        {
            DOUBLE retTime = 0.0;
            if (!isGps)
            { // GPS To Glonass
                retTime = GPSTUTCConvert(srcTime, !isGps);
                retTime = GLOTUTCConvert(retTime, isGps);
            }
            else
            { // Glonass To GPS
                retTime = GLOTUTCConvert(srcTime, isGps);
                retTime = GPSTUTCConvert(retTime, !isGps);
            }
            return retTime;
        }

        DOUBLE CCalcTime::GSTGPSTConvert(const DOUBLE srcTime, const BOOL_T isGps)
        {
            UNREFERENCED_PARAMETER(isGps);
            return srcTime;
        }
    } // end namespace Math
} // end namespace sixents
