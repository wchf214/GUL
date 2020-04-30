#include "ITimeLeap.h"
namespace sixents
{
    namespace GNSSUtilityLib
    {
        ITimeLeap::ITimeLeap(const TIME_TYPE timeType)
        {
            m_timeType = timeType;
        }

        ITimeLeap::~ITimeLeap()
        {

        }

        TIME_TYPE ITimeLeap::GetTimeType() const
        {
            return m_timeType;
        }

    }      // end namespace GNSSUtilityLib
} // end namespace sixents
