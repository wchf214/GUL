/** @file          CGlonassTime.h
 *  @brief         Glonass时间类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _CGLONASS_TIME_H
#define _CGLONASS_TIME_H

#include "IGNSSTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        /**
         *  @class       CGlonassTime
         *  @brief       Glonass时间类
         *  @author      wuchuanfei@sixents.com
         *  @note
         */
        class CGlonassTime : public IGNSSTime
        {
        public:
            explicit CGlonassTime(const TIME_TYPE timeType = GLONASS);
            virtual ~CGlonassTime() override;

            virtual INT32 Format(std::string& formatString) override;

            virtual void ToSec() override;
            virtual void ToSec(DOUBLE& time) override;
            virtual void ToStandTime() override;
            virtual void ToStandTime(SStandardTime& time) override;

            virtual void SetTime(const DOUBLE& time) override;
            virtual void GetTime(DOUBLE& time) override;
            virtual void SetTime(const SStandardTime& time) override;
            virtual void GetTime(SStandardTime& time) override;

        private:
            SStandardTime m_time;
            DOUBLE m_sec; /* 以秒格式表示的时间 */
        };                // end class CGlonassTime
    }                     // end namespace GNSSUtilityLib
} // end namespace sixents

#endif
