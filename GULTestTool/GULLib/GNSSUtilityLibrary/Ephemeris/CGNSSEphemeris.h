/**@file           CGNSSEphemeris
 *  @brief         星历类
 *  @details       所有星历相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _GNSS_EPHEMERIS_H
#define _GNSS_EPHEMERIS_H

#include "../DllMain/GNSSDataStruct.h"

namespace sixents
{
    namespace GNSSUtilityLib
    {
        class IGNSSEphemeris
        {
        public:
            CGNSSEphemeris();
            virtual ~CGNSSEphemeris();

            bool IsNull();
            // Calc Clock and Position
            virtual int CalcSatClock(const double& sec, double& clockVal) = 0;
            virtual int CalcSatPos(const double& sec, double& x, double& y, double& z) = 0;
        };

        class CGNSSEph : public IGNSSEphemeris
        {
        public:
            CGNSSEph(const SEphemeris& ephObj);
            virtual ~CGNSSEph();

            void SetEphObj(const SEphemeris& ephObj);
            SEphemeris GetEphObj();

            void SetSatSys(const int& satSys);
            int GetSatSys();
            bool IsNull();

        private:
            SEphemeris m_ephObj;
            int m_satSys;
        };

        class CGloEph : public IGNSSEphemeris
        {
        public:
            CGloEph(const SGlonassEphemeris& ephObj);
            virtual ~CGloEph();

            virtual int CalcSatClock(const double& sec, double& clockVal);
            virtual int CalcSatPos(const double& sec, double& x, double& y, double& z);

            bool IsNull();

            void SetEphObj(const SGlonassEphemeris& ephObj);
            SGlonassEphemeris GetEphObj();

        private:
            /**
             *  @brief           一个数的平方
             *  @author          wuchuanfei@sixents.com
             * @param[in]        x: 一个double型的数
             * @param[out]       N/A
             * @exception        N/A
             * @return           x的平方
             * @note             N/A
             */
            inline double SQR(const double x)
            {
                return x * x;
            }
            /**
             *  @brief           一个数的平方
             *  @author          wuchuanfei@sixents.com
             * @param[in]        x: 一个double型的数
             * @param[out]       N/A
             * @exception        N/A
             * @return           x的平方
             * @note             N/A
             */
            double Dot(const double* a, const double* b, int n);
            /**
             *  @brief           一个数的平方
             *  @author          wuchuanfei@sixents.com
             * @param[in]        x: 一个double型的数
             * @param[out]       N/A
             * @exception        N/A
             * @return           x的平方
             * @note             N/A
             */
            void Deq(const double* x, double* xdot, const double* acc);
            /**
             *  @brief           一个数的平方
             *  @author          wuchuanfei@sixents.com
             * @param[in]        x: 一个double型的数
             * @param[out]       N/A
             * @exception        N/A
             * @return           x的平方
             * @note             N/A
             */
            void Glorbit(double t, double* x, const double* acc);

        private:
            SGlonassEphemeris m_gloEphObj;
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents
#endif