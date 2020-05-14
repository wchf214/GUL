#include "IGnssDataInterface.h"
#include <cmath>
#include "../Codec/CCodecUtilities.h"
namespace sixents
{
    IGnssDataInterface::IGnssDataInterface()
        : m_enDataType(GDT_UNKNOW)
    {}

    IGnssDataInterface::~IGnssDataInterface()
    {}

    IGnssDataInterface::GnssDataType IGnssDataInterface::GetGnssDataType() const
    {
        return this->m_enDataType;
    }

    IGnssDataInterface::SatelliteSystem IGnssDataInterface::GetSatelliteSystemType() const
    {
        return this->m_enSatSys;
    }

    void IGnssDataInterface::SetSatelliteSystemType(const SatelliteSystem enSatelliteSystem)
    {
        this->m_enSatSys = enSatelliteSystem;
    }

    std::string IGnssDataInterface::GetName() const
    {
        return this->m_strName;
    }

    void IGnssDataInterface::SetName(const std::string& strName)
    {
        this->m_strName = strName;
    }

    // Struct define
    void SSignalValue::InitData()
    {
        m_dbFinePseudoranges = 0.0;
        m_dbFinePhaserange = 0.0;
        m_ui8LockTimeIndicator = 0U;
        m_dbSignalCnr = 0.0;
        m_dbFPRates = 0.0;
        m_dbFinePseudorangesWithER = 0.0;
        m_dbFinePhaserangeWithER = 0.0;
        m_ui16PLTIWithERAR = 0U;
        m_dbSignalCnrsWER = 0.0;
        m_ui8HCAI = 0U;
        m_dbPseudoranges = 0.0;
        m_dbPhaserange = 0.0;
        m_dbPhaseRangeRate = 0.0;
    }

    void SSatelliteValue::InitData()
    {
        m_ui8Milliseconds = 0U;
        m_ui8ExtendedSatInfo = 0U;
        m_dbModulo1Millisecond = 0.0;
        m_i32RoughPhaseRangeRates = 0;
        m_ui8SatFrequencyChannelNumber = 255U;

        for (auto stSignal : m_mapSignalValues)
        {
            stSignal.second.InitData();
        }
        m_mapSignalValues.clear();
    }

    void SEpochSatObs::InitData()
    {
        m_ui16MsgType = 0U;
        m_ui32GmNtiRefStationID = 0U;
        m_ui8DayOfWeek = 0U;
        m_ui32GnssEpochTime = 0U;
        m_ui8MultiMsgBit = 0U;
        m_ui8IODS = 0U;
        m_i8Reserved = 0;
        m_ui8ClockSteeringIndicator = 0U;
        m_ui8ExternalClockIndicator = 0U;
        m_ui8GnssSmoothingIndicator = 0U;
        m_ui8GnssSmoothingInterval = 0U;
        m_ui64SatMask = 0U;
        m_ui32SignalMask = 0U;
        m_ui64CellMask = 0U;
        for (auto stSat : m_mapSatValues)
        {
            stSat.second.InitData();
        }
        m_mapSatValues.clear();
    }

    void SEphemeris::InitData()
    {
        m_ui16MsgType = 0U;
        m_ui8SatId = 0U;
        m_ui16WeekNum = 0U;
        m_ui8URA = 0U;
        m_ui8CodeOnL2 = 0U;
        m_dbIdot = 0.0;
        m_ui8Iode = 0U;
        m_ui32Toc = 0U;
        m_dbAf2 = 0.0;
        m_dbAf1 = 0.0;
        m_dbAf0 = 0.0;
        m_ui16Iodc = 0U;
        m_dbCrs = 0.0;
        m_dbDeltaN = 0.0;
        m_dbM0 = 0.0;
        m_dbCuc = 0.0;
        m_dbEccentricity = 0.0;
        m_dbCus = 0.0;
        m_dbAHalf = 0.0;
        m_ui32Toe = 0U;
        m_dbCic = 0.0;
        m_dbOmega0 = 0.0;
        m_dbCis = 0.0;
        m_dbI0 = 0.0;
        m_dbCrc = 0.0;
        m_dbArgumentOfPerigee = 0.0;
        m_dbOmegaDot = 0.0;
        m_dbIODot = 0.0;
        m_dbTgd = 0.0;
        m_ui8SvHealth = 0U;
        m_ui8L2PDataFlag = 0U;
        m_ui8FitInterval = 0U;
        m_ui8SISAIndex = 0U;
        m_ui16IODnav = 0U;
        m_ui8SvSisa = 0U;
        m_dbBgdE1E5a = 0.0;
        m_dbBgdE5bE1 = 0.0;
        m_ui8OSHS = 0U;
        m_ui8OSDVS = 0U;
        m_ui8E5bSignalHealthStatus = 0U;
        m_ui8E5bDataValidityStatus = 0U;
        m_ui8E1bSignalHealthStatus = 0U;
        m_ui8E1bDataValidityStatus = 0U;
        m_ui8AgeOfDataEphemeris = 0U;
        m_ui8AgeOfDataClock = 0U;
        m_dbTgd1 = 0.0;
        m_dbTgd2 = 0.0;
        m_ui8Reserved = 0U;
    }

    void SGlonassEphemeris::InitData()
    {
        m_ui16MsgType = 0U;
        m_ui8SatId = 0U;
        m_ui8SatFrequencyChannelNumber = 0U;
        m_ui8AlmanacHealth = 0U;
        m_ui8AHAI = 0U;
        m_ui8P1 = 0U;
        m_ui16Tk = 0U;
        m_ui8MsbOfBn = 0U;
        m_ui8P2 = 0U;
        m_ui16Tb = 0U;
        m_dbXnTbFirstDerivative = 0.0;
        m_dbXnTb = 0.0;
        m_dbXnTbSecondDerivative = 0.0;
        m_dbYnTbFirstDerivative = 0.0;
        m_dbYnTb = 0.0;
        m_dbYnTbSecondDerivative = 0.0;
        m_dbZnTbFirstDerivative = 0.0;
        m_dbZnTb = 0.0;
        m_dbZnTbSecondDerivative = 0.0;
        m_ui8P3 = 0U;
        m_dbGammaTb = 0.0;
        m_ui8GmP = 0U;
        m_ui8GmLn3 = 0U;
        m_dbTnTb = 0.0;
        m_dbGmDeltaTn = 0.0;
        m_ui8En = 0U;
        m_ui8GmP4 = 0U;
        m_ui8GmFt = 0U;
        m_ui16GmNt = 0U;
        m_ui8GmM = 0U;
        m_ui8AOAD = 0U;
        m_ui16NA = 0U;
        m_dbTc = 0.0;
        m_ui8GmN4 = 0U;
        m_dbGmTGps = 0.0;
        m_ui8GmLn5 = 0U;
        m_ui8Reserved = 0U;
    }

    void SReferenceInfo::InitData()
    {
        m_ui16MsgType = 0U;
        m_ui16RefStaionId = 0U;
        m_ui8ItrfYear = 0U;
        m_ui8GPSIndicator = 0U;
        m_ui8GlonassIndicator = 0U;
        m_ui8GalileoIndicator = 0U;
        m_ui8RefStationIndicator = 0U;
        m_dbArpEcefX = 0.0;
        m_ui8SingleROI = 0U;
        m_ui8BDSIndicator = 0U;
        m_dbArpEcefY = 0.0;
        m_ui8QuarterCycleIndicator = 0U;
        m_dbArpEcefZ = 0.0;
        m_dbAntennaHeight = 0.0;
        m_ui16PhysicalRefStationId = 0U;
        m_ui8DescriptorCount = 0U;
        m_objAntennaDescriptor = {0};
        m_ui8AntennaSetupId = 0U;
        m_ui8SerialNumberCount = 0U;
        m_objAntennaSerialNumber = {0};
        m_ui8RTDC = 0U;
        m_objReceiverTypeDescriptor = {0};
        m_ui8RFVC = 0U;
        m_objReceiverFirmwareVersion = {0};
        m_ui8ReceiverSerialNumberCount = 0U;
        m_objReceiverSerialNumber = {0};
    }

    void SOrbitCorrectionInfo::InitData()
    {
        m_ui8SatId = 0U;
        m_ui8IODE = 0U;
        m_dbDeltaRadial = 0.0;
        m_dbDeltaAlongTrack = 0.0;
        m_dbDeltaCrossTrack = 0.0;
        m_dbDotDeltaRadial = 0.0;
        m_dbDotDeltaAlongTrack = 0.0;
        m_dbDotDeltaCrossTrack = 0.0;
    }

    void SOrbitCorrection::InitData()
    {
        m_ui16MsgType = 0U;
        m_ui32EpochTime = 0U;
        m_ui32SSRUpdateInterval = 0U;
        m_ui8MulMsgIndicator = 0U;
        m_ui8SatRefDatum = 0U;
        m_ui8IodSsr = 0U;
        m_ui32SsrProviderID = 0U;
        m_ui8SsrSolutionID = 0U;
        m_ui8SatNum = 0U;

        for (auto stOrbitCorrectionInfo : m_mapOrbitCorrectionInfo)
        {
            stOrbitCorrectionInfo.second.InitData();
        }
        m_mapOrbitCorrectionInfo.clear();
    }

    void SClockCorrectionInfo::InitData()
    {
        m_ui8SatId = 0U;
        m_dbDeltaC0 = 0.0;
        m_dbDeltaC1 = 0.0;
        m_dbDeltaC2 = 0.0;
        m_dbDeltaHighFrequencyNum = 0.0;
    }

    void SClockCorrection::InitData()
    {
        m_ui16MsgType = 0U;
        m_ui32EpochTime = 0U;
        m_ui32SSRUpdateInterval = 0U;
        m_ui8MulMsgIndicator = 0U;
        m_ui8IodSsr = 0U;
        m_ui32SsrProviderID = 0U;
        m_ui8SsrSolutionID = 0U;
        m_ui8SatNum = 0U;

        for (auto stClockCorrectionInfo : m_mapClockCorrectionInfo)
        {
            stClockCorrectionInfo.second.InitData();
        }
        m_mapClockCorrectionInfo.clear();
    }

    void SOrbitClockCorrectionInfo::InitData()
    {
        m_ui8SatId = 0U;
        m_ui8IODE = 0U;
        m_db8DeltaRadial = 0.0;
        m_dbDeltaAlongTrack = 0.0;
        m_dbDeltaCrossTrack = 0.0;
        m_dbDotDeltaRadial = 0.0;
        m_dbDotDeltaAlongTrack = 0.0;
        m_dbDotDeltaCrossTrack = 0.0;
        m_dbDeltaC0 = 0.0;
        m_dbDeltaC1 = 0.0;
        m_dbDeltaC2 = 0.0;
    }

    void SOrbitClockCorrection::InitData()
    {
        m_ui16MsgType = 0U;
        m_ui32EpochTime = 0U;
        m_ui32SSRUpdateInterval = 0U;
        m_ui8MulMsgIndicator = 0U;
        m_ui8SatRefDatum = 0U;
        m_ui8IodSsr = 0U;
        m_ui32SsrProviderID = 0U;
        m_ui8SsrSolutionID = 0U;
        m_ui8SatNum = 0U;

        for (auto stOrbitClockCorrectionInfo : m_mapOrbitClockCorrectionInfo)
        {
            stOrbitClockCorrectionInfo.second.InitData();
        }
        m_mapOrbitClockCorrectionInfo.clear();
    }

    void SDcbInfo::InitData()
    {
        m_ui8SignalTrackingModeIndicator = 0U;
        m_dbCodeBias = 0.0;
    }

    void SDcbSatInfo::InitData()
    {
        m_ui8SatId = 0U;
        m_ui8SsrUraNum = 0U;

        for (auto stDcbInfo : m_mapDcbInfo)
        {
            stDcbInfo.second.InitData();
        }
        m_mapDcbInfo.clear();
    }

    void SDcb::InitData()
    {
        m_ui16MsgType = 0U;
        m_ui32EpochTime = 0U;
        m_ui32SSRUpdateInterval = 0U;
        m_ui8MulMsgIndicator = 0U;
        m_ui8IodSsr = 0U;
        m_ui32SsrProviderID = 0U;
        m_ui8SsrSolutionID = 0U;
        m_ui8SatNum = 0U;

        for (auto stDcbSatInfo : m_mapDcbSatInfo)
        {
            stDcbSatInfo.second.InitData();
        }
        m_mapDcbSatInfo.clear();
    }

    void SUraInfo::InitData()
    {
        m_ui8SatId = 0U;
        m_ui8SsrUra = 0U;
    }

    void SUra::InitData()
    {
        m_ui16MsgType = 0U;
        m_ui32EpochTime = 0U;
        m_ui32SSRUpdateInterval = 0U;
        m_ui8MulMsgIndicator = 0U;
        m_ui8IodSsr = 0U;
        m_ui32SsrProviderID = 0U;
        m_ui8SsrSolutionID = 0U;
        m_ui8SatNum = 0U;

        for (auto stUraInfo : m_mapUraInfo)
        {
            stUraInfo.second.InitData();
        }
        m_mapUraInfo.clear();
    }
    // Class define
    // CEpochObs
    CEpochObs::CEpochObs()
        : IGnssDataInterface()
    {
        this->m_enDataType = GDT_OBS;
    }

    CEpochObs::~CEpochObs()
    {}

    const SEpochSatObs& CEpochObs::GetEpochSatObs() const
    {
        return this->m_stEpochSatObs;
    }

    void CEpochObs::InitData()
    {
        m_stEpochSatObs.InitData();
    }

    void CEpochObs::SetEpochSatObs(const SEpochSatObs& stEpochSatObs)
    {
        this->m_stEpochSatObs = std::move(stEpochSatObs);
    }

    SSatelliteValue* CEpochObs::GetSatellite(const INT32 i32SatId)
    {
        SSatelliteValue* pSatallite = nullptr;
        const auto iter = m_stEpochSatObs.m_mapSatValues.find(i32SatId);
        if ((i32SatId < MIN_SAT_ID) || (i32SatId > MAX_SAT_ID) || iter == m_stEpochSatObs.m_mapSatValues.end())
        {
            return pSatallite;
        }

        pSatallite = &m_stEpochSatObs.m_mapSatValues.at(i32SatId);

        return pSatallite;
    }
    SSignalValue* CEpochObs::GetSignal(const INT32 i32SatId, const IGnssDataInterface::SignalCode enSigCode)
    {
        SSignalValue* pSignal = nullptr;
        SSatelliteValue* const pSatallite = GetSatellite(i32SatId);
        if (pSatallite == nullptr)
        {
            return pSignal;
        }

        const UINT32 ui32SigId =
            static_cast< UINT32 >(enSigCode) & static_cast< UINT32 >(IGnssDataInterface::SC_REMOVE_MASK);
        const auto iter = pSatallite->m_mapSignalValues.find(static_cast< INT32 >(ui32SigId));
        if (iter == pSatallite->m_mapSignalValues.end())
        {
            return pSignal;
        }

        pSignal = &pSatallite->m_mapSignalValues.at(static_cast< INT32 >(ui32SigId));

        return pSignal;
    }

    DOUBLE CEpochObs::GetSignalStrength(const INT32 i32SatId, const IGnssDataInterface::SignalCode enSigCode)
    {
        DOUBLE dbSignalStrength = 0.0;
        auto satIter = m_stEpochSatObs.m_mapSatValues.find(i32SatId);
        if (satIter != m_stEpochSatObs.m_mapSatValues.end())
        {
            const UINT32 ui32SigId =
                static_cast< UINT32 >(enSigCode) & static_cast< UINT32 >(IGnssDataInterface::SC_REMOVE_MASK);
            auto sigIter = satIter->second.m_mapSignalValues.find(static_cast< INT32 >(ui32SigId));
            if (sigIter != satIter->second.m_mapSignalValues.end())
            {
                dbSignalStrength = sigIter->second.m_dbSignalCnr * static_cast<DOUBLE>(common::rtcm::SCALE_SIGNAL_STRENGTH);
            }
        }

        return dbSignalStrength;
    }

    DOUBLE CEpochObs::GetPseudorange(const INT32 i32SatId, const IGnssDataInterface::SignalCode enSigCode)
    {
        DOUBLE dbPseudorange = 0.0;
        auto satIter = m_stEpochSatObs.m_mapSatValues.find(i32SatId);
        if (satIter != m_stEpochSatObs.m_mapSatValues.end())
        {
            const UINT32 ui32SigId =
                static_cast< UINT32 >(enSigCode) & static_cast< UINT32 >(IGnssDataInterface::SC_REMOVE_MASK);
            auto sigIter = satIter->second.m_mapSignalValues.find(static_cast< INT32 >(ui32SigId));
            if (sigIter != satIter->second.m_mapSignalValues.end())
            {
                dbPseudorange = sigIter->second.m_dbPseudoranges;
            }
        }

        return dbPseudorange;
    }

    DOUBLE CEpochObs::GetPhaseRange(const INT32 i32SatId, const IGnssDataInterface::SignalCode enSigCode)
    {
        auto satIter = m_stEpochSatObs.m_mapSatValues.find(i32SatId);
        if (satIter != m_stEpochSatObs.m_mapSatValues.end())
        {
            const UINT32 ui32SigId =
                static_cast< UINT32 >(enSigCode) & static_cast< UINT32 >(IGnssDataInterface::SC_REMOVE_MASK);
            auto sigIter = satIter->second.m_mapSignalValues.find(static_cast< INT32 >(ui32SigId));
            if (sigIter != satIter->second.m_mapSignalValues.end())
            {
                const auto wl = CCodecUtilities::GetSatWaveLen(
                    GetSatelliteSystemType(), enSigCode, satIter->second.m_ui8SatFrequencyChannelNumber);
                if (!CCodecUtilities::DoubleEqualToZero(wl))
                {
                    return sigIter->second.m_dbPhaserange / wl;
                }
            }
        }
        return 0.0;
    }

    DOUBLE CEpochObs::GetPhaseRangeRate(const INT32 i32SatId, const IGnssDataInterface::SignalCode enSigCode)
    {
        auto satIter = m_stEpochSatObs.m_mapSatValues.find(i32SatId);
        if (satIter != m_stEpochSatObs.m_mapSatValues.end())
        {
            const UINT32 ui32SigId =
                static_cast< UINT32 >(enSigCode) & static_cast< UINT32 >(IGnssDataInterface::SC_REMOVE_MASK);
            auto sigIter = satIter->second.m_mapSignalValues.find(static_cast< INT32 >(ui32SigId));
            if (sigIter != satIter->second.m_mapSignalValues.end())
            {
                const auto wl = CCodecUtilities::GetSatWaveLen(
                    GetSatelliteSystemType(), enSigCode, satIter->second.m_ui8SatFrequencyChannelNumber);
                if (!CCodecUtilities::DoubleEqualToZero(wl))
                {
                    return sigIter->second.m_dbPhaseRangeRate / wl;
                }
            }
        }
        return 0.0;
    }

    // CEphemeris
    CEphemeris::CEphemeris()
        : IGnssDataInterface()
    {
        this->m_enDataType = GDT_EPH;
    }

    CEphemeris::~CEphemeris()
    {}

    void CEphemeris::InitData()
    {
        m_stEphemeris.InitData();
    }

    const SEphemeris& CEphemeris::GetEphemeris() const
    {
        return this->m_stEphemeris;
    }

    void CEphemeris::SetEphemeris(const SEphemeris& stEphemeris)
    {
        this->m_stEphemeris = std::move(stEphemeris);
    }

    // CGlonassEphemeris
    CGlonassEphemeris::CGlonassEphemeris()
        : IGnssDataInterface()
    {
        this->m_enDataType = GDT_GLO_EPH;
    }

    CGlonassEphemeris::~CGlonassEphemeris()
    {}

    void CGlonassEphemeris::InitData()
    {
        m_stGlonassEphemeris.InitData();
    }

    const SGlonassEphemeris& CGlonassEphemeris::GetGlonassEphemeris() const
    {
        return this->m_stGlonassEphemeris;
    }
    void CGlonassEphemeris::SetGlonassEphemeris(const SGlonassEphemeris& stGlonassEphemeris)
    {
        this->m_stGlonassEphemeris = std::move(stGlonassEphemeris);
    }

    // CReferenceInfo
    CReferenceInfo::CReferenceInfo()
        : IGnssDataInterface()
    {
        this->m_enDataType = GDT_REF_INFO;
    }

    CReferenceInfo::~CReferenceInfo()
    {}

    void CReferenceInfo::InitData()
    {
        m_stReferenceInfo.InitData();
    }

    const SReferenceInfo& CReferenceInfo::GetReferenceInfo() const
    {
        return this->m_stReferenceInfo;
    }

    void CReferenceInfo::SetReferenceInfo(const SReferenceInfo& stReferenceInfo)
    {
        this->m_stReferenceInfo = std::move(stReferenceInfo);
    }

    // COrbitCorrection
    COrbitCorrection::COrbitCorrection()
        : IGnssDataInterface()
    {
        this->m_enDataType = GDT_ORBIT;
    }

    COrbitCorrection::~COrbitCorrection()
    {}

    void COrbitCorrection::InitData()
    {
        m_stOrbitCorrection.InitData();
    }

    SOrbitCorrection& COrbitCorrection::GetOrbitCorrection()
    {
        return this->m_stOrbitCorrection;
    }

    void COrbitCorrection::SetOrbitCorrection(const SOrbitCorrection& stOrbitCorrection)
    {
        this->m_stOrbitCorrection = std::move(stOrbitCorrection);
    }

    // CClockCorrection
    CClockCorrection::CClockCorrection()
        : IGnssDataInterface()
    {
        this->m_enDataType = GDT_CLOCK;
    }

    CClockCorrection::~CClockCorrection()
    {}

    void CClockCorrection::InitData()
    {
        m_stClockCorrection.InitData();
    }

    SClockCorrection& CClockCorrection::GetClockCorrection()
    {
        return this->m_stClockCorrection;
    }

    void CClockCorrection::SetClockCorrection(const SClockCorrection& stSatClock)
    {
        this->m_stClockCorrection = std::move(stSatClock);
    }

    // COrbitClockCorrection
    COrbitClockCorrection::COrbitClockCorrection()
        : IGnssDataInterface()
    {
        this->m_enDataType = GDT_ORBIT_CLOCK;
    }

    COrbitClockCorrection::~COrbitClockCorrection()
    {}

    void COrbitClockCorrection::InitData()
    {
        m_stOrbitClockCorrection.InitData();
    }

    SOrbitClockCorrection& COrbitClockCorrection::GetOrbitClockCorrection()
    {
        return this->m_stOrbitClockCorrection;
    }

    void COrbitClockCorrection::SetOrbitClockCorrection(const SOrbitClockCorrection& stOrbitClockCorrection)
    {
        this->m_stOrbitClockCorrection = std::move(stOrbitClockCorrection);
    }

    // CDcb
    CDcb::CDcb()
        : IGnssDataInterface()
    {
        this->m_enDataType = GDT_DCB;
    }

    CDcb::~CDcb()
    {}

    void CDcb::InitData()
    {
        m_stDcb.InitData();
    }

    const SDcb& CDcb::GetDcb() const
    {
        return this->m_stDcb;
    }

    void CDcb::SetDcb(const SDcb& stDcb)
    {
        this->m_stDcb = std::move(stDcb);
    }

    // CUra
    CUra::CUra()
        : IGnssDataInterface()
    {
        this->m_enDataType = GDT_URA;
    }

    CUra::~CUra()
    {}

    void CUra::InitData()
    {
        m_stUra.InitData();
    }

    const SUra& CUra::GetUra() const
    {
        return this->m_stUra;
    }

    void CUra::SetUra(const SUra& stUra)
    {
        this->m_stUra = std::move(stUra);
    }
} // namespace sixents
