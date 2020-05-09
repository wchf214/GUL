/** @file          CGNSSCoord
 *  @brief         坐标类
 *  @details       所有坐标相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef GNSS_COORDINATE_H
#define GNSS_COORDINATE_H

#include <map>
#include "../DllMain/GNSSCommonDef.h"
#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace Math
    {
        /**
         *  @class       CGNSSCoordinate
         *  @brief       坐标类
         *  @author      pengshupan@sixents.com
         *  @note        坐标转换算法
         */
        class CGNSSCoordinate
        {
        public:
            /**
             * @brief       坐标转换类构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        坐标系类型为1代表地理坐标，坐标系类型为2代表空间直角坐标
             */
            CGNSSCoordinate();

            /**
             * @brief       坐标转换类构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   x                   输入数据x
             * @param[in]   y                   输入数据y
             * @param[in]   z                   输入数据z
             * @param[in]   coordinateType      坐标系类型
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        坐标系类型为1代表地理坐标，坐标系类型为2代表空间直角坐标
             */
            CGNSSCoordinate(const DOUBLE x, const DOUBLE y, const DOUBLE z, const COORDINATE_TYPE coordinateType);

            /**
             * @brief       析构函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            virtual ~CGNSSCoordinate();

            /**
             * @brief       设置空间直角坐标x，y，z
             * @author      pengshupan@sixents.com
             * @param[in]   coordinate      空间直角坐标数据
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetXYZ(const SXYZ& coordinate);

            /**
             * @brief       获取空间直角坐标x，y，z
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      空间直角坐标数据
             * @retval      N/A
             * @note        N/A
             */
            SXYZ GetXYZ() const;

            /**
             * @brief       设置大地坐标B,L,H
             * @author      pengshupan@sixents.com
             * @param[in]   coordinate 大地坐标数据
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetBLH(const SBLH& coordinate);

            /**
             * @brief       获取大地坐标B,L.H
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      大地坐标数据
             * @retval      N/A
             * @note        N/A
             */
            SBLH GetBLH() const;

            /**
             * @brief       大地坐标转空间直角坐标
             * @author      pengshupan@sixents.com
             * @param[in]   lat         大地坐标纬度
             * @param[in]   lon         大地坐标经度
             * @param[in]   height      大地坐标高程
             * @param[out]  x           空间直角坐标x
             * @param[out]  z           空间直角坐标y
             * @param[out]  y           空间直角坐标z
             * @exception   N/A
             * @return      函数的执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32
            BLH2XYZ(const DOUBLE lat,
                    const DOUBLE lon,
                    const DOUBLE height,
                    DOUBLE& x,
                    DOUBLE& y,
                    DOUBLE& z);

            /**
             * @brief       空间直角坐标转大地坐标
             * @author      pengshupan@sixents.com
             * @param[in]   x           空间之角坐标x
             * @param[in]   y           空间之角坐标y
             * @param[in]   z           空间之角坐标z
             * @param[out]  lat         大地坐标纬度
             * @param[out]  lon         大地坐标经度
             * @param[out]  height      大地坐标高程
             * @exception   N/A
             * @return      函数的执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32
            XYZ2BLH(const DOUBLE x,
                    const DOUBLE y,
                    const DOUBLE z,
                    DOUBLE& lat,
                    DOUBLE& lon,
                    DOUBLE& height);

            /**
             * @brief       空间直角坐标转站心坐标
             * @author      pengshupan@sixents.com
             * @param[in]   curX            目标点空间之角坐标x
             * @param[in]   curY            目标点空间之角坐标y
             * @param[in]   curZ            目标点空间之角坐标z
             * @param[in]   refX            参考点空间之角坐标x
             * @param[in]   refY            参考点空间之角坐标y
             * @param[in]   refZ            参考点空间之角坐标z
             * @param[out]  curEast         目标点站心坐标east
             * @param[out]  curNorth        目标点站心坐标north
             * @param[out]  curUp           目标点站心坐标up
             * @exception   N/A
             * @return      函数的执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 XYZ2ENU(const DOUBLE curX,
                          const DOUBLE curY,
                          const DOUBLE curZ,
                          const DOUBLE refX,
                          const DOUBLE refY,
                          const DOUBLE refZ,
                          DOUBLE& curEast,
                          DOUBLE& curNorth,
                          DOUBLE& curUp);

            /**
             * @brief       站心坐标转空间直角坐标
             * @author      pengshupan@sixents.com
             * @param[in]   curEast         目标点站心坐标east
             * @param[in]   curNorth        目标点站心坐标north
             * @param[in]   curUp           目标点站心坐标up
             * @param[in]   refX            参考点空间之角坐标x
             * @param[in]   refY            参考点空间之角坐标y
             * @param[in]   refZ            参考点空间之角坐标在、
             * @param[out]  curX            目标点空间之角坐标x
             * @param[out]  curY            目标点空间之角坐标y
             * @param[out]  curZ            目标点空间之角坐标z
             * @exception   N/A
             * @return      函数的执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 ENU2XYZ(const DOUBLE curEast,
                          const DOUBLE curNorth,
                          const DOUBLE curUp,
                          const DOUBLE refX,
                          const DOUBLE refY,
                          const DOUBLE refZ,
                          DOUBLE& curX,
                          DOUBLE& curY,
                          DOUBLE& curZ);

        private:
            /**
             * @brief       设置不同坐标的参数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void InitCoordinateData();

            /**
             * @brief       利用迭代方法计算大地坐标的纬度
             * @author      pengshupan@sixents.com
             * @param[in]   x                       空间之角坐标x
             * @param[in]   y                       空间之角坐标y
             * @param[in]   z                       空间之角坐标z
             * @param[in]   coordinateFrame         坐标系类型
             * @param[out]  N/A
             * @exception   N/A
             * @return      大地坐标的纬度
             * @retval      N/A
             * @note        N/A
             */
            INT32 CalcLat(DOUBLE x, DOUBLE y, DOUBLE z, DOUBLE& lat) const;

        private:
            SXYZ m_spaceCoordinate;
            SBLH m_geoCoordinate;
            SENU m_stationCoordinate;
            std::map<COORDINATE_SYS_TYPE, SCoordData> m_CoordinateData;
        };
    } // end namespace Math
} // end namespace sixents
#endif
