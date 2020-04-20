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
            m_gnssTime.m_week = week;
            m_gnssTime.m_secAndMsec = sec;
            m_gnssTime.m_satType = satType;
        }

        CGNSSTime::CGNSSTime(const int year, const int month, const int day, const int hour, const int minute, const double sec)
        {
            m_standardTime.m_year = year;
            m_standardTime.m_month = month;
            m_standardTime.m_day = day;
            m_standardTime.m_hour = hour;
            m_standardTime.m_minute = minute;
            m_standardTime.m_seconde = sec;
        }

        SGNSSTime CGNSSTime::GetGNSSTime()
        {
            return m_gnssTime;
        }

        SStandardTime CGNSSTime::GetStandardTime()
        {
            return m_standardTime;
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

        int CGNSSTime::StandardToString(SStandardTime m_standardTime, char* timeString, int& len)
        {
            do
            {
                std::string m_year = std::to_string(m_standardTime.m_year) + "-";
                std::string m_month = std::to_string(m_standardTime.m_month) + "-";
                std::string m_day = std::to_string(m_standardTime.m_day) + " ";
                std::string m_hour = std::to_string(m_standardTime.m_hour) + ":";
                std::string m_minute = std::to_string(m_standardTime.m_minute) + ":";
                std::string m_second = std::to_string(m_standardTime.m_hour);
                std::string output = m_year + m_month + m_day + m_hour + m_minute + m_second;

                int dataBufLen = strlen(output.c_str()) + 1;
                if (timeString == nullptr || len == 0 || len != dataBufLen)
                {
                    len = dataBufLen;
                    return RETURN_FAIL;
                }
                strcpy_s(timeString, strlen(timeString) + 1, output.c_str());
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
                else if (satType == GLONASS)
                {
                    GLOT2Time(gnssTime, standardTime);
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
                else if (satType == GLONASS)
                {
                    GLOT2UTC(gnssTime, standardTime);
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
                else if (satType == GLONASS)
                {
                    UTC2GLOT(standardTime, gnssTime);
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
                else if (srcSatType == GLONASS && tarSatType == GPS)
                {
                    GLOT2GPST(srcGnssTime, tarGnssTime);
                }
                else if (srcSatType == GALILEO && tarSatType == GPS)
                {
                    GST2GPST(srcGnssTime, tarGnssTime);
                }
                else if (srcSatType == GPS && tarSatType == BDS)
                {
                    GPST2BDT(srcGnssTime, tarGnssTime);
                }
                else if (srcSatType == GPS && tarSatType == GLONASS)
                {
                    GPST2GLOT(srcGnssTime, tarGnssTime);
                }
                else if (srcSatType == GPS && tarSatType == GALILEO)
                {
                    GST2GPST(srcGnssTime, tarGnssTime);
                }
                else
                {
                    return 0;
                }
            } while (false);
            return 1;
        }

        CGNSSTime::~CGNSSTime()
        {
        }

        int CGNSSTime::GPST2Time(SGNSSTime m_GNSSTime, SStandardTime& m_StandardTime)
        {
            do
            {
                //获取毫秒数
                double m_millisecond = m_GNSSTime.m_secAndMsec - floor(m_GNSSTime.m_secAndMsec);
                //转化成秒
                time_t m_sec = SatTime2Epoch(GPST0);
                if (m_GNSSTime.m_secAndMsec < -1E9 || 1E9 < m_GNSSTime.m_secAndMsec)
                {
                    m_GNSSTime.m_secAndMsec = 0.0;
                }
                m_sec += 86400 * 7 * m_GNSSTime.m_week + static_cast<int>(m_GNSSTime.m_secAndMsec);
                //把秒转年月日表达形式
                struct tm* standTime = gmtime(&m_sec);
                m_StandardTime.m_year = standTime->tm_year + 1900;
                m_StandardTime.m_month = standTime->tm_mon + 1;
                m_StandardTime.m_day = standTime->tm_mday;
                m_StandardTime.m_hour = standTime->tm_hour;
                m_StandardTime.m_minute = standTime->tm_min;
                m_StandardTime.m_seconde = standTime->tm_sec + m_millisecond;
            } while (false);
            return 1;
        }

        int CGNSSTime::GLOT2Time(SGNSSTime m_GNSSTime, SStandardTime& m_StandardTime)
        {
            do
            {
                //GLO首先获取当前系统时间
                time_t m_gloNowTime = time(nullptr);
                //获取毫秒数
                double m_Millisecond = m_GNSSTime.m_secAndMsec - floor(m_GNSSTime.m_secAndMsec);
                //把秒转年月日
                struct tm* standTime = gmtime(&m_gloNowTime);
                m_StandardTime.m_year = standTime->tm_year + 1900;
                m_StandardTime.m_month = standTime->tm_mon + 1;
                m_StandardTime.m_day = standTime->tm_mday;
                m_StandardTime.m_hour = standTime->tm_hour;
                m_StandardTime.m_minute = standTime->tm_min;
                m_StandardTime.m_seconde = standTime->tm_sec + m_Millisecond;
            } while (false);
            return 1;
        }

        int CGNSSTime::GST2Time(SGNSSTime m_GNSSTime, SStandardTime& m_StandardTime)
        {
            do
            {
                //获取毫秒数
                double m_Millisecond = m_GNSSTime.m_secAndMsec - floor(m_GNSSTime.m_secAndMsec);
                //把GST时间转秒
                time_t m_sec = SatTime2Epoch(GST0);
                if (m_GNSSTime.m_secAndMsec < -1E9 || 1E9 < m_GNSSTime.m_secAndMsec)
                {
                    m_GNSSTime.m_secAndMsec = 0.0;
                }

                m_sec += 86400 * 7 * m_GNSSTime.m_week + static_cast<int>(m_GNSSTime.m_secAndMsec);

                //把秒转年月日
                struct tm* standTime = gmtime(&m_sec);
                m_StandardTime.m_year = standTime->tm_year + 1900;
                m_StandardTime.m_month = standTime->tm_mon + 1;
                m_StandardTime.m_day = standTime->tm_mday;
                m_StandardTime.m_hour = standTime->tm_hour;
                m_StandardTime.m_minute = standTime->tm_min;
                m_StandardTime.m_seconde = standTime->tm_sec + m_Millisecond;
            } while (false);
            return 1;
        }

        int CGNSSTime::BDT2Time(SGNSSTime m_GNSSTime, SStandardTime& m_StandardTime)
        {
            do
            {
                //获取毫秒数
                double m_Millisecond = m_GNSSTime.m_secAndMsec - floor(m_GNSSTime.m_secAndMsec);
                //把BDT时间转秒
                time_t m_sec = SatTime2Epoch(BDT0);
                if (m_GNSSTime.m_secAndMsec < -1E9 || 1E9 < m_GNSSTime.m_secAndMsec)
                {
                    m_GNSSTime.m_secAndMsec = 0.0;
                }

                m_sec += 86400 * 7 * m_GNSSTime.m_week + static_cast<int>(m_GNSSTime.m_secAndMsec);

                //把秒转年月日
                struct tm* standTime = gmtime(&m_sec);
                m_StandardTime.m_year = standTime->tm_year + 1900;
                m_StandardTime.m_month = standTime->tm_mon + 1;
                m_StandardTime.m_day = standTime->tm_mday;
                m_StandardTime.m_hour = standTime->tm_hour;
                m_StandardTime.m_minute = standTime->tm_min;
                m_StandardTime.m_seconde = standTime->tm_sec + m_Millisecond;
            } while (false);
            return 1;
        }

        int CGNSSTime::GPST2UTC(SGNSSTime m_GNSSTime, SStandardTime& m_UtcTime)
        {
            do
            {
                double m_Millisecond = m_GNSSTime.m_secAndMsec - floor(m_GNSSTime.m_secAndMsec);
                time_t m_sec = SatTime2Epoch(GPST0);
                if (m_GNSSTime.m_secAndMsec < -1E9 || 1E9 < m_GNSSTime.m_secAndMsec)
                {
                    m_GNSSTime.m_secAndMsec = 0.0;
                }

                m_sec += 86400 * 7 * m_GNSSTime.m_week + static_cast<int>(m_GNSSTime.m_secAndMsec);
                for (int i = 0; leaps[i][0] > 0; i++)
                {
                    m_sec = m_sec + leaps[i][6];
                    if ((m_sec - SatTime2Epoch(leaps[i])) >= 0.0)
                    {
                        break;
                    }
                }
                struct tm* local = gmtime(&m_sec);
                m_UtcTime.m_year = local->tm_year + 1900;
                m_UtcTime.m_month = local->tm_mon + 1;
                m_UtcTime.m_day = local->tm_mday;
                m_UtcTime.m_hour = local->tm_hour;
                m_UtcTime.m_minute = local->tm_min;
                m_UtcTime.m_seconde = local->tm_sec + m_Millisecond;
            } while (false);
            return 1;
        }

        int CGNSSTime::GLOT2UTC(SGNSSTime m_GNSSTime, SStandardTime& m_UtcTime)
        {
            double Millisecond = m_GNSSTime.m_secAndMsec - floor(m_GNSSTime.m_secAndMsec);
            time_t tu = SatTime2Epoch(GPST0);
            if (m_GNSSTime.m_secAndMsec < -1E9 || 1E9 < m_GNSSTime.m_secAndMsec)
            {
                m_GNSSTime.m_secAndMsec = 0.0;
            }

            tu += 86400 * 7 * m_GNSSTime.m_week + (int)m_GNSSTime.m_secAndMsec;
            for (int i = 0; leaps[i][0] > 0; i++)
            {
                tu = tu + leaps[i][6];
                if ((tu - SatTime2Epoch(leaps[i])) >= 0.0)
                {
                    break;
                }
            }
            struct tm* local = gmtime(&tu);
            m_UtcTime.m_year = local->tm_year + 1900;
            m_UtcTime.m_month = local->tm_mon + 1;
            m_UtcTime.m_day = local->tm_mday;
            m_UtcTime.m_hour = local->tm_hour;
            m_UtcTime.m_minute = local->tm_min;
            m_UtcTime.m_seconde = local->tm_sec + Millisecond;
            return 1;
        }

        int CGNSSTime::GST2UTC(SGNSSTime m_GNSSTime, SStandardTime& m_UtcTime)
        {
            double Millisecond = m_GNSSTime.m_secAndMsec - floor(m_GNSSTime.m_secAndMsec);
            time_t tu = SatTime2Epoch(GST0);
            if (m_GNSSTime.m_secAndMsec < -1E9 || 1E9 < m_GNSSTime.m_secAndMsec)
            {
                m_GNSSTime.m_secAndMsec = 0.0;
            }

            tu += 86400 * 7 * m_GNSSTime.m_week + (int)m_GNSSTime.m_secAndMsec;
            for (int i = 0; leaps[i][0] > 0; i++)
            {
                tu = tu + leaps[i][6];
                if ((tu - SatTime2Epoch(leaps[i])) >= 0.0)
                {
                    break;
                }
            }
            struct tm* local = gmtime(&tu);
            m_UtcTime.m_year = local->tm_year + 1900;
            m_UtcTime.m_month = local->tm_mon + 1;
            m_UtcTime.m_day = local->tm_mday;
            m_UtcTime.m_hour = local->tm_hour;
            m_UtcTime.m_minute = local->tm_min;
            m_UtcTime.m_seconde = local->tm_sec + Millisecond;
            return 1;
        }

        int CGNSSTime::BDT2UTC(SGNSSTime m_GNSSTime, SStandardTime& m_UtcTime)
        {
            double Millisecond = m_GNSSTime.m_secAndMsec - floor(m_GNSSTime.m_secAndMsec);
            time_t tu = SatTime2Epoch(BDT0) - 14;
            if (m_GNSSTime.m_secAndMsec < -1E9 || 1E9 < m_GNSSTime.m_secAndMsec)
            {
                m_GNSSTime.m_secAndMsec = 0.0;
            }

            tu += 86400 * 7 * m_GNSSTime.m_week + (int)m_GNSSTime.m_secAndMsec;
            for (int i = 0; leaps[i][0] > 0; i++)
            {
                tu = tu + leaps[i][6];
                if ((tu - SatTime2Epoch(leaps[i])) >= 0.0)
                {
                    break;
                }
            }
            struct tm* local = gmtime(&tu);
            m_UtcTime.m_year = local->tm_year + 1900;
            m_UtcTime.m_month = local->tm_mon + 1;
            m_UtcTime.m_day = local->tm_mday;
            m_UtcTime.m_hour = local->tm_hour;
            m_UtcTime.m_minute = local->tm_min;
            m_UtcTime.m_seconde = local->tm_sec + Millisecond;
            return 1;
        }

        //GUL_UC_009
        int CGNSSTime::UTC2GPST(SStandardTime m_UtcTime, SGNSSTime& m_GNSSTime)
        {
            do
            {
                double Millisecond = m_UtcTime.m_seconde - floor(m_UtcTime.m_seconde);
                struct tm localTime;
                localTime.tm_year = m_UtcTime.m_year - 1900;
                localTime.tm_mon = m_UtcTime.m_month - 1;
                localTime.tm_mday = m_UtcTime.m_day;
                localTime.tm_hour = m_UtcTime.m_hour;
                localTime.tm_min = m_UtcTime.m_minute;
                localTime.tm_sec = m_UtcTime.m_seconde;
                time_t tu = mktime(&localTime);
                time_t gpst = tu + 18 - CPU2GPST0;
                m_GNSSTime.m_week = gpst / 604800;
                m_GNSSTime.m_secAndMsec = gpst % 604800 + Millisecond;

                for (int i = 0; leaps[i][0] > 0; i++)
                {
                    if (tu - SatTime2Epoch(leaps[i]) >= 0.0)
                        return tu - leaps[i][6];
                }
            } while (false);

            return 1;
        }
        //GUL_UC_010
        int CGNSSTime::UTC2GLOT(SStandardTime m_UtcTime, SGNSSTime& m_GNSSTime)
        {
            do
            {
                double Millisecond = m_UtcTime.m_seconde - floor(m_UtcTime.m_seconde);
                struct tm localTime;
                localTime.tm_year = m_UtcTime.m_year - 1900;
                localTime.tm_mon = m_UtcTime.m_month - 1;
                localTime.tm_mday = m_UtcTime.m_day;
                localTime.tm_hour = m_UtcTime.m_hour;
                localTime.tm_min = m_UtcTime.m_minute;
                localTime.tm_sec = m_UtcTime.m_seconde + Millisecond;

                time_t tu = mktime(&localTime);
                time_t glot = tu + 3 * 60 * 60;
                m_GNSSTime.m_week = glot / 604800;
                m_GNSSTime.m_secAndMsec = glot % 604800 + Millisecond;

                for (int i = 0; leaps[i][0] > 0; i++)
                {
                    if (tu - SatTime2Epoch(leaps[i]) >= 0.0)
                        return tu - leaps[i][6];
                }
            } while (false);

            return 1;
        }

        //GUL_UC_011
        int CGNSSTime::UTC2GST(SStandardTime m_UtcTime, SGNSSTime& m_GNSSTime)
        {
            do
            {
                double Millisecond = m_UtcTime.m_seconde - floor(m_UtcTime.m_seconde);
                struct tm localTime;
                localTime.tm_year = m_UtcTime.m_year - 1900;
                localTime.tm_mon = m_UtcTime.m_month - 1;
                localTime.tm_mday = m_UtcTime.m_day;
                localTime.tm_hour = m_UtcTime.m_hour;
                localTime.tm_min = m_UtcTime.m_minute;
                localTime.tm_sec = m_UtcTime.m_seconde;
                time_t tu = mktime(&localTime);
                time_t gpst = tu + 18 - CPU2GPST0;
                m_GNSSTime.m_week = gpst / 604800;
                m_GNSSTime.m_secAndMsec = gpst % 604800 + Millisecond;

                for (int i = 0; leaps[i][0] > 0; i++)
                {
                    if (tu - SatTime2Epoch(leaps[i]) >= 0.0)
                        return tu - leaps[i][6];
                }
            } while (false);

            return 1;
        }

        //GUL_UC_012
        int CGNSSTime::UTC2BDT(SStandardTime m_UtcTime, SGNSSTime& m_GNSSTime)
        {
            do
            {
                double Millisecond = m_UtcTime.m_seconde - floor(m_UtcTime.m_seconde);
                struct tm localTime;
                localTime.tm_year = m_UtcTime.m_year - 1900;
                localTime.tm_mon = m_UtcTime.m_month - 1;
                localTime.tm_mday = m_UtcTime.m_day;
                localTime.tm_hour = m_UtcTime.m_hour;
                localTime.tm_min = m_UtcTime.m_minute;
                localTime.tm_sec = m_UtcTime.m_seconde;

                time_t tu = mktime(&localTime);

                time_t gpst = tu + 4 - CPU2BDT0;

                m_GNSSTime.m_week = gpst / 604800;

                m_GNSSTime.m_secAndMsec = gpst % 604800 + Millisecond;

                for (int i = 0; leaps[i][0] > 0; i++)
                {
                    if (tu - SatTime2Epoch(leaps[i]) >= 0.0)
                        return tu - leaps[i][6];
                }
            } while (false);

            return 1;
        }

        //GUL_UC_013
        int CGNSSTime::BDT2GPST(SGNSSTime m_SRCGNSSTime, SGNSSTime& m_GPSTime)
        {
            if (m_SRCGNSSTime.m_secAndMsec + 14 < 604800)
            {
                m_GPSTime.m_secAndMsec = m_GPSTime.m_secAndMsec + 14;
                m_GPSTime.m_week = m_SRCGNSSTime.m_week + 1356;
            }
            else
            {
                m_GPSTime.m_secAndMsec = m_SRCGNSSTime.m_secAndMsec + 14 - 604800;
                m_GPSTime.m_week = m_SRCGNSSTime.m_week + 1 + 1356;
            }
            return 1;
        }
        //GUL_UC_014
        int CGNSSTime::GLOT2GPST(SGNSSTime m_SRCGNSSTime, SGNSSTime& m_GPSTime)
        {
            return 1;
        }
        //GUL_UC_015
        int CGNSSTime::GST2GPST(SGNSSTime m_SRCGNSSTime, SGNSSTime& m_GPSTime)
        {
            m_GPSTime.m_secAndMsec = m_SRCGNSSTime.m_secAndMsec + 1024;
            m_GPSTime.m_week = m_SRCGNSSTime.m_week;
            return 1;
        }

        //GUL_UC_016
        int CGNSSTime::GPST2BDT(SGNSSTime m_GPSTime, SGNSSTime& m_TARGNSSTime)
        {
            if (m_GPSTime.m_secAndMsec - 14 >= 0)
            {
                m_TARGNSSTime.m_secAndMsec = m_GPSTime.m_secAndMsec - 14;
                m_TARGNSSTime.m_week = m_GPSTime.m_week - 1356;
            }
            else
            {
                m_TARGNSSTime.m_secAndMsec = 604800 - m_GPSTime.m_secAndMsec;
                m_TARGNSSTime.m_week = m_GPSTime.m_week - 1 - 1356;
            }
            return 1;
        }
        //GUL_UC_017
        int CGNSSTime::GPST2GLOT(SGNSSTime m_GPSTime, SGNSSTime& m_TARGNSSTime)
        {
            return 1;
        }
        //GUL_UC_018
        int CGNSSTime::GPST2GST(SGNSSTime m_GPSTime, SGNSSTime& m_TARGNSSTime)
        {
            m_TARGNSSTime.m_secAndMsec = m_GPSTime.m_secAndMsec - 1024;
            m_TARGNSSTime.m_week = m_GPSTime.m_week;
            return 1;
        }

        long CGNSSTime::weekToSec(int week, double Sec, double& OutputWeek)
        {
            return 1;
        }
    } // end namespace GNSSUtilityLib
} // end namespace sixents