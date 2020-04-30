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
            /**
             * @brief       角度构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   angleVal 角度/弧度
             * @param[in]   angleType 角度传入类型
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        传入类型为true代表角度，false代表弧度
             */
            explicit CGNSSAngle(const DOUBLE angleVal, const BOOL_T angleType = true);

            /**
             * @brief       角度构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   角度的度
             * @param[in]   角度的分
             * @param[in]   角度的秒
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            CGNSSAngle(const INT32 degree, const INT32 minute, const DOUBLE second);

            /**
             * @brief       析构函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            virtual ~CGNSSAngle();

            /**
             * @brief       设置角度
             * @author      pengshupan@sixents.com
             * @param[in]   degreeVal 角度值
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetDeg(const DOUBLE degreeVal);

            /**
             * @brief       获取角度
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      获取角度值
             * @retval      N/A
             * @note        N/A
             */
            DOUBLE GetDeg();

            /**
             * @brief       设置弧度
             * @author      pengshupan@sixents.com
             * @param[in]   radVal 弧度值
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetRad(const DOUBLE radVal);

            /**
             * @brief       获取弧度
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      获取弧度值
             * @retval      N/A
             * @note        N/A
             */
            DOUBLE GetRad();

            /**
             * @brief       获取字符串长度
             * @author      pengshupan@sixents.com
             * @param[in]   formatType 格式化类型
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        formatType为true代表输入的为度形式，formatType为false代表输入的度分秒形式
             */
            INT32 GetLength(const BOOL_T formatType);

            /**
             * @brief       角度格式化
             * @author      pengshupan@sixents.com
             * @param[in]   angleString 字符串存储指针
             * @param[in]   len 字符串长度
             * @param[in]   formatType 格式化类型
             * @param[out]  格式化后的字符串
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        formatType为true代表输入的为度形式，formatType为false代表输入的度分秒形式
             */
            INT32 ToDegString(CHAR* angleString, UINT32& len, const BOOL_T formatType);

            /**
             * @brief       角度形式转化为弧度形式
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 DegToRad();

            /**
             * @brief       角度形式转化为弧度形式
             * @author      pengshupan@sixents.com
             * @param[in]   degree 角度角度形式
             * @param[out]  radian 角度弧度形式
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 DegToRad(const DOUBLE degree, DOUBLE& radian);

            /**
             * @brief       弧度形式转化为角度形式
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 RadToDeg();

            /**
             * @brief       弧度形式转化为角度形式
             * @author      pengshupan@sixents.com
             * @param[in]   角度弧度形式
             * @param[out]  角度角度形式
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 RadToDeg(const DOUBLE radian, DOUBLE& degree);

            /**
             * @brief       角度形式转化为度分秒形式
             * @author      pengshupan@sixents.com
             * @param[in]   radian 角度度形式
             * @param[out]  degree 角度度
             * @param[out]  minute 角度分
             * @param[out]  second 角度秒
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 DegToDMS(const DOUBLE deg, INT32& degree, INT32& minute, DOUBLE& second);

            /**
             * @brief       角度形式转化为度分秒形式
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 DegToDMS();

            /**
             * @brief       度分秒形式转化为角度形式
             * @author      pengshupan@sixents.com
             * @param[in]   角度度
             * @param[in]   角度分
             * @param[in]   角度秒
             * @param[out]  角度度形式
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 DMSToDeg(const INT32 degree, const INT32 minute, const DOUBLE second, DOUBLE& deg);

            /**
             * @brief       度分秒形式转化为角度形式
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        N/A
             */
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
