/** @file          CGPSTime.h
 *  @brief         GPS时间类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _CGPS_TIME_H
#define _CGPS_TIME_H

#include "IGNSSTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        /**
         *  @class       CGPSTime
         *  @brief       GPS时间类
         *  @author      wuchuanfei@sixents.com
         *  @note
         */
        class CGPSTime : public IGNSSTime
        {
        public:
            CGPSTime();
            virtual ~CGPSTime();

            virtual INT32 Format(std::string& formatString);

            virtual DOUBLE ToSec() const;
            virtual void ToStandTime(SStandardTime& time) const;
            virtual void ToWeekSec(SGNSSTime& time) const;

            virtual void SetTime(const DOUBLE& time);
            virtual void GetTime(DOUBLE& time) const;
            virtual void SetTime(const SGNSSTime& time);
            virtual void GetTime(SGNSSTime& time) const;

        private:
            SGNSSTime m_time;
            DOUBLE m_sec; /* 以秒格式表示的时间 */
        };                // end class CGPSTime
    }                     // end namespace GNSSUtilityLib
} // end namespace sixents

#endif