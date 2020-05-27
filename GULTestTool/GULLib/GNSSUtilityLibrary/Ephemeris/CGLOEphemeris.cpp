#include "CGLOEphemeris.h"
#include <cmath>
#include <cstring>
#include "../Time/TimeCalc/CCalcTime.h"
#include "../Time/TimeSys/CGPSTime.h"
#include "../Time/TimeSys/CTimeFactory.h"
#include "../Time/TimeSys/IGNSSTime.h"

namespace sixents
{
    namespace Math
    {
        CGLOEphemeris::CGLOEphemeris()
        {
            InitVar();
        }

        CGLOEphemeris::CGLOEphemeris(const SGlonassEphemeris& gloephObj)
        {
            InitVar();
            m_gloEphObj = std::move(gloephObj);
        }

        CGLOEphemeris::~CGLOEphemeris()
        {}

        void CGLOEphemeris::InitVar()
        {
            IGNSSEphemeris::InitVar();
            memset(&m_gloEphObj, 0, sizeof(SGlonassEphemeris));
            m_gloEphTime = DOUBLE_ZONE_LITTLE;
        }

        INT32 CGLOEphemeris::SetGloEphTime(const DOUBLE gloEphTime)
        {
            if (gloEphTime <= 0)
            {
                return RETURN_ERROR_PARAMETER;
            }
            m_gloEphTime = gloEphTime;
            return RETURN_SUCCESS;
        }

        INT32 CGLOEphemeris::CalcSatClock()
        {
            INT32 iRet = RETURN_FAIL;
            do
            {
                DOUBLE timeDiff = GetCurTime() - m_gloEphTime;
                if (timeDiff == DOUBLE_ZONE_LITTLE)
                {
                    iRet = RETURN_ERROR_PARAMETER;
                    break;
                }
                for (INT32 i = 0; i < NUM_TWO; ++i)
                {
                    timeDiff -= -m_gloEphObj.m_dbTnTb + m_gloEphObj.m_dbGammaTb * timeDiff;
                }
                SetClock(-m_gloEphObj.m_dbTnTb + m_gloEphObj.m_dbGammaTb * timeDiff);
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        INT32 CGLOEphemeris::CalcSatPos()
        {
            INT32 iRet = RETURN_FAIL;
            do
            {
                DOUBLE x[NUM_SIX];
                memset(x, 0, sizeof(DOUBLE) * NUM_SIX);
                x[NUM_ZERO] = m_gloEphObj.m_dbXnTb;
                x[NUM_ONE] = m_gloEphObj.m_dbYnTb;
                x[NUM_TWO] = m_gloEphObj.m_dbZnTb;
                x[NUM_THREE] = m_gloEphObj.m_dbXnTbFirstDerivative;
                x[NUM_FOUR] = m_gloEphObj.m_dbYnTbFirstDerivative;
                x[NUM_FIVE] = m_gloEphObj.m_dbZnTbFirstDerivative;
                DOUBLE acc[NUM_THREE];
                memset(acc, 0, sizeof(DOUBLE) * NUM_THREE);
                acc[NUM_ZERO] = m_gloEphObj.m_dbXnTbSecondDerivative;
                acc[NUM_ONE] = m_gloEphObj.m_dbYnTbSecondDerivative;
                acc[NUM_TWO] = m_gloEphObj.m_dbZnTbSecondDerivative;
                DOUBLE timeStepLen = 0;
                DOUBLE timeDiff = GetCurTime() - m_gloEphTime;
                if (timeDiff == DOUBLE_ZONE_LITTLE)
                {
                    iRet = RETURN_ERROR_PARAMETER;
                    break;
                }
                if (timeDiff < 0.0)
                {
                    timeStepLen = -GLO_EPHENERI_INTEGRATION_STEP;
                }
                else
                {
                    timeStepLen = GLO_EPHENERI_INTEGRATION_STEP;
                }
                for (; fabs(timeDiff) > DOUBLE_ZONE_BIG; timeDiff -= timeStepLen)
                {
                    if (fabs(timeDiff) < GLO_EPHENERI_INTEGRATION_STEP)
                    {
                        timeStepLen = timeDiff;
                    }
                    Glorbit(timeStepLen, x, acc);
                }
                SetPos(x[NUM_ZERO], x[NUM_ONE], x[NUM_TWO]);
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        DOUBLE CGLOEphemeris::CalcDiffTime()
        {
            DOUBLE iRetVar = DOUBLE_ZONE_LITTLE;
            if (m_gloEphTime == DOUBLE_ZONE_LITTLE || GetCurTime() == DOUBLE_ZONE_LITTLE || m_gloEphObj.m_ui8SatId == 0)
            {
                return iRetVar;
            }
            // 把外部获取到的时间传入,此处是UTC时间，需要把UTC时间转换为GPS时间
            DOUBLE utcSec = m_gloEphTime;
            // 计算星历时间
            // 注意: 这里的时间还是UTC时间，只不过是利用GPS的函数来进行计算
            IGNSSTime* utcObj = CTimeFactory::CreateTimeObj(GPS);
            if (utcObj == nullptr)
            {
                return iRetVar;
            }
            utcObj->SetTime(utcSec);
            SGNSSTime utcData;
            utcObj->GetTime(utcData);
            INT64 utcWeek = static_cast<INT64>(utcData.m_week);

            // 剔除掉一天内的秒,只保留整天的秒数，使用fmod函数，剔除掉毫秒数
            DOUBLE secOfWeek = utcData.m_secAndMsec - fmod(utcData.m_secAndMsec, static_cast<DOUBLE>(SEC_IN_DAY));
            // 计算一天内的秒数
            DOUBLE secOfDay = fmod(utcData.m_secAndMsec, static_cast<DOUBLE>(SEC_IN_DAY));

            // 通过星历文件计算具体的秒数m_ui16Tb单位为15min ，在RTCM中为分钟，不是15分钟
            DOUBLE timeOfEphemeris =
                static_cast<DOUBLE>(m_gloEphObj.m_ui16Tb * BASE_60) - static_cast<DOUBLE>(SEC_OF_3HOUR);
            if (timeOfEphemeris < secOfDay - SEC_IN_HALF_DAY)
            {
                timeOfEphemeris += SEC_IN_DAY;
            }
            else if (timeOfEphemeris > secOfDay + SEC_IN_HALF_DAY)
            {
                timeOfEphemeris -= SEC_IN_DAY;
            }

            DOUBLE glonassEphemerisTime = static_cast<DOUBLE>(EPOCH_TO_GPST0) + static_cast<DOUBLE>(utcWeek * WEEK_SEC)
                                          + secOfWeek + timeOfEphemeris;
            DOUBLE glonassEphemerisTimeToGPSTime = CCalcTime::TimeConvert(glonassEphemerisTime, UTC, GPS);
            iRetVar = GetCurTime() - glonassEphemerisTimeToGPSTime;
            return iRetVar;
        }

        DOUBLE CGLOEphemeris::VectorDot(const DOUBLE* leftVector, const DOUBLE* rightVector, INT32 n)
        {
            if (leftVector == nullptr || rightVector == nullptr || n < 0)
            {
                return 0;
            }
            DOUBLE result = 0.0;
            while (true)
            {
                n--;
                result += leftVector[n] * rightVector[n];
                if (n <= 0)
                {
                    break;
                }
            }
            return result;
        }

        // 轨道微分方程
        INT32 CGLOEphemeris::OrbitDifferentialEquations(const DOUBLE* x, DOUBLE* xdot, const DOUBLE* acc)
        {
            INT32 iRet = RETURN_FAIL;
            do
            {
                if (x == nullptr || xdot == nullptr || acc == nullptr)
                {
                    iRet = RETURN_NULL_PTR;
                    break;
                }
                DOUBLE a = 0;
                DOUBLE b = 0;
                DOUBLE c = 0;
                DOUBLE r2 = VectorDot(x, x, NUM_THREE);
                DOUBLE r3 = r2 * sqrt(r2);
                DOUBLE omg2 = pow(GLO_ANGULAR_VELOCITY, NUM_TWO);
                if (r2 <= 0.0)
                {
                    xdot[NUM_ZERO] = 0;
                    xdot[NUM_ONE] = 0;
                    xdot[NUM_TWO] = 0;
                    xdot[NUM_THREE] = 0;
                    xdot[NUM_FOUR] = 0;
                    xdot[NUM_FIVE] = 0;
                    break;
                }
                a = ONE_POINT_FIVE * J2_GLO * GLO_GRAVITATION * pow(PZ90_EARTH_LONG_RADIUS, NUM_TWO) / r2 / r3;
                b = (NUM_FIVE * x[NUM_TWO] * x[NUM_TWO]) / static_cast<DOUBLE>(r2);
                c = -GLO_GRAVITATION / r3 - a * (NUM_ONE - b);
                xdot[NUM_ZERO] = x[NUM_THREE];
                xdot[NUM_ONE] = x[NUM_FOUR];
                xdot[NUM_TWO] = x[NUM_FIVE];
                xdot[NUM_THREE] = (c + omg2) * x[NUM_ZERO]
                                  + static_cast<DOUBLE>(NUM_TWO) * GLO_ANGULAR_VELOCITY * x[NUM_FOUR] + acc[NUM_ZERO];
                xdot[NUM_FOUR] = (c + omg2) * x[NUM_ONE]
                                 - static_cast<DOUBLE>(NUM_TWO) * GLO_ANGULAR_VELOCITY * x[NUM_THREE] + acc[NUM_ONE];
                xdot[NUM_FIVE] = (c - static_cast<DOUBLE>(NUM_TWO) * a) * x[NUM_TWO] + acc[NUM_TWO];
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        // glonass位置和速度的数值积分
        INT32 CGLOEphemeris::Glorbit(DOUBLE t, DOUBLE* x, const DOUBLE* acc)
        {
            INT32 iRet = RETURN_FAIL;
            do
            {
                if (x == nullptr || acc == nullptr)
                {
                    iRet = RETURN_NULL_PTR;
                    break;
                }
                DOUBLE k1[NUM_SIX] = {0};
                DOUBLE k2[NUM_SIX] = {0};
                DOUBLE k3[NUM_SIX] = {0};
                DOUBLE k4[NUM_SIX] = {0};
                DOUBLE w[NUM_SIX] = {0};
                OrbitDifferentialEquations(x, k1, acc);
                for (INT32 i = 0; i < NUM_SIX; ++i)
                {
                    w[i] = x[i] + k1[i] * t / static_cast<DOUBLE>(NUM_TWO);
                }
                OrbitDifferentialEquations(w, k2, acc);
                for (INT32 i = 0; i < NUM_SIX; ++i)
                {
                    w[i] = x[i] + k2[i] * t / static_cast<DOUBLE>(NUM_TWO);
                }
                OrbitDifferentialEquations(w, k3, acc);
                for (INT32 i = 0; i < NUM_SIX; ++i)
                {
                    w[i] = x[i] + k3[i] * t;
                }
                OrbitDifferentialEquations(w, k4, acc);
                for (INT32 i = 0; i < NUM_SIX; ++i)
                {
                    x[i] +=
                        (k1[i] + static_cast<DOUBLE>(NUM_TWO) * k2[i] + static_cast<DOUBLE>(NUM_TWO) * k3[i] + k4[i])
                        * t / static_cast<DOUBLE>(NUM_SIX);
                }
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        DOUBLE CGLOEphemeris::GetClock()
        {
            CalcSatClock();
            return IGNSSEphemeris::GetClock();
        }

        SXYZ CGLOEphemeris::GetPos()
        {
            CalcSatPos();
            return IGNSSEphemeris::GetPos();
        }
    } // end namespace Math
} // end namespace sixents