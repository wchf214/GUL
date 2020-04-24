/** @file          CUTCTime.h
 *  @brief         UTC时间类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _CUTC_TIME_H
#define _CUTC_TIME_H

#include "IGNSSTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        /**
         *  @class       CUTCTime
         *  @brief       UTC时间类
         *  @author      wuchuanfei@sixents.com
         *  @note
         */
        class CUTCTime : public IGNSSTime
        {
        public:
            CUTCTime();
            virtual ~CUTCTime();

            virtual INT32 Format(std::string& formatString);

            virtual DOUBLE ToSec() const;
            virtual void ToStandTime(SStandardTime& time) const;

            virtual void SetTime(const DOUBLE& time);
            virtual void GetTime(DOUBLE& time) const;
            virtual void SetTime(const SStandardTime& time);
            virtual void GetTime(SStandardTime& time) const;

        private:
            SStandardTime m_time;
            DOUBLE m_sec; /* 以秒格式表示的时间 */
        };                // end class CUTCTime
    }                     // end namespace GNSSUtilityLib
} // end namespace sixents

#endif