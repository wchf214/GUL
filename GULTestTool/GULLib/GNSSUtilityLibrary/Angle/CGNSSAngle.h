/** @file          CGNSSAngle
 *  @brief         角度类
 *  @details       所有角度相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef GNSS_ANGLE_H
#define GNSS_ANGLE_H
#include <string>

#include "../DllMain/GNSSCommonDef.h"
#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace Math
    {
        /**
         *  @class       CGNSSAngle
         *  @brief       角度类
         *  @author      pengshupan@sixents.com
         *  @note        角度转换与格式化算法
         */
        class CGNSSAngle
        {
        public:
            /**
             * @brief       角度构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   angleVal        角度/弧度
             * @param[in]   angleType       角度传入类型
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        传入类型为true代表角度，false代表弧度
             */
            CGNSSAngle();

            /**
             * @brief       角度构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   angleVal        角度/弧度
             * @param[in]   angleType       角度传入类型
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        传入类型为true代表角度，false代表弧度
             */
            explicit CGNSSAngle(const DOUBLE angleVal);

            /**
             * @brief       角度构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   degree      角度的度
             * @param[in]   minute      角度的分
             * @param[in]   second      角度的秒
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            CGNSSAngle(const INT32 degree, const UINT32 minute, const DOUBLE second);

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
             * @param[in]   degreeVal       角度值
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
            DOUBLE GetDeg() const;

            /**
             * @brief       获取角度
             * @author      pengshupan@sixents.com
             * @param[in]   degree DMS的度
             * @param[in]   minute DMS的分
             * @param[in]   second DMS的秒
             * @param[out]  N/A
             * @exception   N/A
             * @return      获取角度值
             * @retval      N/A
             * @note        N/A
             */
            void SetDMS(const INT32 degree, const UINT32 minute, const DOUBLE second);

            /**
             * @brief       获取DMS
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      获取DMS
             * @retval      N/A
             * @note        N/A
             */
            SDMS GetDMS() const;

            /**
             * @brief       角度格式化
             * @author      pengshupan@sixents.com
             * @param[in]   angleString         字符串存储指针
             * @param[in]   len                 字符串长度
             * @param[in]   formatType          格式化类型
             * @param[out]  angleString         格式化后的字符串
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        formatType为true代表输入的为度形式，formatType为false代表输入的度分秒形式
             */
            INT32 DegToString(std::string& angleString, const BOOL_T formatType) const;

        private:
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
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 DMSToDeg();

        private:
            SDMS m_dms;
            DOUBLE m_decimalDegree; // degree of decimal form
        };
    } // end namespace Math
} // end namespace sixents

#endif // !_GNSS_ANGLE_H
