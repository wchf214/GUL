#include "CGNSSAngle.h"
#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "../DllMain/GNSSCommonDef.h"
#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        CGNSSAngle::CGNSSAngle(const double angleVal, const bool angleType)
        {
            if (angleType)
            {
                m_decimalDegree = angleVal;
                DegToRad();
                DegToDMS();
            }
            else
            {
                m_radian = angleVal;
                RadToDeg();
                DegToDMS();
            }
        }

        void CGNSSAngle::SetDeg(const DOUBLE degreeVal)
        {
            m_decimalDegree = degreeVal;
        }

        void CGNSSAngle::SetRad(const DOUBLE radVal)
        {
            m_radian = radVal;
        }

        DOUBLE CGNSSAngle::GetRad()
        {
            return m_radian;
        }

        DOUBLE CGNSSAngle::GetDeg()
        {
            return m_decimalDegree;
        }

        CGNSSAngle::CGNSSAngle(const INT32 degree, const INT32 minute, const double second)
        {
            m_degree = degree;
            m_minute = minute;
            m_second = second;
        }

        CGNSSAngle::~CGNSSAngle()
        {}

        INT32 CGNSSAngle::DegToRad()
        {
            return DegToRad(m_decimalDegree, m_radian);
        }

        INT32 CGNSSAngle::GetLength(const bool formatType)
        {
            INT32 curLen = 0;
            if (formatType == true)
            {
                std::stringstream ss;
                ss.str("");
                ss << std::setprecision(DEGREE_ACCURACY) << m_decimalDegree;
                std::string str = ss.str(); // 3.14159265358979
                str += "'";                 // 替代方案，待修改
                curLen = static_cast<INT32>(strlen(str.c_str()));
                ss.str("");
            }
            else
            {
                std::string result = "";
                result += std::to_string(m_degree) + "du"; // 替代方案，待修改
                result += std::to_string(m_minute) + "'";
                result += std::to_string(m_second) + "\"";
                curLen = static_cast<INT32>(strlen(result.c_str()));
            }
            return curLen;
        }

        INT32 CGNSSAngle::ToDegString(char* angleString, UINT32& len, const bool formatType)
        {
            if (formatType)
            {
                std::stringstream ss;
                ss << std::setprecision(DEGREE_ACCURACY) << m_decimalDegree;
                std::string str = ss.str(); // 3.14159265358979
                str += "'";
                strcpy_s(angleString, len + 1, str.c_str());
            }
            else
            {
                std::string result = "";
                result += std::to_string(m_degree) + "du";
                result += std::to_string(m_minute) + "'";
                result += std::to_string(m_second) + "\"";
                strcpy_s(angleString, len + 1, result.c_str());
            }
            return 1;
        }

        INT32 CGNSSAngle::DegToRad(const DOUBLE degree, DOUBLE& radian)
        {
            radian = degree * D2R;
            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::RadToDeg()
        {
            return RadToDeg(m_radian, m_decimalDegree);
        }

        INT32 CGNSSAngle::RadToDeg(const DOUBLE radian, DOUBLE& degree)
        {
            degree = radian * R2D;
            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::DegToDMS()
        {
            return DegToDMS(m_decimalDegree, m_degree, m_minute, m_second);
        }

        INT32 CGNSSAngle::DegToDMS(const DOUBLE deg, INT32& degree, INT32& minute, double& second)
        {
            const INT32 MINUS_FLAG = -1;
            DOUBLE absDeg = fabs(deg);
            degree = static_cast<INT32>(floor(absDeg));
            double degreetomin = (absDeg - m_degree) * BASE_60;
            minute = static_cast<INT32>(floor(degreetomin));
            double mintosec = static_cast<double>(degreetomin - m_minute) * BASE_60;
            second = mintosec;
            if (deg < 0)
            {
                degree *= MINUS_FLAG;
            }
            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::DMSToDeg()
        {
            return DMSToDeg(m_degree, m_minute, m_second, m_decimalDegree);
        }

        INT32 CGNSSAngle::DMSToDeg(const INT32 degree, const INT32 minute, const DOUBLE second, DOUBLE& deg)
        {
            const DOUBLE MINUS_FLAG = -1.0;
            deg = fabs(degree) + minute / BASE_60 + second / DEG_TO_SEC;
            if (degree < 0.0)
            {
                deg *= MINUS_FLAG;
            }
            return RETURN_SUCCESS;
        }
    } // namespace GNSSUtilityLib
} // namespace sixents