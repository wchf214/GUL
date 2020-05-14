/**
 * @file        CRtcmCode.h
 * @author      yangchengyi/yangchengyi@sixents.com
 * @version     1.0
 * @date        2019-12-20
 * @brief       RTCM 编解码实现类
 * @details     CRtcmCode实现了了编解码接口对应的虚接口
 * @note        change history:
 *                  <2019-12-20>  | 1.0 | yangchengyi | 创建初始版本
 * @copyright   Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _CRTCM_CODE_H_
#define _CRTCM_CODE_H_

#include "CRtcmDecoder.h"
#include "CRtcmEncoder.h"
#include "../Framework/CCfgMng.h"
#include "../Framework/CLog.h"
#include "ICodecOpt.h"

namespace sixents
{
    /**
     * @class   CRtcmCode
     * @brief   Rtcm 编码类
     * @author  yangzhenxing
     * @note    N/A
     */
    class CRtcmCode : public ICodecOpt
    {
    public:
        CRtcmCode();
        virtual ~CRtcmCode();

        /**
         * @brief        初始化接口
         * @author       yangchengyi
         * @param[in]    pobjLog:日志对象指针，pobjCfgMng:配置对象指针
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       true,false
         * @note         N/A
         */
        BOOL_T Init(CLog* const pobjLog, CCfgMng* const pobjCfgMng);

        /**
         * @brief        解码接口
         * @author       yangchengyi
         * @param[in]    pamIn:PN_BA_MESSAGE_DATA
         * @param[out]   pamOut:PN_INT_STATUS,PN_STR_ERR_INF,PN_INT_MESSAGE_TYPE,PN_PTR_GNSS_DATA_OBJECT
         * @exception    N/A
         * @return       返回值参考Constents.h中的返回值定义
         * @retval       同上
         * @note         N/A
         */
        virtual INT32 RtcmDecode(CParam& pamIn, CParam& pamOut);

        /**
         * @brief        编码接口
         * @author       yangchengyi
         * @param[in]    pamIn: PN_PTR_GNSS_DATA_OBJECT,PN_INT_MESSAGE_TYPE
         * @param[out]   pamOut: PN_INT_STATUS,PN_STR_ERR_INF,PN_BA_MESSAGE_DATA
         * @exception    N/A
         * @return       返回值参考Constents.h中的返回值定义
         * @retval       同上
         * @note         N/A
         */
        virtual INT32 RtcmEncode(CParam& pamIn, CParam& pamOut);

    private:
        CLog* m_pobjLog;
        CCfgMng* m_pobjCfgMng;
        CRtcmDecoder m_objDecoder;
        CRtcmEncoder m_objEncoder;
    };

} // namespace sixents

#endif //_CRTCM_CODE_H_
