#include "CGNSSTime.h"
#include <iostream>

namespace sixents
{
    namespace GNSSUtilityLib
    {
        CGNSSTime::CGNSSTime(const std::string timeString, const SAT_SYS_TYPE satType)
        {}

        CGNSSTime::CGNSSTime(const INT32 week, const double sec, const INT32 satType)
        {
            m_gnssTime.m_week = week;
            m_gnssTime.m_secAndMsec = sec;
            m_gnssTime.m_timeType = satType;
        }

        CGNSSTime::CGNSSTime(const INT32 year,
                             const INT32 month,
                             const INT32 day,
                             const INT32 hour,
                             const INT32 minute,
                             const double sec)
        {
            m_standardTime.m_year = year;
            m_standardTime.m_month = month;
            m_standardTime.m_day = day;
            m_standardTime.m_hour = hour;
            m_standardTime.m_minute = minute;
            m_standardTime.m_second = sec;
        }

        SGNSSTime CGNSSTime::GetGNSSTime()
        {
            return m_gnssTime;
        }

        SStandardTime CGNSSTime::GetStandardTime()
        {
            return m_standardTime;
        }

        INT32 CGNSSTime::Sec2EpochDataTime(
            UINT64 sec, INT32& year, INT32& month, INT32& day, INT32& hour, INT32& minute, double& second)
        {
            do
            {
                const INT32 mday[] = {/* # of days in a month */
                                      31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28, 31, 30,
                                      31, 30, 31, 31, 30, 31, 30, 31, 31, 29, 31, 30, 31, 30, 31, 31,
                                      30, 31, 30, 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                DOUBLE milliSecond = sec - floor(sec);
                INT32 tempDays = 0;
                INT32 tempSec = 0;
                INT32 tempMon = 0;
                INT32 days = 0;
                /* leap year if year%4==0 in 1901-2099 */
                tempDays = static_cast<INT32>(sec / 86400);
                tempSec = static_cast<INT32>(sec - tempDays * 86400);
                for (days = tempDays % 1461, tempMon = 0; tempMon < 48; tempMon++)
                {
                    if (days >= mday[tempMon])
                        days -= mday[tempMon];
                    else
                        break;
                }
                year = 1970 + tempDays / 1461 * 4 + tempMon / 12;
                month = tempMon % 12 + 1;
                day = days + 1;
                hour = tempSec / 3600;
                minute = tempSec % 3600 / 60;
                second = tempSec % 60 + milliSecond;
            } while (false);
            return 1;
        }

        DOUBLE CGNSSTime::EpochDataTime2Sec(const DOUBLE* m_epochTime)
        {
            DOUBLE Sec = 0;
            const INT32 doy[] = {1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
            INT32 days = 0;
            INT32 sec = 0;
            INT32 year = static_cast<INT32>(m_epochTime[0]);
            INT32 mon = static_cast<INT32>(m_epochTime[1]);
            INT32 day = static_cast<INT32>(m_epochTime[2]);

            if (year < 1970 || 2099 < year || mon < 1 || 12 < mon)
                return 0;
            /* leap year if year%4==0 in 1901-2099 */
            days =
                (year - 1970) * 365 + (year - 1969) / 4 + doy[mon - 1] + day - 2 + (year % 4 == 0 && mon >= 3 ? 1 : 0);
            sec = static_cast<INT32>(m_epochTime[5]);
            Sec = static_cast<INT32>(days * DAY_SEC) + static_cast<INT32>(m_epochTime[3] * 3600)
                  + static_cast<INT32>(m_epochTime[4] * NUM_SIXTY) + sec;
            return Sec;
        }

        double CGNSSTime::EpochDataTime2Sec(INT32 year, INT32 month, INT32 day, INT32 hour, INT32 minute, double second)
        {
            DOUBLE Sec = 0;
            const INT32 doy[] = {1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
            INT32 days = 0;
            INT32 sec = 0;
            INT32 tempYear = static_cast<INT32>(year);
            INT32 tempMon = static_cast<INT32>(month);
            INT32 tempDay = static_cast<INT32>(day);

            if (tempYear < 1970 || 2099 < tempYear || tempMon < 1 || 12 < tempMon)
                return 0;
            /* leap year if year%4==0 in 1901-2099 */
            days = (tempYear - 1970) * 365 + (tempYear - 1969) / 4 + doy[tempMon - 1] + day - 2
                   + (tempYear % 4 == 0 && tempMon >= 3 ? 1 : 0);
            sec = static_cast<INT32>(second);
            Sec = static_cast<INT32>(days * DAY_SEC) + static_cast<INT32>(hour * 3600)
                  + static_cast<INT32>(minute * NUM_SIXTY) + sec;
            return Sec;
        }

        INT32 CGNSSTime::StandardTimeToString(SStandardTime standardTime, char* timeString, INT32& len)
        {
            do
            {
                //字符串拼接
                std::string year = std::to_string(standardTime.m_year) + "-";
                std::string month = std::to_string(standardTime.m_month) + "-";
                std::string day = std::to_string(standardTime.m_day) + " ";
                std::string hour = std::to_string(standardTime.m_hour) + ":";
                std::string minute = std::to_string(standardTime.m_minute) + ":";
                std::string second = std::to_string(standardTime.m_second);
                std::string outputTime = year + month + day + hour + minute + second;

                INT32 dataBufLen = strlen(outputTime.c_str()) + 1;
                if (timeString == nullptr || len == 0 || len != dataBufLen)
                {
                    len = dataBufLen;
                    return RETURN_FAIL;
                }
                strcpy_s(timeString, dataBufLen, outputTime.c_str());
            } while (false);
            return 1;
        }

        INT32
        CGNSSTime::GNSSTimeToStandardTime(const SGNSSTime& gnssTime, SStandardTime& standardTime, const INT32 satType)
        {
            do
            {
                if (satType == GPS)
                {
                    GPST2Time(gnssTime, standardTime);
                }
                else if (satType == GALILEO)
                {
                    GST2Time(gnssTime, standardTime);
                }
                else if (satType == BDS)
                {
                    BDT2Time(gnssTime, standardTime);
                }
                else
                {
                    std::cout << "请输入正确的导航系统" << std::endl;
                    return 0;
                }
            } while (false);
            return 1;
        }

        INT32 CGNSSTime::GNSSTimeToUTCTime(const SGNSSTime& gnssTime, SStandardTime& standardTime, const INT32 satType)
        {
            do
            {
                if (satType == GPS)
                {
                    GPST2UTC(gnssTime, standardTime);
                }
                else if (satType == GALILEO)
                {
                    GST2UTC(gnssTime, standardTime);
                }
                else if (satType == BDS)
                {
                    BDT2UTC(gnssTime, standardTime);
                }
                else
                {
                    std::cout << "请输入正确的导航系统" << std::endl;
                    return 0;
                }
            } while (false);
            return 1;
        }

        INT32
        CGNSSTime::StandardTimeToGNSSTime(const SStandardTime& standardTime, SGNSSTime& gnssTime, const INT32 satType)
        {
            do
            {
                if (satType == GPS)
                {
                    UTC2GPST(standardTime, gnssTime);
                }
                else if (satType == GALILEO)
                {
                    UTC2GST(standardTime, gnssTime);
                }
                else if (satType == BDS)
                {
                    UTC2BDT(standardTime, gnssTime);
                }
                else
                {
                    std::cout << "请输入正确的导航系统" << std::endl;
                    return 0;
                }
            } while (false);
            return 1;
        }

        INT32 CGNSSTime::GNSSTimeConvert(const SGNSSTime& srcGNSSTime,
                                         const INT32 srcSatType,
                                         SGNSSTime& tarGNSSTime,
                                         const INT32 tarSatType)
        {
            do
            {
                if (srcSatType == BDS && tarSatType == GPS)
                {
                    BDT2GPST(srcGNSSTime, tarGNSSTime);
                }
                else if (srcSatType == GALILEO && tarSatType == GPS)
                {
                    GST2GPST(srcGNSSTime, tarGNSSTime);
                }
                else if (srcSatType == GPS && tarSatType == BDS)
                {
                    GPST2BDT(srcGNSSTime, tarGNSSTime);
                }
                else if (srcSatType == GPS && tarSatType == GALILEO)
                {
                    GPST2GST(srcGNSSTime, tarGNSSTime);
                }
                else
                {
                    std::cout << "请输入正确的导航系统" << std::endl;
                    return 0;
                }
            } while (false);
            return 1;
        }

        CGNSSTime::~CGNSSTime()
        {}

        // GPS时间从星期天开始
        //已测试 2102w+100s;
        INT32 CGNSSTime::GPST2Time(SGNSSTime GNSSTime, SStandardTime& standardTime)
        {
            do
            {
                //获取毫秒数
                DOUBLE milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                //计算1970.1.1-1980.1.6
                INT32 GPStimeSec = EPOCH_TO_GPST0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }
                GPStimeSec += WEEK_SEC * GNSSTime.m_week + static_cast<INT32>(GNSSTime.m_secAndMsec);
                //把秒转年月日表达形式

                INT32 year = 0;
                INT32 month = 0;
                INT32 day = 0;
                INT32 hour = 0;
                INT32 minute = 0;
                double second = 0;

                Sec2EpochDataTime(GPStimeSec, year, month, day, hour, minute, second);

                standardTime.m_year = year;
                standardTime.m_month = month;
                standardTime.m_day = day;
                standardTime.m_hour = hour;
                standardTime.m_minute = minute;
                standardTime.m_second = second;
            } while (false);
            return 1;
        }

        INT32 CGNSSTime::GST2Time(SGNSSTime GNSSTime, SStandardTime& standardTime)
        {
            do
            {
                //获取毫秒数
                DOUBLE milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                ////计算1970.1.1-1999.8.22
                INT32 GALtimeSec = EPOCH_TO_GALT0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }
                //与后面的卫星时间相加
                GALtimeSec += WEEK_SEC * GNSSTime.m_week + static_cast<INT32>(GNSSTime.m_secAndMsec);
                //把秒转年月日
                INT32 year = 0;
                INT32 month = 0;
                INT32 day = 0;
                INT32 hour = 0;
                INT32 minute = 0;
                double second = 0;

                Sec2EpochDataTime(GALtimeSec, year, month, day, hour, minute, second);
                standardTime.m_year = year;
                standardTime.m_month = month;
                standardTime.m_day = day;
                standardTime.m_hour = hour;
                standardTime.m_minute = minute;
                standardTime.m_second = second;
            } while (false);
            return 1;
        }

        // BDS时间从星期天开始
        //已测试 746w+100s;
        INT32 CGNSSTime::BDT2Time(SGNSSTime GNSSTime, SStandardTime& standardTime)
        {
            do
            {
                //获取毫秒数
                DOUBLE milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                //把BDT时间转秒
                INT32 BDStimeSec = EPOCH_TO_BDT0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }
                //与后面的卫星时间相加
                BDStimeSec += WEEK_SEC * GNSSTime.m_week + static_cast<INT32>(GNSSTime.m_secAndMsec);
                //把秒转年月日
                INT32 year = 0;
                INT32 month = 0;
                INT32 day = 0;
                INT32 hour = 0;
                INT32 minute = 0;
                DOUBLE second = 0;
                Sec2EpochDataTime(BDStimeSec, year, month, day, hour, minute, second);
                standardTime.m_year = year;
                standardTime.m_month = month;
                standardTime.m_day = day;
                standardTime.m_hour = hour;
                standardTime.m_minute = minute;
                standardTime.m_second = second;
            } while (false);
            return 1;
        }

        INT32 CGNSSTime::GPST2UTC(SGNSSTime GNSSTime, SStandardTime& utcTime)
        {
            do
            {
                DOUBLE milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                UINT64 GPStimeSec = EPOCH_TO_GPST0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }
                //与后面的卫星时间相加
                GPStimeSec += static_cast<UINT64>(GNSSTime.m_week) * WEEK_SEC;
                UINT64 tempGPSSec = 0;
                for (INT32 i = 0; GPS_LEAPSEC_INFO[i][0] > 0; i++)
                {

                    //依次加入不同的跳秒信息
                    tempGPSSec = GPStimeSec + GPS_LEAPSEC_INFO[i][NUM_SIX];

                    if ((tempGPSSec - EpochDataTime2Sec(GPS_LEAPSEC_INFO[i])) >= 0.0) //如果差0则表示为当前时间
                    {
                        GPStimeSec = tempGPSSec;
                        break;
                    }
                }
                INT32 year = 0;
                INT32 month = 0;
                INT32 day = 0;
                INT32 hour = 0;
                INT32 minute = 0;
                DOUBLE second = 0;

                Sec2EpochDataTime(GPStimeSec, year, month, day, hour, minute, second);

                utcTime.m_year = year;
                utcTime.m_month = month;
                utcTime.m_day = day;
                utcTime.m_hour = hour;
                utcTime.m_minute = minute;
                utcTime.m_second = second + milliSecond;
            } while (false);
            return 1;
        }

        INT32 CGNSSTime::GLOT2UTC(SStandardTime GNSSTime, SStandardTime& utcTime)
        {
            do
            {
                DOUBLE milliSecond = GNSSTime.m_second - floor(GNSSTime.m_second);
                DOUBLE gloSec = 0;
                gloSec = EpochDataTime2Sec(GNSSTime.m_year,
                                           GNSSTime.m_month,
                                           GNSSTime.m_day,
                                           GNSSTime.m_hour,
                                           GNSSTime.m_minute,
                                           GNSSTime.m_second);

                DOUBLE utcSec = gloSec - GLOSEC_TO_UTCSEC;

                INT32 year = 0;
                INT32 month = 0;
                INT32 day = 0;
                INT32 hour = 0;
                INT32 minute = 0;
                DOUBLE second = 0;

                Sec2EpochDataTime(utcSec, year, month, day, hour, minute, second);

                utcTime.m_year = year;
                utcTime.m_month = month;
                utcTime.m_day = day;
                utcTime.m_hour = hour;
                utcTime.m_minute = minute;
                utcTime.m_second = second;
            } while (false);
            return 1;
        }

        INT32 CGNSSTime::GST2UTC(SGNSSTime GNSSTime, SStandardTime& utcTime)
        {
            do
            {
                DOUBLE milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                UINT64 GALtimeSec = EPOCH_TO_GALT0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }

                GALtimeSec +=
                    static_cast<UINT64>(GNSSTime.m_week) * WEEK_SEC + static_cast<INT32>(GNSSTime.m_secAndMsec);
                for (INT32 i = 0; GPS_LEAPSEC_INFO[i][0] > 0; i++)
                {
                    double tempGALSec = 0;
                    tempGALSec = GALtimeSec + GPS_LEAPSEC_INFO[i][NUM_SIX];
                    if ((GALtimeSec - EpochDataTime2Sec(GPS_LEAPSEC_INFO[i])) >= 0.0)
                    {
                        GALtimeSec = tempGALSec;
                        break;
                    }
                }

                INT32 year = 0;
                INT32 month = 0;
                INT32 day = 0;
                INT32 hour = 0;
                INT32 minute = 0;
                DOUBLE second = 0;

                Sec2EpochDataTime(GALtimeSec, year, month, day, hour, minute, second);

                utcTime.m_year = year;
                utcTime.m_month = month;
                utcTime.m_day = day;
                utcTime.m_hour = hour;
                utcTime.m_minute = minute;
                utcTime.m_second = second;
            } while (false);
            return 1;
        }

        INT32 CGNSSTime::BDT2UTC(SGNSSTime GNSSTime, SStandardTime& utcTime)
        {
            do
            {
                DOUBLE Millisecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                UINT64 BDStimeSec = EPOCH_TO_BDT0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }
                BDStimeSec += static_cast<UINT64>(GNSSTime.m_week) * WEEK_SEC;
                //++i;
                for (INT32 i = 0; BDS_LEAPSEC_INFO[i][0] > 0; i++)
                {
                    double tempBDTSec = 0;
                    tempBDTSec = BDStimeSec + BDS_LEAPSEC_INFO[i][NUM_SIX];

                    if ((BDStimeSec - EpochDataTime2Sec(BDS_LEAPSEC_INFO[i])) >= 0.0)
                    {
                        BDStimeSec = tempBDTSec;
                        break;
                    }
                }

                INT32 year = 0;
                INT32 month = 0;
                INT32 day = 0;
                INT32 hour = 0;
                INT32 minute = 0;
                DOUBLE second = 0;

                Sec2EpochDataTime(BDStimeSec, year, month, day, hour, minute, second);

                utcTime.m_year = year;
                utcTime.m_month = month;
                utcTime.m_day = day;
                utcTime.m_hour = hour;
                utcTime.m_minute = minute;
                utcTime.m_second = second + Millisecond;
            } while (false);
            return 1;
        }

        // GUL_UC_009
        INT32 CGNSSTime::UTC2GPST(SStandardTime utcTime, SGNSSTime& GNSSTime)
        {
            do
            {
                DOUBLE milliSecond = utcTime.m_second - floor(utcTime.m_second);

                DOUBLE utcSec = 0;
                utcSec = EpochDataTime2Sec(
                    utcTime.m_year, utcTime.m_month, utcTime.m_day, utcTime.m_hour, utcTime.m_minute, utcTime.m_second);
                ;
                DOUBLE GPSSec = utcSec;
                for (INT32 i = 0; GPS_LEAPSEC_INFO[i][0] > 0; ++i)
                {
                    INT32 tempGPSSec = 0;
                    tempGPSSec = utcSec - GPS_LEAPSEC_INFO[i][NUM_SIX];

                    double a = tempGPSSec - EpochDataTime2Sec(GPS_LEAPSEC_INFO[i]);
                    if (tempGPSSec - EpochDataTime2Sec(GPS_LEAPSEC_INFO[i]) >= 0.0)
                    {
                        GPSSec = tempGPSSec;
                        break;
                    }
                }
                GNSSTime.m_week = static_cast<INT32>(GPSSec - EPOCH_TO_GPST0) / WEEK_SEC;
                GNSSTime.m_secAndMsec = static_cast<INT32>(GPSSec - EPOCH_TO_GPST0) % WEEK_SEC + milliSecond;
            } while (false);
            return 1;
        }

        // GUL_UC_010
        INT32 CGNSSTime::UTC2GLOT(SStandardTime utcTime, SStandardTime& GNSSTime)
        {
            do
            {
                DOUBLE milliSecond = GNSSTime.m_second - floor(GNSSTime.m_second);
                DOUBLE utcSec = 0;
                utcSec = EpochDataTime2Sec(
                    utcTime.m_year, utcTime.m_month, utcTime.m_day, utcTime.m_hour, utcTime.m_minute, utcTime.m_second);

                DOUBLE gloSec = utcSec + GLOSEC_TO_UTCSEC;

                INT32 year = 0;
                INT32 month = 0;
                INT32 day = 0;
                INT32 hour = 0;
                INT32 minute = 0;
                double second = 0;

                Sec2EpochDataTime(gloSec, year, month, day, hour, minute, second);

                GNSSTime.m_year = year;
                GNSSTime.m_month = month;
                GNSSTime.m_day = day;
                GNSSTime.m_hour = hour;
                GNSSTime.m_minute = minute;
                GNSSTime.m_second = second;
            } while (false);
            return 1;
        }

        // GUL_UC_011
        INT32 CGNSSTime::UTC2GST(SStandardTime utcTime, SGNSSTime& GNSSTime)
        {
            do
            {
                DOUBLE milliSecond = utcTime.m_second - floor(utcTime.m_second);
                DOUBLE utcSec = 0;
                utcSec = EpochDataTime2Sec(
                    utcTime.m_year, utcTime.m_month, utcTime.m_day, utcTime.m_hour, utcTime.m_minute, utcTime.m_second);

                DOUBLE GSTSec = utcSec;
                for (INT32 i = 0; GPS_LEAPSEC_INFO[i][0] > 0; i++)
                {
                    INT32 tempGALSec = 0;
                    ;
                    tempGALSec = utcSec - GPS_LEAPSEC_INFO[i][NUM_SIX];
                    if (tempGALSec - EpochDataTime2Sec(GPS_LEAPSEC_INFO[i]) >= 0.0)
                    {
                        GSTSec = tempGALSec;
                        break;
                    }
                }
                GNSSTime.m_week = static_cast<INT32>(GSTSec - EPOCH_TO_GALT0) / WEEK_SEC;
                GNSSTime.m_secAndMsec = static_cast<INT32>(GSTSec - EPOCH_TO_GALT0) % WEEK_SEC + milliSecond;
            } while (false);
            return 1;
        }

        // GUL_UC_012
        INT32 CGNSSTime::UTC2BDT(SStandardTime utcTime, SGNSSTime& GNSSTime)
        {
            do
            {
                DOUBLE milliSecond = utcTime.m_second - floor(utcTime.m_second);

                DOUBLE utcSec = 0;
                utcSec = EpochDataTime2Sec(
                    utcTime.m_year, utcTime.m_month, utcTime.m_day, utcTime.m_hour, utcTime.m_minute, utcTime.m_second);
                double BDTSec = utcSec;
                for (INT32 i = 0; BDS_LEAPSEC_INFO[i][0] > 0; i++)
                {
                    INT32 tempBDTSec = 0;
                    ;
                    tempBDTSec = utcSec - BDS_LEAPSEC_INFO[i][NUM_SIX];
                    if (tempBDTSec - EpochDataTime2Sec(BDS_LEAPSEC_INFO[i]) >= 0.0)
                    {
                        BDTSec = tempBDTSec;
                        break;
                    }
                }
                GNSSTime.m_week = static_cast<INT32>(BDTSec - EPOCH_TO_BDT0) / WEEK_SEC;
                GNSSTime.m_secAndMsec = static_cast<INT32>(BDTSec - EPOCH_TO_BDT0) % WEEK_SEC + milliSecond;
            } while (false);
            return 1;
        }

        // GUL_UC_013
        INT32 CGNSSTime::BDT2GPST(SGNSSTime srcGNSSTime, SGNSSTime& GPSTime)
        {
            do
            {
                DOUBLE milliSecond = srcGNSSTime.m_secAndMsec - floor(srcGNSSTime.m_secAndMsec);
                UINT64 BDTSec = 0;
                WeekSecToSec(srcGNSSTime, BDTSec);
                UINT64 GPSSec = BDTSec + 14;
                GPSTime.m_week = static_cast<INT32>(GPSSec - EPOCH_TO_GPST0) / WEEK_SEC;
                GPSTime.m_secAndMsec = static_cast<INT32>(GPSSec - EPOCH_TO_GPST0) % WEEK_SEC + milliSecond;
            } while (false);
            return 1;
        }

        // GUL_UC_015
        INT32 CGNSSTime::GST2GPST(SGNSSTime srcGNSSTime, SGNSSTime& GPSTime)
        {
            do
            {
                DOUBLE milliSecond = srcGNSSTime.m_secAndMsec - floor(srcGNSSTime.m_secAndMsec);
                UINT64 GALSec = 0;
                WeekSecToSec(srcGNSSTime, GALSec);
                UINT64 GPSSec = GALSec;
                GPSTime.m_week = static_cast<INT32>(GPSSec - EPOCH_TO_GPST0) / WEEK_SEC;
                GPSTime.m_secAndMsec = static_cast<INT32>(GPSSec - EPOCH_TO_GPST0) % WEEK_SEC + milliSecond;
            } while (false);
            return 1;
        }

        // GUL_UC_016
        INT32 CGNSSTime::GPST2BDT(SGNSSTime GPSTime, SGNSSTime& tarGNSSTime)
        {
            do
            {
                DOUBLE milliSecond = GPSTime.m_secAndMsec - floor(GPSTime.m_secAndMsec);
                UINT64 GPSSec = 0;
                WeekSecToSec(GPSTime, GPSSec);
                INT64 BDTSec = GPSSec - 14;
                tarGNSSTime.m_week = static_cast<INT32>(BDTSec - EPOCH_TO_BDT0) / WEEK_SEC;
                tarGNSSTime.m_secAndMsec = static_cast<INT32>(BDTSec - EPOCH_TO_BDT0) % WEEK_SEC + milliSecond;
            } while (false);

            return 1;
        }

        // GUL_UC_018
        INT32 CGNSSTime::GPST2GST(SGNSSTime GPSTime, SGNSSTime& tarGNSSTime)
        {
            do
            {
                DOUBLE milliSecond = GPSTime.m_secAndMsec - floor(GPSTime.m_secAndMsec);
                UINT64 GPSSec = 0;
                WeekSecToSec(GPSTime, GPSSec);
                UINT64 GALSec = GPSSec;

                tarGNSSTime.m_week = static_cast<INT32>(GALSec - EPOCH_TO_GALT0) / WEEK_SEC;
                tarGNSSTime.m_secAndMsec = (GALSec - EPOCH_TO_GALT0) % WEEK_SEC + milliSecond;
            } while (false);
            return 1;
        }

        bool
        CGNSSTime::TimeConvert(const double srcTime, const INT32 srcSatType, double& destTime, const INT32 destSatType)
        {
            return false;
        }

        INT32 CGNSSTime::WeekSecToSec(SGNSSTime srcTime, UINT64& tarSec)
        {
            do
            {
                UINT64 timeChange = 0;
                if (srcTime.m_timeType == GPS)
                {
                    timeChange = EPOCH_TO_GPST0;
                }
                else if (srcTime.m_timeType == GALILEO)
                {
                    timeChange = EPOCH_TO_GALT0;
                }
                else if (srcTime.m_timeType == BDS)
                {
                    timeChange = EPOCH_TO_BDT0;
                }
                else
                {
                    return 0;
                }
                tarSec = timeChange + static_cast<UINT64>(srcTime.m_week) * WEEK_SEC + srcTime.m_secAndMsec;
            } while (false);
            return 1;
        }
        INT32 CGNSSTime::SecToWeekSec(double srcSec, INT32 satType, SGNSSTime& tarTime)
        {
            do
            {
                INT32 timeChange = 0;

                DOUBLE milliSecond = srcSec - floor(srcSec);
                if (satType == GPS)
                {
                    timeChange = EPOCH_TO_GPST0;
                }
                else if (satType == GALILEO)
                {
                    timeChange = EPOCH_TO_GALT0;
                }
                else if (satType == BDS)
                {
                    timeChange = EPOCH_TO_BDT0;
                }
                else
                {
                    return 0;
                }

                tarTime.m_week = (srcSec - timeChange) / WEEK_SEC;
                tarTime.m_secAndMsec = static_cast<UINT32>(srcSec - timeChange) % WEEK_SEC + milliSecond;
            } while (false);
            return 1;
        }
        INT32 CGNSSTime::StandTimeToSec(SStandardTime srcTime, UINT64& tarSec)
        {
            do
            {
                INT32 year = 0;
                INT32 month = 0;
                INT32 day = 0;
                INT32 hour = 0;
                INT32 minute = 0;
                DOUBLE second = 0;
                tarSec = EpochDataTime2Sec(
                    srcTime.m_year, srcTime.m_month, srcTime.m_day, srcTime.m_hour, srcTime.m_minute, srcTime.m_second);
            } while (false);
            return 1;
        }
        INT32 CGNSSTime::SecToStandTime(double srcSec, SStandardTime& tarTime)
        {
            do
            {
                INT32 year = 0;
                INT32 month = 0;
                INT32 day = 0;
                INT32 hour = 0;
                INT32 minute = 0;
                double second = 0;

                Sec2EpochDataTime(srcSec, year, month, day, hour, minute, second);

                tarTime.m_year = year;
                tarTime.m_month = month;
                tarTime.m_day = day;
                tarTime.m_hour = hour;
                tarTime.m_minute = minute;
                tarTime.m_second = second;
            } while (false);
            return 1;
        }
    } // end namespace GNSSUtilityLib
} // end namespace sixents