#include "CTimeFactory.h"
#include "CBDSTime.h"
#include "CGPSTime.h"
#include "CGalileoTime.h"
#include "CGlonassTime.h"
#include "CUTCTime.h"

namespace sixents
{
    namespace Math
    {
        IGNSSTime* CTimeFactory::CreateTimeObj(const TIME_TYPE timeType)
        {
            IGNSSTime* timeObj = nullptr;
            switch (timeType)
            {
                case UTC:
                    timeObj = new CUTCTime(timeType);
                    break;
                case BDS:
                    timeObj = new CBDSTime(timeType);
                    break;
                case GLONASS:
                    timeObj = new CGlonassTime(timeType);
                    break;
                case GALILEO:
                    timeObj = new CGalileoTime(timeType);
                    break;
                case GPS:
                    timeObj = new CGPSTime(timeType);
                    break;
                default:
                    break;
            }
            return timeObj;
        }
    } // end namespace Math
} // end namespace sixents
