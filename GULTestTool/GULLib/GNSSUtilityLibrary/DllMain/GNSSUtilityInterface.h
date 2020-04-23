/**@file           CGNSSCoord
 *  @brief         坐标类
 *  @details       所有坐标相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */
#ifndef _GNSS_UTILITY_INTERFACE_H_
#define _GNSS_UTILITY_INTERFACE_H_

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
#define UNREFERENCED_PARAMETER(P) (P)

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
         * @param[in]       week: 周
                            sec: 秒，精确到毫秒
                            timeType: 时间类型
         * @param[out]      formatString: 时间格式化后字符串
                            len: formatString的长度
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL
        FormatWeekSecTime(const int week, const double sec, const int timeType, char* formatString, int& len);

        /**
         * @brief           格式化标准时间 以年月日时分秒格式输出
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
        DLL_API int STD_CALL FormatStandardTime(const int year,
                                                const int month,
                                                const int day,
                                                const int hour,
                                                const int minute,
                                                const double second,
                                                char* formatString,
                                                int& len);

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
        DLL_API int STD_CALL UTCTimeToGlonassTime(const int utcYear,
                                                  const int utcMonth,
                                                  const int utcDay,
                                                  const int utcHour,
                                                  const int utcMinute,
                                                  const double utcSecond,
                                                  int& gloYear,
                                                  int& gloMonth,
                                                  int& gloDay,
                                                  int& gloHour,
                                                  int& gloMinute,
                                                  double& gloSecond);

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
        DLL_API int STD_CALL GlonassTimeToUTCTime(const int gloYear,
                                                  const int gloMonth,
                                                  const int gloDay,
                                                  const int gloHour,
                                                  const int gloMinute,
                                                  const double gloSecond,
                                                  int& utcYear,
                                                  int& utcMonth,
                                                  int& utcDay,
                                                  int& utcHour,
                                                  int& utcMinute,
                                                  double& utcSecond);

        // GNSS时间类型与UTC时间互转
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
        DLL_API int STD_CALL GNSSTimeToUTCTime(const int week,
                                               const double sec,
                                               const int timeType,
                                               int& year,
                                               int& month,
                                               int& day,
                                               int& hour,
                                               int& minute,
                                               double& second);

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
        DLL_API int STD_CALL GNSSTimeToUTCSecTime(const int week, const double second, const int timeType, double& sec);

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
        DLL_API int STD_CALL UTCTimeToGNSSTime(const int year,
                                               const int month,
                                               const int day,
                                               const int hour,
                                               const int minute,
                                               const double second,
                                               const int timeType,
                                               int& week,
                                               double& sec);

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
        DLL_API int STD_CALL UTCTimeToGNSSSecTime(const int year,
                                                  const int month,
                                                  const int day,
                                                  const int hour,
                                                  const int minute,
                                                  const double second,
                                                  const int timeType,
                                                  double& sec);

        /**
         * @brief           BD、Glonass、Galileo时间类型与GPS时间互转
         * @author          wuchuanfei@sixents.com
         * @param[in]       srcWeek: 源GNSS时间的周
                            srcSec: 源GNSS时间的秒，精确到毫秒
                            srcTimeType: 源GNSS时间的时间类型
                            destTimeType: 目标GNSS时间的时间类型
         * @param[out]      destWeek: 目标GNSS时间的周
                            destSec: 目标GNSS时间的秒，精确到毫秒
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            2020.04.17新增
         */
        DLL_API int STD_CALL GNSSTimeConvert(const int srcWeek,
                                             const double srcSec,
                                             const int srcTimeType,
                                             int& destWeek,
                                             double& destSec,
                                             const int destTimeType);

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
        DLL_API int STD_CALL WeekSecToSec(const int week, const double second, const int timeType, double& sec);

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
        DLL_API int STD_CALL GPSTimeToGlonassTime(
            const int week, const double second, int& year, int& month, int& day, int& hour, int& minute, double& sec);

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
        DLL_API int STD_CALL GlonassTimeToGPSTime(const int year,
                                                  const int month,
                                                  const int day,
                                                  const int hour,
                                                  const int minute,
                                                  const double second,
                                                  int& week,
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
        // 计算钟差
        // ephObj: 输入参数，星历数据
        // clockVal: 输入/输出参数，计算出来的钟差值
        // 站心坐标转空间直角坐标
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
                                                 int& len,
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
                                              int& len,
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
         * @brief           度转弧度
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
         * @brief           弧度转度
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
