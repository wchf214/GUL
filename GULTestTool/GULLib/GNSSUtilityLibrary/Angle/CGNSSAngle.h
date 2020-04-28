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

#include "../DllMain/GNSSDataStruct.h"

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
            explicit CGNSSAngle(const DOUBLE angleVal, const BOOL_T angleType = true);
            CGNSSAngle(const CGNSSAngle& angle);
            CGNSSAngle(const INT32 degree, const INT32 minute, const DOUBLE second);
            ~CGNSSAngle();

            void SetDeg(const DOUBLE degreeVal);
            DOUBLE GetDeg();

            void SetRad(const DOUBLE radVal);
            DOUBLE GetRad();

            INT32 GetLength(const BOOL_T formatType);
            // format angle to string
            // if formatType is true, angleString:dd.ssssss°
            // else angleString:dd°mm′ss.sss″
            INT32 ToDegString(CHAR* angleString, INT32& len, const BOOL_T formatType);

            // degree to radian
            // GUL_UC_026
            INT32 DegToRad();
            INT32 DegToRad(const DOUBLE degree, DOUBLE& radian);
            // radian to degree
            // GUL_UC_027
            INT32 RadToDeg();
            INT32 RadToDeg(const DOUBLE radian, DOUBLE& degree);
            // transfrom between two degree form
            INT32 DegToDMS(const DOUBLE deg, INT32& degree, INT32& minute, DOUBLE& second);
            INT32 DegToDMS();
            INT32 DMSToDeg(const INT32 degree, const INT32 minute, const DOUBLE second, DOUBLE& deg);
            INT32 DMSToDeg();
        private:
            INT32 m_degree;
            INT32 m_minute;
            DOUBLE m_second;
            DOUBLE m_decimalDegree; // degree of decimal form
            DOUBLE m_radian;        // radian
            std::string m_formatString;
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents

#endif // !_GNSS_ANGLE_H
