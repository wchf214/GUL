#include "CGNSSEphemeris.h"

#include "../DllMain/GNSSCommonDef.h"
#include "../Time/TimeCalc/CCalcTime.h"
#include "../Time/TimeSys/CTimeFactory.h"
#include "../Time/TimeSys/IGNSSTime.h"

#define TSTEP 60.0
namespace sixents
{
    namespace GNSSUtilityLib
    {
        CGNSSEphemeris::CGNSSEphemeris(const SEphemeris& ephObj)
        {
            m_ephObj = ephObj;
        }

        CGNSSEphemeris::CGNSSEphemeris(const SGlonassEphemeris& ephObj)
        {
            m_gloEphObj = ephObj;
        }

        SEphemeris CGNSSEphemeris::GetEph()
        {
            return m_ephObj;
        }
        SGlonassEphemeris CGNSSEphemeris::GetGloEph()
        {
            return m_gloEphObj;
        }

        CGNSSEphemeris::~CGNSSEphemeris()
        {}

        // Clock and Position except Glonass
        INT32 CGNSSEphemeris::CalcEphSatClock(const double& sec, const SEphemeris& ephObj, double& clockVal)
        {
            //获取Toc时间
            SGNSSTime srcTime = {ephObj.m_ui16WeekNum, ephObj.m_ui32Toc, 0};
            IGNSSTime* srcTimeObj = CTimeFactory::CreateTimeObj(GPS);
            srcTimeObj->SetTime(srcTime);
            //对应的卫星时间，把对应的w+s转s
            DOUBLE outTime = 0.0;
            srcTimeObj->GetTime(outTime);
            // GNSSTime.WeekSecToSec(srcTime, outTime);
            DOUBLE timeDifference = sec - outTime;
            do
            {
                for (INT32 i = 0; i < 2; i++)
                {
                    timeDifference -= ephObj.m_dbAf0 + ephObj.m_dbAf1 * timeDifference
                                      + ephObj.m_dbAf2 * timeDifference * timeDifference;
                }
                clockVal =
                    ephObj.m_dbAf0 + ephObj.m_dbAf0 * timeDifference + ephObj.m_dbAf0 * timeDifference * timeDifference;
            } while (false);
            return 1;
        }

        INT32 CGNSSEphemeris::CalcEphSatPos(
            const double& sec, const SEphemeris& ephObj, double& xPos, double& yPos, double& zPos)
        {
            DOUBLE E = 0, Ek, O = 0;
            INT32 n, sys = 0, prn = 0;
            if (pow(ephObj.m_dbAHalf, 2) <= 0)
            {
                xPos = 0;
                yPos = 0;
                zPos = 0;
                return 0;
            }

            //获取W+S
            SGNSSTime srcTime = {ephObj.m_ui16WeekNum, ephObj.m_ui32Toc, 0};
            IGNSSTime* srcTimeObj = CTimeFactory::CreateTimeObj(GPS);
            srcTimeObj->SetTime(srcTime);
            //对应的卫星时间，把对应的w+s转s
            DOUBLE outTime = 0.0;
            srcTimeObj->GetTime(outTime);
            // 引力常量
            DOUBLE gravtiation = 0;
            // 角速度
            DOUBLE angularVelocity = 0;
            if (sys == GPS)
            {
                gravtiation = GPS_GRAVITATION;
                angularVelocity = GPS_ANGULAR_VELOCITY;
            }
            else if (sys == GALILEO)
            {
                gravtiation = GAL_GRAVITATION;
                angularVelocity = GAL_ANGULAR_VELOCITY;
            }
            else if (sys == BDS)
            {
                gravtiation = BDS_GRAVITATION;
                angularVelocity = BDS_ANGULAR_VELOCITY;
            }
            else
            {
                return 0;
            }

            DOUBLE timeDifference = sec - outTime;
            // 平近点角M
            DOUBLE M =
                ephObj.m_dbM0 + (sqrt(gravtiation / (pow(ephObj.m_dbAHalf, 6))) + ephObj.m_dbDeltaN) * timeDifference;
            for (n = 0, E = M, Ek = 0.0; fabs(E - Ek) > RTOL_KEPLER && n < MAX_ITER_KEPLER; n++)
            {
                Ek = E;
                E -= (E - ephObj.m_dbEccentricity * sin(E) - M) / (1.0 - ephObj.m_dbEccentricity * cos(E));
            }
            if (n >= MAX_ITER_KEPLER)
            {
                return 0;
            }
            DOUBLE sinE = sin(E);
            DOUBLE cosE = cos(E);
            //计算升交距角u 、卫星矢径r 、卫星轨道倾角i
            DOUBLE u = atan2(sqrt(1.0 - ephObj.m_dbEccentricity * ephObj.m_dbEccentricity) * sinE,
                             cosE - ephObj.m_dbEccentricity);
            DOUBLE r = ephObj.m_dbAHalf * ephObj.m_dbAHalf * (1.0 - ephObj.m_dbEccentricity * cosE);
            DOUBLE i = ephObj.m_dbI0 + ephObj.m_dbIdot * timeDifference;
            DOUBLE sin2u = sin(2.0 * u);
            DOUBLE cos2u = cos(2.0 * u);
            u += ephObj.m_dbCus * sin2u + ephObj.m_dbCuc * cos2u;
            r += ephObj.m_dbCrs * sin2u + ephObj.m_dbCrc * cos2u;
            i += ephObj.m_dbCis * sin2u + ephObj.m_dbCic * cos2u;

            DOUBLE x = 0;
            DOUBLE y = 0;
            x = r * cos(u);
            y = r * sin(u);
            DOUBLE cosi = cos(i);
            DOUBLE sinO = sin(O);
            DOUBLE cosO = cos(O);
            if (sys == BDS && prn <= 5)
            {
                O = ephObj.m_dbOmega0 + ephObj.m_dbOmegaDot * timeDifference - angularVelocity * ephObj.m_ui32Toe;
                DOUBLE xg = x * cosO - y * cosi * sinO;
                DOUBLE yg = x * sinO + y * cosi * cosO;
                DOUBLE zg = y * sin(i);
                DOUBLE sino = sin(angularVelocity * timeDifference);
                DOUBLE coso = cos(angularVelocity * timeDifference);
                xPos = xg * coso + yg * sino * COS_5 + zg * sino * SIN_5;
                yPos = -xg * sino + yg * coso * COS_5 + zg * coso * SIN_5;
                zPos = -yg * SIN_5 + zg * COS_5;
            }
            else
            {
                O = ephObj.m_dbOmega0 + (ephObj.m_dbOmegaDot - angularVelocity) * timeDifference
                    - angularVelocity * ephObj.m_ui32Toe;
                sinO = sin(O);
                cosO = cos(O);
                xPos = x * cosO - y * cosi * sinO;
                yPos = x * sinO + y * cosi * cosO;
                zPos = y * sin(i);
            }
            return 1;
        }

        // Glonass Clock and Position
        INT32 CGNSSEphemeris::CalcGloEphSatClock(const DOUBLE& sec, const SGlonassEphemeris& ephObj, DOUBLE& clockVal)
        {
            //计算星历时间
            SStandardTime utcTime = {};
            IGNSSTime* utcObj = CTimeFactory::CreateTimeObj(UTC);
            utcObj->SetTime(utcTime);
            DOUBLE utcSec = 0.0;
            utcObj->GetTime(utcSec);
            DOUBLE gpsSec = CCalcTime::TimeConvert(utcSec, UTC, GPS);
            IGNSSTime* gpsObj = CTimeFactory::CreateTimeObj(GPS);
            gpsObj->SetTime(gpsSec);
            SGNSSTime gpsData;
            gpsObj->GetTime(gpsData);
            INT64 gpsWeek = gpsData.m_week;
            // 剔除掉一天内的秒,只保留整天的秒数
            DOUBLE timeOfWeek = gpsData.m_secAndMsec - (static_cast<INT64>(gpsData.m_secAndMsec) % 86400);
            // 计算一天内的秒数
            DOUBLE timeOfDay = static_cast<INT64>(gpsData.m_secAndMsec) % 86400;
            //通过星历文件计算具体的秒数m_ui16Tb单位为15min
            DOUBLE TimeOfEphemeris = ephObj.m_ui16Tb * 900.0 - 10800.0; /* lt->utc */
            if (TimeOfEphemeris < timeOfDay - 43200.0)
                TimeOfEphemeris += 86400.0;
            else if (TimeOfEphemeris > timeOfDay + 43200.0)
                TimeOfEphemeris -= 86400.0;
            DOUBLE glonassEphemerisTime = EPOCH_TO_GPST0 + gpsWeek * WEEK_SEC + timeOfWeek + TimeOfEphemeris;
            do
            {
                DOUBLE time = sec - glonassEphemerisTime;
                for (INT32 i = 0; i < 2; i++)
                {
                    time -= -ephObj.m_dbTnTb + ephObj.m_dbGammaTb * time;
                }
                clockVal = -ephObj.m_dbTnTb + ephObj.m_dbGammaTb * time;
            } while (false);
            return 1;
        }

        extern DOUBLE Dot(const DOUBLE* a, const DOUBLE* b, INT32 n)
        {
            DOUBLE c = 0.0;
            while (--n >= 0)
            {
                c += a[n] * b[n];
            }
            return c;
        }

        static void OrbitDifferentialEquations(const DOUBLE* x, DOUBLE* xdot, const DOUBLE* acc)
        {
            DOUBLE a, b, c, r2 = Dot(x, x, 3), r3 = r2 * sqrt(r2), omg2 = 0; // SQR(GLO_ANGULAR_VELOCITY);
            if (r2 <= 0.0)
            {
                xdot[0] = xdot[1] = xdot[2] = xdot[3] = xdot[4] = xdot[5] = 0.0;
                return;
            }
            /* ref [2] A.3.1.2 with bug fix for xdot[4],xdot[5] */
            a = 1.5 * J2_GLO * GLO_GRAVITATION;        ///*    // SQR(RE_GLO) / r2 / r3; /* 3/2*J2*mu*Ae^2/r^5 */
            b = 5.0 * x[2] * x[2] / r2;                /* 5*z^2/r^2 */
            c = -GLO_GRAVITATION / r3 - a * (1.0 - b); /* -mu/r^3-a(1-b) */
            xdot[0] = x[3];
            xdot[1] = x[4];
            xdot[2] = x[5];
            xdot[3] = (c + omg2) * x[0] + 2.0 * GLO_ANGULAR_VELOCITY * x[4] + acc[0];
            xdot[4] = (c + omg2) * x[1] - 2.0 * GLO_ANGULAR_VELOCITY * x[3] + acc[1];
            xdot[5] = (c - 2.0 * a) * x[2] + acc[2];
        }

        static void glorbit(DOUBLE t, DOUBLE* x, const DOUBLE* acc)
        {
            double k1[6], k2[6], k3[6], k4[6], w[6];
            INT32 i;
            OrbitDifferentialEquations(x, k1, acc);
            for (i = 0; i < 6; i++)
            {
                w[i] = x[i] + k1[i] * t / 2.0;
            }
            OrbitDifferentialEquations(w, k2, acc);
            for (i = 0; i < 6; i++)
            {
                w[i] = x[i] + k2[i] * t / 2.0;
            }
            OrbitDifferentialEquations(w, k3, acc);
            for (i = 0; i < 6; i++)
            {
                w[i] = x[i] + k3[i] * t;
            }
            OrbitDifferentialEquations(w, k4, acc);
            for (i = 0; i < 6; i++)
            {
                x[i] += (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]) * t / 6.0;
            }
        }

        INT32 CGNSSEphemeris::CalcGloEphSatPos(
            const double& sec, const SGlonassEphemeris& ephObj, double& xPos, double& yPos, double& zPos)
        {
            //计算星历时间
            SStandardTime utcTime = {};
            IGNSSTime* utcObj = CTimeFactory::CreateTimeObj(UTC);
            utcObj->SetTime(utcTime);
            DOUBLE utcSec = 0.0;
            utcObj->GetTime(utcSec);
            DOUBLE gpsSec = CCalcTime::TimeConvert(utcSec, UTC, GPS);
            IGNSSTime* gpsObj = CTimeFactory::CreateTimeObj(GPS);
            gpsObj->SetTime(gpsSec);
            SGNSSTime gpsData;
            gpsObj->GetTime(gpsData);
            INT64 gpsWeek = gpsData.m_week;

            // 剔除掉一天内的秒,只保留整天的秒数
            DOUBLE timeOfWeek = gpsData.m_secAndMsec - (static_cast<INT64>(gpsData.m_secAndMsec) % 86400);

            // 计算一天内的秒数
            DOUBLE timeOfDay = static_cast<INT64>(gpsData.m_secAndMsec) % 86400;

            //通过星历文件计算具体的秒数m_ui16Tb单位为15min
            DOUBLE TimeOfEphemeris = ephObj.m_ui16Tb * 900.0 - 10800.0; /* lt->utc */
            if (TimeOfEphemeris < timeOfDay - 43200.0)
                TimeOfEphemeris += 86400.0;
            else if (TimeOfEphemeris > timeOfDay + 43200.0)
                TimeOfEphemeris -= 86400.0;

            DOUBLE glonassEphemerisTime = EPOCH_TO_GPST0 + gpsWeek * WEEK_SEC + timeOfWeek + TimeOfEphemeris;

            DOUBLE t = sec - glonassEphemerisTime, tt;
            DOUBLE x[6] = {0};

            x[0] = ephObj.m_dbXnTb;
            x[1] = ephObj.m_dbYnTb;
            x[2] = ephObj.m_dbZnTb;
            x[3] = ephObj.m_dbXnTbFirstDerivative;
            x[4] = ephObj.m_dbYnTbFirstDerivative;
            x[5] = ephObj.m_dbZnTbFirstDerivative;
            double* acc = new double[3];
            acc[0] = ephObj.m_dbXnTbSecondDerivative;
            acc[1] = ephObj.m_dbYnTbSecondDerivative;
            acc[2] = ephObj.m_dbZnTbSecondDerivative;
            for (tt = t < 0.0 ? -TSTEP : TSTEP; fabs(t) > 1E-9; t -= tt)
            {
                if (fabs(t) < TSTEP)
                    tt = t;
                glorbit(tt, x, acc);
            }
            xPos = x[0];
            yPos = x[1];
            zPos = x[2];
            return 1;
        }
    } // namespace GNSSUtilityLib
} // namespace sixents
