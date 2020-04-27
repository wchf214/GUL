/** @file          ITimeLeap.h
 *  @brief         跳秒信息父类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef ITIME_LEAP_H
#define ITIME_LEAP_H

#include "../../DllMain/GNSSCommonDef.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        /**
         *  @class       ITimeLeap
         *  @brief       跳秒信息父类
         *  @author      wuchuanfei@sixents.com
         *  @note
         */
        class ITimeLeap
        {
        public:
            explicit ITimeLeap(const TIME_TYPE timeType);
            virtual ~ITimeLeap();

            virtual DOUBLE GetLeapTime(const DOUBLE timeSec, const TIME_TYPE timeType) = 0;

            TIME_TYPE GetTimeType() const;
        private:
            TIME_TYPE m_timeType;
        };
    }      // end namespace GNSSUtilityLib
} // end namespace sixents
#endif // ITIMELEAP_H
