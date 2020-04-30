/** @file          GNSSUtilityInterface.h
 *  @brief         对外接口
 *  @details       GNSS Utility 对外接口，包含星历的钟差和位置计算、导航时间转换和格式化、坐标转换、角度转换和格式化
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */
#ifndef GNSS_UTILITY_INTERFACE_H
#define GNSS_UTILITY_INTERFACE_H

#include "GNSSDataStruct.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
#ifdef _WIN32
#define STD_CALL _stdcall

#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#else
#define DLL_API __attribute__((visibility("default")))
#define STD_CALL
#endif

#ifdef __cplusplus
        extern "C" {
#endif
        // 对外接口声明
        // 时间相关接口
        // 时间结构
        // 标准格式：年-月-日 时：分：秒.毫秒
        // 示例：1111-11-11 11:11:11.111

        /**
         * @brief           格式化周内秒时间 以年月日时分秒格式输出
         * @author          wuchuanfei@sixents.com
         * @param[in]       week            周
         * @param[in]       sec             秒，精确到毫秒
         * @param[in]       timeType        时间类型
         * @param[out]      formatString    时间格式化后字符串
         * @param[out]      len             formatString的长度
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL FormatWeekSecTime(const unsigned int week,
                                               const double sec,
                                               const unsigned int timeType,
                                               char* formatString,
                                               unsigned int& len);

        /**
         * @brief           格式化标准时间 以年月日时分秒格式输出
         * @author          wuchuanfei@sixents.com
         * @param[in]       year            年
         * @param[in]       month           月
         * @param[in]       day             日
         * @param[in]       hour            时
         * @param[in]       minute          分
         * @param[in]       second          秒，精确到毫秒
         * @param[out]      formatString    时间格式化后字符串
         * @param[out]      len             formatString的长度
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL FormatStandardTime(const unsigned int year,
                                                const unsigned int month,
                                                const unsigned int day,
                                                const unsigned int hour,
                                                const unsigned int minute,
                                                const double second,
                                                char* formatString,
                                                unsigned int& len);

        /**
         * @brief           UTC时间转Glonass时间
         * @author          wuchuanfei@sixents.com
         * @param[in]       utcYear     年
         * @param[in]       utcMonth    月
         * @param[in]       utcDay      日
         * @param[in]       utcHour     时
         * @param[in]       utcMinute   分
         * @param[in]       utcSecond   秒，精确到毫秒
         * @param[out]      gloYear     年
         * @param[out]      gloMonth    月
         * @param[out]      gloDay      日
         * @param[out]      gloHour     时
         * @param[out]      gloMinute   分
         * @param[out]      gloSecond   秒，精确到毫秒
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            2020.04.20新增
         */
        DLL_API int STD_CALL UTCTimeToGlonassTime(const unsigned int utcYear,
                                                  const unsigned int utcMonth,
                                                  const unsigned int utcDay,
                                                  const unsigned int utcHour,
                                                  const unsigned int utcMinute,
                                                  const double utcSecond,
                                                  unsigned int& gloYear,
                                                  unsigned int& gloMonth,
                                                  unsigned int& gloDay,
                                                  unsigned int& gloHour,
                                                  unsigned int& gloMinute,
                                                  double& gloSecond);

        /**
         * @brief           Glonass时间转UTC时间
         * @author          wuchuanfei@sixents.com
         * @param[in]       gloYear     年
         * @param[in]       gloMonth    月
         * @param[in]       gloDay      日
         * @param[in]       gloHour     时
         * @param[in]       gloMinute   分
         * @param[in]       gloSecond   秒，精确到毫秒
         * @param[out]      utcYear     年
         * @param[out]      utcMonth    月
         * @param[out]      utcDay      日
         * @param[out]      utcHour     时
         * @param[out]      utcMinute   分
         * @param[out]      utcSecond   秒，精确到毫秒
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            2020.04.20新增
         */
        DLL_API int STD_CALL GlonassTimeToUTCTime(const unsigned int gloYear,
                                                  const unsigned int gloMonth,
                                                  const unsigned int gloDay,
                                                  const unsigned int gloHour,
                                                  const unsigned int gloMinute,
                                                  const double gloSecond,
                                                  unsigned int& utcYear,
                                                  unsigned int& utcMonth,
                                                  unsigned int& utcDay,
                                                  unsigned int& utcHour,
                                                  unsigned int& utcMinute,
                                                  double& utcSecond);

        /**
         * @brief           GNSS时间转UTC时间
         * @author          wuchuanfei@sixents.com
         * @param[in]       week         周
         * @param[in]       sec          秒，精确到毫秒
         * @param[in]       timeType     时间类型
         * @param[out]      year         年
         * @param[out]      month        月
         * @param[out]      day          日
         * @param[out]      hour         时
         * @param[out]      minute       分
         * @param[out]      second       秒，精确到毫秒
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL GNSSTimeToUTCTime(const unsigned int week,
                                               const double sec,
                                               const unsigned int timeType,
                                               unsigned int& year,
                                               unsigned int& month,
                                               unsigned int& day,
                                               unsigned int& hour,
                                               unsigned int& minute,
                                               double& second);

        /**
         * @brief           GNSS时间转UTC时间，以小数秒表示转换后的UTC时间
         * @author          wuchuanfei@sixents.com
         * @param[in]       week        周
         * @param[in]       sec         秒，精确到毫秒
         * @param[in]       timeType    时间类型
         * @param[out]      sec         秒，精确到毫秒
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            2020.04.17新增
         */
        DLL_API int STD_CALL GNSSTimeToUTCSecTime(const unsigned int week,
                                                  const double second,
                                                  const unsigned int timeType,
                                                  double& sec);

        /**
         * @brief           UTC时间转GNSS时间
         * @author          wuchuanfei@sixents.com
         * @param[in]       year        年
         * @param[in]       month       月
         * @param[in]       day         日
         * @param[in]       hour        时
         * @param[in]       minute      分
         * @param[in]       second      秒，精确到毫秒
         * @param[in]       timeType    时间类型
         * @param[out]      week        周
         * @param[out]      sec         秒
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL UTCTimeToGNSSTime(const unsigned int year,
                                               const unsigned int month,
                                               const unsigned int day,
                                               const unsigned int hour,
                                               const unsigned int minute,
                                               const double second,
                                               const unsigned int timeType,
                                               unsigned int& week,
                                               double& sec);

        /**
         * @brief           UTC时间转GNSS时间，以小数秒表示转换后的GNSS时间
         * @author          wuchuanfei@sixents.com
         * @param[in]       year        年
         * @param[in]       month       月
         * @param[in]       day         日
         * @param[in]       hour        时
         * @param[in]       minute      分
         * @param[in]       second      秒，精确到毫秒
         * @param[in]       timeType    时间类型
         * @param[out]      sec         秒，精确到毫秒
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            2020.04.17新增
         */
        DLL_API int STD_CALL UTCTimeToGNSSSecTime(const unsigned int year,
                                                  const unsigned int month,
                                                  const unsigned int day,
                                                  const unsigned int hour,
                                                  const unsigned int minute,
                                                  const double second,
                                                  const unsigned int timeType,
                                                  double& sec);

        /**
         * @brief           BD、Glonass、Galileo时间类型与GPS时间互转
         * @author          wuchuanfei@sixents.com
         * @param[in]       srcWeek         源GNSS时间的周
         * @param[in]       srcSec          源GNSS时间的秒，精确到毫秒
         * @param[in]       srcTimeType     源GNSS时间的时间类型
         * @param[in]       destTimeType    目标GNSS时间的时间类型
         * @param[out]      destWeek        目标GNSS时间的周
         * @param[out]      destSec         目标GNSS时间的秒，精确到毫秒
         * @exception       有不支持的类型，返回类型不支持错误码
         * @return          函数执行是否成功
         * @note            2020.04.17新增
         */
        DLL_API int STD_CALL GNSSTimeConvert(const unsigned int srcWeek,
                                             const double srcSec,
                                             const unsigned int srcTimeType,
                                             unsigned int& destWeek,
                                             double& destSec,
                                             const unsigned int destTimeType);

        /**
         * @brief           周内秒转秒
         * @author          wuchuanfei@sixents.com
         * @param[in]       week        周
         * @param[in]       sec         秒，精确到毫秒
         * @param[in]       timeType    时间类型
         * @param[out]      sec         秒，精确到毫秒
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            2020.04.17新增
         */
        DLL_API int STD_CALL WeekSecToSec(const unsigned int week,
                                          const double second,
                                          const unsigned int timeType,
                                          double& sec);

        /**
         * @brief           GPS时间转Glonass时间
         * @author          wuchuanfei@sixents.com
         * @param[in]       week        周
         * @param[in]       second      秒，精确到毫秒
         * @param[out]      year        年
         * @param[out]      month       月
         * @param[out]      day         日
         * @param[out]      hour        时
         * @param[out]      minute      分
         * @param[out]      second      秒，精确到毫秒
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            2020.04.20新增
         */
        DLL_API int STD_CALL GPSTimeToGlonassTime(const unsigned int week,
                                                  const double second,
                                                  unsigned int& year,
                                                  unsigned int& month,
                                                  unsigned int& day,
                                                  unsigned int& hour,
                                                  unsigned int& minute,
                                                  double& sec);

        /**
         * @brief           Glonass时间转GPS时间
         * @author          wuchuanfei@sixents.com
         * @param[in]       year        年
         * @param[in]       month       月
         * @param[in]       day         日
         * @param[in]       hour        时
         * @param[in]       minute      分
         * @param[in]       second      秒，精确到毫秒
         * @param[out]      week        周
         * @param[out]      second      秒，精确到毫秒
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            2020.04.20新增
         */
        DLL_API int STD_CALL GlonassTimeToGPSTime(const unsigned int year,
                                                  const unsigned int month,
                                                  const unsigned int day,
                                                  const unsigned int hour,
                                                  const unsigned int minute,
                                                  const double second,
                                                  unsigned int& week,
                                                  double& sec);

        // 坐标相关接口
        // 坐标结构
        // 空间直角坐标格式为x,y,z
        // 站心坐标格式为east,north,up
        // 大地坐标格式为lat,lon,height

        /**
         * @brief           空间直角坐标转大地坐标
         * @author          wuchuanfei@sixents.com
         * @param[in]       x,y,z: 空间直角坐标，精确到小数点后9位
         * @param[out]      lon: 经度，精确到小数点后11位
                            lat: 纬度，精确到小数点后11位
                            height: 高程，精确到小数点后9位
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL
        XYZ2BLH(const double x, const double y, const double z, double& lon, double& lat, double& height);

        /**
         * @brief           大地坐标转空间直角坐标
         * @author          wuchuanfei@sixents.com
         * @param[in]       lon: 经度，精确到小数点后11位
                            lat: 纬度，精确到小数点后11位
                            height: 高程，精确到小数点后9位
         * @param[out]      x,y,z: 空间直角坐标，精确到小数点后9位
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL
        BLH2XYZ(const double lon, const double lat, const double height, double& x, double& y, double& z);

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
        DLL_API int STD_CALL XYZ2ENU(const double curX,
                                     const double curY,
                                     const double curZ,
                                     const double refX,
                                     const double refY,
                                     const double refZ,
                                     double& east,
                                     double& north,
                                     double& up);

        // 站心坐标转空间直角坐标
        /**
         * @brief           空间直角坐标转站心坐标
         * @author          wuchuanfei@sixents.com
         * @param[in]       east,north,up: 当前站的站心坐标，精确到小数点后9位
                            refX,refY,refZ: 参考站空间直角坐标，精确到小数点后9位
         * @param[out]      curX,curY,curZ: 当前站的空间直角坐标，精确到小数点后9位
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL ENU2XYZ(const double east,
                                     const double north,
                                     const double up,
                                     const double refX,
                                     const double refY,
                                     const double refZ,
                                     double& curX,
                                     double& curY,
                                     double& curZ);

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
        DLL_API int STD_CALL CalcGlonassEphSatClock(const double& sec,
                                                    const SGlonassEphemeris& ephObj,
                                                    double& clockVal);

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
        DLL_API int STD_CALL CalcEphSatClock(const double& sec, const SEphemeris& ephObj, double& clockVal);

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
        DLL_API int STD_CALL
        CalcGlonassEphSatPos(const double sec, const SGlonassEphemeris& ephObj, double& x, double& y, double& z);

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
        DLL_API int STD_CALL CalcEphSatPos(const double sec, const SEphemeris& ephObj, double& x, double& y, double& z);

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
        DLL_API int STD_CALL FormatAngleByDegree(const double degree,
                                                 char* formatString,
                                                 unsigned int& len,
                                                 const bool formatType = true);

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
        DLL_API int STD_CALL FormatAngleByDMS(const int degree,
                                              const int minute,
                                              const double sec,
                                              char* formatString,
                                              unsigned int& len,
                                              const bool formatType = true);

        /**
         * @brief           度转弧度
         * @author          wuchuanfei@sixents.com
         * @param[in]       degree: 小数形式的度，精确到小数点后9位
         * @param[out]      radian: 弧度，精确到小数点后9位
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL Deg2Rad(const double degree, double& radian);

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
        DLL_API int STD_CALL DMS2Rad(const int degree, const int minute, const double sec, double& radian);

        /**
         * @brief           弧度转度
         * @author          wuchuanfei@sixents.com
         * @param[in]       radian: 弧度，精确到小数点后9位
         * @param[out]      degree: 小数形式的度，精确到小数点后9位
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL Rad2Deg(const double radian, double& degree);

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
        DLL_API int STD_CALL Rad2DMS(const double radian, int& degree, int& minute, double& sec);

#ifdef __cplusplus
        } // end extern "C"
#endif
    } // end namespace GNSSUtilityLib
} // end namespace sixents

#endif