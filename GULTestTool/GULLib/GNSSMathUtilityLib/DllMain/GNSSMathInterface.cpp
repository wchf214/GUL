#define DLL_EXPORT

#include "GNSSMathInterface.h"
#include "../AppIFs/MathAppInterface.h"

namespace sixents
{
    namespace Math
    {
        extern "C" DLL_API int STD_CALL MatrixAdd(const double* leftMatrixData,
                                                  const unsigned int leftRow,
                                                  const unsigned int leftCol,
                                                  const double* rightMatrixData,
                                                  const unsigned int rightRow,
                                                  const unsigned int rightCol,
                                                  const unsigned int outRow,
                                                  const unsigned int outCol,
                                                  double* outMatrixData)
        {
            return CMathAppInterface::MatrixAdd(
                leftMatrixData, leftRow, leftCol, rightMatrixData, rightRow, rightCol, outRow, outCol, outMatrixData);
        }
        extern "C" DLL_API int STD_CALL MatrixSub(const double* leftMatrixData,
                                                  const unsigned int leftRow,
                                                  const unsigned int leftCol,
                                                  const double* rightMatrixData,
                                                  const unsigned int rightRow,
                                                  const unsigned int rightCol,
                                                  const unsigned int outRow,
                                                  const unsigned int outCol,
                                                  double* outMatrixData)
        {
            return CMathAppInterface::MatrixSub(
                leftMatrixData, leftRow, leftCol, rightMatrixData, rightRow, rightCol, outRow, outCol, outMatrixData);
        }

        extern "C" DLL_API int STD_CALL MatrixMul(const double* leftMatrixData,
                                                  const unsigned int leftRow,
                                                  const unsigned int leftCol,
                                                  const double* rightMatrixData,
                                                  const unsigned int rightRow,
                                                  const unsigned int rightCol,
                                                  const unsigned int outRow,
                                                  const unsigned int outCol,
                                                  double* outMatrixData)
        {
            return CMathAppInterface::MatrixMul(
                leftMatrixData, leftRow, leftCol, rightMatrixData, rightRow, rightCol, outRow, outCol, outMatrixData);
        }

        extern "C" DLL_API int STD_CALL MatrixTransposition(const double* inMatrixData,
                                                            const unsigned int inRow,
                                                            const unsigned int inCol,
                                                            const unsigned int outRow,
                                                            const unsigned int outCol,
                                                            double* outMatrixData)
        {
            return CMathAppInterface::MatrixTransposition(inMatrixData, inRow, inCol, outRow, outCol, outMatrixData);
        }

        extern "C" DLL_API int STD_CALL MatrixInverse(const double* inMatrixData,
                                                      const unsigned int inRow,
                                                      const unsigned int inCol,
                                                      const unsigned int outRow,
                                                      const unsigned int outCol,
                                                      double* outMatrixData)
        {
            return CMathAppInterface::MatrixInverse(inMatrixData, inRow, inCol, outRow, outCol, outMatrixData);
        }

        extern "C" DLL_API int STD_CALL MatrixAddRowCol(const double* inMatrixData,
                                                        const unsigned int inRow,
                                                        const unsigned int inCol,
                                                        const unsigned int outRow,
                                                        const unsigned int outCol,
                                                        double* outMatrixData)
        {
            return CMathAppInterface::MatrixAddRowCol(inMatrixData, inRow, inCol, outRow, outCol, outMatrixData);
        }

        extern "C" DLL_API int STD_CALL MatrixSubRowCol(const double* inMatrixData,
                                                        const unsigned int inRow,
                                                        const unsigned int inCol,
                                                        const unsigned int outRow,
                                                        const unsigned int outCol,
                                                        double* outMatrixData)
        {
            return CMathAppInterface::MatrixSubRowCol(inMatrixData, inRow, inCol, outRow, outCol, outMatrixData);
        }
    } // namespace Math
} // namespace sixents