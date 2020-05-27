#include "IGNSSEphemeris.h"

#include <cmath>
#include <cstring>

namespace sixents
{
    namespace Math
    {
        IGNSSEphemeris::IGNSSEphemeris()
        {
            InitVar();
        }

        IGNSSEphemeris::~IGNSSEphemeris()
        {}

        DOUBLE IGNSSEphemeris::GetCurTime() const
        {
            return m_curTime;
        }

        void IGNSSEphemeris::InitVar()
        {
            m_clock = DOUBLE_ZONE_LITTLE;
            memset(&m_pos, 0, sizeof(SXYZ));
            m_curTime = DOUBLE_ZONE_LITTLE;
        }

        DOUBLE IGNSSEphemeris::GetClock()
        {
            return m_clock;
        }

        void IGNSSEphemeris::SetClock(const DOUBLE clock)
        {
            m_clock = clock;
        }

        SXYZ IGNSSEphemeris::GetPos()
        {
            return m_pos;
        }

        void IGNSSEphemeris::SetPos(const SXYZ& pos)
        {
            m_pos = std::move(pos);
        }

        void IGNSSEphemeris::SetPos(const DOUBLE x, const DOUBLE y, const DOUBLE z)
        {
            m_pos.m_x = x;
            m_pos.m_y = y;
            m_pos.m_z = z;
        }

        INT32 IGNSSEphemeris::SetCurTime(const DOUBLE time)
        {
            if (time < 0)
            {
                return RETURN_ERROR_PARAMETER;
            }
            m_curTime = time;
            return RETURN_SUCCESS;
        }
    } // namespace Math
} // namespace sixents