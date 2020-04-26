#include "CCalcTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {

        DOUBLE CCalcTime::TimeConvert(const DOUBLE srcSec, const TIME_TYPE srctimeType, const TIME_TYPE destTimeType)
        {
//            DOUBLE leapSec = GetLeapTime(srctimeType);
            DOUBLE leapSec = 0.0;
            if (srctimeType == destTimeType)
            {
                return srcSec;
            }
            else if (srctimeType > destTimeType)
            {
                return srcSec - leapSec;
            }
            else
            {
                return srcSec + leapSec;
            }
        }
    }      // end namespace GNSSUtilityLib
} // end namespace sixents
