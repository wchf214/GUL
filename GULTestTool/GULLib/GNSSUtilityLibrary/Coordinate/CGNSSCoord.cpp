#include "CGNSSCoord.h"
#include "../Angle/CGNSSAngle.h"
#include "../DllMain/GNSSCommonDef.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {

        CGNSSCoord::CGNSSCoord(const DOUBLE x, const DOUBLE y, const DOUBLE z, const INT32 coordType)
        {
            m_geoCoord.m_lon=x;
            m_geoCoord.m_lat=y;
            m_geoCoord.m_height=z;
        }

        void CGNSSCoord::SetCoordData()
        {
            SCoordData wgs84;
            wgs84.a = 6378137.0;
            wgs84.f = (1.0 / 298.257223563);

            SCoordData pz90;
            pz90.a = 6378136.0;
            pz90.f = (1.0 / 298.257839303);

            SCoordData itrf96;
            itrf96.a = 6378137.0;
            itrf96.f = (1.0 / 298.257223563);

            SCoordData cgcs2000;
            cgcs2000.a = 6378137.0;
            cgcs2000.f = (1.0 / 298.257222101);

            m_CoordData.insert(std::make_pair(1, wgs84));
            m_CoordData.insert(std::make_pair(2, pz90));
            m_CoordData.insert(std::make_pair(3, itrf96));
            m_CoordData.insert(std::make_pair(4, cgcs2000));
        }


        DOUBLE CGNSSCoord::CalcB(DOUBLE X, DOUBLE Y, DOUBLE Z)
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
            return 1;
        }

        int CGNSSCoord::XYZ2BLH(const DOUBLE x, const DOUBLE y, const DOUBLE z,
            DOUBLE& lat, DOUBLE& lon, DOUBLE& height, INT32 i)
        {
            do
            {
                DOUBLE N = 0;
                lon = atan(y / x);
                lat = CalcB(x, y, z);
                N = 6378137 / sqrt(1 - E2 * sin(lat) * sin(lat));
                height = sqrt(x * x + y * y) / cos(lat) - N;
                //弧度转换为角度
                lon = lon * 180 / PI;
                lat = lat * 180 / PI;
                if (lat < 0)
                    lat += 180;
            }while(false);
            return 1;
        }

        // transform between XYZ and ENU
        INT32 CGNSSCoord::XYZ2ENU(const DOUBLE ref_X,
                                  const DOUBLE ref_Y,
                                  const DOUBLE ref_Z,
                                  const DOUBLE Cur_X,
                                  const DOUBLE Cur_Y,
                                  const DOUBLE Cur_Z,
                                  DOUBLE& Cur_East,
                                  DOUBLE& Cur_North,
                                  DOUBLE& Cur_Up)
        {
            do
            {
                //首先把目标点的xyz转为blh
                DOUBLE Cur_B = 0;
                DOUBLE Cur_L = 0;
                DOUBLE Cur_H = 0;
                XYZ2BLH(Cur_X, Cur_Y, Cur_Z, Cur_B, Cur_L, Cur_H, 1);

                //定义向量
                SXYZ tmpXYZ;
                tmpXYZ.m_x = ref_X - Cur_X;
                tmpXYZ.m_y = ref_Y - Cur_Y;
                tmpXYZ.m_z = ref_Z - Cur_Z;

                //度转弧度
                DOUBLE degtoRad = PI / 180;
                Cur_East = -sin(Cur_L * degtoRad) * tmpXYZ.m_x + cos(Cur_L * degtoRad) * tmpXYZ.m_y;
                Cur_North = -sin(Cur_B * degtoRad) * cos(Cur_L * degtoRad) * tmpXYZ.m_x
                               - sin(Cur_B * degtoRad) * sin(Cur_L * degtoRad) * tmpXYZ.m_y + cos(Cur_B * degtoRad) * tmpXYZ.m_z;
                Cur_Up = cos(Cur_B * degtoRad) * cos(Cur_L * degtoRad) * tmpXYZ.m_x
                            + cos(Cur_B * degtoRad) * sin(Cur_L * degtoRad) * tmpXYZ.m_y + sin(Cur_B * degtoRad) * tmpXYZ.m_z;
            } while (false);
            return 1;
        }

        INT32 CGNSSCoord::ENU2XYZ( const DOUBLE Cur_East,
                                   const DOUBLE Cur_North,
                                   const DOUBLE Cur_Up,
                                   const DOUBLE ref_X,
                                   const DOUBLE ref_Y,
                                   const DOUBLE ref_Z,
                                   DOUBLE& Cur_X,
                                   DOUBLE& Cur_Y,
                                   DOUBLE& Cur_Z)
        {
            do
            {
                DOUBLE ref_B = 0;
                DOUBLE ref_L = 0;
                DOUBLE ref_H = 0;
                XYZ2BLH(ref_X, ref_X, ref_X, ref_B, ref_L, ref_H, 1);
                DOUBLE a = 6378137;      // a为椭球的长半轴:a=6378.137km
                DOUBLE b = 6356752.3141; // b为椭球的短半轴:a=6356.7523141km
                DOUBLE H0 = ref_H;
                DOUBLE e = sqrt(1 - pow(b, 2) / pow(a, 2)); // e为椭球的第一偏心率
                // DOUBLE e=sqrt(0.006693421622966); //克拉索夫斯基椭球
                // DOUBLE e=sqrt(0.006694384999588); //1975年国际椭球
                // DOUBLE e=sqrt(0.0066943799013); //WGS-84椭球
                DOUBLE m = 3.1415926 / 180; //经度维度需要转换成弧度.
                DOUBLE B0 = ref_B * m;
                DOUBLE L0 = ref_L * m;
                DOUBLE W = sqrt(1 - pow(e, 2) * pow(sin(B0), 2));
                DOUBLE N0 = a / W; // N为椭球的卯酉圈曲率半径
                Cur_X = (N0 + H0) * cos(B0) * cos(L0) - sin(B0) * cos(L0) * Cur_East - sin(L0) * Cur_North
                        + cos(B0) * cos(L0) * Cur_Up;
                Cur_Y = (N0 + H0) * cos(B0) * sin(L0) - sin(B0) * sin(L0) * Cur_East + cos(L0) * Cur_North
                        + cos(B0) * sin(L0) * Cur_Up;
                Cur_Z = (N0 * (1 - pow(e, 2)) + H0) * sin(B0) + cos(B0) * Cur_East + sin(B0) * Cur_Up;
            } while (false);
            return 1;
        }

        CGNSSCoord::~CGNSSCoord()
        {}
    } // namespace GNSSUtilityLib
} // namespace sixents
