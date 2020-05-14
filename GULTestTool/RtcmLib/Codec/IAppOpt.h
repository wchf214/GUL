/**
 * @file        IAppOpt.h 
 * @author      yangzhenxing/yangzhenxing@sixents.com
 * @version     1.0
 * @date        2019-12-20
 * @brief       RTCM 导出接口抽象类
 * @details     IAppOpt包含了本模块六个导出接口对应的纯虚函数，以供实现类继承。
 * @note        change history:
 *                  <2019-12-20>  | 1.0 | yangzhenxing | 创建初始版本
 * @copyright   Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _IAPPOPT_H_
#define _IAPPOPT_H_

#include "../Framework/CParam.h"
#include "../Framework/Constants.h"
#include "../Platform/BasicType.h"

namespace sixents
{
#ifdef __cplusplus
    extern "C" {
#endif

    /**
    * @brief        命初始化Rtcm编解码模块
    * @author       yangzhenxing
    * @param[in]    pamIn 必须包含 PN_INT_LOG_LEVEL,PN_INT_LOG_FILE_NUM,PN_STR_LOG_FILE_NAME,PN_INT_LOG_MAX_SIZE ，数据元
    * @param[out]   pamOut 包含 PN_INT_STATUS,PN_STR_ERR_INF
    * @exception    N/A
    * @return       返回值参考Constents.h中的返回值定义
    * @retval       RETURN_SUCCESS  成功
    *               RETURN_FAIL     失败
    *               RETURN_UNSUPPORTED_RTCM_MSG 暂不支持的协议
    * @note         N/A
    */
    DLL_API INT32 STD_CALL RtcmInit(CParam& pamIn, CParam& pamOut);

    /**
    * @brief        原始电文数据长度计算
    * @author       yangzhenxing
    * @param[in]    pbyBuf:输入缓冲
                    uiLen: 缓冲长度
                    uiMsgPos:当前缓冲的偏移
    * @param[out]   uiMsgPos:当前缓冲的偏移,如没有找到D3 ，则会不断累加向后查找，找到D3后,该值不变，直到调用方将该偏移进行调整
                    uiMsgType:电文类型，解析成功后，该值表示当前解析电文的类型，例如1074，1005等
                    uiExpectLen:期待字节数，该长度表示，电文接收方在uiLen的基础上，至少还需要收取多长的数据，才可能解析出一条完整电文。
    * @exception    N/A
    * @return       "0" 表示电文数据不全还需要读取更多数据， ">0"表示当前以uiMsgPos 偏移为起点，实际解析出来的电文长度
    * @retval       RETURN_SUCCESS  成功
    *               RETURN_FAIL     失败
    *               RETURN_UNSUPPORTED_RTCM_MSG 暂不支持的协议
    * @note         N/A
    */
    DLL_API INT32 STD_CALL RtcmGetMessage(
        const BYTE* const pbyBuf, const UINT32& uiLen, UINT32& uiMsgType, UINT32& uiMsgPos, UINT32& uiExpectLen);

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
    DLL_API INT32 STD_CALL RtcmDecode(CParam& pamIn, CParam& pamOut);

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
    DLL_API INT32 STD_CALL RtcmEncode(CParam& pamIn, CParam& pamOut);

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
    DLL_API INT32 STD_CALL RtcmCmd(CParam& pamIn, CParam& pamOut);

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
    DLL_API INT32 STD_CALL RtcmFinal();

    /**
     * @class   IAppOpt
     * @brief   Rtcm接口类
     * @author  yangzhenxing
     * @note    N/A
     */
    class IAppOpt
    {
    public:
        IAppOpt();
        virtual ~IAppOpt();

    public:
        /**
        * @brief        命初始化Rtcm编解码模块
        * @author       yangzhenxing
        * @param[in]    pamIn 必须包含 PN_INT_LOG_LEVEL,PN_INT_LOG_FILE_NUM,PN_STR_LOG_FILE_NAME,PN_INT_LOG_MAX_SIZE ，数据元
        * @param[out]   pamOut 包含 PN_INT_STATUS,PN_STR_ERR_INF
        * @exception    N/A
        * @return       返回值参考Constents.h中的返回值定义
        * @retval       RETURN_SUCCESS  成功
        *               RETURN_FAIL     失败
        *               RETURN_UNSUPPORTED_RTCM_MSG 暂不支持的协议
        * @note         N/A
        */
        virtual INT32 RtcmInit(CParam& pamIn, CParam& pamOut) = 0;

        /**
        * @brief        原始电文数据长度计算
        * @author       yangzhenxing
        * @param[in]    pbyBuf:输入缓冲
                        uiLen: 缓冲长度
                        uiMsgPos:当前缓冲的偏移
        * @param[out]   uiMsgPos:当前缓冲的偏移,如没有找到D3 ，则会不断累加向后查找，找到D3后,该值不变，直到调用方将该偏移进行调整
                        uiMsgType:电文类型，解析成功后，该值表示当前解析电文的类型，例如1074，1005等
                        uiExpectLen:期待字节数，该长度表示，电文接收方在uiLen的基础上，至少还需要收取多长的数据，才可能解析出一条完整电文。
        * @exception    N/A
        * @return       "0" 表示电文数据不全还需要读取更多数据， ">0"表示当前以uiMsgPos 偏移为起点，实际解析出来的电文长度
        * @retval       RETURN_SUCCESS  成功
        *               RETURN_FAIL     失败
        *               RETURN_UNSUPPORTED_RTCM_MSG 暂不支持的协议
        * @note         N/A
        */
        virtual INT32 RtcmGetMessage(
            const BYTE* pbyBuf, const UINT32& uiLen, UINT32& uiMsgType, UINT32& uiMsgPos, UINT32& uiExpectLen) = 0;

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
        virtual INT32 RtcmDecode(CParam& pamIn, CParam& pamOut) = 0;

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
        virtual INT32 RtcmEncode(CParam& pamIn, CParam& pamOut) = 0;

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
        virtual INT32 RtcmCmd(CParam& pamIn, CParam& pamOut) = 0;

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
        virtual INT32 RtcmFinal() = 0;

    public:
        static std::unique_ptr< IAppOpt > CreateInstance();
    };
#ifdef __cplusplus
    }
#endif
} // namespace sixents

#endif // #ifndef _IAPPOPT_H_
