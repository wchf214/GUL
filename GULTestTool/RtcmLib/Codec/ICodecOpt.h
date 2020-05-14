#ifndef _ICODEC_OPT_H_
#define _ICODEC_OPT_H_

#include "../Framework/CParam.h"
#include "../Framework/CValue.h"
#include "../Framework/Constants.h"
#include "../GnssData/IGnssDataInterface.h"
#include "../Platform/BasicType.h"

namespace sixents
{
    class ICodecOpt
    {
    public:
        ICodecOpt();
        virtual ~ICodecOpt();

    public:
        virtual INT32 RtcmDecode(CParam& pamIn, CParam& pamOut) = 0;
        virtual INT32 RtcmEncode(CParam& pamIn, CParam& pamOut) = 0;
    };
}
#endif  //_ICODEC_OPT_H_
