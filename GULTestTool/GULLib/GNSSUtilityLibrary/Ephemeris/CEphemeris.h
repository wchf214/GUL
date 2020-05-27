/** @file          CGNSSEphemeris
 *  @brief         星历类
 *  @details       所有星历相关的算法
 *  @author        pengshupan@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef EPHEMERIS_H
#define EPHEMERIS_H

#include "IGNSSEphemeris.h"

namespace sixents
{
    namespace Math
    {
        /**
         *  @class       IGNSSEphemeris
         *  @brief       星历抽象类
         *  @author      pengshupan@sixents.com
         *  @note        星历运算算法
         */
        class CEphemeris : public IGNSSEphemeris
        {
        public:
            CEphemeris(); // 允许声明空对象
            /**
             * @brief       GPS,GAL,BDS卫星系统的构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            explicit CEphemeris(const SEphemeris& ephObj);

            /**
             * @brief       析构函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            virtual ~CEphemeris();

            /**
             * @brief       设置GPS,GAL,BDS星历
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            INT32 SetEphemeris();

            /**
             * @brief       获得卫星钟差
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      卫星钟差
             * @retval      N/A
             * @note        N/A
             */
            virtual DOUBLE GetClock() override;

            /**
             * @brief       获得卫星位置
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      卫星位置
             * @retval      N/A
             * @note        N/A
             */
            virtual SXYZ GetPos() override;

            /**
             * @brief       初始化成员变量
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @note        N/A
             */
            virtual void InitVar() override;

        private:
            /**
             * @brief       计算GPS,GAL,BDS卫星系统的时间差
             * @author      pengshupan@sixents.com
             * @exception   N/A
             * @param[in]   N/A
             * @param[out]  N/A
             * @return      GPS,GAL,BDS卫星系统的时间差
             * @note        N/A
             */
            DOUBLE CalcDiffTime(const UINT32 timeType);

            /**
             * @brief       计算GPS,GAL,BDS卫星系统的钟差
             * @author      pengshupan@sixents.com
             * @exception   N/A
             * @return      函数的执行结果
             * @note        N/A
             */
            virtual INT32 CalcSatClock() override;

            /**
             * @brief       计算GPS,GAL,BDS卫星系统的
             * @author      pengshupan@sixents.com
             * @exception   N/A
             * @return      函数的执行结果
             * @note        N/A
             */
            virtual INT32 CalcSatPos() override;

        private:
            SEphemeris m_ephObj; ///< 非GLONASS星历结构
        };
    } // end namespace Math
} // end namespace sixents
#endif
