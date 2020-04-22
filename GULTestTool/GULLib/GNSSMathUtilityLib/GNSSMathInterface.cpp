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
            mat3 = mat1 + mat2;
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

        extern "C" DLL_API int STD_CALL MatrixMul(SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix)
        {
            CGNSSMatrix mat1(srcMatrix);
            CGNSSMatrix mat2(destMatrix);
            CGNSSMatrix mat3;
            mat3 = mat1 * mat2;
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixTransposition(SGNSSMatrix& matrix)
        {
            CGNSSMatrix mat1(matrix);
            mat1.MatrixTransposition(matrix);
            return 0;
        }

        extern "C" DLL_API int STD_CALL MatrixInverse(SGNSSMatrix& matrix)
        {
            CGNSSMatrix mat1(matrix);
            mat1.MatrixInverse(matrix);
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
