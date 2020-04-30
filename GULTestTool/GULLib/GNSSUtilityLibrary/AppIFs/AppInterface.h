/** @file          AppInterface.h
 *  @brief         接口实现类
 *  @details       GNSS Utility所有对外接口的实现
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */
#ifndef _APP_INTERFACE_H_
#define _APP_INTERFACE_H_

#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        /**
         *  @class       CAppInterface
         *  @brief       GNSS Utility Library接口实现类
         *  @author      wuchuanfei@sixents.com
         *  @note        用于接口算法实现
         */
        class CAppInterface
        {
        public:
            /**
             * @brief           格式化周内秒时间，以年月日时分秒格式输出
             * @author          wuchuanfei@sixents.com
             * @param[in]       week: 周
                                sec: 秒，精确到毫秒
                                timeType: 时间类型
             * @param[out]      formatString: 时间格式化后字符串
                                len: formatString的长度
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 FormatWeekSecTime(
                const UINT64 week, const DOUBLE sec, const UINT32 timeType, CHAR* formatString, UINT32& len);

            /**
             * @brief           格式化标准时间，以年月日时分秒格式输出
             * @author          wuchuanfei@sixents.com
             * @param[in]       year: 年
                                month: 月
                                day: 日
                                hour: 时
                                minute: 分
                                second: 秒，精确到毫秒
             * @param[out]      formatString: 时间格式化后字符串
                                len: formatString的长度
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 FormatStandardTime(const UINT32 year,
                                            const UINT32 month,
                                            const UINT32 day,
                                            const UINT32 hour,
                                            const UINT32 minute,
                                            const DOUBLE second,
                                            CHAR* formatString,
                                            UINT32& len);

            /**
             * @brief           UTC时间转Glonass时间
             * @author          wuchuanfei@sixents.com
             * @param[in]       utcYear: 年
                                utcMonth: 月
                                utcDay: 日
                                utcHour: 时
                                utcMinute: 分
                                utcSecond: 秒，精确到毫秒
             * @param[out]      gloYear: 年
                                gloMonth: 月
                                gloDay: 日
                                gloHour: 时
                                gloMinute: 分
                                gloSecond: 秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.20新增
             */
            static INT32 UTCTimeToGlonassTime(const UINT32 utcYear,
                                              const UINT32 utcMonth,
                                              const UINT32 utcDay,
                                              const UINT32 utcHour,
                                              const UINT32 utcMinute,
                                              const DOUBLE utcSecond,
                                              UINT32& gloYear,
                                              UINT32& gloMonth,
                                              UINT32& gloDay,
                                              UINT32& gloHour,
                                              UINT32& gloMinute,
                                              DOUBLE& gloSecond);

            /**
             * @brief           Glonass时间转UTC时间
             * @author          wuchuanfei@sixents.com
             * @param[in]       gloYear: 年
                                gloMonth: 月
                                gloDay: 日
                                gloHour: 时
                                gloMinute: 分
                                gloSecond: 秒，精确到毫秒
             * @param[out]      utcYear: 年
                                utcMonth: 月
                                utcDay: 日
                                utcHour: 时
                                utcMinute: 分
                                utcSecond: 秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.20新增
             */
            static INT32 GlonassTimeToUTCTime(const UINT32 gloYear,
                                              const UINT32 gloMonth,
                                              const UINT32 gloDay,
                                              const UINT32 gloHour,
                                              const UINT32 gloMinute,
                                              const DOUBLE gloSecond,
                                              UINT32& utcYear,
                                              UINT32& utcMonth,
                                              UINT32& utcDay,
                                              UINT32& utcHour,
                                              UINT32& utcMinute,
                                              DOUBLE& utcSecond);

            /**
             * @brief           GNSS时间转UTC时间
             * @author          wuchuanfei@sixents.com
             * @param[in]       week: 周
                                sec: 秒，精确到毫秒
                                timeType: 时间类型
             * @param[out]      year: 年
                                month: 月
                                day: 日
                                hour: 时
                                minute: 分
                                second: 秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 GNSSTimeToUTCTime(const UINT64 week,
                                           const DOUBLE sec,
                                           const UINT32 timeType,
                                           UINT32& year,
                                           UINT32& month,
                                           UINT32& day,
                                           UINT32& hour,
                                           UINT32& minute,
                                           DOUBLE& second);

            /**
             * @brief           GNSS时间转UTC时间，以小数秒表示转换后的UTC时间
             * @author          wuchuanfei@sixents.com
             * @param[in]       week: 周
                                sec: 秒，精确到毫秒
                                timeType: 时间类型
             * @param[out]      sec: 秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.17新增
             */
            static INT32
            GNSSTimeToUTCSecTime(const UINT64 week, const DOUBLE second, const UINT32 timeType, DOUBLE& sec);

            /**
             * @brief           UTC时间转GNSS时间
             * @author          wuchuanfei@sixents.com
             * @param[in]       year: 年
                                month: 月
                                day: 日
                                hour: 时
                                minute: 分
                                second: 秒，精确到毫秒
                                timeType: 时间类型
             * @param[out]      week: 周
                                sec: 秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 UTCTimeToGNSSTime(const UINT32 year,
                                           const UINT32 month,
                                           const UINT32 day,
                                           const UINT32 hour,
                                           const UINT32 minute,
                                           const DOUBLE second,
                                           const UINT32 timeType,
                                           UINT64& week,
                                           DOUBLE& sec);

            /**
             * @brief           UTC时间转GNSS时间，以小数秒表示转换后的GNSS时间
             * @author          wuchuanfei@sixents.com
             * @param[in]       year: 年
                                month: 月
                                day: 日
                                hour: 时
                                minute: 分
                                second: 秒，精确到毫秒
                                timeType: 时间类型
             * @param[out]      sec: 秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.17新增
             */
            static INT32 UTCTimeToGNSSSecTime(const UINT32 year,
                                              const UINT32 month,
                                              const UINT32 day,
                                              const UINT32 hour,
                                              const UINT32 minute,
                                              const DOUBLE second,
                                              const UINT32 timeType,
                                              DOUBLE& sec);

            /**
             * @brief           BD、Glonass、Galileo时间类型与GPS时间互转
             * @author          wuchuanfei@sixents.com
             * @param[in]       srcWeek: 源GNSS时间的周
                                srcSec: 源GNSS时间的秒，精确到毫秒
                                srcTimeType: 源GNSS时间的时间类型
                                destTimeType: 目标GNSS时间的时间类型
             * @param[out]      destWeek: 目标GNSS时间的周
                                destSec: 目标GNSS时间的秒，精确到毫秒
             * @exception       有不支持的类型，返回类型不支持错误码
             * @return          函数执行是否成功
             * @note            2020.04.17新增
             */
            static INT32 GNSSTimeConvert(const UINT64 srcWeek,
                                         const DOUBLE srcSec,
                                         const UINT32 srcTimeType,
                                         UINT64& destWeek,
                                         DOUBLE& destSec,
                                         const UINT32 destTimeType);

            /**
             * @brief           周内秒转秒
             * @author          wuchuanfei@sixents.com
             * @param[in]       week: 周
                                sec: 秒，精确到毫秒
                                timeType: 时间类型
             * @param[out]      sec: 秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.17新增
             */
            static INT32 WeekSecToSec(const UINT64 week, const DOUBLE second, const UINT32 timeType, DOUBLE& sec);

            /**
             * @brief           GPS时间转Glonass时间
             * @author          wuchuanfei@sixents.com
             * @param[in]       week: 周
                                second: 秒，精确到毫秒
             * @param[out]      year: 年
                                month: 月
                                day: 日
                                hour: 时
                                minute: 分
                                sec: 秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.20新增
             */
            static INT32 GPSTimeToGlonassTime(const UINT64 week,
                                              const DOUBLE second,
                                              UINT32& year,
                                              UINT32& month,
                                              UINT32& day,
                                              UINT32& hour,
                                              UINT32& minute,
                                              DOUBLE& sec);

            /**
             * @brief           Glonass时间转GPS时间
             * @author          wuchuanfei@sixents.com
             * @param[in]       year: 年
                                month: 月
                                day: 日
                                hour: 时
                                minute: 分
                                second: 秒，精确到毫秒
             * @param[out]      week: 周
                                second: 秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.20新增
             */
            static INT32 GlonassTimeToGPSTime(const UINT32 year,
                                              const UINT32 month,
                                              const UINT32 day,
                                              const UINT32 hour,
                                              const UINT32 minute,
                                              const DOUBLE second,
                                              UINT64& week,
                                              DOUBLE& sec);

            // 坐标相关接口
            // 坐标结构
            // 空间直角坐标格式为x,y,z
            // 站心坐标格式为east,north,up
            // 大地坐标格式为lat,lon,height

            /**
             * @brief           空间直角坐标转大地坐标
             * @author          wuchuanfei@sixents.com
             * @param[in]       x,y,z: 空间直角坐标，精确到小数点后9位
             * @param[out]      lon: 经度，以度为单位，精确到小数点后11位
                                lat: 纬度，以度为单位，精确到小数点后11位
                                height: 高程，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32
            XYZ2BLH(const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lon, DOUBLE& lat, DOUBLE& height);

            /**
             * @brief           大地坐标转空间直角坐标
             * @author          wuchuanfei@sixents.com
             * @param[in]       lon: 经度，以度为单位，精确到小数点后11位
                                lat: 纬度，以度为单位，精确到小数点后11位
                                height: 高程，精确到小数点后9位
             * @param[out]      x,y,z: 空间直角坐标，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32
            BLH2XYZ(const DOUBLE lon, const DOUBLE lat, const DOUBLE height, DOUBLE& x, DOUBLE& y, DOUBLE& z);

            /**
             * @brief           空间直角坐标转站心坐标
             * @author          wuchuanfei@sixents.com
             * @param[in]       curX,curY,curZ: 当前站的空间直角坐标，精确到小数点后9位
                                refX,refY,refZ: 参考站空间直角坐标，精确到小数点后9位
             * @param[out]      east,north,up: 当前站的站心坐标，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 XYZ2ENU(const DOUBLE curX,
                                 const DOUBLE curY,
                                 const DOUBLE curZ,
                                 const DOUBLE refX,
                                 const DOUBLE refY,
                                 const DOUBLE refZ,
                                 DOUBLE& east,
                                 DOUBLE& north,
                                 DOUBLE& up);

            /**
             * @brief           站心坐标转空间直角坐标
             * @author          wuchuanfei@sixents.com
             * @param[in]       east,north,up: 当前站的站心坐标，精确到小数点后9位
                                refX,refY,refZ: 参考站空间直角坐标，精确到小数点后9位
             * @param[out]      curX,curY,curZ: 当前站的空间直角坐标，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 ENU2XYZ(const DOUBLE east,
                                 const DOUBLE north,
                                 const DOUBLE up,
                                 const DOUBLE refX,
                                 const DOUBLE refY,
                                 const DOUBLE refZ,
                                 DOUBLE& curX,
                                 DOUBLE& curY,
                                 DOUBLE& curZ);

            // 星历相关接口 2020.04.17修改

            /**
             * @brief           计算Glonass钟差
             * @author          wuchuanfei@sixents.com
             * @param[in]       sec: 指定时间，秒，精确到毫秒
                                ephObj: Glonass星历数据
             * @param[out]      clockVal: 计算出来的钟差值，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 CalcGlonassEphSatClock(const DOUBLE& sec, const SGlonassEphemeris& ephObj, DOUBLE& clockVal);

            /**
             * @brief           计算钟差
             * @author          wuchuanfei@sixents.com
             * @param[in]       sec: 指定时间，秒，精确到毫秒
                                ephObj: 星历数据
             * @param[out]      clockVal: 计算出来的钟差值，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 CalcEphSatClock(const DOUBLE& sec, const SEphemeris& ephObj, DOUBLE& clockVal);

            /**
             * @brief           计算Glonass位置
             * @author          wuchuanfei@sixents.com
             * @param[in]       sec: 指定时间，秒，精确到毫秒
                                ephObj: Glonass星历数据
             * @param[out]      x,y,z: 计算出来的空间位置值，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32
            CalcGlonassEphSatPos(const DOUBLE sec, const SGlonassEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z);

            /**
             * @brief           计算位置
             * @author          wuchuanfei@sixents.com
             * @param[in]       sec: 指定时间，秒，精确到毫秒
                                ephObj: 星历数据
             * @param[out]      x,y,z: 计算出来的空间位置值，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 CalcEphSatPos(const DOUBLE sec, const SEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z);

            // 角度相关接口
            /**
             * @brief           将小数形式的角度进行格式化
             * @author          wuchuanfei@sixents.com
             * @param[in]       degree: 小数形式的度，精确到小数点后9位
                                formatType: 格式化类型；true时，格式化为度，false时格式化为度分秒;默认为true
             * @param[out]      formatString: 格式化后的字符串
                                len: formatString的长度
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32
            FormatAngleByDegree(const DOUBLE degree, char* formatString, UINT32& len, const BOOL_T formatType = true);

            /**
             * @brief           将度分秒形式的角度格式化
             * @author          wuchuanfei@sixents.com
             * @param[in]       degree: 度
                                minute: 分
                                sec: 秒，精确到毫秒
                                formatType: 格式化类型；true时，格式化为度，false时格式化为度分秒;默认为true
             * @param[out]      formatString: 输出参数，格式化后的字符串
                                len: formatString的长度
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 FormatAngleByDMS(const INT32 degree,
                                          const INT32 minute,
                                          const DOUBLE sec,
                                          CHAR* formatString,
                                          UINT32& len,
                                          const BOOL_T formatType = true);

            /**
             * @brief           度转弧度
             * @author          wuchuanfei@sixents.com
             * @param[in]       degree: 小数形式的度，精确到小数点后9位
             * @param[out]      radian: 弧度，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 Deg2Rad(const DOUBLE degree, DOUBLE& radian);

            /**
             * @brief           度分秒转弧度
             * @author          wuchuanfei@sixents.com
             * @param[in]       degree: 度
                                minute: 分
                                sec: 秒，精确到毫秒
             * @param[out]      radian: 弧度，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 DMS2Rad(const INT32 degree, const INT32 minute, const DOUBLE sec, DOUBLE& radian);

            /**
             * @brief           弧度转度
             * @author          wuchuanfei@sixents.com
             * @param[in]       radian: 弧度，精确到小数点后9位
             * @param[out]      degree: 小数形式的度，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 Rad2Deg(const DOUBLE radian, DOUBLE& degree);

            /**
             * @brief           弧度转度分秒
             * @author          wuchuanfei@sixents.com
             * @param[in]       radian: 弧度，精确到小数点后9位
             * @param[out]      degree: 度
                                minute: 分
                                sec: 秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 Rad2DMS(const DOUBLE radian, INT32& degree, INT32& minute, DOUBLE& sec);
        }; // end class CAppInterface
    }      // end namespace GNSSUtilityLib
} // end namespace sixents

#endif