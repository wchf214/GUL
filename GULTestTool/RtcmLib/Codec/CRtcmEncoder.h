/**
 * @copyright Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd.
 *       All rights reserved.
 * @file    CRtcmEncoder.h
 * @author  yangchenyi/yangchengyi@sixents.com
 * @version 1.0
 * @date    2019-12-23
 * @brief   编码类
 * @details 参照RTCM STANDARD 10403.3编码电文
 *
 * @note
 *    change history:
 *    <2019-12-23>  | 1.0 | yangchenyi | 创建初始版本
 */

#ifndef _CRTCM_ENCODER_H_
#define _CRTCM_ENCODER_H_

#include <functional>
#include <sstream>
#include "ICodecOpt.h"

#ifdef UNIT_TEST
#undef private
#define private public
#endif

namespace sixents
{
    class CLog;

    /**
     * @class   CRtcmEncoder
     * @brief   编码类
     * @author  yangchengyi
     * @note    参照RTCM STANDARD 10403.3解码电文
     */
    class CRtcmEncoder
    {
    public:
        CRtcmEncoder();
        ~CRtcmEncoder();

        /**
         * @brief      编码数据结构成电文
         * @author      yangchengyi
         * @param[in]   pamIn 传入日志对象指针和需要编码的数据结构
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值参考Constents.h中的返回值定义
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         *  RETURN_UNSUPPORTED_RTCM_MSG 暂不支持的协议
         * @note        日志对象指针和解码数据结构都需要存在，否则编码失败，目前支持的有观测值，星历，
         *              Glonass星历，参考站，轨道，钟差，Dcb和Ura类型的编码
         */
        INT32 RtcmEncode(CParam& pamIn, CParam& pamOut);

    private:
        /**
         * @brief       获取电文号
         * @author      yangchengyi
         * @param[in]   pamIn 需要获取电文号的结构指针
         * @param[out]  N/A
         * @exception   N/A
         * @return      返回电文号
         * @retval
         * @note        N/A
         */
        static UINT32 GetMsgType(CParam& pamIn);

        /**
         * @brief       GPS类型电文伪距载波数据转换
         * @author      pengshupan
         * @param[in]   L1载波数据
         * @param[in]   L2载波数据
         * @param[out]  处理后信号数据
         * @exception   N/A
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        static INT32 GenOBSGPS(SSignalValue& signal1,
                               SSignalValue& signal2,
                               SSatelliteValue& sateValue,
                               UINT32& l1PRange,
                               INT32& l1CarrierSubl1PRange,
                               INT32& l2Subl1PRange,
                               INT32& l2CarrierSubl1PRange);

        /**
         * @brief       GLONASS类型电文伪距载波数据转换
         * @author      pengshupan
         * @param[in]   L1载波数据
         * @param[in]   L2载波数据
         * @param[out]  处理后信号数据
         * @exception   N/A
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        static INT32 GenOBSGLONASS(SSignalValue& signal1,
                                   SSignalValue& signal2,
                                   SSatelliteValue& sateValue,
                                   UINT32& l1PRange,
                                   INT32& l1CarrierSubl1PRange,
                                   INT32& l2Subl1PRange,
                                   INT32& l2CarrierSubl1PRange);

        /**
         * @brief       编码1004的电文
         * @author      penghshupan
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1004(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1005的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1005(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1006的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1006(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1012的电文
         * @author      penghshupan
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1012(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1019的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEphemeris指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1019(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1020的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CGlonassEphemeris指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1020(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1033的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1033(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1042的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEphemeris指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1042(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1044的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEphemeris指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1044(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1045的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEphemeris指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1045(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1046的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEphemeris指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1046(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1057的电文
         * @author      penghshupan
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1057(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1058的电文
         * @author      penghshupan
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1058(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1059的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CDcb指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1059(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1060的电文
         * @author      penghshupan
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1060(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1061的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CUra指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1061(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1062的电文
         * @author      penghshupan
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1062(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1063的电文
         * @author      penghshupan
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1063(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1064的电文
         * @author      penghshupan
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1064(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1065的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CDcb指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1065(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1066的电文
         * @author      penghshupan
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1066(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1067的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CUra指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1067(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1068的电文
         * @author      penghshupan
         * @param[in]   pamIn 需要编码的CReferenceInfo指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1068(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1074的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEpochObs指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1074(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1077的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEpochObs指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1077(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1084的电文
         * @author      pengshupan
         * @param[in]   pamIn 需要编码的CEpochObs指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1084(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1087的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEpochObs指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1087(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1094的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEpochObs指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1094(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1097的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEpochObs指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1097(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1114的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEpochObs指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1114(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1117的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEpochObs指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1117(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1124的电文
         * @author      pengshupan
         * @param[in]   pamIn 需要编码的CEpochObs指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1124(CParam& pamIn, std::string& out);

        /**
         * @brief       编码1127的电文
         * @author      yangchengyi
         * @param[in]   pamIn 需要编码的CEpochObs指针
         * @param[out]  pamOut 输出解码后的ByteArray
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoder1127(CParam& pamIn, std::string& out);

        /**
         * @brief       编码电文头
         * @author      yangchengyi
         * @param[in]   out 编码头部需要写入的buff空间
         * @param[out]  out 填充电文头后的buff
         * @exception   N/A
         * @return      N/A
         * @retval
         * @note        会先清空buff中的内容，然后从头开始希尔电文头的前3个字节(0xD3,0x00,0x00)
         */
        static void CommonRtcmEncodeHeader(std::string& out);

        /**
         * @brief       重写电文长度
         * @author      yangchengyi
         * @param[in]   out 需要重写电文长度的buff空间
         * @param[out]  out 填充电文长度后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        如果电文长度过大会导致失败
         */
        INT32 RtcmEncodeMsgLength(std::string& out) const;

        /**
         * @brief       写入CRC校验信息
         * @author      yangchengyi
         * @param[in]   out 需要写入CRC校验信息的buff空间
         * @param[out]  out 填充CRC校验信息后的buff
         * @exception   N/A
         * @return      N/A
         * @retval
         * @note        N/A
         */
        static void RtcmEncodeCrc24(std::string& out); // 注意此方法不需要分配CRC 校验的内存 函数内部处理CRC校验的内存

        /**
         * @brief       编码MSM类型的消息的头部
         * @author      yangchengyi
         * @param[in]   obs 观测值数据
         * @param[in]   out 编码后填充的buff
         * @param[in]   pos 填充编码数据的起始位置
         * @param[in]   cells 卫星信号所对应槽的位置
         * @param[in]   bGlo 是否是Glonass的观测值数据
         * @param[out]  out 填充MSM消息头部后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 RtcmEncoderMsmHead(const SEpochSatObs& obs,
                                 string& out,
                                 UINT32& pos,
                                 std::map< INT32, INT32 >& cells,
                                 const BOOL_T bGlo) const;

        /**
         * @brief       编码MSM4类型的消息的头部
         * @author      yangchengyi
         * @param[in]   obs 观测值数据
         * @param[in]   out 编码后填充的buff
         * @param[in]   bGlo 是否是Glonass的观测值数据
         * @param[out]  out 填充MSM4消息后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 EncodeMsm4(const SEpochSatObs& obs, string& out, const BOOL_T bGlo = false);

        /**
         * @brief       编码MSM7类型的消息
         * @author      yangchengyi
         * @param[in]   obs 观测值数据
         * @param[in]   out 编码后填充的buff
         * @param[in]   bGlo 是否是Glonass的观测值数据
         * @param[out]  out 填充MSM4消息后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        INT32 EncodeMsm7(const SEpochSatObs& obs, string& out, const BOOL_T bGlo = false);

        /**
         * @brief       编码1004，1012类型的消息
         * @author      pengshupan
         * @param[in]   type 卫星电文类型
         * @param[in]   obs  观测值数据结构体
         * @param[out]  out  填充编码消息后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        static UINT32 EncodeOldObsHead(const INT32 type, const SEpochSatObs& epochObs, string& out);

        /**
         * @brief       编码SSR1类型的消息
         * @author      pengshupan
         * @param[in]   sOrbitCorrection  卫星轨道结构体
         * @param[in]   enSatSystemconst  卫星系统
         * @param[out]  out  填充编码消息后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        static INT32 EncodeSSR1(SOrbitCorrection& sOrbitCorrection,
                                const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                string& out);

        /**
         * @brief       编码SSR2类型的消息
         * @author      pengshupan
         * @param[in]   sClockCorrection  卫星钟差结构体
         * @param[in]   enSatSystemconst  卫星系统
         * @param[out]  out  填充编码消息后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        static INT32 EncodeSSR2(SClockCorrection& sClockCorrection,
                                const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                string& out);
        /**
         * @brief       编码SSR4类型的消息
         * @author      pengshupan
         * @param[in]   sOrbitClockCorrection  卫星轨道钟差结构体
         * @param[in]   enSatSystemconst  卫星系统
         * @param[out]  out  填充编码消息后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        static INT32 EncodeSSR4(SOrbitClockCorrection& sOrbitClockCorrection,
                                const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                string& out);
        /**
         * @brief       编码SSR1类型头的消息
         * @author      pengshupan
         * @param[in]   type              卫星电文类型
         * @param[in]   sOrbitCorrection  卫星轨道结构体
         * @param[in]   enSatSystemconst  卫星系统
         * @param[out]  out  填充编码消息后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        static INT32 EncodeSSR1Head(const SOrbitCorrection& sOrbitCorrection,
                                    const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                    UINT32& offset,
                                    string& out);
        /**
         * @brief       编码SSR2类型头的消息
         * @author      pengshupan
         * @param[in]   type              卫星电文类型
         * @param[in]   sClockCorrection  卫星钟差结构体
         * @param[in]   enSatSystemconst  卫星系统
         * @param[out]  out  填充编码消息后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        static INT32 EncodeSSR2Head(const SClockCorrection& sClockCorrection,
                                    const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                    UINT32& offset,
                                    string& out);

        /**
         * @brief       编码SSR4类型头的消息
         * @author      pengshupan
         * @param[in]   type                   卫星电文类型
         * @param[in]   sOrbitClockCorrection  卫星轨道钟差结构体
         * @param[in]   enSatSystemconst       卫星系统
         * @param[out]  out  填充编码消息后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  RETURN_SUCCESS  成功
         *  RETURN_FAIL     失败
         * @note        N/A
         */
        static INT32 EncodeSSR4Head(const SOrbitClockCorrection& sOrbitClockCorrection,
                                    const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                    UINT32& offset,
                                    string& out);
        /**
         * @brief       判断pGnssData是否是GnssDataType类型的数据
         * @author      yangchengyi
         * @param[in]   pGnssData GnssData的数据指针
         * @param[in]   GnssDataType GnssData的数据类型
         * @param[in]   bGlo 是否是Glonass的观测值数据
         * @param[out]  out 填充MSM4消息后的buff
         * @exception   N/A
         * @return      返回值执行成功或者失败
         * @retval
         *  true        成功
         *  false       失败
         * @note        N/A
         */
        static BOOL_T CheckGnssDataType(const IGnssDataInterface* const pGnssData,
                                        const IGnssDataInterface::GnssDataType type);

    private:
        /** 电文的对应处理函数映射关系，map<电文号, 电文处理函数> */
        static const std::map< UINT32, std::function< INT32(CRtcmEncoder&, CParam&, std::string&) > >& GetMsgMap();
        /** 写日志需要用到的指针 */
        CLog* m_pobjLog;
    };

} // namespace sixents

#endif //_CRTCM_ENCODER_H_
