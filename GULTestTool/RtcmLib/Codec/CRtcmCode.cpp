#include "CRtcmCode.h"

namespace sixents
{
    CRtcmCode::CRtcmCode()
        : ICodecOpt()
    {
        m_pobjLog = nullptr;
        m_pobjCfgMng = nullptr;
    }

    CRtcmCode::~CRtcmCode()
    {}

    BOOL_T CRtcmCode::Init(CLog* const pobjLog, CCfgMng* const pobjCfgMng)
    {
        if ((pobjLog == nullptr) || (pobjCfgMng == nullptr))
        {
            return false;
        }

        m_pobjLog = pobjLog;
        m_pobjCfgMng = pobjCfgMng;

        return true;
    }

    sixents::INT32 CRtcmCode::RtcmDecode(CParam& pamIn, CParam& pamOut)
    {
        return m_objDecoder.RtcmDecode(pamIn, pamOut);
    }

    sixents::INT32 CRtcmCode::RtcmEncode(CParam& pamIn, CParam& pamOut)
    {
        return m_objEncoder.RtcmEncode(pamIn, pamOut);
    }

} // namespace sixents