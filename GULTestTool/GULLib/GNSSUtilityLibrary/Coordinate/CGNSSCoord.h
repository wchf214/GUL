/**@file           CGNSSCoord
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
    namespace GNSSUtilityLib
    {
        class CGNSSCoord
        {
        public:
            /**
             * @brief       坐标转换类构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   x 空间直角坐标x
             * @param[in]   y 空间直角坐标y
             * @param[in]   z 空间直角坐标z
             * @param[in]   coordType 坐标类型
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        坐标系类型为1代表空间直角坐标，坐标系类型为1代表空间直角坐标，坐标系类型为3代表站心坐标，
             */

            CGNSSCoord(const DOUBLE x, const DOUBLE y, const DOUBLE z, const INT32 coordType);

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
            virtual ~CGNSSCoord();

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
            void SetCoordData();

            /**
             * @brief       设置空间直角坐标x，y，z
             * @author      pengshupan@sixents.com
             * @param[in]   coord 空间直角坐标系结构体
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetXYZ(const SXYZ& coord);
            /**
             * @brief       获取空间直角坐标x，y，z
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            SXYZ GetXYZ();

            /**
             * @brief       设置大地坐标B,L,H
             * @author      pengshupan@sixents.com
             * @param[in]   coord 大地坐标系结构体
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetBLH(const SBLH& coord);

            /**
             * @brief       获取大地坐标B,L.H
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            SBLH GetBLH();

            /**
             * @brief       设置站心坐标east，north，up
             * @author      pengshupan@sixents.com
             * @param[in]   coord 站心坐标系结构体
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetENU(const SENU& coord);

            /**
             * @brief       获取站心坐标east，north，up
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            SENU GetENU();

            /**
             * @brief       大地坐标转空间直角坐标
             * @author      pengshupan@sixents.com
             * @param[in]   lon 大地坐标经度
             * @param[in]   lat 大地坐标纬度
             * @param[in]   height 大地坐标高程
             * @param[out]  x 空间直角坐标
             * @param[out]  z 空间直角坐标
             * @param[out]  y 空间直角坐标
             * @exception   N/A
             * @return      函数的执行情况
             * @retval      N/A
             * @note        N/A
             */

            INT32
            BLH2XYZ(const DOUBLE lon, const DOUBLE lat, const DOUBLE height, DOUBLE& x, DOUBLE& y, DOUBLE& z, INT32 i);

            /**
             * @brief       空间直角坐标转大地坐标
             * @author      pengshupan@sixents.com
             * @param[in]   x 空间之角坐标x
             * @param[in]   y 空间之角坐标y
             * @param[in]   z 空间之角坐标z
             * @param[out]  lon 大地坐标经度
             * @param[out]  lat 大地坐标纬度
             * @param[out]  height 大地坐标高程
             * @exception   N/A
             * @return      函数的执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32
            XYZ2BLH(const DOUBLE x, const DOUBLE y, const DOUBLE z, DOUBLE& lon, DOUBLE& lat, DOUBLE& height, INT32 i);

            /**
             * @brief       空间直角坐标转站心坐标
             * @author      pengshupan@sixents.com
             * @param[in]   refX     参考点空间之角坐标x
             * @param[in]   refY     参考点空间之角坐标y
             * @param[in]   refZ     参考点空间之角坐标z
             * @param[in]   curX     目标点空间之角坐标x
             * @param[in]   curY     目标点空间之角坐标y
             * @param[in]   curZ     目标点空间之角坐标z
             * @param[out]  curEast  目标点站心坐标east
             * @param[out]  curNorth 目标点站心坐标north
             * @param[out]  curUp    目标点站心坐标up
             * @exception   N/A
             * @return      函数的执行情况
             * @retval      N/A
             * @note        N/A
             */
            INT32 XYZ2ENU(const DOUBLE refX,
                          const DOUBLE refY,
                          const DOUBLE refZ,
                          const DOUBLE curX,
                          const DOUBLE curY,
                          const DOUBLE curZ,
                          DOUBLE& curEast,
                          DOUBLE& curNorth,
                          DOUBLE& curUp);

            /**
             * @brief       站心坐标转空间直角坐标
             * @author      pengshupan@sixents.com
             * @param[in]   curEast  目标点站心坐标east
             * @param[in]   curNorth 目标点站心坐标north
             * @param[in]   curUp    目标点站心坐标up
             * @param[in]   refX     参考点空间之角坐标x
             * @param[in]   refY     参考点空间之角坐标y
             * @param[in]   refZ     参考点空间之角坐标在、
             * @param[out]  curX     目标点空间之角坐标x
             * @param[out]  curY     目标点空间之角坐标y
             * @param[out]  curZ     目标点空间之角坐标z
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
             * @brief       利用迭代方法计算大地坐标的纬度
             * @author      pengshupan@sixents.com
             * @param[in]   x 空间之角坐标x
             * @param[in]   y 空间之角坐标y
             * @param[in]   z 空间之角坐标z
             * @param[out]  N/A
             * @exception   N/A
             * @return      大地坐标的纬度
             * @retval      N/A
             * @note        N/A
             */
            double CalcLat(DOUBLE X, DOUBLE Y, DOUBLE Z);

            SXYZ m_spaceCoord;
            SBLH m_geoCoord;
            SENU m_stationCoord;
            std::map<COORDINATE_SYS_TYPE, SCoordData> m_CoordData;
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents
#endif
