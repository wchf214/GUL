#include "CGNSSMatrix.h"
#include "../Eigen/eigen-eigen-323c052e1731/Eigen/Dense"
namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        CGNSSMatrix::CGNSSMatrix()
        {
        }

        CGNSSMatrix::~CGNSSMatrix()
        {
        }

        CGNSSMatrix::CGNSSMatrix(const CGNSSMatrix& matrixObj)
        {
        }

        CGNSSMatrix CGNSSMatrix::operator+(CGNSSMatrix& matrix)  // 加法
        {
            if (matrix.GetMatrix().row != this->GetMatrix().row || matrix.GetMatrix().col != this->GetMatrix().col)
            {
            }
            for (int i = 0; i < matrix.GetMatrix().row; i++)
            {
                for (int j = 0; j < matrix.GetMatrix().col; j++)
                {
                    matrix.GetMatrix().matrixNum[i][j] = this->GetMatrix().matrixNum[i][j] + matrix.GetMatrix().matrixNum[i][j];
                }
            }
            return matrix;
        }
        CGNSSMatrix CGNSSMatrix::operator-(CGNSSMatrix& matrix)  // 减法
        {
            if (matrix.GetMatrix().row != this->GetMatrix().row || matrix.GetMatrix().col != this->GetMatrix().col)
            {
            }
            for (int i = 0; i < matrix.GetMatrix().row; i++)
            {
                for (int j = 0; j < matrix.GetMatrix().col; j++)
                {
                    matrix.GetMatrix().matrixNum[i][j] = this->GetMatrix().matrixNum[i][j] - matrix.GetMatrix().matrixNum[i][j];
                }
            }
            return matrix;
        }
        //CGNSSMatrix CGNSSMatrix::operator*(const CGNSSMatrix& matrix) const// 乘法
        //{
        //    return matrix;
        //}

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