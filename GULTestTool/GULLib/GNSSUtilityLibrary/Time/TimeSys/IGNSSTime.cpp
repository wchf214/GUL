#include "IGNSSTime.h"

namespace sixents
{
    namespace Math
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

        UINT32 IGNSSTime::GetTimeType()
        {
            return m_timeType;
        }

        DOUBLE IGNSSTime::StandTimeToSec(const SStandardTime& stdTime)
        {
            DOUBLE retSec = 0.0;
            if ((stdTime.m_year < EPOCHT0.m_year || stdTime.m_year > CURRENT_MAX_YEAR)
             || (stdTime.m_month == 0 || stdTime.m_month > MONTH_IN_YEAR)
             || (stdTime.m_day == 0 || stdTime.m_day > MAX_DAY_IN_MONTH)
             || (stdTime.m_hour >= MAX_HOUR_IN_DAY) || (stdTime.m_minute >= BASE_60)
             || (stdTime.m_second < 0 || stdTime.m_second > BASE_60))
            {
                return retSec;
            }

            // 计算天数
            /* leap year if year%4==0 in 1901-2099 */
            const INT32 FEB_LEAP_DAY = NUM_TWO; // 每个月按30天算，2月多了两天。
            const INT32 MIN_MONTH_NUM = NUM_THREE;
            const INT32 BEFORE_ONE_DATA = NUM_ONE; // 除当前年或月或日外，之前所有的年或月或日
            // 含当前年的年数，与1970相差多少年，并将年数转为天数
            INT32 curDayInYear = static_cast<INT32>((stdTime.m_year - EPOCHT0.m_year)) * DAY_IN_YEAR;
            // 除当前年以前的年数中存在的闰年年数
            INT32 leapYearCount =
                static_cast<INT32>((stdTime.m_year - (EPOCHT0.m_year - BEFORE_ONE_DATA))) / LEAP_YEAR_INTERVAL;
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

            INT64 allDay =
                static_cast<INT64>(curDayInYear) + leapYearCount + curDayInMonth + stdTime.m_day - dayOfLeapMonth;
            // 根据天数计算秒数
            retSec = static_cast<DOUBLE>(allDay * SEC_IN_DAY) + stdTime.m_hour * BASE_60 * BASE_60
                     + stdTime.m_minute * BASE_60 + stdTime.m_second;
            return retSec;
        }

        INT32 IGNSSTime::SecToStandTime(const DOUBLE sec, SStandardTime& stdTime)
        {
            if (sec < DOUBLE_ZONE_LITTLE)
            {
                return RETURN_FAIL;
            }
            INT64 secOfIntegerPart = static_cast<INT64>(sec);               // 秒的整数部分
            DOUBLE secOfMsec = sec - static_cast<DOUBLE>(secOfIntegerPart); // 毫秒

            /* leap year if year%4==0 in 1901-2099 */
            INT64 allDays = secOfIntegerPart / SEC_IN_DAY;                              // 当前总天数
            INT64 curSec = static_cast<INT64>(secOfIntegerPart - allDays * SEC_IN_DAY); // 当前秒的整数部分

            // 计算日期
            INT64 day = allDays % DAY_IN_4YEAR; // 在4年中确定日期
            INT64 month = 0;
            while (month < MONTH_IN_4YRAR)
            {
                if (day >= DAY_IN_EACH_MON[month])
                {                                       // 天数大于当前月的天数，则说明不在当前月
                    day = day - DAY_IN_EACH_MON[month]; // 不在当前月，则将天数减当前月对应的天数
                    ++month;                            // 同时月数加1
                }
                else
                { // 天数小于当前月，则说明日期在当前月中，同时也确定了月数
                    break;
                }
            }
            stdTime.m_year = EPOCHT0.m_year
                             + static_cast<UINT32>(allDays / DAY_IN_4YEAR * LEAP_YEAR_INTERVAL + month / MONTH_IN_YEAR);
            stdTime.m_month = static_cast<UINT32>(month % MONTH_IN_YEAR) + EPOCHT0.m_month;
            stdTime.m_day = static_cast<UINT32>(day) + EPOCHT0.m_day;
            stdTime.m_hour = static_cast<UINT32>(curSec / (BASE_60 * BASE_60));
            stdTime.m_minute = curSec % (BASE_60 * BASE_60) / BASE_60;
            stdTime.m_second = static_cast<DOUBLE>(curSec % BASE_60) + secOfMsec;
            return RETURN_SUCCESS;
        }

        DOUBLE IGNSSTime::WeekSecToSec(const SGNSSTime& stdTime, const UINT64 startTime)
        {
            DOUBLE retTime =
                static_cast<DOUBLE>(startTime) + static_cast<DOUBLE>(stdTime.m_week) * WEEK_SEC + stdTime.m_secAndMsec;
            return retTime;
        }

        INT32 IGNSSTime::SecToWeekSec(const DOUBLE sec, const UINT64 startTime, SGNSSTime& stdTime)
        {
            DOUBLE curSec = sec - static_cast<DOUBLE>(startTime);
            if (curSec <= 0)
            {
                stdTime.m_week = 0;
                stdTime.m_secAndMsec = DOUBLE_ZONE_LITTLE;
            }
            else
            {
                stdTime.m_week = static_cast<UINT64>(curSec) / WEEK_SEC;
                stdTime.m_secAndMsec = curSec - static_cast<DOUBLE>(stdTime.m_week) * WEEK_SEC;
            }
            return RETURN_SUCCESS;
        }

        BOOL_T IGNSSTime::IsLeapYear(const UINT32 &time)
        {
            BOOL_T retVal = false;
            do
            {
                if (time < EPOCHT0.m_year || time > CURRENT_MAX_YEAR)
                {
                    break;
                }

                if (time % LEAP_YEAR_INTERVAL == 0 || time % CENTURY_LEAP_YEAR == 0)
                {
                    retVal = true;
                    break;
                }
            } while(false);
            return retVal;
        }

        UINT32 IGNSSTime::GetDayInFeb(const BOOL_T leapYear)
        {
            UINT32 retVal = DAY_IN_FEB;
            if (leapYear)
            {
                retVal = DAY_IN_LEAP_FEB;
            }
            return retVal;
        }

        MONTH_TYPE IGNSSTime::GetMonthType(const UINT32 &month)
        {
            const UINT32 NUM_TWO = 2;
            MONTH_TYPE retVal = MONTH_TYPE_NONE;
            do
            {
                if (month == 0 || month > MONTH_IN_YEAR)
                {
                    break;
                }

                if (month == NUM_TWO)
                {
                    break;
                }
                else if (month != MONTH_AUG && month % NUM_TWO == 0)
                {
                    retVal = SMALL_MONTH;
                    break;
                }
                else
                {
                    retVal = BIG_MONTH;
                }
            } while (false);
            return retVal;
        }
    } // end namespace Math
} // end namespace sixents
