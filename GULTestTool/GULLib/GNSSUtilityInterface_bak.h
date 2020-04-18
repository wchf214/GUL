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

#include <string>

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
            // 周内秒格式： 周，秒
            // 示例：11周，11.111秒

            // 格式化周内秒时间
            // week: 输入参数，周
            // sec: 输入参数，秒
            // satType: 输入参数，卫星类型
            // formatString: 输出参数，时间格式化后字符串
            DLL_API int STD_CALL FormatWeekSecTime(const int week, const double sec, const int satType, char* formatString);
            // 格式化标准时间
            // year: 输入参数，年
            // month: 输入参数，月
            // day: 输入参数，日
            // hour: 输入参数，时
            // minute: 输入参数，分
            // second: 输入参数，秒
            // formatString: 输出参数，时间格式化后字符串
            DLL_API int STD_CALL FormatStandardTime(const int year, const int month, const int day,
                const int hour, const int minute, const double second,
                char* formatString);

            // GNSS时间类型与UTC时间互转
            DLL_API int STD_CALL GNSSTimeToUTCTime(const int week, const double sec, const int satType,
                int& year, int& month, int& day,
                int& hour, int& minute, double& second);
            DLL_API int STD_CALL UTCTimeToGNSSTime(const int year, const int month, const int day,
                const int hour, const int minute, const double second,
                const int satType,
                int& week, double& sec);

            // BD、Glonass、Galileo时间类型与GPS时间互转
            DLL_API int STD_CALL GNSSTimeConvert(const int srcWeek, const double srcSec, const int srcSatType,
                int& destWeek, double& destSec, const int destSatType);

            // 坐标相关接口
            // 坐标结构
            // 空间直角坐标格式为x,y,z
            // 站心坐标格式为east,north,up
            // 大地坐标格式为lat,lon,height
            // 空间直角坐标转大地坐标
            // x,y,z: 输入参数，空间直角坐标
            // lon,lat,height: 输出参数，大地坐标
            DLL_API int STD_CALL XYZ2BLH(const double x, const double y, const double z,
                double& lon, double& lat, double& height);
            // 大地坐标转空间直角坐标
            // lon,lat,height: 输入参数，空间直角坐标
            // x,y,z: 输出参数，大地坐标
            DLL_API int STD_CALL BLH2XYZ(const double lon, const double lat, const double height,
                double& x, double& y, double& z);
            // 空间直角坐标转站心坐标
            // curX,curY,curZ: 输入参数，当前站的空间直角坐标
            // refX,refY,refZ: 输入参数，参考站空间直角坐标
            // east,north,up: 输出参数，当前站的站心角坐标
            DLL_API int STD_CALL XYZ2ENU(const double curX, const double curY, const double curZ,
                const double refX, const double refY, const double refZ,
                double& east, double& north, double& up);
            // 站心坐标转空间直角坐标
            // east,north,up: 输入参数，当前站的站心角坐标
            // refX,refY,refZ: 输入参数，参考站空间直角坐标
            // curX,curY,curZ: 输出参数，当前站的空间直角坐标
            DLL_API int STD_CALL ENU2XYZ(const double east, const double north, const double up,
                const double refX, const double refY, const double refZ,
                double& curX, double& curY, double& curZ);

            // 星历相关接口
            // 计算钟差
            // ephObj: 输入参数，星历数据
            // clockVal: 输入/输出参数，计算出来的钟差值
            DLL_API int STD_CALL CalcGlonassEphSatClock(const SEpochSatObs& obsObj, const SGlonassEphemeris& ephObj, double& clockVal);
            DLL_API int STD_CALL CalcEphSatClock(const SEpochSatObs& obsObj, const SEphemeris& ephObj, double& clockVal);
            // 计算位置
            // ephObj: 输入参数，星历数据
            // x,y,z: 输出参数，计算出来的位置值
            DLL_API int STD_CALL CalcGlonassEphSatPos(const SEpochSatObs& obsObj, const SGlonassEphemeris& ephObj, double& x, double& y, double& z);
            DLL_API int STD_CALL CalcEphSatPos(const SEpochSatObs& obsObj, const SEphemeris& ephObj, double& x, double& y, double& z);

            // 角度相关接口
            // 格式化角度
            // degree: 输入参数，小数形式的度
            // formatType: 输入参数，true时，格式化为度，false时格式化为度分秒;默认为true
            // formatString: 输出参数，格式化后的字符串
            DLL_API int STD_CALL FormatAngleByDegree(const double degree, char* formatString, const bool formatType = true);
            // 格式化角度
            // degree: 输入参数，角
            // minute: 输入参数，分
            // sec: 输入参数，秒
            // formatType: 输入参数，true时，格式化为度，false时格式化为度分秒;默认为true
            // formatString: 输出参数，格式化后的字符串
            DLL_API int STD_CALL FormatAngleByDMS(const int degree, const int minute, const double sec,
                char* formatString, const bool formatType = true);
            // 度转弧度
            // degree: 输入参数，度
            // radian: 输出参数，弧度
            DLL_API int STD_CALL Deg2Rad(const double degree, double& radian);
            // degree: 输入参数，度
            // minute: 输入参数，度
            // sec: 输入参数，度
            // radian: 输出参数，弧度
            DLL_API int STD_CALL DMS2Rad(const int degree, const int minute, const double sec, double& radian);
            // 弧度转度
            // radian: 输入参数，弧度
            // degree: 输出参数，度
            DLL_API int STD_CALL Rad2Deg(const double radian, double& degree);
            // radian: 输入参数，弧度
            // degree: 输出参数，度
            // minute: 输出参数，分
            // sec: 输出参数，秒
            DLL_API int STD_CALL Rad2DMS(const double radian, int& degree, int& minute, double& sec);
#ifdef __cplusplus
        } // end extern "C"
#endif
    }  // end namespace GNSSUtilityLib
}  // end namespace sixents

#endif