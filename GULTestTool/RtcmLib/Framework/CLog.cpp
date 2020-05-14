/**
 * @file         	CLog.cpp
 * @brief        	日志打印类实现文件
 * @details         日志打印类，可以同时支持Windows以及Linux下的日志打印功能，具体功能包括：
                        1.日志级别，通过打印打印级别可以动态实现日志打印的范围。
                        2.日志文件数量，可以通过设定日志文件个数，当日志数量超过制定的文件数量时，进行滚动更新，即更总是新最早的日志文件
                        3.日志文件大小，设定了日志文件最大字节数（MB），当日志大小超过设定最大字节数后，从新创建新的日志文件。
 * @author       	yangchenyi/yangchengyi@sixents.com,yangzhenxing/yangzhenxing@sixents.com
 * @date            2019-12-21
 * @version      	V1.0.0
 * @note            注解
 * @copyright   	版权
 */
#include "CLog.h"
#include <algorithm>
#include <regex>
#include <sstream>
#include <thread>

#include "../Platform/Windows/ToolFunc.h"
#include "CCfgMng.h"
#include "CommonFunc.h"
#include "Constants.h"

namespace sixents
{
    using namespace std;
    using namespace common::rtcm;
    using namespace common;

    namespace
    {
        const UINT32 CLOG_VALUE_1 = 1U;
        const UINT32 CLOG_VALUE_4 = 4U;
        const UINT32 CLOG_VALUE_10 = 10U;
        const UINT32 CLOG_VALUE_100 = 100U;
        const UINT32 CLOG_VALUE_0X0F = 0x0FU;
        const UINT32 CLOG_VALUE_65536 = 65536U;
        const UINT32 CLOG_VALUE_1024 = 1024U;
        // 对应 E_LOG_LEVEL 中的类型
        constexpr UINT64 ONE_MB = 1U * CLOG_VALUE_1024 * CLOG_VALUE_1024; // 1M 文件大小
        PCSTR STR_PATH_SLASH = "/";
    } // namespace

    // 构造
    CLog::CLog()
        : m_iLevel(static_cast< INT32 >(LL_ANY)) // 默认全部打印
        , m_uiFileNum(CLOG_VALUE_10)             // 默认文件数量
        , m_uiFileSize(CLOG_VALUE_100)           // 默认单个文件size最大100MB
    {}

    /**
     * @brief        ~CLog()
     * @author       yangchenyi/yangchengyi@sixents.com
     * @param[in]    N/A
     * @param[out]   N/A
     * @exception    N/A
     * @return       N/A
     * @retval       返回值说明
     * @note         CLog类析构函数，该函数内部调用Final()函数实现资源的关闭和释放操作
     */
    CLog::~CLog()
    {
        try
        {
            Final();
        }
        catch (...)
        {
            // Do nothing
        }
    }

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
    BOOL_T CLog::Init(CCfgMng* const pobjCfgMng)
    {
        BOOL_T bRet = false;
        INT32 iLevel = 0;
        string strLogFileName;
        UINT32 uiFileNum = 0U;
        UINT32 uiLogFileSize = 0U;

        do
        {
            if (pobjCfgMng == nullptr)
            {
                break;
            }

            // Get parameters from configuration object
            if (pobjCfgMng->GetValue< INT32 >(STR_CONFIG_LOG_LEVEL, iLevel) == false)
            {
                break;
            }
            else if (pobjCfgMng->GetValue(STR_CONFIG_LOG_FILE_NAME, strLogFileName) == false)
            {
                break;
            }
            else if (pobjCfgMng->GetValue< UINT32 >(STR_CONFIG_LOG_MAX_FILE_NUM, uiFileNum) == false)
            {
                break;
            }
            else if (pobjCfgMng->GetValue< UINT32 >(STR_CONFIG_LOG_FILE_MAX_SIZE, uiLogFileSize) == false)
            {
                break;
            }
            else
            {
                // Do nothing
            }

            // Invoke internal function to implement initialization process
            if (!Init(iLevel, uiFileNum, uiLogFileSize, strLogFileName))
            {
                break;
            }
            bRet = true;

        } while (false);

        return bRet;
    }

    /**
     * @brief        CLog::Init(CCfgMng* pobjCfgMng)，初始化接口，从外部输入参数进行初始化
     * @author       yangchenyi/yangchengyi@sixents.com
     * @param[in]    iLevel:日志对象
     *                   uiFileNum:最大文件数量,有效取值 [1-65536]
     *                   uiFileSize:最大文件长度 [1-65536]
     *                   strFileName: 文件路径，不能为空
     * @param[out]   N/A
     * @exception    N/A
     * @return       BOOL_T(true,false)
     * @retval       返回值说明
     * @note         N/A
     */
    BOOL_T CLog::Init(const INT32 iLevel, const UINT32 uiFileNum, const UINT32 uiFileSize, const string& strFileName)
    {
        // Check if the input parameters are invalid
        if (strFileName.empty() || (uiFileNum > CLOG_VALUE_65536) || (uiFileNum == 0U) || (uiFileSize < CLOG_VALUE_1)
            || (uiFileSize > CLOG_VALUE_65536))
        {
            // invalid input parameters
            return false;
        }

        m_strFileName = strFileName;
        //         if (m_strFileName.empty() == false)
        //         {
        //             if (OpenLogFile() == true)
        //             {
        //                 bRet = true;
        //             }
        //         }

        m_iLevel = iLevel;
        m_uiFileNum = uiFileNum;
        m_uiFileSize = uiFileSize;

        return true;
    }

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
    BOOL_T CLog::Final()
    {
        if (m_objFileStream.is_open())
        {
            m_objFileStream.close();
        }

        m_strFileName.empty();
        return true;
    }

    /**
     * @brief        CLog::Trace(const string& strLogInfo, const INT32 iLevel)，日志打印接口
     * @author       yangchenyi/yangchengyi@sixents.com
     * @param[in]    strLogInfo:日志信息
     *               iLevel:日志级别
     * @param[out]   N/A
     * @exception    N/A
     * @return       BOOL_T(true,false)
     * @retval       返回值说明
     * @note         N/A
     */
    BOOL_T CLog::Trace(const string& strLogInfo, const INT32 iLevel)
    {
        if (!IsNeedLog(iLevel))
        {
            return true;
        }

        if (!OpenLogFile())
        {
            return false;
        }

        m_objFileStream << Now2Str("%Y-%m-%d %H:%M:%S") << "|" << this_thread::get_id() << "|"
                        << GetShortNameByLevel(iLevel) << "|" << strLogInfo << endl;

        if (m_objFileStream.bad())
        {
            return false;
        }

        return true;
    }

    /**
     * @brief        CLog::Trace(const string& strLogInfo, const INT32 iLevel)，二进制数据打印接口
     * @author       yangchenyi/yangchengyi@sixents.com
     * @param[in]    pbBin:二进制首地址
     *               uiLen:二进制长度,（单位:字节）
     *               iLevel:日志级别
     * @param[out]   N/A
     * @exception    N/A
     * @return       BOOL_T(true,false)
     * @retval       返回值说明
     * @note         N/A
     */
    BOOL_T CLog::TraceHex(const BYTE* pbBin, const UINT32 uiLen, const INT32 iLevel)
    {
        BOOL_T bRet = false;

        if (IsNeedLog(iLevel) && (pbBin != nullptr) && (uiLen > 0U))
        {
            if (OpenLogFile())
            {
                BYTE byHigh = 0U;
                BYTE byLow = 0U;
                CHAR chHigh = static_cast< CHAR >(0);
                CHAR chLow = static_cast< CHAR >(0);
                m_objFileStream << Now2Str("%Y-%m-%d %H:%M:%S") << "|" << this_thread::get_id() << "|"
                                << GetShortNameByLevel(iLevel) << "|";

                UINT32 ui32Value = 0U;
                for (UINT32 i = 0U; i < uiLen; ++i)
                {
                    byHigh = ((*(pbBin)) >> CLOG_VALUE_4) & CLOG_VALUE_0X0F;
                    byLow = (*(pbBin)) & CLOG_VALUE_0X0F;

                    if (byHigh < CLOG_VALUE_10)
                    {
                        chHigh = static_cast< CHAR >(byHigh) + '0';
                    }
                    else
                    {
                        ui32Value = byHigh + static_cast< UINT32 >('A') - CLOG_VALUE_10;
                        chHigh = static_cast< CHAR >(ui32Value);
                    }

                    if (byLow < CLOG_VALUE_10)
                    {
                        chLow = static_cast< CHAR >(byLow) + '0';
                    }
                    else
                    {
                        ui32Value = byLow + static_cast< UINT32 >('A') - CLOG_VALUE_10;
                        chLow = static_cast< CHAR >(ui32Value);
                    }

                    m_objFileStream << chHigh << chLow;
                    ++pbBin;
                }
                m_objFileStream << endl;
                if (m_objFileStream.bad())
                {
                    bRet = false;
                }
                else
                {
                    bRet = true;
                }
            }
        }

        return bRet;
    }

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
    BOOL_T CLog::SetLogLevel(const INT32 iLevel)
    {
        m_iLevel = (iLevel & static_cast< INT32 >(LL_MASK));
        return true;
    }

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
    BOOL_T CLog::IsNeedLog(const INT32 iLevel) const
    {
        const BOOL_T bRet = ((iLevel & m_iLevel) != 0);
        return bRet;
    }

    /**
     * @brief        CLog::GetLogLevel(),获取日志级别
     * @author       yangzhenxing/yangzhenxing@sixents.com
     * @param[in]    iLevel:日志级别
     * @param[out]   N/A
     * @exception    N/A
     * @return       INT32
     * @retval       返回值说明，日志界别
     *               LL_NONE        = 0x00,      // 所有日志都不写
     *               LL_INFO        = 0x01,      // 写info
     *               LL_WARN        = 0x02,      // 警告日志
     *               LL_ERROR       = 0x04,      // 写错误日志
     *               LL_DEBUG       = 0x10,      // 调试日志
     *               LL_ANY         = 0x17,      // 所有日志
     *               LL_MASK        = 0xFF,      // 日志掩码
     * @note         N/A
     */
    INT32 CLog::GetLogLevel() const
    {
        return m_iLevel;
    }

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
    BOOL_T CLog::OpenLogFile()
    {
        string strAdjustFileName;
        string sFileName = m_strFileName;
        auto idx = m_strFileName.find_last_of(STR_PATH_SLASH);
        if (idx != string::npos)
            sFileName = m_strFileName.substr(idx + 1);
        auto iPos = sFileName.find(".");
        if (iPos == string::npos)
        {
            strAdjustFileName = m_strFileName.substr(0, idx + 1) + sFileName + "_" + Now2Str();
        }
        else
        {
            strAdjustFileName = m_strFileName.substr(0, idx + 1) + sFileName.substr(0U, iPos);
            strAdjustFileName += "_" + Now2Str() + sFileName.substr(iPos);
        }

        if (!m_objFileStream.is_open())
        {
            m_objFileStream.open(strAdjustFileName, ios::app);
            if (!m_objFileStream.is_open())
            {
                return false;
            }
        }

        // 删除历史日志
        if ((static_cast< UINT64 >(m_objFileStream.tellp())) >= ((static_cast< UINT64 >(m_uiFileSize) * ONE_MB)))
        {
            m_objFileStream.close();
            m_objFileStream.open(strAdjustFileName, ios::app);
        }

        const auto pos = m_strFileName.find_last_of(STR_PATH_SLASH);
        string strTempFilePath;
        string strFileName;
        if (pos != string::npos)
        {
            strTempFilePath = m_strFileName.substr(0, pos);
            strFileName = m_strFileName.substr(pos + 1U);
        }
        else
        {
            strTempFilePath = ".";
            strFileName = m_strFileName; // 当前文件夹
        }

        vector< string > vTmp;
        ScanDirFiles(strTempFilePath, vTmp);
        vector< string > vFiles;
        for (auto& sFile : vTmp)
        {
            auto iter = strFileName.find_last_of(".");
            string header, tail;
            if (iter == string::npos)
            {
                header = strFileName;
            }
            else
            {
                header = strFileName.substr(0, iter);
                tail = strFileName.substr(iter);
            }
            std::regex re(header + "_[0-9]{14}" + tail);
            std::smatch match;
            if (regex_match(sFile, match, re))
            {
                vFiles.push_back(sFile);
            }
        }

        sort(vFiles.begin(), vFiles.end());
        const size_t szSurplusFiles = vFiles.size() - m_uiFileNum;
        if (vFiles.size() > m_uiFileNum)
        {
            for (size_t i = 0U; i < szSurplusFiles; ++i)
            {
                remove((strTempFilePath + STR_PATH_SLASH + vFiles[i]).c_str());
            }
        }

        if (m_objFileStream.is_open())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

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
    BOOL_T CLog::SetMaxFileNum(const UINT32 uiMaxFileNum)
    {
        if (uiMaxFileNum > CLOG_VALUE_65536)
        {
            return false;
        }

        m_uiFileNum = uiMaxFileNum;
        return true;
    }

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
    const UINT32 CLog::GetMaxFileNum() const
    {
        return m_uiFileNum;
    }

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
    BOOL_T CLog::SetMaxFileSize(const UINT32 uiMaxFileSize)
    {
        if (uiMaxFileSize > CLOG_VALUE_65536)
        {
            return false;
        }
        m_uiFileSize = uiMaxFileSize;
        return true;
    }

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
    const UINT32 CLog::GetMaxFileSize() const
    {
        return m_uiFileSize;
    }

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
    BOOL_T CLog::SetLogFileName(const string& strFileName)
    {
        m_strFileName = strFileName;
        return true;
    }

    /**
     * @brief        CLog::GetLogFileName(),获取日志文件名(包含路径)
     * @author       yangzhenxing/yangzhenxing@sixents.com
     * @param[in]    N/A
     * @param[out]   N/A
     * @exception    N/A
     * @return       string
     * @retval       日志文件名
     * @note         N/A
     */
    string CLog::GetLogFileName() const
    {
        return m_strFileName;
    }

    /**
     * @brief        CLog::GetShortNameByLevel(),通过日志级别，获取对应的级别字符串
     * @author       yangzhenxing/yangzhenxing@sixents.com
     * @param[in]    INT32 iLevel:日志级别
     * @param[out]   N/A
     * @exception    N/A
     * @return       string
     * @retval       日志级别字符串,A表示Any，I表示Inf，W表示Warning，E表示Error，D表示Debug
     * @note         N/A
     */
    string CLog::GetShortNameByLevel(const INT32 iLevel)
    {
        string strName;

        if ((static_cast< INT32 >(CLog::LL_ANY) == (iLevel & static_cast< INT32 >(CLog::LL_MASK))))
        {

            strName = "A";
            return strName;
        }

        if ((static_cast< INT32 >(CLog::LL_INFO) & (iLevel & static_cast< INT32 >(CLog::LL_MASK)))
            != static_cast< INT32 >(LL_NONE))
        {

            strName += "I";
        }

        if ((static_cast< INT32 >(CLog::LL_WARN) & (iLevel & static_cast< INT32 >(CLog::LL_MASK)))
            != static_cast< INT32 >(LL_NONE))
        {
            strName += "W";
        }

        if ((static_cast< INT32 >(CLog::LL_ERROR) & (iLevel & static_cast< INT32 >(CLog::LL_MASK)))
            != static_cast< INT32 >(LL_NONE))
        {
            strName += "E";
        }

        if ((static_cast< INT32 >(CLog::LL_DEBUG) & (iLevel & static_cast< INT32 >(CLog::LL_MASK)))
            != static_cast< INT32 >(LL_NONE))
        {
            strName += "D";
        }

        return strName;
    }

} // namespace sixents
