/** @file          CGPSTime.h
 *  @brief         GPSʱ����
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#include <iomanip>
#include <sstream>
#include "CUTCTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        CUTCTime::CUTCTime(const TIME_TYPE timeType)
            :IGNSSTime(timeType)
        {
            m_time.m_timeType = timeType;
            m_sec = 0.0;
        }

        CUTCTime::~CUTCTime()
        {}

        INT32 CUTCTime::Format(std::string& formatString)
        {
            std::stringstream formatStream("");
            formatStream << m_time.m_year << DAY_INTERVAL << m_time.m_month << DAY_INTERVAL << m_time.m_day << " "
                         << m_time.m_hour << TIME_INTERVAL << m_time.m_minute << TIME_INTERVAL
                         << std::fixed << std::setprecision(MSEC_ACCURACY) << m_time.m_second;
            formatString = formatStream.str();
            formatStream.str(""); // 清空缓存
            return RETURN_SUCCESS;
        }

        void CUTCTime::ToSec()
        {
            m_sec = StandTimeToSec(m_time);
        }

        void CUTCTime::ToSec(DOUBLE &time)
        {
            time = StandTimeToSec(m_time);
        }

        void CUTCTime::ToStandTime(SStandardTime& time)
        {
            SecToStandTime(m_sec, time);
        }

        void CUTCTime::ToStandTime()
        {
            SecToStandTime(m_sec, m_time);
        }

        void CUTCTime::SetTime(const DOUBLE& time)
        {
            m_sec = time;
            ToStandTime();
        }

        void CUTCTime::GetTime(DOUBLE& time)
        {
            time = m_sec;
        }

        void CUTCTime::SetTime(const SStandardTime& time)
        {
            m_time = std::move(time);
            ToSec();
        }

        void CUTCTime::GetTime(SStandardTime& time)
        {
            time = std::move(m_time);
        }

        // end class IGNSSTime
    } // end namespace GNSSUtilityLib
} // end namespace sixents
