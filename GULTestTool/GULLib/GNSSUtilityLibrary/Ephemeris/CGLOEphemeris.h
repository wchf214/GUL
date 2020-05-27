/** @file          CGNSSEphemeris
 *  @brief         星历类
 *  @details       所有星历相关的算法
 *  @author        pengshupan@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef GLOEPHEMERIS_H
#define GLOEPHEMERIS_H

#include "../DllMain/GNSSDataStruct.h"
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
        class CGLOEphemeris : public IGNSSEphemeris
        {
        public:
            /**
             * @brief       GLONASS卫星系统的构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            CGLOEphemeris();

            /**
             * @brief       GLONASS卫星系统的构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   gloephObj GLONASS卫星结构体
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            explicit CGLOEphemeris(const SGlonassEphemeris& gloephObj);

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
            virtual ~CGLOEphemeris() override;

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
            virtual void InitVar() override;

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
             * @brief       设置星历时间
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            INT32 SetGloEphTime(const DOUBLE gloEphTime);

        private:
            /**
             * @brief       计算GLONASS卫星系统的钟差
             * @author      pengshupan@sixents.com
             * @exception   N/A
             * @return      函数的执行结果
             * @note        N/A
             */
            INT32 CalcSatClock() override;

            /**
             * @brief       计算GLONASS卫星系统的
             * @author      pengshupan@sixents.com
             * @exception   N/A
             * @return      函数的执行结果
             * @note        N/A
             */
            INT32 CalcSatPos() override;

            DOUBLE CalcDiffTime();

            DOUBLE VectorDot(const DOUBLE* a, const DOUBLE* b, INT32 n);
            INT32 OrbitDifferentialEquations(const DOUBLE* x, DOUBLE* xdot, const DOUBLE* acc);
            INT32 Glorbit(DOUBLE t, DOUBLE* x, const DOUBLE* acc);

        private:
            SGlonassEphemeris m_gloEphObj; ///< GLONASS星历结构
            DOUBLE m_gloEphTime;           ///< m_gloEphTime,GLONASS星历时间，该时间在GPS系统下
        };
    } // end namespace Math
} // end namespace sixents
#endif
