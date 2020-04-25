/** @file          CGPSTime.h
 *  @brief         GPS时间类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#include "CGPSTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        CGPSTime::CGPSTime()
        {}
        CGPSTime::~CGPSTime()
        {}
        INT32 CGPSTime::Format(std::string& formatString)
        {
            return INT32();
        }
        DOUBLE CGPSTime::ToSec() const
        {
            return DOUBLE();
        }
        void CGPSTime::ToStandTime(SStandardTime& time) const
        {}

        void CGPSTime::ToWeekSec(SGNSSTime& time) const
        {}
        void CGPSTime::SetTime(const DOUBLE& time)
        {}
        void CGPSTime::GetTime(DOUBLE& time) const
        {}
        void CGPSTime::SetTime(const SGNSSTime& time)
        {}
        void CGPSTime::GetTime(SGNSSTime& time) const
        {}
    } // end namespace GNSSUtilityLib
} // end namespace sixents
