#include "CGNSSAngle.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
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
        CGNSSAngle::CGNSSAngle(const DOUBLE angleVal, const BOOL_T angleType)
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

        CGNSSAngle::CGNSSAngle(const INT32 degree, const UINT32 minute, const DOUBLE second)
        {
            /* m_degree = degree;
             m_minute = minute;
             m_second = second;*/
            m_radian = 0;
            DMSToDeg();
        }

        void CGNSSAngle::SetDeg(const DOUBLE degreeVal)
        {
            m_decimalDegree = degreeVal;
            DegToRad();
            DegToDMS();
        }

        void CGNSSAngle::SetRad(const DOUBLE radVal)
        {
            m_radian = radVal;
            RadToDeg();
            DegToDMS();
        }

        DOUBLE CGNSSAngle::GetRad() const
        {
            return m_radian;
        }

        DOUBLE CGNSSAngle::GetDeg() const
        {
            return m_decimalDegree;
        }

        CGNSSAngle::~CGNSSAngle()
        {}

        INT32 CGNSSAngle::DegToRad()
        {
            return DegToRad(m_decimalDegree, m_radian);
        }

        INT32 CGNSSAngle::GetLength(const BOOL_T formatType) const
        {
            INT32 curLen = 0;
            if (formatType == true)
            {
                std::stringstream ss;
                ss.str("");
                ss << std::setprecision(DEGREE_ACCURACY) << m_decimalDegree;
                std::string str = ss.str(); // 3.14159265358979
                str += "";                  // 替代方案，待修改
                curLen = static_cast<INT32>(strlen(str.c_str()));
                ss.str("");
            }
            else
            {
                std::string result = "";
                // result += std::to_string(m_degree) + ":"; // 替代方案，待修改
                // result += std::to_string(m_minute) + ":";
                // result += std::to_string(m_second) + ":";
                curLen = static_cast<INT32>(strlen(result.c_str()));
            }
            return curLen;
        }

        INT32 CGNSSAngle::ToDegString(CHAR* angleString, UINT32& len, const BOOL_T formatType) const
        {
            INT32 iRet = RETURN_FAIL;
            do
            {
                if (angleString == nullptr)
                {
                    iRet = RETURN_NULL_PTR;
                    break;
                }
                if (formatType)
                {
                    std::stringstream ss;
                    ss << std::setprecision(DEGREE_ACCURACY) << m_decimalDegree;
                    std::string str = ss.str(); // 3.14159265358979
                    str += "";
                    memcpy(angleString, str.c_str(), len + NUM_ONE);
                }
                else
                {
                    std::string result = "";
                    /*   result += std::to_string(m_degree) + ":";
                       result += std::to_string(m_minute) + ":";
                       result += std::to_string(m_second) + ":";*/
                    memcpy(angleString, result.c_str(), len + NUM_ONE);
                }
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        INT32 CGNSSAngle::DegToRad(const DOUBLE degree, DOUBLE& radian)
        {
            radian = degree * D2R;
            return RETURN_SUCCESS;
        }

        INT32 CGNSSAngle::RadToDeg()
        {
            // return RadToDeg(m_radian, m_decimalDegree);
            return 0;
        }

        /*   INT32 CGNSSAngle::RadToDeg(const DOUBLE radian, DOUBLE& degree)
           {
               degree = radian * R2D;
               return RETURN_SUCCESS;
           }*/

        INT32 CGNSSAngle::DegToDMS()
        {
            return 0;
            //  return DegToDMS(m_decimalDegree, m_degree, m_minute, m_second);
        }

        // INT32 CGNSSAngle::DegToDMS(const DOUBLE deg, INT32& degree, UINT32& minute, DOUBLE& second)
        //{
        //    const INT32 MINUS_FLAG = NUM_NEGATIVE_ONE;

        //    // 取绝对值
        //    DOUBLE absDeg = fabs(deg);

        //    // 取整，度的整数部分
        //    degree = static_cast<INT32>(floor(absDeg));
        //    DOUBLE degreeToMin = (absDeg - floor(absDeg)) * static_cast<DOUBLE>(BASE_60);
        //    minute = static_cast<UINT32>(floor(degreeToMin));

        //    DOUBLE minToSec = static_cast<DOUBLE>(degreeToMin - minute) * BASE_60;
        //    second = minToSec;
        //    if (deg < 0.0)
        //    {
        //        degree *= MINUS_FLAG;
        //    }
        //    return RETURN_SUCCESS;
        //}

        INT32 CGNSSAngle::DMSToDeg()
        {
            return 0;
            // return DMSToDeg(m_degree, m_minute, m_second, m_decimalDegree);
        }

        /* INT32 CGNSSAngle::DMSToDeg(const INT32 degree, const UINT32 minute, const DOUBLE second, DOUBLE& deg)
         {
             INT32 iRet = RETURN_FAIL;
             do
             {
                 if (second < 0 || second >= 60 || minute >= 60)
                 {
                     iRet = RETURN_ERROR_PARAMETER;
                 }
                 const DOUBLE MINUS_FLAG = NUM_NEGATIVE_ONE;
                 deg = fabs(degree) + static_cast<DOUBLE>(minute) / BASE_60 + second / static_cast<DOUBLE>(DEG_TO_SEC);
                 if (degree < 0)
                 {
                     deg *= MINUS_FLAG;
                 }
                 iRet = RETURN_SUCCESS;
             } while (false);
             return iRet;
         }*/
    } // namespace Math
} // namespace sixents