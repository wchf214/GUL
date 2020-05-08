/** @file          CUTCTime.h
 *  @brief         UTC时间类
 *  @details       N/A
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef CUTC_TIME_H
#define CUTC_TIME_H

#include "IGNSSTime.h"

namespace sixents
{
    namespace Math
    {
        /**
         *  @class       CUTCTime
         *  @brief       UTC时间类，继承于IGNSSTime
         *  @author      wuchuanfei@sixents.com
         *  @note
         */
        class CUTCTime : public IGNSSTime
        {
        public:
            /**
             * @brief          构造函数
             * @author         wuchuanfei@sixents.com
             * @param[in]      timeType         时间类型,UTC
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            explicit CUTCTime(const TIME_TYPE timeType = UTC);

            /**
             * @brief          析构函数
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual ~CUTCTime() override;

            /**
             * @brief          以年月日时分秒格式对时间进行格式化的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     formatString         格式化后的字符串
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
             * @param[out]     time         转换后的时间
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void ToSec(DOUBLE& time) override;

            /**
             * @brief          把时间转为标准时间结构的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     time         转换后的时间
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void ToStandTime(SStandardTime& time) override;

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
             * @brief          设置小数形式的时间到对象的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      time         时间数据
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
             * @param[out]     time         小数形式的时间数据
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void GetTime(DOUBLE& time) override;

            /**
             * @brief          以标准时间格式设置时间的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      time         标准时间格式的时间数据
             * @param[out]     N/A
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void SetTime(const SStandardTime& time) override;

            /**
             * @brief          从对象中获取标准时间格式的时间的接口
             * @author         wuchuanfei@sixents.com
             * @param[in]      N/A
             * @param[out]     time         标准时间格式的时间数据
             * @exception      N/A
             * @return         N/A
             * @note           N/A
             */
            virtual void GetTime(SStandardTime& time) override;

        private:
            SStandardTime m_time; ///< 以年月日时分秒格式表示的时间，与m_sec的数值可互转
            DOUBLE m_sec;         ///< 以秒格式表示的时间
        };                        // end class CUTCTime
    }                             // end namespace Math
} // end namespace sixents

#endif
