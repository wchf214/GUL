/**@file             文件名
 *  @brief          项目简述
 *  @details       项目细节
 *  @author       作者
 *  @date          日期
 *  @version      版本
 *  @note          注解
 *  @copyright   版权
 */

#ifndef _GNSS_MATRIX_H
#define _GNSS_MATRIX_H

#include "../GNSSCommonStruct.h"

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        // 矩阵结构
        class CGNSSMatrix
        {
        public:
            explicit CGNSSMatrix();
            explicit CGNSSMatrix(const SGNSSMatrix& matrix);
            CGNSSMatrix(const CGNSSMatrix& matrixObj);
            ~CGNSSMatrix();

            void SetMatrix(const SGNSSMatrix& matrix);
            SGNSSMatrix GetMatrix();

            // 计算方法
            int MatrixTransposition(SGNSSMatrix& matrix); // 转置
            int MatrixInverse(SGNSSMatrix& matrix);       // 求逆
            CGNSSMatrix operator+(CGNSSMatrix& matrix) const; // 加法
            CGNSSMatrix operator-(CGNSSMatrix& matrix); // 减法
            CGNSSMatrix operator*(CGNSSMatrix& matrix); // 乘法

        private:
            SGNSSMatrix m_matrix;
        };
    }  // end namespace GNSSMathUtilityLib
}  // end namespace sixents

#endif
