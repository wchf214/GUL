#include "CGNSSAngle.h"
#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include "../DllMain/GNSSCommonDef.h"
#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace Math
    {
        CGNSSAngle::CGNSSAngle(const DOUBLE angleVal)
        {
            m_decimalDegree = angleVal;
            DegToDMS();
        }

        CGNSSAngle::CGNSSAngle(const INT32 degree, const UINT32 minute, const DOUBLE second)
        {
            if (minute >= 60 || second < 0 || second >= 60)
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
            if (minute >= 60 || second < 0 || second >= 60)
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

            if (formatType)
            {
                std::stringstream ss;
                ss << std::setprecision(DEGREE_ACCURACY) << m_decimalDegree;
                angleString = ss.str(); // 3.14159265358979
            }
            else
            {
                angleString += std::to_string(m_dms.m_degree) + ":";
                angleString += std::to_string(m_dms.m_minute) + ":";
                angleString += std::to_string(m_dms.m_second);
            }

            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::DegToDMS()
        {
            const INT32 MINUS_FLAG = NUM_NEGATIVE_ONE;

            // 取绝对值
            DOUBLE absDeg = fabs(m_decimalDegree);

            // 取整，度的整数部分
            m_dms.m_degree = static_cast<INT32>(floor(absDeg));

            DOUBLE degreeToMin = (absDeg - floor(absDeg)) * static_cast<DOUBLE>(BASE_60);
            m_dms.m_minute = static_cast<UINT32>(floor(degreeToMin));

            m_dms.m_second = static_cast<DOUBLE>(degreeToMin - m_dms.m_minute) * static_cast<DOUBLE>(BASE_60);

            if (m_decimalDegree < 0.0)
            {
                m_dms.m_degree *= MINUS_FLAG;
            }
            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::DMSToDeg()
        {
            const DOUBLE MINUS_FLAG = NUM_NEGATIVE_ONE;
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