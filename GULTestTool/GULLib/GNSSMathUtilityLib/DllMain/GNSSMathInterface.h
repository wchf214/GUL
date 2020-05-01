/** @file          GNSSMathInterface.h
 *  @brief         矩阵运算接口
 *  @details       N/A
 *  @author        pengshupan@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef GNSS_MATH_UTILITY_INTERFACE_H_
#define GNSS_MATH_UTILITY_INTERFACE_H_

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
#ifdef _WIN32
#define STD_CALL _stdcall
#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#else
#define DLL_API __attribute__((visibility("default")))
#define STD_CALL
#endif

#ifdef __cplusplus
        extern "C" {
#endif
        // 矩阵相关接口

        /**
         * @brief           矩阵加法
         * @author          pengshupan@sixents.com
         * @param[in]       inLeftMatrix            运算符左边的矩阵
         * @param[in]       inRightMatrix           运算符左边的矩阵
         * @param[out]      outMatrix               输出矩阵
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL MatrixAdd(const double* leftMatrixData,
                                       const unsigned int leftRow,
                                       const unsigned int leftCol,
                                       const double* rightMatrixData,
                                       const unsigned int rightRow,
                                       const unsigned int rightCol,
                                       double* outMatrixData,
                                       unsigned int& outRow,
                                       unsigned int& outCol);

        /**
         * @brief           矩阵减法
         * @author          pengshupan@sixents.com
         * @param[in]       inLeftMatrix            运算符左边的矩阵
         * @param[in]       inRightMatrix           运算符左边的矩阵
         * @param[out]      outMatrix               输出矩阵
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL MatrixSub(const double* leftMatrixData,
                                       const unsigned int leftRow,
                                       const unsigned int leftCol,
                                       const double* rightMatrixData,
                                       const unsigned int rightRow,
                                       const unsigned int rightCol,
                                       double* outMatrixData,
                                       unsigned int& outRow,
                                       unsigned int& outCol);

        /**
         * @brief           矩阵乘法
         * @author          pengshupan@sixents.com
         * @param[in]       inLeftMatrix            运算符左边的矩阵
         * @param[in]       inRightMatrix           运算符左边的矩阵
         * @param[out]      outMatrix               输出矩阵
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL MatrixMul(const double* leftMatrixData,
                                       const unsigned int leftRow,
                                       const unsigned int leftCol,
                                       const double* rightMatrixData,
                                       const unsigned int rightRow,
                                       const unsigned int rightCol,
                                       double* outMatrixData,
                                       unsigned int& outRow,
                                       unsigned int& outCol);

        /**
         * @brief           矩阵转置
         * @author          pengshupan@sixents.com
         * @param[in]       inMatrix                转置前的矩阵
         * @param[out]      outMatrix               输出矩阵
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL MatrixTransposition(const double* inMatrixData,
                                                 const unsigned int inRow,
                                                 const unsigned int inCol,
                                                 double* outMatrixData,
                                                 unsigned int& outRow,
                                                 unsigned int& outCol);

        /**
         * @brief           矩阵求逆
         * @author          pengshupan@sixents.com
         * @param[in]       inMatrix                待求逆矩阵
         * @param[out]      outMatrix               输出矩阵
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL MatrixInverse(const double* inMatrixData,
                                           const unsigned int inRow,
                                           const unsigned int inCol,
                                           double* outMatrixData,
                                           unsigned int& outRow,
                                           unsigned int& outCol);

        /**
         * @brief           矩阵增加行列
         * @author          pengshupan@sixents.com
         * @param[in]       inMatrix            待增加行列的矩阵
         * @param[in]       row                 指定增加的行
         * @param[out]      col                 指定增加的列
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL MatrixAddRowCol(const double* inMatrixData,
                                             const unsigned int inRow,
                                             const unsigned int inCol,
                                             double* outMatrixData,
                                             unsigned int& outRow,
                                             unsigned int& outCol);

        /**
         * @brief           矩阵减少行列
         * @author          pengshupan@sixents.com
         * @param[in]       inMatrix            待减少行列的矩阵
         * @param[in]       row                 指定减少的行
         * @param[out]      col                 指定减少的列
         * @exception       N/A
         * @return          函数执行是否成功
         * @note            N/A
         */
        DLL_API int STD_CALL MatrixSubRowCol(const double* inMatrixData,
                                             const unsigned int inRow,
                                             const unsigned int inCol,
                                             double* outMatrixData,
                                             unsigned int& outRow,
                                             unsigned int& outCol);

#ifdef __cplusplus
        }  // extern "C"
#endif
    } // end namespace GNSSMathUtilityLib
} // end namespace sixents

#endif