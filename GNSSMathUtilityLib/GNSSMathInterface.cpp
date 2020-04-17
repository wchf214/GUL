#include "GNSSMathInterface.h"

#include "GNSSMatrix/CGNSSMatrix.h"

namespace sixents
{
    namespace GNSSMathUtilityLib
    {
        extern "C" DLL_API int STD_CALL MatrixAdd(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixSub(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixMul(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixTransposition(SGNSSMatrix& matrix)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixInverse(SGNSSMatrix& matrix)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixAddRowCol(SGNSSMatrix& matrix, const int row, const int col)
        {
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixSubRowCol(SGNSSMatrix& matrix, const int row, const int col)
        {
            return 0;
        }
    }
}