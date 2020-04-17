#include "CGNSSAngle.h"

#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
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

        CGNSSAngle::CGNSSAngle(const int degree, const int minute, const double second)
        {
            m_degree = degree;
            m_minute = minute;
            m_second = second;
        }

        CGNSSAngle::~CGNSSAngle()
        {
        }
        int CGNSSAngle::GetLength(const bool formatType)
        {
            if (formatType == true)
            {
                std::stringstream ss;
                ss << std::setprecision(15) << m_decimalDegree;
                std::string str = ss.str();  // 3.14159265358979
                str += "¡ã";
                std::cout << str << std::endl;
                int curLen = strlen(str.c_str()) + 1;
                return curLen;
            }
            else
            {
                std::string str = std::to_string(m_degree);
                str += "¡ã";
                str = std::to_string(m_minute);
                str += "¡ä";
                str = std::to_string(m_second);
                str += "¡å";
                int curLen = strlen(str.c_str()) + 1;
                return curLen;
            }
        }

        int CGNSSAngle::ToDegString(char* angleString, int& len, const bool formatType)
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
                str += "¡ã";
                std::cout << str << std::endl;
                int curLen = strlen(str.c_str()) + 1;
                if (curLen != len)
                {
                    return curLen;
                }
                strcpy_s(angleString, strlen(angleString) + 1, str.c_str());
            }
            else
            {
                std::string result = "";
                result += std::to_string(m_degree) + "¡ã";
                result += std::to_string(m_minute) + "¡ä";
                result += std::to_string(m_second) + "¡å";

                strcpy_s(angleString, strlen(angleString) + 1, result.c_str());
            }
            return 1;
        }

        int CGNSSAngle::DegToRad(double degree, double& radian)
        {
            do
            {
                radian = (degree * 3.1415926) / 180;
            } while (false);
            return 1;
        }

        int CGNSSAngle::RadToDeg(double radian, double& degree)
        {
            do
            {
                degree = radian * 180 / 3.1415926;
            } while (false);
            return 1;
        }

        int CGNSSAngle::DegToDMS(double Degree, int& degree, int& minute, double& second)
        {
            do
            {
                int sign = 0;
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
                double degreetomin = (Degree - degree)*60.0;
                minute = floor(degreetomin);

                double mintosec = (degreetomin - minute)*60.0;
                second = floor(mintosec);

                degree *= sign;
            } while (false);
            return 1;
        }
        int CGNSSAngle::DMSToDeg(const int degree, const int minute, const double second, double& Degree)
        {
            do
            {
                double sign = degree < 0.0 ? -1.0 : 1.0;
                Degree = sign * (fabs(degree) + minute / 60.0 + second / 3600.0);
            } while (false);
            return 1;
        }
    }
}