/** @file          CGNSSMatrix.h
 *  @brief         矩阵运算类
 *  @details       N/A
 *  @author        pengshupan@sixens.com
 *  @date          2020/04/24
 *  @version       1.0
 *  @note          N/A
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef GNSS_MATRIX_H
#define GNSS_MATRIX_H

#include "../DllMain/GNSSCommonStruct.h"

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        /**
         *  @class       CGNSSMatrix
         *  @brief       矩阵算法类
         *  @author      pengshupan@sixents.com
         *  @note
         */
        class CGNSSMatrix
        {
        public:
            /**
             * @brief       矩阵的默认构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @note        N/A
             */
            explicit CGNSSMatrix();

            /**
             * @brief       参数为行和列的构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   row         矩阵行
             * @param[in]   col         矩阵列
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @note        N/A
             */
            CGNSSMatrix(UINT32 row, UINT32 col);

            /**
             * @brief       参数为矩阵类型的构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   matrix          矩阵结构
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @note        N/A
             */
            explicit CGNSSMatrix(const SGNSSMatrix& matrix);

            /**
             * @brief       拷贝构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   matrixObj       被拷贝对象
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @note        N/A
             */
            CGNSSMatrix(const CGNSSMatrix& matrixObj);

            /**
             * @brief       析构函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @note        N/A
             */
            virtual ~CGNSSMatrix();

            /**
             * @brief       设置矩阵
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @note        N/A
             */
            BOOL_T InitMatrixObj();

            /**
             * @brief       设置矩阵
             * @author      pengshupan@sixents.com
             * @param[in]   matrix 设置的矩阵
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @note        N/A
             */
            void SetMatrix(const SGNSSMatrix& matrix);

            /**
             * @brief       设置矩阵
             * @author      pengshupan@sixents.com
             * @param[in]   matrixData      矩阵数据
             * @param[in]   row             当前矩阵的行
             * @param[in]   col             当前矩阵的列
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @note        N/A
             */
            void SetMatrix(const DOUBLE* matrixData, const UINT32 row, const UINT32 col);

            /**
             * @brief       获取矩阵数据
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            SGNSSMatrix GetMatrix();

            /**
             * @brief       矩阵加法运算符重载
             * @author      pengshupan@sixents.com
             * @param[in]   matrix 矩阵加数
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            CGNSSMatrix operator+(CGNSSMatrix& matrix) const;
            /**
             * @brief       矩阵减法运算符重载
             * @author      pengshupan@sixents.com
             * @param[in]   matrix 矩阵减数
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            CGNSSMatrix operator-(CGNSSMatrix& matrix);
            /**
             * @brief       矩阵乘法运算符重载
             * @author      pengshupan@sixents.com
             * @param[in]   matrix 矩阵乘数
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            CGNSSMatrix operator*(CGNSSMatrix& matrix);

            /**
             * @brief       矩阵转置运算
             * @author      pengshupan@sixents.com
             * @param[in]   matrix 待转置的矩阵
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            CGNSSMatrix MatrixTransposition(SGNSSMatrix& matrix);
            /**
             * @brief       矩阵求逆运算
             * @author      pengshupan@sixents.com
             * @param[in]   matrix 待求逆的矩阵
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            SGNSSMatrix MatrixInverse(SGNSSMatrix& matrix);
            /**
             * @brief       矩阵添加行列运算
             * @author      pengshupan@sixents.com
             * @param[in]   addNum 矩阵增加行列数
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            CGNSSMatrix MatrixAdd(UINT32 addNum);
            /**
             * @brief       矩阵删除行列
             * @author      pengshupan@sixents.com
             * @param[in]   subNum 矩阵删除行列数
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            CGNSSMatrix MatrixSub(UINT32 subNum);

        private:
            SGNSSMatrix m_matrix;
        };
    } // end namespace GNSSMathUtilityLib
} // end namespace sixents

#endif
