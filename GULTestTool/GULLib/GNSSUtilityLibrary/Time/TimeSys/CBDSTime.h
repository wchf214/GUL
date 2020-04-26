/** @file          CBDSTime.h
 *  @brief         北斗时间类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _CBDS_TIME_H
#define _CBDS_TIME_H

#include "IGNSSTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        /**
         *  @class       CBDSTime
         *  @brief       北斗时间类
         *  @author      wuchuanfei@sixents.com
         *  @note
         */
        class CBDSTime : public IGNSSTime
        {
        public:
            explicit CBDSTime(const TIME_TYPE timeType = BDS);
            virtual ~CBDSTime() override;

            virtual INT32 Format(std::string& formatString) override;

            virtual void ToSec() override;
            virtual void ToSec(DOUBLE& time) override;
            virtual void ToStandTime(SStandardTime& time) override;
            virtual void ToStandTime() override;
            virtual void ToWeekSec(SGNSSTime& time) override;

            virtual void SetTime(const DOUBLE& time) override;
            virtual void GetTime(DOUBLE& time) override;
            virtual void SetTime(const SGNSSTime& time) override;
            virtual void GetTime(SGNSSTime& time) override;

        private:
            SGNSSTime m_time;
            DOUBLE m_sec; /* 以秒格式表示的时间 */
        };                // end class CBDSTime
    }                     // end namespace GNSSUtilityLib
} // end namespace sixents

#endif
