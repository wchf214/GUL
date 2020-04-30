#define DLL_EXPORT
#include "GNSSMathInterface.h"

#include "GNSSMatrix/CGNSSMatrix.h"

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        extern "C" DLL_API int STD_CALL MatrixAdd(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix)
        {
            CGNSSMatrix mat1(srcMatrix);
            CGNSSMatrix mat2(destMatrix);
            CGNSSMatrix mat3;
            mat3 = mat1+ mat2;
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixSub(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix)
        {
            CGNSSMatrix mat1(srcMatrix);
            CGNSSMatrix mat2(destMatrix);
            CGNSSMatrix mat3;
            mat3 = mat1 - mat2;
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixMul(SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix,SGNSSMatrix& outPutMatrix)
        {
            CGNSSMatrix mat1(srcMatrix);
            CGNSSMatrix mat2(destMatrix);
            CGNSSMatrix mat3(srcMatrix.row,destMatrix.col);
            mat3 = mat1 * mat2;
            for(int i=0;i<outPutMatrix.row;i++)
            {
                for(int j=0;j<outPutMatrix.col;j++)
                {
                    outPutMatrix.matrixNum[i][j]=mat3.GetMatrix().matrixNum[i][j];
                }
            }
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixTransposition(SGNSSMatrix& matrix,SGNSSMatrix& outPutMatrix)
        {
            CGNSSMatrix mat1(matrix);
            CGNSSMatrix mat2(matrix.col,matrix.row);
            mat2=mat1.MatrixTransposition(matrix);
            for(int i=0;i<outPutMatrix.row;i++)
            {
                for(int j=0;j<outPutMatrix.col;j++)
                {
                    outPutMatrix.matrixNum[i][j]=mat2.GetMatrix().matrixNum[i][j];
                }
            }
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixInverse(SGNSSMatrix& matrix)
        {
            CGNSSMatrix mat1(matrix);
            mat1.MatrixInverse(matrix);
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixAddRowCol(SGNSSMatrix& matrix, const int row, const int col,SGNSSMatrix& outPutMatrix)
        {
            CGNSSMatrix mat1(matrix);
            CGNSSMatrix mat2(matrix.row+row,matrix.col+col);
            mat2=mat1.MatrixAdd(row);
            for(int i=0;i<outPutMatrix.row;i++)
            {
                for(int j=0;j<outPutMatrix.col;j++)
                {
                    outPutMatrix.matrixNum[i][j]=mat2.GetMatrix().matrixNum[i][j];
                }
            }
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixSubRowCol(SGNSSMatrix& matrix, const int row, const int col,SGNSSMatrix& outPutMatrix)
        {
            CGNSSMatrix mat1(matrix);
            CGNSSMatrix mat2(matrix.row+row,matrix.col+col);
            mat2=mat1.MatrixAdd(row);
            for(int i=0;i<outPutMatrix.row;i++)
            {
                for(int j=0;j<outPutMatrix.col;j++)
                {
                    outPutMatrix.matrixNum[i][j]=mat2.GetMatrix().matrixNum[i][j];
                }
            }
            return 0;
        }
    }
}