/**@file           CGNSSTime
 *  @brief         时间类
 *  @details       所有时间相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _GNSS_TIME_H
#define _GNSS_TIME_H

#include <string>
#include "../DllMain/GNSSCommonDef.h"
#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        class CGNSSTime
        {
        public:
            explicit CGNSSTime(const std::string timeString, const SAT_SYS_TYPE satType = GPS);
            CGNSSTime(const INT32 week, const DOUBLE sec, const INT32 satType = GPS);
            CGNSSTime(const SGNSSTime& time);
            CGNSSTime(const INT32 year, const INT32 month, const INT32 day, const INT32 hour, const INT32 minute, const DOUBLE sec);
            CGNSSTime(const INT32 year, const INT32 month, const INT32 day, const INT32 hour, const INT32 minute, const DOUBLE sec, const SAT_SYS_TYPE satType);
            CGNSSTime(const SStandardTime& time, const SAT_SYS_TYPE satType = GPS);
            CGNSSTime(const CGNSSTime& time);
            ~CGNSSTime();

            // format time and output string
            INT32 StandardTimeToString(SStandardTime standardTime, CHAR* timeString, INT32& len);  // yyyy-MM-dd HH:mm:ss.sss
            // INT32 GNSSToString(char* timeString, INT32& len); // ***w,**.*****s
            INT32 StandardTimeToGNSSTime(const SStandardTime& standardTime, SGNSSTime& gnssTime, const INT32 satType);
            // transform standard time to GNSS time;

            INT32 GNSSTimeConvert(const SGNSSTime& srcGNSSTime, const INT32 srcSatType, SGNSSTime& tarGNSSTime, const INT32 tarSatType);
            INT32 GNSSTimeToStandardTime(const SGNSSTime& gnssTime, SStandardTime& standardTime, const INT32 satType);
            INT32 GNSSTimeToUTCTime(const SGNSSTime& gnssTime, SStandardTime& standardTime, const INT32 satType);

            // overload operation
            CGNSSTime operator=(const CGNSSTime& time) const;
            bool operator==(const CGNSSTime& time) const;
            DOUBLE operator-(const CGNSSTime& time) const;
            CGNSSTime operator+(const CGNSSTime& time) const;
            CGNSSTime operator-(const DOUBLE& time) const;
            INT32 operator>(const CGNSSTime& rTime) const;
            INT32 operator>=(const CGNSSTime& rTime) const;

            SGNSSTime GetGNSSTime();
            SStandardTime GetStandardTime();

        public:
            SStandardTime m_standardTime;
            SGNSSTime m_gnssTime;
            std::string m_formatString;
            SAT_SYS_TYPE m_curSatType;

            INT32 Sec2EpochDataTime(UINT64 sec, INT32& year, INT32& month, INT32& day, INT32& hour, INT32& minute, DOUBLE& second);
            DOUBLE EpochDataTime2Sec(const DOUBLE* m_epochTime);

            DOUBLE EpochDataTime2Sec(INT32 year, INT32 month, INT32 day, INT32 hour, INT32 minute, DOUBLE second);

            //GUL_UC_001
            INT32 GPST2Time(SGNSSTime GNSSTime, SStandardTime& standardTime);
            //GUL_UC_002
            //这个函数不需要了
            //GUL_UC_003
            INT32 GST2Time(SGNSSTime GNSSTime, SStandardTime& standardTime);
            //GUL_UC_004
            INT32 BDT2Time(SGNSSTime GNSSTime, SStandardTime& standardTime);
            //GUL_UC_005
            INT32 GPST2UTC(SGNSSTime GNSSTime, SStandardTime& utcTime);
            //GUL_UC_006
            INT32 GLOT2UTC(SStandardTime GNSSTime, SStandardTime& utcTime);
            //GUL_UC_007
            INT32 GST2UTC(SGNSSTime GNSSTime, SStandardTime& utcTime);
            //GUL_UC_008
            INT32 BDT2UTC(SGNSSTime GNSSTime, SStandardTime& utcTime);

            //GUL_UC_09
            INT32 UTC2GPST(SStandardTime utcTime, SGNSSTime& GNSSTime);
            //GUL_UC_010
            INT32 UTC2GLOT(SStandardTime utcTime, SStandardTime& GNSSTime);
            //GUL_UC_011
            INT32 UTC2GST(SStandardTime utcTime, SGNSSTime& GNSSTime);
            //GUL_UC_012
            INT32 UTC2BDT(SStandardTime utcTime, SGNSSTime& GNSSTime);

            //GUL_UC_013
            INT32 BDT2GPST(SGNSSTime srcGNSSTime, SGNSSTime& GPSTime);
            //GUL_UC_014
            INT32 GLOT2GPST(SStandardTime srcGNSSTime, SGNSSTime& GPSTime);
            //GUL_UC_015
            INT32 GST2GPST(SGNSSTime srcGNSSTime, SGNSSTime& GPSTime);

            //GUL_UC_016
            INT32 GPST2BDT(SGNSSTime GPSTime, SGNSSTime& tarGNSSTime);
            //GUL_UC_017
            INT32 GPST2GLOT(SGNSSTime GPSTime, SStandardTime& tarGNSSTime);
            //GUL_UC_018
            INT32 GPST2GST(SGNSSTime GPSTime, SGNSSTime& tarGNSSTime);

            BOOL_T TimeConvert(const DOUBLE srcTime, const INT32 srcSatType, DOUBLE& destTime, const INT32 destSatType);
            INT32 WeekSecToSec(SGNSSTime srcTime, UINT64& tarSec);
            INT32 SecToWeekSec(DOUBLE srcSec, INT32 satType, SGNSSTime& tarTime);
            INT32 StandTimeToSec(SStandardTime srcTime, UINT64& tarSec);
            INT32 SecToStandTime(DOUBLE srcSec, SStandardTime& tarTime);
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents

#endif