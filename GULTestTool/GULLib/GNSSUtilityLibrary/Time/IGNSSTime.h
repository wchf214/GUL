/** @file          IGNSSTime.h
 *  @brief         时间父类
 *  @details       时间对象的基类
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _IGNSS_TIME_H
#define _IGNSS_TIME_H

#include <string>

#include "../DllMain/GNSSCommonDef.h"
#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        /**
         *  @class       IGNSSTime
         *  @brief       时间父类
         *  @author      wuchuanfei@sixents.com
         *  @note        时间对象的基类
         */
        class IGNSSTime
        {
        public:
            /**
             * @brief          构造函数
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            IGNSSTime();

            /**
             * @brief          析构函数
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual ~IGNSSTime();

            /**
             * @brief          设置小数形式的时间到对象的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      time: 时间数据
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void SetTime(const DOUBLE& time);

            /**
             * @brief          从对象中获取小数形式的时间的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     N/A
             * @exception      N/A
             * @return         返回小数形式的时间数据
             * @note           N/A
             */
            virtual void GetTime(DOUBLE& time) const;

            virtual void SetTime(const SStandardTime& time);
            virtual void GetTime(SStandardTime& time) const;
            virtual void SetTime(const SGNSSTime& time);
            virtual void GetTime(SGNSSTime& time) const;

            /**
             * @brief          以年月日时分秒格式对时间进行格式化的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     formatString: 格式化后的字符串
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual INT32 Format(std::string& formatString) = 0;

            /**
             * @brief          时间转为小数形式的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     N/A
             * @exception      N/A
             * @return         转换后的时间
             * @note           N/A
             */
            virtual DOUBLE ToSec() const = 0;

            /**
             * @brief          把时间转为标准时间结构的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     time: 转换后的时间
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void ToStandTime(SStandardTime& time) const = 0;

            /**
             * @brief          把时间转为周内秒结构的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     time: 转换后的时间
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void ToWeekSec(SGNSSTime& time) const;

            /**
             * @brief          获取当前时间的时间类型
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            INT32 GetTimeType();

        private:
            INT32 m_timeType;
        }; // end class IGNSSTime
    }      // end namespace GNSSUtilityLib
} // end namespace sixents

#endif