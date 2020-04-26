/** @file          CGPSTime.h
 *  @brief         GPS时间类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#include <iomanip>
#include <sstream>
#include "CGPSTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        CGPSTime::CGPSTime(const TIME_TYPE timeType)
            : IGNSSTime(timeType)
        {
            m_time.m_timeType = timeType;
            m_sec = 0.0;
        }

        CGPSTime::~CGPSTime()
        {}

        INT32 CGPSTime::Format(std::string& formatString)
        {
            std::stringstream formatStream("");
            SStandardTime curTime;
            ToStandTime(curTime);
            formatStream << curTime.m_year << DAY_INTERVAL << curTime.m_month << DAY_INTERVAL << curTime.m_day << " "
                         << curTime.m_hour << TIME_INTERVAL << curTime.m_minute << TIME_INTERVAL
                         << std::setprecision(MSEC_ACCURACY) << curTime.m_second;
            formatString = formatStream.str();
            formatStream.str(""); // 清空缓存
            return RETURN_SUCCESS;
        }

        void CGPSTime::ToSec()
        {
            m_sec = WeekSecToSec(m_time, EPOCH_TO_GPST0);
        }

        void CGPSTime::ToSec(DOUBLE &time)
        {
            time = WeekSecToSec(m_time, EPOCH_TO_GPST0);
        }

        void CGPSTime::ToStandTime()
        {

        }

        void CGPSTime::ToStandTime(SStandardTime& time)
        {
            SecToStandTime(m_sec, time);
        }

        void CGPSTime::ToWeekSec(SGNSSTime& time)
        {
            SecToWeekSec(m_sec, EPOCH_TO_GPST0, time);
        }

        void CGPSTime::SetTime(const DOUBLE& time)
        {
            m_sec = time;
            ToWeekSec(m_time);
        }

        void CGPSTime::GetTime(DOUBLE& time)
        {
            time = m_sec;
        }

        void CGPSTime::SetTime(const SGNSSTime& time)
        {
            m_time = std::move(time);
            ToSec();
        }

        void CGPSTime::GetTime(SGNSSTime& time)
        {
            time = std::move(m_time);
        }
    } // end namespace GNSSUtilityLib
} // end namespace sixents
