
#include "TestFunc.h"
// rtk lib
#include "RtkLib/rtklib.h"

// gul lib
#include "GULLib/GNSSUtilityInterface.h"
#include "GULLib/GNSSMathInterface.h"

#include <ctime>

namespace sixents {
    namespace GNSSUtilityLib {
        extern "C" {

        }
    } // end namespace GNSSUtilityLib

    namespace GNSSMathUtilityLib {
        extern "C" {
            DLL_API int STD_CALL MatrixAdd(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix);
            DLL_API int STD_CALL MatrixSub(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix);
            DLL_API int STD_CALL MatrixMul(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix);
            DLL_API int STD_CALL MatrixTransposition(SGNSSMatrix& matrix);
            DLL_API int STD_CALL MatrixInverse(SGNSSMatrix& matrix);
            DLL_API int STD_CALL MatrixAddRowCol(SGNSSMatrix& matrix, const int row, const int col);
            DLL_API int STD_CALL MatrixSubRowCol(SGNSSMatrix& matrix, const int row, const int col);
        }
    } // end namespace GNSSMathUtilityLib
} // end namespace sixents

// For RtkLib
extern "C" {
//#ifndef EXPORT
//#define EXPORT
// 时间
EXPORT gtime_t epoch2time(const double *ep);
EXPORT void    time2epoch(gtime_t t, double *ep);
EXPORT gtime_t gpst2time(int week, double sec);
EXPORT double  time2gpst(gtime_t t, int *week);
EXPORT gtime_t gst2time(int week, double sec);
EXPORT double  time2gst(gtime_t t, int *week);
EXPORT gtime_t bdt2time(int week, double sec);
EXPORT double  time2bdt(gtime_t t, int *week);
EXPORT gtime_t gpst2utc (gtime_t t);
EXPORT gtime_t utc2gpst (gtime_t t);
EXPORT gtime_t gpst2bdt (gtime_t t);
EXPORT gtime_t bdt2gpst (gtime_t t);

// 坐标
EXPORT void ecef2pos(const double *r, double *pos);
EXPORT void pos2ecef(const double *pos, double *r);
EXPORT void ecef2enu(const double *pos, const double *r, double *e);
EXPORT void enu2ecef(const double *pos, const double *e, double *r);
EXPORT void xyz2enu (const double *pos, double *E);

// 角度
// #define D2R         (PI/180.0)          /* deg to rad */
// #define R2D         (180.0/PI)          /* rad to deg */
EXPORT void deg2dms(double deg, double *dms, int ndec);
EXPORT double dms2deg(const double *dms);

// 星历
EXPORT double eph2clk (gtime_t time, const eph_t  *eph);
EXPORT double geph2clk(gtime_t time, const geph_t *geph);
EXPORT void eph2pos (gtime_t time, const eph_t  *eph,  double *rs, double *dts,
                     double *var);
EXPORT void geph2pos(gtime_t time, const geph_t *geph, double *rs, double *dts,
                     double *var);

// 矩阵
// 乘法
EXPORT void matmul(const char *tr, int n, int k, int m, double alpha,
                   const double *A, const double *B, double beta, double *C);
// 求逆
EXPORT int  matinv(double *A, int n);
// 打印矩阵到文件
//EXPORT void matfprint(const double *A, int n, int m, int p, int q, FILE *fp);

//#endif
}

// 常量定义
const static int COORDINATE_ACCURACY = 9;
const static int BLH_ACCURACY = 11;

CTestFunc::CTestFunc()
    : mLoadRtkLibFlag(false)
    , mLoadGULLibFlag(false)
    , mLoadGULMathLibFlag(false)
    , mRtkLibObj(nullptr)
    , mGULLibObj(nullptr)
    , mGULMathLibObj(nullptr)
{
    InitFuncMap();
}

CTestFunc::~CTestFunc()
{
    if (mRtkLibObj) {
        delete mRtkLibObj;
        mRtkLibObj = nullptr;
    }

    if (mGULLibObj) {
        delete mGULLibObj;
        mGULLibObj = nullptr;
    }

    if (mGULMathLibObj != nullptr) {
        delete mGULMathLibObj;
        mGULMathLibObj = nullptr;
    }
}

bool CTestFunc::LoadRtkLib()
{
    mLoadRtkLibFlag = false;
    QString libName("RTKLIB");
    if (mRtkLibObj) {
        delete mRtkLibObj;
        mRtkLibObj = nullptr;
    }

    do
    {
        mRtkLibObj = new QLibrary(libName);
        if (mRtkLibObj == nullptr) {
            break;
        }
        if (!mRtkLibObj->load()) {
            break;
        }
        mLoadRtkLibFlag = true;
    } while(false);

    return mLoadRtkLibFlag;
}

void CTestFunc::UnloadRtkLib()
{
    if (!mLoadRtkLibFlag && nullptr == mRtkLibObj) {
        return;
    }
    if (mRtkLibObj->unload()) {
        mLoadRtkLibFlag = false;
    }
}

bool CTestFunc::LoadGULLib()
{
    mLoadGULLibFlag = false;
    QString libName("GNSSUtilityLib");
    if (mGULLibObj) {
        delete mGULLibObj;
        mGULLibObj = nullptr;
    }

    do
    {
        mGULLibObj = new QLibrary(libName);
        if (mGULLibObj == nullptr) {
            break;
        }
        if (!mGULLibObj->load()) {
            break;
        }
        mLoadGULLibFlag = true;
    } while(false);

    return mLoadGULLibFlag;
}

void CTestFunc::UnloadGULLib()
{
    if (!mLoadGULLibFlag && nullptr == mGULLibObj) {
        return;
    }
    if (mGULLibObj->unload()) {
        mLoadGULLibFlag = false;
    }
}

bool CTestFunc::LoadGULMathLib()
{
    mLoadGULMathLibFlag = false;
    QString libName("GNSSMathLib");
    if (mGULMathLibObj != nullptr) {
        delete mGULMathLibObj;
        mGULMathLibObj = nullptr;
    }

    do
    {
        mGULMathLibObj = new QLibrary(libName);
        if (mGULMathLibObj == nullptr) {
            break;
        }
        if (!mGULMathLibObj->load()) {
            break;
        }
        mLoadGULMathLibFlag = true;
    } while(false);

    return mLoadGULMathLibFlag;
}

void CTestFunc::UnloadGULMathLib()
{
    if (!mLoadGULMathLibFlag && nullptr == mGULMathLibObj) {
        return;
    }
    if (mGULMathLibObj->unload()) {
        mLoadGULMathLibFlag = false;
    }
}

int CTestFunc::ExecuteTest(const QString testData, const int testFunc, QString &result)
{
    if (testFunc == 0) {
        return -1;
    }

    FuncList::iterator iter = mFuncs.find(testFunc);
    if (iter == mFuncs.end()) {
        return -1;
    }
    bool ret = iter->second(*this, testData, result);
    if (ret) {
        return 0;
    }
    return -1;
}


//int CTestFunc::ExecuteTest(const QString testData, const int testFunc, QString &result)
//{
//    LoadRtkLib();
//    if (testData.isEmpty()) {
//        return -1;
//    }
//    switch (testFunc) {
//    case 1:
//        FormatWeekSecTime(testData,result);
//        break;
//    case 2:
//        FormatStandardTime(testData, result);
//        break;
//    case 3:
//        GNSSTimeToUTCTime(testData,result);
//        break;
//    case 4:
//        UTCTimeToGNSSTime(testData,result);
//        break;
//    case 5:
//        GNSSTimeConvert(testData,result);
//        break;
//    case 6:
//        XYZ2BLH(testData,result);
//        break;
//    case 7:
//        BLH2XYZ(testData,result);
//        break;
//    case 8:
//        XYZ2ENU(testData,result);
//        break;
//    case 9:
//        ENU2XYZ(testData,result);
//        break;
//    case 10:
//        CalcGlonassEphSatClock(testData,result);
//        break;
//    case 11:
//        CalcEphSatClock(testData,result);
//        break;
//    case 12:
//        CalcGlonassEphSatPos(testData,result);
//        break;
//    case 13:
//        CalcEphSatPos(testData,result);
//        break;
//    case 14:
//        FormatAngleByDegree(testData,result);
//        break;
//    case 15:
//        FormatAngleByDMS(testData,result);
//        break;
//    case 16:
//        Deg2Rad(testData,result);
//        break;
//    case 17:
//        DMS2Rad(testData,result);
//        break;
//    case 18:
//        Rad2Deg(testData,result);
//        break;
//    case 19:
//        Rad2DMS(testData,result);
//        break;
//    case 20:
//        MatrixAdd(testData, result);
//        break;
//    case 21:
//        MatrixSub(testData, result);
//        break;
//    case 22:
//        MatrixMul(testData, result);
//        break;
//    case 23:
//        MatrixTransposition(testData, result);
//        break;
//    case 24:
//        MatrixInverse(testData, result);
//        break;
//    case 25:
//        MatrixAddRowCol(testData, result);
//        break;
//    case 26:
//        MatrixSubRowCol(testData, result);
//        break;
//    default:
//        break;
//    }
//    UnloadRtkLib();
//    return -1;
//}

void CTestFunc::InitFuncMap()
{
    mFuncs.clear();
    mFuncs[1] = &CTestFunc::FormatWeekSecTime;
    mFuncs[2] = &CTestFunc::FormatStandardTime;
    mFuncs[3] = &CTestFunc::GNSSTimeToUTCTime;
    mFuncs[4] = &CTestFunc::GNSSTimeToUTCSecTime;
    mFuncs[5] = &CTestFunc::UTCTimeToGNSSTime;
    mFuncs[6] = &CTestFunc::UTCTimeToGNSSSecTime;
    mFuncs[7] = &CTestFunc::GNSSTimeConvert;
    mFuncs[8] = &CTestFunc::WeekSecToSec;
    mFuncs[9] = &CTestFunc::XYZ2BLH;
    mFuncs[10] = &CTestFunc::BLH2XYZ;
    mFuncs[11] = &CTestFunc::XYZ2ENU;
    mFuncs[12] = &CTestFunc::ENU2XYZ;
    mFuncs[13] = &CTestFunc::CalcGlonassEphSatClock;
    mFuncs[14] = &CTestFunc::CalcEphSatClock;
    mFuncs[15] = &CTestFunc::CalcGlonassEphSatPos;
    mFuncs[16] = &CTestFunc::CalcEphSatPos;
    mFuncs[17] = &CTestFunc::FormatAngleByDegree;
    mFuncs[18] = &CTestFunc::FormatAngleByDMS;
    mFuncs[19] = &CTestFunc::Deg2Rad;
    mFuncs[20] = &CTestFunc::DMS2Rad;
    mFuncs[21] = &CTestFunc::Rad2Deg;
    mFuncs[22] = &CTestFunc::Rad2DMS;
    mFuncs[23] = &CTestFunc::MatrixAdd;
    mFuncs[24] = &CTestFunc::MatrixSub;
    mFuncs[25] = &CTestFunc::MatrixMul;
    mFuncs[26] = &CTestFunc::MatrixTransposition;
    mFuncs[27] = &CTestFunc::MatrixInverse;
    mFuncs[28] = &CTestFunc::MatrixAddRowCol;
    mFuncs[29] = &CTestFunc::MatrixSubRowCol;
}

bool CTestFunc::FormatWeekSecTime(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 拆分参数
    QStringList weekSecData = testData.split(",");
    if (weekSecData.count() != 3) {
        return false;
    }
    int week = weekSecData[0].toInt();
    double sec = weekSecData[1].toDouble();

    // 执行Rtk接口，未实现该结果

    // 执行GUL接口

    // 组装结果

    return true;
}

bool CTestFunc::FormatStandardTime(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::GNSSTimeToUTCTime(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData

    // 执行Rtk接口，未实现该结果

    // 执行GUL接口

    // 组装结果

    return true;
}

bool CTestFunc::GNSSTimeToUTCSecTime(const QString testData, QString &result)
{
    return true;
}

bool CTestFunc::UTCTimeToGNSSTime(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::UTCTimeToGNSSSecTime(const QString testData, QString &result)
{
    return true;
}

bool CTestFunc::GNSSTimeConvert(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::WeekSecToSec(const QString testData, QString &result)
{
    return true;
}

bool CTestFunc::XYZ2BLH(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData
    QStringList srcTestData = testData.split(",");
    if (srcTestData.count() != 3) {
        return false;
    }
    double xyz[3];
    double blh[3];
    memset(blh, 0, sizeof(blh));
    memset(xyz, 0, sizeof(blh));
    for (int idx = 0; idx < srcTestData.count(); ++idx) {
        xyz[idx] = srcTestData.at(idx).toDouble();
    }

    // 执行Rtk接口，未实现该结果
    ecef2pos(xyz, blh);
    QString rtkRet = QString::number(blh[0], 'f', BLH_ACCURACY) + "," +
                     QString::number(blh[1], 'f', BLH_ACCURACY) + "," +
                     QString::number(blh[2], 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    QString gulRet("null");
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::BLH2XYZ(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData
    QStringList srcTestData = testData.split(",");
    if (srcTestData.count() != 3) {
        return false;
    }
    double blh[3];
    double xyz[3];
    memset(blh, 0, sizeof(blh));
    memset(xyz, 0, sizeof(xyz));
    for (int idx = 0; idx < srcTestData.count(); ++idx) {
        blh[idx] = srcTestData.at(idx).toDouble();
    }

    // 执行Rtk接口，未实现该结果
    pos2ecef(blh, xyz);
    QString rtkRet = QString::number(xyz[0], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(xyz[1], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(xyz[2], 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    QString gulRet("null");
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::XYZ2ENU(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData
    QStringList srcTestData = testData.split(";");
    if (srcTestData.count() != 2) {

        return false;
    }
    QStringList srcXYZList = srcTestData[0].split(",");
    QStringList refXYZList = srcTestData[1].split(",");

    double srcXYZ[3];
    double refXYZ[3];
    double enu[3];
    memset(srcXYZ, 0, sizeof(srcXYZ));
    memset(refXYZ, 0, sizeof(refXYZ));
    memset(enu, 0, sizeof(enu));

    for (int idx = 0; idx < srcXYZList.count(); ++idx) {
        srcXYZ[idx] = srcXYZList.at(idx).toDouble();
    }

    for (int idx = 0; idx < refXYZList.count(); ++idx) {
        refXYZ[idx] = refXYZList.at(idx).toDouble();
    }

    // 执行Rtk接口，未实现该结果
    // 参考站的空间直角坐标转大地坐标
    double refBLH[3];
    memset(refBLH, 0, sizeof(refBLH));
    ecef2pos(refXYZ, refBLH);

    // 计算向量
    double r[3];
    memset(r, 0, sizeof (r));
    r[0] = srcXYZ[0] - refXYZ[0];
    r[1] = srcXYZ[1] - refXYZ[1];
    r[2] = srcXYZ[2] - refXYZ[2];
    // 计算ENU
    ecef2enu(refBLH, r, enu);

    QString rtkRet = QString::number(enu[0], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(enu[1], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(enu[2], 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    QString gulRet("null");
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::ENU2XYZ(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();

    // 解析testData
    QStringList srcTestData = testData.split(";");
    if (srcTestData.count() != 2) {

        return false;
    }
    QStringList srcENUList = srcTestData[0].split(",");
    QStringList refXYZList = srcTestData[1].split(",");

    double srcENU[3];
    double refXYZ[3];
    double refBLH[3];
    double srcXYZ[3];
    double r[3];
    memset(srcENU, 0, sizeof(srcENU));
    memset(refXYZ, 0, sizeof(refXYZ));
    memset(refBLH, 0, sizeof(refBLH));
    memset(srcXYZ, 0, sizeof(srcXYZ));
    memset(r, 0, sizeof (r));

    for (int idx = 0; idx < srcENUList.count(); ++idx) {
        srcENU[idx] = srcENUList.at(idx).toDouble();
    }

    for (int idx = 0; idx < refXYZList.count(); ++idx) {
        refXYZ[idx] = refXYZList.at(idx).toDouble();
    }

    // 执行Rtk接口，未实现该结果
    // 参考站的空间直角坐标转大地坐标
    ecef2pos(refXYZ, refBLH);
    // 计算向量
    enu2ecef(refBLH, srcENU, r);
    // 计算坐标
    srcXYZ[0] =  refXYZ[0] + r[0];
    srcXYZ[1] =  refXYZ[1] + r[1];
    srcXYZ[2] =  refXYZ[2] + r[2];

    QString rtkRet = QString::number(srcXYZ[0], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(srcXYZ[1], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(srcXYZ[2], 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    QString gulRet("null");
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::CalcGlonassEphSatClock(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::CalcEphSatClock(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::CalcGlonassEphSatPos(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::CalcEphSatPos(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::FormatAngleByDegree(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::FormatAngleByDMS(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::Deg2Rad(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::DMS2Rad(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::Rad2Deg(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::Rad2DMS(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::MatrixAdd(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::MatrixSub(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::MatrixMul(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::MatrixTransposition(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::MatrixInverse(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::MatrixAddRowCol(const QString testData, QString& result)
{
    return true;
}

bool CTestFunc::MatrixSubRowCol(const QString testData, QString& result)
{
    return true;
}


