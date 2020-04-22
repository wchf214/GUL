#ifndef _GNSS_MATH_UTILITY_INTERFACE_H_
#define _GNSS_MATH_UTILITY_INTERFACE_H_

#include <string>

#include "GNSSCommonStruct.h"
#include "GNSSMatrix/CGNSSMatrix.h"

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
            // 矩阵加法
            // destMatrix：输入/输出参数，既是被加数，又是结果
            // srcMatrix 输入参数，加数
            DLL_API int STD_CALL MatrixAdd(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix);

            // 矩阵减法
            // destMatrix：输入/输出参数，既是被减数，又是结果
            // srcMatrix 输入参数，减数
            DLL_API int STD_CALL MatrixSub(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix);

            // 矩阵乘法
            // destMatrix：输入/输出参数，既是被乘数，又是结果
            // srcMatrix 输入参数，乘数
            DLL_API int STD_CALL MatrixMul(SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix);

            // 矩阵转置
            // desMatrix：输入/输出参数，待转置矩阵，同时也是结果
            DLL_API int STD_CALL MatrixTransposition(SGNSSMatrix& matrix);

            // 矩阵求逆
            // desMatrix：输入/输出参数，待求逆矩阵，同时也是结果
            DLL_API int STD_CALL MatrixInverse(SGNSSMatrix& matrix);

            // 矩阵增加行列
            // 增加的行列，给默认值1，以后再根据需求进行优化。
            // desMatrix：输入/输出参数，待增加行列的矩阵，同时也是结果
            // row: 输入参数，增加的行数
            // col: 输入参数，增加的列数
            DLL_API int STD_CALL MatrixAddRowCol(SGNSSMatrix& matrix, const int row, const int col);

            // 矩阵减少行列
            // desMatrix：输入/输出参数，待减少行列的矩阵，同时也是结果
            // row: 输入参数，减少的行数
            // col: 输入参数，减少的列数
            DLL_API int STD_CALL MatrixSubRowCol(SGNSSMatrix& matrix, const int row, const int col);

#ifdef __cplusplus
        }
#endif
    }  // end namespace GNSSMathUtilityLib
}  // end namespace sixents

#endif