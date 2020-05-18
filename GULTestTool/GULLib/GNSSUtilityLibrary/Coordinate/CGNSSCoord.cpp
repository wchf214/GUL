#include "CGNSSCoord.h"
#include <cmath>
#include "../Angle/CGNSSAngle.h"
#include "../DllMain/GNSSCommonDef.h"

namespace sixents
{
    namespace Math
    {
        CGNSSCoordinate::CGNSSCoordinate()
        {}

        CGNSSCoordinate::CGNSSCoordinate(const DOUBLE x,
                                         const DOUBLE y,
                                         const DOUBLE z,
                                         const COORDINATE_TYPE coordinateType)
        {
            if (coordinateType == BLH)
            {
                m_geoCoordinate.m_lat = x;
                m_geoCoordinate.m_lon = y;
                m_geoCoordinate.m_height = z;

                BLH2XYZ(m_geoCoordinate.m_lat,
                        m_geoCoordinate.m_lon,
                        m_geoCoordinate.m_height,
                        m_spaceCoordinate.m_x,
                        m_spaceCoordinate.m_y,
                        m_spaceCoordinate.m_z);
            }
            else if (coordinateType == XYZ)
            {
                m_spaceCoordinate.m_x = x;
                m_spaceCoordinate.m_y = y;
                m_spaceCoordinate.m_z = z;
                XYZ2BLH(m_spaceCoordinate.m_x,
                        m_spaceCoordinate.m_y,
                        m_spaceCoordinate.m_z,
                        m_geoCoordinate.m_lat,
                        m_geoCoordinate.m_lon,
                        m_geoCoordinate.m_height);
            }
            else
            {
                m_geoCoordinate.m_lat = 0.0;
                m_geoCoordinate.m_lon = 0.0;
                m_geoCoordinate.m_height = 0.0;
                m_spaceCoordinate.m_x = 0.0;
                m_spaceCoordinate.m_y = 0.0;
                m_spaceCoordinate.m_z = 0.0;
            }
            m_stationCoordinate.m_east = 0.0;
            m_stationCoordinate.m_north = 0.0;
            m_stationCoordinate.m_up = 0.0;
        }

        void CGNSSCoordinate::SetXYZ(const SXYZ& coordinate)
        {
            m_spaceCoordinate.m_x = coordinate.m_x;
            m_spaceCoordinate.m_y = coordinate.m_y;
            m_spaceCoordinate.m_z = coordinate.m_z;
            XYZ2BLH(m_spaceCoordinate.m_x,
                    m_spaceCoordinate.m_y,
                    m_spaceCoordinate.m_z,
                    m_geoCoordinate.m_lat,
                    m_geoCoordinate.m_lon,
                    m_geoCoordinate.m_height);
        }

        SXYZ CGNSSCoordinate::GetXYZ() const
        {
            return m_spaceCoordinate;
        }

        void CGNSSCoordinate::SetBLH(const SBLH& coordinate)
        {
            m_geoCoordinate.m_lat = coordinate.m_lat;
            m_geoCoordinate.m_lon = coordinate.m_lon;
            m_geoCoordinate.m_height = coordinate.m_height;
            BLH2XYZ(m_geoCoordinate.m_lat,
                    m_geoCoordinate.m_lon,
                    m_geoCoordinate.m_height,
                    m_spaceCoordinate.m_x,
                    m_spaceCoordinate.m_y,
                    m_spaceCoordinate.m_z);
        }

        SBLH CGNSSCoordinate::GetBLH() const
        {
            return m_geoCoordinate;
        }

        INT32 CGNSSCoordinate::CalcLat(const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lat) const
        {
            DOUBLE tempLat1 = 0.0;
            DOUBLE tempLat2 = 0.0;
            DOUBLE N = 0.0;
            tempLat2 = atan(z / sqrt(x * x + y * y));
            while (true)
            {
                tempLat1 = tempLat2;
                N = WGS84_EARTH_LONG_RADIUS
                    / sqrt(static_cast<DOUBLE>(NUM_ONE) - WGS84_FIRST_E2 * sin(tempLat1) * sin(tempLat1));
                tempLat2 = atan((z + N * WGS84_FIRST_E2 * sin(tempLat1)) / sqrt(x * x + y * y));
                if (fabs(tempLat2 - tempLat1) < LAT_ACCURACY)
                {
                    lat = tempLat2;
                    break;
                }
            }
            return RETURN_SUCCESS;
        }

        INT32 CGNSSCoordinate::BLH2XYZ(
            const DOUBLE lat, const DOUBLE lon, const DOUBLE height, DOUBLE& x, DOUBLE& y, DOUBLE& z)
        {
            INT32 iRet = RETURN_FAIL;

            do
            {
                if (lat < LATITUDE_LOWER_LIMIT || lat > LATITUDE_UPPER_LIMIT || lon < LONGITUDE_LOWER_LIMIT
                    || lon > LONGITUDE_UPPER_LIMIT)
                {
                    iRet = RETURN_ERROR_PARAMETER;
                    break;
                }

                const DOUBLE sinLat = sin(lat * D2R);
                const DOUBLE cosLat = cos(lat * D2R);
                const DOUBLE sinLon = sin(lon * D2R);
                const DOUBLE cosLon = cos(lon * D2R);

                //计算代表卯酉圈曲率半径N，公式 a / Sqrt(1 - e2 * sinB * sinB)
                DOUBLE N =
                    WGS84_EARTH_LONG_RADIUS / sqrt(static_cast<DOUBLE>(NUM_ONE) - WGS84_FIRST_E2 * sinLat * sinLat);

                x = (N + height) * cosLat * cosLon;
                y = (N + height) * cosLat * sinLon;
                z = (N * (static_cast<DOUBLE>(NUM_ONE) - WGS84_FIRST_E2) + height) * sinLat;
                iRet = RETURN_SUCCESS;
            } while (false);
            return iRet;
        }

        INT32 CGNSSCoordinate::XYZ2BLH(
            const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lat, DOUBLE& lon, DOUBLE& height)
        {
            //计算经度，单位弧度
            if (x > LAT_ACCURACY)
            {
                lon = atan(y / x);
            }
            else if (x < -LAT_ACCURACY)
            {
                lon = atan(y / x) + PI;
            }
            else
            {
                if (y > 0)
                    lon = PI * ZERO_POINT_FIVE;
                else
                    lon = PI * ONE_POINT_FIVE;
            }

            //计算纬度，单位弧度
            CalcLat(x, y, z, lat);

            //计算代表卯酉圈曲率半径N，公式 a / Sqrt(1 - e2 * sinB * sinB)
            DOUBLE N =
                WGS84_EARTH_LONG_RADIUS / sqrt(static_cast<DOUBLE>(NUM_ONE) - WGS84_FIRST_E2 * sin(lat) * sin(lat));
            //计算高程
            height =
                sqrt(x * x + y * y) * cos(lat) + z * sin(lat) - N * (NUM_ONE - WGS84_FIRST_E2 * pow(sin(lat), NUM_TWO));

            //弧度转换为角度
            lon = lon * R2D;
            lat = lat * R2D;
            if (lon > LONGITUDE_UPPER_LIMIT)
            {
                lon = lon - LONGITUDE_DOUBLE_UPPER_LIMIT;
            }
            return RETURN_SUCCESS;
        }

        INT32 CGNSSCoordinate::XYZ2ENU(const DOUBLE curX,
                                       const DOUBLE curY,
                                       const DOUBLE curZ,
                                       const DOUBLE refX,
                                       const DOUBLE refY,
                                       const DOUBLE refZ,
                                       DOUBLE& curEast,
                                       DOUBLE& curNorth,
                                       DOUBLE& curUp)
        {
            //首先把目标点的xyz转为blh
            DOUBLE refB = 0.0;
            DOUBLE refL = 0.0;
            DOUBLE refH = 0.0;
            XYZ2BLH(refX, refY, refZ, refB, refL, refH);
            //定义向量
            SXYZ tmpXYZ;
            tmpXYZ.m_x = curX - refX;
            tmpXYZ.m_y = curY - refY;
            tmpXYZ.m_z = curZ - refZ;

            DOUBLE lat = refB * D2R;
            DOUBLE lon = refL * D2R;

            curEast = -sin(lon) * tmpXYZ.m_x + cos(lon) * tmpXYZ.m_y;
            curNorth = -sin(lat) * cos(lon) * tmpXYZ.m_x - sin(lat) * sin(lon) * tmpXYZ.m_y + cos(lat) * tmpXYZ.m_z;
            curUp = cos(lat) * cos(lon) * tmpXYZ.m_x + cos(lat) * sin(lon) * tmpXYZ.m_y + sin(lat) * tmpXYZ.m_z;
            return RETURN_SUCCESS;
        }

        INT32 CGNSSCoordinate::ENU2XYZ(const DOUBLE curEast,
                                       const DOUBLE curNorth,
                                       const DOUBLE curUp,
                                       const DOUBLE refX,
                                       const DOUBLE refY,
                                       const DOUBLE refZ,
                                       DOUBLE& curX,
                                       DOUBLE& curY,
                                       DOUBLE& curZ)
        {
            DOUBLE refB = 0.0;
            DOUBLE refL = 0.0;
            DOUBLE refH = 0.0;
            XYZ2BLH(refX, refY, refZ, refB, refL, refH);
            DOUBLE lat = refB * D2R;
            DOUBLE lon = refL * D2R;

            DOUBLE sinLat = sin(lat);
            DOUBLE cosLat = cos(lat);
            DOUBLE sinLon = sin(lon);
            DOUBLE cosLon = cos(lon);

            DOUBLE tempX1 = sinLat * cosLon * curNorth;
            DOUBLE tempX2 = sinLon * curEast;
            DOUBLE tempX3 = cosLat * cosLon * curUp;
            curX = refX - tempX1 - tempX2 + tempX3;

            tempX1 = sinLat * sinLon * curNorth;
            tempX2 = cosLon * curEast;
            tempX3 = cosLat * sinLon * curUp;
            curY = refY - tempX1 + tempX2 + tempX3;

            tempX1 = cosLat * curNorth;
            tempX2 = sinLat * curUp;
            curZ = refZ + tempX1 + tempX2;

            return RETURN_SUCCESS;
        }

        CGNSSCoordinate::~CGNSSCoordinate()
        {}
    } // namespace Math
} // namespace sixents
