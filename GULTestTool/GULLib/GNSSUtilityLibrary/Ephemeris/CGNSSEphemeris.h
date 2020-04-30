/**@file           CGNSSEphemeris
 *  @brief         星历类
 *  @details       所有星历相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _GNSS_EPHEMERIS_H
#define _GNSS_EPHEMERIS_H

#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        class CGNSSEphemeris
        {
        public:
            /**
             * @brief       GPS,GALILEO,BDS卫星系统的构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   GPS,GALILEO,BDS卫星系统的星历结构体
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            explicit CGNSSEphemeris(const SEphemeris& ephObj);

            /**
             * @brief       GLONASS卫星系统的构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   GLONASS卫星系统的星历结构体
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            explicit CGNSSEphemeris(const SGlonassEphemeris& ephObj);

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
             * @brief       获取GPS,GALILEO,BDS卫星系统星历对象
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            SEphemeris GetEph();

            /**
             * @brief       获取GLONASS卫星系统星历对象
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            SGlonassEphemeris GetGloEph();

            /**
             * @brief       计算GPS,GALILEO,BDS卫星系统的钟差
             * @author      pengshupan@sixents.com
             * @param[in]   sec 接收机获取星历文件的时间(s)
             * @param[in]   ephObj GPS,GALILEO,BDS星历文件
             * @param[out]  clockVal GPS,GALILEO,BDS卫星系统的钟差
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            INT32 CalcEphSatClock(const double& sec, const SEphemeris& ephObj, double& clockVal);

            /**
             * @brief       计算GPS,GALILEO,BDS卫星系统的位置
             * @author      pengshupan@sixents.com
             * @param[in]   sec 接收机获取星历文件的时间(s)
             * @param[in]   ephObj jGPS,GALILEO,BDS星历文件
             * @param[out]  x GPS,GALILEO,BDS卫星系统位置x
             * @param[out]  y GPS,GALILEO,BDS卫星系统位置y
             * @param[out]  z GPS,GALILEO,BDS卫星系统位置z
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            INT32 CalcEphSatPos(const double& sec, const SEphemeris& ephObj, double& x, double& y, double& z);

            /**
             * @brief       计算GLONASS卫星系统的钟差
             * @author      pengshupan@sixents.com
             * @param[in]   sec 接收机获取星历文件的时间(s)
             * @param[in]   ephObj GLONASS星历文件
             * @param[out]  clockVal GLONASS卫星系统的钟差
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            INT32 CalcGloEphSatClock(const double& sec, const SGlonassEphemeris& ephObj, double& clockVal);

            /**
             * @brief       计算GLONASS卫星系统的
             * @author      pengshupan@sixents.com
             * @param[in]   sec 接收机获取星历文件的时间(s)
             * @param[in]   ephObj jGPS,GALILEO,BDS星历文件
             * @param[out]  x GLONASS卫星系统位置x
             * @param[out]  y GLONASS卫星系统位置y
             * @param[out]  z GLONASS卫星系统位置z
             * @exception   N/A
             * @return      函数的执行结果
             * @retval      N/A
             * @note        N/A
             */
            INT32 CalcGloEphSatPos(const double& sec, const SGlonassEphemeris& ephObj, double& x, double& y, double& z);

        private:
            SEphemeris m_ephObj;
            SGlonassEphemeris m_gloEphObj;
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents
#endif