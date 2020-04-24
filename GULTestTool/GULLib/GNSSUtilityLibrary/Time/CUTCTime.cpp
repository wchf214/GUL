/** @file          CGPSTime.h
 *  @brief         GPS时间类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#include "CUTCTime.h"
#include <iomanip>
#include <sstream>

namespace sixents
{
    namespace GNSSUtilityLib
    {
        CUTCTime::CUTCTime()
        {
            m_time.m_timeType = UTC;
        }

        CUTCTime::~CUTCTime()
        {}

        INT32 CUTCTime::Format(std::string& formatString)
        {
            std::stringstream formatStream("");

            formatStream << m_time.m_year << DAY_INTERVAL << m_time.m_month << DAY_INTERVAL << m_time.m_day << " "
                         << m_time.m_hour << TIME_INTERVAL << m_time.m_minute << TIME_INTERVAL << std::setprecision(3)
                         << m_time.m_second;
            formatString = formatStream.str();
            formatStream.str(""); // 清空缓存区
            return RETURN_SUCCESS;
        }

        DOUBLE CUTCTime::ToSec() const
        {
            return DOUBLE();
        }

        void CUTCTime::ToStandTime(SStandardTime& time) const
        {}

        void CUTCTime::SetTime(const DOUBLE& time)
        {}

        void CUTCTime::GetTime(DOUBLE& time) const
        {}

        void CUTCTime::SetTime(const SStandardTime& time)
        {}

        void CUTCTime::GetTime(SStandardTime& time) const
        {}
        // end class IGNSSTime
    } // end namespace GNSSUtilityLib
} // end namespace sixents
