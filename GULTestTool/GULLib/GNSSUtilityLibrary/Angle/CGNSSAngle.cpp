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
                ss << std::setprecision(15) << m_decimalDegree;
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

        INT32 CGNSSAngle::DegToRad(double degree, double& radian)
        {
            do
            {
                radian = (degree * PI) / 180;
            } while (false);
            return 1;
        }

        INT32 CGNSSAngle::RadToDeg(double radian, double& degree)
        {
            do
            {
                degree = radian * 180 / PI;
            } while (false);
            return 1;
        }

        INT32 CGNSSAngle::DegToDMS(double Degree, INT32& degree, INT32& minute, double& second)
        {
            do
            {
                INT32 sign = 0;
                if (Degree >= 0)
                {
                    sign = 1;
                }
                else
                {
                    sign = -1;
                }
                Degree = fabs(Degree);
                degree = floor(Degree);
                double degreetomin = (Degree - degree)*NUM_SIXTY;
                minute = floor(degreetomin);
                double mintosec = (degreetomin - minute)*NUM_SIXTY;
                second = floor(mintosec);
                degree *= sign;
            } while (false);
            return 1;
        }
        INT32 CGNSSAngle::DMSToDeg(const INT32 degree, const INT32 minute, const double second, double& Degree)
        {
            do
            {
                double sign = degree < 0.0 ? -1.0 : 1.0;
                Degree = sign * (fabs(degree) + minute / NUM_SIXTY + second / DEG_TO_SEC);
            } while (false);
            return 1;
        }
    }
}