#include "CGNSSAngle.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "../DllMain/GNSSCommonDef.h"
#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace Math
    {
        CGNSSAngle::CGNSSAngle()
        {
            m_decimalDegree = 0;
            m_dms.m_degree = 0;
            m_dms.m_minute = 0;
            m_dms.m_second = 0;
        }

        CGNSSAngle::CGNSSAngle(const DOUBLE angleVal)
        {
            m_decimalDegree = angleVal;
            DegToDMS();
        }

        CGNSSAngle::CGNSSAngle(const INT32 degree, const UINT32 minute, const DOUBLE second)
        {
            if (minute >= BASE_60 || second < 0 || second >= BASE_60)
            {
                m_dms.m_degree = 0;
                m_dms.m_minute = 0;
                m_dms.m_second = 0;
            }
            else
            {
                m_dms.m_degree = degree;
                m_dms.m_minute = minute;
                m_dms.m_second = second;
            }
            DMSToDeg();
        }

        void CGNSSAngle::SetDeg(const DOUBLE degreeVal)
        {
            m_decimalDegree = degreeVal;
            DegToDMS();
        }

        DOUBLE CGNSSAngle::GetDeg() const
        {
            return m_decimalDegree;
        }

        void CGNSSAngle::SetDMS(const INT32 degree, const UINT32 minute, const DOUBLE second)
        {
            if (minute >= BASE_60 || second < 0 || second >= BASE_60)
            {
                return;
            }
            else
            {
                m_dms.m_degree = degree;
                m_dms.m_minute = minute;
                m_dms.m_second = second;
                DMSToDeg();
            }
        }

        SDMS CGNSSAngle::GetDMS() const
        {
            return m_dms;
        }

        CGNSSAngle::~CGNSSAngle()
        {}

        INT32 CGNSSAngle::DegToString(std::string& angleString, const BOOL_T formatType) const
        {
            std::stringstream formatStream("");
            formatStream.str("");
            if (formatType)
            {
                formatStream << std::fixed << std::setprecision(DEGREE_ACCURACY) << m_decimalDegree << DEGREE_UNIT;
            }
            else
            {
                formatStream << m_dms.m_degree << TIME_INTERVAL << m_dms.m_minute << TIME_INTERVAL << std::fixed
                             << std::setprecision(MATRIX_ACCURACY) << m_dms.m_second;
            }
            angleString = formatStream.str();
            formatStream.str(""); // 清空缓存
            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::DegToDMS()
        {
            const INT32 MINUS_FLAG = -1;

            // 取绝对值
            DOUBLE absDeg = fabs(m_decimalDegree);
            // 取整，度的整数部分
            m_dms.m_degree = static_cast<INT32>(floor(absDeg));
            // 取分部分
            DOUBLE degreeToMin = (absDeg - floor(absDeg)) * static_cast<DOUBLE>(BASE_60);
            m_dms.m_minute = static_cast<UINT32>(floor(degreeToMin));
            // 取秒部分
            m_dms.m_second = static_cast<DOUBLE>(degreeToMin - m_dms.m_minute) * static_cast<DOUBLE>(BASE_60);
            //如果小于0乘以-1
            if (m_decimalDegree < 0.0)
            {
                m_dms.m_degree *= MINUS_FLAG;
            }
            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::DMSToDeg()
        {
            const DOUBLE MINUS_FLAG = -1;
            m_decimalDegree = fabs(m_dms.m_degree) + static_cast<DOUBLE>(m_dms.m_minute) / BASE_60
                              + m_dms.m_second / static_cast<DOUBLE>(DEG_TO_SEC);
            if (m_dms.m_degree < 0)
            {
                m_decimalDegree *= MINUS_FLAG;
            }

            return RETURN_SUCCESS;
        }
    } // namespace Math
} // namespace sixents