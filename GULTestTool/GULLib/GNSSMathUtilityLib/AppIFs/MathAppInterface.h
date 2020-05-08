/** @file          CMathAppInterface.h
 *  @brief         矩阵运算接口类
 *  @details       N/A
 *  @author        pengshupan@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef MATH_APP_INTERFACE_H_
#define MATH_APP_INTERFACE_H_

#include "../DllMain/GNSSCommonStruct.h"

namespace sixents
{
    namespace Math
    {
        /**
         *  @class       CMathAppInterface
         *  @brief       CMathAppInterface接口实现类
         *  @author      pengshupan@sixents.com
         *  @note        用于接口算法实现
         */
        class CMathAppInterface
        {
        public:
            /**
             * @brief           矩阵加法
             * @author          pengshupan@sixents.com
             * @param[in]       leftMatrixData      运算符左边的矩阵数据
             * @param[in]       leftRow             运算符左边的矩阵行
             * @param[in]       leftCol             运算符左边的矩阵列
             * @param[in]       rightMatrixData     运算符右边的矩阵数据
             * @param[in]       rightRow            运算符右边的矩阵行
             * @param[in]       rightCol            运算符右边的矩阵列
             * @param[in]       outRow              输出矩阵行
             * @param[in]       outCol              输出矩阵列
             * @param[out]      outMatrixData       输出矩阵数据
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 MatrixAdd(const DOUBLE* leftMatrixData,
                                   const UINT32 leftRow,
                                   const UINT32 leftCol,
                                   const DOUBLE* rightMatrixData,
                                   const UINT32 rightRow,
                                   const UINT32 rightCol,
                                   const UINT32 outRow,
                                   const UINT32 outCol,
                                   DOUBLE* outMatrixData);

            /**
             * @brief           矩阵减法
             * @author          pengshupan@sixents.com
             * @param[in]       leftMatrixData      运算符左边的矩阵数据
             * @param[in]       leftRow             运算符左边的矩阵行
             * @param[in]       leftCol             运算符左边的矩阵列
             * @param[in]       rightMatrixData     运算符右边的矩阵数据
             * @param[in]       rightRow            运算符右边的矩阵行
             * @param[in]       rightCol            运算符右边的矩阵列
             * @param[in]       outRow              输出矩阵行
             * @param[in]       outCol              输出矩阵列
             * @param[out]      outMatrixData       输出矩阵数据
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 MatrixSub(const DOUBLE* leftMatrixData,
                                   const UINT32 leftRow,
                                   const UINT32 leftCol,
                                   const DOUBLE* rightMatrixData,
                                   const UINT32 rightRow,
                                   const UINT32 rightCol,
                                   const UINT32 outRow,
                                   const UINT32 outCol,
                                   DOUBLE* outMatrixData);

            /**
             * @brief           矩阵乘法
             * @param[in]       leftMatrixData      运算符左边的矩阵数据
             * @param[in]       leftRow             运算符左边的矩阵行
             * @param[in]       leftCol             运算符左边的矩阵列
             * @param[in]       rightMatrixData     运算符右边的矩阵数据
             * @param[in]       rightRow            运算符右边的矩阵行
             * @param[in]       rightCol            运算符右边的矩阵列
             * @param[in]       outRow              输出矩阵行
             * @param[in]       outCol              输出矩阵列
             * @param[out]      outMatrixData       输出矩阵数据
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 MatrixMul(const DOUBLE* leftMatrixData,
                                   const UINT32 leftRow,
                                   const UINT32 leftCol,
                                   const DOUBLE* rightMatrixData,
                                   const UINT32 rightRow,
                                   const UINT32 rightCol,
                                   const UINT32 outRow,
                                   const UINT32 outCol,
                                   DOUBLE* outMatrixData);

            /**
             * @brief           矩阵转置
             * @author          pengshupan@sixents.com
             * @param[in]       inMatrixData        输入矩阵数据
             * @param[in]       inRow               输入矩阵行
             * @param[in]       inCol               输入矩阵列
             * @param[in]       outRow              输出矩阵行
             * @param[in]       outCol              输出矩阵列
             * @param[out]      outMatrixData       输出矩阵数据
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 MatrixTransposition(const DOUBLE* inMatrixData,
                                             const UINT32 inRow,
                                             const UINT32 inCol,
                                             const UINT32 outRow,
                                             const UINT32 outCol,
                                             DOUBLE* outMatrixData);

            /**
             * @brief           矩阵求逆
             * @author          pengshupan@sixents.com
             * @param[in]       inMatrixData        输入矩阵数据
             * @param[in]       inRow               输入矩阵行
             * @param[in]       inCol               输入矩阵列
             * @param[in]       outRow              输出矩阵行
             * @param[in]       outCol              输出矩阵列
             * @param[out]      outMatrixData       输出矩阵数据
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 MatrixInverse(const DOUBLE* inMatrixData,
                                       const UINT32 inRow,
                                       const UINT32 inCol,
                                       const UINT32 outRow,
                                       const UINT32 outCol,
                                       DOUBLE* outMatrixData);

            /**
             * @brief           矩阵增加行列
             * @author          pengshupan@sixents.com
             * @param[in]       inMatrixData        输入矩阵数据
             * @param[in]       inRow               输入矩阵行
             * @param[in]       inCol               输入矩阵列
             * @param[in]       outRow              输出矩阵行
             * @param[in]       outCol              输出矩阵列
             * @param[out]      outMatrixData       输出矩阵数据
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 MatrixAddRowCol(const DOUBLE* inMatrixData,
                                         const UINT32 inRow,
                                         const UINT32 inCol,
                                         const UINT32 outRow,
                                         const UINT32 outCol,
                                         DOUBLE* outMatrixData);

            /**
             * @brief           矩阵减少行列
             * @author          pengshupan@sixents.com
             * @param[in]       inMatrixData        输入矩阵数据
             * @param[in]       inRow               输入矩阵行
             * @param[in]       inCol               输入矩阵列
             * @param[in]       outRow              输出矩阵行
             * @param[in]       outCol              输出矩阵列
             * @param[out]      outMatrixData       输出矩阵数据
             * @exception       N/A
             * @return          函数执行是否成功
             * @note            N/A
             */
            static INT32 MatrixSubRowCol(const DOUBLE* inMatrixData,
                                         const UINT32 inRow,
                                         const UINT32 inCol,
                                         const UINT32 outRow,
                                         const UINT32 outCol,
                                         DOUBLE* outMatrixData);
        };
    } // namespace Math
} // end namespace sixents

#endif