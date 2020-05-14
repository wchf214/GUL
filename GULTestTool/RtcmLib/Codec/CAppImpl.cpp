#define DLL_EXPORT

#include "CAppImpl.h"
#include "CCodecUtilities.h"
#include "CRtcmCode.h"
#include "../Framework/CCfgMng.h"
#include "../Framework/CLog.h"
#include "../Framework/CParam.h"
#include "../Platform/Windows/ToolFunc.h"

using namespace sixents::common::rtcm;

namespace sixents
{
    CAppImpl* CAppImpl::s_pobjInstance = nullptr;

    CAppImpl::CAppImpl()
        : IAppOpt()
        , m_pobjCfgMng(nullptr)
        , m_pobjLog(nullptr)
        , m_pobjCodecOpt(nullptr)
        , m_bInitFlag(false)
    {}
    CAppImpl::~CAppImpl()
    {
        CAppImpl::RtcmFinal();
    }

    sixents::INT32 CAppImpl::RtcmInit(CParam& pamIn, CParam& pamOut)
    {
        INT32 iRetCode = common::rtcm::RETURN_FAIL;
        do
        {
            if (m_bInitFlag == true)
            {
                iRetCode = common::rtcm::RETURN_SUCCESS;
                break;
            }

            if (!InitCfgMng(pamIn))
            {
                iRetCode = common::rtcm::RETURN_INVALID_PARAMETER;
                break;
            }

            if (!InitLog(pamIn))
            {
                iRetCode = common::rtcm::RETURN_FAIL;
                break;
            }

            if (!InitCodec(pamIn))
            {
                m_pobjLog->Trace("Failed to initialize RtcmCodec object.", sixents::CLog::LL_ERROR);
                iRetCode = common::rtcm::RETURN_FAIL;
                break;
            }

            iRetCode = common::rtcm::RETURN_SUCCESS;
            m_bInitFlag = true;
        } while (false);

        if (!AddErrorStr(iRetCode, pamOut))
        {
            if (m_pobjLog != nullptr)
            {
                m_pobjLog->Trace("Failed to add error information.\n", sixents::CLog::LL_ERROR);
            }
        }
        return iRetCode;
    }

    sixents::INT32 CAppImpl::RtcmGetMessage(
        const BYTE* pbyBuf, const UINT32& uiLen, UINT32& uiMsgType, UINT32& uiMsgPos, UINT32& uiExpectLen)
    {
        BOOL_T bRet = false;
        INT32 iRet = 0;
        UINT32 uiValidBufLen = 0U;
        UINT32 uiCalcLen = 0U;

        do
        {
            if ((pbyBuf == nullptr) || (uiLen == 0U) || (uiMsgPos >= uiLen))
            {
                break;
            }

            uiExpectLen = 3U;

            const UINT32 ui32ValidBufLen = uiLen - uiMsgPos;
            uiValidBufLen = ui32ValidBufLen;
            pbyBuf += uiMsgPos;

            bRet = true;
            while (uiValidBufLen != 0U)
            {
                if (static_cast< BYTE >(*pbyBuf) != static_cast< BYTE >(RTCM32_PREABLE))
                {
                    ++uiMsgPos;
                    ++pbyBuf;
                    --uiValidBufLen;
                    continue;
                }

                if (uiValidBufLen < MSG_HEAD_BYTE_LENGTH)
                {
                    uiExpectLen = MSG_HEAD_BYTE_LENGTH - uiValidBufLen;
                    break; // exit with success
                }

                uiCalcLen =
                    sixents::CCodecUtilities::GetUnsignedIntBit(pbyBuf,
                                                                MSG_DATA_LENGTH_START_INDEX,
                                                                MSG_DATA_LENGTH); // calculate length for data field
                if (uiCalcLen > MSG_MAX_LENGTH)
                {
                    ++uiMsgPos;
                    ++pbyBuf;
                    --uiValidBufLen;
                    continue;
                }

                if ((uiCalcLen + MSG_HEAD_BYTE_LENGTH) > uiValidBufLen)
                {
                    uiExpectLen = uiCalcLen + MSG_HEAD_BYTE_LENGTH - uiValidBufLen;
                    break; // exit with success
                }

                const UINT32 cc = sixents::CCodecUtilities::RtkCrc24q(pbyBuf, uiCalcLen + MSG_HEAD_BYTE_LENGTH);
                const UINT32 cb = sixents::CCodecUtilities::GetUnsignedIntBit(
                    &pbyBuf[MSG_HEAD_BYTE_LENGTH], uiCalcLen * DATA_LENGTH_8, DATA_LENGTH_24);
                if (cc != cb)
                {
                    ++uiMsgPos;
                    ++pbyBuf;
                    --uiValidBufLen;
                    continue;
                }

                const UINT32 tp =
                    sixents::CCodecUtilities::GetUnsignedIntBit(pbyBuf, MSG_TYPE_BIT_OFFSET, MSG_TYPE_BIT_SIZE);
                if ((uiMsgType == 0U) || (tp == uiMsgType))
                {
                    uiMsgType = tp;
                    iRet = static_cast< INT32 >(uiCalcLen) + MSG_HEAD_BYTE_LENGTH + CRC24_DATA_LENGTH;
                    uiExpectLen = MSG_HEAD_BYTE_LENGTH;
                    break; // exit with success
                }

                ++uiMsgPos;
                ++pbyBuf;
                --uiValidBufLen;
            }

        } while (false);

        if (!bRet)
        {
            iRet = -1;
            uiExpectLen = 3U;
        }

        return iRet;
    }

    sixents::INT32 CAppImpl::RtcmDecode(CParam& pamIn, CParam& pamOut)
    {
        INT32 iRetCode = common::rtcm::RETURN_FAIL;
        do
        {
            if (m_bInitFlag == false)
            {
                iRetCode = common::rtcm::RETURN_NOT_INITIALIZED;
                break;
            }

            if ((m_pobjCodecOpt == nullptr) || (m_pobjLog == nullptr))
            {
                iRetCode = common::rtcm::RETURN_INVALID_PARAMETER;
                break;
            }

            if (!pamIn.AddValue(sixents::common::rtcm::PN_PTR_LOG_OBJECT, sixents::PDT_POINTER, m_pobjLog, nullptr))
            {
                m_pobjLog->Trace("Failed to initialize RtcmCodec object.\n", sixents::CLog::LL_ERROR);
                break;
            }

            iRetCode = m_pobjCodecOpt->RtcmDecode(pamIn, pamOut);
            pamIn.DeleteValue(sixents::common::rtcm::PN_PTR_LOG_OBJECT);

        } while (false);

        if (!AddErrorStr(iRetCode, pamOut))
        {
            if (m_pobjLog != nullptr)
            {
                m_pobjLog->Trace("Failed to add error information.\n", sixents::CLog::LL_ERROR);
            }
        }

        return iRetCode;
    }

    sixents::INT32 CAppImpl::RtcmEncode(CParam& pamIn, CParam& pamOut)
    {
        INT32 iRetCode = common::rtcm::RETURN_FAIL;

        do
        {
            if (!m_bInitFlag)
            {
                iRetCode = common::rtcm::RETURN_NOT_INITIALIZED;
                break;
            }

            if ((m_pobjCodecOpt == nullptr) || (m_pobjLog == nullptr))
            {
                iRetCode = common::rtcm::RETURN_INVALID_PARAMETER;
                break;
            }

            if (!pamIn.AddValue(sixents::common::rtcm::PN_PTR_LOG_OBJECT, sixents::PDT_POINTER, m_pobjLog, nullptr))
            {
                m_pobjLog->Trace(string("Failed to wrap") + sixents::common::rtcm::PN_PTR_LOG_OBJECT,
                                 sixents::CLog::LL_ERROR);
                break;
            }

            iRetCode = m_pobjCodecOpt->RtcmEncode(pamIn, pamOut);

            // 将日志对象指针从
            pamIn.DeleteValue(sixents::common::rtcm::PN_PTR_LOG_OBJECT);
        } while (false);

        if (!AddErrorStr(iRetCode, pamOut))
        {
            if (m_pobjLog != nullptr)
            {
                m_pobjLog->Trace("Failed to add error information.\n", sixents::CLog::LL_ERROR);
            }
        }

        return iRetCode;
    }

    sixents::INT32 CAppImpl::RtcmCmd(CParam& pamIn, CParam& pamOut)
    {
        INT32 iRetCode = common::rtcm::RETURN_FAIL;
        UINT32 uiCmdCode = 0U;

        do
        {
            if (!m_bInitFlag)
            {
                iRetCode = common::rtcm::RETURN_NOT_INITIALIZED;
                break;
            }

            if (!pamIn.GetValue(common::rtcm::PN_INT_CMD_CODE, &uiCmdCode, NULL))
            {
                iRetCode = common::rtcm::RETURN_INVALID_PARAMETER;
                break;
            }

            if (uiCmdCode == common::rtcm::CMD_GET_LOG)
            {
                if (!GetLogParameter(pamOut))
                {
                    iRetCode = common::rtcm::RETURN_FAIL;
                    break;
                }
            }
            else if (uiCmdCode == common::rtcm::CMD_SET_LOG)
            {
                if (!SetLogParameter(pamIn))
                {
                    iRetCode = common::rtcm::RETURN_INVALID_PARAMETER;
                    break;
                }
            }
            else
            {
                iRetCode = common::rtcm::RETURN_INVALID_PARAMETER;
                break;
            }

            iRetCode = common::rtcm::RETURN_SUCCESS;

        } while (false);

        if (!AddErrorStr(iRetCode, pamOut))
        {
            if (m_pobjLog != nullptr)
            {
                m_pobjLog->Trace("Failed to add error information.\n", sixents::CLog::LL_ERROR);
            }
        }

        return iRetCode;
    }

    sixents::INT32 CAppImpl::RtcmFinal()
    {
        if (m_pobjCodecOpt != nullptr)
        {
            delete m_pobjCodecOpt;
            m_pobjCodecOpt = nullptr;
        }

        if (m_pobjLog != nullptr)
        {
            delete m_pobjLog;
            m_pobjLog = nullptr;
        }

        m_bInitFlag = false;

        return common::rtcm::RETURN_SUCCESS;
    }

    BOOL_T CAppImpl::InitCfgMng(CParam& pamIn)
    {
        BOOL_T bRet = false;
        string strConfigName;

        do
        {
            if (m_pobjCfgMng == nullptr)
            {
                m_pobjCfgMng = new (std::nothrow) CCfgMng();
                if (m_pobjCfgMng == nullptr)
                {
                    break;
                }
            }

            if (pamIn.GetValue(common::rtcm::PN_STR_CONFIG_FILE, &strConfigName, nullptr))
            {
                if (!IsFileExist(strConfigName))
                {
                    break;
                }

                if (!m_pobjCfgMng->Init(strConfigName))
                {
                    break;
                }
            }
            else
            {
                if (!m_pobjCfgMng->UpdateByDefaultValue())
                {
                    break;
                }
            }

            bRet = true;
        } while (false);

        return bRet;
    }

    BOOL_T CAppImpl::InitLog(CParam& pamIn)
    {
        BOOL_T bRet = false;

        do
        {
            if (m_pobjLog == nullptr)
            {
                m_pobjLog = new (std::nothrow) CLog();
                if (m_pobjLog == nullptr)
                {
                    break;
                }
            }

            string strFileName = MAP_CONFIG_DEF.at(STR_CONFIG_LOG_FILE_NAME); // "./rtcm.log";

            if (pamIn.IsExist(sixents::common::rtcm::PN_STR_LOG_FILE_NAME)
                || pamIn.IsExist(sixents::common::rtcm::PN_INT_LOG_LEVEL)
                || pamIn.IsExist(sixents::common::rtcm::PN_INT_LOG_FILE_NUM)
                || pamIn.IsExist(sixents::common::rtcm::PN_INT_LOG_MAX_SIZE))
            {
                INT32 iLevel = CLog::LL_ANY;
                UINT32 uiFileNum = 0U;
                UINT32 uiMaxSize = 0U;

                if ((!pamIn.GetValue(sixents::common::rtcm::PN_STR_LOG_FILE_NAME, &strFileName, nullptr))
                    || (!pamIn.GetValue(sixents::common::rtcm::PN_INT_LOG_LEVEL, &iLevel, nullptr))
                    || (!pamIn.GetValue(sixents::common::rtcm::PN_INT_LOG_FILE_NUM, &uiFileNum, nullptr))
                    || (!pamIn.GetValue(sixents::common::rtcm::PN_INT_LOG_MAX_SIZE, &uiMaxSize, nullptr)))
                {
                    break;
                }
                if (!m_pobjLog->Init(iLevel, uiFileNum, uiMaxSize, strFileName))
                {
                    break;
                }

                // synchronize the values to CCfgMng object.
                BOOL_T bRet1 = m_pobjCfgMng->SetValue(sixents::common::rtcm::PN_STR_LOG_FILE_NAME, strFileName);
                bRet1 &= m_pobjCfgMng->SetValue(sixents::common::rtcm::PN_INT_LOG_LEVEL, iLevel);
                bRet1 &= m_pobjCfgMng->SetValue(sixents::common::rtcm::PN_INT_LOG_FILE_NUM, uiFileNum);
                bRet1 &= m_pobjCfgMng->SetValue(sixents::common::rtcm::PN_INT_LOG_MAX_SIZE, uiMaxSize);
                if (!bRet1)
                {
                    if (m_pobjLog != nullptr)
                    {
                        m_pobjLog->Trace("Failed to synchronize the values to CCfgMng object!", sixents::CLog::LL_WARN);
                    }
                }
            }
            else
            {
                if (!m_pobjLog->Init(m_pobjCfgMng))
                {
                    break;
                }
            }

            bRet = true;
        } while (false);

        return bRet;
    }

    BOOL_T CAppImpl::InitCodec(CParam& pamIn)
    {
        UNREFERENCED_PARAMETER(pamIn);
        BOOL_T bRet = false;

        do
        {
            if (m_pobjCodecOpt == nullptr)
            {
                m_pobjCodecOpt = new (std::nothrow) CRtcmCode();
                if (m_pobjCodecOpt == nullptr)
                {
                    break;
                }
            }

            bRet = true;
        } while (false);

        return bRet;
    }

    BOOL_T CAppImpl::GetLogParameter(CParam& pamOut) const
    {
        BOOL_T bRet = false;
        UINT32 uiMaxFileSize = 0U;
        UINT32 uiMaxFileNum = 0U;
        INT32 iLogLevel = 0;
        std::string strLogFileName;

        do
        {
            if (m_pobjLog == nullptr)
            {
                break;
            }

            strLogFileName = m_pobjLog->GetLogFileName();
            if (!pamOut.AddValue(PN_STR_LOG_FILE_NAME, PDT_STRING, &strLogFileName, nullptr))
            {
                break;
            }

            iLogLevel = m_pobjLog->GetLogLevel();
            if (!pamOut.AddValue(PN_INT_LOG_LEVEL, PDT_INT, &iLogLevel, nullptr))
            {
                break;
            }

            uiMaxFileNum = m_pobjLog->GetMaxFileNum();
            if (!pamOut.AddValue(PN_INT_LOG_FILE_NUM, PDT_INT, &uiMaxFileNum, nullptr))
            {
                break;
            }

            uiMaxFileSize = m_pobjLog->GetMaxFileSize();
            if (!pamOut.AddValue(PN_INT_LOG_MAX_SIZE, PDT_INT, &uiMaxFileSize, nullptr))
            {
                break;
            }

            bRet = true;
        } while (false);

        return bRet;
    }

    BOOL_T CAppImpl::SetLogParameter(CParam& pamIn)
    {
        BOOL_T bRet = false;
        UINT32 uiMaxFileSize = 0U;
        UINT32 uiMaxFileNum = 0U;
        INT32 iLogLevel = 0;
        std::string strLogFileName;

        do
        {
            if (m_pobjLog == nullptr)
            {
                break;
            }

            if (pamIn.GetValue(PN_STR_LOG_FILE_NAME, &strLogFileName, nullptr))
            {
                if (!m_pobjLog->SetLogFileName(strLogFileName))
                {
                    break;
                }
            }

            if (pamIn.GetValue(PN_INT_LOG_LEVEL, &iLogLevel, nullptr))
            {
                if (!m_pobjLog->SetLogLevel(iLogLevel))
                {
                    break;
                }
            }

            if (pamIn.GetValue(PN_INT_LOG_FILE_NUM, &uiMaxFileNum, nullptr))
            {
                if (!m_pobjLog->SetMaxFileNum(uiMaxFileNum))
                {
                    break;
                }
            }

            if (pamIn.GetValue(PN_INT_LOG_MAX_SIZE, &uiMaxFileSize, nullptr))
            {
                if (!m_pobjLog->SetMaxFileSize(uiMaxFileSize))
                {
                    break;
                }
            }

            bRet = true;
        } while (false);

        return bRet;
    }

    sixents::IAppOpt* CAppImpl::GetSingletonInstance()
    {
        if (s_pobjInstance == nullptr)
        {
            s_pobjInstance = new CAppImpl();
        }

        return s_pobjInstance;
    }

    sixents::BOOL_T CAppImpl::AddErrorStr(sixents::INT32 iRetCode, CParam& pamOut)
    {
        string strError;
        switch (iRetCode)
        {
            case RETURN_SUCCESS:
            {
                strError = ERRINF_SUCCESS;
            }
            break;
            case RETURN_FAIL:
            {
                strError = ERRINF_FAIL;
            }
            break;
            case RETURN_PACKAGE_LENGHT_ERROR:
            {
                strError = ERRINF_PACKAGE_LENGHT_ERROR;
            }
            break;
            case RETURN_CRC_CHECK_FAILED:
            {
                strError = ERRINF_CRC_CHECK_FAILED;
            }
            break;
            case RETURN_STATION_CORRECT:
            {
                strError = ERRINF_STATION_CORRECT;
            }
            break;
            case RETURN_PERMISSION_ERROR:
            {
                strError = ERRINF_PERMISSION_ERROR;
            }
            break;
            case RETURN_UNSUPPORTED_RTCM_MSG:
            {
                strError = ERRINF_UNSUPPORTED_RTCM_MSG;
            }
            break;
            case RETURN_NOT_INITIALIZED:
            {
                strError = ERRINF_NOT_INITIALIZED;
            }
            break;
            case RETURN_INVALID_PARAMETER:
            {
                strError = ERRINF_INVALID_PARAMETER;
            }
            break;
            default:
            {
                // Do nothing
            }
            break;
        }
        return (pamOut.AddValue(PN_INT_STATUS, PDT_INT, &iRetCode, nullptr)
                && pamOut.AddValue(PN_STR_ERR_INF, PDT_STRING, &strError, nullptr));
    }
} // namespace sixents
