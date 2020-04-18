#pragma once

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        // 矩阵结构
        struct SGNSSMatrix
        {
            double** matrixNum;    // 二维数组用于存放矩阵数据
            int row;               // 行数
            int col;               // 列数
        };
    }  // end namespace GNSSMathUtilityLib
}  // end namespace sixents