#include "GULMathAppIFs.h"
//#include "../GNSSMatrix/CGNSSMatrix.h"

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
                if (leftMatrixData == nullptr || rightMatrixData == nullptr
                    || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }
                if (leftRow == 0 || leftCol == 0 ||
                    rightRow == 0 || rightCol == 0 ||
                    outRow == 0 || outCol == 0) {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

//                CGNSSMatrix leftMatrix;
//                CGNSSMatrix rightMatrix;
//                CGNSSMatrix outMatrix;
//                leftMatrix.setMatrix(leftMatrixData, leftRow, leftCol);
//                rightMatrix.setMatrix(rightMatrixData, rightRow, rightCol);
//                outMatrix.setMatrix(outMatrixData, outRow, outCol);
//                outMatrix = leftMatrix + rightMatrix;
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
                if (leftMatrixData == nullptr || rightMatrixData == nullptr
                    || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }
                if (leftRow == 0 || leftCol == 0 ||
                    rightRow == 0 || rightCol == 0 ||
                    outRow == 0 || outCol == 0) {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

//                CGNSSMatrix leftMatrix;
//                CGNSSMatrix rightMatrix;
//                CGNSSMatrix outMatrix;
//                leftMatrix.setMatrix(leftMatrixData, leftRow, leftCol);
//                rightMatrix.setMatrix(rightMatrixData, rightRow, rightCol);
//                outMatrix.setMatrix(outMatrixData, outRow, outCol);
//                outMatrix = leftMatrix + rightMatrix;
                ret = RETURN_SUCCESS;
            } while (false);

            return ret;
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
            INT32 ret = RETURN_FAIL;
            do
            {
                if (leftMatrixData == nullptr || rightMatrixData == nullptr
                    || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }
                if (leftRow == 0 || leftCol == 0 ||
                    rightRow == 0 || rightCol == 0 ||
                    outRow == 0 || outCol == 0) {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

//                CGNSSMatrix leftMatrix;
//                CGNSSMatrix rightMatrix;
//                CGNSSMatrix outMatrix;
//                leftMatrix.setMatrix(leftMatrixData, leftRow, leftCol);
//                rightMatrix.setMatrix(rightMatrixData, rightRow, rightCol);
//                outMatrix.setMatrix(outMatrixData, outRow, outCol);
//                outMatrix = leftMatrix + rightMatrix;
                ret = RETURN_SUCCESS;
            } while (false);

            return ret;
        }

        INT32 CMathAppInterface::MatrixTransposition(const DOUBLE* inMatrixData,
                                                     const UINT32 inRow,
                                                     const UINT32 inCol,
                                                     DOUBLE* outMatrixData,
                                                     UINT32& outRow,
                                                     UINT32& outCol)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if (inMatrixData == nullptr || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }
                if (inRow == 0 || inCol == 0 ||
                    outRow == 0 || outCol == 0) {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

//                CGNSSMatrix inMatrix;
//                CGNSSMatrix outMatrix;
//                inMatrix.setMatrix(inMatrixData, inRow, inCol);
//                outMatrix.setMatrix(outMatrixData, outRow, outCol);
//                inMatrix.MatrixTransposition(outMatrix);
                ret = RETURN_SUCCESS;
            } while (false);

            return ret;
        }

        INT32 CMathAppInterface::MatrixInverse(const DOUBLE* inMatrixData,
                                               const UINT32 inRow,
                                               const UINT32 inCol,
                                               DOUBLE* outMatrixData,
                                               UINT32& outRow,
                                               UINT32& outCol)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if (inMatrixData == nullptr || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }
                if (inRow == 0 || inCol == 0 ||
                    outRow == 0 || outCol == 0) {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

//                CGNSSMatrix inMatrix;
//                CGNSSMatrix outMatrix;
//                inMatrix.setMatrix(inMatrixData, inRow, inCol);
//                outMatrix.setMatrix(outMatrixData, outRow, outCol);
//                inMatrix.MatrixInverse(outMatrix);
                ret = RETURN_SUCCESS;
            } while (false);

            return ret;
        }

        INT32 CMathAppInterface::MatrixAddRowCol(const DOUBLE* inMatrixData,
                                                 const UINT32 inRow,
                                                 const UINT32 inCol,
                                                 DOUBLE* outMatrixData,
                                                 UINT32& outRow,
                                                 UINT32& outCol)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if (inMatrixData == nullptr || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }
                if (inRow == 0 || inCol == 0 ||
                    outRow == 0 || outCol == 0) {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

//                CGNSSMatrix inMatrix;
//                CGNSSMatrix outMatrix;
//                inMatrix.setMatrix(inMatrixData, inRow, inCol);
//                outMatrix.setMatrix(outMatrixData, outRow, outCol);
//                inMatrix.MatrixInverse(outMatrix);
                ret = RETURN_SUCCESS;
            } while (false);

            return ret;
        }

        INT32 CMathAppInterface::MatrixSubRowCol(const DOUBLE* inMatrixData,
                                                 const UINT32 inRow,
                                                 const UINT32 inCol,
                                                 DOUBLE* outMatrixData,
                                                 UINT32& outRow,
                                                 UINT32& outCol)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if (inMatrixData == nullptr || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }
                if (inRow == 0 || inCol == 0 ||
                    outRow == 0 || outCol == 0) {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

//                CGNSSMatrix inMatrix;
//                CGNSSMatrix outMatrix;
//                inMatrix.setMatrix(inMatrixData, inRow, inCol);
//                outMatrix.setMatrix(outMatrixData, outRow, outCol);
//                inMatrix.MatrixInverse(outMatrix);
                ret = RETURN_SUCCESS;
            } while (false);

            return ret;
        }
    } // namespace GNSSMathUtilityLib
} // namespace sixents