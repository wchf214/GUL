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
            CGNSSTime(const int week, const double sec, const int satType = GPS);
            CGNSSTime(const SGNSSTime& time);
            CGNSSTime(const int year, const int month, const int day, const int hour, const int minute, const double sec);
            CGNSSTime(const int year, const int month, const int day, const int hour, const int minute, const double sec, const SAT_SYS_TYPE satType);
            CGNSSTime(const SStandardTime& time, const SAT_SYS_TYPE satType = GPS);
            CGNSSTime(const CGNSSTime& time);

            ~CGNSSTime();

            // format time and output string
            int StandardToString(SStandardTime m_standardTime, char* timeString, int& len);  // yyyy-MM-dd HH:mm:ss.sss
            int GNSSToString(char* timeString, int& len); // ***w,**.*****s
            int StandardTimeToGNSSTime(const SStandardTime& standardTime, SGNSSTime& gnssTime, const int satType);
            // transform standard time to GNSS time;

            int GNSSTimeConvert(const SGNSSTime& srcGnssTime, const int srcSatType, SGNSSTime& tarGnssTime, const int tarSatType);
            int GNSSTimeToStandardTime(const SGNSSTime& gnssTime, SStandardTime& standardTime, const int satType);
            int GNSSTimeToUTCTime(const SGNSSTime& gnssTime, SStandardTime& standardTime, const int satType);

            // overload operation
            CGNSSTime operator=(const CGNSSTime& time) const;
            bool operator==(const CGNSSTime& time) const;
            double operator-(const CGNSSTime& time) const;
            CGNSSTime operator+(const CGNSSTime& time) const;
            CGNSSTime operator-(const double& time) const;
            int operator>(const CGNSSTime& rTime) const;
            int operator>=(const CGNSSTime& rTime) const;

            SGNSSTime GetGNSSTime();
            SStandardTime GetStandardTime();

        private:
            SStandardTime m_standardTime;
            SGNSSTime m_gnssTime;
            std::string m_formatString;
            SAT_SYS_TYPE m_curSatType;

            int epoch2time(const double* ep);

            //GUL_UC_001
            int GPS2Time(SGNSSTime m_GNSSTime, SStandardTime& m_StandardTime);
            //GUL_UC_002
            int GLOT2Time(SGNSSTime m_GNSSTime, SStandardTime& m_StandardTime);
            //GUL_UC_003
            int GST2Time(SGNSSTime m_GNSSTime, SStandardTime& m_StandardTime);
            //GUL_UC_004
            int BDT2Time(SGNSSTime m_GNSSTime, SStandardTime& m_StandardTime);

            //GUL_UC_005
            int GPS2UTC(SGNSSTime m_GNSSTime, SStandardTime& m_UtcTime);
            //GUL_UC_006
            int GLOT2UTC(SGNSSTime m_GNSSTime, SStandardTime& m_UtcTime);
            //GUL_UC_007
            int GST2UTC(SGNSSTime m_GNSSTime, SStandardTime& m_UtcTime);
            //GUL_UC_008
            int BDT2UTC(SGNSSTime m_GNSSTime, SStandardTime& m_UtcTime);

            //GUL_UC_09
            int UTC2GPST(SStandardTime m_UtcTime, SGNSSTime& m_GNSSTime);
            //GUL_UC_010
            int UTC2GLOT(SStandardTime m_UtcTime, SGNSSTime& m_GNSSTime);
            //GUL_UC_011
            int UTC2GST(SStandardTime m_UtcTime, SGNSSTime& m_GNSSTime);
            //GUL_UC_012
            int UTC2BDT(SStandardTime m_UtcTime, SGNSSTime& m_GNSSTime);

            //GUL_UC_013
            int BDT2GPST(SGNSSTime m_SRCGNSSTime, SGNSSTime& m_GPSTime);
            //GUL_UC_014
            int GLOT2GPST(SGNSSTime m_SRCGNSSTime, SGNSSTime& m_GPSTime);
            //GUL_UC_015
            int GST2GPST(SGNSSTime m_SRCGNSSTime, SGNSSTime& m_GPSTime);

            //GUL_UC_016
            int GPST2BDT(SGNSSTime m_GPSTime, SGNSSTime& m_TARGNSSTime);
            //GUL_UC_017
            int GPST2GLOT(SGNSSTime m_GPSTime, SGNSSTime& m_TARGNSSTime);
            //GUL_UC_018
            int GPST2GST(SGNSSTime m_GPSTime, SGNSSTime& m_TARGNSSTime);
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents

#endif