#ifndef _GNSS_MATH_UTILITY_INTERFACE_H_
#define _GNSS_MATH_UTILITY_INTERFACE_H_

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
#define UNREFERENCED_PARAMETER(P) (P)

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
                                       const int leftRow,
                                       const int leftCol,
                                       const double* rightMatrixData,
                                       const int rightRow,
                                       const int rightCol,
                                       double* outMatrixData,
                                       int& outRow,
                                       int& outCol);

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
                                       const int leftRow,
                                       const int leftCol,
                                       const double* rightMatrixData,
                                       const int rightRow,
                                       const int rightCol,
                                       double* outMatrixData,
                                       int& outRow,
                                       int& outCol);

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
                                       const int leftRow,
                                       const int leftCol,
                                       const double* rightMatrixData,
                                       const int rightRow,
                                       const int rightCol,
                                       double* outMatrixData,
                                       int& outRow,
                                       int& outCol);

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
                                                 const int inRow,
                                                 const int inCol,
                                                 double* outMatrixData,
                                                 int& outRow,
                                                 int& outCol);

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
                                           const int inRow,
                                           const int inCol,
                                           double* outMatrixData,
                                           int& outRow,
                                           int& outCol);

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
                                             const int inRow,
                                             const int inCol,
                                             double* outMatrixData,
                                             int& outRow,
                                             int& outCol);

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
                                             const int inRow,
                                             const int inCol,
                                             double* outMatrixData,
                                             int& outRow,
                                             int& outCol);

#ifdef __cplusplus
        }
#endif
    } // end namespace GNSSMathUtilityLib
} // end namespace sixents

#endif