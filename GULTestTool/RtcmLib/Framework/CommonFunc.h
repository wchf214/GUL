/**
 * @file        CommonFunc.h
 * @author      yangchenyi/yangchengyi@sixents.com
 * @version     1.0
 * @date        2019-12-20
 * @brief       公共函数模块。
 * @details     提供了通过的函数接口，例如字符串修剪、时间转换、HexString和二进制互转等。
 * @note        change history:
 *                  <2019-12-20>  | 1.0 | yangchenyi | 创建初始版本
 * @copyright   Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */
#ifndef _RTCM_COMMON_FUNC_H_
#define _RTCM_COMMON_FUNC_H_

#include <string>
#include <vector>

#include "../Platform/BasicType.h"

namespace sixents
{
    namespace common
    {
        // Todo： 修改为有意义的名称
        /**
         * @brief       去掉头部以及尾部的字符或字符串
         * @author      yangchengyi
         * @param[in]   strSrc 输入字符串
         * @param[in]   strTrim 需要去掉的字符
         * @param[in]   bIsChar 如果为true, 则去掉s中每个字符; 如果为false, 则去掉s字符串
         * @param[out]  N/A
         * @exception   N/A
         * @return      返回去掉后的字符串
         * @retval
         * @note        example: Trim("aabbccaaccbbaa", "ab", false) 返回值为:ccaacc
         *                       Trim("aabbccaaccbbaa", "ab", true)  返回值为:aabbccaaccbbaa
         */
        std::string
        Trim(const std::string& strSrc, const std::string& strTrim = " \r\n\t", const BOOL_T bIsChar = true);

        /**
         * @brief       去掉左边的字符或字符串
         * @author      yangchengyi
         * @param[in]   strSrc 输入字符串
         * @param[in]   strTrim 需要去掉的字符
         * @param[in]   bIsChar 如果为true, 则去掉s中每个字符; 如果为false, 则去掉s字符串
         * @param[out]  N/A
         * @exception   N/A
         * @return      返回去掉后的字符串
         * @retval
         * @note        example: Trim("aabbccaaccbbaa", "ab", false) 返回值为:ccaaccbbaa
         *                       Trim("aabbccaaccbbaa", "ab", true)  返回值为:aabbccaaccbbaa
         */
        std::string
        TrimLeft(const std::string& strSrc, const std::string& strTrim = " \r\n\t", const BOOL_T bIsChar = true);

        /**
         * @brief       去掉右边的字符或字符串
         * @author      yangchengyi
         * @param[in]   strSrc 输入字符串
         * @param[in]   strTrim 需要去掉的字符
         * @param[in]   bIsChar 如果为true, 则去掉s中每个字符; 如果为false, 则去掉s字符串
         * @param[out]  N/A
         * @exception   N/A
         * @return      返回去掉后的字符串
         * @retval
         * @note        example: Trim("aabbccaaccbbaa", "ab", false) 返回值为:aabbccaacc
         *                       Trim("aabbccaaccbbaa", "ab", true)  返回值为:aabbccaaccbbaa
         */
        std::string
        TrimRight(const std::string& strSrc, const std::string& strTrim = " \r\n\t", const BOOL_T bIsChar = true);

        /**
         * @brief       时间转字符串
         * @author      yangchengyi
         * @param[in]   tmObj 时间
         * @param[in]   strFmt 输出格式，默认输出格式是:（YYYYmmddHHMMSS:20191121093040)
         * @param[out]  N/A
         * @exception   N/A
         * @return      返回时间字符串
         * @retval
         * @note
         */
        std::string Time2Str(const time_t& tmObj, const std::string& strFmt = "%Y%m%d%H%M%S");

        /**
         * @brief       当前时间转字符串
         * @author      yangchengyi
         * @param[in]   strFmt 输出格式，默认输出格式是:（YYYYmmddHHMMSS:20191121093040)
         * @param[out]  N/A
         * @exception   N/A
         * @return      返回时间字符串
         * @retval
         * @note
         */
        std::string Now2Str(const std::string& strFmt = "%Y%m%d%H%M%S");

        /**
         * @brief       16进制数据转换为字符串
         * @author      yangchengyi
         * @param[in]   strSrc 需要转换的16进制的字符串
         * @param[out]  N/A
         * @exception   N/A
         * @return      返回转换后字符串
         * @retval
         * @note        example: "616263" 转换后为:"abc"
         */
        std::string HexStr2Str(const std::string& strSrc);

        /**
         * @brief       16进制数据转换为字符串
         * @author      yangchengyi
         * @param[in]   需要转换的16进制的buff
         * @param[in]   需要转换的buff的长度
         * @param[out]  N/A
         * @exception   N/A
         * @return      返回转换后字符串
         * @retval
         * @note        example: HexStr2Str("616263", 6) 转换后为:"abc"
         */
        std::string HexStr2Str(UINT8* const pbHex, const INT32 i32Len);

        /**
         * @brief       字符串转换为16进制数据
         * @author      yangchengyi
         * @param[in]   需要转换的字符串
         * @param[out]  N/A
         * @exception   N/A
         * @return      返回转换后16进制字符串
         * @retval
         * @note        example: Str2HexStr("abc") 转换后为:"616263"
         */
        std::string Str2HexStr(const std::string& strSrc);

        /**
         * @brief       断言功能实现
         * @author      zhuquanlin@sixents.com
         * @param[in]   bExpression 断言表达式结果
         * @param[in]   strInfo 触发断言时信息
         * @exception   N/A
         * @return      N/A
         * @retval      N/A
         * @note        N/A
         */
        void SixentsAssert(BOOL_T bExpression, const std::string& strInfo);
    } // namespace common
} // namespace sixents
#endif
