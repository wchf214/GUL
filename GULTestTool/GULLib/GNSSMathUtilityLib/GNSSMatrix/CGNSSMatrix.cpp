#include "CGNSSMatrix.h"

#include <iostream>

#include "../Eigen/eigen-eigen-323c052e1731/Eigen/Dense"
namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        CGNSSMatrix::CGNSSMatrix(const SGNSSMatrix& matrix)
        {
            m_matrix = matrix;
        }

        CGNSSMatrix::CGNSSMatrix()
        {}

        CGNSSMatrix::CGNSSMatrix(int row, int col)
        {
            m_matrix.row = row;
            m_matrix.col = col;
            m_matrix.matrixNum = new double*[row];
            for (int i = 0; i < row; i++)
            {
                m_matrix.matrixNum[i] = new double[col];
            }
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    m_matrix.matrixNum[i][j] = 0;
                }
            }
        }

        CGNSSMatrix::~CGNSSMatrix()
        {
            //            for (int i = 0; i <m_matrix.row; i++)
            //            {
            //                   delete[] m_matrix.matrixNum[i];
            //            }
            //            delete[] m_matrix.matrixNum;
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
            if (matrix.GetMatrix().row != m_matrix.row || matrix.GetMatrix().col != m_matrix.col)
            {
                return matrix;
            }
            for (int i = 0; i < matrix.GetMatrix().row; i++)
            {
                for (int j = 0; j < matrix.GetMatrix().col; j++)
                {
                    matrix.GetMatrix().matrixNum[i][j] = m_matrix.matrixNum[i][j] + matrix.GetMatrix().matrixNum[i][j];
                }
            }
            return matrix;
        }

        CGNSSMatrix CGNSSMatrix::operator-(CGNSSMatrix& matrix) // 减法
        {
            if (matrix.GetMatrix().row != m_matrix.row || matrix.GetMatrix().col != m_matrix.col)
            {
                return matrix;
            }
            for (int i = 0; i < matrix.GetMatrix().row; i++)
            {
                for (int j = 0; j < matrix.GetMatrix().col; j++)
                {
                    matrix.GetMatrix().matrixNum[i][j] = m_matrix.matrixNum[i][j] - matrix.GetMatrix().matrixNum[i][j];
                }
            }
            return matrix;
        }

        CGNSSMatrix CGNSSMatrix::operator*(CGNSSMatrix& matrix) // 乘法
        {
            // 定义一个返回矩阵
            CGNSSMatrix matrixResult(m_matrix.row, matrix.GetMatrix().col);
            // 分配被乘数
            Eigen::MatrixXd mat1(m_matrix.row, m_matrix.col);
            // 分配乘数
            Eigen::MatrixXd mat2(matrix.GetMatrix().row, matrix.GetMatrix().col);
            // 分配结果
            Eigen::MatrixXd matall(m_matrix.row, matrix.GetMatrix().col);
            if (m_matrix.col != matrix.GetMatrix().row)
            {
                return matrixResult;
            }
            // 把m_matrix存入Eigen自定义数据类型mat1
            for (int i = 0; i < m_matrix.row; i++)
            {
                for (int j = 0; j < m_matrix.col; j++)
                {
                    mat1(i, j) = m_matrix.matrixNum[i][j];
                }
            }
            // 把matrix存入Eigen自定义数据类型mat2
            for (int i = 0; i < matrix.GetMatrix().row; i++)
            {
                for (int j = 0; j < matrix.GetMatrix().col; j++)
                {
                    mat2(i, j) = matrix.GetMatrix().matrixNum[i][j];
                }
            }
            matall = mat1 * mat2;
            for (int i = 0; i < matrixResult.GetMatrix().row; i++)
            {
                for (int j = 0; j < matrixResult.GetMatrix().col; j++)
                {
                    matrixResult.GetMatrix().matrixNum[i][j] = matall(i, j);
                }
            }
            return matrixResult;
        }

        //        CGNSSMatrix CGNSSMatrix::operator=(CGNSSMatrix& matrix) // 赋值
        //        {
        //            for(int i=0;i<m_matrix.row;i++)
        //            {
        //                for(int j=0;j<m_matrix.col;j++)
        //                {
        //                    matrix.GetMatrix().matrixNum[i][j]=m_matrix.matrixNum[i][j];
        //                }
        //            }
        //            return matrix;
        //        }

        SGNSSMatrix GNSSMathUtilityLib::CGNSSMatrix::MatrixInverse(SGNSSMatrix& matrix)
        {
            // 只有方阵才有逆矩阵
            if (m_matrix.row != m_matrix.col)
            {
                return matrix;
            }
            CGNSSMatrix matrixResult(matrix.col, matrix.row);
            Eigen::MatrixXd mat(matrix.row, matrix.col);
            for (int i = 0; i < m_matrix.row; i++)
            {
                for (int j = 0; j < m_matrix.col; j++)
                {
                    mat(i, j) = m_matrix.matrixNum[i][j];
                }
            }
            Eigen::MatrixXd maxInverse = mat.inverse();
            for (int i = 0; i < matrixResult.GetMatrix().row; i++)
            {
                for (int j = 0; j < matrixResult.GetMatrix().col; j++)
                {
                    matrix.matrixNum[i][j] = maxInverse(i, j);
                }
            }
            return matrix;
        }

        CGNSSMatrix GNSSMathUtilityLib::CGNSSMatrix::MatrixTransposition(SGNSSMatrix& matrix)
        {
            Eigen::MatrixXd mat(m_matrix.row, m_matrix.col);
            for (int i = 0; i < m_matrix.row; i++)
            {
                for (int j = 0; j < m_matrix.col; j++)
                {
                    mat(i, j) = m_matrix.matrixNum[i][j];
                }
            }
            Eigen::MatrixXd matTransposition = mat.transpose();
            CGNSSMatrix TranspositionMatrix(m_matrix.col, m_matrix.row);
            for (int i = 0; i < matTransposition.rows(); i++)
            {
                for (int j = 0; j < matTransposition.cols(); j++)
                {
                    TranspositionMatrix.GetMatrix().matrixNum[i][j] = matTransposition(i, j);
                }
            }
            return TranspositionMatrix;
        }

        CGNSSMatrix GNSSMathUtilityLib::CGNSSMatrix::MatrixAdd(int addNum)
        {
            CGNSSMatrix matrixResult(m_matrix.row + addNum, m_matrix.col + addNum);
            if (m_matrix.row != m_matrix.col)
            {
                return matrixResult;
            }

            for (int i = 0; i < m_matrix.row; i++)
            {
                for (int j = 0; j < m_matrix.col; j++)
                {
                    matrixResult.GetMatrix().matrixNum[i][j] = m_matrix.matrixNum[i][j];
                }
            }

            for (int i = m_matrix.row; i < m_matrix.row + addNum; i++)
            {
                for (int j = m_matrix.col; j < m_matrix.col + addNum; j++)
                {
                    matrixResult.GetMatrix().matrixNum[i][j] = 0;
                }
            }
            return matrixResult;
        }

        CGNSSMatrix GNSSMathUtilityLib::CGNSSMatrix::MatrixSub(int subNum)
        {
            CGNSSMatrix matrixResult(m_matrix.row - subNum, m_matrix.col - subNum);
            if (m_matrix.row != m_matrix.col)
            {
                return matrixResult;
            }

            for (int i = 0; i < matrixResult.GetMatrix().row - subNum; i++)
            {
                for (int j = 0; j < matrixResult.GetMatrix().col - subNum; j++)
                {
                    matrixResult.GetMatrix().matrixNum[i][j] = m_matrix.matrixNum[i][j];
                }
            }
            return matrixResult;
        }
    } // namespace GNSSMathUtilityLib
} // namespace sixents