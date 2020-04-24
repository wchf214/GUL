#include "IGNSSTime.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        IGNSSTime::IGNSSTime()
        {
            m_timeType = 0;
        }

        IGNSSTime::~IGNSSTime()
        {}

        void IGNSSTime::SetTime(const DOUBLE& time)
        {}

        void IGNSSTime::GetTime(DOUBLE& time) const
        {}

        void IGNSSTime::SetTime(const SStandardTime& time)
        {}

        void IGNSSTime::GetTime(SStandardTime& time) const
        {}

        void IGNSSTime::SetTime(const SGNSSTime& time)
        {}

        void IGNSSTime::GetTime(SGNSSTime& time) const
        {}

        void IGNSSTime::ToWeekSec(SGNSSTime& time) const
        {}

        INT32 IGNSSTime::GetTimeType()
        {
            return m_timeType;
        }

    } // end namespace GNSSUtilityLib
} // end namespace sixents