#include "CGNSSCoord.h"
#include "../Angle/CGNSSAngle.h"
#include "../DllMain/GNSSCommonDef.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        CGNSSCoord::CGNSSCoord(const DOUBLE x, const DOUBLE y, const DOUBLE z, const INT32 coordType)
        {
            UNREFERENCED_PARAMETER(coordType);
            m_geoCoord.m_lon = x;
            m_geoCoord.m_lat = y;
            m_geoCoord.m_height = z;
        }

        void CGNSSCoord::SetCoordData()
        {
            m_CoordData.insert(std::make_pair(WGS84, WGS84_DATA));
            m_CoordData.insert(std::make_pair(PZ90, PZ90_DATA));
            m_CoordData.insert(std::make_pair(ITRF96, ITRF96_DATA));
            m_CoordData.insert(std::make_pair(CGCS2000, CGCS2000_DATA));
        }

        void CGNSSCoord::SetXYZ(const SXYZ& coord)
        {
            m_spaceCoord.m_x = coord.m_x;
            m_spaceCoord.m_y = coord.m_y;
            m_spaceCoord.m_z = coord.m_z;
        }

        SXYZ CGNSSCoord::GetXYZ()
        {
            return m_spaceCoord;
        }

        void CGNSSCoord::SetBLH(const SBLH& coord)
        {
            m_geoCoord.m_lat = coord.m_lat;
            m_geoCoord.m_lon = coord.m_lon;
            m_geoCoord.m_height = coord.m_height;
        }

        SBLH CGNSSCoord::GetBLH()
        {
            return m_geoCoord;
        }

        void CGNSSCoord::SetENU(const SENU& coord)
        {
            m_stationCoord.m_east = coord.m_east;
            m_stationCoord.m_north = coord.m_north;
            m_stationCoord.m_up = coord.m_up;
        }

        SENU CGNSSCoord::GetENU()
        {
            return m_stationCoord;
        }

        DOUBLE CGNSSCoord::CalcLat(DOUBLE X, DOUBLE Y, DOUBLE Z)
        {
            DOUBLE b1, b2, N;
            b2 = atan(Z / sqrt(X * X + Y * Y));
            while (1)
            {
                b1 = b2;
                N = EARTH_LONG_RADIUS / sqrt(1 - E2 * sin(b1) * sin(b1));
                b2 = atan((Z + N * E2 * sin(b1)) / sqrt(X * X + Y * Y));
                if (fabs(b2 - b1) < LAT_ACCURACY)
                    break;
            }
            return b2;
        }

        INT32 CGNSSCoord::BLH2XYZ(
            const DOUBLE lat, const DOUBLE lon, const DOUBLE height, DOUBLE& x, DOUBLE& y, DOUBLE& z, INT32 i)
        {
            DOUBLE RE_WGS84 = 6378137.0;             /* earth semimajor axis (WGS84) (m) */
            DOUBLE FE_WGS84 = (1.0 / 298.257223563); /* earth flattening (WGS84) */
            CGNSSAngle c(0, true);
            DOUBLE latrad = 0;
            c.DegToRad(lat, latrad);
            DOUBLE lonrad = 0;
            c.DegToRad(lon, lonrad);
            do
            {
                DOUBLE sinLat = sin(latrad);
                DOUBLE cosLat = cos(latrad);
                DOUBLE sinLon = sin(lonrad);
                DOUBLE cosLon = cos(lonrad);
                DOUBLE e2 = FE_WGS84 * (2.0 - FE_WGS84);
                DOUBLE N = RE_WGS84 / sqrt(1.0 - e2 * sinLat * sinLat);
                x = (N + height) * cosLat * cosLon;
                y = (N + height) * cosLat * sinLon;
                z = (N * (1.0 - e2) + height) * sinLat;
            } while (false);
            return RETURN_SUCCESS;
        }

        INT32 CGNSSCoord::XYZ2BLH(
            const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lat, DOUBLE& lon, DOUBLE& height, INT32 i)
        {
            UNREFERENCED_PARAMETER(i);
            do
            {
                DOUBLE N = 0;
                lon = atan(y / x);
                lat = CalcLat(x, y, z);
                N = 6378137 / sqrt(1 - E2 * sin(lat) * sin(lat));
                height = sqrt(x * x + y * y) / cos(lat) - N;
                //弧度转换为角度
                lon = lon * D2R;
                lat = lat * D2R;
                if (lat < 0)
                    lat += 180;
            } while (false);
            return 1;
        }

        INT32 CGNSSCoord::XYZ2ENU(const DOUBLE refX,
                                  const DOUBLE refY,
                                  const DOUBLE refZ,
                                  const DOUBLE curX,
                                  const DOUBLE curY,
                                  const DOUBLE curZ,
                                  DOUBLE& curEast,
                                  DOUBLE& curNorth,
                                  DOUBLE& curUp)
        {
            do
            {
                //首先把目标点的xyz转为blh
                DOUBLE curB = 0;
                DOUBLE curL = 0;
                DOUBLE curH = 0;
                XYZ2BLH(curX, curY, curZ, curB, curL, curH, 1);

                //定义向量
                SXYZ tmpXYZ;
                tmpXYZ.m_x = refX - curX;
                tmpXYZ.m_y = refY - curY;
                tmpXYZ.m_z = refZ - curZ;

                //度转弧度
                DOUBLE degtoRad = PI / 180;
                curEast = -sin(curL * degtoRad) * tmpXYZ.m_x + cos(curL * degtoRad) * tmpXYZ.m_y;
                curNorth = -sin(curB * degtoRad) * cos(curL * degtoRad) * tmpXYZ.m_x
                           - sin(curB * degtoRad) * sin(curL * degtoRad) * tmpXYZ.m_y
                           + cos(curB * degtoRad) * tmpXYZ.m_z;
                curUp = cos(curB * degtoRad) * cos(curL * degtoRad) * tmpXYZ.m_x
                        + cos(curB * degtoRad) * sin(curL * degtoRad) * tmpXYZ.m_y + sin(curB * degtoRad) * tmpXYZ.m_z;
            } while (false);
            return 1;
        }

        INT32 CGNSSCoord::ENU2XYZ(const DOUBLE curEast,
                                  const DOUBLE curNorth,
                                  const DOUBLE curUp,
                                  const DOUBLE refX,
                                  const DOUBLE refY,
                                  const DOUBLE refZ,
                                  DOUBLE& curX,
                                  DOUBLE& curY,
                                  DOUBLE& curZ)
        {
            do
            {
                DOUBLE refB = 0;
                DOUBLE refL = 0;
                DOUBLE refH = 0;
                XYZ2BLH(refX, refY, refZ, refB, refL, refH, 1);
                DOUBLE a = 6378137;      // a为椭球的长半轴:a=6378.137km
                DOUBLE b = 6356752.3141; // b为椭球的短半轴:a=6356.7523141km
                DOUBLE H0 = refH;
                DOUBLE e = sqrt(1 - pow(b, 2) / pow(a, 2)); // e为椭球的第一偏心率
                // DOUBLE e=sqrt(0.006693421622966); //克拉索夫斯基椭球
                // DOUBLE e=sqrt(0.006694384999588); //1975年国际椭球
                // DOUBLE e=sqrt(0.0066943799013); //WGS-84椭球
                DOUBLE m = 3.1415926 / 180; //经度维度需要转换成弧度.
                DOUBLE B0 = refB * m;
                DOUBLE L0 = refL * m;
                DOUBLE W = sqrt(1 - pow(e, 2) * pow(sin(B0), 2));
                DOUBLE N0 = a / W; // N为椭球的卯酉圈曲率半径
                curX = (N0 + H0) * cos(B0) * cos(L0) - sin(B0) * cos(L0) * curEast - sin(L0) * curNorth
                       + cos(B0) * cos(L0) * curUp;
                curY = (N0 + H0) * cos(B0) * sin(L0) - sin(B0) * sin(L0) * curEast + cos(L0) * curNorth
                       + cos(B0) * sin(L0) * curUp;
                curZ = (N0 * (1 - pow(e, 2)) + H0) * sin(B0) + cos(B0) * curEast + sin(B0) * curUp;
            } while (false);
            return 1;
        }

        CGNSSCoord::~CGNSSCoord()
        {}
    } // namespace GNSSUtilityLib
} // namespace sixents