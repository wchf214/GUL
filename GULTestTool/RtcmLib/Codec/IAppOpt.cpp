#define DLL_EXPORT

#include "IAppOpt.h"
#include "CAppImpl.h"

namespace sixents
{
    extern "C" DLL_API INT32 STD_CALL RtcmInit(CParam& pamIn, CParam& pamOut)
    {
//         return IAppOpt::CreateInstance()->RtcmInit(pamIn, pamOut);
        return CAppImpl::GetSingletonInstance()->RtcmInit(pamIn, pamOut);
    }

    extern "C" DLL_API INT32 STD_CALL RtcmGetMessage(
        const BYTE* const pbyBuf, const UINT32& uiLen, UINT32& uiMsgType, UINT32& uiMsgPos, UINT32& uiExpectLen)
    {
//        return IAppOpt::CreateInstance()->RtcmGetMessage(pbyBuf, uiLen, uiMsgType, uiMsgPos, uiExpectLen);
         return CAppImpl::GetSingletonInstance()->RtcmGetMessage(pbyBuf, uiLen, uiMsgType, uiMsgPos, uiExpectLen);
    }

    extern "C" DLL_API INT32 STD_CALL RtcmDecode(CParam& pamIn, CParam& pamOut)
    {
//        return IAppOpt::CreateInstance()->RtcmDecode(pamIn, pamOut);
          return CAppImpl::GetSingletonInstance()->RtcmDecode(pamIn, pamOut);
    }

    extern "C" DLL_API INT32 STD_CALL RtcmEncode(CParam& pamIn, CParam& pamOut)
    {
//        return IAppOpt::CreateInstance()->RtcmEncode(pamIn, pamOut);
          return CAppImpl::GetSingletonInstance()->RtcmEncode(pamIn, pamOut);
    }

    extern "C" DLL_API INT32 STD_CALL RtcmCmd(CParam& pamIn, CParam& pamOut)
    {
//        return IAppOpt::CreateInstance()->RtcmCmd(pamIn, pamOut);
          return CAppImpl::GetSingletonInstance()->RtcmCmd(pamIn, pamOut);
    }

    extern "C" DLL_API INT32 STD_CALL RtcmFinal()
    {
//        return IAppOpt::CreateInstance()->RtcmFinal();
         return CAppImpl::GetSingletonInstance()->RtcmFinal();
    }

    IAppOpt::IAppOpt()
    {}

    IAppOpt::~IAppOpt()
    {}

    std::unique_ptr< sixents::IAppOpt > sixents::IAppOpt::CreateInstance()
    {
        std::unique_ptr< sixents::IAppOpt > instance = std::make_unique< CAppImpl >();
        return std::move(instance);
    }
} // namespace sixents
