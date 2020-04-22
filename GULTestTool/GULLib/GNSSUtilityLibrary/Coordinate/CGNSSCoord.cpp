#include "CGNSSCoord.h"

#include "../DllMain/GNSSCommonDef.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
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

        int CGNSSCoord::XYZ2BLH(const double x, const double y, const double z,
            double& lon, double& lat, double& height, int i)
        {
            /*      do
                  {
                      double e2 = m_CoordData[i].f * (2.0 - m_CoordData[i].f);
                      double r2 = dot(r, r, 2), z, zk, v = m_CoordData[i].a, sinp;
                      for (z = z, zk = 0.0; fabs(z - zk) >= 1E-4;)
                      {
                          zk = z;
                          sinp = z / sqrt(r2 + z * z);
                          v = m_CoordData[i].a / sqrt(1.0 - e2 * sinp*sinp);
                      }
                      lat = r2 > 1E-12 ? atan(z / sqrt(r2)) : (z > 0.0 ? PI / 2.0 : -PI / 2.0);
                      lon = r2 > 1E-12 ? atan2(y, x) : 0.0;
                      height = sqrt(r2 + z * z) - v;
                  } while (false);*/
            return 1;
        }
        int CGNSSCoord::BLH2XYZ(const double lon, const double lat, const double height,
            double& x, double& y, double& z, int i)
        {
            do
            {
                double sinp = sin(lat), cosp = cos(lat), sinl = sin(lon), cosl = cos(lon);
                double e2 = m_CoordData[i].f * (2.0 - m_CoordData[i].f);
                double N = m_CoordData[i].a / sqrt(1.0 - e2 * sinp*sinp);
                x = (N + height)*cosp*cosl;
                y = (N + height)*cosp*sinl;
                z = (N*(1.0 - e2) + height)*sinp;
            } while (false);
            return 1;
        }

        // transform between XYZ and ENU
        int CGNSSCoord::XYZ2ENU(const double origin_X, const double origin_Y, const double origin_Z,
            const double target_B, const double target_L, const double target_H,
            double& target_East, double& target_North, double& target_Up)
        {
            do
            {
                double target_X = 0;
                double target_Y = 0;
                double target_Z = 0;
                BLH2XYZ(target_B, target_L, target_H, target_X, target_Y, target_Z, 1);
                SXYZ tmpXYZ;
                tmpXYZ.m_x = target_X - origin_X;
                tmpXYZ.m_y = target_Y - origin_Y;
                tmpXYZ.m_z = target_Z - origin_Z;
                double m = PI / 180;
                target_East = -sin(target_L*m)*tmpXYZ.m_x + cos(target_L*m)*tmpXYZ.m_y;
                target_North = -sin(target_B*m)*cos(target_L*m)*tmpXYZ.m_x - sin(target_B*m)*sin(target_L*m)*tmpXYZ.m_y
                    + cos(target_B*m)*tmpXYZ.m_z;
                target_Up = cos(target_B*m)*cos(target_L*m)*tmpXYZ.m_x + cos(target_B*m)*sin(target_L*m)*tmpXYZ.m_y
                    + sin(target_B*m)*tmpXYZ.m_z;
            } while (false);
            return 1;
        }
        int CGNSSCoord::ENU2XYZ(const double origin_B, const double origin_L, const double origin_H,
            const double target_East, const double target_North, double target_Up,
            double& target_X, double& target_Y, double& target_Z)
        {
            do
            {
                double a = 6378137;//a为椭球的长半轴:a=6378.137km
                double b = 6356752.3141;//b为椭球的短半轴:a=6356.7523141km
                double H0 = origin_H + a;
                double e = sqrt(1 - pow(b, 2) / pow(a, 2)); //e为椭球的第一偏心率
                // double e=sqrt(0.006693421622966); //克拉索夫斯基椭球
                // double e=sqrt(0.006694384999588); //1975年国际椭球
                // double e=sqrt(0.0066943799013); //WGS-84椭球
                double m = 3.1415926 / 180;//经度维度需要转换成弧度.
                double B0 = origin_B * m;
                double L0 = origin_L * m;
                double W = sqrt(1 - pow(e, 2)*pow(sin(B0), 2));
                double N0 = a / W; //N为椭球的卯酉圈曲率半径
                target_X = (N0 + H0)*cos(B0)*cos(L0)
                    - sin(B0)*cos(L0)*target_East - sin(L0)*target_North + cos(B0)*cos(L0)*target_Z;
                target_Y = (N0 + H0)*cos(B0)*sin(L0)
                    - sin(B0)*sin(L0)*target_East - cos(L0)*target_North + cos(B0)*sin(L0)*target_Z;
                target_Z = (N0*(1 - pow(e, 2)) + H0)*sin(B0)
                    - cos(B0)*target_East + sin(B0)*target_Z;
            } while (false);

            return 1;
        }

        void CGNSSCoord::xyz2enu(const double *pos, double *E)
        {
            double sinp = sin(pos[0]), cosp = cos(pos[0]), sinl = sin(pos[1]), cosl = cos(pos[1]);
            E[0] = -sinl;      E[3] = cosl;       E[6] = 0.0;
            E[1] = -sinp * cosl; E[4] = -sinp * sinl; E[7] = cosp;
            E[2] = cosp * cosl;  E[5] = cosp * sinl;  E[8] = sinp;
        }
    }
}