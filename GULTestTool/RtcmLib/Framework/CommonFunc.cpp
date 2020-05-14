/**
 * @file        CommonFunc.cpp
 * @author      yangchenyi/yangchengyi@sixents.com
 * @version     1.0
 * @date        2019-12-20
 * @brief       公共函数模块。
 * @details     提供了通过的函数接口，例如字符串修剪、时间转换、HexString和二进制互转等。
 * @note        change history:
 *                  <2019-12-20>  | 1.0 | yangchenyi | 创建初始版本
 * @copyright   Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */
#include <chrono>
#include <exception>
#include <iomanip>
#include <sstream>

#include "CommonFunc.h"

namespace sixents
{
    static const sixents::UINT32 COMMON_FUNC_VALUE_1 = 1U;
    static const sixents::UINT32 COMMON_FUNC_VALUE_2 = 2U;
    static const sixents::UINT32 COMMON_FUNC_VALUE_16 = 16U;
    static const sixents::UINT32 COMMON_FUNC_VALUE_0XFF = 0xFFU;

    namespace common
    {
        using std::string;
        string Trim(const string& strSrc, const string& strTrim, const BOOL_T bIsChar)
        {

            std::string strTemp;
            if (strSrc.empty())
            {
                return strSrc;
            }

            // 将完全与s相同的字符串去掉
            if (!bIsChar)
            {
                strTemp = TrimLeft(strSrc, strTrim, false);
                return TrimRight(strTemp, strTrim, false);
            }

            strTemp = TrimLeft(strSrc, strTrim, true);
            return TrimRight(strTemp, strTrim, true);
        }

        string TrimLeft(const string& strSrc, const string& strTrim, const BOOL_T bIsChar)
        {
            if (strSrc.empty())
            {
                return strSrc;
            }

            // 去掉strSrc左边的字符串s
            if (!bIsChar)
            {
                if (strSrc.length() < strTrim.length())
                {
                    return strSrc;
                }

                if (strSrc.compare(0U, strTrim.length(), strTrim) == 0)
                {
                    return strSrc.substr(strTrim.length());
                }

                return strSrc;
            }

            // 去掉strSrc左边的 字符串s中的字符
            string::size_type szPos = 0U;
            while (szPos < strSrc.length())
            {
                if (strTrim.find_first_of(strSrc[szPos]) == string::npos)
                {
                    break;
                }

                ++szPos;
            }

            if (szPos == 0U)
            {
                return strSrc;
            }

            return strSrc.substr(szPos);
        }

        string TrimRight(const string& strSrc, const string& strTrim, const BOOL_T bIsChar)
        {
            if (strSrc.empty())
            {
                return strSrc;
            }

            // 去掉strSrc右边的字符串s
            if (!bIsChar)
            {
                if (strSrc.length() < strTrim.length())
                {
                    return strSrc;
                }

                if (strSrc.compare(strSrc.length() - strTrim.length(), strTrim.length(), strTrim) == 0)
                {
                    return strSrc.substr(0U, strSrc.length() - strTrim.length());
                }

                return strSrc;
            }

            // 去掉strSrc右边的 字符串s中的字符
            string::size_type szPos = strSrc.length();
            while (szPos != 0U)
            {
                if (strTrim.find_first_of(strSrc[szPos - COMMON_FUNC_VALUE_1]) == string::npos)
                {
                    break;
                }

                szPos--;
            }

            if (szPos == strSrc.length())
            {
                return strSrc;
            }

            return strSrc.substr(0U, szPos);
        }

        std::string Time2Str(const time_t& tmObj, const std::string& strFmt)
        {
            std::stringstream ss;
            ss << std::put_time(std::localtime(&tmObj), strFmt.c_str());
            return ss.str();
        }

        std::string Now2Str(const std::string& strFmt)
        {
            const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::stringstream ss;
            ss << std::put_time(std::localtime(&now), strFmt.c_str());
            return ss.str();
        }

        std::string HexStr2Str(const std::string& strSrc)
        {
            string strDst("");
            if ((strSrc.length() % COMMON_FUNC_VALUE_2) != 0U)
            {
                return std::move(strDst);
            }

            string strTmp = strSrc;
            while (true)
            {
                if (strTmp.empty() == true)
                {
                    break;
                }
                const string strValue = strTmp.substr(0U, COMMON_FUNC_VALUE_2);
                const INT32 i32Value = std::stoi(strValue, nullptr, static_cast< INT32 >(COMMON_FUNC_VALUE_16));
                strDst.push_back(static_cast< char >(i32Value));
                strTmp = strTmp.substr(2U);
            }
            return std::move(strDst);
        }

        std::string HexStr2Str(UINT8* const pbHex, const INT32 i32Len)
        {
            const std::string strTmp(reinterpret_cast< char* >(pbHex), static_cast< std::size_t >(i32Len));
            return HexStr2Str(strTmp);
        }

        std::string Str2HexStr(const std::string& strSrc)
        {
            string strDst("");
            for (const auto item : strSrc)
            {
                std::stringstream ss;
                ss << std::setw(static_cast< std::streamsize >(COMMON_FUNC_VALUE_2)) << std::setfill('0') << std::hex
                   << (static_cast< INT32 >(item) & static_cast< INT32 >(COMMON_FUNC_VALUE_0XFF));
                string strTmp = ss.str();
                strDst.insert(strDst.end(), strTmp.begin(), strTmp.end());
            }
            return std::move(strDst);
        }

        std::string Str2ByteArray(const std::string& strSrc)
        {
            return Str2HexStr(strSrc);
        }

        void SixentsAssert(BOOL_T bExpression, const string& strInfo)
        {
#ifdef NDEBUG
            return;
#else
            if (bExpression == false)
            {
                std::stringstream str;
                str << "File=" << __FILE__ << " Line=" << __LINE__ << "\t" << strInfo;
                throw std::logic_error(str.str().c_str());
            }
#endif
        }
    } // namespace common
} // namespace sixents
