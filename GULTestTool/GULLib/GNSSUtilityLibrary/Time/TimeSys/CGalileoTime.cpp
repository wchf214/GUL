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
#include "CGalileoTime.h"

namespace sixents
{
    namespace Math
    {

        CGalileoTime::CGalileoTime(const TIME_TYPE timeType)
            :IGNSSTime(timeType)
        {
            m_time.m_timeType = timeType;
            m_sec = 0.0;
        }

        CGalileoTime::~CGalileoTime()
        {

        }

        INT32 CGalileoTime::Format(std::string &formatString)
        {
            std::stringstream formatStream("");
            SStandardTime curTime;
            ToStandTime(curTime);
            formatStream << curTime.m_year << DAY_INTERVAL << curTime.m_month << DAY_INTERVAL << curTime.m_day << " "
                         << curTime.m_hour << TIME_INTERVAL << curTime.m_minute << TIME_INTERVAL
                         << std::fixed << std::setprecision(MSEC_ACCURACY) << curTime.m_second;
            formatString = formatStream.str();
            formatStream.str(""); // 清空缓存
            return RETURN_SUCCESS;
        }

        void CGalileoTime::ToSec()
        {
            m_sec = WeekSecToSec(m_time, EPOCH_TO_GALT0);
        }

        void CGalileoTime::ToSec(DOUBLE &time)
        {
            time = WeekSecToSec(m_time, EPOCH_TO_GALT0);
        }

        void CGalileoTime::ToStandTime()
        {

        }

        void CGalileoTime::ToStandTime(SStandardTime &time)
        {
            SecToStandTime(m_sec, time);
            time.m_timeType = GALILEO;
        }

        void CGalileoTime::ToWeekSec(SGNSSTime &time)
        {
            SecToWeekSec(m_sec, EPOCH_TO_GALT0, time);
            time.m_timeType = GALILEO;
        }

        void CGalileoTime::SetTime(const DOUBLE &time)
        {
            m_sec = time;
            ToWeekSec(m_time);
        }

        void CGalileoTime::GetTime(DOUBLE &time)
        {
            time = m_sec;
        }

        void CGalileoTime::SetTime(const SGNSSTime &time)
        {
            m_time = std::move(time);
            ToSec();
        }

        void CGalileoTime::GetTime(SGNSSTime &time)
        {
            time = std::move(m_time);
        }

    } // end namespace Math
} // end namespace sixents
