#include "CGPSTimeLeap.h"

namespace sixents
{
namespace GNSSUtilityLib
{

CGPSTimeLeap::CGPSTimeLeap(const TIME_TYPE timeType)
    : ITimeLeap(timeType)
{

}

CGPSTimeLeap::~CGPSTimeLeap()
{

}

DOUBLE CGPSTimeLeap::GetLeapTime(const DOUBLE timeSec, const TIME_TYPE timeType)
{
    DOUBLE retLeapTime = 0.0;
    const DOUBLE MINUS_FLAG = -1.0;
    switch (timeType) {
    case UTC:

        break;
    case BDS:
        retLeapTime = MINUS_FLAG * SEC_BETWEEN_GPS_BDS;
        break;
    default:
        break;
    }
    return  retLeapTime;
}

    }      // end namespace GNSSUtilityLib
} // end namespace sixents
