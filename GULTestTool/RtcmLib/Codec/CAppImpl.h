/**
 * @file        CAppImpl.h
 * @author      yangzhenxing/yangzhenxing@sixents.com
 * @version     1.0
 * @date        2019-12-20
 * @brief       RTCM 接口标准实现类。
 * @details     通过对IAppOpt的继承，实现IAppOpt中的纯虚函数。
 * @note        change history:
 *                  <2019-12-20>  | 1.0 | yangzhenxing | 创建初始版本
 * @copyright   Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _CAPPIMPL_H_
#define _CAPPIMPL_H_

#include "IAppOpt.h"

namespace sixents
{
    class CCfgMng;
    class CLog;
    class ICodecOpt;

    /**
     * @class   CAppImpl
     * @brief   Rtcm接口实现类
     * @author  yangzhenxing
     * @note    N/A
     */
    class DLL_API CAppImpl : public IAppOpt
    {
    public:
        CAppImpl();
        virtual ~CAppImpl();

    public:
        /**
         * @brief           初始化Rtcm编解码模块
         * @author          yangchengyi
         * @param[in]       pamIn PN_INT_LOG_LEVEL,PN_INT_LOG_FILE_NUM,PN_STR_LOG_FILE_NAME,PN_INT_LOG_MAX_SIZE
         * @param[out]      pamOut PN_INT_STATUS,PN_STR_ERR_INF
         * @exception       N/A
         * @return          返回值参考Constents.h中的返回值定义
         * @retval          RETURN_SUCCESS  成功
         *                  RETURN_FAIL     失败
         *                  RETURN_UNSUPPORTED_RTCM_MSG 暂不支持的协议
         * @note            N/A
         */
        virtual INT32 RtcmInit(CParam& pamIn, CParam& pamOut) final;

        /**
        * @brief        原始电文数据长度计算
        * @author       yangzhenxing
        * @param[in]    pbyBuf:输入缓冲
                        uiLen: 缓冲长度
                        uiMsgPos:当前缓冲的偏移
        * @param[out]   uiMsgPos:当前缓冲的偏移,如没有找到D3
        ，则会不断累加向后查找，找到D3后,该值不变，直到调用方将该偏移进行调整
                        uiMsgType:电文类型，解析成功后，该值表示当前解析电文的类型，例如1074，1005等
                        uiExpectLen:期待字节数，该长度表示，电文接收方在uiLen的基础上，至少还需要收取多长的数据，才可能解析出一条完整电文。
        * @exception    N/A
        * @return       "0" 表示电文数据不全还需要读取更多数据， ">0"表示当前以uiMsgPos
        偏移为起点，实际解析出来的电文长度
        * @retval       RETURN_SUCCESS  成功
        *               RETURN_FAIL     失败
        *               RETURN_UNSUPPORTED_RTCM_MSG 暂不支持的协议
        * @note         N/A
        */
        virtual INT32 RtcmGetMessage(
            const BYTE* pbyBuf, const UINT32& uiLen, UINT32& uiMsgType, UINT32& uiMsgPos, UINT32& uiExpectLen) final;

        /**
         * @brief        Rtcm 电文解码接口
         * @author       yangzhenxing
         * @param[in]    pamIn: PN_BA_MESSAGE_DATA
         * @param[out]   pamOut: PN_INT_STATUS,PN_STR_ERR_INF,PN_INT_MESSAGE_TYPE,PN_PTR_GNSS_DATA_OBJECT
         * @exception    N/A
         * @return       返回值参考Constents.h中的返回值定义
         * @retval       同上
         * @note         N/A
         */
        virtual INT32 RtcmDecode(CParam& pamIn, CParam& pamOut) final;

        /**
         * @brief        Rtcm 电文编码接口
         * @author       yangzhenxing
         * @param[in]    pamIn: PN_PTR_GNSS_DATA_OBJECT,PN_INT_MESSAGE_TYPE
         * @param[out]   pamOut: PN_INT_STATUS,PN_STR_ERR_INF,PN_BA_MESSAGE_DATA
         * @exception    N/A
         * @return       返回值参考Constents.h中的返回值定义
         * @retval       同上
         * @note         N/A
         */
        virtual INT32 RtcmEncode(CParam& pamIn, CParam& pamOut) final;

        /**
        * @brief        Rtcm控制接口，用于控制管理Rtcm运行时行为。
        * @author       yangzhenxing
        * @param[in]    pamIn: PN_INT_CMD_CODE = CMD_GET_LOG 时，无其他输入.
                               PN_INT_CMD_CODE = CMD_SET_LOG 时, PN_INT_LOG_LEVEL,PN_INT_LOG_FILE_NUM,
                                   PN_STR_LOG_FILE_NAME,PN_INT_LOG_MAX_SIZE 做为输入
        * @param[out]   pamOut:当 pamIn 中，PN_INT_CMD_CODE = CMD_GET_LOG 时, PN_INT_LOG_LEVEL,PN_INT_LOG_FILE_NUM,
                                   PN_STR_LOG_FILE_NAME,PN_INT_LOG_MAX_SIZEPN_INT_STATUS,PN_STR_ERR_INF 做为输出
                               当 pamIn 中，PN_INT_CMD_CODE = CMD_SET_LOG 时, PN_INT_STATUS,PN_STR_ERR_INF 做为输出
        * @exception    N/A
        * @return       返回值参考Constents.h中的返回值定义
        * @retval       同上
        * @note         N/A
        */
        virtual INT32 RtcmCmd(CParam& pamIn, CParam& pamOut) final;

        /**
         * @brief        Rtcm模块终止接口
         * @author       yangzhenxing
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       返回值参考Constents.h中的返回值定义
         * @retval       同上
         * @note         N/A
         */
        virtual INT32 RtcmFinal() final;

    private:
        /**
         * @brief        初始化配置
         * @author       yangzhenxing
         * @param[in]    pamIn:PN_INT_LOG_LEVEL,PN_INT_LOG_FILE_NUM, PN_STR_LOG_FILE_NAME,PN_INT_LOG_MAX_SIZE
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       true,false
         * @note         N/A
         */
        sixents::BOOL_T InitCfgMng(CParam& pamIn);

        /**
         * @brief        初始化Log
         * @author       yangzhenxing
         * @param[in]    pamIn:PN_INT_LOG_LEVEL,PN_INT_LOG_FILE_NUM, PN_STR_LOG_FILE_NAME,PN_INT_LOG_MAX_SIZE
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       true,false
         * @note         N/A
         */
        sixents::BOOL_T InitLog(CParam& pamIn);

        /**
         * @brief        初始化编解码
         * @author       yangzhenxing
         * @param[in]    pamIn:暂无输入数据元
         * @param[out]   N/A
         * @exception    N/A
         * @return       返回值参考Constents.h中的返回值定义
         * @retval       同上
         * @note         N/A
         */
        sixents::BOOL_T InitCodec(CParam& pamIn);

        /**
         * @brief        获取日志参数
         * @author       yangzhenxing
         * @param[in]    N/A
         * @param[out]   pamOut:PN_INT_LOG_LEVEL,PN_INT_LOG_FILE_NUM, PN_STR_LOG_FILE_NAME,PN_INT_LOG_MAX_SIZE
         * @exception    N/A
         * @return       BOOL_T
         * @retval       true,false
         * @note         N/A
         */
        sixents::BOOL_T GetLogParameter(CParam& pamOut) const;

        /**
         * @brief        获取日志参数
         * @author       yangzhenxing
         * @param[in]    pamIn: 其中任意一个或多个：PN_INT_LOG_LEVEL,PN_INT_LOG_FILE_NUM,
         * PN_STR_LOG_FILE_NAME,PN_INT_LOG_MAX_SIZE
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       true,false
         * @note         N/A
         */
        sixents::BOOL_T SetLogParameter(CParam& pamIn);

        /**
         * @brief        添加错误码和错误信息到参数封装类
         * @author       yangzhenxing
         * @param[in]    iRetCode
         * @param[out]   pamOut
         * @exception    N/A
         * @return       BOOL_T
         * @retval       true,false
         * @note         N/A
         */
        static sixents::BOOL_T AddErrorStr(sixents::INT32 iRetCode, CParam& pamOut);

    public:
        /**
         * @brief        获取单例对象指针
         * @author       yangzhenxing
         * @param[in]    iRetCode
         * @param[out]   N/A
         * @exception    N/A
         * @return       IAppOpt*
         * @retval       IAppOpt* 对象指针，内部错误时，返回nullptr
         * @note         N/A
         */
        static IAppOpt* GetSingletonInstance();
        static CAppImpl* s_pobjInstance;

    private:
        sixents::BOOL_T m_bInitFlag;
        CCfgMng* m_pobjCfgMng;
        CLog* m_pobjLog;
        ICodecOpt* m_pobjCodecOpt;
    };

} // namespace sixents

#endif // _CAPPIMPL_H_