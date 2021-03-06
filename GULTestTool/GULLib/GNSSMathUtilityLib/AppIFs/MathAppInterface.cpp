﻿#include "MathAppInterface.h"
#include "../Eigen/Dense"

namespace sixents
{
    namespace Math
    {
        INT32 CMathAppInterface::MatrixAdd(const DOUBLE* leftMatrixData,
                                           const UINT32 leftRow,
                                           const UINT32 leftCol,
                                           const DOUBLE* rightMatrixData,
                                           const UINT32 rightRow,
                                           const UINT32 rightCol,
                                           const UINT32 outRow,
                                           const UINT32 outCol,
                                           DOUBLE* outMatrixData)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if (leftMatrixData == nullptr || rightMatrixData == nullptr || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }
                if ((leftRow == 0 || leftCol == 0) || (rightRow == 0 || rightCol == 0) || (outRow == 0 || outCol == 0)
                    || (leftRow != rightRow || leftCol != rightCol) || (outRow != leftRow || outCol != leftCol))
                {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

                for (UINT32 dataIdx = 0; dataIdx < leftRow * leftCol; ++dataIdx)
                {
                    outMatrixData[dataIdx] = leftMatrixData[dataIdx] + rightMatrixData[dataIdx];
                }
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
                                           const UINT32 outRow,
                                           const UINT32 outCol,
                                           DOUBLE* outMatrixData)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if (leftMatrixData == nullptr || rightMatrixData == nullptr || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }
                if ((leftRow == 0 || leftCol == 0) || (rightRow == 0 || rightCol == 0) || (outRow == 0 || outCol == 0)
                    || (leftRow != rightRow || leftCol != rightCol) || (outRow != leftRow || outCol != leftCol))
                {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

                for (UINT32 dataIdx = 0; dataIdx < leftRow * leftCol; ++dataIdx)
                {
                    outMatrixData[dataIdx] = leftMatrixData[dataIdx] - rightMatrixData[dataIdx];
                }
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
                                           const UINT32 outRow,
                                           const UINT32 outCol,
                                           DOUBLE* outMatrixData)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if (leftMatrixData == nullptr || rightMatrixData == nullptr || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }

                if (leftRow == 0 || leftCol == 0 || rightRow == 0 || rightCol == 0 || outRow == 0 || outCol == 0
                    || leftCol != rightRow || outRow != leftRow || outCol != rightCol)
                {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

                // 分配被乘数
                Eigen::Map<Eigen::Matrix<DOUBLE, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> leftMtx(
                    const_cast<DOUBLE*>(leftMatrixData), leftRow, leftCol);
                // 分配乘数
                Eigen::Map<Eigen::Matrix<DOUBLE, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> rightMtx(
                    const_cast<DOUBLE*>(rightMatrixData), rightRow, rightCol);
                // 分配结果
                Eigen::Map<Eigen::Matrix<DOUBLE, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> retMtx(
                    outMatrixData, outRow, outCol);
                retMtx = leftMtx * rightMtx;
                // 与Rtk算法时间一致
//                for (UINT32 rowIdx = 0; rowIdx < outRow; ++rowIdx)
//                {
//                    for (UINT32 colIdx = 0; colIdx < outCol; ++colIdx)
//                    {
//                        for (UINT32 addIdx = 0; addIdx < leftCol; ++addIdx)
//                        {
//                            outMatrixData[rowIdx * outCol + colIdx] += leftMatrixData[rowIdx * leftCol + addIdx] *
//                                                                       rightMatrixData[addIdx * rightCol + colIdx];
//                        }
//                    }
//                }
                ret = RETURN_SUCCESS;
            } while (false);

            return ret;
        }

        INT32 CMathAppInterface::MatrixTransposition(const DOUBLE* inMatrixData,
                                                     const UINT32 inRow,
                                                     const UINT32 inCol,
                                                     const UINT32 outRow,
                                                     const UINT32 outCol,
                                                     DOUBLE* outMatrixData)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if (inMatrixData == nullptr || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }

                if (inRow == 0 || inCol == 0 || outRow == 0 || outCol == 0 || inRow != outCol || inCol != outRow)
                {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

                for (UINT32 rowIdx = 0; rowIdx < outRow; ++rowIdx)
                {
                    for (UINT32 colIdx = 0; colIdx < outCol; ++colIdx)
                    {
                        outMatrixData[rowIdx * outCol + colIdx] = inMatrixData[colIdx * inCol + rowIdx];
                    }
                }
                ret = RETURN_SUCCESS;
            } while (false);

            return ret;
        }

        INT32 CMathAppInterface::MatrixInverse(const DOUBLE* inMatrixData,
                                               const UINT32 inRow,
                                               const UINT32 inCol,
                                               const UINT32 outRow,
                                               const UINT32 outCol,
                                               DOUBLE* outMatrixData)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if (inMatrixData == nullptr || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }

                if (inRow == 0 || inCol == 0 || outRow == 0 || outCol == 0 || inRow != outRow || inCol != outCol)
                {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

                if (inRow != inCol)
                {
                    ret = RETURN_NOT_SQUARE_MATRIX;
                    break;
                }

                Eigen::Map<Eigen::Matrix<DOUBLE, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> inMtx(
                    const_cast<DOUBLE*>(inMatrixData), inRow, inCol);

                //行列式不能为0=满秩矩阵
                if (inMtx.determinant() > DOUBLE_ZONE_LITTLE && inMtx.determinant() < DOUBLE_ZONE_BIG)
                {
                    ret = RETURN_ZERO_DETERMINANT;
                    break;
                }
                Eigen::Map<Eigen::Matrix<DOUBLE, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> outMtx(
                    outMatrixData, outRow, outCol);
                outMtx = inMtx.inverse();

                ret = RETURN_SUCCESS;
            } while (false);
            return ret;
        }

        INT32 CMathAppInterface::MatrixRowColChange(const DOUBLE* inMatrixData,
                                                    const UINT32 inRow,
                                                    const UINT32 inCol,
                                                    const UINT32 outRow,
                                                    const UINT32 outCol,
                                                    DOUBLE* outMatrixData)
        {
            INT32 ret = RETURN_FAIL;
            do
            {
                if (inMatrixData == nullptr || outMatrixData == nullptr)
                {
                    ret = RETURN_NULL_PTR;
                    break;
                }

                if (inRow == 0 || inCol == 0 || outRow == 0 || outCol == 0)
                {
                    ret = RETURN_ERROR_PARAMETER;
                    break;
                }

                // 根据需求，当前仅支持方阵
                if (inRow != inCol || outRow != outCol)
                {
                    ret = RETURN_NOT_SQUARE_MATRIX;
                    break;
                }

                for (UINT32 rowIdx = 0; rowIdx < outRow; ++rowIdx)
                {
                    for (UINT32 colIdx = 0; colIdx < outCol; ++colIdx)
                    {
                        outMatrixData[rowIdx * outCol + colIdx] = 0; // 超出输出矩阵的部分
                        if (colIdx < inCol && rowIdx < inRow)
                        {
                            outMatrixData[rowIdx * outCol + colIdx] = inMatrixData[rowIdx * inCol + colIdx];
                        }
                    }
                }
                ret = RETURN_SUCCESS;
            } while (false);
            return ret;
        }
    } // namespace Math
} // namespace sixents
