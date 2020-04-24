﻿#include "CGNSSEphemeris.h"

#include <ctime>
#include "../DllMain/GNSSCommonDef.h"
//#include "../Time/CGNSSTime.h"
#define TSTEP 60.0
namespace sixents
{
    namespace GNSSUtilityLib
    {
        // Clock and Position except Glonass
        INT32 CGNSSEphemeris::CalcEphSatClock(const double& sec, const SEphemeris& ephObj, double& clockVal)
        {
//            CGNSSTime GNSSTime(ephObj.m_ui16WeekNum, ephObj.m_ui32Toc);
//            long double outtime = 0;
//            SGNSSTime srcTime;
//            srcTime.m_week = ephObj.m_ui16WeekNum;
//            srcTime.m_secAndMsec = ephObj.m_ui32Toc;
//            srcTime.m_timeType = GPS;
//            //对应的卫星时间
//            // GNSSTime.WeekSecToSec(srcTime, outtime);
//            time_t t = sec - outtime;
//            do
//            {
//                for (INT32 i = 0; i < 2; i++)
//                {
//                    t -= ephObj.m_dbAf0 + ephObj.m_dbAf1 * t + ephObj.m_dbAf2 * t * t;
//                }
//                clockVal = ephObj.m_dbAf0 + ephObj.m_dbAf0 * t + ephObj.m_dbAf0 * t * t;
//            } while (false);
            return 1;
        }

        INT32 CGNSSEphemeris::CalcEphSatPos(
            const double& sec, const SEphemeris& ephObj, double& xPos, double& yPos, double& zPos)
        {
//            double E = 0, Ek, O = 0, x, y = 0;
//            INT32 n, sys = 0, prn = 0;

//            if (pow(ephObj.m_dbAHalf, 2) <= 0)
//            {
//                xPos = 0;
//                yPos = 0;
//                zPos = 0;
//                return 0;
//            }

//            CGNSSTime GNSSTime(ephObj.m_ui16WeekNum, ephObj.m_ui32Toc);
//            UINT64 outtime = 0;
//            SGNSSTime srcTime;
//            srcTime.m_week = ephObj.m_ui16WeekNum;
//            srcTime.m_secAndMsec = ephObj.m_ui32Toc;
//            srcTime.m_timeType = GPS;
//            //对应的卫星时间
//            //   GNSSTime.WeekSecToSec(srcTime, outtime);

//            double gravtiation = 0;
//            double angularVelocity = 0;

//            if (sys == GPS)
//            {
//                gravtiation = GPS_GRAVITATION;
//                angularVelocity = GPS_ANGULAR_VELOCITY;
//            }
//            else if (sys == GALILEO)
//            {
//                gravtiation = GAL_GRAVITATION;
//                angularVelocity = GAL_ANGULAR_VELOCITY;
//            }
//            else if (sys == BDS)
//            {
//                gravtiation = BDS_GRAVITATION;
//                angularVelocity = BDS_ANGULAR_VELOCITY;
//            }
//            else
//            {
//                return 0;
//            }

//            double tk = sec - outtime;
//            //平近点角M
//            double M = ephObj.m_dbM0 + (sqrt(gravtiation / (pow(ephObj.m_dbAHalf, 6))) + ephObj.m_dbDeltaN) * tk;

//            for (n = 0, E = M, Ek = 0.0; fabs(E - Ek) > RTOL_KEPLER && n < MAX_ITER_KEPLER; n++)
//            {
//                Ek = E;
//                E -= (E - ephObj.m_dbEccentricity * sin(E) - M) / (1.0 - ephObj.m_dbEccentricity * cos(E));
//            }
//            if (n >= MAX_ITER_KEPLER)
//            {
//                return 0;
//            }

//            double sinE = sin(E);
//            double cosE = cos(E);

//            //计算升交距角u 、卫星矢径r 、卫星轨道倾角i
//            double u = atan2(sqrt(1.0 - ephObj.m_dbEccentricity * ephObj.m_dbEccentricity) * sinE,
//                             cosE - ephObj.m_dbEccentricity);
//            double r = ephObj.m_dbAHalf * ephObj.m_dbAHalf * (1.0 - ephObj.m_dbEccentricity * cosE);
//            double i = ephObj.m_dbI0 + ephObj.m_dbIdot * tk;
//            double sin2u = sin(2.0 * u);
//            double cos2u = cos(2.0 * u);
//            u += ephObj.m_dbCus * sin2u + ephObj.m_dbCuc * cos2u;
//            r += ephObj.m_dbCrs * sin2u + ephObj.m_dbCrc * cos2u;
//            i += ephObj.m_dbCis * sin2u + ephObj.m_dbCic * cos2u;

//            x = r * cos(u);
//            y = r * sin(u);
//            double cosi = cos(i);
//            double sinO = sin(O);
//            double cosO = cos(O);

//            if (sys == BDS && prn <= 5)
//            {
//                O = ephObj.m_dbOmega0 + ephObj.m_dbOmegaDot * tk - angularVelocity;
//                double xg = x * cosO - y * cosi * sinO;
//                double yg = x * sinO + y * cosi * cosO;
//                double zg = y * sin(i);
//                double sino = sin(angularVelocity * tk);
//                double coso = cos(angularVelocity * tk);
//                xPos = xg * coso + yg * sino * COS_5 + zg * sino * SIN_5;
//                yPos = -xg * sino + yg * coso * COS_5 + zg * coso * SIN_5;
//                zPos = -yg * SIN_5 + zg * COS_5;
//            }
//            else
//            {
//                O = ephObj.m_dbOmega0 + (ephObj.m_dbOmegaDot - angularVelocity) * tk - angularVelocity;
//                sinO = sin(O);
//                cosO = cos(O);
//                xPos = x * cosO - y * cosi * sinO;
//                yPos = x * sinO + y * cosi * cosO;
//                zPos = y * sin(i);
//            }
            return 1;
        }

        // Glonass Clock and Position
        INT32 CGNSSEphemeris::CalcGloEphSatClock(const double& sec, const SGlonassEphemeris& ephObj, double& clockVal)
        {
            do
            {
                double time = sec - ephObj.m_ui16Tb * FIFTEEN_MIN_TO_SEC;

                for (INT32 i = 0; i < 2; i++)
                {
                    time -= -ephObj.m_dbTnTb + ephObj.m_dbGammaTb * time;
                }
                clockVal = -ephObj.m_dbTnTb + ephObj.m_dbGammaTb * time;
            } while (false);
            return 1;
        }

        extern double dot(const double* a, const double* b, INT32 n)
        {
            double c = 0.0;
            while (--n >= 0)
                c += a[n] * b[n];
            return c;
        }

        static void deq(const double* x, double* xdot, const double* acc)
        {
            double a, b, c, r2 = dot(x, x, 3), r3 = r2 * sqrt(r2), omg2 = 0; // SQR(GLO_ANGULAR_VELOCITY);

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

        static void glorbit(double t, double* x, const double* acc)
        {
            double k1[6], k2[6], k3[6], k4[6], w[6];
            INT32 i;
            deq(x, k1, acc);
            for (i = 0; i < 6; i++)
            {
                w[i] = x[i] + k1[i] * t / 2.0;
            }
            deq(w, k2, acc);
            for (i = 0; i < 6; i++)
                w[i] = x[i] + k2[i] * t / 2.0;
            {
                deq(w, k3, acc);
            }
            for (i = 0; i < 6; i++)
                w[i] = x[i] + k3[i] * t;
            {
                deq(w, k4, acc);
            }
            for (i = 0; i < 6; i++)
            {
                x[i] += (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]) * t / 6.0;
            }
        }

        INT32 CGNSSEphemeris::CalcGloEphSatPos(
            const double& sec, const SGlonassEphemeris& ephObj, double& xPos, double& yPos, double& zPos)
        {
            double t = 0, tt;
            double x[6] = {0};
            INT32 i;
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
