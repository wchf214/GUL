#define DLL_EXPORT
#include "GULMathAppIFs.h"
#include "../GNSSMatrix/CGNSSMatrix.h"

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        INT32 CMathAppInterface::MatrixAdd(const DOUBLE* leftMatrixData,
                                           const UINT32 leftRow,
                                           const UINT32 leftCol,
                                           const DOUBLE* rightMatrixData,
                                           const UINT32 rightRow,
                                           const UINT32 rightCol,
                                           DOUBLE* outMatrixData,
                                           UINT32& outRow,
                                           UINT32& outCol)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if ((inLeftMatrix.matrixNum == nullptr || *(inLeftMatrix.matrixNum) == nullptr)
                    || (inRightMatrix.matrixNum == nullptr || *(inRightMatrix.matrixNum) == nullptr)
                    || (outMatrix.matrixNum == nullptr || *(outMatrix.matrixNum) == nullptr))
                {
                    ret = RETURN_NULL_PTR;
                }

                CGNSSMatrix mat1(inLeftMatrix);
                CGNSSMatrix mat2(inRightMatrix);
                CGNSSMatrix mat3(outMatrix);
                mat3 = mat1 + mat2;
                ret = RETURN_SUCCESS;
            } while (false);

            return ret;
        }

        INT32 CMathAppInterface::MatrixSub(const DOUBLE* leftMatrixData,
                                           const UINT32 leftRow,
                                           const UINT32 leftCol,
                                           const DOUBLE* rightMatrixData,
                                           const UINT32 rightRow,
                                           const UINT32 rightCol,
                                           DOUBLE* outMatrixData,
                                           UINT32& outRow,
                                           UINT32& outCol)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if ((inLeftMatrix.matrixNum == nullptr || *(inLeftMatrix.matrixNum) == nullptr)
                    || (inRightMatrix.matrixNum == nullptr || *(inRightMatrix.matrixNum) == nullptr)
                    || (outMatrix.matrixNum == nullptr || *(outMatrix.matrixNum) == nullptr))
                {
                    ret = RETURN_NULL_PTR;
                }

                CGNSSMatrix mat1(inLeftMatrix);
                CGNSSMatrix mat2(inRightMatrix);
                CGNSSMatrix mat3(outMatrix);
                mat3 = mat1 - mat2;
                ret = RETURN_SUCCESS;
            } while (false);

            return 0;
        }

        INT32 CMathAppInterface::MatrixMul(const DOUBLE* leftMatrixData,
                                           const UINT32 leftRow,
                                           const UINT32 leftCol,
                                           const DOUBLE* rightMatrixData,
                                           const UINT32 rightRow,
                                           const UINT32 rightCol,
                                           DOUBLE* outMatrixData,
                                           UINT32& outRow,
                                           UINT32& outCol)
        {
            if (outMatrix.row != inLeftMatrix.row || outMatrix.col != inLeftMatrix.col)
            {
                return RETURN_ERROR_PARAMETER;
            }

            CGNSSMatrix mat1(inLeftMatrix);
            CGNSSMatrix mat2(inRightMatrix);
            CGNSSMatrix mat3(inLeftMatrix.row, inRightMatrix.col);
            mat3 = mat1 * mat2;
            for (int i = 0; i < outMatrix.row; ++i)
            {
                for (int j = 0; j < outMatrix.col; ++j)
                {
                    outPutMatrix.matrixNum[i][j] = mat3.GetMatrix().matrixNum[i][j];
                }
            }
            return 0;
        }

        INT32 CMathAppInterface::MatrixTransposition(const DOUBLE* inMatrixData,
                                                     const UINT32 inRow,
                                                     const UINT32 inCol,
                                                     DOUBLE* outMatrixData,
                                                     UINT32& outRow,
                                                     UINT32& outCol)
        {
            CGNSSMatrix mat1(matrix);
            CGNSSMatrix mat2(matrix.col, matrix.row);
            mat2 = mat1.MatrixTransposition(matrix);
            for (int i = 0; i < outPutMatrix.row; i++)
            {
                for (int j = 0; j < outPutMatrix.col; j++)
                {
                    outPutMatrix.matrixNum[i][j] = mat2.GetMatrix().matrixNum[i][j];
                }
            }
            return 0;
        }

        INT32 CMathAppInterface::MatrixInverse(const DOUBLE* inMatrixData,
                                               const UINT32 inRow,
                                               const UINT32 inCol,
                                               DOUBLE* outMatrixData,
                                               UINT32& outRow,
                                               UINT32& outCol)
        {
            CGNSSMatrix mat1(matrix);
            mat1.MatrixInverse(matrix);
            return 0;
        }

        INT32 CMathAppInterface::MatrixAddRowCol(const DOUBLE* inMatrixData,
                                                 const UINT32 inRow,
                                                 const UINT32 inCol,
                                                 DOUBLE* outMatrixData,
                                                 UINT32& outRow,
                                                 UINT32& outCol)
        {
            CGNSSMatrix mat1(matrix);
            CGNSSMatrix mat2(matrix.row + row, matrix.col + col);
            mat2 = mat1.MatrixAdd(row);
            for (int i = 0; i < outPutMatrix.row; i++)
            {
                for (int j = 0; j < outPutMatrix.col; j++)
                {
                    outPutMatrix.matrixNum[i][j] = mat2.GetMatrix().matrixNum[i][j];
                }
            }
            return 0;
        }

        INT32 CMathAppInterface::MatrixSubRowCol(const DOUBLE* inMatrixData,
                                                 const UINT32 inRow,
                                                 const UINT32 inCol,
                                                 DOUBLE* outMatrixData,
                                                 UINT32& outRow,
                                                 UINT32& outCol)
        {
            CGNSSMatrix mat1(matrix);
            CGNSSMatrix mat2(matrix.row + row, matrix.col + col);
            mat2 = mat1.MatrixAdd(row);
            for (int i = 0; i < outPutMatrix.row; i++)
            {
                for (int j = 0; j < outPutMatrix.col; j++)
                {
                    outPutMatrix.matrixNum[i][j] = mat2.GetMatrix().matrixNum[i][j];
                }
            }
            return 0;
        }
    } // namespace GNSSMathUtilityLib
} // namespace sixents