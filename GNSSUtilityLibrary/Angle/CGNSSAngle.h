/**@file           CGNSSAngle
 *  @brief         角度类
 *  @details       所有角度相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _GNSS_ANGLE_H
#define _GNSS_ANGLE_H
#include <string>

namespace sixents
{
    namespace GNSSUtilityLib
    {
        class CGNSSAngle
        {
        public:
            // if angleType is true, angleVal is degree value
            // else angleVal is radian value
            // default angleType is true
            explicit CGNSSAngle(const double angleVal, const bool angleType = true);
            CGNSSAngle(const CGNSSAngle& angle);
            CGNSSAngle(const int degree, const int minute, const double second);
            ~CGNSSAngle();

            void SetDeg(const double degreeVal);
            double GetDeg();

            void SetRad(const double radVal);
            double GetRad();

            int GetLength(const bool formatType);
            // format angle to string
            // if formatType is true, angleString:dd.ssssss°
            // else angleString:dd°mm′ss.sss″
            int ToDegString(char* angleString, int& len, const bool formatType);

            // degree to radian
            // GUL_UC_026
            int DegToRad(double degree, double& radian);
            // radian to degree
            // GUL_UC_027
            int RadToDeg(double radian, double& degree);
            // transfrom between two degree form
            int DegToDMS(double Degree, int& degree, int& minute, double& second);
            int DMSToDeg(const int degree, const int minute, const double second, double& Degree);
        private:
            int m_degree;
            int m_minute;
            double m_second;
            double m_decimalDegree;     // degree of decimal form
            double m_radian;            // radian
            std::string m_formatString;
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents

#endif // !_GNSS_ANGLE_H
