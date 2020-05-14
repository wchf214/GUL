#include "CGNSSEphemeris.h"
#include <cmath>
#include <ctime>
#include "../DllMain/GNSSCommonDef.h"
#include "../Time/TimeCalc/CCalcTime.h"
#include "../Time/TimeSys/CTimeFactory.h"
#include "../Time/TimeSys/IGNSSTime.h"

namespace sixents
{
    namespace Math
    {
        CGNSSEphemeris::CGNSSEphemeris()
        {}

        CGNSSEphemeris::~CGNSSEphemeris()
        {}

        INT32 CGNSSEphemeris::CalcEphSatClock(const DOUBLE& sec, const SEphemeris& ephObj, DOUBLE& clockVal)
        {
            INT32 iRet = RETURN_FAIL;
            // 获取Toc时间
            do
            {
                SGNSSTime srcTime = {
                    static_cast<UINT64>(ephObj.m_ui16WeekNum), static_cast<DOUBLE>(ephObj.m_ui32Toc), 0};
                IGNSSTime* srcTimeObj = nullptr;
                if (ephObj.m_ui16MsgType == 1019)
                {
                    srcTimeObj = CTimeFactory::CreateTimeObj(GPS);
                }

                else if (ephObj.m_ui16MsgType == 1045)
                {
                    srcTimeObj = CTimeFactory::CreateTimeObj(GALILEO);
                }

                else if (ephObj.m_ui16MsgType == 1046)
                {
                    srcTimeObj = CTimeFactory::CreateTimeObj(BDS);
                }
                else
                {
                    //不存在的卫星系统
                    iRet = RETURN_ERROR_PARAMETER;
                    break;
                }

                srcTimeObj->SetTime(srcTime);
                // 对应的卫星时间，把对应的w+s转s
                DOUBLE gnssSec = 0.0;
                srcTimeObj->GetTime(gnssSec);

                // BDS需要转换为GPS时间
                if (ephObj.m_ui16MsgType == 1046)
                {
                    gnssSec = CCalcTime::TimeConvert(gnssSec, BDS, GPS);
                }

                DOUBLE timeDifference = sec - gnssSec;

                for (INT32 i = 0; i < NUM_TWO; ++i)
                {
                    timeDifference -= ephObj.m_dbAf0 + ephObj.m_dbAf1 * timeDifference
                                      + ephObj.m_dbAf2 * timeDifference * timeDifference;
                }
                clockVal =
                    ephObj.m_dbAf0 + ephObj.m_dbAf0 * timeDifference + ephObj.m_dbAf0 * timeDifference * timeDifference;
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        INT32 CGNSSEphemeris::CalcEphSatPos(
            const DOUBLE& sec, const SEphemeris& ephObj, DOUBLE& xPos, DOUBLE& yPos, DOUBLE& zPos)
        {
            INT32 iRet = RETURN_FAIL;
            do
            {
                if (pow(ephObj.m_dbAHalf, NUM_TWO) <= 0)
                {
                    xPos = 0;
                    yPos = 0;
                    zPos = 0;
                    iRet = RETURN_ERROR_PARAMETER;
                }

                // 获取W+S
                SGNSSTime srcTime = {
                    static_cast<UINT64>(ephObj.m_ui16WeekNum), static_cast<DOUBLE>(ephObj.m_ui32Toc), 0};

                IGNSSTime* srcTimeObj = nullptr;
                if (ephObj.m_ui16MsgType == 1019)
                {
                    srcTimeObj = CTimeFactory::CreateTimeObj(GPS);
                }

                else if (ephObj.m_ui16MsgType == 1045)
                {
                    srcTimeObj = CTimeFactory::CreateTimeObj(GALILEO);
                }

                else if (ephObj.m_ui16MsgType == 1046)
                {
                    srcTimeObj = CTimeFactory::CreateTimeObj(BDS);
                }
                else
                {
                    //不存在的卫星系统
                    iRet = RETURN_ERROR_PARAMETER;
                    break;
                }

                srcTimeObj->SetTime(srcTime);
                // 对应的卫星时间，把对应的w+s转s
                DOUBLE gnssSec = 0.0;
                srcTimeObj->GetTime(gnssSec);

                if (ephObj.m_ui16MsgType == 1046)
                {
                    gnssSec = CCalcTime::TimeConvert(gnssSec, BDS, GPS);
                }

                // 引力常量
                DOUBLE gravtiation = 0;
                // 角速度
                DOUBLE angularVelocity = 0;

                INT32 prn = 0;
                if (ephObj.m_ui16MsgType == 1019)
                {
                    gravtiation = GPS_GRAVITATION;
                    angularVelocity = GPS_ANGULAR_VELOCITY;
                }
                else if (ephObj.m_ui16MsgType == 1045)
                {
                    gravtiation = GAL_GRAVITATION;
                    angularVelocity = GAL_ANGULAR_VELOCITY;
                }
                else
                {
                    gravtiation = BDS_GRAVITATION;
                    angularVelocity = BDS_ANGULAR_VELOCITY;
                }

                // 1.计算观测瞬间卫星的平近点角M
                // timeDifference代表tk
                DOUBLE timeDifference = sec - gnssSec;
                // 平近点角M
                DOUBLE M =
                    ephObj.m_dbM0
                    + (sqrt(gravtiation / (pow(ephObj.m_dbAHalf, NUM_SIX))) + ephObj.m_dbDeltaN) * timeDifference;

                // 2.计算偏近点角E,利用迭代法计算，或者微分迭代法
                DOUBLE E = 0;
                DOUBLE Ek = 0;
                INT32 n = 0;
                for (n = 0, E = M, Ek = 0.0; fabs(E - Ek) > RTOL_KEPLER && n < MAX_ITER_KEPLER; n++)
                {
                    Ek = E;
                    E -= (E - ephObj.m_dbEccentricity * sin(E) - M) / (NUM_ONE - ephObj.m_dbEccentricity * cos(E));
                }
                if (n >= MAX_ITER_KEPLER)
                {
                    iRet = RETURN_ERROR_PARAMETER;
                }

                // 3.计算升交距角u 、卫星矢径r 、卫星轨道倾角i
                DOUBLE sinE = sin(E);
                DOUBLE cosE = cos(E);

                DOUBLE u = atan2(sqrt(NUM_ONE - ephObj.m_dbEccentricity * ephObj.m_dbEccentricity) * sinE,
                                 cosE - ephObj.m_dbEccentricity);
                DOUBLE r = ephObj.m_dbAHalf * ephObj.m_dbAHalf * (NUM_ONE - ephObj.m_dbEccentricity * cosE);
                DOUBLE i = ephObj.m_dbI0 + ephObj.m_dbIdot * timeDifference;
                DOUBLE sin2u = sin(NUM_TWO * u);
                DOUBLE cos2u = cos(NUM_TWO * u);
                u += ephObj.m_dbCus * sin2u + ephObj.m_dbCuc * cos2u;
                r += ephObj.m_dbCrs * sin2u + ephObj.m_dbCrc * cos2u;
                i += ephObj.m_dbCis * sin2u + ephObj.m_dbCic * cos2u;

                // 4.计算卫星在轨道面坐标系中的位置
                DOUBLE x = 0;
                DOUBLE y = 0;
                x = r * cos(u);
                y = r * sin(u);

                // 5.计算卫星在坐标系中的位置
                DOUBLE O = 0;
                DOUBLE cosi = cos(i);
                DOUBLE sinO = sin(O);
                DOUBLE cosO = cos(O);
                if (ephObj.m_ui16MsgType == 1046 && prn <= NUM_FIVE)
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
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        INT32 CGNSSEphemeris::CalcGloEphSatClock(const DOUBLE& sec, const SGlonassEphemeris& ephObj, DOUBLE& clockVal)
        {
            //获取系统秒数
            DOUBLE utcSec = time(nullptr);
            // 计算星历时间

            // utc时间转GPS时间
            DOUBLE gpsSec = CCalcTime::TimeConvert(utcSec, UTC, GPS);
            IGNSSTime* gpsObj = CTimeFactory::CreateTimeObj(GPS);
            gpsObj->SetTime(gpsSec);
            SGNSSTime gpsData;
            gpsObj->GetTime(gpsData);
            INT64 gpsWeek = static_cast<INT64>(gpsData.m_week);

            // 剔除掉一天内的秒,只保留整天的秒数
            DOUBLE secOfWeek =
                gpsData.m_secAndMsec - static_cast<DOUBLE>(static_cast<INT64>(gpsData.m_secAndMsec) % SEC_IN_DAY);
            // 计算一天内的秒数
            DOUBLE secOfDay = static_cast<DOUBLE>(static_cast<INT64>(gpsData.m_secAndMsec) % SEC_IN_DAY);

            // 通过星历文件计算具体的秒数m_ui16Tb单位为15min
            DOUBLE timeOfEphemeris =
                static_cast<DOUBLE>(ephObj.m_ui16Tb * SEC_OF_FIFTEEN_MIN) - static_cast<DOUBLE>(SEC_OF_3HOUR);
            if (timeOfEphemeris < secOfDay - SEC_IN_HALF_DAY)
            {
                timeOfEphemeris += SEC_IN_DAY;
            }
            else
            {
                timeOfEphemeris -= SEC_IN_DAY;
            }

            DOUBLE glonassEphemerisTime = static_cast<DOUBLE>(EPOCH_TO_GPST0) + static_cast<DOUBLE>(gpsWeek * WEEK_SEC)
                                          + secOfWeek + timeOfEphemeris;

            DOUBLE time = sec - glonassEphemerisTime;
            for (INT32 i = 0; i < NUM_TWO; ++i)
            {
                time -= -ephObj.m_dbTnTb + ephObj.m_dbGammaTb * time;
            }
            clockVal = -ephObj.m_dbTnTb + ephObj.m_dbGammaTb * time;
            return RETURN_SUCCESS;
        }

        INT32 CGNSSEphemeris::CalcGloEphSatPos(
            const DOUBLE& sec, const SGlonassEphemeris& ephObj, DOUBLE& xPos, DOUBLE& yPos, DOUBLE& zPos)
        {
            //获取系统秒数
            DOUBLE utcSec = time(nullptr);
            // 计算星历时间

            // utc时间转GPS时间
            DOUBLE gpsSec = CCalcTime::TimeConvert(utcSec, UTC, GPS);
            IGNSSTime* gpsObj = CTimeFactory::CreateTimeObj(GPS);
            gpsObj->SetTime(gpsSec);
            SGNSSTime gpsData;
            gpsObj->GetTime(gpsData);
            INT64 gpsWeek = static_cast<INT64>(gpsData.m_week);

            // 剔除掉一天内的秒,只保留整天的秒数
            DOUBLE secOfWeek =
                gpsData.m_secAndMsec - static_cast<DOUBLE>(static_cast<INT64>(gpsData.m_secAndMsec) % SEC_IN_DAY);
            // 计算一天内的秒数
            DOUBLE secOfDay = static_cast<DOUBLE>(static_cast<INT64>(gpsData.m_secAndMsec) % SEC_IN_DAY);

            // 通过星历文件计算具体的秒数m_ui16Tb单位为15min
            DOUBLE timeOfEphemeris =
                static_cast<DOUBLE>(ephObj.m_ui16Tb * SEC_OF_FIFTEEN_MIN) - static_cast<DOUBLE>(SEC_OF_3HOUR);
            if (timeOfEphemeris < secOfDay - SEC_IN_HALF_DAY)
            {
                timeOfEphemeris += SEC_IN_DAY;
            }
            else
            {
                timeOfEphemeris -= SEC_IN_DAY;
            }

            DOUBLE glonassEphemerisTime = static_cast<DOUBLE>(EPOCH_TO_GPST0) + static_cast<DOUBLE>(gpsWeek * WEEK_SEC)
                                          + secOfWeek + timeOfEphemeris;

            DOUBLE x[NUM_SIX] = {0};
            x[NUM_ZERO] = ephObj.m_dbXnTb;
            x[NUM_ONE] = ephObj.m_dbYnTb;
            x[NUM_TWO] = ephObj.m_dbZnTb;
            x[NUM_THREE] = ephObj.m_dbXnTbFirstDerivative;
            x[NUM_FOUR] = ephObj.m_dbYnTbFirstDerivative;
            x[NUM_FIVE] = ephObj.m_dbZnTbFirstDerivative;
            DOUBLE* acc = new DOUBLE[NUM_THREE];
            acc[NUM_ZERO] = ephObj.m_dbXnTbSecondDerivative;
            acc[NUM_ONE] = ephObj.m_dbYnTbSecondDerivative;
            acc[NUM_TWO] = ephObj.m_dbZnTbSecondDerivative;
            DOUBLE tt = 0;
            DOUBLE time = sec - glonassEphemerisTime;

            if (time < 0.0)
            {
                tt = -GLO_EPHENERI_INTEGRATION_STEP;
            }
            else
            {
                tt = GLO_EPHENERI_INTEGRATION_STEP;
            }
            for (; fabs(time) > GLO_EPHENERI_INTEGRATION_STEP_PRN; time -= tt)
            {
                if (fabs(time) < GLO_EPHENERI_INTEGRATION_STEP)
                    tt = time;
                Glorbit(tt, x, acc);
            }
            xPos = x[NUM_ZERO];
            yPos = x[NUM_ONE];
            zPos = x[NUM_TWO];
            return RETURN_SUCCESS;
        }

        DOUBLE CGNSSEphemeris::VectorDot(const DOUBLE* leftVector, const DOUBLE* rightVector, INT32 n)
        {
            DOUBLE result = 0.0;
            while (true)
            {
                result += leftVector[n] * rightVector[n];
                n--;
                if (n < 0)
                {
                    break;
                }
            }
            return result;
        }

        // 轨道微分方程
        void CGNSSEphemeris::OrbitDifferentialEquations(const DOUBLE* x, DOUBLE* xdot, const DOUBLE* acc)
        {
            DOUBLE a = 0;
            DOUBLE b = 0;
            DOUBLE c = 0;
            DOUBLE r2 = VectorDot(x, x, NUM_THREE);
            DOUBLE r3 = r2 * sqrt(r2);
            DOUBLE omg2 = 0;

            if (r2 <= 0.0)
            {
                xdot[NUM_ZERO] = 0;
                xdot[NUM_ONE] = 0;
                xdot[NUM_TWO] = 0;
                xdot[NUM_THREE] = 0;
                xdot[NUM_FOUR] = 0;
                xdot[NUM_FIVE] = 0;
                return;
            }

            a = ONE_POINT_FIVE * J2_GLO * GLO_GRAVITATION;
            b = NUM_FIVE * x[NUM_TWO] * x[NUM_TWO] / r2;
            c = -GLO_GRAVITATION / r3 - a * (NUM_ONE - b);
            xdot[NUM_ZERO] = x[NUM_THREE];
            xdot[NUM_ONE] = x[NUM_FOUR];
            xdot[NUM_TWO] = x[NUM_FIVE];
            xdot[NUM_THREE] = (c + omg2) * x[NUM_ZERO] + NUM_TWO * GLO_ANGULAR_VELOCITY * x[NUM_FOUR] + acc[NUM_ZERO];
            xdot[NUM_FOUR] = (c + omg2) * x[NUM_ONE] - NUM_TWO * GLO_ANGULAR_VELOCITY * x[NUM_THREE] + acc[NUM_ONE];
            xdot[NUM_FIVE] = (c - NUM_TWO * a) * x[NUM_TWO] + acc[NUM_TWO];
        }

        // glonass位置和速度的数值积分
        void CGNSSEphemeris::Glorbit(DOUBLE t, DOUBLE* x, const DOUBLE* acc)
        {
            DOUBLE k1[NUM_SIX] = {0};
            DOUBLE k2[NUM_SIX] = {0};
            DOUBLE k3[NUM_SIX] = {0};
            DOUBLE k4[NUM_SIX] = {0};
            DOUBLE w[NUM_SIX] = {0};

            OrbitDifferentialEquations(x, k1, acc);
            for (INT32 i = 0; i < NUM_SIX; ++i)
            {
                w[i] = x[i] + k1[i] * t / NUM_TWO;
            }
            OrbitDifferentialEquations(w, k2, acc);
            for (INT32 i = 0; i < NUM_SIX; ++i)
            {
                w[i] = x[i] + k2[i] * t / NUM_TWO;
            }
            OrbitDifferentialEquations(w, k3, acc);
            for (INT32 i = 0; i < NUM_SIX; ++i)
            {
                w[i] = x[i] + k3[i] * t;
            }
            OrbitDifferentialEquations(w, k4, acc);
            for (INT32 i = 0; i < NUM_SIX; ++i)
            {
                x[i] += (k1[i] + NUM_TWO * k2[i] + NUM_TWO * k3[i] + k4[i]) * t / NUM_SIX;
            }
        }
    } // namespace Math
} // namespace sixents
