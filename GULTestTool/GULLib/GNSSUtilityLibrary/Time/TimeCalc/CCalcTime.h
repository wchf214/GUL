/** @file          CCalcTime.h
 *  @brief         时间处理类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef CCALC_TIME_H
#define CCALC_TIME_H

#include "../../DllMain/GNSSCommonDef.h"

namespace sixents
{
    namespace Math
    {
        /**
         *  @class       CCalcTime
         *  @brief       时间处理类
         *  @author      wuchuanfei@sixents.com
         *  @note
         */
        class CCalcTime
        {
        public:
            /**
             * @brief          两个时间系统之间的时间数据互转
             * @author         wuchuanfei@sixents.com
             * @param[in]      srcSec           源时间数据
             * @param[in]      srcTimeType      源时间类型
             * @param[in]      destTimeType     目标时间类型
             * @param[out]     N/A
             * @exception      N/A
             * @return         目标时间数据
             * @note           N/A
             */
            static DOUBLE TimeConvert(const DOUBLE srcSec, const TIME_TYPE srcTimeType, const TIME_TYPE destTimeType);

        private:
            /**
             * @brief          GPS与UTC的互转
             * @author         wuchuanfei@sixents.com
             * @param[in]      srcTime      源时间数据
             * @param[in]      isUtc        是否转UTC。true:GPS转UTC，false:UTC转GPS
             * @param[out]     N/A
             * @exception      N/A
             * @return         目标时间数据
             * @note           N/A
             */
            static DOUBLE GPSTUTCConvert(const DOUBLE srcTime, const BOOL_T isUtc);

            /**
             * @brief          Glonass与UTC的互转
             * @author         wuchuanfei@sixents.com
             * @param[in]      srcTime      源时间数据
             * @param[in]      isUtc        是否转UTC。true:Glonass转UTC，false:UTC转Glonass
             * @param[out]     N/A
             * @exception      N/A
             * @return         目标时间数据
             * @note           N/A
             */
            static DOUBLE GLOTUTCConvert(const DOUBLE srcTime, const BOOL_T isUtc);

            /**
             * @brief          Galileo与UTC的互转
             * @author         wuchuanfei@sixents.com
             * @param[in]      srcTime      源时间数据
             * @param[in]      isUtc        是否转UTC。true:Galileo转UTC，false:UTC转Galileo
             * @param[out]     N/A
             * @exception      N/A
             * @return         目标时间数据
             * @note           N/A
             */
            static DOUBLE GSTUTCConvert(const DOUBLE srcTime, const BOOL_T isUtc);

            /**
             * @brief          BDS与UTC的互转
             * @author         wuchuanfei@sixents.com
             * @param[in]      srcTime      源时间数据
             * @param[in]      isUtc        是否转UTC。true:BDS转UTC，false:UTC转BDS
             * @param[out]     N/A
             * @exception      N/A
             * @return         目标时间数据
             * @note           N/A
             */
            static DOUBLE BDTUTCConvert(const DOUBLE srcTime, const BOOL_T isUtc);

            /**
             * @brief          BDS与GPS的互转
             * @author         wuchuanfei@sixents.com
             * @param[in]      srcTime          源时间数据
             * @param[in]      isGps            是否转GPS。true:BDS转GPS，false:GPS转BDS
             * @param[out]     N/A
             * @exception      N/A
             * @return         目标时间数据
             * @note           N/A
             */
            static DOUBLE BDTGPSTConvert(const DOUBLE srcTime, const BOOL_T isGps);

            /**
             * @brief          Glonass与GPS的互转
             * @author         wuchuanfei@sixents.com
             * @param[in]      srcTime          源时间数据
             * @param[in]      isGps            是否转GPS。true:Glonass转GPS，false:GPS转Glonass
             * @param[out]     N/A
             * @exception      N/A
             * @return         目标时间数据
             * @note           N/A
             */
            static DOUBLE GLOTGPSTConvert(const DOUBLE srcTime, const BOOL_T isGps);

            /**
             * @brief          Galileo与GPS的互转
             * @author         wuchuanfei@sixents.com
             * @param[in]      srcTime          源时间数据
             * @param[in]      isGps            是否转GPS。true:Galileo转GPS，false:GPS转Galileo
             * @param[out]     N/A
             * @exception      N/A
             * @return         目标时间数据
             * @note           N/A
             */
            static DOUBLE GSTGPSTConvert(const DOUBLE srcTime, const BOOL_T isGps);
        };
    } // end namespace Math
} // end namespace sixents
#endif // CCALCTIME_H
