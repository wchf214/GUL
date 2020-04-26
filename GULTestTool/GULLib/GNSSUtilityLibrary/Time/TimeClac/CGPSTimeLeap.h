/** @file          ITimeLeap.h
 *  @brief         跳秒信息父类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */
#ifndef CGPS_TIME_LEAP_H
#define CGPS_TIME_LEAP_H

#include "ITimeLeap.h"

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
        class CGPSTimeLeap : public ITimeLeap
        {
        public:
            explicit CGPSTimeLeap(const TIME_TYPE timeType);
            virtual ~CGPSTimeLeap();

            virtual DOUBLE GetLeapTime(const DOUBLE timeSec, const TIME_TYPE destTimeType);
        };
    }      // end namespace GNSSUtilityLib
} // end namespace sixents

#endif // CGPSTIMELEAP_H
