#define DLL_EXPORT

#include "GNSSUtilityInterface.h"
#include "../AppIFs/AppInterface.h"
#include "GNSSCommonDef.h"

namespace sixents
{
    namespace Math
    {
        // GUL_UC_001 GUL_UC_003 GUL_UC_004
        extern "C" DLL_API int STD_CALL FormatWeekSecTime(const unsigned int week,
                                                          const double sec,
                                                          const unsigned int timeType,
                                                          char* formatString,
                                                          unsigned int& len)
        {
            return CAppInterface::FormatWeekSecTime(static_cast<UINT64>(week), sec, timeType, formatString, len);
        }

        // GUL_UC_002
        extern "C" DLL_API int STD_CALL FormatStandardTime(const unsigned int year,
                                                           const unsigned int month,
                                                           const unsigned int day,
                                                           const unsigned int hour,
                                                           const unsigned int minute,
                                                           const double second,
                                                           char* formatString,
                                                           unsigned int& len)
        {
            return CAppInterface::FormatStandardTime(year, month, day, hour, minute, second, formatString, len);
        }

        // GUL_UC_005 GUL_UC_007 GUL_UC_008
        extern "C" DLL_API int STD_CALL GNSSTimeToUTCTime(const unsigned int week,
                                                          const double sec,
                                                          const unsigned int timeType,
                                                          unsigned int& year,
                                                          unsigned int& month,
                                                          unsigned int& day,
                                                          unsigned int& hour,
                                                          unsigned int& minute,
                                                          double& second)
        {
            return CAppInterface::GNSSTimeToStandardTime(
                static_cast<UINT64>(week), sec, timeType, UTC, year, month, day, hour, minute, second);
        }

        // GUL_UC_006
        extern "C" DLL_API int STD_CALL GlonassTimeToUTCTime(const unsigned int gloYear,
                                                             const unsigned int gloMonth,
                                                             const unsigned int gloDay,
                                                             const unsigned int gloHour,
                                                             const unsigned int gloMinute,
                                                             const double gloSecond,
                                                             unsigned int& utcYear,
                                                             unsigned int& utcMonth,
                                                             unsigned int& utcDay,
                                                             unsigned int& utcHour,
                                                             unsigned int& utcMinute,
                                                             double& utcSecond)
        {
            return CAppInterface::StandardTimeConvert(gloYear,
                                                      gloMonth,
                                                      gloDay,
                                                      gloHour,
                                                      gloMinute,
                                                      gloSecond,
                                                      GLONASS,
                                                      UTC,
                                                      utcYear,
                                                      utcMonth,
                                                      utcDay,
                                                      utcHour,
                                                      utcMinute,
                                                      utcSecond);
        }

        // GUL_UC_009 GUL_UC_011 GUL_UC_012
        extern "C" DLL_API int STD_CALL UTCTimeToGNSSTime(const unsigned int year,
                                                          const unsigned int month,
                                                          const unsigned int day,
                                                          const unsigned int hour,
                                                          const unsigned int minute,
                                                          const double second,
                                                          const unsigned int timeType,
                                                          unsigned int& week,
                                                          double& sec)
        {
            UINT64 weekNum = 0;
            int ret = CAppInterface::StandardTimeToGNSSTime(
                year, month, day, hour, minute, second, UTC, timeType, weekNum, sec);
            week = static_cast<unsigned int>(weekNum);
            return ret;
        }

        extern "C" int STD_CALL WeekSecToSec(const unsigned int week,
                                             const double second,
                                             const unsigned int timeType,
                                             double& sec)
        {
            return CAppInterface::WeekSecToSec(static_cast<UINT64>(week), second, timeType, sec);
        }

        // GUL_UC_010
        extern "C" DLL_API int STD_CALL UTCTimeToGlonassTime(const unsigned int utcYear,
                                                             const unsigned int utcMonth,
                                                             const unsigned int utcDay,
                                                             const unsigned int utcHour,
                                                             const unsigned int utcMinute,
                                                             const double utcSecond,
                                                             unsigned int& gloYear,
                                                             unsigned int& gloMonth,
                                                             unsigned int& gloDay,
                                                             unsigned int& gloHour,
                                                             unsigned int& gloMinute,
                                                             double& gloSecond)
        {
            return CAppInterface::StandardTimeConvert(utcYear,
                                                      utcMonth,
                                                      utcDay,
                                                      utcHour,
                                                      utcMinute,
                                                      utcSecond,
                                                      UTC,
                                                      GLONASS,
                                                      gloYear,
                                                      gloMonth,
                                                      gloDay,
                                                      gloHour,
                                                      gloMinute,
                                                      gloSecond);
        }

        // GUL_UC_013  GUL_UC_015 GUL_UC_016  GUL_UC_018
        extern "C" DLL_API int STD_CALL GNSSTimeConvert(const unsigned int srcWeek,
                                                        const double srcSec,
                                                        const unsigned int srcTimeType,
                                                        unsigned int& destWeek,
                                                        double& destSec,
                                                        const unsigned int destTimeType)
        {
            UINT64 temp = 0;
            int ret = CAppInterface::GNSSTimeConvert(
                static_cast<UINT64>(srcWeek), srcSec, srcTimeType, destTimeType, temp, destSec);
            destWeek = static_cast<unsigned int>(temp);
            return ret;
        }

        // GUL_UC_014
        extern "C" DLL_API int STD_CALL GlonassTimeToGPSTime(const unsigned int year,
                                                             const unsigned int month,
                                                             const unsigned int day,
                                                             const unsigned int hour,
                                                             const unsigned int minute,
                                                             const double second,
                                                             unsigned int& week,
                                                             double& sec)
        {
            UINT64 temp = 0;
            int ret =
                CAppInterface::StandardTimeToGNSSTime(year, month, day, hour, minute, second, GLONASS, GPS, temp, sec);
            week = static_cast<unsigned int>(temp);
            return ret;
        }

        // GUL_UC_017
        extern "C" DLL_API int STD_CALL GPSTimeToGlonassTime(const unsigned int week,
                                                             const double second,
                                                             unsigned int& year,
                                                             unsigned int& month,
                                                             unsigned int& day,
                                                             unsigned int& hour,
                                                             unsigned int& minute,
                                                             double& sec)
        {
            return CAppInterface::GNSSTimeToStandardTime(
                static_cast<UINT64>(week), second, GPS, GLONASS, year, month, day, hour, minute, sec);
        }

        extern "C" DLL_API int STD_CALL
        XYZ2BLH(const double x, const double y, const double z, double& lat, double& lon, double& height)
        {
            return CAppInterface::XYZ2BLH(x, y, z, lat, lon, height);
        }

        extern "C" DLL_API int STD_CALL
        BLH2XYZ(const double lat, const double lon, const double height, double& x, double& y, double& z)
        {
            return CAppInterface::BLH2XYZ(lat, lon, height, x, y, z);
        }

        extern "C" DLL_API int STD_CALL XYZ2ENU(const double curX,
                                                const double curY,
                                                const double curZ,
                                                const double refX,
                                                const double refY,
                                                const double refZ,
                                                double& east,
                                                double& north,
                                                double& up)
        {
            return CAppInterface::XYZ2ENU(curX, curY, curZ, refX, refY, refZ, east, north, up);
        }

        extern "C" DLL_API int STD_CALL ENU2XYZ(const double east,
                                                const double north,
                                                const double up,
                                                const double refX,
                                                const double refY,
                                                const double refZ,
                                                double& curX,
                                                double& curY,
                                                double& curZ)
        {
            return CAppInterface::ENU2XYZ(east, north, up, refX, refY, refZ, curX, curY, curZ);
        }

        extern "C" DLL_API int STD_CALL CalcGlonassEphSatClock(const double sec,
                                                               const double gloEphSec,
                                                               const SGlonassEphemeris ephObj,
                                                               double& clockVal)
        {
            return CAppInterface::CalcGlonassEphSatClock(sec, gloEphSec, ephObj, clockVal);
        }

        extern "C" DLL_API int STD_CALL CalcGloEphClock(const double sec,
                                                        const double gloEphSec,
                                                        const unsigned int satId,
                                                        const unsigned int tb,
                                                        const double tnTb,
                                                        const double gammaTb,
                                                        double& clockVal)
        {
            SGlonassEphemeris ephObj;
            ephObj.m_ui8SatId = satId;
            ephObj.m_ui16Tb = tb;
            ephObj.m_dbTnTb = tnTb;
            ephObj.m_dbGammaTb = gammaTb;
            return CalcGlonassEphSatClock(sec, gloEphSec, ephObj, clockVal);
        }

        extern "C" DLL_API int STD_CALL CalcEphSatClock(const double sec, const SEphemeris ephObj, double& clockVal)
        {
            return CAppInterface::CalcEphSatClock(sec, ephObj, clockVal);
        }

        extern "C" DLL_API int STD_CALL CalcEphClock(const double sec,
                                                     const unsigned int satId,
                                                     const unsigned int msgType,
                                                     const unsigned int weekNum,
                                                     const unsigned int toc,
                                                     const double af0,
                                                     const double af1,
                                                     const double af2,
                                                     double& clockVal)
        {
            SEphemeris ephObj;
            ephObj.m_ui8SatId = satId;
            ephObj.m_ui16MsgType = msgType;
            ephObj.m_ui16WeekNum = weekNum;
            ephObj.m_ui32Toc = toc;
            ephObj.m_dbAf0 = af0;
            ephObj.m_dbAf1 = af1;
            ephObj.m_dbAf2 = af2;
            return CalcEphSatClock(sec, ephObj, clockVal);
        }

        extern "C" DLL_API int STD_CALL CalcGlonassEphSatPos(
            const double sec, const double gloEphSec, const SGlonassEphemeris ephObj, double& x, double& y, double& z)
        {
            return CAppInterface::CalcGlonassEphSatPos(sec, gloEphSec, ephObj, x, y, z);
        }

        extern "C" DLL_API int STD_CALL CalcGloEphPos(const double sec,
                                                      const double gloEphSec,
                                                      const unsigned int satId,
                                                      const unsigned int tb,
                                                      const double xnTb,
                                                      const double ynTb,
                                                      const double znTb,
                                                      const double xnTbFirstDer,
                                                      const double ynTbFirstDer,
                                                      const double znTbFirstDer,
                                                      const double xnTbSecDer,
                                                      const double ynTbSecDer,
                                                      const double znTbSecDer,
                                                      double& x,
                                                      double& y,
                                                      double& z)
        {
            SGlonassEphemeris ephObj;
            ephObj.m_ui8SatId = satId;
            ephObj.m_ui16Tb = tb;
            ephObj.m_dbXnTb = xnTb;
            ephObj.m_dbYnTb = ynTb;
            ephObj.m_dbZnTb = znTb;
            ephObj.m_dbXnTbFirstDerivative = xnTbFirstDer;
            ephObj.m_dbYnTbFirstDerivative = ynTbFirstDer;
            ephObj.m_dbZnTbFirstDerivative = znTbFirstDer;
            ephObj.m_dbXnTbSecondDerivative = xnTbSecDer;
            ephObj.m_dbYnTbSecondDerivative = ynTbSecDer;
            ephObj.m_dbZnTbSecondDerivative = znTbSecDer;
            return CalcGlonassEphSatPos(sec, gloEphSec, ephObj, x, y, z);
        }

        extern "C" DLL_API int STD_CALL
        CalcEphSatPos(const double sec, const SEphemeris ephObj, double& x, double& y, double& z)
        {
            return CAppInterface::CalcEphSatPos(sec, ephObj, x, y, z);
        }

        extern "C" DLL_API int STD_CALL CalcEphPos(const double sec,
                                                   const unsigned int satId,
                                                   const unsigned int msgType,
                                                   const unsigned int weekNum,
                                                   const unsigned int toe,
                                                   const double aHalf,
                                                   const double m0,
                                                   const double deltaN,
                                                   const double eccentricity,
                                                   const double argumentOfPerigee,
                                                   const double i0,
                                                   const double idot,
                                                   const double cus,
                                                   const double cuc,
                                                   const double crs,
                                                   const double crc,
                                                   const double cis,
                                                   const double cic,
                                                   const double omega0,
                                                   const double omegaDot,
                                                   double& x,
                                                   double& y,
                                                   double& z)
        {
            SEphemeris ephObj;
            ephObj.m_ui8SatId = satId;
            ephObj.m_ui16MsgType = msgType;
            ephObj.m_ui16WeekNum = weekNum;
            ephObj.m_ui32Toe = toe;
            ephObj.m_dbAHalf = aHalf;
            ephObj.m_dbM0 = m0;
            ephObj.m_dbDeltaN = deltaN;
            ephObj.m_dbEccentricity = eccentricity;
            ephObj.m_dbArgumentOfPerigee = argumentOfPerigee;
            ephObj.m_dbI0 = i0;
            ephObj.m_dbIdot = idot;
            ephObj.m_dbCus = cus;
            ephObj.m_dbCuc = cuc;
            ephObj.m_dbCrs = crs;
            ephObj.m_dbCrc = crc;
            ephObj.m_dbCis = cis;
            ephObj.m_dbCic = cic;
            ephObj.m_dbOmega0 = omega0;
            ephObj.m_dbOmegaDot = omegaDot;
            return CalcEphSatPos(sec, ephObj, x, y, z);
        }

        extern "C" DLL_API int STD_CALL FormatAngle(const double radian,
                                                    char* formatString,
                                                    unsigned int& len,
                                                    const bool formatType)
        {
            return CAppInterface::FormatAngle(radian, formatString, len, formatType);
        }

        extern "C" DLL_API int STD_CALL Deg2Rad(const double degree, double& radian)
        {
            return CAppInterface::Deg2Rad(degree, radian);
        }

        extern "C" DLL_API int STD_CALL DMS2Rad(const int degree,
                                                const unsigned int minute,
                                                const double sec,
                                                double& radian)
        {
            return CAppInterface::DMS2Rad(degree, minute, sec, radian);
        }

        extern "C" DLL_API int STD_CALL Rad2Deg(const double radian, double& degree)
        {
            return CAppInterface::Rad2Deg(radian, degree);
        }

        extern "C" DLL_API int STD_CALL Rad2DMS(const double radian, int& degree, unsigned int& minute, double& sec)
        {
            return CAppInterface::Rad2DMS(radian, degree, minute, sec);
        }
    } // namespace Math
} // namespace sixents
