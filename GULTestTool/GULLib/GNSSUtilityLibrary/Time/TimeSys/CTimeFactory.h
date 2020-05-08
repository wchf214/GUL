/** @file          CTimeFactory.h
 *  @brief         时间对象工厂类
 *  @details       创建时间对象
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef CTIME_FACTORY_H
#define CTIME_FACTORY_H

#include "IGNSSTime.h"

namespace sixents
{
    namespace Math
    {
        /**
         *  @class       CTimeFactory
         *  @brief       时间对象工厂类
         *  @author      wuchuanfei@sixents.com
         *  @note        创建时间对象
         */
        class CTimeFactory
        {
        public:
            /**
             * @brief          创建时间对象函数
             * @author         wuchuanfei@sixents.com
             * @param[in]      timeType             时间类型
             * @param[out]     N/A
             * @exception      N/A
             * @return         创建成功的时间对象指针
             * @note           N/A
             */
            static IGNSSTime* CreateTimeObj(const TIME_TYPE timeType);
        };
    } // end namespace Math
} // end namespace sixents

#endif
