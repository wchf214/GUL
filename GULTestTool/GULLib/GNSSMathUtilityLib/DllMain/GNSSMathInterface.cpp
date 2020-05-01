#define DLL_EXPORT

#include "GNSSMathInterface.h"
#include "../AppIFs/MathAppInterface.h"

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        extern "C" DLL_API int STD_CALL MatrixAdd(const double* leftMatrixData,
                                                  const unsigned int leftRow,
                                                  const unsigned int leftCol,
                                                  const double* rightMatrixData,
                                                  const unsigned int rightRow,
                                                  const unsigned int rightCol,
                                                  double* outMatrixData,
                                                  unsigned int& outRow,
                                                  unsigned int& outCol)
        {
            return CMathAppInterface::MatrixAdd(leftMatrixData, leftRow, leftCol,
                                                rightMatrixData,rightRow, rightCol,
                                                outMatrixData, outRow, outCol);
        }
        extern "C" DLL_API int STD_CALL MatrixSub(const double* leftMatrixData,
                                                  const unsigned int leftRow,
                                                  const unsigned int leftCol,
                                                  const double* rightMatrixData,
                                                  const unsigned int rightRow,
                                                  const unsigned int rightCol,
                                                  double* outMatrixData,
                                                  unsigned int& outRow,
                                                  unsigned int& outCol)
        {
            return CMathAppInterface::MatrixSub(leftMatrixData, leftRow, leftCol,
                                                rightMatrixData, rightRow, rightCol,
                                                outMatrixData, outRow, outCol);
        }

        extern "C" DLL_API int STD_CALL MatrixMul(const double* leftMatrixData,
                                                  const unsigned int leftRow,
                                                  const unsigned int leftCol,
                                                  const double* rightMatrixData,
                                                  const unsigned int rightRow,
                                                  const unsigned int rightCol,
                                                  double* outMatrixData,
                                                  unsigned int& outRow,
                                                  unsigned int& outCol)
        {
            return CMathAppInterface::MatrixMul(leftMatrixData, leftRow, leftCol,
                                                rightMatrixData, rightRow, rightCol,
                                                outMatrixData, outRow, outCol);
        }

        extern "C" DLL_API int STD_CALL MatrixTransposition(const double* inMatrixData,
                                                            const unsigned int inRow,
                                                            const unsigned int inCol,
                                                            double* outMatrixData,
                                                            unsigned int& outRow,
                                                            unsigned int& outCol)
        {
            return CMathAppInterface::MatrixTransposition(inMatrixData, inRow, inCol,
                                                          outMatrixData, outRow, outCol);
        }

        extern "C" DLL_API int STD_CALL MatrixInverse(const double* inMatrixData,
                                                      const unsigned int inRow,
                                                      const unsigned int inCol,
                                                      double* outMatrixData,
                                                      unsigned int& outRow,
                                                      unsigned int& outCol)
        {
            return CMathAppInterface::MatrixInverse(inMatrixData, inRow, inCol,
                                                    outMatrixData, outRow, outCol);
        }

        extern "C" DLL_API int STD_CALL MatrixAddRowCol(const double* inMatrixData,
                                                        const unsigned int inRow,
                                                        const unsigned int inCol,
                                                        double* outMatrixData,
                                                        unsigned int& outRow,
                                                        unsigned int& outCol)
        {
            return CMathAppInterface::MatrixAddRowCol(inMatrixData, inRow, inCol,
                                                      outMatrixData, outRow, outCol);
        }

        extern "C" DLL_API int STD_CALL MatrixSubRowCol(const double* inMatrixData,
                                                        const unsigned int inRow,
                                                        const unsigned int inCol,
                                                        double* outMatrixData,
                                                        unsigned int& outRow,
                                                        unsigned int& outCol)
        {
            return CMathAppInterface::MatrixSubRowCol(inMatrixData, inRow, inCol,
                                                      outMatrixData, outRow, outCol);
        }
    } // namespace GNSSMathUtilityLib
} // namespace sixents