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
//class ITimeLeap;

namespace sixents
{
    namespace GNSSUtilityLib
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
             * @param[in]      srcSec: 源时间数据
             *                 srctimeType: 源时间类型
             *                 destTimeType: 目标时间类型
             * @param[out]     N/A
             * @exception      N/A
             * @return         目标时间数据
             * @note           N/A
             */
            static DOUBLE TimeConvert(const DOUBLE srcSec, const TIME_TYPE srctimeType, const TIME_TYPE destTimeType);
        private:
            static DOUBLE GPST2UTC(const DOUBLE srcTime, const BOOL_T isUtc);
            static DOUBLE GLOT2UTC(const DOUBLE srcTime, const BOOL_T isUtc);
            static DOUBLE GST2UTC(const DOUBLE srcTime, const BOOL_T isUtc);
            static DOUBLE BDT2UTC(const DOUBLE srcTime, const BOOL_T isUtc);

            static DOUBLE BDT2GPST(const DOUBLE srcTime, const BOOL_T isGps);
            static DOUBLE GLOT2GPST(const DOUBLE srcTime, const BOOL_T isGps);
            static DOUBLE GST2GPST(const DOUBLE srcTime, const BOOL_T isGps);
//        private:
//            ITimeLeap* m_leap;
        };
    }      // end namespace GNSSUtilityLib
} // end namespace sixents
#endif // CCALCTIME_H
