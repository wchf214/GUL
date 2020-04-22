#include "CGNSSTime.h"
#include <iostream>

namespace sixents
{
    namespace GNSSUtilityLib
    {
        CGNSSTime::CGNSSTime(const std::string timeString, const SAT_SYS_TYPE satType)
        {
        }

        CGNSSTime::CGNSSTime(const int week, const double sec, const int satType)
        {
            GNSSTime.m_week = week;
            GNSSTime.m_secAndMsec = sec;
            GNSSTime.m_satType = satType;
        }

        CGNSSTime::CGNSSTime(const int year, const int month, const int day, const int hour, const int minute, const double sec)
        {
            standardTime.m_year = year;
            standardTime.m_month = month;
            standardTime.m_day = day;
            standardTime.m_hour = hour;
            standardTime.m_minute = minute;
            standardTime.m_second = sec;
        }

        SGNSSTime CGNSSTime::GetGNSSTime()
        {
            return GNSSTime;
        }

        SStandardTime CGNSSTime::GetStandardTime()
        {
            return standardTime;
        }

        int CGNSSTime::Time2Epoch(int m_year, int m_month, int m_day, int m_hour, int m_min, int m_sec, time_t& m_time)
        {
            do
            {
                const int doy[] = { 1,32,60,91,121,152,182,213,244,274,305,335 };
                int days, sec, year = (int)m_year, mon = (int)m_month, day = (int)m_day;
                if (year < 1970 || 2099 < year || mon < 1 || 12 < mon)
                    return m_time;
                /* leap year if year%4==0 in 1901-2099 */
                days = (year - 1970) * 365 + (year - 1969) / 4 + doy[mon - 1] + day - 2 + (year % 4 == 0 && mon >= 3 ? 1 : 0);
                sec = (int)floor(m_sec);
                m_time = (time_t)days * 86400 + (int)m_hour * 3600 + (int)m_min * 60 + sec;
            } while (false);
            return 1;
        }

        int CGNSSTime::SatTime2Epoch(const double* m_epochTime)
        {
            do
            {
                const int doy[] = { 1,32,60,91,121,152,182,213,244,274,305,335 };
                time_t time = { 0 };
                int days, sec, year = (int)m_epochTime[0], mon = (int)m_epochTime[1], day = (int)m_epochTime[2];
                if (year < 1970 || 2099 < year || mon < 1 || 12 < mon)
                    return time;
                /* leap year if year%4==0 in 1901-2099 */
                days = (year - 1970) * 365 + (year - 1969) / 4 + doy[mon - 1] + day - 2 + (year % 4 == 0 && mon >= 3 ? 1 : 0);
                sec = (int)floor(m_epochTime[5]);
                time = (time_t)days * 86400 + (int)m_epochTime[3] * 3600 + (int)m_epochTime[4] * 60 + sec;
            } while (false);
            return 1;
        }

        int CGNSSTime::StandardTimeToString(SStandardTime standardTime, char* timeString, int& len)
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

                int dataBufLen = strlen(outputTime.c_str()) + 1;
                if (timeString == nullptr || len == 0 || len != dataBufLen)
                {
                    len = dataBufLen;
                    return RETURN_FAIL;
                }
                strcpy_s(timeString, strlen(timeString) + 1, outputTime.c_str());
            } while (false);
            return 1;
        }

        int CGNSSTime::GNSSTimeToStandardTime(const SGNSSTime& gnssTime, SStandardTime& standardTime, const int satType)
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

        int CGNSSTime::GNSSTimeToUTCTime(const SGNSSTime& gnssTime, SStandardTime& standardTime, const int satType)
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

        int CGNSSTime::StandardTimeToGNSSTime(const SStandardTime& standardTime, SGNSSTime& gnssTime, const int satType)
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

        int CGNSSTime::GNSSTimeConvert(const SGNSSTime& srcGnssTime, const int srcSatType, SGNSSTime& tarGnssTime, const int tarSatType)
        {
            do
            {
                if (srcSatType == BDS && tarSatType == GPS)
                {
                    BDT2GPST(srcGnssTime, tarGnssTime);
                }
                else if (srcSatType == GALILEO && tarSatType == GPS)
                {
                    GST2GPST(srcGnssTime, tarGnssTime);
                }
                else if (srcSatType == GPS && tarSatType == BDS)
                {
                    GPST2BDT(srcGnssTime, tarGnssTime);
                }
                else if (srcSatType == GPS && tarSatType == GALILEO)
                {
                    GST2GPST(srcGnssTime, tarGnssTime);
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
        {
        }

        //GPS时间从星期天开始
        //已测试 2102w+100s;
        int CGNSSTime::GPST2Time(SGNSSTime GNSSTime, SStandardTime& standardTime)
        {
            do
            {
                //获取毫秒数
                double milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                //计算1970.1.1-1980.1.6
                time_t GPStimeSec = EPOCH_TO_GPST0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }
                GPStimeSec += 86400 * 7 * GNSSTime.m_week + static_cast<int>(GNSSTime.m_secAndMsec);
                //把秒转年月日表达形式
                tm* GPSstandTime = gmtime(&GPStimeSec);
                standardTime.m_year = GPSstandTime->tm_year + 1900;
                standardTime.m_month = GPSstandTime->tm_mon + 1;
                standardTime.m_day = GPSstandTime->tm_mday;
                standardTime.m_hour = GPSstandTime->tm_hour;
                standardTime.m_minute = GPSstandTime->tm_min;
                standardTime.m_second = GPSstandTime->tm_sec + milliSecond;
            } while (false);
            return 1;
        }

        //int CGNSSTime::GLOT2Time(SGNSSTime GNSSTime, SStandardTime& standardTime)
        //{
        //    do
        //    {
        //        //GLO首先获取当前系统时间
        //        time_t m_gloNowTime = time(nullptr);
        //        //获取毫秒数
        //        double milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
        //        //把秒转年月日
        //        struct tm* standTime = gmtime(&m_gloNowTime);
        //        standardTime.m_year = standTime->tm_year + 1900;
        //        standardTime.m_month = standTime->tm_mon + 1;
        //        standardTime.m_day = standTime->tm_mday;
        //        standardTime.m_hour = standTime->tm_hour;
        //        standardTime.m_minute = standTime->tm_min;
        //        standardTime.m_seconde = standTime->tm_sec + milliSecond;
        //    } while (false);
        //    return 1;
        //}

        //GAL时间从星期天开始
        //已测试 1078w+100s;
        int CGNSSTime::GST2Time(SGNSSTime GNSSTime, SStandardTime& standardTime)
        {
            do
            {
                //获取毫秒数
                double milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                ////计算1970.1.1-1999.8.22
                time_t GALtimeSec = EPOCH_TO_GALT0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }
                //与后面的卫星时间相加
                GALtimeSec += 86400 * 7 * GNSSTime.m_week + static_cast<int>(GNSSTime.m_secAndMsec);
                //把秒转年月日
                struct tm* GALstandTime = gmtime(&GALtimeSec);
                standardTime.m_year = GALstandTime->tm_year + 1900;
                standardTime.m_month = GALstandTime->tm_mon + 1;
                standardTime.m_day = GALstandTime->tm_mday;
                standardTime.m_hour = GALstandTime->tm_hour;
                standardTime.m_minute = GALstandTime->tm_min;
                standardTime.m_second = GALstandTime->tm_sec + milliSecond;
            } while (false);
            return 1;
        }

        //BDS时间从星期天开始
        //已测试 746w+100s;
        int CGNSSTime::BDT2Time(SGNSSTime GNSSTime, SStandardTime& standardTime)
        {
            do
            {
                //获取毫秒数
                double milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                //把BDT时间转秒
                time_t BDStimeSec = EPOCH_TO_BDT0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }
                //与后面的卫星时间相加
                BDStimeSec += 86400 * 7 * GNSSTime.m_week + static_cast<int>(GNSSTime.m_secAndMsec);
                //把秒转年月日
                struct tm* BDSstandTime = gmtime(&BDStimeSec);
                standardTime.m_year = BDSstandTime->tm_year + 1900;
                standardTime.m_month = BDSstandTime->tm_mon + 1;
                standardTime.m_day = BDSstandTime->tm_mday;
                standardTime.m_hour = BDSstandTime->tm_hour;
                standardTime.m_minute = BDSstandTime->tm_min;
                standardTime.m_second = BDSstandTime->tm_sec + milliSecond;
            } while (false);
            return 1;
        }

        int CGNSSTime::GPST2UTC(SGNSSTime GNSSTime, SStandardTime& utcTime)
        {
            do
            {
                double milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                time_t GPStimeSec = EPOCH_TO_GPST0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }
                //与后面的卫星时间相加
                GPStimeSec += 86400 * 7 * GNSSTime.m_week + static_cast<int>(GNSSTime.m_secAndMsec);

                for (int i = 0; leaps[i][0] > 0; i++)
                {
                    double tempGPSSec = 0;
                    //依次加入不同的跳秒信息
                    tempGPSSec = GPStimeSec + leaps[i][6];
                    if ((tempGPSSec - SatTime2Epoch(leaps[i])) >= 0.0) //如果差0则表示为当前时间
                    {
                        GPStimeSec = tempGPSSec;
                        break;
                    }
                }
                struct tm* t_utcTime = gmtime(&GPStimeSec);
                utcTime.m_year = t_utcTime->tm_year + 1900;
                utcTime.m_month = t_utcTime->tm_mon + 1;
                utcTime.m_day = t_utcTime->tm_mday;
                utcTime.m_hour = t_utcTime->tm_hour;
                utcTime.m_minute = t_utcTime->tm_min;
                utcTime.m_second = t_utcTime->tm_sec + milliSecond;
            } while (false);
            return 1;
        }

        int CGNSSTime::GLOT2UTC(SStandardTime GNSSTime, SStandardTime& utcTime)
        {
            do
            {
                double milliSecond = GNSSTime.m_second - floor(GNSSTime.m_second);
                time_t gloSec = 0;
                Time2Epoch(GNSSTime.m_year, GNSSTime.m_month, GNSSTime.m_day, GNSSTime.m_hour, GNSSTime.m_minute, GNSSTime.m_second, gloSec);

                //用秒转换
                time_t utcSec = gloSec - 3 * 60 * 60;
                struct tm* t_utcTime = gmtime(&utcSec);
                utcTime.m_year = t_utcTime->tm_year + 1900;
                utcTime.m_month = t_utcTime->tm_mon + 1;
                utcTime.m_day = t_utcTime->tm_mday;
                utcTime.m_hour = t_utcTime->tm_hour;
                utcTime.m_minute = t_utcTime->tm_min;
                utcTime.m_second = t_utcTime->tm_sec + milliSecond;
            } while (false);
            return 1;
        }

        int CGNSSTime::GST2UTC(SGNSSTime GNSSTime, SStandardTime& utcTime)
        {
            do
            {
                double milliSecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                time_t GALtimeSec = EPOCH_TO_GALT0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }

                GALtimeSec += 86400 * 7 * GNSSTime.m_week + static_cast<int>(GNSSTime.m_secAndMsec);
                for (int i = 0; leaps[i][0] > 0; i++)
                {
                    double tempGALSec = 0;
                    tempGALSec = GALtimeSec + leaps[i][6];
                    if ((GALtimeSec - SatTime2Epoch(leaps[i])) >= 0.0)
                    {
                        GALtimeSec = tempGALSec;
                        break;
                    }
                }
                tm* t_utcTime = gmtime(&GALtimeSec);
                utcTime.m_year = t_utcTime->tm_year + 1900;
                utcTime.m_month = t_utcTime->tm_mon + 1;
                utcTime.m_day = t_utcTime->tm_mday;
                utcTime.m_hour = t_utcTime->tm_hour;
                utcTime.m_minute = t_utcTime->tm_min;
                utcTime.m_second = t_utcTime->tm_sec + milliSecond;
            } while (false);
            return 1;
        }

        int CGNSSTime::BDT2UTC(SGNSSTime GNSSTime, SStandardTime& utcTime)
        {
            do
            {
                double Millisecond = GNSSTime.m_secAndMsec - floor(GNSSTime.m_secAndMsec);
                time_t BDStimeSec = EPOCH_TO_BDT0;
                if (GNSSTime.m_secAndMsec < -1E9 || 1E9 < GNSSTime.m_secAndMsec)
                {
                    GNSSTime.m_secAndMsec = 0.0;
                }

                BDStimeSec += 86400 * 7 * GNSSTime.m_week + (int)GNSSTime.m_secAndMsec;
                //++i;
                for (int i = 0; leaps[i][0] > 0; i++)
                {
                    double tempBDTSec = 0;
                    tempBDTSec = BDStimeSec + leaps[i][6] + 14;
                    if ((BDStimeSec - SatTime2Epoch(leaps[i])) >= 0.0)
                    {
                        BDStimeSec = tempBDTSec;
                        break;
                    }
                }
                tm* t_utcTime = gmtime(&BDStimeSec);
                utcTime.m_year = t_utcTime->tm_year + 1900;
                utcTime.m_month = t_utcTime->tm_mon + 1;
                utcTime.m_day = t_utcTime->tm_mday;
                utcTime.m_hour = t_utcTime->tm_hour;
                utcTime.m_minute = t_utcTime->tm_min;
                utcTime.m_second = t_utcTime->tm_sec + Millisecond;
            } while (false);
            return 1;
        }

        //GUL_UC_009
        int CGNSSTime::UTC2GPST(SStandardTime utcTime, SGNSSTime& GNSSTime)
        {
            do
            {
                double milliSecond = utcTime.m_second - floor(utcTime.m_second);

                time_t m_utcSec = 0;
                Time2Epoch(utcTime.m_year, utcTime.m_month, utcTime.m_day, utcTime.m_hour, utcTime.m_minute, utcTime.m_second, m_utcSec);
                time_t m_GPSSec = 0;;
                for (int i = 0; leaps[i][0] > 0; ++i)
                {
                    time_t tempGPSSec = 0;
                    tempGPSSec = m_utcSec - leaps[i][6];
                    if (tempGPSSec - SatTime2Epoch(leaps[i]) >= 0.0)
                    {
                        m_GPSSec = tempGPSSec;
                        break;
                    }
                }
                GNSSTime.m_week = (m_GPSSec - EPOCH_TO_GPST0) / WEEKSEC;
                GNSSTime.m_secAndMsec = (m_GPSSec - EPOCH_TO_GPST0) % WEEKSEC + milliSecond;
            } while (false);
            return 1;
        }

        //GUL_UC_010
        int CGNSSTime::UTC2GLOT(SStandardTime utcTime, SStandardTime& GNSSTime)
        {
            do
            {
                double milliSecond = utcTime.m_second - floor(utcTime.m_second);
                time_t utcSec = 0;
                Time2Epoch(utcTime.m_year, utcTime.m_month, utcTime.m_day, utcTime.m_hour, utcTime.m_minute, utcTime.m_second, utcSec);

                time_t m_gloSec = utcSec + 3 * 60 * 60;
                struct tm* gloTime = gmtime(&m_gloSec);

                GNSSTime.m_year = gloTime->tm_year + 1900;
                GNSSTime.m_month = gloTime->tm_mon + 1;
                GNSSTime.m_day = gloTime->tm_mday;
                GNSSTime.m_hour = gloTime->tm_hour;
                GNSSTime.m_minute = gloTime->tm_min;
                GNSSTime.m_second = gloTime->tm_sec + milliSecond;
            } while (false);
            return 1;
        }

        //GUL_UC_011
        int CGNSSTime::UTC2GST(SStandardTime utcTime, SGNSSTime& GNSSTime)
        {
            do
            {
                double milliSecond = utcTime.m_second - floor(utcTime.m_second);
                time_t m_utcSec = 0;
                Time2Epoch(utcTime.m_year, utcTime.m_month, utcTime.m_day, utcTime.m_hour, utcTime.m_minute, utcTime.m_second, m_utcSec);
                time_t m_GSTSec = 0;;
                for (int i = 0; leaps[i][0] > 0; i++)
                {
                    time_t tempGALSec = 0;;
                    tempGALSec = m_utcSec - leaps[i][6];
                    if (tempGALSec - SatTime2Epoch(leaps[i]) >= 0.0)
                    {
                        m_GSTSec = tempGALSec;
                        break;
                    }
                }
                GNSSTime.m_week = (m_GSTSec - EPOCH_TO_GALT0) / WEEKSEC;
                GNSSTime.m_secAndMsec = (m_GSTSec - EPOCH_TO_GALT0) % WEEKSEC + milliSecond;
            } while (false);
            return 1;
        }

        //GUL_UC_012
        int CGNSSTime::UTC2BDT(SStandardTime utcTime, SGNSSTime& GNSSTime)
        {
            do
            {
                double milliSecond = utcTime.m_second - floor(utcTime.m_second);
                struct tm localTime;
                time_t m_utcSec = 0;
                Time2Epoch(utcTime.m_year, utcTime.m_month, utcTime.m_day, utcTime.m_hour, utcTime.m_minute, utcTime.m_second, m_utcSec);

                time_t m_BDTSec = 0;;
                for (int i = 0; leaps[i][0] > 0; i++)
                {
                    time_t tempBDTSec = 0;;
                    tempBDTSec = m_utcSec - leaps[i][6] - 14;
                    if (tempBDTSec - SatTime2Epoch(leaps[i]) >= 0.0)
                    {
                        m_BDTSec = tempBDTSec;
                        break;
                    }
                }
                GNSSTime.m_week = (m_BDTSec - EPOCH_TO_BDT0) / WEEKSEC;
                GNSSTime.m_secAndMsec = (m_BDTSec - EPOCH_TO_BDT0) % WEEKSEC + milliSecond;
            } while (false);
            return 1;
        }

        //GUL_UC_013
        int CGNSSTime::BDT2GPST(SGNSSTime m_SRCGNSSTime, SGNSSTime& GPSTime)
        {
            if (m_SRCGNSSTime.m_secAndMsec + 14 < 604800)
            {
                GPSTime.m_week = m_SRCGNSSTime.m_week + 1356;
                GPSTime.m_secAndMsec = GPSTime.m_secAndMsec + 14;
            }
            else
            {
                GPSTime.m_week = m_SRCGNSSTime.m_week + 1 + 1356;
                GPSTime.m_secAndMsec = m_SRCGNSSTime.m_secAndMsec + 14 - 604800;
            }
            return 1;
        }

        ////GUL_UC_014
        //int CGNSSTime::GLOT2GPST(SStandardTime m_SRCGNSSTime, SGNSSTime& GPSTime)
        //{
        //    double Millisecond = m_SRCGNSSTime.m_second - floor(m_SRCGNSSTime.m_second);
        //    struct tm gloTime;
        //    gloTime.tm_year = m_SRCGNSSTime.m_year - 1900;
        //    gloTime.tm_mon = m_SRCGNSSTime.m_month - 1;
        //    gloTime.tm_mday = m_SRCGNSSTime.m_day;
        //    gloTime.tm_hour = m_SRCGNSSTime.m_hour;
        //    gloTime.tm_min = m_SRCGNSSTime.m_minute;
        //    gloTime.tm_sec = m_SRCGNSSTime.m_second;
        //    time_t m_gloSec = 0;
        //    Time2Epoch(gloTime.tm_year, gloTime.tm_mon, gloTime.tm_mday, gloTime.tm_hour, gloTime.tm_min, gloTime.tm_sec, m_gloSec);

        //    time_t m_GPSSec = 0;;
        //    for (int i = 0; leaps[i][0] > 0; i++)
        //    {
        //        time_t m_tempGloSec = 0;;
        //        m_tempGloSec = m_gloSec - leaps[i][6];
        //        if (m_tempGloSec - SatTime2Epoch(leaps[i]) >= 0.0)
        //        {
        //            m_GPSSec = m_tempGloSec;
        //            break;
        //        }
        //    }
        //    GPSTime.m_week = (m_gloSec - EPOCH_TO_GPST0) / WEEKSEC;
        //    GPSTime.m_secAndMsec = (m_gloSec - EPOCH_TO_GPST0) % WEEKSEC + Millisecond;
        //    return 1;
        //}

        //GUL_UC_015
        int CGNSSTime::GST2GPST(SGNSSTime m_SRCGNSSTime, SGNSSTime& GPSTime)
        {
            GPSTime.m_week = m_SRCGNSSTime.m_week + 1024;
            GPSTime.m_secAndMsec = m_SRCGNSSTime.m_secAndMsec;
            return 1;
        }

        //GUL_UC_016
        int CGNSSTime::GPST2BDT(SGNSSTime GPSTime, SGNSSTime& m_TARGNSSTime)
        {
            if (GPSTime.m_secAndMsec - 14 >= 0)
            {
                m_TARGNSSTime.m_week = GPSTime.m_week - 1356;
                m_TARGNSSTime.m_secAndMsec = GPSTime.m_secAndMsec - 14;
            }
            else
            {
                m_TARGNSSTime.m_week = GPSTime.m_week - 1 - 1356;
                m_TARGNSSTime.m_secAndMsec = 604800 + GPSTime.m_secAndMsec - 14;
            }
            return 1;
        }
        //GUL_UC_017
       /* int CGNSSTime::GPST2GLOT(SGNSSTime GPSTime, SStandardTime& m_TARGNSSTime)
        {
            do
            {
                time_t m_GPSSec = EPOCH_TO_GPST0 + GPSTime.m_week * WEEKSEC + GPSTime.m_secAndMsec;
                struct tm* gloTime = gmtime(&m_GPSSec);
                m_TARGNSSTime.m_year = gloTime->tm_year + 1900;
                m_TARGNSSTime.m_month = gloTime->tm_mon + 1;
                m_TARGNSSTime.m_day = gloTime->tm_mday;
                m_TARGNSSTime.m_hour = gloTime->tm_hour;
                m_TARGNSSTime.m_minute = gloTime->tm_min;
                m_TARGNSSTime.m_second = gloTime->tm_sec;
            } while (false);
            return 1;
        }*/

        //GUL_UC_018
        int CGNSSTime::GPST2GST(SGNSSTime GPSTime, SGNSSTime& m_TARGNSSTime)
        {
            m_TARGNSSTime.m_week = GPSTime.m_week - 1024;
            m_TARGNSSTime.m_secAndMsec = GPSTime.m_secAndMsec;
            return 1;
        }

        long CGNSSTime::weekToSec(int week, double Sec, double& OutputWeek)
        {
            return 1;
        }

        bool CGNSSTime::TimeConvert(const double srcTime, const int srcSatType, double& destTime, const int destSatType)
        {
            return false;
        }

        int CGNSSTime::WeekSecToSec(SGNSSTime m_SrcTime, time_t& m_TarSec)
        {
            do
            {
                time_t timeChange = 0;
                if (m_SrcTime.m_satType == GPS)
                {
                    timeChange = EPOCH_TO_GPST0;
                }
                else if (m_SrcTime.m_satType == GALILEO)
                {
                    timeChange = EPOCH_TO_GALT0;
                }
                else if (m_SrcTime.m_satType == BDS)
                {
                    timeChange = EPOCH_TO_BDT0;
                }
                /*else
                {
                    return 0;
                }*/
                m_TarSec = timeChange + m_SrcTime.m_week * 7 * 86400 + m_SrcTime.m_secAndMsec;
            } while (false);
            return 1;
        }
        int CGNSSTime::SecToWeekSec(time_t m_SrcSec, int satType, SGNSSTime& m_TarTime)
        {
            do
            {
                if (satType == GPS)
                {
                    m_TarTime.m_week = (m_SrcSec - EPOCH_TO_GPST0) / (7 * 86400);
                    m_TarTime.m_week = (m_SrcSec - EPOCH_TO_GPST0) % (7 * 86400);
                }
                else if (satType == GALILEO)
                {
                    m_TarTime.m_week = (m_SrcSec - EPOCH_TO_GALT0) / (7 * 86400);
                    m_TarTime.m_week = (m_SrcSec - EPOCH_TO_GALT0) % (7 * 86400);
                }
                else if (satType == BDS)
                {
                    m_TarTime.m_week = (m_SrcSec - EPOCH_TO_BDT0) / (7 * 86400);
                    m_TarTime.m_week = (m_SrcSec - EPOCH_TO_BDT0) % (7 * 86400);
                }
                else
                {
                    return 0;
                }
            } while (false);
            return 1;
        }
        int CGNSSTime::StandTimeToSec(SStandardTime m_SrcTime, time_t& m_TarSec)
        {
            do
            {
                struct tm m_Time;
                m_Time.tm_year = m_SrcTime.m_year - 1900;
                m_Time.tm_mon = m_SrcTime.m_month - 1;
                m_Time.tm_mday = m_SrcTime.m_day;
                m_Time.tm_hour = m_SrcTime.m_hour;
                m_Time.tm_min = m_SrcTime.m_minute;
                m_Time.tm_sec = m_SrcTime.m_second;
            } while (false);
            return 1;
        }
        int CGNSSTime::SecToStandTime(time_t m_SrcSec, SStandardTime& m_TarTime)
        {
            do
            {
                tm* m_Time = gmtime(&m_SrcSec);
                m_TarTime.m_year = m_Time->tm_year + 1900;
                m_TarTime.m_month = m_Time->tm_mon + 1;
                m_TarTime.m_day = m_Time->tm_mday;
                m_TarTime.m_hour = m_Time->tm_hour;
                m_TarTime.m_minute = m_Time->tm_min;
                m_TarTime.m_second = m_Time->tm_sec;
            } while (false);
            return 1;
        }
    } // end namespace GNSSUtilityLib
} // end namespace sixents