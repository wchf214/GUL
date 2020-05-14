#include "CRtcmEncoder.h"
#include <cmath>
#include <map>
#include "../Framework/CLog.h"
#include "CCodecUtilities.h"

namespace sixents
{
    using namespace std;
    using namespace sixents::common::rtcm;
    const map< UINT32, std::function< INT32(CRtcmEncoder&, CParam&, std::string&) > >& CRtcmEncoder::GetMsgMap()
    {
        static const map< UINT32, std::function< INT32(CRtcmEncoder&, CParam&, std::string&) > > mapMsg = {
            {MSG_1004, &CRtcmEncoder::RtcmEncoder1004}, {MSG_1005, &CRtcmEncoder::RtcmEncoder1005},
            {MSG_1006, &CRtcmEncoder::RtcmEncoder1006}, {MSG_1012, &CRtcmEncoder::RtcmEncoder1012},
            {MSG_1019, &CRtcmEncoder::RtcmEncoder1019}, {MSG_1020, &CRtcmEncoder::RtcmEncoder1020},
            {MSG_1033, &CRtcmEncoder::RtcmEncoder1033}, {MSG_1042, &CRtcmEncoder::RtcmEncoder1042},
            {MSG_1044, &CRtcmEncoder::RtcmEncoder1044}, {MSG_1045, &CRtcmEncoder::RtcmEncoder1045},
            {MSG_1046, &CRtcmEncoder::RtcmEncoder1046}, {MSG_1057, &CRtcmEncoder::RtcmEncoder1057},
            {MSG_1058, &CRtcmEncoder::RtcmEncoder1058}, {MSG_1059, &CRtcmEncoder::RtcmEncoder1059},
            {MSG_1060, &CRtcmEncoder::RtcmEncoder1060}, {MSG_1061, &CRtcmEncoder::RtcmEncoder1061},
            {MSG_1062, &CRtcmEncoder::RtcmEncoder1062}, {MSG_1063, &CRtcmEncoder::RtcmEncoder1063},
            {MSG_1064, &CRtcmEncoder::RtcmEncoder1064}, {MSG_1065, &CRtcmEncoder::RtcmEncoder1065},
            {MSG_1066, &CRtcmEncoder::RtcmEncoder1066}, {MSG_1067, &CRtcmEncoder::RtcmEncoder1067},
            {MSG_1068, &CRtcmEncoder::RtcmEncoder1068}, {MSG_1074, &CRtcmEncoder::RtcmEncoder1074},
            {MSG_1077, &CRtcmEncoder::RtcmEncoder1077}, {MSG_1084, &CRtcmEncoder::RtcmEncoder1084},
            {MSG_1087, &CRtcmEncoder::RtcmEncoder1087}, {MSG_1094, &CRtcmEncoder::RtcmEncoder1094},
            {MSG_1097, &CRtcmEncoder::RtcmEncoder1097}, {MSG_1114, &CRtcmEncoder::RtcmEncoder1114},
            {MSG_1117, &CRtcmEncoder::RtcmEncoder1117}, {MSG_1124, &CRtcmEncoder::RtcmEncoder1124},
            {MSG_1127, &CRtcmEncoder::RtcmEncoder1127}};

        return mapMsg;
    }

    CRtcmEncoder::CRtcmEncoder()
        : m_pobjLog(nullptr)
    {}

    CRtcmEncoder::~CRtcmEncoder()
    {}

    UINT32 CRtcmEncoder::GetMsgType(CParam& pamIn)
    {
        UINT32 type = MSG_UNKNOWN;

        IGnssDataInterface* pPointer = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pPointer, nullptr) && (pPointer != nullptr))
        {
            const IGnssDataInterface::GnssDataType dataType = pPointer->GetGnssDataType();
            switch (dataType)
            {
                case sixents::IGnssDataInterface::GDT_OBS:
                {
                    CEpochObs* const ptrGnssData = dynamic_cast< CEpochObs* const >(pPointer);
                    if (ptrGnssData != nullptr)
                    {
                        type = ptrGnssData->GetEpochSatObs().m_ui16MsgType;
                    }
                }
                break;
                case sixents::IGnssDataInterface::GDT_EPH:
                {
                    CEphemeris* const ptrGnssData = dynamic_cast< CEphemeris* const >(pPointer);
                    if (ptrGnssData != nullptr)
                    {
                        type = ptrGnssData->GetEphemeris().m_ui16MsgType;
                    }
                }
                break;
                case sixents::IGnssDataInterface::GDT_GLO_EPH:
                {
                    CGlonassEphemeris* const ptrGnssData = dynamic_cast< CGlonassEphemeris* const >(pPointer);
                    if (ptrGnssData != nullptr)
                    {
                        type = ptrGnssData->GetGlonassEphemeris().m_ui16MsgType;
                    }
                }
                break;
                case sixents::IGnssDataInterface::GDT_REF_INFO:
                {
                    CReferenceInfo* const ptrGnssData = dynamic_cast< CReferenceInfo* const >(pPointer);
                    if (ptrGnssData != nullptr)
                    {
                        type = ptrGnssData->GetReferenceInfo().m_ui16MsgType;
                    }
                }
                break;
                case sixents::IGnssDataInterface::GDT_ORBIT:
                {
                    COrbitCorrection* const ptrGnssData = dynamic_cast< COrbitCorrection* const >(pPointer);
                    if (ptrGnssData != nullptr)
                    {
                        type = ptrGnssData->GetOrbitCorrection().m_ui16MsgType;
                    }
                }
                break;
                case sixents::IGnssDataInterface::GDT_CLOCK:
                {
                    CClockCorrection* const ptrGnssData = dynamic_cast< CClockCorrection* const >(pPointer);
                    if (ptrGnssData != nullptr)
                    {
                        type = ptrGnssData->GetClockCorrection().m_ui16MsgType;
                    }
                }
                break;
                case sixents::IGnssDataInterface::GDT_ORBIT_CLOCK:
                {
                    COrbitClockCorrection* const ptrGnssData = dynamic_cast< COrbitClockCorrection* const >(pPointer);
                    if (ptrGnssData != nullptr)
                    {
                        type = ptrGnssData->GetOrbitClockCorrection().m_ui16MsgType;
                    }
                }
                break;
                case sixents::IGnssDataInterface::GDT_DCB:
                {
                    CDcb* const ptrGnssData = dynamic_cast< CDcb* const >(pPointer);
                    if (ptrGnssData != nullptr)
                    {
                        type = ptrGnssData->GetDcb().m_ui16MsgType;
                    }
                }
                break;
                case sixents::IGnssDataInterface::GDT_URA:
                {
                    CUra* const ptrGnssData = dynamic_cast< CUra* const >(pPointer);
                    if (ptrGnssData != nullptr)
                    {
                        type = ptrGnssData->GetUra().m_ui16MsgType;
                    }
                }
                break;
                case sixents::IGnssDataInterface::GDT_UNKNOW:
                {
                    // Do nothing
                }
                break;
                default:
                {
                    // Do nothing
                }
                break;
            }
        }
        return type;
    }

    INT32 CRtcmEncoder::RtcmEncode(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            if (m_pobjLog == nullptr)
            {
                if (!pamIn.GetValue(PN_PTR_LOG_OBJECT, &m_pobjLog, nullptr) || m_pobjLog == nullptr)
                {
                    i32RetCode = RETURN_INVALID_PARAMETER;
                    break;
                }
            }

            const UINT32 msgType = GetMsgType(pamIn);
            if (msgType == MSG_UNKNOWN)
            {
                m_pobjLog->Trace("No msg type found.", CLog::LL_ERROR);
                i32RetCode = RETURN_UNSUPPORTED_RTCM_MSG;
                break;
            }

            string buff("");
            CommonRtcmEncodeHeader(buff); // 写入包头

            const auto iter = GetMsgMap().find(msgType);
            if (iter == GetMsgMap().end())
            {
                m_pobjLog->Trace("No msg callback found:" + std::to_string(msgType), CLog::LL_ERROR);
                i32RetCode = RETURN_UNSUPPORTED_RTCM_MSG;
                break;
            }

            m_pobjLog->Trace("Start to encode msg:" + std::to_string(msgType), CLog::LL_INFO);
            INT32 i32Ret = iter->second(*this, pamIn, buff);
            if (i32Ret != RETURN_SUCCESS || buff.empty())
            {
                m_pobjLog->Trace("Encode msg failed:" + std::to_string(msgType), CLog::LL_ERROR);
                i32RetCode = i32Ret;
                break;
            }

            m_pobjLog->Trace("Finish encode msg:" + std::to_string(msgType), CLog::LL_INFO);

            i32Ret = RtcmEncodeMsgLength(buff);
            if (i32Ret != RETURN_SUCCESS)
            {
                m_pobjLog->Trace("Encode msg length failed:" + std::to_string(msgType), CLog::LL_ERROR);
                i32RetCode = i32Ret;
                break;
            }

            RtcmEncodeCrc24(buff);

            PVOID const pvValue = reinterpret_cast< PVOID >(&buff[0U]);
            if (pamOut.AddValue(
                    common::rtcm::PN_BA_MESSAGE_DATA, PDT_BYTE_ARRAY, pvValue, reinterpret_cast< PVOID >(buff.length()))
                == false)
            {
                m_pobjLog->Trace("Encode msg failed:" + std::to_string(msgType), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    void CRtcmEncoder::CommonRtcmEncodeHeader(std::string& strOut)
    {
        // 清空缓存 然后重新分配内存
        strOut.clear();
        UINT32 ui32Pos = 0U; // 包头从第一个字节开始写入
        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
            strOut, ui32Pos, MSG_HEAD_PROTOCOL_LENGTH, static_cast< UINT32 >(RTCM32_PREABLE));
        ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, MSG_HEAD_RESERVED_LENGTH, ZERO);
        ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, MSG_DATA_LENGTH, ZERO);
    }

    void CRtcmEncoder::RtcmEncodeCrc24(std::string& strOut)
    {
        const UINT32 crc = CCodecUtilities::RtkCrc24q(strOut);
        const UINT32 ui32Pos = static_cast< UINT32 >(strOut.length() * BYTE_TO_BIT_COUNT);
        // 填充CRC 校验信息
        CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, CRC24_DATA_LENGTH * BYTE_TO_BIT_COUNT, crc);
    }

    INT32 CRtcmEncoder::RtcmEncodeMsgLength(std::string& strOut) const
    {
        if (static_cast< UINT32 >(strOut.length()) > (MSG_HEAD_BYTE_LENGTH + MSG_MAX_LENGTH))
        {
            if (m_pobjLog != nullptr)
            {
                m_pobjLog->Trace("Msg length too long.", CLog::LL_ERROR);
            }

            return RETURN_FAIL;
        }

        const UINT32 ui32Pos = MSG_DATA_LENGTH_START_INDEX;
        // 更新包长度
        CCodecUtilities::SetUnsignedIntBit(
            strOut, ui32Pos, MSG_DATA_LENGTH, static_cast< UINT32 >(strOut.length()) - MSG_HEAD_BYTE_LENGTH);

        return RETURN_SUCCESS;
    }

    INT32 CRtcmEncoder::RtcmEncoderMsmHead(const SEpochSatObs& obs,
                                           string& strOut,
                                           UINT32& ui32Pos,
                                           std::map< INT32, INT32 >& cells,
                                           const BOOL_T bGlo) const
    {
        /* encode msm header (ref [15] table 3.5-78) */
        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
            strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(obs.m_ui16MsgType)); // message number

        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
            strOut, ui32Pos, DATA_LENGTH_12, obs.m_ui32GmNtiRefStationID); // reference station id
        if (bGlo)
        {
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_3, static_cast< UINT32 >(obs.m_ui8DayOfWeek)); // epoch time
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_27, static_cast< UINT32 >(obs.m_ui32GnssEpochTime)); // epoch time
        }
        else
        {
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_30, static_cast< UINT32 >(obs.m_ui32GnssEpochTime)); // epoch time
        }

        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
            strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(obs.m_ui8MultiMsgBit)); // multiple message bit
        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
            strOut, ui32Pos, DATA_LENGTH_3, static_cast< UINT32 >(obs.m_ui8IODS)); // issue of data station
        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
            strOut, ui32Pos, DATA_LENGTH_7, static_cast< UINT32 >(obs.m_i8Reserved)); // reserved
        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
            strOut,
            ui32Pos,
            DATA_LENGTH_2,
            static_cast< UINT32 >(obs.m_ui8ClockSteeringIndicator)); // clock streering indicator
        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
            strOut,
            ui32Pos,
            DATA_LENGTH_2,
            static_cast< UINT32 >(obs.m_ui8ExternalClockIndicator)); // external clock indicator
        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
            strOut,
            ui32Pos,
            DATA_LENGTH_1,
            static_cast< UINT32 >(obs.m_ui8GnssSmoothingIndicator)); // smoothing indicator
        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
            strOut,
            ui32Pos,
            DATA_LENGTH_3,
            static_cast< UINT32 >(obs.m_ui8GnssSmoothingInterval)); // smoothing interval

        /* satellite mask                       */
        for (INT32 i = 1; i <= static_cast< INT32 >(DATA_LENGTH_64); ++i)
        {
            // 有对应卫星的数据就设置标志位
            if (obs.m_mapSatValues.find(i) != obs.m_mapSatValues.end())
            {
                ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_1, ONE);
            }
            else
            {
                ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_1, ZERO);
            }
        }

        /* signal mask */
        std::array< BOOL_T, DATA_LENGTH_32 > mask{};
        mask.fill(false);
        for (auto& sat : obs.m_mapSatValues)
        {
            for (auto& signal : sat.second.m_mapSignalValues)
            {
                if (signal.first >= DATA_LENGTH_1 && signal.first <= static_cast< INT32 >(DATA_LENGTH_32))
                {
                    const UINT32 ui32Index = static_cast< UINT32 >(signal.first) - DATA_LENGTH_1;
                    if (DATA_LENGTH_32 > ui32Index)
                    {
                        mask[static_cast< std::size_t >(ui32Index)] = true;
                    }
                }
            }
        }
        for (UINT32 i = 0U; i < DATA_LENGTH_32; ++i)
        {
            UINT32 ui32MaskValue = ZERO;
            if (mask[static_cast< std::size_t >(i)] == true)
            {
                ui32MaskValue = ONE;
                cells.insert(make_pair(cells.size(), i + DATA_LENGTH_1));
            }

            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_1, ui32MaskValue);
        }

        auto SatMulSignalSize = obs.m_mapSatValues.size() * cells.size();
        if (SatMulSignalSize > DATA_LENGTH_64)
        {
            if (m_pobjLog != nullptr)
            {
                m_pobjLog->Trace("Cells is out of range:" + to_string(SatMulSignalSize), CLog::LL_ERROR);
            }
            return RETURN_FAIL;
        }

        /* cell mask */
        const INT32 i32CellNum = static_cast< INT32 >(cells.size());
        for (auto& sat : obs.m_mapSatValues)
        {
            for (INT32 i = 0; i < i32CellNum; ++i)
            {
                auto item = cells.find(i);
                if ((item != cells.end())
                    && sat.second.m_mapSignalValues.find(cells[i]) != sat.second.m_mapSignalValues.end())
                {
                    ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_1, ONE);
                }
                else
                {
                    ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_1, ZERO);
                }
            }
        }
        return RETURN_SUCCESS;
    }

    INT32 CRtcmEncoder::EncodeMsm4(const SEpochSatObs& obs, string& strOut, const BOOL_T bGlo)
    {
        INT32 iRet = RETURN_FAIL;
        UINT32 ui32Pos = MSG_HEAD_LENGTH; // 跳过消息包头
        std::map< INT32, INT32 > cells;
        if (RtcmEncoderMsmHead(obs, strOut, ui32Pos, cells, bGlo) == RETURN_SUCCESS)
        {
            /* encode msm satellite data */
            ui32Pos = CCodecUtilities::EncodeMsmIntRrng(obs, ui32Pos, strOut); /* rough range integer ms */
            ui32Pos = CCodecUtilities::EncodeMsmModRrng(obs, ui32Pos, strOut); /* rough range modulo 1 ms */

            /* encode msm signal data */
            ui32Pos = CCodecUtilities::EncodeMsmPsrng(obs, ui32Pos, cells, strOut);   /* fine pseudorange */
            ui32Pos = CCodecUtilities::EncodeMsmPhrng(obs, ui32Pos, cells, strOut);   /* fine phase-range */
            ui32Pos = CCodecUtilities::EncodeMsmLock(obs, ui32Pos, cells, strOut);    /* lock-time indicator */
            ui32Pos = CCodecUtilities::EncodeMsmHalfAmb(obs, ui32Pos, cells, strOut); /* half-cycle-amb indicator */
            ui32Pos = CCodecUtilities::EncodeMsmCnr(obs, ui32Pos, cells, strOut);     /* signal cnr */
            iRet = RETURN_SUCCESS;
        }

        return iRet;
    }

    INT32 CRtcmEncoder::EncodeMsm7(const SEpochSatObs& obs, string& strOut, const BOOL_T bGlo)
    {
        INT32 iRet = RETURN_FAIL;
        UINT32 ui32Pos = MSG_HEAD_LENGTH; // 跳过消息包头
        std::map< INT32, INT32 > cells;
        if (RtcmEncoderMsmHead(obs, strOut, ui32Pos, cells, bGlo) == RETURN_SUCCESS)
        {
            /* encode msm satellite data */
            ui32Pos = CCodecUtilities::EncodeMsmIntRrng(obs, ui32Pos, strOut);   /* rough range integer ms */
            ui32Pos = CCodecUtilities::EncodeMsmSatExInfo(obs, ui32Pos, strOut); /* extended satellite info */
            ui32Pos = CCodecUtilities::EncodeMsmModRrng(obs, ui32Pos, strOut);   /* rough range modulo 1 ms */
            ui32Pos = CCodecUtilities::EncodeMsmRrate(obs, ui32Pos, strOut);     /* rough phase-range-rate */

            /* encode msm signal data */
            ui32Pos = CCodecUtilities::EncodeMsmPsrngEx(obs, ui32Pos, cells, strOut); /* fine pseudorange ext */
            ui32Pos = CCodecUtilities::EncodeMsmPhrngEx(obs, ui32Pos, cells, strOut); /* fine phase-range ext */
            ui32Pos = CCodecUtilities::EncodeMsmLockEx(obs, ui32Pos, cells, strOut);  /* lock-time indicator ext */
            ui32Pos = CCodecUtilities::EncodeMsmHalfAmb(obs, ui32Pos, cells, strOut); /* half-cycle-amb indicator */
            ui32Pos = CCodecUtilities::EncodeMsmCnrEx(obs, ui32Pos, cells, strOut);   /* signal cnr ext */
            ui32Pos = CCodecUtilities::EncodeMsmRate(obs, ui32Pos, cells, strOut);    /* fine phase-range-rate */
            iRet = RETURN_SUCCESS;
        }
        return iRet;
    }

    INT32 CRtcmEncoder::GenOBSGPS(SSignalValue& signal1,
                                  SSignalValue& signal2,
                                  SSatelliteValue& sateValue,
                                  UINT32& l1PRange,
                                  INT32& l1CarrierSubl1PRange,
                                  INT32& l2Subl1PRange,
                                  INT32& l2CarrierSubl1PRange)
    {

        INT32 iRet = RETURN_FAIL;
        do
        {
            //重建的L1伪距
            DOUBLE RealL1Range = 0.0;

            if (CCodecUtilities::DoubleEqualToZero(signal1.m_dbPseudoranges) != true)
            {
                sateValue.m_ui8Milliseconds = static_cast< UINT8 >(floor(signal1.m_dbPseudoranges / PRUNIT_GPS));

                l1PRange = static_cast< UINT32 >(std::round(
                    (signal1.m_dbPseudoranges - static_cast< DOUBLE >(sateValue.m_ui8Milliseconds) * PRUNIT_GPS)
                    / SCALE_DF011));

                RealL1Range = static_cast< DOUBLE >(l1PRange) * SCALE_DF011
                              + static_cast< DOUBLE >(sateValue.m_ui8Milliseconds) * PRUNIT_GPS;
            }

            if ((CCodecUtilities::DoubleEqualToZero(signal1.m_dbPseudoranges) != true)
                && (CCodecUtilities::DoubleEqualToZero(signal1.m_dbPhaserange) != true))
            {
                if (l1CarrierSubl1PRange != 0)
                {
                    l1CarrierSubl1PRange =
                        static_cast< INT32 >(std::round((signal1.m_dbPhaserange - RealL1Range) / SCALE_DF012));
                }
            }

            if ((CCodecUtilities::DoubleEqualToZero(signal1.m_dbPseudoranges) != true)
                && (CCodecUtilities::DoubleEqualToZero(signal2.m_dbPseudoranges) != true)
                && (fabs(signal2.m_dbPseudoranges - RealL1Range) <= L2subL1pseudorange))
            {

                if (CCodecUtilities::DoubleEqualToZero(l2Subl1PRange) != true)
                {
                    l2Subl1PRange =
                        static_cast< INT32 >(std::round((signal2.m_dbPseudoranges - RealL1Range) / SCALE_DF017));
                }
            }

            if ((CCodecUtilities::DoubleEqualToZero(signal1.m_dbPseudoranges) != true)
                && (CCodecUtilities::DoubleEqualToZero(signal2.m_dbPhaserange) != true))
            {
                if (CCodecUtilities::DoubleEqualToZero(l2CarrierSubl1PRange) != true)
                {
                    l2CarrierSubl1PRange =
                        static_cast< INT32 >(std::round((signal2.m_dbPhaserange - RealL1Range) / SCALE_DF018));
                }
            }

            iRet = RETURN_SUCCESS;
        } while (false);

        return iRet;
    }

    INT32 CRtcmEncoder::GenOBSGLONASS(SSignalValue& signal1,
                                      SSignalValue& signal2,
                                      SSatelliteValue& sateValue,
                                      UINT32& l1PRange,
                                      INT32& l1CarrierSubl1PRange,
                                      INT32& l2Subl1PRange,
                                      INT32& l2CarrierSubl1PRange)
    {
        INT32 iRet = RETURN_FAIL;
        do
        {
            //重建的L1伪距
            DOUBLE RealL1Range = 0.0;
            if (CCodecUtilities::DoubleEqualToZero(signal1.m_dbPseudoranges) != true)
            {
                sateValue.m_ui8Milliseconds = static_cast< UINT8 >(floor(signal1.m_dbPseudoranges / PRUNIT_GLO));
                l1PRange = static_cast< UINT32 >(std::round(
                    (signal1.m_dbPseudoranges - static_cast< DOUBLE >(sateValue.m_ui8Milliseconds) * PRUNIT_GLO)
                    / SCALE_DF041));
                RealL1Range = static_cast< DOUBLE >(l1PRange) * SCALE_DF041
                              + static_cast< DOUBLE >(sateValue.m_ui8Milliseconds) * PRUNIT_GLO;
            }

            if ((CCodecUtilities::DoubleEqualToZero(signal1.m_dbPseudoranges) != true)
                && (CCodecUtilities::DoubleEqualToZero(signal1.m_dbPhaserange) != true))
            {

                if (CCodecUtilities::DoubleEqualToZero(signal1.m_dbPhaserange) != true)
                {
                    l1CarrierSubl1PRange =
                        static_cast< INT32 >(std::round((signal1.m_dbPhaserange - RealL1Range) / SCALE_DF042));
                }
            }

            if ((CCodecUtilities::DoubleEqualToZero(signal1.m_dbPseudoranges) != true)
                && (CCodecUtilities::DoubleEqualToZero(signal2.m_dbPseudoranges) != true)
                && (fabs(signal2.m_dbPseudoranges - RealL1Range) <= L2subL1pseudorange))
            {
                if (CCodecUtilities::DoubleEqualToZero(signal1.m_dbPseudoranges) != true)
                {
                    l2Subl1PRange =
                        static_cast< INT32 >(std::round((signal2.m_dbPseudoranges - RealL1Range) / SCALE_DF047));
                }
            }

            if ((CCodecUtilities::DoubleEqualToZero(signal1.m_dbPseudoranges) != true)
                && (CCodecUtilities::DoubleEqualToZero(signal2.m_dbPhaserange) != true))
            {

                if (CCodecUtilities::DoubleEqualToZero(signal2.m_dbPhaserange) != true)
                {
                    l2CarrierSubl1PRange =
                        static_cast< INT32 >(std::round((signal2.m_dbPhaserange - RealL1Range) / SCALE_DF048));
                }
            }

            iRet = RETURN_SUCCESS;
        } while (false);
        return iRet;
    }

    UINT32 CRtcmEncoder::EncodeOldObsHead(const INT32 type, const SEpochSatObs& pEpochObs, string& strOut)
    {
        UINT32 ui32Offset = MSG_HEAD_LENGTH;

        CCodecUtilities::SetUnsignedIntBit(
            strOut, ui32Offset, DATA_LENGTH_12, static_cast< UINT32 >(pEpochObs.m_ui16MsgType));
        ui32Offset += DATA_LENGTH_12;

        CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_12, pEpochObs.m_ui32GmNtiRefStationID);
        ui32Offset += DATA_LENGTH_12;

        if (type == IGnssDataInterface::SYS_GLO)
        {
            CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_27, pEpochObs.m_ui32GnssEpochTime);
            ui32Offset += DATA_LENGTH_27;
        }
        else
        {
            CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_30, pEpochObs.m_ui32GnssEpochTime);
            ui32Offset += DATA_LENGTH_30;
        }

        CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_1, pEpochObs.m_ui8MultiMsgBit);
        ui32Offset += DATA_LENGTH_1;

        CCodecUtilities::SetUnsignedIntBit(
            strOut, ui32Offset, DATA_LENGTH_5, static_cast< UINT32 >(pEpochObs.m_mapSatValues.size()));
        ui32Offset += DATA_LENGTH_5;

        CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_1, pEpochObs.m_ui8GnssSmoothingIndicator);
        ui32Offset += DATA_LENGTH_1;

        CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_3, pEpochObs.m_ui8GnssSmoothingInterval);
        ui32Offset += DATA_LENGTH_3;

        return ui32Offset;
    }

    INT32 CRtcmEncoder::EncodeSSR1(SOrbitCorrection& sOrbitCorrection,
                                   const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                   string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        do
        {
            if (enSatSystemconst != IGnssDataInterface::SYS_GPS && enSatSystemconst != IGnssDataInterface::SYS_GLO)
            {
                break;
            }

            UINT32 satNumLength = 0U;
            UINT32 IODELength = DATA_LENGTH_8;
            UINT32 ui32Offset = MSG_HEAD_LENGTH;

            if (enSatSystemconst == IGnssDataInterface::SYS_GPS)
            {
                satNumLength = DATA_LENGTH_6;
            }
            else
            {
                satNumLength = DATA_LENGTH_5;
            }

            if (EncodeSSR1Head(sOrbitCorrection, enSatSystemconst, ui32Offset, strOut) != RETURN_SUCCESS)
            {
                break;
            }

            for (auto stOrbitCorrectionInfo : sOrbitCorrection.m_mapOrbitCorrectionInfo)
            {
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, satNumLength, static_cast< UINT32 >(stOrbitCorrectionInfo.second.m_ui8SatId));
                ui32Offset += satNumLength;

                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, IODELength, static_cast< UINT32 >(stOrbitCorrectionInfo.second.m_ui8IODE));
                ui32Offset += IODELength;

                CCodecUtilities::SetIntBit(
                    strOut,
                    ui32Offset,
                    DATA_LENGTH_22,
                    static_cast< INT32 >(std::round(stOrbitCorrectionInfo.second.m_dbDeltaRadial / SCALE_DF365)));
                ui32Offset += DATA_LENGTH_22;

                CCodecUtilities::SetIntBit(
                    strOut,
                    ui32Offset,
                    DATA_LENGTH_20,
                    static_cast< INT32 >(std::round(stOrbitCorrectionInfo.second.m_dbDeltaAlongTrack / SCALE_DF366)));
                ui32Offset += DATA_LENGTH_20;

                CCodecUtilities::SetIntBit(
                    strOut,
                    ui32Offset,
                    DATA_LENGTH_20,
                    static_cast< INT32 >(std::round(stOrbitCorrectionInfo.second.m_dbDeltaCrossTrack / SCALE_DF367)));
                ui32Offset += DATA_LENGTH_20;

                CCodecUtilities::SetIntBit(
                    strOut,
                    ui32Offset,
                    DATA_LENGTH_21,
                    static_cast< INT32 >(std::round(stOrbitCorrectionInfo.second.m_dbDotDeltaRadial / SCALE_DF368)));
                ui32Offset += DATA_LENGTH_21;

                CCodecUtilities::SetIntBit(strOut,
                                           ui32Offset,
                                           DATA_LENGTH_19,
                                           static_cast< INT32 >(std::round(
                                               stOrbitCorrectionInfo.second.m_dbDotDeltaAlongTrack / SCALE_DF369)));
                ui32Offset += DATA_LENGTH_19;

                CCodecUtilities::SetIntBit(strOut,
                                           ui32Offset,
                                           DATA_LENGTH_19,
                                           static_cast< INT32 >(std::round(
                                               stOrbitCorrectionInfo.second.m_dbDotDeltaCrossTrack / SCALE_DF370)));
                ui32Offset += DATA_LENGTH_19;
            }

            iRet = RETURN_SUCCESS;
        } while (false);

        return iRet;
    }

    INT32 CRtcmEncoder::EncodeSSR2(SClockCorrection& sClockCorrection,
                                   const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                   string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        do
        {
            if (enSatSystemconst != IGnssDataInterface::SYS_GPS && enSatSystemconst != IGnssDataInterface::SYS_GLO)
            {
                break;
            }

            UINT32 satNumLength = 0U;
            UINT32 ui32Offset = MSG_HEAD_LENGTH;
            if (enSatSystemconst == IGnssDataInterface::SYS_GPS)
            {

                satNumLength = DATA_LENGTH_6;
            }
            else
            {
                satNumLength = DATA_LENGTH_5;
            }

            if (EncodeSSR2Head(sClockCorrection, enSatSystemconst, ui32Offset, strOut) != RETURN_SUCCESS)
            {
                break;
            }

            if ((sClockCorrection.m_ui16MsgType == static_cast< UINT16 >(MSG_1058))
                || (sClockCorrection.m_ui16MsgType == static_cast< UINT16 >(MSG_1064)))
            {
                for (const auto stClockCorrection : sClockCorrection.m_mapClockCorrectionInfo)
                {
                    CCodecUtilities::SetUnsignedIntBit(
                        strOut, ui32Offset, satNumLength, static_cast< UINT32 >(stClockCorrection.second.m_ui8SatId));
                    ui32Offset += satNumLength;

                    CCodecUtilities::SetIntBit(
                        strOut,
                        ui32Offset,
                        DATA_LENGTH_22,
                        static_cast< INT32 >(std::round(stClockCorrection.second.m_dbDeltaC0 / SCALE_DF376)));
                    ui32Offset += DATA_LENGTH_22;

                    CCodecUtilities::SetIntBit(
                        strOut,
                        ui32Offset,
                        DATA_LENGTH_21,
                        static_cast< INT32 >(std::round(stClockCorrection.second.m_dbDeltaC1 / SCALE_DF377)));
                    ui32Offset += DATA_LENGTH_21;

                    CCodecUtilities::SetIntBit(
                        strOut,
                        ui32Offset,
                        DATA_LENGTH_27,
                        static_cast< INT32 >(std::round(stClockCorrection.second.m_dbDeltaC2 / SCALE_DF378)));
                    ui32Offset += DATA_LENGTH_27;
                }
            }
            else
            {
                for (const auto stClockCorrection : sClockCorrection.m_mapClockCorrectionInfo)
                {
                    const DOUBLE m_dbDeltaHighFrequencyNum = //临时变量修改
                        std::round(stClockCorrection.second.m_dbDeltaHighFrequencyNum / SCALE_DF390);

                    CCodecUtilities::SetUnsignedIntBit(
                        strOut, ui32Offset, satNumLength, static_cast< UINT32 >(stClockCorrection.second.m_ui8SatId));
                    ui32Offset += satNumLength;

                    CCodecUtilities::SetIntBit(strOut,
                                               ui32Offset,
                                               DATA_LENGTH_22,
                                               static_cast< INT32 >(std::round(
                                                   stClockCorrection.second.m_dbDeltaHighFrequencyNum / SCALE_DF390)));
                    ui32Offset += DATA_LENGTH_22;
                }
            }

            iRet = RETURN_SUCCESS;
        } while (false);

        return iRet;
    }

    INT32 CRtcmEncoder::EncodeSSR4(SOrbitClockCorrection& sOrbitClockCorrection,
                                   const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                   string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        do
        {
            if (enSatSystemconst != IGnssDataInterface::SYS_GPS && enSatSystemconst != IGnssDataInterface::SYS_GLO)
            {
                break;
            }

            UINT32 satNumLength = 0U;
            UINT32 IODELength = DATA_LENGTH_8;
            UINT32 ui32Offset = MSG_HEAD_LENGTH;
            if (enSatSystemconst == IGnssDataInterface::SYS_GPS)
            {
                satNumLength = DATA_LENGTH_6;
            }
            else
            {
                satNumLength = DATA_LENGTH_5;
            }

            if (EncodeSSR4Head(sOrbitClockCorrection, enSatSystemconst, ui32Offset, strOut) != RETURN_SUCCESS)
            {
                break;
            }

            for (auto stOrbitClockCorrectionInfo : sOrbitClockCorrection.m_mapOrbitClockCorrectionInfo)
            {

                CCodecUtilities::SetUnsignedIntBit(strOut,
                                                   ui32Offset,
                                                   satNumLength,
                                                   static_cast< UINT32 >(stOrbitClockCorrectionInfo.second.m_ui8SatId));
                ui32Offset += satNumLength;

                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, IODELength, static_cast< UINT32 >(stOrbitClockCorrectionInfo.second.m_ui8IODE));
                ui32Offset += IODELength;

                CCodecUtilities::SetIntBit(
                    strOut,
                    ui32Offset,
                    DATA_LENGTH_22,
                    static_cast< INT32 >(std::round(stOrbitClockCorrectionInfo.second.m_db8DeltaRadial / SCALE_DF365)));
                ui32Offset += DATA_LENGTH_22;

                CCodecUtilities::SetIntBit(strOut,
                                           ui32Offset,
                                           DATA_LENGTH_20,
                                           static_cast< INT32 >(std::round(
                                               stOrbitClockCorrectionInfo.second.m_dbDeltaAlongTrack / SCALE_DF366)));
                ui32Offset += DATA_LENGTH_20;

                CCodecUtilities::SetIntBit(strOut,
                                           ui32Offset,
                                           DATA_LENGTH_20,
                                           static_cast< INT32 >(std::round(
                                               stOrbitClockCorrectionInfo.second.m_dbDeltaCrossTrack / SCALE_DF367)));
                ui32Offset += DATA_LENGTH_20;

                CCodecUtilities::SetIntBit(strOut,
                                           ui32Offset,
                                           DATA_LENGTH_21,
                                           static_cast< INT32 >(std::round(
                                               stOrbitClockCorrectionInfo.second.m_dbDotDeltaRadial / SCALE_DF368)));
                ui32Offset += DATA_LENGTH_21;

                CCodecUtilities::SetIntBit(
                    strOut,
                    ui32Offset,
                    DATA_LENGTH_19,
                    static_cast< INT32 >(
                        std::round(stOrbitClockCorrectionInfo.second.m_dbDotDeltaAlongTrack / SCALE_DF369)));
                ui32Offset += DATA_LENGTH_19;

                CCodecUtilities::SetIntBit(
                    strOut,
                    ui32Offset,
                    DATA_LENGTH_19,
                    static_cast< INT32 >(
                        std::round(stOrbitClockCorrectionInfo.second.m_dbDotDeltaCrossTrack / SCALE_DF370)));
                ui32Offset += DATA_LENGTH_19;

                CCodecUtilities::SetIntBit(
                    strOut,
                    ui32Offset,
                    DATA_LENGTH_22,
                    static_cast< INT32 >(std::round(stOrbitClockCorrectionInfo.second.m_dbDeltaC0 / SCALE_DF376)));
                ui32Offset += DATA_LENGTH_22;

                CCodecUtilities::SetIntBit(
                    strOut,
                    ui32Offset,
                    DATA_LENGTH_21,
                    static_cast< INT32 >(std::round(stOrbitClockCorrectionInfo.second.m_dbDeltaC1 / SCALE_DF377)));
                ui32Offset += DATA_LENGTH_21;

                CCodecUtilities::SetIntBit(
                    strOut,
                    ui32Offset,
                    DATA_LENGTH_27,
                    static_cast< INT32 >(std::round(stOrbitClockCorrectionInfo.second.m_dbDeltaC2 / SCALE_DF378)));
                ui32Offset += DATA_LENGTH_27;
            }

            iRet = RETURN_SUCCESS;
        } while (false);

        return iRet;
    }

    INT32 CRtcmEncoder::EncodeSSR1Head(const SOrbitCorrection& sOrbitCorrection,
                                       const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                       UINT32& ui32Offset,
                                       string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        do
        {
            if (enSatSystemconst != IGnssDataInterface::SYS_GPS && enSatSystemconst != IGnssDataInterface::SYS_GLO)
            {
                break;
            }

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_12, static_cast< UINT32 >(sOrbitCorrection.m_ui16MsgType));
            ui32Offset += DATA_LENGTH_12;

            if (enSatSystemconst == IGnssDataInterface::SYS_GLO)
            {
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_17, sOrbitCorrection.m_ui32EpochTime);
                ui32Offset += DATA_LENGTH_17;
            }
            else
            {
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_20, sOrbitCorrection.m_ui32EpochTime);
                ui32Offset += DATA_LENGTH_20;
            }

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_4, sOrbitCorrection.m_ui32SSRUpdateInterval);
            ui32Offset += DATA_LENGTH_4;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_1, static_cast< UINT32 >(sOrbitCorrection.m_ui8MulMsgIndicator));
            ui32Offset += DATA_LENGTH_1;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_1, static_cast< UINT32 >(sOrbitCorrection.m_ui8SatRefDatum));
            ui32Offset += DATA_LENGTH_1;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_4, static_cast< UINT32 >(sOrbitCorrection.m_ui8IodSsr));
            ui32Offset += DATA_LENGTH_4;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_16, sOrbitCorrection.m_ui32SsrProviderID);
            ui32Offset += DATA_LENGTH_16;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_4, static_cast< UINT32 >(sOrbitCorrection.m_ui8SsrSolutionID));
            ui32Offset += DATA_LENGTH_4;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_6, static_cast< UINT32 >(sOrbitCorrection.m_ui8SatNum));
            ui32Offset += DATA_LENGTH_6;

            iRet = RETURN_SUCCESS;

        } while (false);
        return iRet;
    }

    INT32 CRtcmEncoder::EncodeSSR2Head(const SClockCorrection& sClockCorrection,
                                       const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                       UINT32& ui32Offset,
                                       string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        do
        {
            if (enSatSystemconst != IGnssDataInterface::SYS_GPS && enSatSystemconst != IGnssDataInterface::SYS_GLO)
            {
                break;
            }

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_12, static_cast< UINT32 >(sClockCorrection.m_ui16MsgType));
            ui32Offset += DATA_LENGTH_12;

            if (enSatSystemconst == IGnssDataInterface::SYS_GLO)
            {
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_17, sClockCorrection.m_ui32EpochTime);
                ui32Offset += DATA_LENGTH_17;
            }
            else
            {
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_20, sClockCorrection.m_ui32EpochTime);
                ui32Offset += DATA_LENGTH_20;
            }

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_4, sClockCorrection.m_ui32SSRUpdateInterval);
            ui32Offset += DATA_LENGTH_4;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_1, static_cast< UINT32 >(sClockCorrection.m_ui8MulMsgIndicator));
            ui32Offset += DATA_LENGTH_1;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_4, static_cast< UINT32 >(sClockCorrection.m_ui8IodSsr));
            ui32Offset += DATA_LENGTH_4;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_16, sClockCorrection.m_ui32SsrProviderID);
            ui32Offset += DATA_LENGTH_16;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_4, static_cast< UINT32 >(sClockCorrection.m_ui8SsrSolutionID));
            ui32Offset += DATA_LENGTH_4;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_6, static_cast< UINT32 >(sClockCorrection.m_ui8SatNum));
            ui32Offset += DATA_LENGTH_6;

            iRet = RETURN_SUCCESS;
        } while (false);
        return iRet;
    }

    INT32 CRtcmEncoder::EncodeSSR4Head(const SOrbitClockCorrection& sOrbitClockCorrection,
                                       const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                       UINT32& ui32Offset,
                                       string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        do
        {
            if (enSatSystemconst != IGnssDataInterface::SYS_GPS && enSatSystemconst != IGnssDataInterface::SYS_GLO)
            {
                break;
            }

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_12, static_cast< UINT32 >(sOrbitClockCorrection.m_ui16MsgType));
            ui32Offset += DATA_LENGTH_12;

            if (enSatSystemconst == IGnssDataInterface::SYS_GLO)
            {
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_17, sOrbitClockCorrection.m_ui32EpochTime);
                ui32Offset += DATA_LENGTH_17;
            }
            else
            {
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_20, sOrbitClockCorrection.m_ui32EpochTime);
                ui32Offset += DATA_LENGTH_20;
            }

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_4, sOrbitClockCorrection.m_ui32SSRUpdateInterval);
            ui32Offset += DATA_LENGTH_4;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_1, static_cast< UINT32 >(sOrbitClockCorrection.m_ui8MulMsgIndicator));
            ui32Offset += DATA_LENGTH_1;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_1, static_cast< UINT32 >(sOrbitClockCorrection.m_ui8SatRefDatum));
            ui32Offset += DATA_LENGTH_1;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_4, static_cast< UINT32 >(sOrbitClockCorrection.m_ui8IodSsr));
            ui32Offset += DATA_LENGTH_4;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_16, sOrbitClockCorrection.m_ui32SsrProviderID);
            ui32Offset += DATA_LENGTH_16;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_4, static_cast< UINT32 >(sOrbitClockCorrection.m_ui8SsrSolutionID));
            ui32Offset += DATA_LENGTH_4;

            CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Offset, DATA_LENGTH_6, static_cast< UINT32 >(sOrbitClockCorrection.m_ui8SatNum));
            ui32Offset += DATA_LENGTH_6;

            iRet = RETURN_SUCCESS;
        } while (false);
        return iRet;
    }

    BOOL_T CRtcmEncoder::CheckGnssDataType(const IGnssDataInterface* const pGnssData,
                                           const IGnssDataInterface::GnssDataType type)
    {
        return ((pGnssData != nullptr) && (pGnssData->GetGnssDataType() == type));
    }

    INT32 CRtcmEncoder::RtcmEncoder1004(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CEpochObs* pEpochObs = nullptr;
        const SEpochSatObs epochstSatObs;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
            && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
        {
            SEpochSatObs stSatObs = pEpochObs->GetEpochSatObs();
            UINT32 ui32Offset = 0U;

            ui32Offset = EncodeOldObsHead(IGnssDataInterface::SYS_GPS, stSatObs, strOut);

            for (map< INT32, SSatelliteValue >::iterator stObs = stSatObs.m_mapSatValues.begin();
                 stObs != stSatObs.m_mapSatValues.end();
                 ++stObs)
            {
                auto sig1 =
                    stObs->second.m_mapSignalValues[IGnssDataInterface::SC_GPS_1C & IGnssDataInterface::SC_REMOVE_MASK];
                auto sig2 =
                    stObs->second.m_mapSignalValues[IGnssDataInterface::SC_GPS_2C & IGnssDataInterface::SC_REMOVE_MASK];

                UINT32 l1PRange = 0U;
                INT32 l1CarrierSubl1PRange = GNSS_INT20_INVALID_VALUE;
                INT32 l2Subl1PRange = GNSS_INT14_INVALID_VALUE;
                INT32 l2CarrierSubl1PRange = GNSS_INT20_INVALID_VALUE;

                GenOBSGPS(
                    sig1, sig2, stObs->second, l1PRange, l1CarrierSubl1PRange, l2Subl1PRange, l2CarrierSubl1PRange);

                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_6, static_cast< UINT32 >(stObs->first));
                ui32Offset += DATA_LENGTH_6;

                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_1, sig1.m_ui8CodeMark);
                ui32Offset += DATA_LENGTH_1;

                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_24, l1PRange);
                ui32Offset += DATA_LENGTH_24;

                CCodecUtilities::SetIntBit(strOut, ui32Offset, DATA_LENGTH_20, l1CarrierSubl1PRange);
                ui32Offset += DATA_LENGTH_20;

                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_7, static_cast< UINT32 >(sig1.m_ui8LockTimeIndicator));
                ui32Offset += DATA_LENGTH_7;

                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_8, static_cast< UINT32 >(stObs->second.m_ui8Milliseconds));
                ui32Offset += DATA_LENGTH_8;

                sig1.m_dbSignalCnr = sig1.m_dbSignalCnr / SCALE_DF015;
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_8, static_cast< UINT32 >(std::round(sig1.m_dbSignalCnr)));
                ui32Offset += DATA_LENGTH_8;

                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_2, sig2.m_ui8CodeMark);
                ui32Offset += DATA_LENGTH_2;

                CCodecUtilities::SetIntBit(strOut, ui32Offset, DATA_LENGTH_14, l2Subl1PRange);
                ui32Offset += DATA_LENGTH_14;

                CCodecUtilities::SetIntBit(strOut, ui32Offset, DATA_LENGTH_20, l2CarrierSubl1PRange);
                ui32Offset += DATA_LENGTH_20;

                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_7, static_cast< UINT32 >(sig2.m_ui8LockTimeIndicator));
                ui32Offset += DATA_LENGTH_7;

                sig2.m_dbSignalCnr = sig2.m_dbSignalCnr / SCALE_DF015;
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_8, static_cast< UINT32 >(std::round(sig2.m_dbSignalCnr)));
                ui32Offset += DATA_LENGTH_8;
            }
            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get CEpochObs object failed for 1004", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1005(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CReferenceInfo* stReferenceInfo = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &stReferenceInfo, nullptr)
            && CheckGnssDataType(stReferenceInfo, IGnssDataInterface::GDT_REF_INFO))
        {
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            const SReferenceInfo info = stReferenceInfo->GetReferenceInfo();
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(info.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(info.m_ui16RefStaionId));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(info.m_ui8ItrfYear));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8GPSIndicator));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8GlonassIndicator));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8GalileoIndicator));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8RefStationIndicator));
            ui32Pos = CCodecUtilities::SetDoubleBit(strOut, ui32Pos, info.m_dbArpEcefX / SCALE_1E_4);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8SingleROI));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8BDSIndicator));
            ui32Pos = CCodecUtilities::SetDoubleBit(strOut, ui32Pos, info.m_dbArpEcefY / SCALE_1E_4);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_2, static_cast< UINT32 >(info.m_ui8QuarterCycleIndicator));
            ui32Pos = CCodecUtilities::SetDoubleBit(strOut, ui32Pos, info.m_dbArpEcefZ / SCALE_1E_4);

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get CReferenceInfo object failed for 1005", CLog::LL_ERROR);
        }

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1006(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CReferenceInfo* stReferenceInfo = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &stReferenceInfo, nullptr)
            && CheckGnssDataType(stReferenceInfo, IGnssDataInterface::GDT_REF_INFO))
        {
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            const SReferenceInfo info = stReferenceInfo->GetReferenceInfo();
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(info.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(info.m_ui16RefStaionId));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(info.m_ui8ItrfYear));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8GPSIndicator));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8GlonassIndicator));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8GalileoIndicator));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8RefStationIndicator));
            ui32Pos = CCodecUtilities::SetDoubleBit(strOut, ui32Pos, info.m_dbArpEcefX / SCALE_1E_4);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8SingleROI));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(info.m_ui8BDSIndicator));
            ui32Pos = CCodecUtilities::SetDoubleBit(strOut, ui32Pos, info.m_dbArpEcefY / SCALE_1E_4);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_2, static_cast< UINT32 >(info.m_ui8QuarterCycleIndicator));
            ui32Pos = CCodecUtilities::SetDoubleBit(strOut, ui32Pos, info.m_dbArpEcefZ / SCALE_1E_4);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut,
                ui32Pos,
                DATA_LENGTH_16,
                static_cast< UINT32 >(std::round(info.m_dbAntennaHeight / SCALE_1E_4)));

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get CReferenceInfo object failed for 1006", CLog::LL_ERROR);
        }

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1012(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CEpochObs* pEpochObs = nullptr;

        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
            && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
        {
            auto stSatObs = pEpochObs->GetEpochSatObs();
            UINT32 ui32Offset = 0U;

            ui32Offset = EncodeOldObsHead(IGnssDataInterface::SYS_GLO, stSatObs, strOut);

            for (map< INT32, SSatelliteValue >::iterator stObs = stSatObs.m_mapSatValues.begin();
                 stObs != stSatObs.m_mapSatValues.end();
                 stObs++)
            {
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_6, static_cast< UINT32 >(stObs->first));
                ui32Offset += DATA_LENGTH_6;

                auto sig1 =
                    stObs->second.m_mapSignalValues[IGnssDataInterface::SC_GLO_1C & IGnssDataInterface::SC_REMOVE_MASK];
                auto sig2 =
                    stObs->second.m_mapSignalValues[IGnssDataInterface::SC_GLO_2C & IGnssDataInterface::SC_REMOVE_MASK];

                UINT32 l1PRange = 0U;
                INT32 l1CarrierSubl1PRange = GNSS_INT20_INVALID_VALUE;
                INT32 l2Subl1PRange = GNSS_INT14_INVALID_VALUE;
                INT32 l2CarrierSubl1PRange = GNSS_INT20_INVALID_VALUE;

                GenOBSGLONASS(
                    sig1, sig2, stObs->second, l1PRange, l1CarrierSubl1PRange, l2Subl1PRange, l2CarrierSubl1PRange);
                if (stObs->second.m_ui8SatFrequencyChannelNumber < 0U)
                {
                    stObs->second.m_ui8SatFrequencyChannelNumber = 0U;
                }

                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_1, sig1.m_ui8CodeMark);
                ui32Offset += DATA_LENGTH_1;

                CCodecUtilities::SetUnsignedIntBit(strOut,
                                                   ui32Offset,
                                                   DATA_LENGTH_5,
                                                   static_cast< UINT32 >(stObs->second.m_ui8SatFrequencyChannelNumber));
                ui32Offset += DATA_LENGTH_5;

                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_25, l1PRange);
                ui32Offset += DATA_LENGTH_25;

                CCodecUtilities::SetIntBit(strOut, ui32Offset, DATA_LENGTH_20, l1CarrierSubl1PRange);
                ui32Offset += DATA_LENGTH_20;

                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_7, static_cast< UINT32 >(sig1.m_ui8LockTimeIndicator));
                ui32Offset += DATA_LENGTH_7;

                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_7, static_cast< UINT32 >(stObs->second.m_ui8Milliseconds));
                ui32Offset += DATA_LENGTH_7;

                sig1.m_dbSignalCnr = sig1.m_dbSignalCnr / SCALE_DF045;
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_8, static_cast< UINT32 >(std::round(sig1.m_dbSignalCnr)));
                ui32Offset += DATA_LENGTH_8;

                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Offset, DATA_LENGTH_2, sig2.m_ui8CodeMark);
                ui32Offset += DATA_LENGTH_2;

                CCodecUtilities::SetIntBit(strOut, ui32Offset, DATA_LENGTH_14, l2Subl1PRange);
                ui32Offset += DATA_LENGTH_14;

                CCodecUtilities::SetIntBit(strOut, ui32Offset, DATA_LENGTH_20, l2CarrierSubl1PRange);
                ui32Offset += DATA_LENGTH_20;

                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_7, static_cast< UINT32 >(sig2.m_ui8LockTimeIndicator));
                ui32Offset += DATA_LENGTH_7;

                sig2.m_dbSignalCnr = sig2.m_dbSignalCnr / SCALE_DF045;
                CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Offset, DATA_LENGTH_8, static_cast< UINT32 >(std::round(sig2.m_dbSignalCnr)));
                ui32Offset += DATA_LENGTH_8;
            }

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get CEpochObs object failed for 1012", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1019(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CEphemeris* ptrEphemeris = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &ptrEphemeris, nullptr)
            && CheckGnssDataType(ptrEphemeris, IGnssDataInterface::GDT_EPH))
        {
            m_pobjLog->Trace("Encode Ephemeris object for 1019", CLog::LL_INFO);

            DOUBLE dbValue = 0.0;
            const auto stEph = ptrEphemeris->GetEphemeris();
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stEph.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(stEph.m_ui8SatId));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< UINT32 >(stEph.m_ui16WeekNum) % SCALE_DF452);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stEph.m_ui8URA));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_2, static_cast< UINT32 >(stEph.m_ui8CodeOnL2));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_14, static_cast< INT32 >(std::round(stEph.m_dbIdot / P2_43 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(stEph.m_ui8Iode));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_16, stEph.m_ui32Toc / P2T4);
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< INT32 >(std::round(stEph.m_dbAf2 / P2_55)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbAf1 / P2_43)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_22, static_cast< INT32 >(std::round(stEph.m_dbAf0 / P2_31)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< UINT32 >(stEph.m_ui16Iodc));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCrs / P2_5)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbDeltaN / P2_43 / SC2RAD)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbM0 / P2_31 / SC2RAD)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCuc / P2_29)));
            dbValue = stEph.m_dbEccentricity / P2_33;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< UINT32 >(std::round(dbValue)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCus / P2_29)));

            // 参考RTCM STANDARD 10403.3数据单位:m 需要转换成常用模式单位:m1/2 转换方式是sqrt(value)
            dbValue = std::sqrt(stEph.m_dbAHalf);

            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< UINT32 >(std::round(dbValue / P2_19)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< UINT32 >(stEph.m_ui32Toe / P2T4));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCic / P2_29)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbOmega0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCis / P2_29)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbI0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCrc / P2_5)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut,
                ui32Pos,
                DATA_LENGTH_32,
                static_cast< INT32 >(std::round(stEph.m_dbArgumentOfPerigee / P2_31 / SC2RAD)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_24, static_cast< INT32 >(std::round(stEph.m_dbOmegaDot / P2_43 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< INT32 >(std::round(stEph.m_dbTgd / P2_31)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(stEph.m_ui8SvHealth));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stEph.m_ui8L2PDataFlag));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stEph.m_ui8FitInterval));
            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get Ephemeris object failed for 1019", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1020(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CGlonassEphemeris* ptrEphemeris = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &ptrEphemeris, nullptr)
            && CheckGnssDataType(ptrEphemeris, IGnssDataInterface::GDT_GLO_EPH))
        {
            DOUBLE dbValue = 0.0;
            const auto eph = ptrEphemeris->GetGlonassEphemeris();
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(eph.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(eph.m_ui8SatId));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_5, static_cast< UINT32 >(eph.m_ui8SatFrequencyChannelNumber));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(eph.m_ui8AlmanacHealth));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(eph.m_ui8AHAI));
            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_2, static_cast< UINT32 >(eph.m_ui8P1));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(eph.m_ui16Tk));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(eph.m_ui8MsbOfBn));
            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(eph.m_ui8P2));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_7, static_cast< UINT32 >(eph.m_ui16Tb) / SCALE_DF110);
            dbValue = eph.m_dbXnTbFirstDerivative / P2_20 / P104;
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_24, static_cast< INT32 >(std::round(dbValue)));
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_27, static_cast< INT32 >(std::round(eph.m_dbXnTb / P2_11 / P104)));
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut,
                ui32Pos,
                DATA_LENGTH_5,
                static_cast< INT32 >(std::round(eph.m_dbXnTbSecondDerivative / P2_30 / P104)));
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut,
                ui32Pos,
                DATA_LENGTH_24,
                static_cast< INT32 >(std::round(eph.m_dbYnTbFirstDerivative / P2_20 / P104)));
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_27, static_cast< INT32 >(std::round(eph.m_dbYnTb / P2_11 / P104)));
            dbValue = eph.m_dbYnTbSecondDerivative / P2_30 / P104;
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_5, static_cast< INT32 >(std::round(dbValue)));
            dbValue = eph.m_dbZnTbFirstDerivative / P2_20 / P104;
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_24, static_cast< INT32 >(std::round(dbValue)));
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_27, static_cast< INT32 >(std::round(eph.m_dbZnTb / P2_11 / P104)));
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut,
                ui32Pos,
                DATA_LENGTH_5,
                static_cast< INT32 >(std::round(eph.m_dbZnTbSecondDerivative / P2_30 / P104)));
            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(eph.m_ui8P3));
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_11, static_cast< INT32 >(std::round(eph.m_dbGammaTb / P2_40)));
            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_2, static_cast< UINT32 >(eph.m_ui8GmP));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(eph.m_ui8GmLn3));
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_22, static_cast< INT32 >(std::round(eph.m_dbTnTb / P2_30)));
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_5, static_cast< INT32 >(std::round(eph.m_dbGmDeltaTn / P2_30)));
            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_5, static_cast< UINT32 >(eph.m_ui8En));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(eph.m_ui8GmP4));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(eph.m_ui8GmFt));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_11, static_cast< UINT32 >(eph.m_ui16GmNt));
            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_2, static_cast< UINT32 >(eph.m_ui8GmM));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(eph.m_ui8AOAD));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_11, static_cast< UINT32 >(eph.m_ui16NA));
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(eph.m_dbTc / P2_31)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_5, static_cast< UINT32 >(eph.m_ui8GmN4) / SCALE_DF134);
            ui32Pos = CCodecUtilities::SetSignMagnitudeIntBit(
                strOut, ui32Pos, DATA_LENGTH_22, static_cast< INT32 >(std::round(eph.m_dbGmTGps / P2_30)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(eph.m_ui8GmLn5));

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get CGlonassEphemeris object failed for 1020", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1033(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CReferenceInfo* pReferenceInfo = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pReferenceInfo, nullptr)
            && CheckGnssDataType(pReferenceInfo, IGnssDataInterface::GDT_REF_INFO))
        {
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            SReferenceInfo stInfo = pReferenceInfo->GetReferenceInfo();
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stInfo.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stInfo.m_ui16RefStaionId));

            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(stInfo.m_ui8DescriptorCount));
            for (size_t i = 0U; i < static_cast< size_t >(stInfo.m_ui8DescriptorCount); ++i)
            {
                ui32Pos = CCodecUtilities::SetIntBit(
                    strOut, ui32Pos, DATA_LENGTH_8, static_cast< INT32 >(stInfo.m_objAntennaDescriptor[i]));
            }

            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(stInfo.m_ui8AntennaSetupId));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(stInfo.m_ui8SerialNumberCount));
            for (size_t i = 0U; i < static_cast< size_t >(stInfo.m_ui8SerialNumberCount); ++i)
            {
                ui32Pos = CCodecUtilities::SetIntBit(
                    strOut, ui32Pos, DATA_LENGTH_8, static_cast< INT32 >(stInfo.m_objAntennaSerialNumber[i]));
            }

            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(stInfo.m_ui8RTDC));
            for (size_t i = 0U; i < static_cast< size_t >(stInfo.m_ui8RTDC); ++i)
            {
                ui32Pos = CCodecUtilities::SetIntBit(
                    strOut, ui32Pos, DATA_LENGTH_8, static_cast< INT32 >(stInfo.m_objReceiverTypeDescriptor[i]));
            }

            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(stInfo.m_ui8RFVC));
            for (size_t i = 0U; i < static_cast< size_t >(stInfo.m_ui8RFVC); ++i)
            {
                ui32Pos = CCodecUtilities::SetIntBit(
                    strOut, ui32Pos, DATA_LENGTH_8, static_cast< INT32 >(stInfo.m_objReceiverFirmwareVersion[i]));
            }

            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(stInfo.m_ui8ReceiverSerialNumberCount));
            for (size_t i = 0U; i < static_cast< size_t >(stInfo.m_ui8ReceiverSerialNumberCount); ++i)
            {
                ui32Pos = CCodecUtilities::SetIntBit(
                    strOut, ui32Pos, DATA_LENGTH_8, static_cast< INT32 >(stInfo.m_objReceiverSerialNumber[i]));
            }

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get CReferenceInfo object failed for 1033", CLog::LL_ERROR);
        }

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1042(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CEphemeris* ptrEphemeris = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &ptrEphemeris, nullptr)
            && CheckGnssDataType(ptrEphemeris, IGnssDataInterface::GDT_EPH))
        {
            const auto stEph = ptrEphemeris->GetEphemeris();
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stEph.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(stEph.m_ui8SatId));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_13, static_cast< UINT32 >(stEph.m_ui16WeekNum) % SCALE_DF489);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stEph.m_ui8URA));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_14, static_cast< INT32 >(std::round(stEph.m_dbIdot / P2_43 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_5, static_cast< UINT32 >(stEph.m_ui8AgeOfDataEphemeris));
            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_17, stEph.m_ui32Toc / SCALE_DF493);
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_11, static_cast< INT32 >(std::round(stEph.m_dbAf2 / P2_66)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_22, static_cast< INT32 >(std::round(stEph.m_dbAf1 / P2_50)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_24, static_cast< INT32 >(std::round(stEph.m_dbAf0 / P2_33)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_5, static_cast< UINT32 >(stEph.m_ui8AgeOfDataClock));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_18, static_cast< INT32 >(std::round(stEph.m_dbCrs / P2_6)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbDeltaN / P2_43 / SC2RAD)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbM0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_18, static_cast< INT32 >(std::round(stEph.m_dbCuc / P2_31)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< UINT32 >(std::round(stEph.m_dbEccentricity / P2_33)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_18, static_cast< INT32 >(std::round(stEph.m_dbCus / P2_31)));
            // 参考RTCM STANDARD 10403.3数据单位:m 需要转换成常用模式单位:m1/2 转换方式是sqrt(value)
            DOUBLE dbAHalf = std::sqrt(stEph.m_dbAHalf);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< UINT32 >(std::round(dbAHalf / P2_19)));
            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_17, stEph.m_ui32Toe / SCALE_DF505);
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_18, static_cast< INT32 >(std::round(stEph.m_dbCic / P2_31)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbOmega0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_18, static_cast< INT32 >(std::round(stEph.m_dbCis / P2_31)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbI0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_18, static_cast< INT32 >(std::round(stEph.m_dbCrc / P2_6)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut,
                ui32Pos,
                DATA_LENGTH_32,
                static_cast< INT32 >(std::round(stEph.m_dbArgumentOfPerigee / P2_31 / SC2RAD)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_24, static_cast< INT32 >(std::round(stEph.m_dbOmegaDot / P2_43 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< INT32 >(std::round(stEph.m_dbTgd1 / SCALE_1E_1)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< INT32 >(std::round(stEph.m_dbTgd2 / SCALE_1E_1)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stEph.m_ui8SvHealth));

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get CEphemeris object failed for 1042", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1044(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CEphemeris* ptrEphemeris = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &ptrEphemeris, nullptr)
            && CheckGnssDataType(ptrEphemeris, IGnssDataInterface::GDT_EPH))
        {
            const auto stEph = ptrEphemeris->GetEphemeris();
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stEph.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stEph.m_ui8SatId));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_16, stEph.m_ui32Toc / P2T4);
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< INT32 >(std::round(stEph.m_dbAf2 / P2_55)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbAf1 / P2_43)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_22, static_cast< INT32 >(std::round(stEph.m_dbAf0 / P2_31)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(stEph.m_ui8Iode));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCrs / P2_5)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbDeltaN / P2_43 / SC2RAD)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbM0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCuc / P2_29)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< UINT32 >(std::round(stEph.m_dbEccentricity / P2_33)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCus / P2_29)));

            // 参考RTCM STANDARD 10403.3数据单位:m 需要转换成常用模式单位:m1/2 转换方式是sqrt(value)
            DOUBLE dbAHalf = std::sqrt(stEph.m_dbAHalf);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< UINT32 >(std::round(dbAHalf / P2_19)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_16, stEph.m_ui32Toe / P2T4);
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCic / P2_29)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbOmega0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCis / P2_29)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbI0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCrc / P2_5)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut,
                ui32Pos,
                DATA_LENGTH_32,
                static_cast< INT32 >(std::round(stEph.m_dbArgumentOfPerigee / P2_31 / SC2RAD)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_24, static_cast< INT32 >(std::round(stEph.m_dbOmegaDot / P2_43 / SC2RAD)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_14, static_cast< INT32 >(std::round(stEph.m_dbIODot / P2_43 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_2, static_cast< UINT32 >(stEph.m_ui8CodeOnL2));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< UINT32 >(stEph.m_ui16WeekNum) % SCALE_DF452);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stEph.m_ui8URA));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(stEph.m_ui8SvHealth));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< INT32 >(std::round(stEph.m_dbTgd / P2_31)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< UINT32 >(stEph.m_ui16Iodc));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stEph.m_ui8FitInterval));

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get CEphemeris object failed for 1044", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1045(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CEphemeris* ptrEphemeris = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &ptrEphemeris, nullptr)
            && CheckGnssDataType(ptrEphemeris, IGnssDataInterface::GDT_EPH))
        {
            const auto stEph = ptrEphemeris->GetEphemeris();
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stEph.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(stEph.m_ui8SatId));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stEph.m_ui16WeekNum) % SCALE_DF289);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< UINT32 >(stEph.m_ui16IODnav));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(stEph.m_ui8SvSisa));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_14, static_cast< INT32 >(std::round(stEph.m_dbIdot / P2_43 / SC2RAD)));

            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_14, stEph.m_ui32Toc / SCALE_DF293);
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< INT32 >(std::round(stEph.m_dbAf2 / P2_59)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_21, static_cast< INT32 >(std::round(stEph.m_dbAf1 / P2_46)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_31, static_cast< INT32 >(std::round(stEph.m_dbAf0 / P2_34)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCrs / P2_5)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbDeltaN / P2_43 / SC2RAD)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbM0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCuc / P2_29)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< UINT32 >(std::round(stEph.m_dbEccentricity / P2_33)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCus / P2_29)));
            // 参考RTCM STANDARD 10403.3数据单位:m 需要转换成常用模式单位:m1/2 转换方式是sqrt(value)
            DOUBLE dbAHalf = std::sqrt(stEph.m_dbAHalf);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< UINT32 >(std::round(dbAHalf / P2_19)));
            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_14, stEph.m_ui32Toe / SCALE_DF304);
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCic / P2_29)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbOmega0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCis / P2_29)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbI0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCrc / P2_5)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut,
                ui32Pos,
                DATA_LENGTH_32,
                static_cast< INT32 >(std::round(stEph.m_dbArgumentOfPerigee / P2_31 / SC2RAD)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_24, static_cast< INT32 >(std::round(stEph.m_dbOmegaDot / P2_43 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< INT32 >(std::round(stEph.m_dbBgdE1E5a / P2_32)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_2, static_cast< UINT32 >(stEph.m_ui8OSHS));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stEph.m_ui8OSDVS));

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get CEphemeris object failed for 1045", CLog::LL_ERROR);
        }

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1046(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CEphemeris* ptrEphemeris = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &ptrEphemeris, nullptr)
            && CheckGnssDataType(ptrEphemeris, IGnssDataInterface::GDT_EPH))
        {
            const auto stEph = ptrEphemeris->GetEphemeris();
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stEph.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(stEph.m_ui8SatId));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stEph.m_ui16WeekNum) % SCALE_DF289);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< UINT32 >(stEph.m_ui16IODnav));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(stEph.m_ui8SISAIndex));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_14, static_cast< INT32 >(std::round(stEph.m_dbIdot / P2_43 / SC2RAD)));

            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_14, stEph.m_ui32Toc / SCALE_DF293);
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< INT32 >(std::round(stEph.m_dbAf2 / P2_59)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_21, static_cast< INT32 >(std::round(stEph.m_dbAf1 / P2_46)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_31, static_cast< INT32 >(std::round(stEph.m_dbAf0 / P2_34)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCrs / P2_5)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbDeltaN / P2_43 / SC2RAD)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbM0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCuc / P2_29)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< UINT32 >(std::round(stEph.m_dbEccentricity / P2_33)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCus / P2_29)));
            // 参考RTCM STANDARD 10403.3数据单位:m 需要转换成常用模式单位:m1/2 转换方式是sqrt(value)
            DOUBLE dbAHalf = std::sqrt(stEph.m_dbAHalf);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< UINT32 >(std::round(dbAHalf / P2_19)));
            ui32Pos =
                CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_14, stEph.m_ui32Toe / SCALE_DF304);
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCic / P2_29)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbOmega0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCis / P2_29)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(std::round(stEph.m_dbI0 / P2_31 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_16, static_cast< INT32 >(std::round(stEph.m_dbCrc / P2_5)));

            // 现单位:deg 需转换成RTCM STANDARD 10403.3数据单位:semicircles 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut,
                ui32Pos,
                DATA_LENGTH_32,
                static_cast< INT32 >(std::round(stEph.m_dbArgumentOfPerigee / P2_31 / SC2RAD)));

            // 现单位:deg/s 需转换成RTCM STANDARD 10403.3数据单位:semicircles/s 转换方式是 value / SC2RAD
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_24, static_cast< INT32 >(std::round(stEph.m_dbOmegaDot / P2_43 / SC2RAD)));

            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< INT32 >(std::round(stEph.m_dbBgdE1E5a / P2_32)));
            ui32Pos = CCodecUtilities::SetIntBit(
                strOut, ui32Pos, DATA_LENGTH_10, static_cast< INT32 >(std::round(stEph.m_dbBgdE5bE1 / P2_32)));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_2, static_cast< UINT32 >(stEph.m_ui8E5bSignalHealthStatus));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stEph.m_ui8E5bDataValidityStatus));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_2, static_cast< UINT32 >(stEph.m_ui8E1bSignalHealthStatus));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stEph.m_ui8E1bDataValidityStatus));

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Get CEphemeris object failed for 1046", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1057(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        COrbitCorrection* cOrbitCorrection = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &cOrbitCorrection, nullptr)
            && CheckGnssDataType(cOrbitCorrection, IGnssDataInterface::GDT_ORBIT))
        {
            auto sOrbit = cOrbitCorrection->GetOrbitCorrection();
            iRet = EncodeSSR1(sOrbit, IGnssDataInterface::SYS_GPS, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get COrbitCorrection obj in RtcmEncoder1057.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1058(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CClockCorrection* cClockCorrection = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &cClockCorrection, nullptr)
            && CheckGnssDataType(cClockCorrection, IGnssDataInterface::GDT_CLOCK))
        {

            auto sClock = cClockCorrection->GetClockCorrection();
            iRet = EncodeSSR2(sClock, IGnssDataInterface::SYS_GPS, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CClockCorrection obj in RtcmEncoder1058.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1059(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CDcb* pDcb = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pDcb, nullptr)
            && CheckGnssDataType(pDcb, IGnssDataInterface::GDT_DCB))
        {
            auto stDcb = pDcb->GetDcb();
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stDcb.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_20, stDcb.m_ui32EpochTime);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_4, stDcb.m_ui32SSRUpdateInterval);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stDcb.m_ui8MulMsgIndicator));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stDcb.m_ui8IodSsr));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_16, stDcb.m_ui32SsrProviderID);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stDcb.m_ui8SsrSolutionID));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(stDcb.m_ui8SatNum));

            // 写入卫星数据
            for (auto& item : stDcb.m_mapDcbSatInfo)
            {
                ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(item.second.m_ui8SatId));
                ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Pos, DATA_LENGTH_5, static_cast< UINT32 >(item.second.m_ui8SsrUraNum));

                for (auto& cbp : item.second.m_mapDcbInfo)
                {
                    ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                        strOut,
                        ui32Pos,
                        DATA_LENGTH_5,
                        static_cast< UINT32 >(cbp.second.m_ui8SignalTrackingModeIndicator));
                    ui32Pos = CCodecUtilities::SetIntBit(
                        strOut,
                        ui32Pos,
                        DATA_LENGTH_14,
                        static_cast< INT32 >(std::round(cbp.second.m_dbCodeBias / SCALE_1E_2)));
                }
            }

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Failed to get CDcb obj in RtcmEncoder1059.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1060(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        COrbitClockCorrection* cOrbitClockCorrection = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &cOrbitClockCorrection, nullptr)
            && CheckGnssDataType(cOrbitClockCorrection, IGnssDataInterface::GDT_ORBIT_CLOCK))
        {

            auto sOrbitClockCorrection = cOrbitClockCorrection->GetOrbitClockCorrection();
            iRet = EncodeSSR4(sOrbitClockCorrection, IGnssDataInterface::SYS_GPS, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get COrbitClockCorrection obj in RtcmEncoder1060.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1061(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CUra* pUra = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pUra, nullptr)
            && CheckGnssDataType(pUra, IGnssDataInterface::GDT_URA))
        {
            auto stUra = pUra->GetUra();
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stUra.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_20, stUra.m_ui32EpochTime);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_4, stUra.m_ui32SSRUpdateInterval);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stUra.m_ui8MulMsgIndicator));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stUra.m_ui8IodSsr));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_16, stUra.m_ui32SsrProviderID);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stUra.m_ui8SsrSolutionID));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(stUra.m_ui8SatNum));

            // 写入卫星数据
            for (auto& item : stUra.m_mapUraInfo)
            {
                ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(item.second.m_ui8SatId));
                ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(item.second.m_ui8SsrUra));
            }

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Failed to get CUra obj in RtcmEncoder1061.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1062(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CClockCorrection* cClockCorrection = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &cClockCorrection, nullptr)
            && CheckGnssDataType(cClockCorrection, IGnssDataInterface::GDT_CLOCK))
        {

            auto sClock = cClockCorrection->GetClockCorrection();
            iRet = EncodeSSR2(sClock, IGnssDataInterface::SYS_GPS, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CClockCorrection obj in RtcmEncoder1062.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1063(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        COrbitCorrection* cOrbitCorrection = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &cOrbitCorrection, nullptr)
            && CheckGnssDataType(cOrbitCorrection, IGnssDataInterface::GDT_ORBIT))
        {
            auto sOrbit = cOrbitCorrection->GetOrbitCorrection();
            iRet = EncodeSSR1(sOrbit, IGnssDataInterface::SYS_GLO, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get COrbitCorrection obj in RtcmEncoder1063.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1064(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CClockCorrection* cClockCorrection = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &cClockCorrection, nullptr)
            && CheckGnssDataType(cClockCorrection, IGnssDataInterface::GDT_CLOCK))
        {
            auto sClock = cClockCorrection->GetClockCorrection();
            iRet = EncodeSSR2(sClock, IGnssDataInterface::SYS_GLO, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CClockCorrection obj in RtcmEncoder1064.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1065(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CDcb* pDcb = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pDcb, nullptr)
            && CheckGnssDataType(pDcb, IGnssDataInterface::GDT_DCB))
        {
            auto stDcb = pDcb->GetDcb();
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stDcb.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_17, stDcb.m_ui32EpochTime);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_4, stDcb.m_ui32SSRUpdateInterval);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stDcb.m_ui8MulMsgIndicator));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stDcb.m_ui8IodSsr));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_16, stDcb.m_ui32SsrProviderID);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stDcb.m_ui8SsrSolutionID));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(stDcb.m_ui8SatNum));

            // 写入卫星数据
            for (auto& item : stDcb.m_mapDcbSatInfo)
            {
                ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Pos, DATA_LENGTH_5, static_cast< UINT32 >(item.second.m_ui8SatId));
                ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Pos, DATA_LENGTH_5, static_cast< UINT32 >(item.second.m_ui8SsrUraNum));

                for (auto& cbp : item.second.m_mapDcbInfo)
                {
                    ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                        strOut,
                        ui32Pos,
                        DATA_LENGTH_5,
                        static_cast< UINT32 >(cbp.second.m_ui8SignalTrackingModeIndicator));
                    ui32Pos = CCodecUtilities::SetIntBit(
                        strOut,
                        ui32Pos,
                        DATA_LENGTH_14,
                        static_cast< INT32 >(std::round(cbp.second.m_dbCodeBias / SCALE_1E_2)));
                }
            }

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Failed to get CDcb obj in RtcmEncoder1065.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1066(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        COrbitClockCorrection* cOrbitClockCorrection = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &cOrbitClockCorrection, nullptr)
            && CheckGnssDataType(cOrbitClockCorrection, IGnssDataInterface::GDT_ORBIT_CLOCK))
        {

            auto sOrbitClockCorrection = cOrbitClockCorrection->GetOrbitClockCorrection();
            iRet = EncodeSSR4(sOrbitClockCorrection, IGnssDataInterface::SYS_GLO, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get COrbitClockCorrection obj in RtcmEncoder1066.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1067(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CUra* pUra = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pUra, nullptr)
            && CheckGnssDataType(pUra, IGnssDataInterface::GDT_URA))
        {
            auto stUra = pUra->GetUra();
            UINT32 ui32Pos = MSG_HEAD_LENGTH;
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_12, static_cast< UINT32 >(stUra.m_ui16MsgType));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_17, stUra.m_ui32EpochTime);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_4, stUra.m_ui32SSRUpdateInterval);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(stUra.m_ui8MulMsgIndicator));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stUra.m_ui8IodSsr));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(strOut, ui32Pos, DATA_LENGTH_16, stUra.m_ui32SsrProviderID);
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(stUra.m_ui8SsrSolutionID));
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(stUra.m_ui8SatNum));

            // 写入卫星数据
            for (auto& item : stUra.m_mapUraInfo)
            {
                ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Pos, DATA_LENGTH_5, static_cast< UINT32 >(item.second.m_ui8SatId));
                ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                    strOut, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(item.second.m_ui8SsrUra));
            }

            iRet = RETURN_SUCCESS;
        }
        else
        {
            m_pobjLog->Trace("Failed to get CUra obj in RtcmEncoder1067.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1068(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CClockCorrection* cClockCorrection = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &cClockCorrection, nullptr)
            && CheckGnssDataType(cClockCorrection, IGnssDataInterface::GDT_CLOCK))
        {
            auto sClock = cClockCorrection->GetClockCorrection();
            iRet = EncodeSSR2(sClock, IGnssDataInterface::SYS_GLO, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CClockCorrection obj in RtcmEncoder1068.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1074(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CEpochObs* pEpochObs = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
            && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
        {
            const auto stSatObs = pEpochObs->GetEpochSatObs();
            iRet = EncodeMsm4(stSatObs, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CEpochObs obj in RtcmEncoder1074.", CLog::LL_ERROR);
        }
        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1077(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CEpochObs* pEpochObs = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
            && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
        {
            const auto stSatObs = pEpochObs->GetEpochSatObs();
            iRet = EncodeMsm7(stSatObs, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CEpochObs obj in RtcmEncoder1077.", CLog::LL_ERROR);
        }

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1084(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        CEpochObs* pEpochObs = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
            && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
        {
            const auto stSatObs = pEpochObs->GetEpochSatObs();
            iRet = EncodeMsm4(stSatObs, strOut, true);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CEpochObs obj in RtcmEncoder1084.", CLog::LL_ERROR);
        }

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1087(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CEpochObs* pEpochObs = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
            && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
        {
            m_pobjLog->Trace("Rtcm start encode 1087", CLog::LL_INFO);
            const auto stSatObs = pEpochObs->GetEpochSatObs();
            iRet = EncodeMsm7(stSatObs, strOut, true);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CEpochObs obj in RtcmEncoder1087.", CLog::LL_ERROR);
        }

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1094(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        do
        {
            CEpochObs* pEpochObs = nullptr;
            if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
                && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
            {
                m_pobjLog->Trace("Rtcm start encode 1094", CLog::LL_INFO);
                const auto stSatObs = pEpochObs->GetEpochSatObs();

                iRet = EncodeMsm4(stSatObs, strOut);
            }
            else
            {
                m_pobjLog->Trace("Failed to get CEpochObs obj in RtcmEncoder1094.", CLog::LL_ERROR);
                break;
            }

        } while (false);

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1097(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CEpochObs* pEpochObs = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
            && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
        {
            m_pobjLog->Trace("Rtcm start encode 1097", CLog::LL_INFO);
            const auto stSatObs = pEpochObs->GetEpochSatObs();
            iRet = EncodeMsm7(stSatObs, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CEpochObs obj in RtcmEncoder1097.", CLog::LL_ERROR);
        }

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1114(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;
        do
        {
            CEpochObs* pEpochObs = nullptr;
            if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
                && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
            {
                m_pobjLog->Trace("Rtcm start encode 1114", CLog::LL_INFO);
                const auto stSatObs = pEpochObs->GetEpochSatObs();
                iRet = EncodeMsm4(stSatObs, strOut);
            }
            else
            {
                m_pobjLog->Trace("Failed to get CEpochObs obj in RtcmEncoder1114.", CLog::LL_ERROR);
                break;
            }

        } while (false);

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1117(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CEpochObs* pEpochObs = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
            && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
        {
            m_pobjLog->Trace("Rtcm start encode 1117", CLog::LL_INFO);
            const auto stSatObs = pEpochObs->GetEpochSatObs();
            iRet = EncodeMsm7(stSatObs, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CEpochObs obj in RtcmEncoder1117.", CLog::LL_ERROR);
        }

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1124(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        do
        {
            CEpochObs* pEpochObs = nullptr;
            if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
                && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
            {
                m_pobjLog->Trace("Rtcm start encode 1124", CLog::LL_INFO);
                const auto stSatObs = pEpochObs->GetEpochSatObs();
                iRet = EncodeMsm4(stSatObs, strOut);
            }
            else
            {
                m_pobjLog->Trace("Failed to get CEpochObs obj in RtcmEncoder1124.", CLog::LL_ERROR);
                break;
            }

        } while (false);

        return iRet;
    }

    INT32 CRtcmEncoder::RtcmEncoder1127(CParam& pamIn, std::string& strOut)
    {
        INT32 iRet = RETURN_FAIL;

        CEpochObs* pEpochObs = nullptr;
        if (pamIn.GetValue(PN_PTR_GNSS_DATA_OBJECT, &pEpochObs, nullptr)
            && CheckGnssDataType(pEpochObs, IGnssDataInterface::GDT_OBS))
        {
            m_pobjLog->Trace("Rtcm start encode 1127", CLog::LL_INFO);
            const auto stSatObs = pEpochObs->GetEpochSatObs();
            iRet = EncodeMsm7(stSatObs, strOut);
        }
        else
        {
            m_pobjLog->Trace("Failed to get CEpochObs obj in RtcmEncoder1127.", CLog::LL_ERROR);
        }

        return iRet;
    }

}; // namespace sixents
