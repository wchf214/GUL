/** @file          CGNSSEphemeris
 *  @brief         星历类
 *  @details       所有星历相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef GNSS_EPHEMERIS_H
#define GNSS_EPHEMERIS_H

#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace Math
    {
        /**
         *  @class       CGNSSEphemeris
         *  @brief       星历类
         *  @author      pengshupan@sixents.com
         *  @note        星历运算算法
         */
        class CGNSSEphemeris
        {
        public:
            /**
             * @brief       GPS,GALILEO,BDS卫星系统的构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            explicit CGNSSEphemeris();

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
            virtual ~CGNSSEphemeris();

            /**
             * @brief       计算GPS,GALILEO,BDS卫星系统的钟差
             * @author      pengshupan@sixents.com
             * @param[in]   sec             接收机获取星历文件的时间(s)
             * @param[in]   ephObj          GPS,GALILEO,BDS星历文件
             * @param[out]  clockVal        GPS,GALILEO,BDS卫星系统的钟差
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            INT32 CalcEphSatClock(const DOUBLE& sec, const SEphemeris& ephObj, DOUBLE& clockVal);

            /**
             * @brief       计算GPS,GALILEO,BDS卫星系统的位置
             * @author      pengshupan@sixents.com
             * @param[in]   sec         接收机获取星历文件的时间(s)
             * @param[in]   ephObj      GPS,GALILEO,BDS星历文件
             * @param[out]  x           GPS,GALILEO,BDS卫星系统位置x
             * @param[out]  y           GPS,GALILEO,BDS卫星系统位置y
             * @param[out]  z           GPS,GALILEO,BDS卫星系统位置z
             * @exception   N/A
             * @return      函数的执行结果
             * @note        N/A
             */
            INT32 CalcEphSatPos(const DOUBLE& sec, const SEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z);

            /**
             * @brief       计算GLONASS卫星系统的钟差
             * @author      pengshupan@sixents.com
             * @param[in]   sec             接收机获取星历文件的时间(s)
             * @param[in]   ephObj          GLONASS星历文件
             * @param[out]  clockVal        GLONASS卫星系统的钟差
             * @exception   N/A
             * @return      函数的执行结果
             * @note        N/A
             */
            INT32 CalcGloEphSatClock(const DOUBLE& sec, const SGlonassEphemeris& ephObj, DOUBLE& clockVal);

            /**
             * @brief       计算GLONASS卫星系统的
             * @author      pengshupan@sixents.com
             * @param[in]   sec         接收机获取星历文件的时间(s)
             * @param[in]   ephObj      jGPS,GALILEO,BDS星历文件
             * @param[out]  x           GLONASS卫星系统位置x
             * @param[out]  y           GLONASS卫星系统位置y
             * @param[out]  z           GLONASS卫星系统位置z
             * @exception   N/A
             * @return      函数的执行结果
             * @note        N/A
             */
            INT32 CalcGloEphSatPos(const DOUBLE& sec, const SGlonassEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z);

        private:
            
            DOUBLE VectorDot(const DOUBLE* a, const DOUBLE* b, INT32 n);
            void OrbitDifferentialEquations(const DOUBLE* x, DOUBLE* xdot, const DOUBLE* acc);
            void Glorbit(DOUBLE t, DOUBLE* x, const DOUBLE* acc);
        };
    } // end namespace Math
} // end namespace sixents
#endif