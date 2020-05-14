/**
 * @copyright Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd.
 *       All rights reserved.
 * @file     : CRtcmDecoder.h
 * @author   : zhuquanlin@sixents.com
 * @version  : 1.0
 * @date     : 2019/12/23 10:39
 * @brief    : 该文件实现RTCM解码功能
 * @details  : 目前支持RTCM的33种电文的解码，涵盖观测值，星历，参考站，轨道改正，钟差改正，码偏差，用户距离精度电文。
 *             所有解码流程参考文档RTCMSTANDARD 10403.3，个别电文原始数据单位可能与RTK lib库保持一致(注释会有标注).
 * @note
 *    change history:
 *    <2019/12/23>  | 1.0 | zhuquanlin | 创建初始版本
 */

#ifndef _CRTCM_DECODER_H_
#define _CRTCM_DECODER_H_

#include <array>
#include <functional>
#include <mutex>
#include <sstream>
#include "../Framework/Constants.h"
#include "ICodecOpt.h"

#ifdef UNIT_TEST
#undef private
#undef protected
#define private public
#define protected public
#endif
namespace sixents
{
    class CLog;

    /**
     * @class   : CRtcmDecoder
     * @author  : zhuquanlin@sixents.com
     * @brief   : RTCM解码实现类
     * @note    : 解码标准参考文档RTCMSTANDARD 10403.3
     */
    class CRtcmDecoder
    {
    public:
        /**
         * @brief      : CRtcmDecoder构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        CRtcmDecoder();

        /**
         * @brief      : CRtcmDecoder析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        ~CRtcmDecoder();

        /**
         * @brief      : 解析电文，得到电文ID
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    包含电文二进制流、电文长度
         * @param[out] : uiMsgType    解析电文成功后得到的电文ID
         * @exception  : N/A
         * @return     : BOOL_T
         * @retval     :
         *  <em>true</em>  表示解析电文成功
         *  <em>false</em> 表示解析电文失败
         * @note       : N/A
         */
        BOOL_T RtcmParseMessage(CParam& pamIn, UINT32& uiMsgType);

        /**
         * @brief      : 解码RTCM电文入口方法
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    包含电文二进制流、电文长度、日志对象
         * @param[out] : pamOut   电文解析成功后得到的GNSS数据对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecode(CParam& pamIn, CParam& pamOut);

    private:
        /**
         * @brief       解码1004电文(GPS卫星观测值电文)
         * @author      pengshupan
         * @param[in]   pamIn    电文二进制数据
         * @param[out]  pamOut   解析电文成功后得到的观测值对象
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 RtcmDecoder1004(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1005电文(坐标数据电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的参考站对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1005(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1006电文(坐标数据加天线数据电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的参考站对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1006(CParam& pamIn, CParam& pamOut);

        /**
         * @brief       解码1012电文(GLONASS卫星观测值电文)
         * @author      pengshupan
         * @param[in]   pamIn    电文二进制数据
         * @param[out]  pamOut   解析电文成功后得到的观测值对象
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 RtcmDecoder1012(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1019电文(GPS卫星导航星历电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的星历对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1019(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1020电文(GLONASS卫星导航星历电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到Glonass星历对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1020(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1033电文(接收机描述数据电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的参考站对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1033(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1042电文(BDS卫星导航星历电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的星历对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1042(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1044电文(QZSS卫星导航星历电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的星历对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1044(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1045电文(Galileo卫星导航星历电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的星历对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1045(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1046电文(Galileo卫星导航星历电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的参考站对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1046(CParam& pamIn, CParam& pamOut);

        /**
         * @brief       解码1057电文(GPS卫星轨道电文)
         * @author      pengshupan
         * @param[in]   pamIn    电文二进制数据
         * @param[out]  pamOut   解析电文成功后得到的卫星轨道对象
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 RtcmDecoder1057(CParam& pamIn, CParam& pamOut);
        /**
         * @brief       解码1058电文(GPS卫星钟差电文)
         * @author      pengshupan
         * @param[in]   pamIn    电文二进制数据
         * @param[out]  pamOut   解析电文成功后得到的卫星钟差对象
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 RtcmDecoder1058(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1059电文(GPS卫星DCB产品电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的DCB对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1059(CParam& pamIn, CParam& pamOut);

        /**
         * @brief       解码1060电文(GPS卫星轨道钟差电文)
         * @author      pengshupan
         * @param[in]   pamIn    电文二进制数据
         * @param[out]  pamOut   解析电文成功后得到的卫星轨道钟差对象
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 RtcmDecoder1060(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1061电文(GPS卫星URA产品电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的URA对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1061(CParam& pamIn, CParam& pamOut);

        /**
         * @brief       解码1062电文(GPS卫星高频钟差电文)
         * @author      pengshupan
         * @param[in]   pamIn    电文二进制数据
         * @param[out]  pamOut   解析电文成功后得到的卫星高频钟差对象
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 RtcmDecoder1062(CParam& pamIn, CParam& pamOut);

        /**
         * @brief       解码1063电文(GLONASS卫星轨道电文)
         * @author      pengshupan
         * @param[in]   pamIn    电文二进制数据
         * @param[out]  pamOut   解析电文成功后得到的卫星轨道对象
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 RtcmDecoder1063(CParam& pamIn, CParam& pamOut);

        /**
         * @brief       解码1064电文(GLONASS卫星钟差电文)
         * @author      pengshupan
         * @param[in]   pamIn    电文二进制数据
         * @param[out]  pamOut   解析电文成功后得到的卫星钟差对象
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 RtcmDecoder1064(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1065电文(GLONASS卫星DCB产品电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的DCB对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1065(CParam& pamIn, CParam& pamOut);

        /**
         * @brief       解码1066电文(GLONASS卫星轨道电文)
         * @author      pengshupan
         * @param[in]   pamIn    电文二进制数据
         * @param[out]  pamOut   解析电文成功后得到的卫星轨道钟差对象
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 RtcmDecoder1066(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1067电文(GLONASS卫星URA产品电文)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的URA对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1067(CParam& pamIn, CParam& pamOut);

        /**
         * @brief       解码1068电文(GLONASS卫星高频钟差电文)
         * @author      pengshupan
         * @param[in]   pamIn    电文二进制数据
         * @param[out]  pamOut   解析电文成功后得到的卫星高频钟差对象
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 RtcmDecoder1068(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1074电文(GPS卫星观测数据电文MSM4)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1074(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1077电文(GPS卫星观测数据电文MSM7)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1077(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1084电文(GLONASS卫星观测数据电文MSM4)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的Glonass观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>  表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1084(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1087电文(GLONASS卫星观测数据电文MSM7)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的Glonass观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1087(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1094电文(Galileo卫星观测数据电文MSM4)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1094(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1097电文(Galileo卫星观测数据电文MSM7)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1097(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1114电文(QZSS卫星观测数据电文MSM4)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1114(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1117电文(QZSS卫星观测数据电文MSM7)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1117(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1124电文(BDS卫星观测数据电文MSM4)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1124(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解码1127电文(BDS卫星观测数据电文MSM7)
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pamIn    电文二进制数据
         * @param[out] : pamOut   解析电文成功后得到的观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 RtcmDecoder1127(CParam& pamIn, CParam& pamOut);

        /**
         * @brief      : 解析MSM4类型电文
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pDataBuf      电文二进制数据
         * @param[in]  : enSatSystem   解析电文所属卫星系统
         * @param[out] : stEpochSatObs 解析电文成功后得到的观测值结构体
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 DecodeMsm4(const UINT8* const pDataBuf,
                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                         SEpochSatObs& stEpochSatObs);

        /**
         * @brief      : 解析MSM7类型电文
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pDataBuf      电文二进制数据
         * @param[in]  : enSatSystem   解析电文所属卫星系统
         * @param[out] : stEpochSatObs 解析电文成功后得到的观测值结构体
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 DecodeMsm7(const UINT8* const pDataBuf,
                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                         SEpochSatObs& stEpochSatObs);

        /**
         * @brief      : 解析MSM电文类型的头数据
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pDataBuf           电文二进制数据
         * @param[in]  : enSatSystem        解析电文所属卫星系统
         * @param[out] : stEpochSatObs      解析电文成功后得到的观测值结构体
         * @param[out] : ui32Index           当前电文解析偏移量
         * @param[out] : ui32SatelliteNum   卫星数量
         * @param[out] : ui32SignalNum      信号数量
         * @param[out] : ui32CellNum        单元数量
         * @param[out] : ui64CellLength     单元数据长度
         * @param[out] : objSatelliteIds    卫星ID数组
         * @param[out] : objSignalIds       信号ID数组
         * @param[out] : objCellNum         单元数据数组
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 DecodeMsmHead(const UINT8* const pDataBuf,
                            const IGnssDataInterface::SatelliteSystem enSatSystem,
                            SEpochSatObs& stEpochSatObs,
                            UINT32& ui32Index,
                            UINT32& ui32SatelliteNum,
                            UINT32& ui32SignalNum,
                            UINT32& ui32CellNum,
                            UINT64& ui64CellLength,
                            std::array< UINT32, common::rtcm::MAX_SATELLITE_NUM >& objSatelliteIds,
                            std::array< UINT32, common::rtcm::MAX_SIGNAL_NUM >& objSignalIds,
                            std::array< UINT32, common::rtcm::MAX_CELL_NUM >& objCellNum);

        /**
         * @brief       解析1004电文类型的头数据
         * @author      pengshupan
         * @param[in]   pDataBuf           电文二进制数据
         * @param[out]  stEpochSatObs      GPS观测值结构体
         * @param[out]  nsat               GPS卫星数量
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 DecodeHead1004(const UINT8* const pDataBuf, SEpochSatObs& stEpochSatObs, UINT32& nsat);

        /**
         * @brief       解析1012电文类型的头数据
         * @author      pengshupan
         * @param[in]   pDataBuf           电文二进制数据
         * @param[out]  stEpochSatObs      GLONASS观测值结构体
         * @param[out]  nsat               GLONASS卫星数量
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 DecodeHead1012(const UINT8* const pDataBuf, SEpochSatObs& stEpochSatObs, UINT32& nsat);

        /**
         * @brief      : 解析MSM4电文类型的卫星数据
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pDataBuf           电文二进制数据
         * @param[in]  : ui32SatelliteNum   卫星数量
         * @param[in]  : objSatelliteIds    卫星ID数组
         * @param[out] : stEpochSatObs      解析电文成功后得到的观测值结构体
         * @param[out] : ui32Index           当前电文解析偏移量
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 DecodeMsm4SatData(const UINT8* const pDataBuf,
                                SEpochSatObs& stEpochSatObs,
                                UINT32& ui32Index,
                                const UINT32& ui32SatelliteNum,
                                const std::array< UINT32, common::rtcm::MAX_SATELLITE_NUM >& objSatelliteIds);

        /**
         * @brief      : 解析MSM4电文类型的信号数据
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pDataBuf          电文二进制数据
         * @param[in]  : ui32Index          当前电文解析偏移量
         * @param[in]  : ui32SignalNum     信号数量
         * @param[in]  : ui32CellNum       单元数量
         * @param[in]  : ui64CellLength    单元数据长度
         * @param[in]  : objSatelliteIds   卫星ID数组
         * @param[in]  : objSignalIds      信号ID数组
         * @param[in]  : objCellNum        单元数据数组
         * @param[out] : stEpochSatObs     解析电文成功后得到的观测值结构体
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 DecodeMsm4SigData(const UINT8* const pDataBuf,
                                SEpochSatObs& stEpochSatObs,
                                const UINT32& ui32Index,
                                const UINT32& ui32SignalNum,
                                const UINT32& ui32CellNum,
                                const UINT64& ui64CellLength,
                                const std::array< UINT32, common::rtcm::MAX_SATELLITE_NUM >& objSatelliteIds,
                                const std::array< UINT32, common::rtcm::MAX_SIGNAL_NUM >& objSignalIds,
                                const std::array< UINT32, common::rtcm::MAX_CELL_NUM >& objCellNum);

        /**
         * @brief      : 解析MSM7电文类型的卫星数据
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pDataBuf           电文二进制数据
         * @param[in]  : ui32SatelliteNum   卫星数量
         * @param[in]  : objSatelliteIds    卫星ID数组
         * @param[out] : stEpochSatObs      解析电文成功后得到的观测值结构体
         * @param[out] : ui32Index           当前电文解析偏移量
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 DecodeMsm7SatData(const UINT8* const pDataBuf,
                                SEpochSatObs& stEpochSatObs,
                                UINT32& ui32Index,
                                const UINT32& ui32SatelliteNum,
                                const std::array< UINT32, common::rtcm::MAX_SATELLITE_NUM >& objSatelliteIds);

        /**
         * @brief      : 解析MSM7电文类型的信号数据
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pDataBuf           电文二进制数据
         * @param[in]  : ui32Index           当前电文解析偏移量
         * @param[in]  : ui32SignalNum      信号数量
         * @param[in]  : ui32CellNum        单元数量
         * @param[in]  : ui64CellLength     单元数据长度
         * @param[in]  : objSatelliteIds    卫星ID数组
         * @param[in]  : objSignalIds       信号ID数组
         * @param[in]  : objCellNum         单元数据数组
         * @param[out] : stEpochSatObs      解析电文成功后得到的观测值结构体
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note       : N/A
         */
        INT32 DecodeMsm7SigData(const UINT8* const pDataBuf,
                                SEpochSatObs& stEpochSatObs,
                                const UINT32& ui32Index,
                                const UINT32& ui32SignalNum,
                                const UINT32& ui32CellNum,
                                const UINT64& ui64CellLength,
                                const std::array< UINT32, common::rtcm::MAX_SATELLITE_NUM >& objSatelliteIds,
                                const std::array< UINT32, common::rtcm::MAX_SIGNAL_NUM >& objSignalIds,
                                const std::array< UINT32, common::rtcm::MAX_CELL_NUM >& objCellNum);

        /**
         * @brief       解析SSR1电文类型数据
         * @author      pengshupan
         * @param[in]   enSatSystemconst      电文所属卫星系统
         * @param[out]  sOrbitCorrection      卫星轨道结构体
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 DecodeSSR1(const UINT8* const pDataBuf,
                         const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                         SOrbitCorrection& sOrbitCorrection);

        /**
         * @brief       解析SSR2电文类型数据
         * @author      pengshupan
         * @param[in]   enSatSystemconst      电文所属卫星系统
         * @param[out]  sClockCorrection      卫星钟差结构体
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 DecodeSSR2(const UINT8* const pDataBuf,
                         const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                         SClockCorrection& sClockCorrection);

        /**
         * @brief       解析SSR4电文类型数据
         * @author      pengshupan
         * @param[in]   enSatSystemconst           电文所属卫星系统
         * @param[out]  sOrbitClockCorrection      卫星轨道钟差结构体
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 DecodeSSR4(const UINT8* const pDataBuf,
                         const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                         SOrbitClockCorrection& sOrbitClockCorrection);

        /**
         * @brief       解析SSR1电文类型头的数据
         * @author      pengshupan
         * @param[in]   enSatSystemconst           电文所属卫星系统
         * @param[out]  sOrbitCorrection           卫星轨道结构体
         * @param[out]  ui32Offset                  电文偏移量
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 DecodeSSR1Head(const UINT8* const pDataBuf,
                             const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                             SOrbitCorrection& sOrbitCorrection,
                             UINT32& ui32Offset);
        /**
         * @brief       解析SSR2电文类型头的数据
         * @author      pengshupan
         * @param[in]   enSatSystemconst           电文所属卫星系统
         * @param[out]  sClockCorrection           卫星钟差结构体
         * @param[out]  ui32Offset                  电文偏移量
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 DecodeSSR2Head(const UINT8* const pDataBuf,
                             const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                             SClockCorrection& sClockCorrection,
                             UINT32& ui32Offset);

        /**
         * @brief       解析SSR4电文类型头的数据
         * @author      pengshupan
         * @param[in]   enSatSystemconst           电文所属卫星系统
         * @param[out]  stOrbitClockCorrection     卫星轨道钟差结构体
         * @param[out]  ui32Offset                  电文偏移量
         * @exception   N/A
         * @return      INT32
         * @retval
         *  <em>0</em>   表示解析电文成功
         *  <em>非0</em> 表示解析电文失败错误码
         * @note        N/A
         */
        INT32 DecodeSSR4Head(const UINT8* const pDataBuf,
                             const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                             SOrbitClockCorrection& sOrbitClockCorrection,
                             UINT32& ui32Offset);

        /**
         * @brief      : 获取电文数据长度（单位字节）
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : pDataBuf    电文二进制数据
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : UINT32
         * @retval     :
         *  <em>0</em>   表示获取电文数据长度失败
         *  <em>非0</em> 表示获取电文数据的长度
         * @note       : N/A
         */
        static UINT32 GetMsgLength(const UINT8* const pDataBuf);

        /**
         * @brief      : 获取GNSS数据对象
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : enSatSystem   数据所属卫星系统
         * @param[in]  : enDataType    获取数据的类型
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : IGnssDataInterface*
         * @retval     :
         *  <em>nullptr</em>   表示获取GNSS数据对象失败
         *  <em>非nullptr</em> 表示获取GNSS数据对象成功，返回对象地址
         * @note       : N/A
         */
        IGnssDataInterface* GetGnssData(const IGnssDataInterface::SatelliteSystem enSatSystem,
                                        const IGnssDataInterface::GnssDataType enDataType);

        /**
         * @brief      : 初始化字符串流
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : strHead  初始化字符串流的头
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitStrStream(const string& strHead);

        /**
         * @brief      : 将参考站数据结构体填入到参考站对象中，并存入到输出参数中
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : objData        参考站数据结构体
         * @param[in]  : enSatSystem    所属卫星系统
         * @param[out] : objStrStream   打印信息字符串流
         * @param[out] : pamOut         输出参数，包含参考站对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示方法执行成功
         *  <em>非0</em> 表示方法执行失败
         * @note       : N/A
         */
        INT32 FillDecodeResult(const SReferenceInfo& objData,
                               const IGnssDataInterface::SatelliteSystem enSatSystem,
                               const IGnssDataInterface::GnssDataType enDataType,
                               std::stringstream& objStrStream,
                               CParam& pamOut);

        /**
         * @brief      : 将轨道改正参数数据结构体填入到轨道改正参数对象中，并存入到输出参数中
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : objData        轨道改正参数数据结构体
         * @param[in]  : enSatSystem    所属卫星系统
         * @param[out] : objStrStream   打印信息字符串流
         * @param[out] : pamOut         输出参数，包含轨道改正参数对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示方法执行成功
         *  <em>非0</em> 表示方法执行失败
         * @note       : N/A
         */
        INT32 FillDecodeResult(const SOrbitCorrection& objData,
                               const IGnssDataInterface::SatelliteSystem enSatSystem,
                               const IGnssDataInterface::GnssDataType enDataType,
                               std::stringstream& objStrStream,
                               CParam& pamOut);

        /**
         * @brief      : 将钟差改正参数数据结构体填入到钟差改正参数对象中，并存入到输出参数中
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : objData        钟差改正参数数据结构体
         * @param[in]  : enSatSystem    所属卫星系统
         * @param[out] : objStrStream   打印信息字符串流
         * @param[out] : pamOut         输出参数，包含钟差改正参数对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示方法执行成功
         *  <em>非0</em> 表示方法执行失败
         * @note       : N/A
         */
        INT32 FillDecodeResult(const SClockCorrection& objData,
                               const IGnssDataInterface::SatelliteSystem enSatSystem,
                               const IGnssDataInterface::GnssDataType enDataType,
                               std::stringstream& objStrStream,
                               CParam& pamOut);

        /**
         * @brief      : 将轨道钟差改正参数数据结构体填入到轨道钟差改正参数对象中，并存入到输出参数中
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : objData        轨道钟差改正参数数据结构体
         * @param[in]  : enSatSystem    所属卫星系统
         * @param[out] : objStrStream   打印信息字符串流
         * @param[out] : pamOut         输出参数，包含钟差改正参数对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示方法执行成功
         *  <em>非0</em> 表示方法执行失败
         * @note       : N/A
         */
        INT32 FillDecodeResult(const SOrbitClockCorrection& objData,
                               const IGnssDataInterface::SatelliteSystem enSatSystem,
                               const IGnssDataInterface::GnssDataType enDataType,
                               std::stringstream& objStrStream,
                               CParam& pamOut);

        /**
         * @brief      : 将DCB数据结构体填入到DCB对象中，并存入到输出参数中
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : objData        DCB数据结构体
         * @param[in]  : enSatSystem    所属卫星系统
         * @param[out] : objStrStream   打印信息字符串流
         * @param[out] : pamOut         输出参数，包含DCB对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示方法执行成功
         *  <em>非0</em> 表示方法执行失败
         * @note       : N/A
         */
        INT32 FillDecodeResult(const SDcb& objData,
                               const IGnssDataInterface::SatelliteSystem enSatSystem,
                               const IGnssDataInterface::GnssDataType enDataType,
                               std::stringstream& objStrStream,
                               CParam& pamOut);

        /**
         * @brief      : 将URA数据结构体填入到DCB对象中，并存入到输出参数中
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : objData        URA数据结构体
         * @param[in]  : enSatSystem    所属卫星系统
         * @param[out] : objStrStream   打印信息字符串流
         * @param[out] : pamOut         输出参数，包含URA对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示方法执行成功
         *  <em>非0</em> 表示方法执行失败
         * @note       : N/A
         */
        INT32 FillDecodeResult(const SUra& objData,
                               const IGnssDataInterface::SatelliteSystem enSatSystem,
                               const IGnssDataInterface::GnssDataType enDataType,
                               std::stringstream& objStrStream,
                               CParam& pamOut);

        /**
         * @brief      : 将观测值数据结构体填入到观测值对象中，并存入到输出参数中
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : objData        观测值数据结构体
         * @param[in]  : enSatSystem    所属卫星系统
         * @param[out] : objStrStream   打印信息字符串流
         * @param[out] : pamOut         输出参数，包含观测值对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示方法执行成功
         *  <em>非0</em> 表示方法执行失败
         * @note       : N/A
         */
        INT32 FillDecodeResult(const SEpochSatObs& objData,
                               const IGnssDataInterface::SatelliteSystem enSatSystem,
                               const IGnssDataInterface::GnssDataType enDataType,
                               std::stringstream& objStrStream,
                               CParam& pamOut);

        /**
         * @brief      : 将星历数据结构体填入到星历对象中，并存入到输出参数中
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : objData        星历数据结构体
         * @param[in]  : enSatSystem    所属卫星系统
         * @param[out] : objStrStream   打印信息字符串流
         * @param[out] : pamOut         输出参数，包含星历对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示方法执行成功
         *  <em>非0</em> 表示方法执行失败
         * @note       : N/A
         */
        INT32 FillDecodeResult(const SEphemeris& objData,
                               const IGnssDataInterface::SatelliteSystem enSatSystem,
                               const IGnssDataInterface::GnssDataType enDataType,
                               std::stringstream& objStrStream,
                               CParam& pamOut);

        /**
         * @brief      : 将Glonass星历数据结构体填入到Glonass星历对象中，并存入到输出参数中
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : objData        Glonass星历数据结构体
         * @param[in]  : enSatSystem    所属卫星系统
         * @param[out] : objStrStream   打印信息字符串流
         * @param[out] : pamOut         输出参数，包含Glonass星历对象
         * @exception  : N/A
         * @return     : INT32
         * @retval     :
         *  <em>0</em>   表示方法执行成功
         *  <em>非0</em> 表示方法执行失败
         * @note       : N/A
         */
        INT32 FillDecodeResult(const SGlonassEphemeris& objData,
                               const IGnssDataInterface::SatelliteSystem enSatSystem,
                               const IGnssDataInterface::GnssDataType enDataType,
                               std::stringstream& objStrStream,
                               CParam& pamOut);

    private:
        static const std::map< UINT32, std::function< INT32(CRtcmDecoder&, CParam&, CParam&) > >& GetMsgMap();
        std::map< INT32, IGnssDataInterface* > m_mapGnssDatas;
        std::mutex m_objMutex;
        CLog* m_pobjLog;
        std::stringstream m_objStrStream;
    };

} // namespace sixents

#ifdef UNIT_TEST
#undef private
#undef protected
#define private private
#define protected protected
#endif

#endif // _CRTCM_DECODER_H_
