/** @file          AppInterface.h
 *  @brief         接口实现类
 *  @details       GNSS Utility所有对外接口的实现
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */
#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace Math
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
             * @param[in]       week                周
             * @param[in]       sec                 秒，精确到毫秒
             * @param[in]       timeType            时间类型
             * @param[out]      formatString        时间格式化后字符串
             * @param[out]      len                 formatString的长度
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 FormatWeekSecTime(
                const UINT64 week, const DOUBLE sec, const UINT32 timeType, CHAR* formatString, UINT32& len);

            /**
             * @brief           格式化标准时间，以年月日时分秒格式输出
             * @author          wuchuanfei@sixents.com
             * @param[in]       year                年
             * @param[in]       month               月
             * @param[in]       day                 日
             * @param[in]       hour                时
             * @param[in]       minute              分
             * @param[in]       second              秒，精确到毫秒
             * @param[out]      formatString        时间格式化后字符串
             * @param[out]      len                 formatString的长度
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
             * @brief           标准时间互相转换
             * @author          wuchuanfei@sixents.com
             * @param[in]       srcYear         年
             * @param[in]       srcMonth        月
             * @param[in]       srcDay          日
             * @param[in]       srcHour         时
             * @param[in]       srcMinute       分
             * @param[in]       srcSecond       秒，精确到毫秒
             * @param[in]       srcTimeType     原始时间类型
             * @param[in]       destTimeType    目标时间类型
             * @param[out]      destYear        年
             * @param[out]      destMonth       月
             * @param[out]      destDay         日
             * @param[out]      destHour        时
             * @param[out]      destMinute      分
             * @param[out]      destSecond      秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.20新增
             */
            static INT32 StandardTimeConvert(const UINT32 srcYear,
                                             const UINT32 srcMonth,
                                             const UINT32 srcDay,
                                             const UINT32 srcHour,
                                             const UINT32 srcMinute,
                                             const DOUBLE srcSecond,
                                             const UINT32 srcTimeType,
                                             const UINT32 destTimeType,
                                             UINT32& destYear,
                                             UINT32& destMonth,
                                             UINT32& destDay,
                                             UINT32& destHour,
                                             UINT32& destMinute,
                                             DOUBLE& destSecond);

            /**
             * @brief           GNSS时间转标准时间
             * @author          wuchuanfei@sixents.com
             * @param[in]       week                    周
             * @param[in]       second                  秒，精确到毫秒
             * @param[in]       gnssTimeType            GNSS卫星系统类型
             * @param[in]       standardTimeType        标准时间类型
             * @param[out]      year                    年
             * @param[out]      month                   月
             * @param[out]      day                     日
             * @param[out]      hour                    时
             * @param[out]      minute                  分
             * @param[out]      sec                     秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.20新增
             */
            static INT32 GNSSTimeToStandardTime(const UINT64 week,
                                                const DOUBLE second,
                                                const UINT32 gnssTimeType,
                                                const UINT32 standardTimeType,
                                                UINT32& year,
                                                UINT32& month,
                                                UINT32& day,
                                                UINT32& hour,
                                                UINT32& minute,
                                                DOUBLE& sec);

            /**
             * @brief           标准时间转GNSS时间
             * @author          wuchuanfei@sixents.com
             * @param[in]       year                年
             * @param[in]       month               月
             * @param[in]       day                 日
             * @param[in]       hour                时
             * @param[in]       minute              分
             * @param[in]       second              秒，精确到毫秒
             * @param[in]       gnssTimeType        GNSS卫星系统类型
             * @param[in]       standardTimeType    标准时间类型
             * @param[out]      week                周
             * @param[out]      sec                 秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.20新增
             */
            static INT32 StandardTimeToGNSSTime(const UINT32 year,
                                                const UINT32 month,
                                                const UINT32 day,
                                                const UINT32 hour,
                                                const UINT32 minute,
                                                const DOUBLE second,
                                                const UINT32 standardTimeType,
                                                const UINT32 gnssTimeType,
                                                UINT64& week,
                                                DOUBLE& sec);

            /**
             * @brief           BD、Glonass、Galileo时间类型与GPS时间互转
             * @author          wuchuanfei@sixents.com
             * @param[in]       srcWeek             源GNSS时间的周
             * @param[in]       srcSec              源GNSS时间的秒，精确到毫秒
             * @param[in]       srcTimeType         源GNSS时间的时间类型
             * @param[in]       destTimeType        目标GNSS时间的时间类型
             * @param[out]      destWeek            目标GNSS时间的周
             * @param[out]      destSec             目标GNSS时间的秒，精确到毫秒
             * @exception       有不支持的类型，返回类型不支持错误码
             * @return          函数执行是否成功
             * @note            2020.04.17新增
             */
            static INT32 GNSSTimeConvert(const UINT64 srcWeek,
                                         const DOUBLE srcSec,
                                         const UINT32 srcTimeType,
                                         const UINT32 destTimeType,
                                         UINT64& destWeek,
                                         DOUBLE& destSec);

            /**
             * @brief           周内秒转秒
             * @author          wuchuanfei@sixents.com
             * @param[in]       week            周
             * @param[in]       second          秒，精确到毫秒
             * @param[in]       timeType        时间类型
             * @param[out]      sec             秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.17新增
             */
            static INT32 WeekSecToSec(const UINT64 week, const DOUBLE second, const UINT32 timeType, DOUBLE& sec);

            /**
             * @brief           标准时间转秒
             * @author          wuchuanfei@sixents.com
             * @param[in]       year            年
             * @param[in]       month           月
             * @param[in]       day             日
             * @param[in]       hour            时
             * @param[in]       minute          分
             * @param[in]       second          秒，精确到毫秒
             * @param[in]       timeType        时间类型
             * @param[out]      sec             秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            2020.04.17新增
             */
            static INT32 StandardTimeToSec(const UINT32 year,
                                           const UINT32 month,
                                           const UINT32 day,
                                           const UINT32 hour,
                                           const UINT32 minute,
                                           const DOUBLE second,
                                           const UINT32 timeType,
                                           DOUBLE& sec);

            // 坐标相关接口
            // 坐标结构
            // 空间直角坐标格式为x,y,z
            // 站心坐标格式为east,north,up
            // 大地坐标格式为lat,lon,height

            /**
             * @brief           空间直角坐标转大地坐标
             * @author          wuchuanfei@sixents.com
             * @param[in]       x,y,z       空间直角坐标，精确到小数点后9位
             * @param[out]      lat         纬度，以度为单位，精确到小数点后11位
             * @param[out]      lon         经度，以度为单位，精确到小数点后11位
             * @param[out]      height      高程，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32
            XYZ2BLH(const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lat, DOUBLE& lon, DOUBLE& height);

            /**
             * @brief           大地坐标转空间直角坐标
             * @author          wuchuanfei@sixents.com
             * @param[in]       lat         纬度，以度为单位，精确到小数点后11位
             * @param[in]       lon         经度，以度为单位，精确到小数点后11位
             * @param[in]       height      高程，精确到小数点后9位
             * @param[out]      x,y,z       空间直角坐标，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32
            BLH2XYZ(const DOUBLE lat, const DOUBLE lon, const DOUBLE height, DOUBLE& x, DOUBLE& y, DOUBLE& z);

            /**
             * @brief           空间直角坐标转站心坐标
             * @author          wuchuanfei@sixents.com
             * @param[in]       curX,curY,curZ      当前站的空间直角坐标，精确到小数点后9位
             * @param[in]       refX,refY,refZ      参考站空间直角坐标，精确到小数点后9位
             * @param[out]      east,north,up       当前站的站心坐标，精确到小数点后9位
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
             * @param[in]       east,north,up       当前站的站心坐标，精确到小数点后9位
             * @param[in]       refX,refY,refZ      参考站空间直角坐标，精确到小数点后9位
             * @param[out]      curX,curY,curZ      当前站的空间直角坐标，精确到小数点后9位
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
             * @param[in]       sec             指定时间，秒，精确到毫秒
             * @param[in]       ephObj          Glonass星历数据
             * @param[out]      clockVal        计算出来的钟差值，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 CalcGlonassEphSatClock(const DOUBLE& sec, const SGlonassEphemeris& ephObj, DOUBLE& clockVal);

            /**
             * @brief           计算钟差
             * @author          wuchuanfei@sixents.com
             * @param[in]       sec             指定时间，秒，精确到毫秒
             * @param[in]       ephObj          星历数据
             * @param[out]      clockVal        计算出来的钟差值，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 CalcEphSatClock(const DOUBLE& sec, const SEphemeris& ephObj, DOUBLE& clockVal);

            /**
             * @brief           计算Glonass位置
             * @author          wuchuanfei@sixents.com
             * @param[in]       sec             指定时间，秒，精确到毫秒
             * @param[in]       ephObj          Glonass星历数据
             * @param[out]      x,y,z           计算出来的空间位置值，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32
            CalcGlonassEphSatPos(const DOUBLE sec, const SGlonassEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z);

            /**
             * @brief           计算位置
             * @author          wuchuanfei@sixents.com
             * @param[in]       sec             指定时间，秒，精确到毫秒
             * @param[in]       ephObj          星历数据
             * @param[out]      x,y,z           计算出来的空间位置值，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 CalcEphSatPos(const DOUBLE sec, const SEphemeris& ephObj, DOUBLE& x, DOUBLE& y, DOUBLE& z);

            // 角度相关接口
            /**
             * @brief           将小数形式的角度进行格式化
             * @author          wuchuanfei@sixents.com
             * @param[in]       rad                 弧度，精确到小数点后9位
             * @param[in]       formatType          格式化类型；true时，格式化为度，false时格式化为度分秒;默认为true
             * @param[out]      formatString        格式化后的字符串
             * @param[out]      len                 formatString的长度
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32
            FormatAngleByDegree(const DOUBLE rad, char* formatString, UINT32& len, const BOOL_T formatType = true);

            /**
             * @brief           将度分秒形式的角度格式化
             * @author          wuchuanfei@sixents.com
             * @param[in]       degree              度
             * @param[in]       minute              分
             * @param[in]       sec                 秒，精确到毫秒
             * @param[in]       formatType          格式化类型；true时，格式化为度，false时格式化为度分秒;默认为true
             * @param[out]      formatString        输出参数，格式化后的字符串
             * @param[out]      len                 formatString的长度
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 FormatAngleByDMS(const INT32 degree,
                                          const UINT32 minute,
                                          const DOUBLE sec,
                                          CHAR* formatString,
                                          UINT32& len,
                                          const BOOL_T formatType = true);

            /**
             * @brief           度转弧度
             * @author          wuchuanfei@sixents.com
             * @param[in]       degree      小数形式的度，精确到小数点后9位
             * @param[out]      radian      弧度，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 Deg2Rad(const DOUBLE degree, DOUBLE& radian);

            /**
             * @brief           度分秒转弧度
             * @author          wuchuanfei@sixents.com
             * @param[in]       degree          度
             * @param[in]       minute          分
             * @param[in]       sec             秒，精确到毫秒
             * @param[out]      radian          弧度，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 DMS2Rad(const INT32 degree, const UINT32 minute, const DOUBLE sec, DOUBLE& radian);

            /**
             * @brief           弧度转度
             * @author          wuchuanfei@sixents.com
             * @param[in]       radian          弧度，精确到小数点后9位
             * @param[out]      degree          小数形式的度，精确到小数点后9位
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 Rad2Deg(const DOUBLE radian, DOUBLE& degree);

            /**
             * @brief           弧度转度分秒
             * @author          wuchuanfei@sixents.com
             * @param[in]       radian          弧度，精确到小数点后9位
             * @param[out]      degree          度
             * @param[out]      minute          分
             * @param[out]      sec             秒，精确到毫秒
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 Rad2DMS(const DOUBLE radian, INT32& degree, UINT32& minute, DOUBLE& sec);
        }; // end class CAppInterface
    }      // end namespace Math
} // end namespace sixents

#endif