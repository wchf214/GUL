/**
 * @copyright Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd.
 *       All rights reserved.
 * @file CLog.h
 * @author yangchenyi/yangchengyi@sixents.com
 * @version 1.0
 * @date 2019-12-20
 * @brief 该文件实现日志功能
 * @details 能配置文件路径、文件大小、文件数量、Log级别，自动按时间生成新的Log文件;
 *          本功能实现是平台无关的，底层做了windows/linux 的差异化处理;
 * @note
 *    change history:
 *    <2019-12-20>  | 1.0 | yangchenyi | 创建初始版本
 */

#ifndef _CLOG_H_
#define _CLOG_H_

#include <fstream>
#include <memory>
#include <string>

#include "CParam.h"
#include "../Platform/BasicType.h"

namespace sixents
{
    class CCfgMng;

    /**
     * @class      CLog
     * @brief      用于日志打印
     * @author     yangchengyi@sixents.com,yangzhenxing@sixents.com
     * @note       N/A
     */
    class CLog
    {
    public:
        enum E_LOG_LEVEL
        {
            LL_NONE = 0x00,  // 所有日志都不写
            LL_INFO = 0x01,  // 写info
            LL_WARN = 0x02,  // 警告日志
            LL_ERROR = 0x04, // 写错误日志
            LL_DEBUG = 0x10, // 调试日志
            LL_ANY = 0x17,   // 所有日志
            LL_MASK = 0xFF,  // 日志掩码
        };

    public:
        CLog();
        ~CLog();

        /**
         * @brief        CLog::Init(CCfgMng* pobjCfgMng)，初始化接口，从配置管理对象中读取相应的日志参数进行初始化
         * @author       yangchenyi/yangchengyi@sixents.com
         * @param[in]    pobjCfgMng:日志对象
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T(true,false)
         * @retval       返回值说明
         * @note         注解
         */
        BOOL_T Init(CCfgMng* const pobjCfgMng);

        /**
        * @brief        CLog::Init(CCfgMng* pobjCfgMng)，初始化接口，从外部输入参数进行初始化
        * @author       yangchenyi/yangchengyi@sixents.com
        * @param[in]    iLevel:日志对象
                        uiFileNum:最大文件数量,有效取值 [1-65536]
                        uiFileSize:最大文件长度 [1-65536]
                        strFileName: 文件路径，不能为空
        * @param[out]   N/A
        * @exception    N/A
        * @return       BOOL_T(true,false)
        * @retval       返回值说明
        * @note         N/A
        */
        BOOL_T
        Init(const INT32 iLevel, const UINT32 uiFileNum, const UINT32 uiFileSize, const std::string& strFileName);

        /**
         * @brief        CLog::Final()，终止接口，用于释放已打开的文件流
         * @author       yangchenyi/yangchengyi@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T(true,false)
         * @retval       返回值说明
         * @note         N/A
         */
        BOOL_T Final();

        /**
        * @brief        CLog::Trace(const string& strLogInfo, const INT32 iLevel)，日志打印接口
        * @author       yangchenyi/yangchengyi@sixents.com
        * @param[in]    strLogInfo:日志信息
                        iLevel:日志级别
        * @param[out]   N/A
        * @exception    N/A
        * @return       BOOL_T(true,false)
        * @retval       返回值说明
        * @note         N/A
        */
        BOOL_T Trace(const std::string& strLogInfo, const INT32 iLevel);

        /**
        * @brief        CLog::Trace(const string& strLogInfo, const INT32 iLevel)，二进制数据打印接口
        * @author       yangchenyi/yangchengyi@sixents.com
        * @param[in]    pbBin:二进制首地址
                        uiLen:二进制长度,（单位:字节）
                        iLevel:日志级别
        * @param[out]   N/A
        * @exception    N/A
        * @return       BOOL_T(true,false)
        * @retval       返回值说明
        * @note         N/A
        */
        BOOL_T TraceHex(const BYTE* pbBin, const UINT32 uiLen, const INT32 iLevel);

    public:
        /**
         * @brief        CLog::SetLogLevel(const INT32 iLevel)，设置日志级别
         * @author       yangzhenxing/yangzhenxing@sixents.com
         * @param[in]    iLevel:日志级别
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T(true,false)
         * @retval       返回值说明
         * @note         N/A
         */
        BOOL_T SetLogLevel(const INT32 iLevel);

        /**
        * @brief        CLog::GetLogLevel(),获取日志级别
        * @author       yangzhenxing/yangzhenxing@sixents.com
        * @param[in]    iLevel:日志级别
        * @param[out]   N/A
        * @exception    N/A
        * @return       INT32
        * @retval       返回值说明，日志界别
                        LL_NONE        = 0x00,      // 所有日志都不写
                        LL_INFO        = 0x01,      // 写info
                        LL_WARN        = 0x02,      // 警告日志
                        LL_ERROR       = 0x04,      // 写错误日志
                        LL_DEBUG       = 0x10,      // 调试日志
                        LL_ANY         = 0x17,      // 所有日志
                        LL_MASK        = 0xFF,      // 日志掩码
        * @note         N/A
        */
        INT32 GetLogLevel() const;

        /**
         * @brief        CLog::IsNeedLog(const INT32 iLevel),当前日志实例是否需要打印指定日志级别的判断接口
         * @author       yangchenyi/yangchengyi@sixents.com
         * @param[in]    iLevel:日志级别
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T(true,false)
         * @retval       返回值说明
         * @note         N/A
         */
        BOOL_T IsNeedLog(const INT32 iLevel) const;

        /**
         * @brief        CLog::OpenLogFile(),打开文件接口
         * @author       yangchenyi/yangchengyi@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T(true,false)
         * @retval       成功/失败
         * @note         N/A
         */
        BOOL_T OpenLogFile();

        /**
         * @brief        CLog::SetMaxFileNum(const UINT32 uiMaxFileNum),设置最大文件数
         * @author       yangzhenxing/yangzhenxing@sixents.com
         * @param[in]    uiMaxFileNum:最大文件数,取值[1-63355]
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T(true,false)
         * @retval       成功/失败
         * @note         N/A
         */
        BOOL_T SetMaxFileNum(const UINT32 uiMaxFileNum);

        /**
         * @brief        CLog::GetMaxFileNum(),获取最大文件数
         * @author       yangzhenxing/yangzhenxing@sixents.com
         * @param[in]    uiMaxFileNum:最大文件数,取值[1-63355]
         * @param[out]   N/A
         * @exception    N/A
         * @return       UINT32
         * @retval       日志文件数
         * @note         N/A
         */
        const UINT32 GetMaxFileNum() const;

        /**
         * @brief        CLog::SetMaxFileSize(),设置日志文件最大长度（字节）
         * @author       yangzhenxing/yangzhenxing@sixents.com
         * @param[in]    uiMaxFileSize:最大文件长度（MB）,取值[1-63355]
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T(true,false)
         * @retval       成功/失败
         * @note         N/A
         */
        BOOL_T SetMaxFileSize(const UINT32 uiMaxFileSize);

        /**
         * @brief        CLog::GetMaxFileSize(),获取最大文件长度
         * @author       yangzhenxing/yangzhenxing@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       UINT32
         * @retval       单个日志文件长度
         * @note         N/A
         */
        const UINT32 GetMaxFileSize() const;

        /**
         * @brief        CLog::SetLogFileName(),设置日志文件名称(包含路径)
         * @author       yangzhenxing/yangzhenxing@sixents.com
         * @param[in]    strFileName:日志文件名
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T(true,false)
         * @retval       成功/失败
         * @note         N/A
         */
        BOOL_T SetLogFileName(const std::string& strFileName);

        /**
         * @brief        CLog::GetLogFileName(),获取日志文件名(包含路径)
         * @author       yangzhenxing/yangzhenxing@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       std::string
         * @retval       日志文件名
         * @note         N/A
         */
        std::string GetLogFileName() const;

        /**
         * @brief        CLog::GetShortNameByLevel(),通过日志级别，获取对应的级别字符串
         * @author       yangzhenxing/yangzhenxing@sixents.com
         * @param[in]    INT32 iLevel:日志级别
         * @param[out]   N/A
         * @exception    N/A
         * @return       std::string
         * @retval       日志级别字符串
         * @note         N/A
         */
        static std::string GetShortNameByLevel(const INT32 iLevel);

    private:
        // 防止拷贝和赋值
        CLog& operator=(const CLog&) = delete;
        CLog(const CLog&) = delete;

    private:
        INT32 m_iLevel;                // 默认写所有日志
        UINT32 m_uiFileNum;            // 最多保留的日志文件数
        UINT32 m_uiFileSize;           // 日志文件最大大小(单位: MB)
        std::string m_strFileName;     // 日志文件名
        std::ofstream m_objFileStream; // 日志文件的文件流
    };
}; // namespace sixents

#endif
