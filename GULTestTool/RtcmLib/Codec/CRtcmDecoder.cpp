
#include "CRtcmDecoder.h"
#include "../Framework/CLog.h"
#include "../Codec/CCodecUtilities.h"

#include <array>
#include <math.h>

namespace sixents
{
    using namespace std;
    using namespace sixents::common::rtcm;

    const std::map< UINT32, std::function< INT32(CRtcmDecoder&, CParam&, CParam&) > >& CRtcmDecoder::GetMsgMap()
    {
        const static std::map< UINT32, std::function< INT32(CRtcmDecoder&, CParam&, CParam&) > > mapMsg = {
            {MSG_1004, &CRtcmDecoder::RtcmDecoder1004}, {MSG_1005, &CRtcmDecoder::RtcmDecoder1005},
            {MSG_1006, &CRtcmDecoder::RtcmDecoder1006}, {MSG_1012, &CRtcmDecoder::RtcmDecoder1012},
            {MSG_1019, &CRtcmDecoder::RtcmDecoder1019}, {MSG_1020, &CRtcmDecoder::RtcmDecoder1020},
            {MSG_1033, &CRtcmDecoder::RtcmDecoder1033}, {MSG_1042, &CRtcmDecoder::RtcmDecoder1042},
            {MSG_1044, &CRtcmDecoder::RtcmDecoder1044}, {MSG_1045, &CRtcmDecoder::RtcmDecoder1045},
            {MSG_1046, &CRtcmDecoder::RtcmDecoder1046}, {MSG_1057, &CRtcmDecoder::RtcmDecoder1057},
            {MSG_1058, &CRtcmDecoder::RtcmDecoder1058}, {MSG_1059, &CRtcmDecoder::RtcmDecoder1059},
            {MSG_1060, &CRtcmDecoder::RtcmDecoder1060}, {MSG_1061, &CRtcmDecoder::RtcmDecoder1061},
            {MSG_1062, &CRtcmDecoder::RtcmDecoder1062}, {MSG_1063, &CRtcmDecoder::RtcmDecoder1063},
            {MSG_1064, &CRtcmDecoder::RtcmDecoder1064}, {MSG_1065, &CRtcmDecoder::RtcmDecoder1065},
            {MSG_1066, &CRtcmDecoder::RtcmDecoder1066}, {MSG_1067, &CRtcmDecoder::RtcmDecoder1067},
            {MSG_1068, &CRtcmDecoder::RtcmDecoder1068}, {MSG_1074, &CRtcmDecoder::RtcmDecoder1074},
            {MSG_1077, &CRtcmDecoder::RtcmDecoder1077}, {MSG_1084, &CRtcmDecoder::RtcmDecoder1084},
            {MSG_1087, &CRtcmDecoder::RtcmDecoder1087}, {MSG_1094, &CRtcmDecoder::RtcmDecoder1094},
            {MSG_1097, &CRtcmDecoder::RtcmDecoder1097}, {MSG_1114, &CRtcmDecoder::RtcmDecoder1114},
            {MSG_1117, &CRtcmDecoder::RtcmDecoder1117}, {MSG_1124, &CRtcmDecoder::RtcmDecoder1124},
            {MSG_1127, &CRtcmDecoder::RtcmDecoder1127}};

        return mapMsg;
    }

    CRtcmDecoder::CRtcmDecoder()
        : m_pobjLog(nullptr)
    {
        INT32 i32Key = 0;
        for (INT32 i = static_cast< INT32 >(IGnssDataInterface::GDT_OBS);
             i != static_cast< INT32 >(IGnssDataInterface::GDT_UNKNOW);
             ++i)
        {
            i32Key = i;
            m_mapGnssDatas.insert(std::make_pair(i32Key, nullptr));
        }
    }

    CRtcmDecoder::~CRtcmDecoder()
    {
        try
        {
            for (auto objGnssData : m_mapGnssDatas)
            {
                if (objGnssData.second != nullptr)
                {
                    delete objGnssData.second;
                    objGnssData.second = nullptr;
                }
            }

            m_mapGnssDatas.clear();

            m_objStrStream.clear();
            m_objStrStream.str("");
        }
        catch (...)
        {
            // Do nothing
        }
    }

    BOOL_T CRtcmDecoder::RtcmParseMessage(CParam& pamIn, UINT32& uiMsgType)
    {
        BOOL_T bRet = false;
        BYTE* pbyBuf = nullptr;
        UINT32 uiLen = 0U;

        do
        {
            // get length of data of CValuestd::string
            if ((pamIn.GetValue(common::rtcm::PN_BA_MESSAGE_DATA, nullptr, &uiLen) == false)
                || (uiLen < MSG_HEAD_BYTE_LENGTH + CRC24_DATA_LENGTH)
                || (uiLen >= MSG_MAX_LENGTH + MSG_HEAD_BYTE_LENGTH + CRC24_DATA_LENGTH))
            {
                break;
            }

            pbyBuf = new (std::nothrow) BYTE[static_cast< std::size_t >(uiLen)];
            if (pbyBuf == nullptr)
            {
                break;
            }

            if (pamIn.GetValue(common::rtcm::PN_BA_MESSAGE_DATA, pbyBuf, &uiLen) == false)
            {
                break;
            }

            const BYTE byData = pbyBuf[RTCM32_PREABLE_INDEX];
            if (byData != RTCM32_PREABLE)
            {
                break;
            }

            const UINT32 ui32MsgLength = GetMsgLength(pbyBuf);
            if (uiLen != (ui32MsgLength + MSG_HEAD_BYTE_LENGTH + CRC24_DATA_LENGTH))
            {
                m_objStrStream << "Invalid data buffer, BufLength: " << uiLen << ", MsgLength: " << ui32MsgLength;
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            UINT32 uiCalcCrc = 0U;
            UINT32 uiCrcInMsg = 0U;
            uiCalcCrc = sixents::CCodecUtilities::RtkCrc24q(pbyBuf, uiLen - DATA_LENGTH_3);
            uiCrcInMsg = sixents::CCodecUtilities::GetUnsignedIntBit(
                pbyBuf, (uiLen - DATA_LENGTH_3) * BYTE_TO_BIT_COUNT, DATA_LENGTH_24);
            if (uiCalcCrc != uiCrcInMsg)
            {
                break;
            }

            uiMsgType = sixents::CCodecUtilities::GetUnsignedIntBit(pbyBuf, MSG_TYPE_BIT_OFFSET, MSG_TYPE_BIT_SIZE);

            bRet = true;

        } while (false);

        if (pbyBuf != nullptr)
        {
            delete[] pbyBuf;
            pbyBuf = nullptr;
        }

        return bRet;
    }

    INT32 CRtcmDecoder::RtcmDecode(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;
        UINT32 uiMsgType = MSG_UNKNOWN;

        do
        {
            if ((pamIn.GetValue(PN_PTR_LOG_OBJECT, &m_pobjLog, nullptr) == false) || (m_pobjLog == nullptr))
            {
                break;
            }

            if (RtcmParseMessage(pamIn, uiMsgType) == false)
            {
                i32RetCode = RETURN_INVALID_PARAMETER;
                m_pobjLog->Trace("Failed to parse message.", CLog::LL_ERROR);
                break;
            }

            auto mapMsg = GetMsgMap();
            auto it = mapMsg.find(uiMsgType);
            if (it == mapMsg.end())
            {
                i32RetCode = RETURN_UNSUPPORTED_RTCM_MSG;
                m_pobjLog->Trace("Unsupported msg type: " + std::to_string(uiMsgType), sixents::CLog::LL_ERROR);
                break;
            }

            i32RetCode = (it->second)(*this, pamIn, pamOut);
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1004(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            InitStrStream("RtcmDecoder1004");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_pobjLog->Trace("Failed to get 1004 data buffer.", CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* >(objDataBuf.data());
            const UINT32 ui32BufLength = static_cast< UINT32 >(objDataBuf.size());
            const UINT32 ui32MsgLength = GetMsgLength(pDataBuf);
            if (ui32BufLength != (ui32MsgLength + MSG_HEAD_BYTE_LENGTH + CRC24_DATA_LENGTH))
            {
                m_objStrStream << "1004 Invalid data buffer, BufLength: " << ui32BufLength
                               << ", ui32MsgLength: " << ui32MsgLength;
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            SEpochSatObs stEpochSatObs;
            UINT32 nsat = 0U;
            if ((DecodeHead1004(pDataBuf, stEpochSatObs, nsat)) != RETURN_SUCCESS) //命名修改
            {
                break;
            }

            //偏移量直接偏移到电文体，跳过电文头
            UINT32 ui32Offset = MSG_HEAD_LENGTH + DATA_LENGTH_64;

            for (UINT32 i = 0U; i < nsat; i++)
            {
                SSatelliteValue sSatelliteValue;

                UINT32 satelliteNumber = 0U;
                satelliteNumber = CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_6);
                ui32Offset += DATA_LENGTH_6;

                SSignalValue signal1;

                signal1.m_ui8CodeMark =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
                ui32Offset += DATA_LENGTH_1;

                signal1.m_dbPseudoranges =
                    static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_24));
                ui32Offset += DATA_LENGTH_24;

                INT32 l1CarrierSubl1PRange = 0;
                l1CarrierSubl1PRange = CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20);
                ui32Offset += DATA_LENGTH_20;

                signal1.m_ui8LockTimeIndicator =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_7));
                ui32Offset += DATA_LENGTH_7;

                sSatelliteValue.m_ui8Milliseconds =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_8));
                ui32Offset += DATA_LENGTH_8;

                signal1.m_dbSignalCnr =
                    static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_8))
                    * SCALE_DF015;
                ui32Offset += DATA_LENGTH_8;

                SSignalValue signal2;

                signal2.m_ui8CodeMark =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_2));
                ui32Offset += DATA_LENGTH_2;

                INT32 l2Subl1PRange = 0;
                l2Subl1PRange = CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_14);
                ui32Offset += DATA_LENGTH_14;

                INT32 l2CarrierSubl1PRange = 0;
                l2CarrierSubl1PRange = CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20);
                ui32Offset += DATA_LENGTH_20;

                signal2.m_ui8LockTimeIndicator =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_7));
                ui32Offset += DATA_LENGTH_7;

                signal2.m_dbSignalCnr =
                    static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_8))
                    * SCALE_DF015;
                ui32Offset += DATA_LENGTH_8;

                signal1.m_dbPseudoranges = signal1.m_dbPseudoranges * SCALE_DF011
                                           + static_cast< DOUBLE >(sSatelliteValue.m_ui8Milliseconds) * PRUNIT_GPS;

                if (l1CarrierSubl1PRange != GNSS_INT20_INVALID_VALUE)
                {
                    signal1.m_dbPhaserange =
                        static_cast< DOUBLE >(l1CarrierSubl1PRange) * SCALE_DF012 + signal1.m_dbPseudoranges;
                }

                if (l2Subl1PRange != GNSS_INT14_INVALID_VALUE)
                {
                    signal2.m_dbPseudoranges =
                        signal1.m_dbPseudoranges + static_cast< DOUBLE >(l2Subl1PRange) * SCALE_DF017;
                }
                if (l2CarrierSubl1PRange != GNSS_INT20_INVALID_VALUE)
                {
                    signal2.m_dbPhaserange =
                        signal1.m_dbPseudoranges + static_cast< DOUBLE >(l2CarrierSubl1PRange) * SCALE_DF018;
                }

                sSatelliteValue.m_mapSignalValues.insert(pair< INT32, SSignalValue >(
                    IGnssDataInterface::SC_GPS_1C & IGnssDataInterface::SC_REMOVE_MASK, signal1));
                sSatelliteValue.m_mapSignalValues.insert(pair< INT32, SSignalValue >(
                    IGnssDataInterface::SC_GPS_2C & IGnssDataInterface::SC_REMOVE_MASK, signal2));
                stEpochSatObs.m_mapSatValues.insert(pair< INT32, SSatelliteValue >(satelliteNumber, sSatelliteValue));
            }

            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GPS;
            CEpochObs* const pGnssData =
                static_cast< CEpochObs* >(GetGnssData(enSatSys, sixents::IGnssDataInterface::GDT_OBS));
            if (pGnssData == nullptr)
            {
                m_objStrStream << "Failed to get 1004 CEpochObs object.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }
            pGnssData->SetEpochSatObs(stEpochSatObs);

            if (pamOut.AddValue(PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr) == false)
            {
                m_pobjLog->Trace("Failed to add 1004 CEpochObs object.", CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);
        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1005(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            InitStrStream("RtcmDecoder1005");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            // 解码电文
            SReferenceInfo stReferenceInfo;
            UINT32 ui32Index = MSG_HEAD_LENGTH;

            stReferenceInfo.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stReferenceInfo.m_ui16RefStaionId =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stReferenceInfo.m_ui8ItrfYear =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            stReferenceInfo.m_ui8GPSIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_ui8GlonassIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_ui8GalileoIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_ui8RefStationIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_dbArpEcefX =
                static_cast< DOUBLE >(CCodecUtilities::GetDoubleBit(pDataBuf, ui32Index)) * SCALE_1E_4;
            ui32Index += DATA_LENGTH_38;

            stReferenceInfo.m_ui8SingleROI =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_ui8BDSIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_dbArpEcefY =
                static_cast< DOUBLE >(CCodecUtilities::GetDoubleBit(pDataBuf, ui32Index)) * SCALE_1E_4;
            ui32Index += DATA_LENGTH_38;

            stReferenceInfo.m_ui8QuarterCycleIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            stReferenceInfo.m_dbArpEcefZ =
                static_cast< DOUBLE >(CCodecUtilities::GetDoubleBit(pDataBuf, ui32Index)) * SCALE_1E_4;
            ui32Index += DATA_LENGTH_38;

            // 传出参考站数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_NONE;
            if (FillDecodeResult(
                    stReferenceInfo, enSatSys, sixents::IGnssDataInterface::GDT_REF_INFO, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    } // namespace sixents

    INT32 CRtcmDecoder::RtcmDecoder1006(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1006");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            // 解码电文
            SReferenceInfo stReferenceInfo;
            UINT32 ui32Index = MSG_HEAD_LENGTH;

            stReferenceInfo.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stReferenceInfo.m_ui16RefStaionId =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stReferenceInfo.m_ui8ItrfYear =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            stReferenceInfo.m_ui8GPSIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_ui8GlonassIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_ui8GalileoIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_ui8RefStationIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_dbArpEcefX =
                static_cast< DOUBLE >(CCodecUtilities::GetDoubleBit(pDataBuf, ui32Index)) * SCALE_1E_4;
            ui32Index += DATA_LENGTH_38;

            stReferenceInfo.m_ui8SingleROI =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_ui8BDSIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stReferenceInfo.m_dbArpEcefY =
                static_cast< DOUBLE >(CCodecUtilities::GetDoubleBit(pDataBuf, ui32Index)) * SCALE_1E_4;
            ui32Index += DATA_LENGTH_38;

            stReferenceInfo.m_ui8QuarterCycleIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            stReferenceInfo.m_dbArpEcefZ =
                static_cast< DOUBLE >(CCodecUtilities::GetDoubleBit(pDataBuf, ui32Index)) * SCALE_1E_4;
            ui32Index += DATA_LENGTH_38;

            stReferenceInfo.m_dbAntennaHeight =
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_16))
                * SCALE_1E_4;
            ui32Index += DATA_LENGTH_16;

            // 传出参考站数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_NONE;
            if (FillDecodeResult(
                    stReferenceInfo, enSatSys, sixents::IGnssDataInterface::GDT_REF_INFO, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1012(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            InitStrStream("RtcmDecoder1012");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_pobjLog->Trace("Failed to get data buffer.", CLog::LL_ERROR);
                break;
            }
            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());
            const UINT32 ui32BufLength = static_cast< UINT32 >(objDataBuf.size());
            const UINT32 ui32MsgLength = GetMsgLength(pDataBuf);
            if (ui32BufLength != (ui32MsgLength + MSG_HEAD_BYTE_LENGTH + CRC24_DATA_LENGTH))
            {
                m_objStrStream << "1012 Invalid data buffer, BufLength: " << ui32BufLength
                               << ", ui32MsgLength: " << ui32MsgLength;
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }
            SEpochSatObs stEpochSatObs;
            UINT32 nsat = 0U;
            if ((DecodeHead1012(pDataBuf, stEpochSatObs, nsat)) != RETURN_SUCCESS)
            {
                break;
            }

            //偏移量直接偏移到电文体，跳过电文头
            UINT32 ui32Offset = MSG_HEAD_LENGTH + DATA_LENGTH_61;
            for (UINT32 i = 0U; i < nsat; ++i)
            {
                SSatelliteValue sSatelliteValue;

                UINT32 SatelliteNumber = 0U;
                SatelliteNumber = CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_6);
                ui32Offset += DATA_LENGTH_6;

                SSignalValue signal1;

                signal1.m_ui8CodeMark =
                    static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
                ui32Offset += DATA_LENGTH_1;

                sSatelliteValue.m_ui8SatFrequencyChannelNumber =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_5));
                ui32Offset += DATA_LENGTH_5;

                signal1.m_dbPseudoranges =
                    static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_25));
                ui32Offset += DATA_LENGTH_25;

                INT32 l1CarrierSubl1PRange = 0;
                l1CarrierSubl1PRange = CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20);
                ui32Offset += DATA_LENGTH_20;

                signal1.m_ui8LockTimeIndicator =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_7));
                ui32Offset += DATA_LENGTH_7;

                sSatelliteValue.m_ui8Milliseconds =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_7));
                ui32Offset += DATA_LENGTH_7;

                signal1.m_dbSignalCnr =
                    static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_8))
                    * SCALE_DF045;
                ui32Offset += DATA_LENGTH_8;

                SSignalValue signal2;

                signal2.m_ui8CodeMark =
                    static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_2));
                ui32Offset += DATA_LENGTH_2;

                INT32 l2Subl1PRange = 0;
                l2Subl1PRange = CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_14);
                ui32Offset += DATA_LENGTH_14;

                INT32 L2CarrierSubL1PRange = 0;
                L2CarrierSubL1PRange = CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20);
                ui32Offset += DATA_LENGTH_20;

                signal2.m_ui8LockTimeIndicator =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_7));
                ui32Offset += DATA_LENGTH_7;

                signal2.m_dbSignalCnr =
                    static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_8))
                    * SCALE_DF045;
                ui32Offset += DATA_LENGTH_8;

                signal1.m_dbPseudoranges = signal1.m_dbPseudoranges * SCALE_DF041
                                           + static_cast< DOUBLE >(sSatelliteValue.m_ui8Milliseconds) * PRUNIT_GLO;

                if (l1CarrierSubl1PRange != GNSS_INT20_INVALID_VALUE)
                {
                    signal1.m_dbPhaserange =
                        static_cast< DOUBLE >(l1CarrierSubl1PRange) * SCALE_DF042 + signal1.m_dbPseudoranges;
                }

                if (l2Subl1PRange != GNSS_INT14_INVALID_VALUE)
                {
                    signal2.m_dbPseudoranges =
                        signal1.m_dbPseudoranges + static_cast< DOUBLE >(l2Subl1PRange) * SCALE_DF047;
                }

                if (L2CarrierSubL1PRange != GNSS_INT20_INVALID_VALUE)
                {
                    signal2.m_dbPhaserange =
                        signal1.m_dbPseudoranges + static_cast< DOUBLE >(L2CarrierSubL1PRange) * SCALE_DF048;
                }

                sSatelliteValue.m_mapSignalValues.insert(pair< INT32, SSignalValue >(
                    IGnssDataInterface::SC_GLO_1C & IGnssDataInterface::SC_REMOVE_MASK, signal1));
                sSatelliteValue.m_mapSignalValues.insert(pair< INT32, SSignalValue >(
                    IGnssDataInterface::SC_GLO_2C & IGnssDataInterface::SC_REMOVE_MASK, signal2));
                stEpochSatObs.m_mapSatValues.insert(pair< INT32, SSatelliteValue >(SatelliteNumber, sSatelliteValue));
            }
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GLO;
            CEpochObs* const pGnssData =
                static_cast< CEpochObs* const >(GetGnssData(enSatSys, sixents::IGnssDataInterface::GDT_OBS));
            if (pGnssData == nullptr)
            {
                m_objStrStream << "Failed to get 1012 CEpochObs object.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }
            pGnssData->SetEpochSatObs(stEpochSatObs);

            if (pamOut.AddValue(PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr) == false)
            {
                m_pobjLog->Trace("Failed to add 1012 CEpochObs object.", CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;

        } while (false);
        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1019(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1019");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            // 解码电文
            SEphemeris stEphemeris;
            UINT32 ui32Index = MSG_HEAD_LENGTH;

            stEphemeris.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stEphemeris.m_ui8SatId =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            stEphemeris.m_ui16WeekNum =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_10));
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_ui8URA =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stEphemeris.m_ui8CodeOnL2 =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbIdot =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_14)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_14;

            stEphemeris.m_ui8Iode =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
            ui32Index += DATA_LENGTH_8;

            stEphemeris.m_ui32Toc =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2T4;
            ui32Index += DATA_LENGTH_16;

            stEphemeris.m_dbAf2 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_8)) * P2_55;
            ui32Index += DATA_LENGTH_8;

            stEphemeris.m_dbAf1 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_43;
            ui32Index += DATA_LENGTH_16;

            stEphemeris.m_dbAf0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_22)) * P2_31;
            ui32Index += DATA_LENGTH_22;

            stEphemeris.m_ui16Iodc =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_10));
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_dbCrs =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_5;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbDeltaN =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbM0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCuc =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            stEphemeris.m_dbEccentricity =
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_33;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCus =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:m1/2 需要转换成常用模式单位:m 转换方式是value * value
            stEphemeris.m_dbAHalf = std::pow(
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_19,
                SQRTM_TO_M);
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_ui32Toe = CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_16) * P2T4;
            ui32Index += DATA_LENGTH_16;

            stEphemeris.m_dbCic =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbOmega0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCis =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbI0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCrc =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_5;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbArgumentOfPerigee =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbOmegaDot =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_24)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_24;

            stEphemeris.m_dbTgd =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_8)) * P2_31;
            ui32Index += DATA_LENGTH_8;

            stEphemeris.m_ui8SvHealth =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            stEphemeris.m_ui8L2PDataFlag =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stEphemeris.m_ui8FitInterval =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));

            // 传出星历数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GPS;
            if (FillDecodeResult(stEphemeris, enSatSys, sixents::IGnssDataInterface::GDT_EPH, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1020(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1020");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            SGlonassEphemeris stGlonassEphemeris;
            // 解码电文
            UINT32 ui32Index = MSG_HEAD_LENGTH;

            stGlonassEphemeris.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stGlonassEphemeris.m_ui8SatId =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            stGlonassEphemeris.m_ui8SatFrequencyChannelNumber =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5));
            ui32Index += DATA_LENGTH_5;

            stGlonassEphemeris.m_ui8AlmanacHealth =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stGlonassEphemeris.m_ui8AHAI =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stGlonassEphemeris.m_ui8P1 =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            stGlonassEphemeris.m_ui16Tk =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stGlonassEphemeris.m_ui8MsbOfBn =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stGlonassEphemeris.m_ui8P2 =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stGlonassEphemeris.m_ui16Tb =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_7))
                * SCALE_DF110;
            ui32Index += DATA_LENGTH_7;

            // 参考 RTCM STANDARD 10403.3文档 文档中变量单位是(km/s) 需转换成(m/s)
            stGlonassEphemeris.m_dbXnTbFirstDerivative =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_24) * P2_20 * P104;
            ui32Index += DATA_LENGTH_24;

            stGlonassEphemeris.m_dbXnTb =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_27) * P2_11 * P104;
            ui32Index += DATA_LENGTH_27;

            stGlonassEphemeris.m_dbXnTbSecondDerivative =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_5) * P2_30 * P104;
            ui32Index += DATA_LENGTH_5;

            stGlonassEphemeris.m_dbYnTbFirstDerivative =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_24) * P2_20 * P104;
            ui32Index += DATA_LENGTH_24;

            stGlonassEphemeris.m_dbYnTb =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_27) * P2_11 * P104;
            ui32Index += DATA_LENGTH_27;

            stGlonassEphemeris.m_dbYnTbSecondDerivative =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_5) * P2_30 * P104;
            ui32Index += DATA_LENGTH_5;

            stGlonassEphemeris.m_dbZnTbFirstDerivative =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_24) * P2_20 * P104;
            ui32Index += DATA_LENGTH_24;

            stGlonassEphemeris.m_dbZnTb =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_27) * P2_11 * P104;
            ui32Index += DATA_LENGTH_27;

            stGlonassEphemeris.m_dbZnTbSecondDerivative =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_5) * P2_30 * P104;
            ui32Index += DATA_LENGTH_5;

            stGlonassEphemeris.m_ui8P3 =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stGlonassEphemeris.m_dbGammaTb =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_11) * P2_40;
            ui32Index += DATA_LENGTH_11;

            stGlonassEphemeris.m_ui8GmP =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            stGlonassEphemeris.m_ui8GmLn3 =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stGlonassEphemeris.m_dbTnTb =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_22) * P2_30;
            ui32Index += DATA_LENGTH_22;

            stGlonassEphemeris.m_dbGmDeltaTn =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_5) * P2_30;
            ui32Index += DATA_LENGTH_5;

            stGlonassEphemeris.m_ui8En =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5));
            ui32Index += DATA_LENGTH_5;

            stGlonassEphemeris.m_ui8GmP4 =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stGlonassEphemeris.m_ui8GmFt =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stGlonassEphemeris.m_ui16GmNt =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_11));
            ui32Index += DATA_LENGTH_11;

            stGlonassEphemeris.m_ui8GmM =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            stGlonassEphemeris.m_ui8AOAD =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stGlonassEphemeris.m_ui16NA =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_11));
            ui32Index += DATA_LENGTH_11;

            stGlonassEphemeris.m_dbTc =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_32) * P2_31;
            ui32Index += DATA_LENGTH_32;

            stGlonassEphemeris.m_ui8GmN4 =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5))
                * SCALE_DF134;
            ui32Index += DATA_LENGTH_5;

            stGlonassEphemeris.m_dbGmTGps =
                CCodecUtilities::GetSignMagnitudeIntBit(pDataBuf, ui32Index, DATA_LENGTH_22) * P2_30;
            ui32Index += DATA_LENGTH_22;

            stGlonassEphemeris.m_ui8GmLn5 =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stGlonassEphemeris.m_ui8Reserved =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_7));
            ui32Index += DATA_LENGTH_7;

            // 传出Glonass星历数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GLO;
            if (FillDecodeResult(
                    stGlonassEphemeris, enSatSys, sixents::IGnssDataInterface::GDT_GLO_EPH, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1033(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1033");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_pobjLog->Trace("Failed to get data buffer.", CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            SReferenceInfo stReferenceInfo;
            UINT32 ui32Index = MSG_HEAD_LENGTH; // 跳过包头
            stReferenceInfo.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stReferenceInfo.m_ui16RefStaionId =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stReferenceInfo.m_ui8DescriptorCount =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
            ui32Index += DATA_LENGTH_8;

            for (UINT8 i = 0U; i < stReferenceInfo.m_ui8DescriptorCount; ++i)
            {
                stReferenceInfo.m_objAntennaDescriptor[static_cast< std::size_t >(i)] =
                    static_cast< INT8 >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
                ui32Index += DATA_LENGTH_8;
            }

            stReferenceInfo.m_ui8AntennaSetupId =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
            ui32Index += DATA_LENGTH_8;

            stReferenceInfo.m_ui8SerialNumberCount =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
            ui32Index += DATA_LENGTH_8;

            for (UINT8 i = 0U; i < stReferenceInfo.m_ui8SerialNumberCount; ++i)
            {
                stReferenceInfo.m_objAntennaSerialNumber[static_cast< std::size_t >(i)] =
                    static_cast< INT8 >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
                ui32Index += DATA_LENGTH_8;
            }

            stReferenceInfo.m_ui8RTDC =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
            ui32Index += DATA_LENGTH_8;

            for (UINT8 i = 0U; i < stReferenceInfo.m_ui8RTDC; ++i)
            {
                stReferenceInfo.m_objReceiverTypeDescriptor[static_cast< std::size_t >(i)] =
                    static_cast< INT8 >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
                ui32Index += DATA_LENGTH_8;
            }

            stReferenceInfo.m_ui8RFVC =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
            ui32Index += DATA_LENGTH_8;

            for (UINT8 i = 0U; i < stReferenceInfo.m_ui8RFVC; ++i)
            {
                stReferenceInfo.m_objReceiverFirmwareVersion[static_cast< std::size_t >(i)] =
                    static_cast< INT8 >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
                ui32Index += DATA_LENGTH_8;
            }

            stReferenceInfo.m_ui8ReceiverSerialNumberCount =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
            ui32Index += DATA_LENGTH_8;

            for (UINT8 i = 0U; i < stReferenceInfo.m_ui8ReceiverSerialNumberCount; ++i)
            {
                stReferenceInfo.m_objReceiverSerialNumber[static_cast< std::size_t >(i)] =
                    static_cast< INT8 >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
                ui32Index += DATA_LENGTH_8;
            }

            // 传出参考站数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_NONE;
            if (FillDecodeResult(
                    stReferenceInfo, enSatSys, sixents::IGnssDataInterface::GDT_REF_INFO, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1042(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1042");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            // 解码电文
            SEphemeris stEphemeris;
            UINT32 ui32Index = MSG_HEAD_LENGTH;

            stEphemeris.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stEphemeris.m_ui8SatId =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            stEphemeris.m_ui16WeekNum =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_13));
            ui32Index += DATA_LENGTH_13;

            stEphemeris.m_ui8URA =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbIdot =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_14)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_14;

            stEphemeris.m_ui8AgeOfDataEphemeris =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5));
            ui32Index += DATA_LENGTH_5;

            stEphemeris.m_ui32Toc =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_17))
                * SCALE_DF493;
            ui32Index += DATA_LENGTH_17;

            stEphemeris.m_dbAf2 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_11)) * P2_66;
            ui32Index += DATA_LENGTH_11;

            stEphemeris.m_dbAf1 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_22)) * P2_50;
            ui32Index += DATA_LENGTH_22;

            stEphemeris.m_dbAf0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_24)) * P2_33;
            ui32Index += DATA_LENGTH_24;

            stEphemeris.m_ui8AgeOfDataClock =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5));
            ui32Index += DATA_LENGTH_5;

            stEphemeris.m_dbCrs =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_18)) * P2_6;
            ui32Index += DATA_LENGTH_18;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbDeltaN =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbM0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCuc =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_18)) * P2_31;
            ui32Index += DATA_LENGTH_18;

            stEphemeris.m_dbEccentricity =
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_33;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCus =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_18)) * P2_31;
            ui32Index += DATA_LENGTH_18;

            // 参考RTCM STANDARD 10403.3数据单位:m1/2 需要转换成常用模式单位:m 转换方式是value * value
            stEphemeris.m_dbAHalf = std::pow(
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_19,
                SQRTM_TO_M);
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_ui32Toe =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_17) * SCALE_DF505;
            ui32Index += DATA_LENGTH_17;

            stEphemeris.m_dbCic =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_18)) * P2_31;
            ui32Index += DATA_LENGTH_18;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbOmega0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCis =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_18)) * P2_31;
            ui32Index += DATA_LENGTH_18;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbI0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCrc =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_18)) * P2_6;
            ui32Index += DATA_LENGTH_18;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbArgumentOfPerigee =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbOmegaDot =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_24)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_24;

            stEphemeris.m_dbTgd1 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_10)) * SCALE_1E_1;
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_dbTgd2 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_10)) * SCALE_1E_1;
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_ui8SvHealth =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            // 传出星历数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_CMP;
            if (FillDecodeResult(stEphemeris, enSatSys, sixents::IGnssDataInterface::GDT_EPH, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1044(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            InitStrStream("RtcmDecoder1044");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }
            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            // 解码电文
            SEphemeris stEphemeris;
            UINT32 ui32Index = MSG_HEAD_LENGTH;

            stEphemeris.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stEphemeris.m_ui8SatId =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stEphemeris.m_ui32Toc =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2T4;
            ui32Index += DATA_LENGTH_16;

            stEphemeris.m_dbAf2 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_8)) * P2_55;
            ui32Index += DATA_LENGTH_8;

            stEphemeris.m_dbAf1 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_43;
            ui32Index += DATA_LENGTH_16;

            stEphemeris.m_dbAf0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_22)) * P2_31;
            ui32Index += DATA_LENGTH_22;

            stEphemeris.m_ui8Iode =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
            ui32Index += DATA_LENGTH_8;

            stEphemeris.m_dbCrs =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_5;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbDeltaN =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbM0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCuc =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            stEphemeris.m_dbEccentricity =
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_33;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCus =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:m1/2 需要转换成常用模式单位:m 转换方式是value * value
            stEphemeris.m_dbAHalf = std::pow(
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_19,
                SQRTM_TO_M);
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_ui32Toe = CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_16) * P2T4;
            ui32Index += DATA_LENGTH_16;

            stEphemeris.m_dbCic =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbOmega0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCis =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbI0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCrc =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_5;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbArgumentOfPerigee =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbOmegaDot =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_24)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_24;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbIODot =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_14)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_14;

            stEphemeris.m_ui8CodeOnL2 =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            stEphemeris.m_ui16WeekNum =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_10));
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_ui8URA =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stEphemeris.m_ui8SvHealth =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            stEphemeris.m_dbTgd =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_8)) * P2_31;
            ui32Index += DATA_LENGTH_8;

            stEphemeris.m_ui16Iodc =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_10));
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_ui8FitInterval =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            // 传出星历数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_QZS;
            if (FillDecodeResult(stEphemeris, enSatSys, sixents::IGnssDataInterface::GDT_EPH, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1045(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1045");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            // 解码电文
            SEphemeris stEphemeris;
            UINT32 ui32Index = MSG_HEAD_LENGTH;

            stEphemeris.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stEphemeris.m_ui8SatId =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            stEphemeris.m_ui16WeekNum =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stEphemeris.m_ui16IODnav =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_10));
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_ui8SvSisa =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
            ui32Index += DATA_LENGTH_8;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbIdot =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_14)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_14;

            stEphemeris.m_ui32Toc =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_14))
                * SCALE_DF293;
            ui32Index += DATA_LENGTH_14;

            stEphemeris.m_dbAf2 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_6)) * P2_59;
            ui32Index += DATA_LENGTH_6;

            stEphemeris.m_dbAf1 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_21)) * P2_46;
            ui32Index += DATA_LENGTH_21;

            stEphemeris.m_dbAf0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_31)) * P2_34;
            ui32Index += DATA_LENGTH_31;

            stEphemeris.m_dbCrs =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_5;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbDeltaN =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbM0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCuc =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            stEphemeris.m_dbEccentricity =
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_33;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCus =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:m1/2 需要转换成常用模式单位:m 转换方式是value * value
            stEphemeris.m_dbAHalf = std::pow(
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_19,
                SQRTM_TO_M);
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_ui32Toe =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_14) * SCALE_DF304;
            ui32Index += DATA_LENGTH_14;

            stEphemeris.m_dbCic =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbOmega0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCis =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbI0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCrc =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_5;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbArgumentOfPerigee =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbOmegaDot =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_24)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_24;

            stEphemeris.m_dbBgdE1E5a =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_10)) * P2_32;
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_ui8OSHS =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            stEphemeris.m_ui8OSDVS =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stEphemeris.m_ui8Reserved =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_7));
            ui32Index += DATA_LENGTH_7;

            // 传出星历数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GAL;
            if (FillDecodeResult(stEphemeris, enSatSys, sixents::IGnssDataInterface::GDT_EPH, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1046(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1046");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            // 解码电文
            SEphemeris stEphemeris;
            UINT32 ui32Index = MSG_HEAD_LENGTH;

            stEphemeris.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stEphemeris.m_ui8SatId =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            stEphemeris.m_ui16WeekNum =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stEphemeris.m_ui16IODnav =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_10));
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_ui8SISAIndex =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_8));
            ui32Index += DATA_LENGTH_8;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbIdot =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_14)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_14;

            stEphemeris.m_ui32Toc =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_14))
                * SCALE_DF293;
            ui32Index += DATA_LENGTH_14;

            stEphemeris.m_dbAf2 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_6)) * P2_59;
            ui32Index += DATA_LENGTH_6;

            stEphemeris.m_dbAf1 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_21)) * P2_46;
            ui32Index += DATA_LENGTH_21;

            stEphemeris.m_dbAf0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_31)) * P2_34;
            ui32Index += DATA_LENGTH_31;

            stEphemeris.m_dbCrs =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_5;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbDeltaN =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbM0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCuc =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            stEphemeris.m_dbEccentricity =
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_33;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCus =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:m1/2 需要转换成常用模式单位:m 转换方式是value * value
            stEphemeris.m_dbAHalf = std::pow(
                static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_19,
                SQRTM_TO_M);
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_ui32Toe =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_14) * SCALE_DF304;
            ui32Index += DATA_LENGTH_14;

            stEphemeris.m_dbCic =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbOmega0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCis =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_29;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbI0 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            stEphemeris.m_dbCrc =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_16)) * P2_5;
            ui32Index += DATA_LENGTH_16;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles 需要转换成常用模式单位:deg 转换方式是value * SC2RAD
            stEphemeris.m_dbArgumentOfPerigee =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_32)) * P2_31 * SC2RAD;
            ui32Index += DATA_LENGTH_32;

            // 参考RTCM STANDARD 10403.3数据单位:semicircles/s 需要转换成常用模式单位:deg/s 转换方式是value * SC2RAD
            stEphemeris.m_dbOmegaDot =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_24)) * P2_43 * SC2RAD;
            ui32Index += DATA_LENGTH_24;

            stEphemeris.m_dbBgdE1E5a =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_10)) * P2_32;
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_dbBgdE5bE1 =
                static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_10)) * P2_32;
            ui32Index += DATA_LENGTH_10;

            stEphemeris.m_ui8E5bSignalHealthStatus =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            stEphemeris.m_ui8E5bDataValidityStatus =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stEphemeris.m_ui8E1bSignalHealthStatus =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            stEphemeris.m_ui8E1bDataValidityStatus =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stEphemeris.m_ui8Reserved =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            // 传出星历数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GAL;
            if (FillDecodeResult(stEphemeris, enSatSys, sixents::IGnssDataInterface::GDT_EPH, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1057(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            InitStrStream("RtcmDecoder1057");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to  get 1057 data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            SOrbitCorrection sOrbitCorrection;
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GPS;
            if (DecodeSSR1(pDataBuf, enSatSys, sOrbitCorrection) != RETURN_SUCCESS)
            {
                m_objStrStream << "1057 DecodeSSR1 Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            if (FillDecodeResult(
                    sOrbitCorrection, enSatSys, sixents::IGnssDataInterface::GDT_ORBIT, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }
            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1058(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1058");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get 1058 data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            SClockCorrection sClockCorrection;
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GPS;
            if (DecodeSSR2(pDataBuf, enSatSys, sClockCorrection) != RETURN_SUCCESS)
            {
                m_objStrStream << "1058 DecodeSSR2 Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            if (FillDecodeResult(
                    sClockCorrection, enSatSys, sixents::IGnssDataInterface::GDT_CLOCK, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1059(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1059");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            // 解码电文头
            SDcb stDcb;
            UINT32 ui32Index = MSG_HEAD_LENGTH;
            stDcb.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stDcb.m_ui32EpochTime =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_20));
            ui32Index += DATA_LENGTH_20;

            stDcb.m_ui32SSRUpdateInterval =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stDcb.m_ui8MulMsgIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stDcb.m_ui8IodSsr =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stDcb.m_ui32SsrProviderID =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_16));
            ui32Index += DATA_LENGTH_16;

            stDcb.m_ui8SsrSolutionID =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stDcb.m_ui8SatNum =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            // 电文体，解析卫星数据
            for (UINT8 i = 0U; i != stDcb.m_ui8SatNum; ++i)
            {
                SDcbSatInfo stDcbSatInfo;
                stDcbSatInfo.m_ui8SatId =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
                ui32Index += DATA_LENGTH_6;

                stDcbSatInfo.m_ui8SsrUraNum =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5));
                ui32Index += DATA_LENGTH_5;

                // 解析码偏差数据
                UINT8 ui8Key = 0U;
                for (UINT8 j = 1U; j <= stDcbSatInfo.m_ui8SsrUraNum; ++j)
                {
                    ui8Key = j;
                    SDcbInfo stDcbInfo;
                    stDcbInfo.m_ui8SignalTrackingModeIndicator =
                        static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5));
                    ui32Index += DATA_LENGTH_5;

                    stDcbInfo.m_dbCodeBias =
                        static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_14))
                        * SCALE_1E_2;
                    ui32Index += DATA_LENGTH_14;

                    // 保存码偏差数据
                    stDcbSatInfo.m_mapDcbInfo.insert(make_pair(ui8Key, std::move(stDcbInfo)));
                }

                // 保存卫星数据
                stDcb.m_mapDcbSatInfo.insert(make_pair(stDcbSatInfo.m_ui8SatId, std::move(stDcbSatInfo)));
            }

            // 传出轨道改正参数数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GPS;
            if (FillDecodeResult(stDcb, enSatSys, sixents::IGnssDataInterface::GDT_DCB, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1060(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1060");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get 1060 data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            SOrbitClockCorrection sOrbitClockCorrection;
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GPS;
            if (DecodeSSR4(pDataBuf, enSatSys, sOrbitClockCorrection) != RETURN_SUCCESS)
            {
                m_objStrStream << "1060 DecodeSSR4 Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            if (FillDecodeResult(sOrbitClockCorrection,
                                 enSatSys,
                                 sixents::IGnssDataInterface::GDT_ORBIT_CLOCK,
                                 m_objStrStream,
                                 pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1061(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1061");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            // 解码电文头
            SUra stUra;
            UINT32 ui32Index = MSG_HEAD_LENGTH;
            stUra.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stUra.m_ui32EpochTime =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_20));
            ui32Index += DATA_LENGTH_20;

            stUra.m_ui32SSRUpdateInterval =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stUra.m_ui8MulMsgIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stUra.m_ui8IodSsr =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stUra.m_ui32SsrProviderID =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_16));
            ui32Index += DATA_LENGTH_16;

            stUra.m_ui8SsrSolutionID =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stUra.m_ui8SatNum =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            // 电文体，解析卫星数据
            for (UINT8 i = 0U; i != stUra.m_ui8SatNum; ++i)
            {
                SUraInfo stUraInfo;
                stUraInfo.m_ui8SatId =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
                ui32Index += DATA_LENGTH_6;

                stUraInfo.m_ui8SsrUra =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
                ui32Index += DATA_LENGTH_6;

                // 保存卫星数据
                stUra.m_mapUraInfo.insert(make_pair(stUraInfo.m_ui8SatId, std::move(stUraInfo)));
            }

            // 传出URA数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GPS;
            if (FillDecodeResult(stUra, enSatSys, sixents::IGnssDataInterface::GDT_URA, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1062(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1062");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get 1062 data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            SClockCorrection sClockCorrection;
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GPS;
            if (DecodeSSR2(pDataBuf, enSatSys, sClockCorrection) != RETURN_SUCCESS)
            {
                m_objStrStream << "1062 DecodeSSR2 Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            if (FillDecodeResult(
                    sClockCorrection, enSatSys, sixents::IGnssDataInterface::GDT_CLOCK, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1063(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1063");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get 1063 data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            SOrbitCorrection sOrbitCorrection;
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GLO;
            if (DecodeSSR1(pDataBuf, enSatSys, sOrbitCorrection) != RETURN_SUCCESS)
            {
                m_objStrStream << "1063 DecodeSSR1 Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            if (FillDecodeResult(
                    sOrbitCorrection, enSatSys, sixents::IGnssDataInterface::GDT_ORBIT, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1064(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1064");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get 1064 data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* >(objDataBuf.data());

            SClockCorrection sClockCorrection;
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GLO;
            if (DecodeSSR2(pDataBuf, enSatSys, sClockCorrection) != RETURN_SUCCESS)
            {
                m_objStrStream << "1064 DecodeSSR2 Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            if (FillDecodeResult(
                    sClockCorrection, enSatSys, sixents::IGnssDataInterface::GDT_CLOCK, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }
            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1065(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1065");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            // 解码电文头
            SDcb stDcb;
            UINT32 ui32Index = MSG_HEAD_LENGTH;
            stDcb.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stDcb.m_ui32EpochTime =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_17));
            ui32Index += DATA_LENGTH_17;

            stDcb.m_ui32SSRUpdateInterval =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stDcb.m_ui8MulMsgIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stDcb.m_ui8IodSsr =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stDcb.m_ui32SsrProviderID =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_16));
            ui32Index += DATA_LENGTH_16;

            stDcb.m_ui8SsrSolutionID =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stDcb.m_ui8SatNum =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            // 电文体，解析卫星数据
            for (UINT8 i = 0U; i != stDcb.m_ui8SatNum; ++i)
            {
                SDcbSatInfo stDcbSatInfo;
                stDcbSatInfo.m_ui8SatId =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5));
                ui32Index += DATA_LENGTH_5;

                stDcbSatInfo.m_ui8SsrUraNum =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5));
                ui32Index += DATA_LENGTH_5;

                // 解析码偏差数据
                UINT8 ui8Key = 0U;
                for (UINT8 j = 1U; j <= stDcbSatInfo.m_ui8SsrUraNum; ++j)
                {
                    ui8Key = j;
                    SDcbInfo stDcbInfo;
                    stDcbInfo.m_ui8SignalTrackingModeIndicator =
                        static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5));
                    ui32Index += DATA_LENGTH_5;

                    stDcbInfo.m_dbCodeBias =
                        static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index, DATA_LENGTH_14))
                        * SCALE_1E_2;
                    ui32Index += DATA_LENGTH_14;

                    // 保存码偏差数据
                    stDcbSatInfo.m_mapDcbInfo.insert(make_pair(ui8Key, std::move(stDcbInfo)));
                }

                // 保存卫星数据
                stDcb.m_mapDcbSatInfo.insert(make_pair(stDcbSatInfo.m_ui8SatId, std::move(stDcbSatInfo)));
            }

            // 传出轨道改正参数数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GLO;
            if (FillDecodeResult(stDcb, enSatSys, sixents::IGnssDataInterface::GDT_DCB, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1066(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1066");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get 1066 data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            SOrbitClockCorrection sOrbitClockCorrection;
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GLO;
            if (DecodeSSR4(pDataBuf, enSatSys, sOrbitClockCorrection) != RETURN_SUCCESS)
            {
                m_objStrStream << "1066 DecodeSSR4 Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            if (FillDecodeResult(sOrbitClockCorrection,
                                 enSatSys,
                                 sixents::IGnssDataInterface::GDT_ORBIT_CLOCK,
                                 m_objStrStream,
                                 pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1067(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1067");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* >(objDataBuf.data());

            // 解码电文头
            SUra stUra;
            UINT32 ui32Index = MSG_HEAD_LENGTH;
            stUra.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            stUra.m_ui32EpochTime =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_17));
            ui32Index += DATA_LENGTH_17;

            stUra.m_ui32SSRUpdateInterval =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stUra.m_ui8MulMsgIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            stUra.m_ui8IodSsr =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stUra.m_ui32SsrProviderID =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_16));
            ui32Index += DATA_LENGTH_16;

            stUra.m_ui8SsrSolutionID =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_4));
            ui32Index += DATA_LENGTH_4;

            stUra.m_ui8SatNum =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
            ui32Index += DATA_LENGTH_6;

            // 电文体，解析卫星数据
            for (UINT8 i = 0U; i != stUra.m_ui8SatNum; ++i)
            {
                SUraInfo stUraInfo;
                stUraInfo.m_ui8SatId =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_5));
                ui32Index += DATA_LENGTH_5;

                stUraInfo.m_ui8SsrUra =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_6));
                ui32Index += DATA_LENGTH_6;

                // 保存卫星数据
                stUra.m_mapUraInfo.insert(make_pair(stUraInfo.m_ui8SatId, std::move(stUraInfo)));
            }

            // 传出URA数据
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GLO;
            if (FillDecodeResult(stUra, enSatSys, sixents::IGnssDataInterface::GDT_URA, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1068(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1068");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get 1068 data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* >(objDataBuf.data());

            SClockCorrection sClockCorrection;
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GLO;
            if (DecodeSSR2(pDataBuf, enSatSys, sClockCorrection) != RETURN_SUCCESS)
            {
                m_objStrStream << "1068 DecodeSSR2 Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            if (FillDecodeResult(
                    sClockCorrection, enSatSys, sixents::IGnssDataInterface::GDT_CLOCK, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }
            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1074(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1074");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());

            SEpochSatObs stEpochSatObs;
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GPS;
            if (DecodeMsm4(pDataBuf, enSatSys, stEpochSatObs) != RETURN_SUCCESS)
            {
                break;
            }

            // 传出观测值数据
            if (FillDecodeResult(stEpochSatObs, enSatSys, sixents::IGnssDataInterface::GDT_OBS, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1077(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1077");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GPS;
            SEpochSatObs stEpochSatObs;
            if (DecodeMsm7(pDataBuf, enSatSys, stEpochSatObs) != RETURN_SUCCESS)
            {
                break;
            }

            // 传出观测值数据
            if (FillDecodeResult(stEpochSatObs, enSatSys, sixents::IGnssDataInterface::GDT_OBS, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1084(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1084");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_pobjLog->Trace("Failed to get data buffer.", CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GLO;
            SEpochSatObs stEpochSatObs;
            if (DecodeMsm4(pDataBuf, enSatSys, stEpochSatObs) != RETURN_SUCCESS)
            {
                break;
            }

            // 传出观测值数据
            if (FillDecodeResult(stEpochSatObs, enSatSys, sixents::IGnssDataInterface::GDT_OBS, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1087(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1087");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GLO;
            SEpochSatObs stEpochSatObs;
            if (DecodeMsm7(pDataBuf, enSatSys, stEpochSatObs) != RETURN_SUCCESS)
            {
                break;
            }

            // 传出观测值数据
            if (FillDecodeResult(stEpochSatObs, enSatSys, sixents::IGnssDataInterface::GDT_OBS, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1094(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1094");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GAL;
            SEpochSatObs stEpochSatObs;
            if (DecodeMsm4(pDataBuf, enSatSys, stEpochSatObs) != RETURN_SUCCESS)
            {
                break;
            }

            // 传出观测值数据
            if (FillDecodeResult(stEpochSatObs, enSatSys, sixents::IGnssDataInterface::GDT_OBS, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1097(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1097");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_GAL;
            SEpochSatObs stEpochSatObs;
            if (DecodeMsm7(pDataBuf, enSatSys, stEpochSatObs) != RETURN_SUCCESS)
            {
                break;
            }

            // 传出观测值数据
            if (FillDecodeResult(stEpochSatObs, enSatSys, sixents::IGnssDataInterface::GDT_OBS, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1114(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1114");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_QZS;
            SEpochSatObs stEpochSatObs;
            if (DecodeMsm4(pDataBuf, enSatSys, stEpochSatObs) != RETURN_SUCCESS)
            {
                break;
            }

            // 传出观测值数据
            if (FillDecodeResult(stEpochSatObs, enSatSys, sixents::IGnssDataInterface::GDT_OBS, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1117(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1117");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_QZS;
            SEpochSatObs stEpochSatObs;
            if (DecodeMsm7(pDataBuf, enSatSys, stEpochSatObs) != RETURN_SUCCESS)
            {
                break;
            }

            // 传出观测值数据
            if (FillDecodeResult(stEpochSatObs, enSatSys, sixents::IGnssDataInterface::GDT_OBS, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1124(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1124");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer.";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_CMP;
            SEpochSatObs stEpochSatObs;
            if (DecodeMsm4(pDataBuf, enSatSys, stEpochSatObs) != RETURN_SUCCESS)
            {
                break;
            }

            // 传出观测值数据
            if (FillDecodeResult(stEpochSatObs, enSatSys, sixents::IGnssDataInterface::GDT_OBS, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::RtcmDecoder1127(CParam& pamIn, CParam& pamOut)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            InitStrStream("RtcmDecoder1127");
            std::string objDataBuf;
            if ((pamIn.GetValue(PN_BA_MESSAGE_DATA, &objDataBuf, nullptr) == false))
            {
                m_objStrStream << "Failed to get data buffer";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            const UINT8* const pDataBuf = reinterpret_cast< const UINT8* const >(objDataBuf.data());
            const IGnssDataInterface::SatelliteSystem enSatSys = IGnssDataInterface::SYS_CMP;
            SEpochSatObs stEpochSatObs;
            if (DecodeMsm7(pDataBuf, enSatSys, stEpochSatObs) != RETURN_SUCCESS)
            {
                break;
            }

            // 传出观测值数据
            if (FillDecodeResult(stEpochSatObs, enSatSys, sixents::IGnssDataInterface::GDT_OBS, m_objStrStream, pamOut)
                != RETURN_SUCCESS)
            {
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeMsm4(const UINT8* const pDataBuf,
                                   const IGnssDataInterface::SatelliteSystem enSatSystem,
                                   SEpochSatObs& stEpochSatObs)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            // 解析电文头
            UINT32 ui32Index = 0U;
            UINT32 ui32SatelliteNum = 0U;
            UINT32 ui32SignalNum = 0U;
            UINT32 ui32CellNum = 0U;
            UINT64 ui64CellLength = 0U;
            array< UINT32, MAX_SATELLITE_NUM > objSatelliteIds = {};
            array< UINT32, MAX_SIGNAL_NUM > objSignalIds = {};
            array< UINT32, MAX_CELL_NUM > objCellNum = {};
            if (DecodeMsmHead(pDataBuf,
                              enSatSystem,
                              stEpochSatObs,
                              ui32Index,
                              ui32SatelliteNum,
                              ui32SignalNum,
                              ui32CellNum,
                              ui64CellLength,
                              objSatelliteIds,
                              objSignalIds,
                              objCellNum)
                != RETURN_SUCCESS)
            {
                break;
            }

            // 解析卫星数据
            if (DecodeMsm4SatData(pDataBuf, stEpochSatObs, ui32Index, ui32SatelliteNum, objSatelliteIds)
                != RETURN_SUCCESS)
            {
                break;
            }

            // 解析信号数据
            if (DecodeMsm4SigData(pDataBuf,
                                  stEpochSatObs,
                                  ui32Index,
                                  ui32SignalNum,
                                  ui32CellNum,
                                  ui64CellLength,
                                  objSatelliteIds,
                                  objSignalIds,
                                  objCellNum)
                != RETURN_SUCCESS)
            {
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeMsm7(const UINT8* const pDataBuf,
                                   const IGnssDataInterface::SatelliteSystem enSatSystem,
                                   SEpochSatObs& stEpochSatObs)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            // 解析电文头
            UINT32 ui32Index = 0U;
            UINT32 ui32SatelliteNum = 0U;
            UINT32 ui32SignalNum = 0U;
            UINT32 ui32CellNum = 0U;
            UINT64 ui64CellLength = 0U;
            array< UINT32, MAX_SATELLITE_NUM > objSatelliteIds = {};
            array< UINT32, MAX_SIGNAL_NUM > objSignalIds = {};
            array< UINT32, MAX_CELL_NUM > objCellNum = {};
            if (DecodeMsmHead(pDataBuf,
                              enSatSystem,
                              stEpochSatObs,
                              ui32Index,
                              ui32SatelliteNum,
                              ui32SignalNum,
                              ui32CellNum,
                              ui64CellLength,
                              objSatelliteIds,
                              objSignalIds,
                              objCellNum)
                != RETURN_SUCCESS)
            {
                break;
            }

            // 解析卫星数据
            if (DecodeMsm7SatData(pDataBuf, stEpochSatObs, ui32Index, ui32SatelliteNum, objSatelliteIds)
                != RETURN_SUCCESS)
            {
                break;
            }

            // 解析信号数据
            if (DecodeMsm7SigData(pDataBuf,
                                  stEpochSatObs,
                                  ui32Index,
                                  ui32SignalNum,
                                  ui32CellNum,
                                  ui64CellLength,
                                  objSatelliteIds,
                                  objSignalIds,
                                  objCellNum)
                != RETURN_SUCCESS)
            {
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeMsmHead(const UINT8* const pDataBuf,
                                      const IGnssDataInterface::SatelliteSystem enSatSystem,
                                      SEpochSatObs& stEpochSatObs,
                                      UINT32& ui32Index,
                                      UINT32& ui32SatelliteNum,
                                      UINT32& ui32SignalNum,
                                      UINT32& ui32CellNum,
                                      UINT64& ui64CellLength,
                                      array< UINT32, MAX_SATELLITE_NUM >& objSatelliteIds,
                                      array< UINT32, MAX_SIGNAL_NUM >& objSignalIds,
                                      array< UINT32, MAX_CELL_NUM >& objCellNum)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            ui32Index = MSG_HEAD_LENGTH;
            // DF002: 电文类型号,用于区分差分电文。
            stEpochSatObs.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, MSG_HEAD_LENGTH, DATA_LENGTH_12));
            ui32Index += DATA_LENGTH_12;

            // DF003: 参考站 ID 由服务提供者确定。
            stEpochSatObs.m_ui32GmNtiRefStationID =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_12);
            ui32Index += DATA_LENGTH_12;

            // GNSS
            // 历元时刻：Glonass忽略前面3位，取后面27位，其他系统取30位，然后乘以比例因子0.001
            if (enSatSystem == IGnssDataInterface::SYS_GLO)
            {
                stEpochSatObs.m_ui8DayOfWeek =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_3));
                ui32Index += DATA_LENGTH_3;

                stEpochSatObs.m_ui32GnssEpochTime =
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_27);
                ui32Index += DATA_LENGTH_27;
            }

            else
            {
                stEpochSatObs.m_ui32GnssEpochTime =
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_30);
                ui32Index += DATA_LENGTH_30;
            }

            // DF393: MSM 后续电文情况。
            stEpochSatObs.m_ui8MultiMsgBit =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            // DF409: 表示测站数据期卷号
            stEpochSatObs.m_ui8IODS =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_3));
            ui32Index += DATA_LENGTH_3;

            // 保留7位
            stEpochSatObs.m_i8Reserved =
                static_cast< INT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_7));
            ui32Index += DATA_LENGTH_7;

            // DF411: 时钟校准标志
            stEpochSatObs.m_ui8ClockSteeringIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            // DF412: 扩展时钟标志
            stEpochSatObs.m_ui8ExternalClockIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_2));
            ui32Index += DATA_LENGTH_2;

            // DF417: GNSS 平滑类型标志
            stEpochSatObs.m_ui8GnssSmoothingIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1));
            ui32Index += DATA_LENGTH_1;

            // DF418: GNSS 平滑区间
            stEpochSatObs.m_ui8GnssSmoothingInterval =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_3));
            ui32Index += DATA_LENGTH_3;

            // DF394: 卫星掩码
            stEpochSatObs.m_ui64SatMask = CCodecUtilities::GetUnsignedInt64Bit(pDataBuf, ui32Index, DATA_LENGTH_64);
            // 卫星数量
            UINT32 ui32Mask = 0U;
            for (UINT32 i = 1U; i <= MAX_SATELLITE_NUM; ++i)
            {
                ui32Mask = CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1);
                ui32Index += DATA_LENGTH_1;
                if (ui32Mask != 0U)
                {
                    objSatelliteIds[static_cast< std::size_t >(ui32SatelliteNum)] = i;
                    ++ui32SatelliteNum;
                }
            }

            // DF395: 信号掩码
            stEpochSatObs.m_ui32SignalMask = CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_32);
            // 信号数量
            ui32Mask = 0U;
            for (UINT32 i = 1U; i <= MAX_SIGNAL_NUM; ++i)
            {
                ui32Mask = CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1);
                ui32Index += DATA_LENGTH_1;
                if (ui32Mask != 0U)
                {
                    objSignalIds[static_cast< std::size_t >(ui32SignalNum)] = i;
                    ++ui32SignalNum;
                }
            }

            // 确保电文符合标准传输要求，保证单元数据长度不能超过64
            ui64CellLength = static_cast< UINT64 >(ui32SatelliteNum) * static_cast< UINT64 >(ui32SignalNum);
            if (ui64CellLength > MAX_CELL_NUM)
            {
                m_objStrStream << "rtcm3 " << stEpochSatObs.m_ui16MsgType
                               << "number of sats and sigs error: nsat=" << ui32SatelliteNum
                               << " nsig= " << ui32SignalNum << "\n";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            // DF395: 单元掩码
            stEpochSatObs.m_ui64CellMask =
                CCodecUtilities::GetUnsignedInt64Bit(pDataBuf, ui32Index, static_cast< UINT32 >(ui64CellLength));

            for (UINT64 i = 0U; i != ui64CellLength; ++i)
            {
                objCellNum[i] = CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index, DATA_LENGTH_1);
                ui32Index += DATA_LENGTH_1;
                if (objCellNum[i] != 0U)
                {
                    ++ui32CellNum;
                }
            }

            // 确保电文长度满足要求
            const UINT32 ui32MsgLength = GetMsgLength(pDataBuf);
            if ((ui32Index + ui32SatelliteNum * MSM4_SAT_DATA_LENGTH + ui32CellNum * MSM4_SIG_DATA_LENGTH
                 - MSG_HEAD_LENGTH)
                > (ui32MsgLength * BYTE_TO_BIT_COUNT))
            {
                m_objStrStream << "rtcm3 " << stEpochSatObs.m_ui16MsgType << " length error: len=" << ui32MsgLength
                               << " nsat=" << ui32SatelliteNum << " ncell= " << ui32CellNum << " len=" << ui32MsgLength
                               << "\n";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeMsm4SatData(const UINT8* const pDataBuf,
                                          SEpochSatObs& stEpochSatObs,
                                          UINT32& ui32Index,
                                          const UINT32& ui32SatelliteNum,
                                          const array< UINT32, common::rtcm::MAX_SATELLITE_NUM >& objSatelliteIds)
    {
        m_pobjLog->Trace("Enter function DecodeMsm4SatData.", CLog::LL_DEBUG);
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            UINT32 ui32Offset = 0U;
            SSatelliteValue stSatellite;
            // 为了避免多次循环，所以在循环内通过偏移分别解析每个数据
            for (UINT32 i = 0U; i != ui32SatelliteNum; ++i)
            {
                // 卫星概略距离的整毫秒数
                ui32Offset = i * DATA_LENGTH_8;
                stSatellite.m_ui8Milliseconds = static_cast< UINT8 >(
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_8));

                // 卫星概略距离的毫秒余数
                ui32Offset = ui32SatelliteNum * DATA_LENGTH_8 + i * DATA_LENGTH_10;
                stSatellite.m_dbModulo1Millisecond = static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(
                                                         pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_10))
                                                     * P2_10;

                // 插入卫星数据
                stEpochSatObs.m_mapSatValues.insert(
                    make_pair(objSatelliteIds[static_cast< std::size_t >(i)], stSatellite));
            }

            ui32Index += ui32SatelliteNum * (DATA_LENGTH_18);
            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeMsm4SigData(const UINT8* const pDataBuf,
                                          SEpochSatObs& stEpochSatObs,
                                          const UINT32& ui32Index,
                                          const UINT32& ui32SignalNum,
                                          const UINT32& ui32CellNum,
                                          const UINT64& ui64CellLength,
                                          const array< UINT32, common::rtcm::MAX_SATELLITE_NUM >& objSatelliteIds,
                                          const array< UINT32, common::rtcm::MAX_SIGNAL_NUM >& objSignalIds,
                                          const array< UINT32, common::rtcm::MAX_CELL_NUM >& objCellNum)
    {
        m_pobjLog->Trace("Enter function DecodeMsm4SigData.", CLog::LL_DEBUG);
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            SSignalValue stSignal;
            UINT32 ui32Offset = 0U;
            UINT32 ui32CellIndex = 0U;
            for (UINT64 i = 0U; i != ui64CellLength; ++i)
            {
                if (objCellNum[static_cast< std::size_t >(i)] == 0U)
                {
                    continue;
                }

                // GNSS 信号精确伪距观测值
                ui32Offset = ui32CellIndex * DATA_LENGTH_15;
                stSignal.m_dbFinePseudoranges =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_15))
                    * P2_24;

                // GNSS 信号精确相位距离数据
                ui32Offset = ui32CellNum * DATA_LENGTH_15 + ui32CellIndex * DATA_LENGTH_22;
                stSignal.m_dbFinePhaserange =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_22))
                    * P2_29;

                // GNSS 相位距离锁定时间标志
                ui32Offset =
                    ui32CellNum * DATA_LENGTH_15 + ui32CellNum * DATA_LENGTH_22 + ui32CellIndex * DATA_LENGTH_4;
                stSignal.m_ui8LockTimeIndicator = static_cast< UINT8 >(
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_4));

                // 半周模糊度指标
                ui32Offset = ui32CellNum * DATA_LENGTH_15 + ui32CellNum * DATA_LENGTH_22 + ui32CellNum * DATA_LENGTH_4
                             + ui32CellIndex * DATA_LENGTH_1;
                stSignal.m_ui8HCAI = static_cast< UINT8 >(
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_1));

                // GNSS 信号CNR
                ui32Offset = ui32CellNum * DATA_LENGTH_15 + ui32CellNum * DATA_LENGTH_22 + ui32CellNum * DATA_LENGTH_4
                             + ui32CellNum * DATA_LENGTH_1 + ui32CellIndex * DATA_LENGTH_6;
                stSignal.m_dbSignalCnr = static_cast< DOUBLE >(
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_6));

                // 向卫星数据中插入信号数据
                SSatelliteValue& stSatValue = stEpochSatObs.m_mapSatValues[static_cast< INT32 >(
                    objSatelliteIds[static_cast< std::size_t >(i / ui32SignalNum)])];
                // Pseudorange(i) = c / 1000 ×(Nms + Rough_range / 1024 + 2^–29
                // ×Fine_Pseudorange(i))
                stSignal.m_dbPseudoranges = RANGE_MS
                                            * (static_cast< DOUBLE >(stSatValue.m_ui8Milliseconds)
                                               + stSatValue.m_dbModulo1Millisecond + stSignal.m_dbFinePseudoranges);

                // PhaseRange(i) = c / 1000 ×(Nms + Rough_range / 1024 + 2^-31
                // ×Fine_PhaseRange(i))
                stSignal.m_dbPhaserange = RANGE_MS
                                          * (static_cast< DOUBLE >(stSatValue.m_ui8Milliseconds)
                                             + stSatValue.m_dbModulo1Millisecond + stSignal.m_dbFinePhaserange);

                stSatValue.m_mapSignalValues.insert(
                    make_pair(objSignalIds[static_cast< std::size_t >(i % ui32SignalNum)], stSignal));
                ++ui32CellIndex;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeMsm7SatData(const UINT8* const pDataBuf,
                                          SEpochSatObs& stEpochSatObs,
                                          UINT32& ui32Index,
                                          const UINT32& ui32SatelliteNum,
                                          const array< UINT32, common::rtcm::MAX_SATELLITE_NUM >& objSatelliteIds)
    {
        m_pobjLog->Trace("Enter function DecodeMsm7SatData.", CLog::LL_DEBUG);
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            UINT32 ui32Offset = 0U;
            SSatelliteValue stSatellite;
            // 为了避免多次循环，所以在循环内通过偏移分别解析每个数据
            for (UINT32 i = 0U; i != ui32SatelliteNum; ++i)
            {
                // 卫星概略距离的整毫秒数
                ui32Offset = i * DATA_LENGTH_8;
                stSatellite.m_ui8Milliseconds = static_cast< UINT8 >(
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_8));

                // 扩展卫星信息
                ui32Offset = ui32SatelliteNum * DATA_LENGTH_8 + i * DATA_LENGTH_4;
                stSatellite.m_ui8ExtendedSatInfo = static_cast< UINT8 >(
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_4));

                // 卫星概略距离的毫秒余数
                ui32Offset = ui32SatelliteNum * DATA_LENGTH_8 + ui32SatelliteNum * DATA_LENGTH_4 + i * DATA_LENGTH_10;
                stSatellite.m_dbModulo1Millisecond = static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(
                                                         pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_10))
                                                     * P2_10;

                // 卫星概略相位距离变化率
                ui32Offset = ui32SatelliteNum * DATA_LENGTH_8 + ui32SatelliteNum * DATA_LENGTH_4
                             + ui32SatelliteNum * DATA_LENGTH_10 + i * DATA_LENGTH_14;
                stSatellite.m_i32RoughPhaseRangeRates =
                    CCodecUtilities::GetIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_14);

                // 插入卫星数据
                stEpochSatObs.m_mapSatValues.insert(
                    make_pair(objSatelliteIds[static_cast< std::size_t >(i)], stSatellite));
            }
            ui32Index += ui32SatelliteNum * (DATA_LENGTH_36);
            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeMsm7SigData(const UINT8* const pDataBuf,
                                          SEpochSatObs& stEpochSatObs,
                                          const UINT32& ui32Index,
                                          const UINT32& ui32SignalNum,
                                          const UINT32& ui32CellNum,
                                          const UINT64& ui64CellLength,
                                          const array< UINT32, common::rtcm::MAX_SATELLITE_NUM >& objSatelliteIds,
                                          const array< UINT32, common::rtcm::MAX_SIGNAL_NUM >& objSignalIds,
                                          const array< UINT32, common::rtcm::MAX_CELL_NUM >& objCellNum)
    {
        m_pobjLog->Trace("Enter function DecodeMsm7SigData.", CLog::LL_DEBUG);
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            SSignalValue stSignal;
            UINT32 ui32Offset = 0U;
            UINT32 ui32CellIndex = 0U;
            for (UINT32 i = 0U; i != ui64CellLength; ++i)
            {
                if (objCellNum[static_cast< std::size_t >(i)] == 0U)
                {
                    continue;
                }

                // 具有扩展分辨率的GNSS 信号精确伪距值
                ui32Offset = ui32CellIndex * DATA_LENGTH_20;
                stSignal.m_dbFinePseudorangesWithER =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_20))
                    * P2_29;

                // 具有扩展分辨率的GNSS 信号精确相位距离
                ui32Offset = ui32CellNum * DATA_LENGTH_20 + ui32CellIndex * DATA_LENGTH_24;
                stSignal.m_dbFinePhaserangeWithER =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_24))
                    * P2_31;

                // 具有扩展范围和分辨率的GNSS 相位距离时间锁定标志
                ui32Offset =
                    ui32CellNum * DATA_LENGTH_20 + ui32CellNum * DATA_LENGTH_24 + ui32CellIndex * DATA_LENGTH_10;
                stSignal.m_ui16PLTIWithERAR = static_cast< UINT16 >(
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_10));

                // 半周模糊度指标
                ui32Offset = ui32CellNum * DATA_LENGTH_20 + ui32CellNum * DATA_LENGTH_24 + ui32CellNum * DATA_LENGTH_10
                             + ui32CellIndex * DATA_LENGTH_1;
                stSignal.m_ui8HCAI = static_cast< UINT8 >(
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_1));

                // 具有扩展分辨率的GNSS 信号信噪比
                ui32Offset = ui32CellNum * DATA_LENGTH_20 + ui32CellNum * DATA_LENGTH_24 + ui32CellNum * DATA_LENGTH_10
                             + ui32CellNum * DATA_LENGTH_1 + ui32CellIndex * DATA_LENGTH_10;
                stSignal.m_dbSignalCnrsWER = static_cast< DOUBLE >(CCodecUtilities::GetUnsignedIntBit(
                                                 pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_10))
                                             * P2_4;

                // GNSS 信号精确相位距离变化率
                ui32Offset = ui32CellNum * DATA_LENGTH_20 + ui32CellNum * DATA_LENGTH_24 + ui32CellNum * DATA_LENGTH_10
                             + ui32CellNum * DATA_LENGTH_1 + ui32CellNum * DATA_LENGTH_10
                             + ui32CellIndex * DATA_LENGTH_15;
                stSignal.m_dbFPRates =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Index + ui32Offset, DATA_LENGTH_15))
                    * SCALE_1E_4;

                // 向卫星数据中插入信号数据
                const std::size_t szindex = static_cast< std::size_t >(i) / static_cast< std::size_t >(ui32SignalNum);
                SSatelliteValue& stSatValue =
                    stEpochSatObs.m_mapSatValues[static_cast< INT32 >(objSatelliteIds[szindex])];

                stSignal.m_dbPseudoranges =
                    RANGE_MS
                    * (static_cast< DOUBLE >(stSatValue.m_ui8Milliseconds) + stSatValue.m_dbModulo1Millisecond
                       + stSignal.m_dbFinePseudorangesWithER);

                stSignal.m_dbPhaserange = RANGE_MS
                                          * (static_cast< DOUBLE >(stSatValue.m_ui8Milliseconds)
                                             + stSatValue.m_dbModulo1Millisecond + stSignal.m_dbFinePhaserangeWithER);

                stSignal.m_dbPhaseRangeRate =
                    static_cast< DOUBLE >(stSatValue.m_i32RoughPhaseRangeRates) + stSignal.m_dbFPRates;

                const std::size_t szIndex = static_cast< std::size_t >(i) % static_cast< std::size_t >(ui32SignalNum);
                stSatValue.m_mapSignalValues.insert(make_pair(objSignalIds[szIndex], stSignal));
                ++ui32CellIndex;
            }

            i32RetCode = RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeHead1004(const UINT8* const pDataBuf, SEpochSatObs& stEpochSatObs, UINT32& nsat)
    {

        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            UINT32 ui32Offset = MSG_HEAD_LENGTH;
            stEpochSatObs.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_12));
            ui32Offset += DATA_LENGTH_12;

            stEpochSatObs.m_ui32GmNtiRefStationID =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_12);
            ui32Offset += DATA_LENGTH_12;

            stEpochSatObs.m_ui32GnssEpochTime =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_30);
            ui32Offset += DATA_LENGTH_30;

            stEpochSatObs.m_ui8MultiMsgBit =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
            ui32Offset += DATA_LENGTH_1;

            nsat = static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_5));
            ui32Offset += DATA_LENGTH_5;

            stEpochSatObs.m_ui8GnssSmoothingIndicator =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
            ui32Offset += DATA_LENGTH_1;

            stEpochSatObs.m_ui8GnssSmoothingInterval =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_3));
            ui32Offset += DATA_LENGTH_3;

            i32RetCode = RETURN_SUCCESS;
        } while (false);
        return i32RetCode;
    }

    INT32
    CRtcmDecoder::DecodeHead1012(const UINT8* const pDataBuf, SEpochSatObs& stEpochSatObs, UINT32& nsat)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            UINT32 ui32Offset = MSG_HEAD_LENGTH;

            stEpochSatObs.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_12));
            ui32Offset += DATA_LENGTH_12;

            stEpochSatObs.m_ui32GmNtiRefStationID =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_12);
            ui32Offset += DATA_LENGTH_12;

            stEpochSatObs.m_ui32GnssEpochTime =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_27);
            ui32Offset += DATA_LENGTH_27;

            stEpochSatObs.m_ui8MultiMsgBit =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
            ui32Offset += DATA_LENGTH_1;

            nsat = static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_5));
            ui32Offset += DATA_LENGTH_5;

            stEpochSatObs.m_ui8GnssSmoothingIndicator =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
            ui32Offset += DATA_LENGTH_1;

            stEpochSatObs.m_ui8GnssSmoothingInterval =
                static_cast< UINT32 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_3));
            ui32Offset += DATA_LENGTH_3;

            i32RetCode = RETURN_SUCCESS;
        } while (false);
        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeSSR1(const UINT8* const pDataBuf,
                                   const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                   SOrbitCorrection& sOrbitCorrection)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            //目前只支持GPS和GLO
            if (enSatSystemconst != IGnssDataInterface::SYS_GPS && enSatSystemconst != IGnssDataInterface::SYS_GLO)
            {
                break;
            }

            UINT32 satNumLength = 0;
            UINT32 IODELength = DATA_LENGTH_8;
            UINT32 ui32Offset = 0U;

            if (enSatSystemconst == IGnssDataInterface::SYS_GPS)
            {

                satNumLength = DATA_LENGTH_6;
            }
            else
            {
                satNumLength = DATA_LENGTH_5;
            }

            if (DecodeSSR1Head(pDataBuf, enSatSystemconst, sOrbitCorrection, ui32Offset) != RETURN_SUCCESS)
            {
                m_objStrStream << sOrbitCorrection.m_ui16MsgType + " DecodeSSR1Head Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            for (UINT8 j = 0U; j < sOrbitCorrection.m_ui8SatNum; ++j)
            {
                SOrbitCorrectionInfo stOrbitCorrectionInfo;

                stOrbitCorrectionInfo.m_ui8SatId =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, satNumLength));
                ui32Offset += satNumLength;

                stOrbitCorrectionInfo.m_ui8IODE =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, IODELength));
                ui32Offset += IODELength;

                stOrbitCorrectionInfo.m_dbDeltaRadial =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_22))
                    * SCALE_DF365;
                ui32Offset += DATA_LENGTH_22;

                stOrbitCorrectionInfo.m_dbDeltaAlongTrack =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20))
                    * SCALE_DF366;
                ui32Offset += DATA_LENGTH_20;

                stOrbitCorrectionInfo.m_dbDeltaCrossTrack =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20))
                    * SCALE_DF367;
                ui32Offset += DATA_LENGTH_20;

                stOrbitCorrectionInfo.m_dbDotDeltaRadial =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_21))
                    * SCALE_DF368;
                ui32Offset += DATA_LENGTH_21;

                stOrbitCorrectionInfo.m_dbDotDeltaAlongTrack =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_19))
                    * SCALE_DF369;
                ui32Offset += DATA_LENGTH_19;

                stOrbitCorrectionInfo.m_dbDotDeltaCrossTrack =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_19))
                    * SCALE_DF370;
                ui32Offset += DATA_LENGTH_19;

                sOrbitCorrection.m_mapOrbitCorrectionInfo.insert(
                    make_pair(stOrbitCorrectionInfo.m_ui8SatId, stOrbitCorrectionInfo));
            }
            i32RetCode = RETURN_SUCCESS;
        } while (false);
        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeSSR2(const UINT8* const pDataBuf,
                                   const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                   SClockCorrection& sClockCorrection)
    {
        INT32 i32RetCode = RETURN_FAIL;

        do
        {
            //目前支持GPS和GLO
            if (enSatSystemconst != IGnssDataInterface::SYS_GPS && enSatSystemconst != IGnssDataInterface::SYS_GLO)
            {
                break;
            }

            UINT32 satNumLength = 0U;
            UINT32 ui32Offset = 0U;

            if (enSatSystemconst == IGnssDataInterface::SYS_GPS)
            {

                satNumLength = DATA_LENGTH_6;
            }
            else
            {
                satNumLength = DATA_LENGTH_5;
            }

            if (DecodeSSR2Head(pDataBuf, enSatSystemconst, sClockCorrection, ui32Offset) != RETURN_SUCCESS)
            {
                m_objStrStream << sClockCorrection.m_ui16MsgType + " DecodeSSR2Head Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            //钟差
            if ((sClockCorrection.m_ui16MsgType == MSG_1058) || (sClockCorrection.m_ui16MsgType == MSG_1064))
            {
                for (UINT8 j = 0U; j < sClockCorrection.m_ui8SatNum; ++j)
                {
                    SClockCorrectionInfo stClockCorrectionInfo;

                    stClockCorrectionInfo.m_ui8SatId =
                        static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, satNumLength));
                    ui32Offset += satNumLength;

                    stClockCorrectionInfo.m_dbDeltaC0 =
                        static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_22))
                        * SCALE_DF376;
                    ui32Offset += DATA_LENGTH_22;

                    stClockCorrectionInfo.m_dbDeltaC1 =
                        static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_21))
                        * SCALE_DF377;
                    ui32Offset += DATA_LENGTH_21;

                    stClockCorrectionInfo.m_dbDeltaC2 =
                        static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_27))
                        * SCALE_DF378;
                    ui32Offset += DATA_LENGTH_27;

                    sClockCorrection.m_mapClockCorrectionInfo.insert(
                        make_pair(stClockCorrectionInfo.m_ui8SatId, stClockCorrectionInfo));
                }
            }

            //高频钟差
            else
            {
                for (UINT8 j = 0U; j < sClockCorrection.m_ui8SatNum; ++j)
                {
                    SClockCorrectionInfo stClockCorrectionInfo;

                    stClockCorrectionInfo.m_ui8SatId =
                        static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, satNumLength));
                    ui32Offset += satNumLength;

                    stClockCorrectionInfo.m_dbDeltaHighFrequencyNum =
                        static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_22))
                        * SCALE_DF390;
                    ui32Offset += DATA_LENGTH_22;

                    sClockCorrection.m_mapClockCorrectionInfo.insert(
                        make_pair(stClockCorrectionInfo.m_ui8SatId, stClockCorrectionInfo));
                }
            }
            i32RetCode = RETURN_SUCCESS;
        } while (false);
        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeSSR4(const UINT8* const pDataBuf,
                                   const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                   SOrbitClockCorrection& sOrbitClockCorrection)
    {

        INT32 i32RetCode = RETURN_FAIL;
        do
        {
            //目前支持GPS和GLO
            if (enSatSystemconst != IGnssDataInterface::SYS_GPS && enSatSystemconst != IGnssDataInterface::SYS_GLO)
            {
                break;
            }

            UINT32 satNumLength = 0U;
            UINT32 IODELength = DATA_LENGTH_8;
            UINT32 ui32Offset = 0U;

            if (enSatSystemconst == IGnssDataInterface::SYS_GPS)
            {

                satNumLength = DATA_LENGTH_6;
            }
            else
            {
                satNumLength = DATA_LENGTH_5;
            }

            if (DecodeSSR4Head(pDataBuf, enSatSystemconst, sOrbitClockCorrection, ui32Offset) != RETURN_SUCCESS)
            {
                m_objStrStream << sOrbitClockCorrection.m_ui16MsgType + " DecodeSSR4Head Failed";
                m_pobjLog->Trace(m_objStrStream.str(), CLog::LL_ERROR);
                break;
            }

            for (UINT8 j = 0U; j < sOrbitClockCorrection.m_ui8SatNum; ++j)
            {
                SOrbitClockCorrectionInfo stOrbitClockCorrectionInfo;

                stOrbitClockCorrectionInfo.m_ui8SatId =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, satNumLength));
                ui32Offset += satNumLength;

                stOrbitClockCorrectionInfo.m_ui8IODE =
                    static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, IODELength));
                ui32Offset += IODELength;

                stOrbitClockCorrectionInfo.m_db8DeltaRadial =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_22))
                    * SCALE_DF365;
                ui32Offset += DATA_LENGTH_22;

                stOrbitClockCorrectionInfo.m_dbDeltaAlongTrack =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20))
                    * SCALE_DF366;
                ui32Offset += DATA_LENGTH_20;

                stOrbitClockCorrectionInfo.m_dbDeltaCrossTrack =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20))
                    * SCALE_DF367;
                ui32Offset += DATA_LENGTH_20;

                stOrbitClockCorrectionInfo.m_dbDotDeltaRadial =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_21))
                    * SCALE_DF368;
                ui32Offset += DATA_LENGTH_21;

                stOrbitClockCorrectionInfo.m_dbDotDeltaAlongTrack =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_19))
                    * SCALE_DF369;
                ui32Offset += DATA_LENGTH_19;

                stOrbitClockCorrectionInfo.m_dbDotDeltaCrossTrack =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_19))
                    * SCALE_DF370;
                ui32Offset += DATA_LENGTH_19;

                stOrbitClockCorrectionInfo.m_dbDeltaC0 =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_22))
                    * SCALE_DF376;
                ui32Offset += DATA_LENGTH_22;

                stOrbitClockCorrectionInfo.m_dbDeltaC1 =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_21))
                    * SCALE_DF377;
                ui32Offset += DATA_LENGTH_21;

                stOrbitClockCorrectionInfo.m_dbDeltaC2 =
                    static_cast< DOUBLE >(CCodecUtilities::GetIntBit(pDataBuf, ui32Offset, DATA_LENGTH_27))
                    * SCALE_DF378;
                ui32Offset += DATA_LENGTH_27;

                sOrbitClockCorrection.m_mapOrbitClockCorrectionInfo.insert(
                    make_pair(stOrbitClockCorrectionInfo.m_ui8SatId, stOrbitClockCorrectionInfo));
            }
            i32RetCode = RETURN_SUCCESS;
        } while (false);
        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeSSR1Head(const UINT8* const pDataBuf,
                                       const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                       SOrbitCorrection& sOrbitCorrection,
                                       UINT32& ui32Offset)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {

            ui32Offset = MSG_HEAD_LENGTH;

            sOrbitCorrection.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_12));
            ui32Offset += DATA_LENGTH_12;

            if (enSatSystemconst == IGnssDataInterface::SYS_GLO)
            {
                sOrbitCorrection.m_ui32EpochTime =
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_17);
                ui32Offset += DATA_LENGTH_17;
            }
            else
            {
                sOrbitCorrection.m_ui32EpochTime =
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20);
                ui32Offset += DATA_LENGTH_20;
            }

            sOrbitCorrection.m_ui32SSRUpdateInterval =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_4);
            ui32Offset += DATA_LENGTH_4;

            sOrbitCorrection.m_ui8MulMsgIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
            ui32Offset += DATA_LENGTH_1;

            sOrbitCorrection.m_ui8SatRefDatum =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
            ui32Offset += DATA_LENGTH_1;

            sOrbitCorrection.m_ui8IodSsr =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_4));
            ui32Offset += DATA_LENGTH_4;

            sOrbitCorrection.m_ui32SsrProviderID =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_16);
            ui32Offset += DATA_LENGTH_16;

            sOrbitCorrection.m_ui8SsrSolutionID =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_4));
            ui32Offset += DATA_LENGTH_4;

            sOrbitCorrection.m_ui8SatNum =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_6));
            ui32Offset += DATA_LENGTH_6;

            i32RetCode = RETURN_SUCCESS;
        } while (false);
        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeSSR2Head(const UINT8* const pDataBuf,
                                       const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                       SClockCorrection& sClockCorrection,
                                       UINT32& ui32Offset)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {

            ui32Offset = MSG_HEAD_LENGTH;

            sClockCorrection.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_12));
            ui32Offset += DATA_LENGTH_12;

            if (enSatSystemconst == IGnssDataInterface::SYS_GLO)
            {
                sClockCorrection.m_ui32EpochTime =
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_17);
                ui32Offset += DATA_LENGTH_17;
            }
            else
            {
                sClockCorrection.m_ui32EpochTime =
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20);
                ui32Offset += DATA_LENGTH_20;
            }

            sClockCorrection.m_ui32SSRUpdateInterval =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_4);
            ui32Offset += DATA_LENGTH_4;

            sClockCorrection.m_ui8MulMsgIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
            ui32Offset += DATA_LENGTH_1;

            sClockCorrection.m_ui8IodSsr =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_4));
            ui32Offset += DATA_LENGTH_4;

            sClockCorrection.m_ui32SsrProviderID =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_16);
            ui32Offset += DATA_LENGTH_16;

            sClockCorrection.m_ui8SsrSolutionID =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_4));
            ui32Offset += DATA_LENGTH_4;

            sClockCorrection.m_ui8SatNum =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_6));
            ui32Offset += DATA_LENGTH_6;

            i32RetCode = RETURN_SUCCESS;
        } while (false);
        return i32RetCode;
    }

    INT32 CRtcmDecoder::DecodeSSR4Head(const UINT8* const pDataBuf,
                                       const IGnssDataInterface::SatelliteSystem enSatSystemconst,
                                       SOrbitClockCorrection& sOrbitClockCorrection,
                                       UINT32& ui32Offset)
    {
        INT32 i32RetCode = RETURN_FAIL;
        do
        {

            ui32Offset = MSG_HEAD_LENGTH;

            sOrbitClockCorrection.m_ui16MsgType =
                static_cast< UINT16 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_12));
            ui32Offset += DATA_LENGTH_12;

            if (enSatSystemconst == IGnssDataInterface::SYS_GLO)
            {
                sOrbitClockCorrection.m_ui32EpochTime =
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_17);
                ui32Offset += DATA_LENGTH_17;
            }
            else
            {
                sOrbitClockCorrection.m_ui32EpochTime =
                    CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_20);
                ui32Offset += DATA_LENGTH_20;
            }

            sOrbitClockCorrection.m_ui32SSRUpdateInterval =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_4);
            ui32Offset += DATA_LENGTH_4;

            sOrbitClockCorrection.m_ui8MulMsgIndicator =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
            ui32Offset += DATA_LENGTH_1;

            sOrbitClockCorrection.m_ui8SatRefDatum =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_1));
            ui32Offset += DATA_LENGTH_1;

            sOrbitClockCorrection.m_ui8IodSsr =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_4));
            ui32Offset += DATA_LENGTH_4;

            sOrbitClockCorrection.m_ui32SsrProviderID =
                CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_16);
            ui32Offset += DATA_LENGTH_16;

            sOrbitClockCorrection.m_ui8SsrSolutionID =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_4));
            ui32Offset += DATA_LENGTH_4;

            sOrbitClockCorrection.m_ui8SatNum =
                static_cast< UINT8 >(CCodecUtilities::GetUnsignedIntBit(pDataBuf, ui32Offset, DATA_LENGTH_6));
            ui32Offset += DATA_LENGTH_6;

            i32RetCode = RETURN_SUCCESS;
        } while (false);
        return i32RetCode;
    }

    UINT32
    CRtcmDecoder::GetMsgLength(const UINT8* const pDataBuf)
    {
        return CCodecUtilities::GetUnsignedIntBit(pDataBuf, MSG_DATA_LENGTH_START_INDEX, DATA_LENGTH_10);
    }

    IGnssDataInterface* CRtcmDecoder::GetGnssData(const IGnssDataInterface::SatelliteSystem enSatSystem,
                                                  const IGnssDataInterface::GnssDataType enDataType)
    {
        const std::lock_guard< std::mutex > objLock(m_objMutex);
        if (m_mapGnssDatas[static_cast< INT32 >(enDataType)] == nullptr)
        {
            switch (enDataType)
            {
                case sixents::IGnssDataInterface::GDT_OBS:
                {
                    m_mapGnssDatas[static_cast< INT32 >(enDataType)] =
                        static_cast< IGnssDataInterface* >(new (std::nothrow) CEpochObs());
                }
                break;
                case sixents::IGnssDataInterface::GDT_EPH:
                {
                    m_mapGnssDatas[static_cast< INT32 >(enDataType)] =
                        static_cast< IGnssDataInterface* >(new (std::nothrow) CEphemeris());
                }
                break;
                case sixents::IGnssDataInterface::GDT_GLO_EPH:
                {
                    m_mapGnssDatas[static_cast< INT32 >(enDataType)] =
                        static_cast< IGnssDataInterface* >(new (std::nothrow) CGlonassEphemeris());
                }
                break;
                case sixents::IGnssDataInterface::GDT_REF_INFO:
                {
                    m_mapGnssDatas[static_cast< INT32 >(enDataType)] =
                        static_cast< IGnssDataInterface* >(new (std::nothrow) CReferenceInfo());
                }
                break;
                case sixents::IGnssDataInterface::GDT_ORBIT:
                {
                    m_mapGnssDatas[static_cast< INT32 >(enDataType)] =
                        static_cast< IGnssDataInterface* >(new (std::nothrow) COrbitCorrection());
                }
                break;
                case sixents::IGnssDataInterface::GDT_CLOCK:
                {
                    m_mapGnssDatas[static_cast< INT32 >(enDataType)] =
                        static_cast< IGnssDataInterface* >(new (std::nothrow) CClockCorrection());
                }
                break;
                case sixents::IGnssDataInterface::GDT_ORBIT_CLOCK:
                {
                    m_mapGnssDatas[static_cast< INT32 >(enDataType)] =
                        static_cast< IGnssDataInterface* >(new (std::nothrow) COrbitClockCorrection());
                }
                break;
                case sixents::IGnssDataInterface::GDT_DCB:
                {
                    m_mapGnssDatas[static_cast< INT32 >(enDataType)] =
                        static_cast< IGnssDataInterface* >(new (std::nothrow) CDcb());
                }
                break;
                case sixents::IGnssDataInterface::GDT_URA:
                {
                    m_mapGnssDatas[static_cast< INT32 >(enDataType)] =
                        static_cast< IGnssDataInterface* >(new (std::nothrow) CUra());
                }
                break;
                default:
                {
                    // Do nothing
                }
                break;
            }
        }

        if (m_mapGnssDatas[static_cast< INT32 >(enDataType)] != nullptr)
        {
            m_mapGnssDatas[static_cast< INT32 >(enDataType)]->SetSatelliteSystemType(enSatSystem);
        }

        return m_mapGnssDatas[static_cast< INT32 >(enDataType)];
    }

    void CRtcmDecoder::InitStrStream(const string& strHead)
    {
        m_objStrStream.clear();
        m_objStrStream.str("");
        m_objStrStream << strHead << ": ";
    }

    INT32 CRtcmDecoder::FillDecodeResult(const SReferenceInfo& objData,
                                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                                         const IGnssDataInterface::GnssDataType enDataType,
                                         stringstream& objStrStream,
                                         CParam& pamOut)
    {
        INT32 i32RetCode = sixents::RETURN_FAIL;
        do
        {
            IGnssDataInterface* const pGnssData = GetGnssData(enSatSystem, enDataType);
            if (pGnssData == nullptr)
            {
                objStrStream << "Failed to get GNSS data object.";
                break;
            }

            CReferenceInfo* const pReferenceInfo = dynamic_cast< CReferenceInfo* const >(pGnssData);
            if (pReferenceInfo == nullptr)
            {
                objStrStream << "Failed to get CReferenceInfo object.";
                break;
            }

            pReferenceInfo->SetReferenceInfo(objData);
            if (pamOut.AddValue(sixents::common::rtcm::PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr)
                == false)
            {
                objStrStream << "Failed to add CReferenceInfo object.";
                break;
            }

            i32RetCode = sixents::RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::FillDecodeResult(const SOrbitCorrection& objData,
                                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                                         const IGnssDataInterface::GnssDataType enDataType,
                                         stringstream& objStrStream,
                                         CParam& pamOut)
    {
        INT32 i32RetCode = sixents::RETURN_FAIL;
        do
        {
            IGnssDataInterface* const pGnssData = GetGnssData(enSatSystem, enDataType);
            if (pGnssData == nullptr)
            {
                objStrStream << "Failed to get GNSS data object.";
                break;
            }

            COrbitCorrection* const pOrbitCorrection = dynamic_cast< COrbitCorrection* const >(pGnssData);
            if (pOrbitCorrection == nullptr)
            {
                objStrStream << "Failed to get COrbitCorrection object.";
                break;
            }

            pOrbitCorrection->SetOrbitCorrection(objData);
            if (pamOut.AddValue(sixents::common::rtcm::PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr)
                == false)
            {
                objStrStream << "Failed to add COrbitCorrection object.";
                break;
            }

            i32RetCode = sixents::RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::FillDecodeResult(const SClockCorrection& objData,
                                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                                         const IGnssDataInterface::GnssDataType enDataType,
                                         stringstream& objStrStream,
                                         CParam& pamOut)
    {
        INT32 i32RetCode = sixents::RETURN_FAIL;
        do
        {
            IGnssDataInterface* const pGnssData = GetGnssData(enSatSystem, enDataType);
            if (pGnssData == nullptr)
            {
                objStrStream << "Failed to get GNSS data object.";
                break;
            }

            CClockCorrection* const pClockCorrection = dynamic_cast< CClockCorrection* const >(pGnssData);
            if (pClockCorrection == nullptr)
            {
                objStrStream << "Failed to get CClockCorrection object.";
                break;
            }

            pClockCorrection->SetClockCorrection(objData);
            if (pamOut.AddValue(sixents::common::rtcm::PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr)
                == false)
            {
                objStrStream << "Failed to add CClockCorrection object.";
                break;
            }

            i32RetCode = sixents::RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::FillDecodeResult(const SOrbitClockCorrection& objData,
                                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                                         const IGnssDataInterface::GnssDataType enDataType,
                                         stringstream& objStrStream,
                                         CParam& pamOut)
    {
        INT32 i32RetCode = sixents::RETURN_FAIL;
        do
        {
            IGnssDataInterface* const pGnssData = GetGnssData(enSatSystem, enDataType);
            if (pGnssData == nullptr)
            {
                objStrStream << "Failed to get GNSS data object.";
                break;
            }

            COrbitClockCorrection* const pOrbitClockCorrection =
                dynamic_cast< COrbitClockCorrection* const >(pGnssData);
            if (pOrbitClockCorrection == nullptr)
            {
                objStrStream << "Failed to get COrbitClockCorrection object.";
                break;
            }

            pOrbitClockCorrection->SetOrbitClockCorrection(objData);
            if (pamOut.AddValue(sixents::common::rtcm::PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr)
                == false)
            {
                objStrStream << "Failed to add COrbitClockCorrection object.";
                break;
            }

            i32RetCode = sixents::RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::FillDecodeResult(const SDcb& objData,
                                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                                         const IGnssDataInterface::GnssDataType enDataType,
                                         stringstream& objStrStream,
                                         CParam& pamOut)
    {
        INT32 i32RetCode = sixents::RETURN_FAIL;
        do
        {
            IGnssDataInterface* const pGnssData = GetGnssData(enSatSystem, enDataType);
            if (pGnssData == nullptr)
            {
                objStrStream << "Failed to get GNSS data object.";
                break;
            }

            CDcb* const pDcb = dynamic_cast< CDcb* const >(pGnssData);
            if (pDcb == nullptr)
            {
                objStrStream << "Failed to get CDcb object.";
                break;
            }

            pDcb->SetDcb(objData);
            if (pamOut.AddValue(sixents::common::rtcm::PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr)
                == false)
            {
                objStrStream << "Failed to add CDcb object.";
                break;
            }

            i32RetCode = sixents::RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::FillDecodeResult(const SUra& objData,
                                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                                         const IGnssDataInterface::GnssDataType enDataType,
                                         stringstream& objStrStream,
                                         CParam& pamOut)
    {
        INT32 i32RetCode = sixents::RETURN_FAIL;
        do
        {
            IGnssDataInterface* const pGnssData = GetGnssData(enSatSystem, enDataType);
            if (pGnssData == nullptr)
            {
                objStrStream << "Failed to get GNSS data object.";
                break;
            }

            CUra* const pUra = dynamic_cast< CUra* const >(pGnssData);
            if (pUra == nullptr)
            {
                objStrStream << "Failed to get CUra object.";
                break;
            }

            pUra->SetUra(objData);
            if (pamOut.AddValue(sixents::common::rtcm::PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr)
                == false)
            {
                objStrStream << "Failed to add CUra object.";
                break;
            }

            i32RetCode = sixents::RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::FillDecodeResult(const SEpochSatObs& objData,
                                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                                         const IGnssDataInterface::GnssDataType enDataType,
                                         std::stringstream& objStrStream,
                                         CParam& pamOut)
    {
        INT32 i32RetCode = sixents::RETURN_FAIL;
        do
        {
            IGnssDataInterface* const pGnssData = GetGnssData(enSatSystem, enDataType);
            if (pGnssData == nullptr)
            {
                objStrStream << "Failed to get GNSS data object.";
                break;
            }

            CEpochObs* const pEpochObs = dynamic_cast< CEpochObs* const >(pGnssData);
            if (pEpochObs == nullptr)
            {
                objStrStream << "Failed to get CEpochObs object.";
                break;
            }

            pEpochObs->SetEpochSatObs(objData);
            if (pamOut.AddValue(sixents::common::rtcm::PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr)
                == false)
            {
                objStrStream << "Failed to add CEpochObs object.";
                break;
            }

            i32RetCode = sixents::RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::FillDecodeResult(const SEphemeris& objData,
                                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                                         const IGnssDataInterface::GnssDataType enDataType,
                                         std::stringstream& objStrStream,
                                         CParam& pamOut)
    {
        INT32 i32RetCode = sixents::RETURN_FAIL;
        do
        {
            IGnssDataInterface* const pGnssData = GetGnssData(enSatSystem, enDataType);
            if (pGnssData == nullptr)
            {
                objStrStream << "Failed to get GNSS data object.";
                break;
            }

            CEphemeris* const pEphemeris = dynamic_cast< CEphemeris* const >(pGnssData);
            if (pEphemeris == nullptr)
            {
                objStrStream << "Failed to get CEphemeris object.";
                break;
            }

            pEphemeris->SetEphemeris(objData);
            if (pamOut.AddValue(sixents::common::rtcm::PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr)
                == false)
            {
                objStrStream << "Failed to add CEphemeris object.";
                break;
            }

            i32RetCode = sixents::RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }

    INT32 CRtcmDecoder::FillDecodeResult(const SGlonassEphemeris& objData,
                                         const IGnssDataInterface::SatelliteSystem enSatSystem,
                                         const IGnssDataInterface::GnssDataType enDataType,
                                         std::stringstream& objStrStream,
                                         CParam& pamOut)
    {
        INT32 i32RetCode = sixents::RETURN_FAIL;
        do
        {
            IGnssDataInterface* const pGnssData = GetGnssData(enSatSystem, enDataType);
            if (pGnssData == nullptr)
            {
                objStrStream << "Failed to get GNSS data object.";
                break;
            }

            CGlonassEphemeris* const pGlonassEphemeris = dynamic_cast< CGlonassEphemeris* const >(pGnssData);
            if (pGlonassEphemeris == nullptr)
            {
                objStrStream << "Failed to get CGlonassEphemeris object.";
                break;
            }

            pGlonassEphemeris->SetGlonassEphemeris(objData);
            if (pamOut.AddValue(sixents::common::rtcm::PN_PTR_GNSS_DATA_OBJECT, PDT_POINTER, pGnssData, nullptr)
                == false)
            {
                objStrStream << "Failed to add CGlonassEphemeris object.";
                break;
            }

            i32RetCode = sixents::RETURN_SUCCESS;
        } while (false);

        return i32RetCode;
    }
} // namespace sixents
