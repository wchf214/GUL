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

#include "../DllMain/GNSSCommonStruct.h"

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
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
             * @retval      N/A
             * @note        N/A
             */
            explicit CGNSSMatrix();
            /**
             * @brief       参数为行和列的构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            explicit CGNSSMatrix(int row, int col);
            /**
             * @brief       参数为矩阵类型的构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            explicit CGNSSMatrix(const SGNSSMatrix& matrix);

            /**
             * @brief       拷贝构造函数
             * @author      pengshupan@sixents.com
             * @param[in]   N/A
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
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
             * @retval      N/A
             * @note        N/A
             */
            virtual ~CGNSSMatrix();

            /**
             * @brief       设置矩阵
             * @author      pengshupan@sixents.com
             * @param[in]   matrix 设置的矩阵
             * @param[out]  N/A
             * @exception   N/A
             * @return      N/A
             * @retval      N/A
             * @note        N/A
             */
            void SetMatrix(const SGNSSMatrix& matrix);

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
            CGNSSMatrix MatrixAdd(int addNum);
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
            CGNSSMatrix MatrixSub(int subNum);

        private:
            SGNSSMatrix m_matrix;
        };
    } // end namespace GNSSMathUtilityLib
} // end namespace sixents

#endif
