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
    namespace Math
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
        DLL_API int STD_CALL MatrixAdd(const double* leftMatrixData,
                                       const unsigned int leftRow,
                                       const unsigned int leftCol,
                                       const double* rightMatrixData,
                                       const unsigned int rightRow,
                                       const unsigned int rightCol,
                                       const unsigned int outRow,
                                       const unsigned int outCol,
                                       double* outMatrixData);

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
        DLL_API int STD_CALL MatrixSub(const double* leftMatrixData,
                                       const unsigned int leftRow,
                                       const unsigned int leftCol,
                                       const double* rightMatrixData,
                                       const unsigned int rightRow,
                                       const unsigned int rightCol,
                                       const unsigned int outRow,
                                       const unsigned int outCol,
                                       double* outMatrixData);

        /**
         * @brief           矩阵乘法
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
        DLL_API int STD_CALL MatrixMul(const double* leftMatrixData,
                                       const unsigned int leftRow,
                                       const unsigned int leftCol,
                                       const double* rightMatrixData,
                                       const unsigned int rightRow,
                                       const unsigned int rightCol,
                                       const unsigned int outRow,
                                       const unsigned int outCol,
                                       double* outMatrixData);

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
        DLL_API int STD_CALL MatrixTransposition(const double* inMatrixData,
                                                 const unsigned int inRow,
                                                 const unsigned int inCol,
                                                 const unsigned int outRow,
                                                 const unsigned int outCol,
                                                 double* outMatrixData);

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
        DLL_API int STD_CALL MatrixInverse(const double* inMatrixData,
                                           const unsigned int inRow,
                                           const unsigned int inCol,
                                           const unsigned int outRow,
                                           const unsigned int outCol,
                                           double* outMatrixData);

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
        DLL_API int STD_CALL MatrixAddRowCol(const double* inMatrixData,
                                             const unsigned int inRow,
                                             const unsigned int inCol,
                                             const unsigned int outRow,
                                             const unsigned int outCol,
                                             double* outMatrixData);

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
        DLL_API int STD_CALL MatrixSubRowCol(const double* inMatrixData,
                                             const unsigned int inRow,
                                             const unsigned int inCol,
                                             const unsigned int outRow,
                                             const unsigned int outCol,
                                             double* outMatrixData);

#ifdef __cplusplus
        } // extern "C"
#endif
    } // namespace Math
} // end namespace sixents

#endif