/** @file          CGNSSEphemeris
 *  @brief         星历类
 *  @details       所有星历相关的算法
 *  @author        pengshupan@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef IGNSS_EPHEMERIS_H
#define IGNSS_EPHEMERIS_H

#include "../DllMain/GNSSCommonDef.h"
#include "../DllMain/GNSSDataStruct.h"

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
        class IGNSSEphemeris
        {
        public:
            /**
             * @brief       构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            IGNSSEphemeris();
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
            virtual ~IGNSSEphemeris();

        public:
            /**
             * @brief       获得卫星钟差
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            virtual DOUBLE GetClock();

            /**
             * @brief       设置卫星钟差
             * @author      pengshupan@sixents.com
             * @param[in]   clock 卫星钟差
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetClock(const DOUBLE clock);

            /**
             * @brief       获得卫星位置
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            virtual SXYZ GetPos();

            /**
             * @brief       设置卫星位置
             * @author      pengshupan@sixents.com
             * @param[in]   pos  位置结构体数据
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetPos(const SXYZ& pos);

            /**
             * @brief       设置卫星位置
             * @author      pengshupan@sixents.com
             * @param[in]   x 空间直角x坐标
             * @param[in]   y 空间直角y坐标
             * @param[in]   z 空间直角z坐标
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetPos(const DOUBLE x, const DOUBLE y, const DOUBLE z);

            /**
             * @brief       设置当前时间
             * @author      pengshupan@sixents.com
             * @param[in]   time 当前时间
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数执行结果
             * @retval      N/A
             * @note        N/A
             */
            INT32 SetCurTime(const DOUBLE time);

            /**
             * @brief       获取当前时间
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      当前时间
             * @retval      N/A
             * @note        N/A
             */
            DOUBLE GetCurTime() const;

        protected:
            /**
             * @brief       初始化成员变量
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            virtual void InitVar();

            /**
             * @brief       计算卫星系统的钟差接口
             * @author      pengshupan@sixents.com
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            virtual INT32 CalcSatClock() = 0;

            /**
             * @brief       计算卫星系统的位置接口
             * @author      pengshupan@sixents.com
             * @exception   N/A
             * @return      函数的执行结果
             * @note        N/A
             */
            virtual INT32 CalcSatPos() = 0;

        private:
            DOUBLE m_curTime; ///< 当前时间，传入GPS时间
            DOUBLE m_clock;   ///<卫星钟差
            SXYZ m_pos;       ///<卫星位置
        };
    } // end namespace Math
} // end namespace sixents
#endif
