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
        {
        }

        CGNSSMatrix::~CGNSSMatrix()
        {
        }

        CGNSSMatrix::CGNSSMatrix(const CGNSSMatrix& matrixObj)
        {
        }

        SGNSSMatrix CGNSSMatrix::GetMatrix()
        {
            return m_matrix;
        }

        CGNSSMatrix CGNSSMatrix::operator+(CGNSSMatrix& matrix)  const // 加法
        {
            CGNSSMatrix mat;
            if (matrix.GetMatrix().row != m_matrix.row || matrix.GetMatrix().col != m_matrix.col)
            {
                return mat;
            }
            for (int i = 0; i < matrix.GetMatrix().row; i++)
            {
                for (int j = 0; j < matrix.GetMatrix().col; j++)
                {
                    mat.GetMatrix().matrixNum[i][j] = m_matrix.matrixNum[i][j] + matrix.GetMatrix().matrixNum[i][j];
                }
            }
            return matrix;
        }

        CGNSSMatrix CGNSSMatrix::operator-(CGNSSMatrix& matrix)  // 减法
        {
            CGNSSMatrix mat;

            if (matrix.GetMatrix().row != m_matrix.row || matrix.GetMatrix().col != m_matrix.col)
            {
                return mat;
            }
            for (int i = 0; i < matrix.GetMatrix().row; i++)
            {
                for (int j = 0; j < matrix.GetMatrix().col; j++)
                {
                    mat.GetMatrix().matrixNum[i][j] = m_matrix.matrixNum[i][j] - matrix.GetMatrix().matrixNum[i][j];
                }
            }
            return matrix;
        }

        CGNSSMatrix CGNSSMatrix::operator*(CGNSSMatrix& matrix) // 乘法
        {
            //分配被乘数
            Eigen::MatrixXd mat1(m_matrix.row, m_matrix.col);
            //分配乘数
            Eigen::MatrixXd mat2(matrix.GetMatrix().row, matrix.GetMatrix().col);
            //分配结果
            Eigen::MatrixXd matResult(m_matrix.row, matrix.GetMatrix().col);
            if (m_matrix.col != matrix.GetMatrix().row)
            {
                return matrix;
            }

            for (int i = 0; i < m_matrix.row; i++)
            {
                for (int j = 0; j < m_matrix.col; j++)
                {
                    mat1(i, j) = m_matrix.matrixNum[i][j];
                }
            }

            for (int i = 0; i < matrix.GetMatrix().row; i++)
            {
                for (int j = 0; j < matrix.GetMatrix().col; j++)
                {
                    mat2(i, j) = matrix.GetMatrix().matrixNum[i][j];
                }
            }

            matResult = mat1 * mat2;
            for (int i = 0; i < m_matrix.row; i++)
            {
                for (int j = 0; j < matrix.GetMatrix().col; j++)
                {
                    std::cout << matResult(i, j) << std::endl;
                }
            }
            return matrix;
        }

        int GNSSMathUtilityLib::CGNSSMatrix::MatrixInverse(SGNSSMatrix& matrix)
        {
            if (matrix.row != matrix.col)
            {
                return 0;
            }
            Eigen::MatrixXd mat(matrix.row, matrix.col);
            for (int i = 0; i < matrix.row; i++)
            {
                for (int j = 0; j < matrix.col; j++)
                {
                    mat(i, j) = matrix.matrixNum[i][j];
                }
            }
            auto matInverse = mat.inverse();
            return 1;
        }

        int GNSSMathUtilityLib::CGNSSMatrix::MatrixTransposition(SGNSSMatrix& matrix)
        {
            Eigen::MatrixXd mat(matrix.row, matrix.col);
            for (int i = 0; i < matrix.row; i++)
            {
                for (int j = 0; j < matrix.col; j++)
                {
                    mat(i, j) = matrix.matrixNum[i][j];
                }
            }
            auto matTransposition = mat.transpose();
            return 1;
        }
    }
}