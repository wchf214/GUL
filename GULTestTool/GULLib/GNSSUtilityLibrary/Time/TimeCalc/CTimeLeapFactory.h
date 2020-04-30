/** @file          ITimeLeap.h
 *  @brief         跳秒信息父类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef CTIME_LEAP_FACTORY_H
#define CTIME_LEAP_FACTORY_H
#include "ITimeLeap.h"
#include "CGPSTimeLeap.h"
#include "CUTCTimeLeap.h"
namespace sixents
{
    namespace GNSSUtilityLib
    {
        class CTimeLeapFactory
        {
            static ITimeLeap* CreateTimeLeapObj(const TIME_TYPE timeType);
        };
    }      // end namespace GNSSUtilityLib
} // end namespace sixents
#endif // CTIMELEAPFACTORY_H
