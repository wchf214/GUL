#include "CTimeLeapFactory.h"
namespace sixents
{
    namespace GNSSUtilityLib
    {
        ITimeLeap* CTimeLeapFactory::CreateTimeLeapObj(const TIME_TYPE timeType)
        {
            ITimeLeap* leapObj = nullptr;
            switch (timeType) {
            case UTC:
//                leapObj = new CUTCTimeLeap(timeType);
                break;
            case GPS:
                leapObj = new CGPSTimeLeap(timeType);
                break;
            default:
                break;
            }
            return leapObj;
        }
    }      // end namespace GNSSUtilityLib
} // end namespace sixents
