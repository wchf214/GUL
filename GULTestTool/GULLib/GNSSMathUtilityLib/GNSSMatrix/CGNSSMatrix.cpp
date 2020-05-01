#include <iostream>

#include "CGNSSMatrix.h"
#include "../Eigen/eigen-eigen-323c052e1731/Eigen/Dense"

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        CGNSSMatrix::CGNSSMatrix(const SGNSSMatrix& matrix)
        {
//            m_matrix = matrix;    //浅拷贝，有问题
            InitMatrixObj();
            do {
                if (matrix.m_matrixNum == nullptr || matrix.m_row == 0 || matrix.m_col == 0) {
                    break;
                }

            } while(false);

        }

        CGNSSMatrix::CGNSSMatrix()
        {
            InitMatrixObj();
        }

        CGNSSMatrix::CGNSSMatrix(UINT32 row, UINT32 col)
        {
            m_matrix.m_row = row;
            m_matrix.m_col = col;
            m_matrix.m_matrixNum = new DOUBLE*[row];
            for (UINT32 i = 0; i < row; i++)
            {
                m_matrix.m_matrixNum[i] = new DOUBLE[col];
            }

            for (UINT32 i = 0; i < row; i++)
            {
                for (UINT32 j = 0; j < col; j++)
                {
                    m_matrix.m_matrixNum[i][j] = 0;
                }
            }
        }

        CGNSSMatrix::~CGNSSMatrix()
        {}

        BOOL_T CGNSSMatrix::InitMatrixObj()
        {
            BOOL_T ret = false;
            do {
                if (m_matrix.m_matrixNum == nullptr) {
                    ret = true;
                } else if (m_matrix.m_row == 0) {
                    m_matrix.m_matrixNum = nullptr;
                    ret = true;
                } else {
                    for (UINT32 rowIdx = 0; rowIdx < m_matrix.m_row; ++rowIdx) {
                        delete [] m_matrix.m_matrixNum[rowIdx];
                        m_matrix.m_matrixNum[rowIdx] = nullptr;
                    }
                    delete [] m_matrix.m_matrixNum;
                    m_matrix.m_matrixNum = nullptr;
                    ret = true;
                }
            } while (false);

            m_matrix.m_row = 0;
            m_matrix.m_col = 0;
            return ret;
        }

        void CGNSSMatrix::SetMatrix(const DOUBLE *matrixData, const UINT32 row, const UINT32 col)
        {
            if (matrixData == nullptr) {
                return;
            }

            if (!InitMatrixObj()) {
                return;
            }
            m_matrix.m_row = row;
            m_matrix.m_col = col;

        }

        CGNSSMatrix::CGNSSMatrix(const CGNSSMatrix& matrixObj)
        {
            m_matrix = matrixObj.m_matrix;
        }

        SGNSSMatrix CGNSSMatrix::GetMatrix()
        {
            return m_matrix;
        }

        CGNSSMatrix CGNSSMatrix::operator+(CGNSSMatrix& matrix) const // 加法
        {
            // 首先判断相加的矩阵行数和列数是否相同，相同再进行计算
            if (matrix.GetMatrix().m_row != m_matrix.m_row || matrix.GetMatrix().m_col != m_matrix.m_col)
            {
                return matrix;
            }
            for (UINT32 i = 0; i < matrix.GetMatrix().m_row; i++)
            {
                for (UINT32 j = 0; j < matrix.GetMatrix().m_col; j++)
                {
                    matrix.GetMatrix().m_matrixNum[i][j] = m_matrix.m_matrixNum[i][j] + matrix.GetMatrix().m_matrixNum[i][j];
                }
            }
            return matrix;
        }

        CGNSSMatrix CGNSSMatrix::operator-(CGNSSMatrix& matrix) // 减法
        {
            if (matrix.GetMatrix().m_row != m_matrix.m_row || matrix.GetMatrix().m_col != m_matrix.m_col)
            {
                return matrix;
            }
            for (UINT32 i = 0; i < matrix.GetMatrix().m_row; i++)
            {
                for (UINT32 j = 0; j < matrix.GetMatrix().m_col; j++)
                {
                    matrix.GetMatrix().m_matrixNum[i][j] = m_matrix.m_matrixNum[i][j] - matrix.GetMatrix().m_matrixNum[i][j];
                }
            }
            return matrix;
        }

        CGNSSMatrix CGNSSMatrix::operator*(CGNSSMatrix& matrix) // 乘法
        {
            // 定义一个返回矩阵
            CGNSSMatrix matrixResult(m_matrix.m_row, matrix.GetMatrix().m_col);
            // 分配被乘数
            Eigen::MatrixXd mat1(m_matrix.m_row, m_matrix.m_col);
            // 分配乘数
            Eigen::MatrixXd mat2(matrix.GetMatrix().m_row, matrix.GetMatrix().m_col);
            // 分配结果
            Eigen::MatrixXd matall(m_matrix.m_row, matrix.GetMatrix().m_col);
            if (m_matrix.m_col != matrix.GetMatrix().m_row)
            {
                return matrixResult;
            }
            // 把m_matrix存入Eigen自定义数据类型mat1
            for (UINT32 i = 0; i < m_matrix.m_row; i++)
            {
                for (UINT32 j = 0; j < m_matrix.m_col; j++)
                {
                    mat1(i, j) = m_matrix.m_matrixNum[i][j];
                }
            }
            // 把matrix存入Eigen自定义数据类型mat2
            for (UINT32 i = 0; i < matrix.GetMatrix().m_row; i++)
            {
                for (UINT32 j = 0; j < matrix.GetMatrix().m_col; j++)
                {
                    mat2(i, j) = matrix.GetMatrix().m_matrixNum[i][j];
                }
            }
            matall = mat1 * mat2;
            for (UINT32 i = 0; i < matrixResult.GetMatrix().m_row; i++)
            {
                for (UINT32 j = 0; j < matrixResult.GetMatrix().m_col; j++)
                {
                    matrixResult.GetMatrix().m_matrixNum[i][j] = matall(i, j);
                }
            }
            return matrixResult;
        }

        //        CGNSSMatrix CGNSSMatrix::operator=(CGNSSMatrix& matrix) // 赋值
        //        {
        //            for(UINT32 i=0;i<m_matrix.row;i++)
        //            {
        //                for(UINT32 j=0;j<m_matrix.col;j++)
        //                {
        //                    matrix.GetMatrix().matrixNum[i][j]=m_matrix.matrixNum[i][j];
        //                }
        //            }
        //            return matrix;
        //        }

        SGNSSMatrix GNSSMathUtilityLib::CGNSSMatrix::MatrixInverse(SGNSSMatrix& matrix)
        {
            // 只有方阵才有逆矩阵
            if (m_matrix.m_row != m_matrix.m_col)
            {
                return matrix;
            }
            CGNSSMatrix matrixResult(matrix.m_col, matrix.m_row);
            Eigen::MatrixXd mat(matrix.m_row, matrix.m_col);
            for (UINT32 i = 0; i < m_matrix.m_row; i++)
            {
                for (UINT32 j = 0; j < m_matrix.m_col; j++)
                {
                    mat(i, j) = m_matrix.m_matrixNum[i][j];
                }
            }
            Eigen::MatrixXd maxInverse = mat.inverse();
            for (UINT32 i = 0; i < matrixResult.GetMatrix().m_row; i++)
            {
                for (UINT32 j = 0; j < matrixResult.GetMatrix().m_col; j++)
                {
                    matrix.m_matrixNum[i][j] = maxInverse(i, j);
                }
            }
            return matrix;
        }

        CGNSSMatrix GNSSMathUtilityLib::CGNSSMatrix::MatrixTransposition(SGNSSMatrix& matrix)
        {
            Eigen::MatrixXd mat(m_matrix.m_row, m_matrix.m_col);
            for (UINT32 i = 0; i < m_matrix.m_row; i++)
            {
                for (UINT32 j = 0; j < m_matrix.m_col; j++)
                {
                    mat(i, j) = m_matrix.m_matrixNum[i][j];
                }
            }
            Eigen::MatrixXd matTransposition = mat.transpose();
            CGNSSMatrix TranspositionMatrix(m_matrix.m_col, m_matrix.m_row);
            for (UINT32 i = 0; i < matTransposition.rows(); i++)
            {
                for (UINT32 j = 0; j < matTransposition.cols(); j++)
                {
                    TranspositionMatrix.GetMatrix().m_matrixNum[i][j] = matTransposition(i, j);
                }
            }
            return TranspositionMatrix;
        }

        CGNSSMatrix GNSSMathUtilityLib::CGNSSMatrix::MatrixAdd(UINT32 addNum)
        {
            CGNSSMatrix matrixResult(m_matrix.m_row + addNum, m_matrix.m_col + addNum);
            if (m_matrix.m_row != m_matrix.m_col)
            {
                return matrixResult;
            }

            for (UINT32 i = 0; i < m_matrix.m_row; i++)
            {
                for (UINT32 j = 0; j < m_matrix.m_col; j++)
                {
                    matrixResult.GetMatrix().m_matrixNum[i][j] = m_matrix.m_matrixNum[i][j];
                }
            }

            for (UINT32 i = m_matrix.m_row; i < m_matrix.m_row + addNum; i++)
            {
                for (UINT32 j = m_matrix.m_col; j < m_matrix.m_col + addNum; j++)
                {
                    matrixResult.GetMatrix().m_matrixNum[i][j] = 0;
                }
            }
            return matrixResult;
        }

        CGNSSMatrix GNSSMathUtilityLib::CGNSSMatrix::MatrixSub(UINT32 subNum)
        {
            CGNSSMatrix matrixResult(m_matrix.m_row - subNum, m_matrix.m_col - subNum);
            if (m_matrix.m_row != m_matrix.m_col)
            {
                return matrixResult;
            }

            for (UINT32 i = 0; i < matrixResult.GetMatrix().m_row - subNum; i++)
            {
                for (UINT32 j = 0; j < matrixResult.GetMatrix().m_col - subNum; j++)
                {
                    matrixResult.GetMatrix().m_matrixNum[i][j] = m_matrix.m_matrixNum[i][j];
                }
            }
            return matrixResult;
        }
    } // namespace GNSSMathUtilityLib
} // namespace sixents