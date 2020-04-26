#include "CGNSSAngle.h"

#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

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
                //DegToRad();
            }
            else
            {
                m_radian = angleVal;
                //  RadToDeg();
            }
        }

        CGNSSAngle::CGNSSAngle(const INT32 degree, const INT32 minute, const double second)
        {
            m_degree = degree;
            m_minute = minute;
            m_second = second;
        }

        CGNSSAngle::~CGNSSAngle()
        {
        }

        INT32 CGNSSAngle::GetLength(const bool formatType)
        {
            if (formatType == true)
            {
                std::stringstream ss;
                ss << std::setprecision(15) << m_decimalDegree;
                std::string str = ss.str();  // 3.14159265358979
                str += "°";
                std::cout << str << std::endl;
                INT32 curLen = strlen(str.c_str()) + 1;
                return curLen;
            }
            else
            {
                std::string str = std::to_string(m_degree);
                str += "°";
                str = std::to_string(m_minute);
                // str += "′";
                str = std::to_string(m_second);
                // str += "″";
                INT32 curLen = strlen(str.c_str()) + 1;
                return curLen;
            }
        }

        INT32 CGNSSAngle::ToDegString(char* angleString, INT32& len, const bool formatType)
        {
            /*  if (nullptr == angleString || m_formatString.length() != len)
              {
                  return m_formatString.length();
              }*/
            if (formatType)
            {
                std::stringstream ss;
                ss << std::setprecision(DEGREE_ACCURACY) << m_decimalDegree;
                std::string str = ss.str();  // 3.14159265358979
                str += "°";
                std::cout << str << std::endl;
                INT32 curLen = strlen(str.c_str()) + 1;
                if (curLen != len)
                {
                    return curLen;
                }
                strcpy_s(angleString, strlen(angleString) + 1, str.c_str());
            }
            else
            {
                std::string result = "";
                result += std::to_string(m_degree) + "";
                result += std::to_string(m_minute) + "";
                result += std::to_string(m_second) + "";

                strcpy_s(angleString, strlen(angleString) + 1, result.c_str());
            }
            return 1;
        }

        INT32 CGNSSAngle::DegToRad(const DOUBLE degree, DOUBLE& radian)
        {
            radian = degree * D2R;
            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::RadToDeg(const DOUBLE radian, DOUBLE& degree)
        {
            degree = radian * R2D;
            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::DegToDMS(const DOUBLE deg, INT32& degree, INT32& minute, DOUBLE& second)
        {
            do
            {
                const INT32 MINUS_FLAG = -1;
                DOUBLE absDeg = fabs(deg);
                degree = static_cast<INT32>(floor(absDeg));
                DOUBLE degreetomin = (absDeg - degree) * BASE_60;
                minute = static_cast<INT32>(floor(degreetomin));
                DOUBLE mintosec = (degreetomin - minute) * BASE_60;
                second = floor(mintosec);
                if (deg < 0) {
                    degree *= MINUS_FLAG;
                }
            } while (false);
            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::DMSToDeg(const INT32 degree, const INT32 minute, const DOUBLE second, DOUBLE& deg)
        {
            const DOUBLE MINUS_FLAG = -1.0;
            deg = fabs(degree) + minute / BASE_60 + second / DEG_TO_SEC;
            if (degree < 0.0) {
                deg *= MINUS_FLAG;
            }
            return RETURN_SUCCESS;
        }
    }
}