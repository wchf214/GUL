#include <iomanip>
#include <sstream>
#include "CBDSTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {

        CBDSTime::CBDSTime(const TIME_TYPE timeType)
            :IGNSSTime(timeType)
        {
            m_time.m_timeType = timeType;
            m_sec = 0.0;
        }

        CBDSTime::~CBDSTime()
        {}

        INT32 CBDSTime::Format(std::string& formatString)
        {
            std::stringstream formatStream("");
            formatStream.str("");
            SStandardTime curTime;
            ToStandTime(curTime);
            formatStream << curTime.m_year << DAY_INTERVAL << curTime.m_month << DAY_INTERVAL << curTime.m_day << " "
                         << curTime.m_hour << TIME_INTERVAL << curTime.m_minute << TIME_INTERVAL
                         << std::fixed << std::setprecision(MSEC_ACCURACY) << curTime.m_second;
            formatString = formatStream.str();
            formatStream.str(""); // 清空缓存
            return RETURN_SUCCESS;
        }

        void CBDSTime::ToSec()
        {
            m_sec = WeekSecToSec(m_time, EPOCH_TO_BDT0);
        }

        void CBDSTime::ToSec(DOUBLE &time)
        {
            time = WeekSecToSec(m_time, EPOCH_TO_BDT0);
        }

        void CBDSTime::ToStandTime(SStandardTime &time)
        {
            SecToStandTime(m_sec, time);
        }

        void CBDSTime::ToStandTime()
        {
        }

        void CBDSTime::ToWeekSec(SGNSSTime& time)
        {
            SecToWeekSec(m_sec, EPOCH_TO_BDT0, time);
        }

        void CBDSTime::SetTime(const DOUBLE& time)
        {
            m_sec = time;
            ToWeekSec(m_time);
        }

        void CBDSTime::GetTime(DOUBLE& time)
        {
            time = m_sec;
        }

        void CBDSTime::SetTime(const SGNSSTime& time)
        {
            m_time = std::move(time);
            ToSec();
        }

        void CBDSTime::GetTime(SGNSSTime& time)
        {
            time = std::move(m_time);
        }
    } // end namespace GNSSUtilityLib
} // end namespace sixents
