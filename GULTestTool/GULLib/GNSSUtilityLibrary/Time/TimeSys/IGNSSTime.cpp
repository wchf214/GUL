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
        {
            UNREFERENCED_PARAMETER(time);
        }

        void IGNSSTime::GetTime(DOUBLE& time)
        {
            UNREFERENCED_PARAMETER(time);
        }

        void IGNSSTime::SetTime(const SStandardTime& time)
        {
            UNREFERENCED_PARAMETER(time);
        }

        void IGNSSTime::GetTime(SStandardTime& time)
        {
            UNREFERENCED_PARAMETER(time);
        }

        void IGNSSTime::SetTime(const SGNSSTime& time)
        {
            UNREFERENCED_PARAMETER(time);
        }

        void IGNSSTime::GetTime(SGNSSTime& time)
        {
            UNREFERENCED_PARAMETER(time);
        }

        void IGNSSTime::ToWeekSec(SGNSSTime& time)
        {
            UNREFERENCED_PARAMETER(time);
        }

        INT32 IGNSSTime::GetTimeType()
        {
            return m_timeType;
        }

        DOUBLE IGNSSTime::StandTimeToSec(const SStandardTime &stdTime)
        {
            DOUBLE retSec = 0.0;
            if ((stdTime.m_year < EPOCHT0.m_year || stdTime.m_year > CURRENT_MAX_YEAR) ||
                (stdTime.m_month <= 0 || stdTime.m_month > MONTH_IN_YEAR))
            {
                return retSec;
            }

            // 计算天数
            /* leap year if year%4==0 in 1901-2099 */
            const INT32 FEB_LEAP_DAY = 2;    // 每个月按30天算，2月多了两天。
            const INT32 MIN_MONTH_NUM = 3;
            const INT32 BEFORE_ONE_DATA = 1;  // 除当前年或月或日外，之前所有的年或月或日
            // 含当前年的年数，与1970相差多少年，并将年数转为天数
            INT32 curDayInYear = static_cast<INT32>((stdTime.m_year - EPOCHT0.m_year)) * DAY_IN_YEAR;
            // 除当前年以前的年数中存在的闰年年数
            INT32 leapYearCount =
                    static_cast<INT32>((stdTime.m_year - EPOCHT0.m_year - BEFORE_ONE_DATA)) / LEAP_YEAR_INTERVAL;
            // 当前月份之前所有月的天数
            INT32 curDayInMonth = DAY_OF_YEAR[stdTime.m_month - BEFORE_ONE_DATA];
            // 当前日期对应的天数 stdTime.m_day
            // 是闰年，且月份在3月以后的，此时2月份是29天，要减1天，否则减2天
            INT32 dayOfLeapMonth = 0;

            if (stdTime.m_year % LEAP_YEAR_INTERVAL == 0 && stdTime.m_month >= MIN_MONTH_NUM)
            {
                dayOfLeapMonth = BEFORE_ONE_DATA;
            }
            else
            {
                dayOfLeapMonth = FEB_LEAP_DAY;
            }

            INT32 allDay = curDayInYear + leapYearCount + curDayInMonth - dayOfLeapMonth;
            // 根据天数计算秒数
            retSec = static_cast<DOUBLE>(allDay * SEC_IN_DAY) + stdTime.m_hour * BASE_60 * BASE_60 +
                  stdTime.m_minute * BASE_60 + stdTime.m_second;
            return retSec;
        }

        INT32 IGNSSTime::SecToStandTime(const DOUBLE sec, SStandardTime &stdTime)
        {
            if (sec < DOUBLE_ZONE_LITTLE) {
                return RETURN_FAIL;
            }
            INT32 secOfIntegerPart = static_cast<INT32>(sec);  // 秒的整数部分
            DOUBLE secOfMsec = sec - static_cast<DOUBLE>(secOfIntegerPart);  // 毫秒

            /* leap year if year%4==0 in 1901-2099 */
            INT32 allDays = secOfIntegerPart / SEC_IN_DAY;  // 当前总天数
            UINT32 curSec = static_cast<UINT32>(secOfIntegerPart - allDays * SEC_IN_DAY); // 当前秒的整数部分

            // 计算日期
            INT32 day = allDays % DAY_IN_4YEAR; // 在4年中确定日期
            INT32 month = 0;
            while (month < MONTH_IN_4YRAR) {
                if (day >= DAY_IN_EACH_MON[month]) { // 天数大于当前月的天数，则说明不在当前月
                    day = day - DAY_IN_EACH_MON[month]; // 不在当前月，则将天数减当前月对应的天数
                    ++month;                            // 同时月数加1
                }else {   // 天数小于当前月，则说明日期在当前月中，同时也确定了月数
                    break;
                }
            }

            stdTime.m_year = EPOCHT0.m_year + static_cast<UINT32>(allDays / DAY_IN_4YEAR + month / MONTH_IN_YEAR);
            stdTime.m_month = static_cast<UINT32>(month % MONTH_IN_YEAR) + EPOCHT0.m_month;
            stdTime.m_day = static_cast<UINT32>(day) + EPOCHT0.m_day;
            stdTime.m_hour = curSec / (BASE_60 * BASE_60);
            stdTime.m_minute = curSec % (BASE_60 * BASE_60) / BASE_60;
            stdTime.m_second = static_cast<DOUBLE>(curSec % BASE_60) + secOfMsec;

            return RETURN_SUCCESS;
        }

        DOUBLE IGNSSTime::WeekSecToSec(const SGNSSTime &stdTime, const UINT64 startTime)
        {
            return static_cast<DOUBLE>(startTime) + stdTime.m_week * WEEK_SEC + stdTime.m_secAndMsec;
        }

        INT32 IGNSSTime::SecToWeekSec(const DOUBLE sec, const UINT64 startTime, SGNSSTime &stdTime)
        {
            DOUBLE curSec = sec - static_cast<DOUBLE>(startTime);
            stdTime.m_week = static_cast<INT64>(curSec) / WEEK_SEC;
            stdTime.m_secAndMsec = curSec - static_cast<DOUBLE>(stdTime.m_week * WEEK_SEC);
            return RETURN_SUCCESS;
        }
    } // end namespace GNSSUtilityLib
} // end namespace sixents
