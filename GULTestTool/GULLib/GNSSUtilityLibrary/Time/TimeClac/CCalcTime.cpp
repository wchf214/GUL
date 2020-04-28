#include "CCalcTime.h"
//#include "CTimeLeapFactory.h"
#include "../TimeSys/CTimeFactory.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {

//        DOUBLE CCalcTime::TimeConvert(const DOUBLE srcSec, const TIME_TYPE srctimeType, const TIME_TYPE destTimeType)
//        {
////            DOUBLE leapSec = GetLeapTime(srctimeType);
//            ITimeLeap* timeLeapObj = nullptr;
//            if (srctimeType == UTC || destTimeType == UTC)
//            {
//                timeLeapObj = CTimeLeapFactory::Create
//            }
//            else if (srctimeType == GPS || destTimeType == GPS)
//            {

//            }
//            else
//            {
//                // 1、 ToUTC
//                // 2、 ToOther
//            }
//            DOUBLE leapSec = 0.0;
//            if (srctimeType == destTimeType)
//            {
//                return srcSec;
//            }
//            else if (srctimeType > destTimeType)
//            {
//                return srcSec - leapSec;
//            }
//            else
//            {
//                return srcSec + leapSec;
//            }
//        }
        DOUBLE CCalcTime::TimeConvert(const DOUBLE srcSec, const TIME_TYPE srctimeType, const TIME_TYPE destTimeType)
        {
            // UTC 与 其它时间互转
            DOUBLE retLeap = 0.0;
            if (srctimeType == GPS && destTimeType == UTC) {  // GPS 转 UTC
                retLeap = GPST2UTC(srcSec, true);
            } else if (srctimeType == GLONASS && destTimeType == UTC) {  // GLONASS 转 UTC
                retLeap = GLOT2UTC(srcSec, true);
            } else if (srctimeType == BDS && destTimeType == UTC) {  // BDS 转 UTC
                retLeap = BDT2UTC(srcSec, true);
            } else if (srctimeType == GALILEO && destTimeType == UTC) {  // GALILEO 转 UTC
                retLeap = GST2UTC(srcSec, true);
            } else if (srctimeType == UTC && destTimeType == GPS) {  // UTC 转 GPS
                retLeap = GPST2UTC(srcSec, false);
            } else if (srctimeType == UTC && destTimeType == GLONASS) {  // GPS 转 UTC
                retLeap = GLOT2UTC(srcSec, false);
            } else if (srctimeType == UTC && destTimeType == BDS) {  // GPS 转 UTC
                retLeap = BDT2UTC(srcSec, false);
            } else if (srctimeType == UTC && destTimeType == GALILEO) {  // GPS 转 UTC
                retLeap = GST2UTC(srcSec, false);
            } else if (srctimeType == GLONASS && destTimeType == GPS) {  // GPS 转 UTC
                retLeap = GLOT2GPST(srcSec, true);
            } else if (srctimeType == BDS && destTimeType == GPS) {  // GPS 转 UTC
                retLeap = BDT2GPST(srcSec, true);
            } else if (srctimeType == GALILEO && destTimeType == GPS) {  // GPS 转 UTC
                retLeap = GST2GPST(srcSec, true);
            } else if (srctimeType == GPS && destTimeType == GLONASS) {  // GPS 转 UTC
                retLeap = GLOT2GPST(srcSec, false);
            } else if (srctimeType == GPS && destTimeType == BDS) {  // GPS 转 UTC
                retLeap = BDT2GPST(srcSec, false);
            } else if (srctimeType == GPS && destTimeType == GALILEO) {  // GPS 转 UTC
                retLeap = GST2GPST(srcSec, false);
            }
            return retLeap;
        }

        DOUBLE CCalcTime::GPST2UTC(const DOUBLE srcTime, const BOOL_T isUtc)
        {
            DOUBLE retTime = 0.0;
            INT64 retTimeSec = 0;
            DOUBLE timeMSec = srcTime - static_cast<DOUBLE>(floor(srcTime));
            for (int i = 0; GPS_LEAPSEC_INFO[i][0] > 0; ++i)
            {
                //依次加入不同的跳秒信息
                if (!isUtc) {  // UTC to GPS
                    retTimeSec = static_cast<INT64>(srcTime) - static_cast<INT64>(GPS_LEAPSEC_INFO[i][NUM_SIX]);
                } else {  // GPS to UTC
                    retTimeSec = static_cast<INT64>(srcTime) + static_cast<INT64>(GPS_LEAPSEC_INFO[i][NUM_SIX]);
                }

                IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(UTC);
                UINT32 year = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][0]);
                UINT32 month = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][1]);
                UINT32 day = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][2]);
                UINT32 hour = 0;
                UINT32 min = 0;
                DOUBLE sec = 0.0;
                SStandardTime leapTime = {year, month, day, hour, min, sec, UTC};
                DOUBLE leapTimeSec = timeObj->StandTimeToSec(leapTime);
                if (static_cast<DOUBLE>(retTimeSec) - leapTimeSec >= 0.0) // 如果差大于等于0则表示为当前时间
                {
                    retTime = static_cast<DOUBLE>(retTimeSec) + timeMSec;
                    break;
                }
            }

            return retTime;
        }

        DOUBLE CCalcTime::GLOT2UTC(const DOUBLE srcTime, const BOOL_T isUtc)
        {
            DOUBLE retTime = 0.0;
            if (!isUtc) {  // UTC to Glonass
                retTime = srcTime + static_cast<DOUBLE>(SEC_OF_3HOUR);
            } else {  // Glonass to UTC
                retTime = srcTime - static_cast<DOUBLE>(SEC_OF_3HOUR);
            }
            return retTime;
        }

        DOUBLE CCalcTime::GST2UTC(const DOUBLE srcTime, const BOOL_T isUtc)
        {
            DOUBLE retTime = 0.0;
            INT32 retTimeSec = 0;
            DOUBLE timeMSec = srcTime - static_cast<DOUBLE>(floor(srcTime));
            for (int i = 0; GPS_LEAPSEC_INFO[i][0] > 0; ++i)
            {
                //依次加入不同的跳秒信息
                if (!isUtc) {  // UTC to Galileo
                    retTimeSec = static_cast<INT32>(srcTime) - static_cast<INT32>(GPS_LEAPSEC_INFO[i][NUM_SIX]);
                } else {   // Galileo to UTC
                    retTimeSec = static_cast<INT32>(srcTime) + static_cast<INT32>(GPS_LEAPSEC_INFO[i][NUM_SIX]);
                }

                IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(UTC);
                UINT32 year = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][0]);
                UINT32 month = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][1]);
                UINT32 day = static_cast<UINT32>(GPS_LEAPSEC_INFO[i][2]);
                UINT32 hour = 0;
                UINT32 min = 0;
                DOUBLE sec = 0.0;
                SStandardTime leapTime = {year, month, day, hour, min, sec, UTC};
                DOUBLE leapTimeSec = timeObj->StandTimeToSec(leapTime);
                if (static_cast<DOUBLE>(retTimeSec) - leapTimeSec >= 0.0) // 如果差大于等于0则表示为当前时间
                {
                    retTime = static_cast<DOUBLE>(retTimeSec) + timeMSec;
                    break;
                }
            }

            return retTime;
        }

        DOUBLE CCalcTime::BDT2UTC(const DOUBLE srcTime, const BOOL_T isUtc)
        {
            DOUBLE retTime = 0.0;
            INT32 retTimeSec = 0;
            DOUBLE timeMSec = srcTime - static_cast<DOUBLE>(floor(srcTime));
            for (int i = 0; BDS_LEAPSEC_INFO[i][0] > 0; ++i)
            {
                if (!isUtc) {  // UTC to BDS
                    retTimeSec = static_cast<INT32>(srcTime) - static_cast<INT32>(BDS_LEAPSEC_INFO[i][NUM_SIX]);
                } else {  // BDS to UTC
                    retTimeSec = static_cast<INT32>(srcTime) + static_cast<INT32>(BDS_LEAPSEC_INFO[i][NUM_SIX]);
                }

                IGNSSTime* timeObj = CTimeFactory::CreateTimeObj(UTC);
                UINT32 year = static_cast<UINT32>(BDS_LEAPSEC_INFO[i][0]);
                UINT32 month = static_cast<UINT32>(BDS_LEAPSEC_INFO[i][1]);
                UINT32 day = static_cast<UINT32>(BDS_LEAPSEC_INFO[i][2]);
                UINT32 hour = 0;
                UINT32 min = 0;
                DOUBLE sec = 0.0;
                SStandardTime leapTime = {year, month, day, hour, min, sec, UTC};
                DOUBLE leapTimeSec = timeObj->StandTimeToSec(leapTime);
                if (static_cast<DOUBLE>(retTimeSec) - leapTimeSec >= 0.0)
                {
                    retTime = static_cast<DOUBLE>(retTimeSec) + timeMSec;
                    break;
                }
            }
            return  retTime;
        }

        DOUBLE CCalcTime::BDT2GPST(const DOUBLE srcTime, const BOOL_T isGps)
        {
            DOUBLE retTime = 0.0;
            if (!isGps) {  // GPS To BDS
                retTime = srcTime - SEC_BETWEEN_GPS_BDS;
            } else { // BDS To GPS
                retTime = srcTime + SEC_BETWEEN_GPS_BDS;
            }
            return retTime;
        }

        DOUBLE CCalcTime::GLOT2GPST(const DOUBLE srcTime, const BOOL_T isGps)
        {
            DOUBLE retTime = 0.0;
            if (!isGps) { // GPS To Glonass
                retTime = GPST2UTC(srcTime, !isGps);
                retTime = GLOT2UTC(retTime, isGps);
            } else { // Glonass To GPS
                retTime = GLOT2UTC(srcTime, isGps);
                retTime = GPST2UTC(retTime, !isGps);
            }
            return  retTime;
        }

        DOUBLE CCalcTime::GST2GPST(const DOUBLE srcTime, const BOOL_T isGps)
        {
            return srcTime;
        }
    }      // end namespace GNSSUtilityLib
} // end namespace sixents
