#define DLL_EXPORT
#include "GNSSMathInterface.h"
#include "../AppIFs/GULMathAppIFs.h"

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        extern "C" DLL_API int STD_CALL MatrixAdd(const double* leftMatrixData,
                                                  const int leftRow,
                                                  const int leftCol,
                                                  const double* rightMatrixData,
                                                  const int rightRow,
                                                  const int rightCol,
                                                  double* outMatrixData,
                                                  int& outRow,
                                                  int& outCol)
        {
            return CMathAppInterface::MatrixAdd(
                leftMatrixData, leftRow, leftCol, rightMatrixData, rightRow, rightCol, outMatrixData, outRow, outCol);
        }

        extern "C" DLL_API int STD_CALL MatrixSub(const double* leftMatrixData,
                                                  const int leftRow,
                                                  const int leftCol,
                                                  const double* rightMatrixData,
                                                  const int rightRow,
                                                  const int rightCol,
                                                  double* outMatrixData,
                                                  int& outRow,
                                                  int& outCol)
        {
            return CMathAppInterface::MatrixSub(
                leftMatrixData, leftRow, leftCol, rightMatrixData, rightRow, rightCol, outMatrixData, outRow, outCol);
        }

        extern "C" DLL_API int STD_CALL MatrixMul(const double* leftMatrixData,
                                                  const int leftRow,
                                                  const int leftCol,
                                                  const double* rightMatrixData,
                                                  const int rightRow,
                                                  const int rightCol,
                                                  double* outMatrixData,
                                                  int& outRow,
                                                  int& outCol)
        {
            return CMathAppInterface::MatrixMul(
                leftMatrixData, leftRow, leftCol, rightMatrixData, rightRow, rightCol, outMatrixData, outRow, outCol);
            ;
        }

        extern "C" DLL_API int STD_CALL MatrixTransposition(const double* inMatrixData,
                                                            const int inRow,
                                                            const int inCol,
                                                            double* outMatrixData,
                                                            int& outRow,
                                                            int& outCol)
        {
            return CMathAppInterface::MatrixTransposition(inMatrixData, inRow, inCol, outMatrixData, outRow, outCol);
        }

        extern "C" DLL_API int STD_CALL MatrixInverse(const double* inMatrixData,
                                                      const int inRow,
                                                      const int inCol,
                                                      double* outMatrixData,
                                                      int& outRow,
                                                      int& outCol)
        {
            return CMathAppInterface::MatrixInverse(inMatrixData, inRow, inCol, outMatrixData, outRow, outCol);
        }

        extern "C" DLL_API int STD_CALL MatrixAddRowCol(const double* inMatrixData,
                                                        const int inRow,
                                                        const int inCol,
                                                        double* outMatrixData,
                                                        int& outRow,
                                                        int& outCol)
        {
            return CMathAppInterface::MatrixAddRowCol(inMatrixData, inRow, inCol, outMatrixData, outRow, outCol);
        }

        extern "C" DLL_API int STD_CALL MatrixSubRowCol(const double* inMatrixData,
                                                        const int inRow,
                                                        const int inCol,
                                                        double* outMatrixData,
                                                        int& outRow,
                                                        int& outCol)
        {
            return CMathAppInterface::MatrixSubRowCol(inMatrixData, inRow, inCol, outMatrixData, outRow, outCol);
        }
    } // namespace GNSSMathUtilityLib
} // namespace sixents