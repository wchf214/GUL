#include "CGNSSCoord.h"
#include "../Angle/CGNSSAngle.h"
#include "../DllMain/GNSSCommonDef.h"

namespace sixents
{
    namespace Math
    {
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
                        m_spaceCoordinate.m_z,
                        WGS84);
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
                        m_geoCoordinate.m_height,
                        WGS84);
            }
            else
            {
                m_geoCoordinate.m_lat = 0;
                m_geoCoordinate.m_lon = 0;
                m_geoCoordinate.m_height = 0;
                m_spaceCoordinate.m_x = 0;
                m_spaceCoordinate.m_y = 0;
                m_spaceCoordinate.m_z = 0;
            }
            m_stationCoordinate.m_east = 0;
            m_stationCoordinate.m_north = 0;
            m_stationCoordinate.m_up = 0;
            InitCoordinateData();
        }

        void CGNSSCoordinate::InitCoordinateData()
        {
            m_CoordinateData.clear();
            m_CoordinateData.insert(std::make_pair(WGS84, WGS84_DATA));
            m_CoordinateData.insert(std::make_pair(PZ90, PZ90_DATA));
            m_CoordinateData.insert(std::make_pair(ITRF96, ITRF96_DATA));
            m_CoordinateData.insert(std::make_pair(CGCS2000, CGCS2000_DATA));
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
                    m_geoCoordinate.m_height,
                    WGS84);
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
                    m_spaceCoordinate.m_z,
                    WGS84);
        }

        SBLH CGNSSCoordinate::GetBLH() const
        {
            return m_geoCoordinate;
        }

        //形参
        DOUBLE CGNSSCoordinate::CalcLat(DOUBLE x, DOUBLE y, DOUBLE z, const COORDINATE_SYS_TYPE coordinateFrame) const
        {
            //利用迭代法计算纬度
            DOUBLE tempLat1 = 0;
            DOUBLE tempLat2 = 0;

            //计算第一偏心率e2，公式 2 * f - f * f
            DOUBLE e2 = m_CoordinateData.at(coordinateFrame).m_f * (NUM_TWO - m_CoordinateData.at(coordinateFrame).m_f);

            //卯酉圈曲率半径N
            DOUBLE N = 0;

            tempLat2 = atan(z / sqrt(x * x + y * y));
            //不断的迭代，直到计算出的纬度的精度达到要求退出循环
            while (true)
            {
                tempLat1 = tempLat2;
                //计算代表卯酉圈曲率半径N，公式 a / Sqrt(1 - e2 * sinB * sinB)
                // m_a代表不同坐标框架下的长半轴a
                N = m_CoordinateData.at(coordinateFrame).m_a / sqrt(NUM_ONE - e2 * sin(tempLat1) * sin(tempLat1));
                tempLat2 = atan((z + N * e2 * sin(tempLat1)) / sqrt(x * x + y * y));
                if (fabs(tempLat2 - tempLat1) < LAT_ACCURACY)
                {
                    break;
                }
            }
            return tempLat2;
        }

        INT32 CGNSSCoordinate::BLH2XYZ(const DOUBLE lat,
                                       const DOUBLE lon,
                                       const DOUBLE height,
                                       DOUBLE& x,
                                       DOUBLE& y,
                                       DOUBLE& z,
                                       const COORDINATE_SYS_TYPE coordinateFrame)
        {
            //数据转换
            const DOUBLE sinLat = sin(lat * D2R);
            const DOUBLE cosLat = cos(lat * D2R);
            const DOUBLE sinLon = sin(lon * D2R);
            const DOUBLE cosLon = cos(lon * D2R);

            //计算第一偏心率e2，公式 2 * f - f * f
            DOUBLE e2 = m_CoordinateData.at(coordinateFrame).m_f * (NUM_TWO - m_CoordinateData.at(coordinateFrame).m_f);

            //计算代表卯酉圈曲率半径N，公式 a / Sqrt(1 - e2 * sinB * sinB)
            DOUBLE N = m_CoordinateData.at(coordinateFrame).m_a / sqrt(NUM_ONE - e2 * sinLat * sinLat);

            x = (N + height) * cosLat * cosLon;
            y = (N + height) * cosLat * sinLon;
            z = (N * (NUM_ONE - e2) + height) * sinLat;
            return RETURN_SUCCESS;
        }

        INT32 CGNSSCoordinate::XYZ2BLH(const DOUBLE x,
                                       const DOUBLE y,
                                       const DOUBLE z,
                                       DOUBLE& lat,
                                       DOUBLE& lon,
                                       DOUBLE& height,
                                       const COORDINATE_SYS_TYPE coordinateFrame)
        {
            //计算第一偏心率e2，公式 2 * f - f * f
            DOUBLE e2 = m_CoordinateData.at(coordinateFrame).m_f * (NUM_TWO - m_CoordinateData.at(coordinateFrame).m_f);

            //计算经度，单位弧度
            lon = atan(y / x);
            //计算纬度，单位弧度
            lat = CalcLat(x, y, z, coordinateFrame);
            //计算代表卯酉圈曲率半径N，公式 a / Sqrt(1 - e2 * sinB * sinB)
            DOUBLE N = m_CoordinateData.at(coordinateFrame).m_a / sqrt(NUM_ONE - e2 * sin(lat) * sin(lat));
            //计算高程
            height = sqrt(x * x + y * y) / cos(lat) - N;
            //弧度转换为角度
            lon = lon * R2D;
            lat = lat * R2D;
            if (lat < 0)
            {
                lat += LONGITUDE_UPPER_LIMIT;
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
                                       DOUBLE& curUp,
                                       const COORDINATE_SYS_TYPE coordinateFrame)
        {
            //首先把目标点的xyz转为blh
            DOUBLE curB = 0;
            DOUBLE curL = 0;
            DOUBLE curH = 0;
            XYZ2BLH(curX, curY, curZ, curB, curL, curH, coordinateFrame);
            //定义向量
            SXYZ tmpXYZ;
            tmpXYZ.m_x = refX - curX;
            tmpXYZ.m_y = refY - curY;
            tmpXYZ.m_z = refZ - curZ;

            DOUBLE lon = curL * D2R;
            DOUBLE lat = curB * D2R;

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
                                       DOUBLE& curZ,
                                       const COORDINATE_SYS_TYPE coordinateFrame)
        {
            //参数判断
            //数据转换
            //把空间直角坐标转换角度
            DOUBLE refB = 0;
            DOUBLE refL = 0;
            DOUBLE refH = 0;
            XYZ2BLH(refX, refY, refZ, refB, refL, refH, coordinateFrame);

            DOUBLE lat = refB * D2R;
            DOUBLE lon = refL * D2R;
            DOUBLE height = refH;

            DOUBLE e2 = m_CoordinateData.at(coordinateFrame).m_f * (NUM_TWO - m_CoordinateData.at(coordinateFrame).m_f);
            //计算代表卯酉圈曲率半径N，公式 a / Sqrt(1 - e2 * sinB * sinB)
            DOUBLE N0 = m_CoordinateData.at(coordinateFrame).m_a / sqrt(NUM_ONE - e2 * sin(lat) * sin(lat));

            curX = (N0 + height) * cos(lat) * cos(lon) - sin(lat) * cos(lon) * curEast - sin(lon) * curNorth
                   + cos(lat) * cos(lon) * curUp;
            curY = (N0 + height) * cos(lat) * sin(lon) - sin(lat) * sin(lon) * curEast + cos(lon) * curNorth
                   + cos(lat) * sin(lon) * curUp;
            curZ = (N0 * (NUM_ONE - e2) + height) * sin(lat) + cos(lat) * curEast + sin(lat) * curUp;
            return RETURN_SUCCESS;
        }

        CGNSSCoordinate::~CGNSSCoordinate()
        {}
    } // namespace Math
} // namespace sixents