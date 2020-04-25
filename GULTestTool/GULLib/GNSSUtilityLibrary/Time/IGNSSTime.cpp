#include "IGNSSTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        IGNSSTime::IGNSSTime(const TIME_TYPE timeType)
        {
            m_timeType = timeType;
        }

        IGNSSTime::~IGNSSTime()
        {}

        void IGNSSTime::SetTime(const DOUBLE& time)
        {}

        void IGNSSTime::GetTime(DOUBLE& time) const
        {}

        void IGNSSTime::SetTime(const SStandardTime& time)
        {}

        void IGNSSTime::GetTime(SStandardTime& time) const
        {}

        void IGNSSTime::SetTime(const SGNSSTime& time)
        {}

        void IGNSSTime::GetTime(SGNSSTime& time) const
        {}

        void IGNSSTime::ToWeekSec(SGNSSTime& time) const
        {}

        INT32 IGNSSTime::GetTimeType()
        {
            return m_timeType;
        }

        INT32 IGNSSTime::StandTimeToSec(const SStandardTime &stdTime, DOUBLE &sec)
        {
            INT32 days = 0;
            DOUBLE stdTimeSec = 0.0;
            INT32 year = stdTime.m_year;
            INT32 mon = stdTime.m_month;
            INT32 day = stdTime.m_day;
            if ((year < EPOCHT0.m_year || year > CURRENT_MAX_YEAR) || (mon <= 0 || mon > MONTH_IN_YEAR))
            {
                sec = stdTimeSec;
                return RETURN_FAIL;
            }

            /* leap year if year%4==0 in 1901-2099 */
            INT32 dayOfLeapMonth = (year % 4 == 0 && mon >= 3) ? 1 : 0;
            days = (year - EPOCHT0.m_year) * DAY_IN_YEAR + (year - 1969) / 4 + DAY_OF_YEAR[mon - 1] + day - 2 + dayOfLeapMonth;
            sec = (int)floor(stdTime.m_second);
            m_time = (time_t)days * DAY_SEC + (int)m_hour * 3600 + (int)m_min * 60 + sec;
            return RETURN_SUCCESS;
        }

        INT32 IGNSSTime::SecToStandTime(const DOUBLE sec, SStandardTime &stdTime)
        {
            const int doy[] = { 1,32,60,91,121,152,182,213,244,274,305,335 };
            time_t time = { 0 };
            int days, sec, year = (int)m_epochTime[0], mon = (int)m_epochTime[1], day = (int)m_epochTime[2];
            if (year < 1970 || 2099 < year || mon < 1 || 12 < mon)
                return time;
            /* leap year if year%4==0 in 1901-2099 */
            days = (year - 1970) * 365 + (year - 1969) / 4 + doy[mon - 1] + day - 2 + (year % 4 == 0 && mon >= 3 ? 1 : 0);
            sec = (int)floor(m_epochTime[5]);
            time = (time_t)days * DAY_SEC + (int)m_epochTime[3] * 3600 + (int)m_epochTime[4] * 60 + sec;
            return RETURN_SUCCESS;
        }

    } // end namespace GNSSUtilityLib
} // end namespace sixents
