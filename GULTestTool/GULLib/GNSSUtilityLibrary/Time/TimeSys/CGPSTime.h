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
            /**
             * @brief          构造函数
             * @author         wuchuanfei@sixents.com
             * @param[in]      timeType: 时间类型，目前仅支持TIME_TYPE中定义的几种时间类型
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            explicit CGPSTime(const TIME_TYPE timeType = GPS);

            /**
             * @brief          析构函数
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual ~CGPSTime() override;

            /**
             * @brief          以年月日时分秒格式对时间进行格式化的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     formatString: 格式化后的字符串
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual INT32 Format(std::string& formatString) override;

            /**
             * @brief          当前时间转为小数形式的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void ToSec() override;

            /**
             * @brief          当前时间转为小数形式的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     time: 转换后的时间
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void ToSec(DOUBLE& time) override;

            /**
             * @brief          把时间转为标准时间结构的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void ToStandTime() override;

            /**
             * @brief          把时间转为标准时间结构的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     time: 转换后的时间
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void ToStandTime(SStandardTime& time) override;

            /**
             * @brief          把时间转为周内秒结构的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     time: 转换后的时间
             * @exception      N/A
             * @return         N/A
             * @note           只有支持周内秒格式的时间才需要用到此函数
             */
            virtual void ToWeekSec(SGNSSTime& time) override;

            /**
             * @brief          设置小数形式的时间到对象的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      time: 时间数据
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void SetTime(const DOUBLE& time) override;

            /**
             * @brief          从对象中获取小数形式的时间的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     time: 小数形式的时间数据
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void GetTime(DOUBLE& time) override;

            /**
             * @brief          以周内秒时间格式设置时间的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      time: 周内秒格式的时间数据
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void SetTime(const SGNSSTime& time) override;

            /**
             * @brief          从对象中获取周内秒格式的时间的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     time: 周内秒格式的时间数据
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void GetTime(SGNSSTime& time) override;

        private:
            SGNSSTime m_time; /*以周内秒格式表示的时间，与m_sec之间可互转*/
            DOUBLE m_sec;     /* 以秒格式表示的时间 */
        };                    // end class CGPSTime
    }                         // end namespace GNSSUtilityLib
} // end namespace sixents

#endif
