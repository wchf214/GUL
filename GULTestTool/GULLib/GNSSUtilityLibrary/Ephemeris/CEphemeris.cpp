#include "CEphemeris.h"
#include <cmath>
#include <cstring>
#include "../Time/TimeCalc/CCalcTime.h"
#include "../Time/TimeSys/CTimeFactory.h"
#include "../Time/TimeSys/IGNSSTime.h"

namespace sixents
{
    namespace Math
    {
        CEphemeris::CEphemeris()
        {
            InitVar();
        }

        CEphemeris::CEphemeris(const SEphemeris& ephObj)
        {
            InitVar();
            m_ephObj = std::move(ephObj);
        }

        CEphemeris::~CEphemeris()
        {}

        void CEphemeris::InitVar()
        {
            IGNSSEphemeris::InitVar();
            memset(&m_ephObj, 0, sizeof(SEphemeris));
        }

        DOUBLE CEphemeris::CalcDiffTime(const UINT32 timeType)
        {
            DOUBLE iRetVar = DOUBLE_ZONE_LITTLE;
            // 传入的时间为负数或者星历电文卫星编号为0表示目前星历结构体没有数据
            if (GetCurTime() < 0 || m_ephObj.m_ui8SatId == 0)
            {
                return iRetVar;
            }

            SGNSSTime srcTime;
            IGNSSTime* srcTimeObj = nullptr;
            if (m_ephObj.m_ui16MsgType == GPS_EPH)
            {
                srcTimeObj = CTimeFactory::CreateTimeObj(GPS);
                srcTime = {
                    static_cast<UINT64>(m_ephObj.m_ui16WeekNum + GPS_WEEK_LOOP), static_cast<DOUBLE>(timeType), GPS};
            }
            else if (m_ephObj.m_ui16MsgType == GAL_EPH_1 || m_ephObj.m_ui16MsgType == GAL_EPH_2)
            {
                srcTimeObj = CTimeFactory::CreateTimeObj(GALILEO);
                srcTime = {static_cast<UINT64>(m_ephObj.m_ui16WeekNum), static_cast<DOUBLE>(timeType), GALILEO};
            }
            else if (m_ephObj.m_ui16MsgType == BDS_EPH)
            {
                srcTimeObj = CTimeFactory::CreateTimeObj(BDS);
                srcTime = {static_cast<UINT64>(m_ephObj.m_ui16WeekNum), static_cast<DOUBLE>(timeType), BDS};
            }
            else
            {
                // 不存在的卫星系统
                return iRetVar;
            }

            if (srcTimeObj == nullptr)
            {
                return iRetVar;
            }
            srcTimeObj->SetTime(srcTime);
            // 对应的卫星时间，把对应的w+s转s
            DOUBLE gnssSec = 0.0;
            srcTimeObj->GetTime(gnssSec);

            // BDS需要转换为GPS时间
            if (m_ephObj.m_ui16MsgType == BDS_EPH)
            {
                gnssSec = CCalcTime::TimeConvert(gnssSec, BDS, GPS);
            }
            iRetVar = GetCurTime() - gnssSec;
            return iRetVar;
        }

        INT32 CEphemeris::CalcSatClock()
        {
            INT32 iRet = RETURN_FAIL;
            do
            {
                DOUBLE timeDifference = CalcDiffTime(m_ephObj.m_ui32Toc);
                for (INT32 i = 0; i < NUM_TWO; ++i)
                {
                    timeDifference -= m_ephObj.m_dbAf0 + m_ephObj.m_dbAf1 * timeDifference
                                      + m_ephObj.m_dbAf2 * timeDifference * timeDifference;
                }

                SetClock(m_ephObj.m_dbAf0 + m_ephObj.m_dbAf1 * timeDifference
                         + m_ephObj.m_dbAf2 * timeDifference * timeDifference);
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        INT32 CEphemeris::CalcSatPos()
        {
            INT32 iRet = RETURN_FAIL;
            do
            {
                if (pow(m_ephObj.m_dbAHalf, NUM_TWO) <= 0)
                {
                    SetPos(0, 0, 0);
                    iRet = RETURN_ERROR_PARAMETER;
                    break;
                }

                DOUBLE timeDifference = CalcDiffTime(m_ephObj.m_ui32Toe);

                // 引力常量
                DOUBLE gravtiation = 0;
                // 角速度
                DOUBLE angularVelocity = 0;

                INT32 prn = 0;
                if (m_ephObj.m_ui16MsgType == GPS_EPH)
                {
                    gravtiation = GPS_GRAVITATION;
                    angularVelocity = GPS_ANGULAR_VELOCITY;
                }
                else if (m_ephObj.m_ui16MsgType == GAL_EPH_1 || m_ephObj.m_ui16MsgType == GAL_EPH_2)
                {
                    gravtiation = GAL_GRAVITATION;
                    angularVelocity = GAL_ANGULAR_VELOCITY;
                }
                else
                {
                    gravtiation = BDS_GRAVITATION;
                    angularVelocity = BDS_ANGULAR_VELOCITY;
                }

                //注意，m_dbAHalf是地球长半轴不是半轴
                DOUBLE earthA = m_ephObj.m_dbAHalf;

                // 平近点角M
                DOUBLE M = m_ephObj.m_dbM0
                           + (sqrt(gravtiation / (pow(earthA, NUM_THREE))) + m_ephObj.m_dbDeltaN) * timeDifference;

                // 2.计算偏近点角E,利用迭代法计算，或者微分迭代法
                DOUBLE E = 0;
                DOUBLE Ek = 0;
                INT32 n = 0;
                for (n = 0, E = M, Ek = 0.0; fabs(E - Ek) > RTOL_KEPLER && n < MAX_ITER_KEPLER; ++n)
                {
                    Ek = E;
                    E -= (E - m_ephObj.m_dbEccentricity * sin(E) - M) / (NUM_ONE - m_ephObj.m_dbEccentricity * cos(E));
                }
                if (n >= MAX_ITER_KEPLER)
                {
                    iRet = RETURN_ERROR_PARAMETER;
                }

                // 3.计算升交距角u 、卫星矢径r 、卫星轨道倾角i
                DOUBLE sinE = sin(E);
                DOUBLE cosE = cos(E);
                DOUBLE u = atan2(sqrt(NUM_ONE - m_ephObj.m_dbEccentricity * m_ephObj.m_dbEccentricity) * sinE,
                                 cosE - m_ephObj.m_dbEccentricity)
                           + m_ephObj.m_dbArgumentOfPerigee;
                DOUBLE r = earthA * (NUM_ONE - m_ephObj.m_dbEccentricity * cosE);
                DOUBLE i = m_ephObj.m_dbI0 + m_ephObj.m_dbIdot * timeDifference;
                DOUBLE sin2u = sin(NUM_TWO * u);
                DOUBLE cos2u = cos(NUM_TWO * u);
                u += m_ephObj.m_dbCus * sin2u + m_ephObj.m_dbCuc * cos2u;
                r += m_ephObj.m_dbCrs * sin2u + m_ephObj.m_dbCrc * cos2u;
                i += m_ephObj.m_dbCis * sin2u + m_ephObj.m_dbCic * cos2u;

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
                if (m_ephObj.m_ui16MsgType == BDS_EPH && prn <= NUM_FIVE)
                {
                    O = m_ephObj.m_dbOmega0 + m_ephObj.m_dbOmegaDot * timeDifference
                        - angularVelocity * m_ephObj.m_ui32Toe;
                    DOUBLE xg = x * cosO - y * cosi * sinO;
                    DOUBLE yg = x * sinO + y * cosi * cosO;
                    DOUBLE zg = y * sin(i);
                    DOUBLE sino = sin(angularVelocity * timeDifference);
                    DOUBLE coso = cos(angularVelocity * timeDifference);

                    SetPos(xg * coso + yg * sino * COS_5 + zg * sino * SIN_5,
                           -xg * sino + yg * coso * COS_5 + zg * coso * SIN_5,
                           -yg * SIN_5 + zg * COS_5);
                }
                else
                {
                    O = m_ephObj.m_dbOmega0 + (m_ephObj.m_dbOmegaDot - angularVelocity) * timeDifference
                        - angularVelocity * m_ephObj.m_ui32Toe;
                    sinO = sin(O);
                    cosO = cos(O);
                    SetPos(x * cosO - y * cosi * sinO, x * sinO + y * cosi * cosO, y * sin(i));
                }
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        INT32 CEphemeris::SetEphemeris()
        {
            return 0;
        }

        DOUBLE CEphemeris::GetClock()
        {
            CalcSatClock();
            return IGNSSEphemeris::GetClock();
        }

        SXYZ CEphemeris::GetPos()
        {
            CalcSatPos();
            return IGNSSEphemeris::GetPos();
        }
    } // end namespace Math
} // end namespace sixents
