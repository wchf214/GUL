
#include "TestFunc.h"
#include "ConstantDef.h"

// rtk lib
#include "RtkLib/rtklib.h"

// gul lib
#include "GULLib/GNSSUtilityLibrary/DllMain/GNSSUtilityInterface.h"
#include "GULLib/GNSSMathUtilityLib/DllMain/GNSSMathInterface.h"
#include "GULLib/GNSSMathUtilityLib/DllMain/GNSSCommonStruct.h"
#include "GULLib/GNSSUtilityLibrary/DllMain/GNSSDataStruct.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDataStream>

#include <stdio.h>

namespace sixents {
    namespace Math {
        extern "C" {
            DLL_API int STD_CALL FormatWeekSecTime(const unsigned int week,
                                                  const double sec,
                                                  const unsigned int timeType,
                                                  char* formatString,
                                                  unsigned int& len);
            DLL_API int STD_CALL FormatStandardTime(const unsigned int year,
                                                   const unsigned int month,
                                                   const unsigned int day,
                                                   const unsigned int hour,
                                                   const unsigned int minute,
                                                   const double second,
                                                   char* formatString,
                                                   unsigned int& len);
            DLL_API int STD_CALL UTCTimeToGlonassTime(const unsigned int utcYear,
                                                     const unsigned int utcMonth,
                                                     const unsigned int utcDay,
                                                     const unsigned int utcHour,
                                                     const unsigned int utcMinute,
                                                     const double utcSecond,
                                                     unsigned int& gloYear,
                                                     unsigned int& gloMonth,
                                                     unsigned int& gloDay,
                                                     unsigned int& gloHour,
                                                     unsigned int& gloMinute,
                                                     double& gloSecond);
            DLL_API int STD_CALL GlonassTimeToUTCTime(const unsigned int gloYear,
                                                     const unsigned int gloMonth,
                                                     const unsigned int gloDay,
                                                     const unsigned int gloHour,
                                                     const unsigned int gloMinute,
                                                     const double gloSecond,
                                                     unsigned int& utcYear,
                                                     unsigned int& utcMonth,
                                                     unsigned int& utcDay,
                                                     unsigned int& utcHour,
                                                     unsigned int& utcMinute,
                                                     double& utcSecond);
            DLL_API int STD_CALL GNSSTimeToUTCTime(const unsigned int week,
                                                  const double sec,
                                                  const unsigned int timeType,
                                                  unsigned int& year,
                                                  unsigned int& month,
                                                  unsigned int& day,
                                                  unsigned int& hour,
                                                  unsigned int& minute,
                                                  double& second);
            DLL_API int STD_CALL GNSSTimeToUTCSecTime(const unsigned int week,
                                                     const double second,
                                                     const unsigned int timeType,
                                                     double& sec);
            DLL_API int STD_CALL UTCTimeToGNSSTime(const unsigned int year,
                                                  const unsigned int month,
                                                  const unsigned int day,
                                                  const unsigned int hour,
                                                  const unsigned int minute,
                                                  const double second,
                                                  const unsigned int timeType,
                                                  unsigned int& week,
                                                  double& sec);
            DLL_API int STD_CALL UTCTimeToGNSSSecTime(const unsigned int year,
                                                     const unsigned int month,
                                                     const unsigned int day,
                                                     const unsigned int hour,
                                                     const unsigned int minute,
                                                     const double second,
                                                     const unsigned int timeType,
                                                     double& sec);
            DLL_API int STD_CALL GNSSTimeConvert(const unsigned int srcWeek,
                                                const double srcSec,
                                                const unsigned int srcTimeType,
                                                unsigned int& destWeek,
                                                double& destSec,
                                                const unsigned int destTimeType);
            DLL_API int STD_CALL WeekSecToSec(const unsigned int week,
                                             const double second,
                                             const unsigned int timeType,
                                             double& sec);
            DLL_API int STD_CALL GPSTimeToGlonassTime(const unsigned int week,
                                                     const double second,
                                                     unsigned int& year,
                                                     unsigned int& month,
                                                     unsigned int& day,
                                                     unsigned int& hour,
                                                     unsigned int& minute,
                                                     double& sec);
            DLL_API int STD_CALL GlonassTimeToGPSTime(const unsigned int year,
                                                     const unsigned int month,
                                                     const unsigned int day,
                                                     const unsigned int hour,
                                                     const unsigned int minute,
                                                     const double second,
                                                     unsigned int& week,
                                                     double& sec);
            DLL_API int STD_CALL
            XYZ2BLH(const double x, const double y, const double z, double& lon, double& lat, double& height);
            DLL_API int STD_CALL
            BLH2XYZ(const double lon, const double lat, const double height, double& x, double& y, double& z);
            DLL_API int STD_CALL XYZ2ENU(const double curX,
                                        const double curY,
                                        const double curZ,
                                        const double refX,
                                        const double refY,
                                        const double refZ,
                                        double& east,
                                        double& north,
                                        double& up);
            DLL_API int STD_CALL ENU2XYZ(const double east,
                                        const double north,
                                        const double up,
                                        const double refX,
                                        const double refY,
                                        const double refZ,
                                        double& curX,
                                        double& curY,
                                        double& curZ);
            DLL_API int STD_CALL CalcGlonassEphSatClock(const double& sec,
                                                       const SGlonassEphemeris& ephObj,
                                                       double& clockVal);
            DLL_API int STD_CALL CalcEphSatClock(const double& sec, const SEphemeris& ephObj, double& clockVal);
            DLL_API int STD_CALL
            CalcGlonassEphSatPos(const double sec, const SGlonassEphemeris& ephObj, double& x, double& y, double& z);
            DLL_API int STD_CALL CalcEphSatPos(const double sec, const SEphemeris& ephObj,
                                              double& x, double& y, double& z);
            DLL_API int STD_CALL FormatAngleByDegree(const double degree,
                                                    char* formatString,
                                                    unsigned int& len,
                                                    const bool formatType);
            DLL_API int STD_CALL FormatAngleByDMS(const int degree,
                                                 const int minute,
                                                 const double sec,
                                                 char* formatString,
                                                 unsigned int& len,
                                                 const bool formatType);
            DLL_API int STD_CALL Deg2Rad(const double degree, double& radian);
            DLL_API int STD_CALL DMS2Rad(const int degree, const int minute, const double sec, double& radian);
            DLL_API int STD_CALL Rad2Deg(const double radian, double& degree);
            DLL_API int STD_CALL Rad2DMS(const double radian, int& degree, int& minute, double& sec);
            DLL_API int STD_CALL MatrixAdd(const double* leftMatrixData,
                                           const unsigned int leftRow,
                                           const unsigned int leftCol,
                                           const double* rightMatrixData,
                                           const unsigned int rightRow,
                                           const unsigned int rightCol,
                                           double* outMatrixData,
                                           unsigned int& outRow,
                                           unsigned int& outCol);
            DLL_API int STD_CALL MatrixSub(const double* leftMatrixData,
                                           const unsigned int leftRow,
                                           const unsigned int leftCol,
                                           const double* rightMatrixData,
                                           const unsigned int rightRow,
                                           const unsigned int rightCol,
                                           double* outMatrixData,
                                           unsigned int& outRow,
                                           unsigned int& outCol);
            DLL_API int STD_CALL MatrixMul(const double* leftMatrixData,
                                           const unsigned int leftRow,
                                           const unsigned int leftCol,
                                           const double* rightMatrixData,
                                           const unsigned int rightRow,
                                           const unsigned int rightCol,
                                           double* outMatrixData,
                                           unsigned int& outRow,
                                           unsigned int& outCol);
            DLL_API int STD_CALL MatrixTransposition(const double* inMatrixData,
                                                     const unsigned int inRow,
                                                     const unsigned int inCol,
                                                     double* outMatrixData,
                                                     unsigned int& outRow,
                                                     unsigned int& outCol);
            DLL_API int STD_CALL MatrixInverse(const double* inMatrixData,
                                               const unsigned int inRow,
                                               const unsigned int inCol,
                                               double* outMatrixData,
                                               unsigned int& outRow,
                                               unsigned int& outCol);
            DLL_API int STD_CALL MatrixAddRowCol(const double* inMatrixData,
                                                 const unsigned int inRow,
                                                 const unsigned int inCol,
                                                 double* outMatrixData,
                                                 unsigned int& outRow,
                                                 unsigned int& outCol);
            DLL_API int STD_CALL MatrixSubRowCol(const double* inMatrixData,
                                                 const unsigned int inRow,
                                                 const unsigned int inCol,
                                                 double* outMatrixData,
                                                 unsigned int& outRow,
                                                 unsigned int& outCol);
//            DLL_API int STD_CALL MatrixAdd(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix);
//            DLL_API int STD_CALL MatrixSub(const SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix);
//            DLL_API int STD_CALL MatrixMul(SGNSSMatrix& srcMatrix, SGNSSMatrix& destMatrix, SGNSSMatrix& outPutMatrix);
//            DLL_API int STD_CALL MatrixTransposition(SGNSSMatrix& matrix,SGNSSMatrix& outPutMatrix);
//            DLL_API int STD_CALL MatrixInverse(SGNSSMatrix& matrix);
//            DLL_API int STD_CALL MatrixAddRowCol(SGNSSMatrix& matrix, const int row, const int col,SGNSSMatrix& outPutMatrix);
//            DLL_API int STD_CALL MatrixSubRowCol(SGNSSMatrix& matrix, const int row, const int col,SGNSSMatrix& outPutMatrix);
        }
    } // end namespace Math
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
const static int COORDINATE_ACCURACY = 9;  // 空间直角坐标，以及大地坐标中高程的精确度
const static int BLH_ACCURACY = 11;        // 大地坐标中经纬度的精确度
const static int MSEC_ACCURACY = 3;        // 小数秒的精确度（精确到毫秒）
const static int MATRIX_ACCURACY = 6;      // 矩阵中double数据的精确度

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
    FuncList::iterator iter = mFuncs.find(testFunc);
    if (iter == mFuncs.end()) {
        return -1;
    }
    QString curTestData = static_cast<QString>(testData);
    if (testFunc >= 1 && testFunc <= 18) {
        ExecuteTestTime(curTestData, testFunc);
    }

    bool ret = iter->second(*this, curTestData, result);
    if (ret) {
        return 0;
    }
    return -1;
}

void CTestFunc::ExecuteTestTime(QString& testData, const int testFunc)
{
    QString flag;
    switch(testFunc) {
    case 1: // GPS时间格式化
    case 5: // GPS时间转为UTC时间
    case 9: // UTC时间转为GPS时间
        flag = "2";
        break;
    case 2: // GLONASS时间格式化
    case 6: // GLONASS时间转为UTC时间
    case 10: // UTC时间转为GLONASS时间
        flag = "3";
        break;
    case 3: // Galileo时间格式化
    case 7: // GALILEO时间转为UTC时间
    case 11: // UTC时间转为GALILEO时间
        flag = "4";
        break;
    case 4: // 北斗时间格式化
    case 8: // 北斗时间转为UTC时间
    case 12: // UTC时间转为北斗时间
        flag = "5";
        break;
    case 13: // 北斗时间转为GPS时间
        flag = "5,2";
        break;
    case 14: // GLONASS时间转为GPS时间
        flag = "3,2";
        break;
    case 15: // GALILEO时间转为GPS时间
        flag = "4,2";
        break;
    case 16: // GPS时间转为北斗时间
        flag = "2,5";
        break;
    case 17: // GPS时间转为GLONASS时间
        flag = "2,3";
        break;
    case 18: // GPS时间转为GALILEO时间
        flag = "2,4";
        break;
    default:
        break;
    }
    testData = testData + ";" + flag;
}

void CTestFunc::InitFuncMap()
{
    mFuncs.clear();
    mFuncs[1] = &CTestFunc::FormatWeekSecTime; // GPS时间格式化
    mFuncs[2] = &CTestFunc::FormatStandardTime; // GLONASS时间格式化
    mFuncs[3] = &CTestFunc::FormatWeekSecTime; // Galileo时间格式化
    mFuncs[4] = &CTestFunc::FormatWeekSecTime; // 北斗时间格式化
    mFuncs[5] = &CTestFunc::GNSSTimeToUTCTime; // GPS时间转为UTC时间
    mFuncs[6] = &CTestFunc::GlonassToUTC; // GLONASS时间转为UTC时间
    mFuncs[7] = &CTestFunc::GNSSTimeToUTCTime; // GALILEO时间转为UTC时间
    mFuncs[8] = &CTestFunc::GNSSTimeToUTCTime; // 北斗时间转为UTC时间
    mFuncs[9] = &CTestFunc::UTCTimeToGNSSTime; // UTC时间转为GPS时间
    mFuncs[10] = &CTestFunc::UTCToGlonass; // UTC时间转为GLONASS时间
    mFuncs[11] = &CTestFunc::UTCTimeToGNSSTime; // UTC时间转为GALILEO时间
    mFuncs[12] = &CTestFunc::UTCTimeToGNSSTime; // UTC时间转为北斗时间
    mFuncs[13] = &CTestFunc::GNSSTimeConvert; // 北斗时间转为GPS时间
    mFuncs[14] = &CTestFunc::GlonassToGPS; // GLONASS时间转为GPS时间
    mFuncs[15] = &CTestFunc::GNSSTimeConvert; // GALILEO时间转为GPS时间
    mFuncs[16] = &CTestFunc::GNSSTimeConvert; // GPS时间转为北斗时间
    mFuncs[17] = &CTestFunc::GPSToGlonass; // GPS时间转为GLONASS时间
    mFuncs[18] = &CTestFunc::GNSSTimeConvert; // GPS时间转为GALILEO时间
    mFuncs[19] = &CTestFunc::CalcGlonassEphSatClock; // 计算卫星钟差（GLONASS）  // 比需求文档多一个
    mFuncs[20] = &CTestFunc::CalcEphSatClock; // 计算卫星钟差（非GLONASS）
    mFuncs[21] = &CTestFunc::CalcEphSatPos; // 计算卫星位置（非GLONASS）
    mFuncs[22] = &CTestFunc::CalcGlonassEphSatPos; // 计算卫星位置（GLONASS）
    mFuncs[23] = &CTestFunc::BLH2XYZ; // 大地坐标转换为空间直角坐标
    mFuncs[24] = &CTestFunc::XYZ2BLH; // 空间直角坐标转换为大地坐标
    mFuncs[25] = &CTestFunc::XYZ2ENU; // 空间直角坐标转换为站心坐标
    mFuncs[26] = &CTestFunc::ENU2XYZ; // 站心坐标转换为空间直角坐标
    mFuncs[27] = &CTestFunc::Deg2Rad; // 度转换为弧度
    mFuncs[28] = &CTestFunc::Rad2Deg; // 弧度转换为度
    mFuncs[29] = &CTestFunc::FormatAngleByDegree; // 角度以度格式化输出
    mFuncs[30] = &CTestFunc::FormatAngleByDMS; // 角度以度分秒格式化输出
    mFuncs[31] = &CTestFunc::MatrixAdd; // 矩阵加法
    mFuncs[32] = &CTestFunc::MatrixSub; // 矩阵减法
    mFuncs[33] = &CTestFunc::MatrixMul; // 矩阵乘法
    mFuncs[34] = &CTestFunc::MatrixTransposition; // 矩阵转置
    mFuncs[35] = &CTestFunc::MatrixInverse; // 矩阵求逆
    mFuncs[36] = &CTestFunc::MatrixAddRowCol; // 矩阵增加行列
    mFuncs[37] = &CTestFunc::MatrixSubRowCol; // 矩阵减少行列
}

bool CTestFunc::FormatWeekSecTime(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 拆分参数
    QStringList testDatas = testData.split(";");
    int flag = testDatas[1].toInt();
    QStringList weekSecData = testDatas[0].split(",");
    if (weekSecData.count() != 2) {
        return false;
    }
    int week = weekSecData[0].toInt();
    double sec = weekSecData[1].toDouble();

    char* outStr = nullptr;
    unsigned int outStrLen = 0;
    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    sixents::GNSSUtilityLib::FormatWeekSecTime(static_cast<unsigned int>(week), sec, static_cast<unsigned int>(flag),
                                               outStr, outStrLen);
    if (outStrLen == 0) {
        return false;
    }
    outStr = new char[static_cast<unsigned long long>(outStrLen)];
    memset(outStr, 0, sizeof (char) * static_cast<unsigned long long>(outStrLen));
    sixents::GNSSUtilityLib::FormatWeekSecTime(static_cast<unsigned int>(week), sec, static_cast<unsigned int>(flag),
                                               outStr, outStrLen);
    QString gulRet = outStr;
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::FormatStandardTime(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 拆分参数
    QStringList testDatas = testData.split(";");
    QStringList weekSecData = testDatas[0].split(",");
    if (weekSecData.count() != 2) {
        return false;
    }

    QStringList dayTime = weekSecData[0].split("-");
    if (dayTime.count() != 3) {
        return false;
    }

    QStringList hourTime = weekSecData[1].split(":");
    if (hourTime.count() != 3) {
        return false;
    }

    int year = dayTime[0].toInt();
    int month = dayTime[1].toInt();
    int day = dayTime[2].toInt();
    int hour = hourTime[0].toInt();
    int minute = hourTime[1].toInt();
    double sec = hourTime[2].toDouble();

    char* outStr = nullptr;
    unsigned int outStrLen = 0;
    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    sixents::GNSSUtilityLib::FormatStandardTime(static_cast<unsigned int>(year), static_cast<unsigned int>(month),
                                                static_cast<unsigned int>(day), static_cast<unsigned int>(hour),
                                                static_cast<unsigned int>(minute), sec, outStr, outStrLen);
    if (outStrLen == 0) {
        return false;
    }
    outStr = new char[static_cast<unsigned long long>(outStrLen)];
    memset(outStr, 0, sizeof (char)* static_cast<unsigned long long>(outStrLen));
    sixents::GNSSUtilityLib::FormatStandardTime(static_cast<unsigned int>(year), static_cast<unsigned int>(month),
                                                static_cast<unsigned int>(day), static_cast<unsigned int>(hour),
                                                static_cast<unsigned int>(minute), sec, outStr, outStrLen);
    QString gulRet = outStr;
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::GNSSTimeToUTCTime(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 拆分参数
    QStringList testDatas = testData.split(";");
    int flag = testDatas[1].toInt();
    QStringList weekSecData = testDatas[0].split(",");
    if (weekSecData.count() != 2) {
        return false;
    }
    int week = weekSecData[0].toInt();
    double sec = weekSecData[1].toDouble();

    unsigned int year = 0;
    unsigned int month = 0;
    unsigned int day = 0;
    unsigned int hour = 0;
    unsigned int minute = 0;
    double second = 0.0;
    // 执行Rtk接口，未实现该结果
    // 调用Rtk时间接口
    gtime_t rtkTime;
    switch (flag) {
    case 2:    // GPS时间
        rtkTime = gpst2time(week, sec);
        break;
    case 4:    // Galileo时间
        rtkTime = gst2time(week, sec);
        break;
    case 5:    // BD时间
        rtkTime = bdt2time(week, sec);
        rtkTime = bdt2gpst(rtkTime);
        break;
    default:
        break;
    }
    gtime_t rtkRetTime = gpst2utc(rtkTime);
    char* chRet = new char[1000];
    memset(chRet, 0, sizeof (char)*1000);
    int n = MSEC_ACCURACY;
    time2str(rtkRetTime, chRet, n);
    if (chRet == nullptr) {
        return false;
    }
    QString rtkRet(chRet);
    // 执行GUL接口
    sixents::GNSSUtilityLib::GNSSTimeToUTCTime(static_cast<unsigned int>(week), sec, static_cast<unsigned int>(flag),
                                               year, month, day, hour, minute, second);
    QString gulRet = QString::number(year) + "-" + QString::number(month) + "-" + QString::number(day) + " "
            + QString::number(hour) + ":" + QString::number(minute) + ":" + QString::number(second, 'f', MSEC_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::UTCTimeToGNSSTime(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 拆分参数
    QStringList testDatas = testData.split(";");
    int flag = testDatas[1].toInt();
    QStringList weekSecData = testDatas[0].split(",");
    if (weekSecData.count() != 2) {
        return false;
    }

    QStringList dayTime = weekSecData[0].split("-");
    if (dayTime.count() != 3) {
        return false;
    }

    QStringList hourTime = weekSecData[1].split(":");
    if (hourTime.count() != 3) {
        return false;
    }

    int year = dayTime[0].toInt();
    int month = dayTime[1].toInt();
    int day = dayTime[2].toInt();
    int hour = hourTime[0].toInt();
    int minute = hourTime[1].toInt();
    double sec = hourTime[2].toDouble();

    double standTime[6] = {static_cast<double>(year), static_cast<double>(month), static_cast<double>(day),
                           static_cast<double>(hour), static_cast<double>(minute), sec};
    gtime_t rtkTime = epoch2time(standTime);
    gtime_t gpsTime = utc2gpst(rtkTime);
    int rtkWeek = 0;
    double rtkSecond = 0.0;
    // 执行Rtk接口，未实现该结果
    switch (flag) {
    case 2:    // GPS时间
    {
        rtkSecond = time2gpst(gpsTime, &rtkWeek);
        break;
    }
    case 4:    // Galileo时间
    {
        rtkSecond = time2gst(gpsTime, &rtkWeek);
        break;
    }
    case 5:    // BD时间
    {
        gtime_t bdTime = gpst2bdt(gpsTime);
        rtkSecond = time2bdt(bdTime, &rtkWeek);
        break;
    }
    default:
        break;
    }

    QString rtkRet = QString::number(rtkWeek) + "," + QString::number(rtkSecond, 'f', MSEC_ACCURACY);
    // 执行GUL接口
    unsigned int week = 0;
    double second = 0.0;
    sixents::GNSSUtilityLib::UTCTimeToGNSSTime(static_cast<UINT32>(year),
                                               static_cast<UINT32>(month),
                                               static_cast<UINT32>(day),
                                               static_cast<UINT32>(hour),
                                               static_cast<UINT32>(minute),
                                               sec, static_cast<UINT32>(flag), week, second);
    QString gulRet = QString::number(week) + "," + QString::number(second, 'f', MSEC_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::GNSSTimeConvert(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 拆分参数
    QStringList testDatas = testData.split(";");
    if (testDatas.count() != 2) {
        return false;
    }

    QStringList flagList = testDatas[1].split(",");
    if (flagList.count() != 2) {
        return false;
    }
    int srcType = flagList[0].toInt();
    int destType = flagList[1].toInt();

    QStringList weekSecData = testDatas[0].split(",");
    if (weekSecData.count() != 2) {
        return false;
    }
    int srcWeek = weekSecData[0].toInt();
    double srcSec = weekSecData[1].toDouble();

    int destRtkWeek = 0;
    double destRtkSec = 0.0;
    // 执行Rtk接口，未实现该结果
    if (srcType == 2) {  // GPS to BD or Galileo
        gtime_t gpsTime = gpst2time(srcWeek, srcSec);
        if (destType == 4) { // to Galileo
            destRtkSec = time2gst(gpsTime, &destRtkWeek);
        } else if (destType == 5){ // to BD
            gtime_t bdTime = gpst2bdt(gpsTime);
            destRtkSec = time2bdt(bdTime, &destRtkWeek);
        }
    } else if (destType == 2) { // BD or Galileo to GPS
        if (srcType == 4) {
            gtime_t gstTime = gst2time(srcWeek, srcSec);
            destRtkSec = time2gpst(gstTime, &destRtkWeek);
        } else if (srcType == 5) {
            gtime_t bdTime = bdt2time(srcWeek, srcSec);
            gtime_t gpsTime = bdt2gpst(bdTime);
            destRtkSec = time2gpst(gpsTime, &destRtkWeek);
        }
    }
    QString rtkRet = QString::number(destRtkWeek) + "," + QString::number(destRtkSec, 'f', MSEC_ACCURACY);

    // 执行GUL接口
    unsigned int destWeek = 0;
    double destSec = 0.0;
    sixents::GNSSUtilityLib::GNSSTimeConvert(static_cast<UINT32>(srcWeek), srcSec, static_cast<UINT32>(srcType),
                                             destWeek, destSec, static_cast<UINT32>(destType));
    QString gulRet = QString::number(destWeek) + "," + QString::number(destSec, 'f', MSEC_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::GlonassToUTC(const QString testData, QString &result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 拆分参数
    QStringList testDatas = testData.split(";");
    if (testDatas.count() != 2) {
        return false;
    }

    QStringList weekSecData = testDatas[0].split(",");
    if (weekSecData.count() != 2) {
        return false;
    }

    QStringList dayTime = weekSecData[0].split("-");
    if (dayTime.count() != 3) {
        return false;
    }

    QStringList hourTime = weekSecData[1].split(":");
    if (hourTime.count() != 3) {
        return false;
    }

    int year = dayTime[0].toInt();
    int month = dayTime[1].toInt();
    int day = dayTime[2].toInt();
    int hour = hourTime[0].toInt();
    int minute = hourTime[1].toInt();
    double sec = hourTime[2].toDouble();
    unsigned int utcYear = 0;
    unsigned int utcMonth = 0;
    unsigned int utcDay = 0;
    unsigned int utcHour = 0;
    unsigned int utcMinute = 0;
    double utcSec = 0.0;
    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    sixents::GNSSUtilityLib::GlonassTimeToUTCTime(static_cast<unsigned int>(year), static_cast<unsigned int>(month),
                                                  static_cast<unsigned int>(day), static_cast<unsigned int>(hour),
                                                  static_cast<unsigned int>(minute), sec,
                                                  utcYear, utcMonth, utcDay, utcHour, utcMinute, utcSec);
    QString gulRet = QString::number(utcYear) + "-" + QString::number(utcMonth) + "-" + QString::number(utcDay) + " " +
                     QString::number(utcHour) + ":" + QString::number(utcMinute) + ":" +
                     QString::number(utcSec, 'f', MSEC_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::UTCToGlonass(const QString testData, QString &result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 拆分参数
    QStringList testDatas = testData.split(";");
    if (testDatas.count() != 2) {
        return false;
    }

    QStringList weekSecData = testDatas[0].split(",");
    if (weekSecData.count() != 2) {
        return false;
    }

    QStringList dayTime = weekSecData[0].split("-");
    if (dayTime.count() != 3) {
        return false;
    }

    QStringList hourTime = weekSecData[1].split(":");
    if (hourTime.count() != 3) {
        return false;
    }

    int year = dayTime[0].toInt();
    int month = dayTime[1].toInt();
    int day = dayTime[2].toInt();
    int hour = hourTime[0].toInt();
    int minute = hourTime[1].toInt();
    double sec = hourTime[2].toDouble();
    unsigned int gloYear = 0;
    unsigned int gloMonth = 0;
    unsigned int gloDay = 0;
    unsigned int gloHour = 0;
    unsigned int gloMinute = 0;
    double gloSec = 0.0;
    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    sixents::GNSSUtilityLib::UTCTimeToGlonassTime(static_cast<unsigned int>(year), static_cast<unsigned int>(month),
                                                  static_cast<unsigned int>(day), static_cast<unsigned int>(hour),
                                                  static_cast<unsigned int>(minute), sec,
                                                  gloYear, gloMonth, gloDay, gloHour, gloMinute, gloSec);
    QString gulRet = QString::number(gloYear) + "-" + QString::number(gloMonth) + "-" + QString::number(gloDay) + " " +
                     QString::number(gloHour) + ":" + QString::number(gloMinute) + ":" + QString::number(gloSec, 'f', MSEC_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::GlonassToGPS(const QString testData, QString &result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 拆分参数
    QStringList testDatas = testData.split(";");
    if (testDatas.count() != 2) {
        return false;
    }

    QStringList weekSecData = testDatas[0].split(",");
    if (weekSecData.count() != 2) {
        return false;
    }

    QStringList dayTime = weekSecData[0].split("-");
    if (dayTime.count() != 3) {
        return false;
    }

    QStringList hourTime = weekSecData[1].split(":");
    if (hourTime.count() != 3) {
        return false;
    }

    int year = dayTime[0].toInt();
    int month = dayTime[1].toInt();
    int day = dayTime[2].toInt();
    int hour = hourTime[0].toInt();
    int minute = hourTime[1].toInt();
    double sec = hourTime[2].toDouble();

    unsigned int week = 0;
    double second = 0.0;
    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    sixents::GNSSUtilityLib::GlonassTimeToGPSTime(static_cast<unsigned int>(year), static_cast<unsigned int>(month),
                                                  static_cast<unsigned int>(day), static_cast<unsigned int>(hour),
                                                  static_cast<unsigned int>(minute), sec, week, second);
    QString gulRet = QString::number(week) + "," + QString::number(second, 'f', MSEC_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::GPSToGlonass(const QString testData, QString &result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 拆分参数
    QStringList testDatas = testData.split(";");
    if (testDatas.count() != 2) {
        return false;
    }

    QStringList weekSecData = testDatas[0].split(",");
    if (weekSecData.count() != 2) {
        return false;
    }
    int week = weekSecData[0].toInt();
    double second = weekSecData[1].toDouble();

    unsigned int year = 0;
    unsigned int month = 0;
    unsigned int day = 0;
    unsigned int hour = 0;
    unsigned int minute = 0;
    double sec = 0.0;
    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    sixents::GNSSUtilityLib::GPSTimeToGlonassTime(static_cast<unsigned int>(week), second,
                                                  year, month, day, hour, minute, sec);
    QString gulRet = QString::number(year) + "-" + QString::number(month) + "-" + QString::number(day) + " " +
                     QString::number(hour) + ":" + QString::number(minute) + ":" +
                     QString::number(sec, 'f', MSEC_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
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
    // blh值转角度
    double lat = blh[0] * R2D;
    double lon = blh[1] * R2D;
    QString rtkRet = QString::number(lat, 'f', BLH_ACCURACY) + "," +
                     QString::number(lon, 'f', BLH_ACCURACY) + "," +
                     QString::number(blh[2], 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    double b = 0;
    double l = 0;
    double h = 0;
    sixents::GNSSUtilityLib::XYZ2BLH(xyz[0], xyz[1], xyz[2], b, l, h);
    QString gulRet = QString::number(b, 'f', BLH_ACCURACY) + "," +
                     QString::number(l, 'f', BLH_ACCURACY) + "," +
                     QString::number(h, 'f', COORDINATE_ACCURACY);
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
    // blh进行角度转弧度
    double lat = blh[0] * D2R;
    double lon = blh[1] * D2R;
    double rtkBLH[3] = {lat, lon, blh[2]};
    pos2ecef(rtkBLH, xyz);
    QString rtkRet = QString::number(xyz[0], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(xyz[1], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(xyz[2], 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    double x = 0;
    double y = 0;
    double z = 0;
    sixents::GNSSUtilityLib::BLH2XYZ(blh[0], blh[1], blh[2], x, y, z);
    QString gulRet = QString::number(x, 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(y, 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(z, 'f', COORDINATE_ACCURACY);
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
    double e = 0;
    double n = 0;
    double u = 0;
    sixents::GNSSUtilityLib::XYZ2ENU(srcXYZ[0], srcXYZ[1], srcXYZ[2], refXYZ[0], refXYZ[1], refXYZ[2],
                                     e, n, u);
    QString gulRet = QString::number(e, 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(n, 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(u, 'f', COORDINATE_ACCURACY);
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
    double x = 0;
    double y = 0;
    double z = 0;
    sixents::GNSSUtilityLib::ENU2XYZ(srcENU[0], srcENU[1], srcENU[2], refXYZ[0], refXYZ[1], refXYZ[2],
                                     x, y, z);
    QString gulRet = QString::number(x, 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(y, 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(z, 'f', COORDINATE_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::CalcGlonassEphSatClock(const QString testData, QString& result)
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
    QString testDataFilePath = srcTestData[0];
    QStringList testTimeList = srcTestData[1].split(",");
    if (testTimeList.count() != 2) {
        return false;
    }

    QStringList dateList = testTimeList[0].split("-");
    if (dateList.count() != 3) {
        return false;
    }
    int year = dateList[0].toInt();
    int month = dateList[1].toInt();
    int day = dateList[2].toInt();

    QStringList timeList = testTimeList[1].split(":");
    if (timeList.count() != 3) {
        return false;
    }
    int hour = timeList[0].toInt();
    int minute = timeList[1].toInt();
    double second = timeList[2].toDouble();

    // 从文件中读取星历电文
    QString binFilePath("");
    FileConvertToBin(testDataFilePath, binFilePath);
    FILE *rtkFP = new FILE();
    std::string temp = binFilePath.toStdString();
    const char* fileName = temp.c_str();
    errno_t openFlag = fopen_s(&rtkFP, fileName, "rb+");
    if (openFlag != 0) {
        return false;
    }
    // 文本文件转二进制文件
    rtcm_t rtcm;
    init_rtcm(&rtcm);
    int ret = input_rtcm3f(&rtcm, rtkFP);
    if (ret < 0) {
        return false;
    }
    fclose(rtkFP);
    // 执行Rtk接口，未实现该结果
    // 调用Rtk接口解算
    gtime_t rtkClk;
    double epochTime[6] = {static_cast<double>(year), static_cast<double>(month), static_cast<double>(day),
                           static_cast<double>(hour), static_cast<double>(minute), second};
    gtime_t tTemp = epoch2time(epochTime);
    rtkClk = utc2gpst(tTemp);
    double rtkClkRet = geph2clk(rtkClk, rtcm.nav.geph);
    free_rtcm(&rtcm);
    QString rtkRet = QString::number(rtkClkRet, 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    // 调用RTCM接口，解码星历电文


    sixents::GNSSUtilityLib::SGlonassEphemeris glonassEphemeris;

    glonassEphemeris.m_dbGammaTb=2.72848e-12;
    glonassEphemeris.m_dbGmDeltaTn=0;
    glonassEphemeris.m_dbGmTGps=0;
    glonassEphemeris.m_dbTc=0;
    glonassEphemeris.m_dbTnTb=-0.0018718;
    glonassEphemeris.m_dbXnTb=-9490.91;
    glonassEphemeris.m_dbXnTbFirstDerivative=-7.3524;
    glonassEphemeris.m_dbXnTbSecondDerivative=9.31323e-10;
    glonassEphemeris.m_dbYnTb=8989.82;
    glonassEphemeris.m_dbYnTbFirstDerivative=0.35082;
    glonassEphemeris.m_dbYnTbSecondDerivative=0;
    glonassEphemeris.m_dbZnTb=-27565.3;
    glonassEphemeris.m_dbZnTbFirstDerivative=3.48408;
    glonassEphemeris.m_dbZnTbSecondDerivative=0;
    glonassEphemeris.m_ui16GmNt=1422;
    glonassEphemeris.m_ui16MsgType=1020;
    glonassEphemeris.m_ui16NA=0;
    glonassEphemeris.m_ui16Tb=375;
    glonassEphemeris.m_ui16Tk=768;
    glonassEphemeris.m_ui8AHAI=0;
    glonassEphemeris.m_ui8AOAD=0;
    glonassEphemeris.m_ui8AlmanacHealth=0;
    glonassEphemeris.m_ui8En=0;
    glonassEphemeris.m_ui8GmFt=0;
    glonassEphemeris.m_ui8GmLn3=0;
    glonassEphemeris.m_ui8GmLn5=0;
    glonassEphemeris.m_ui8GmM=0;
    glonassEphemeris.m_ui8GmN4=0;
    glonassEphemeris.m_ui8GmP=0;
    glonassEphemeris.m_ui8GmP4=0;
    glonassEphemeris.m_ui8MsbOfBn=0;
    glonassEphemeris.m_ui8P1=0;
    glonassEphemeris.m_ui8P2=0;
    glonassEphemeris.m_ui8P3=0;
    glonassEphemeris.m_ui8Reserved=0;
    glonassEphemeris.m_ui8SatFrequencyChannelNumber=6;
    glonassEphemeris.m_ui8SatId=12;

    // 调用GUL接口解算
    QString gulRet("null");
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::CalcEphSatClock(const QString testData, QString& result)
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
    QString testDataFilePath = srcTestData[0];
    QStringList testTimeList = srcTestData[1].split(",");
    if (testTimeList.count() != 2) {
        return false;
    }

    QStringList dateList = testTimeList[0].split("-");
    if (dateList.count() != 3) {
        return false;
    }
    int year = dateList[0].toInt();
    int month = dateList[1].toInt();
    int day = dateList[2].toInt();

    QStringList timeList = testTimeList[1].split(":");
    if (timeList.count() != 3) {
        return false;
    }
    int hour = timeList[0].toInt();
    int minute = timeList[1].toInt();
    double second = timeList[2].toDouble();

    // 从文件中读取星历电文
    QString binFilePath("");
    FileConvertToBin(testDataFilePath, binFilePath);
    FILE *rtkFP = new FILE();
    std::string temp = binFilePath.toStdString();
    const char* fileName = temp.c_str();
    errno_t openFlag = fopen_s(&rtkFP, fileName, "rb+");
    if (openFlag != 0) {
        return false;
    }
    // 文本文件转二进制文件
    rtcm_t rtcm;
    init_rtcm(&rtcm);
    int ret = input_rtcm3f(&rtcm, rtkFP);
    if (ret < 0) {
        return false;
    }
    fclose(rtkFP);
    // 执行Rtk接口，未实现该结果
    // 调用Rtk接口解算
    gtime_t rtkClk;
    double epochTime[6] = {static_cast<double>(year), static_cast<double>(month), static_cast<double>(day),
                           static_cast<double>(hour), static_cast<double>(minute), second};
    gtime_t timeTemp = epoch2time(epochTime);
    rtkClk = utc2gpst(timeTemp);
    double rtkClkRet = eph2clk(rtkClk, rtcm.nav.eph);
    free_rtcm(&rtcm);
    QString rtkRet = QString::number(rtkClkRet, 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    // 调用RTCM接口，解码星历电文

    sixents::GNSSUtilityLib::SEphemeris ephemeris;
    ephemeris.m_dbAHalf=5153.61;
    ephemeris.m_dbAf0=0.000167371;
    ephemeris.m_dbAf1=6.9349e-12;
    ephemeris.m_dbAf2=0;
    ephemeris.m_dbArgumentOfPerigee=-0.5372;
    ephemeris.m_dbBgdE1E5a=0;
    ephemeris.m_dbBgdE5bE1=0;
    ephemeris.m_dbCic=-2.27243e-07;
    ephemeris.m_dbCis=-2.47732e-07;
    ephemeris.m_dbCrc=187.5;
    ephemeris.m_dbCrs=-22.8125;
    ephemeris.m_dbCuc=-1.32993e-06;
    ephemeris.m_dbCus=1.08909e-05;
    ephemeris.m_dbDeltaN=1.21099e-09;
    ephemeris.m_dbEccentricity=0.0133868;
    ephemeris.m_dbI0=0.313307;
    ephemeris.m_dbIODot=0;
    ephemeris.m_dbIdot=-3.71756e-11;
    ephemeris.m_dbM0=0.408408;
    ephemeris.m_dbOmega0=-0.263181;
    ephemeris.m_dbOmegaDot=-2.49622e-09;
    ephemeris.m_dbTgd=-1.11759e-08;
    ephemeris.m_dbTgd1=0;
    ephemeris.m_dbTgd2=0;
    ephemeris.m_ui16IODnav=0;
    ephemeris.m_ui16Iodc=76;
    ephemeris.m_ui16MsgType=1019;
    ephemeris.m_ui16WeekNum=32;
    ephemeris.m_ui32Toc=446400;
    ephemeris.m_ui32Toe=446400;
    ephemeris.m_ui8AgeOfDataClock=0;
    ephemeris.m_ui8AgeOfDataEphemeris=0;
    ephemeris.m_ui8CodeOnL2=1;
    ephemeris.m_ui8E1bDataValidityStatus=0;
    ephemeris.m_ui8E1bSignalHealthStatus=0;
    ephemeris.m_ui8E5bDataValidityStatus=0;
    ephemeris.m_ui8E5bSignalHealthStatus=0;
    ephemeris.m_ui8FitInterval=0;
    ephemeris.m_ui8Iode=76;
    ephemeris.m_ui8L2PDataFlag=0;
    ephemeris.m_ui8OSDVS=0;
    ephemeris.m_ui8OSHS=0;
    ephemeris.m_ui8Reserved=0;
    ephemeris.m_ui8SISAIndex=0;
    ephemeris.m_ui8SatId=17;
    ephemeris.m_ui8SvHealth=0;
    ephemeris.m_ui8SvSisa=0;
    ephemeris.m_ui8URA=0;
    double clock=0;
    sixents::GNSSUtilityLib::CalcEphSatClock(1577836818,ephemeris,clock);

    // 调用GUL接口解算
    QString gulRet("null");
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::CalcGlonassEphSatPos(const QString testData, QString& result)
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
    QString testDataFilePath = srcTestData[0];
    QStringList testTimeList = srcTestData[1].split(",");
    if (testTimeList.count() != 2) {
        return false;
    }

    QStringList dateList = testTimeList[0].split("-");
    if (dateList.count() != 3) {
        return false;
    }
    int year = dateList[0].toInt();
    int month = dateList[1].toInt();
    int day = dateList[2].toInt();

    QStringList timeList = testTimeList[1].split(":");
    if (timeList.count() != 3) {
        return false;
    }
    int hour = timeList[0].toInt();
    int minute = timeList[1].toInt();
    double second = timeList[2].toDouble();

    // 从文件中读取星历电文
    QString binFilePath("");
    FileConvertToBin(testDataFilePath, binFilePath);
    FILE *rtkFP = new FILE();
    std::string temp = binFilePath.toStdString();
    const char* fileName = temp.c_str();
    errno_t openFlag = fopen_s(&rtkFP, fileName, "rb+");
    if (openFlag != 0) {
        return false;
    }
    // 文本文件转二进制文件
    rtcm_t rtcm;
    init_rtcm(&rtcm);
    int ret = input_rtcm3f(&rtcm, rtkFP);
    if (ret < 0) {
        return false;
    }
    fclose(rtkFP);
    // 执行Rtk接口，未实现该结果
    // 调用Rtk接口解算
    gtime_t rtkClk;
    double epochTime[6] = {static_cast<double>(year), static_cast<double>(month), static_cast<double>(day),
                           static_cast<double>(hour), static_cast<double>(minute), second};
    gtime_t timeTemp = epoch2time(epochTime);
    rtkClk = utc2gpst(timeTemp);
    double rtkClkRet = 0.0;
    double rtkPos[3] = {0.0, 0.0, 0.0};
    double rtkVar = 0.0;
    geph2pos(rtkClk, rtcm.nav.geph, rtkPos, &rtkClkRet, &rtkVar);
    free_rtcm(&rtcm);
    QString rtkRet = QString::number(rtkPos[0], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(rtkPos[1], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(rtkPos[2], 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    // 调用RTCM接口，解码星历电文

    // 调用GUL接口解算
    QString gulRet("null");
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::CalcEphSatPos(const QString testData, QString& result)
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
    QString testDataFilePath = srcTestData[0];
    QStringList testTimeList = srcTestData[1].split(",");
    if (testTimeList.count() != 2) {
        return false;
    }

    QStringList dateList = testTimeList[0].split("-");
    if (dateList.count() != 3) {
        return false;
    }
    int year = dateList[0].toInt();
    int month = dateList[1].toInt();
    int day = dateList[2].toInt();

    QStringList timeList = testTimeList[1].split(":");
    if (timeList.count() != 3) {
        return false;
    }
    int hour = timeList[0].toInt();
    int minute = timeList[1].toInt();
    double second = timeList[2].toDouble();

    // 从文件中读取星历电文
    QString binFilePath("");
    FileConvertToBin(testDataFilePath, binFilePath);
    FILE *rtkFP = new FILE();
    std::string temp = binFilePath.toStdString();
    const char* fileName = temp.c_str();
    errno_t openFlag = fopen_s(&rtkFP, fileName, "rb+");
    if (openFlag != 0) {
        return false;
    }
    // 文本文件转二进制文件
    rtcm_t rtcm;
    init_rtcm(&rtcm);
    int ret = input_rtcm3f(&rtcm, rtkFP);
    if (ret < 0) {
        return false;
    }
    fclose(rtkFP);
    // 执行Rtk接口，未实现该结果
    // 调用Rtk接口解算
    gtime_t rtkClk;
    double epochTime[6] = {static_cast<double>(year), static_cast<double>(month), static_cast<double>(day),
                           static_cast<double>(hour), static_cast<double>(minute), second};
    gtime_t timeTemp = epoch2time(epochTime);
    rtkClk = utc2gpst(timeTemp);
    double rtkClkRet = 0.0;
    double rtkPos[3] = {0.0, 0.0, 0.0};
    double rtkVar = 0.0;
    eph2pos(rtkClk, rtcm.nav.eph, rtkPos, &rtkClkRet, &rtkVar);
    free_rtcm(&rtcm);
    QString rtkRet = QString::number(rtkPos[0], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(rtkPos[1], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(rtkPos[2], 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    // 调用RTCM接口，解码星历电文

    // 调用GUL接口解算
    QString gulRet("null");
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::FormatAngleByDegree(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData
    double deg = testData.toDouble();

    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    char* gulChRet = nullptr;
    unsigned int len = 0;
    sixents::GNSSUtilityLib::FormatAngleByDegree(deg, gulChRet, len);

    gulChRet=new char[len + 1];
    sixents::GNSSUtilityLib::FormatAngleByDegree(deg, gulChRet, len);

    QString gulRet = gulChRet;
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::FormatAngleByDMS(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData
    QStringList dmsList = testData.split(",");
    if (dmsList.count() != 3) {
        return false;
    }
    int degree = dmsList[0].toInt();
    int minute = dmsList[1].toInt();
    double sec = dmsList[2].toDouble();

    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    char* gulChRet = nullptr;
    unsigned int len = 0;
    sixents::GNSSUtilityLib::FormatAngleByDMS(degree, minute, sec, gulChRet, len, false);

    gulChRet=new char[len + 1];
    sixents::GNSSUtilityLib::FormatAngleByDMS(degree, minute, sec, gulChRet, len, false);

    QString gulRet = gulChRet;
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::Deg2Rad(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData
    double deg = testData.toDouble();

    // 执行Rtk接口
    double rtkRad = deg * (D2R);
    QString rtkRet = QString::number(rtkRad, 'f', COORDINATE_ACCURACY);

    // 执行GUL接口
    double gulRad = 0.0;
    sixents::GNSSUtilityLib::Deg2Rad(deg, gulRad);
    QString gulRet = QString::number(gulRad, 'f', COORDINATE_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::DMS2Rad(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData
    QStringList dmsList = testData.split(",");
    if (dmsList.count() != 3) {
        return false;
    }
    int degree = dmsList[0].toInt();
    int minute = dmsList[1].toInt();
    double sec = dmsList[2].toDouble();

    // 执行Rtk接口
    double dmsArr[3] = {static_cast<double>(degree), static_cast<double>(minute), sec};
    double rtkDeg = dms2deg(dmsArr);
    double rtkRad = rtkDeg * (D2R);
    QString rtkRet = QString::number(rtkRad, 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    double gulRad = 0.0;
    sixents::GNSSUtilityLib::DMS2Rad(degree, minute, sec, gulRad);
    QString gulRet = QString::number(gulRad, 'f', COORDINATE_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::Rad2Deg(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData
    double rad = testData.toDouble();

    // 执行Rtk接口
    double rtkDeg = rad * (R2D);
    QString rtkRet = QString::number(rtkDeg, 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    double gulDeg = 0.0;
    sixents::GNSSUtilityLib::Rad2Deg(rad, gulDeg);
    QString gulRet = QString::number(gulDeg, 'f', COORDINATE_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::Rad2DMS(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData
    double rad = testData.toDouble();

    // 执行Rtk接口，未实现该结果
    double rtkDeg = rad * (R2D);
    double rtkDMSArr[3];
    memset(rtkDMSArr, 0, sizeof (double)*3);
    deg2dms(rtkDeg, rtkDMSArr, 3);
    QString rtkRet = QString::number(rtkDMSArr[0], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(rtkDMSArr[1], 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(rtkDMSArr[2], 'f', COORDINATE_ACCURACY);
    // 执行GUL接口
    int gulDegree = 0;
    int gulMinute = 0;
    double gulSec = 0.0;
    sixents::GNSSUtilityLib::Rad2DMS(rad, gulDegree, gulMinute, gulSec);
    QString gulRet = QString::number(gulDegree, 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(gulMinute, 'f', COORDINATE_ACCURACY) + "," +
                     QString::number(gulSec, 'f', COORDINATE_ACCURACY);
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::MatrixAdd(const QString testData, QString& result)
{
    if (testData.isEmpty()) {
        return false;
    }
    result.clear();
    // 解析testData
    QStringList srcTestData = testData.split(";");
    if (srcTestData.count()!= 2) {
        return false;
    }
    QString srcDataFilePath = srcTestData[0];
    QString destDataFilePath = srcTestData[1];
    if (srcDataFilePath.isEmpty() || destDataFilePath.isEmpty()) {
        return false;
    }

    QString twoMatrixData = ReadTxtFile(srcDataFilePath);
    QStringList allData = twoMatrixData.split(";");
    if (allData.count() != 2) {
        return false;
    }

    QStringList srcData = allData[0].split("\n");
    if (srcData.count() < 2) {
        return false;
    }
    QStringList srcRowAndCol = srcData[0].trimmed().split(",");
    if (srcRowAndCol.count() != 2) {
        return false;
    }
    int srcRow = srcRowAndCol[0].toInt();
    const int srcCol = srcRowAndCol[1].toInt();

    QStringList destData = allData[1].split("\n");
    if (destData.count() < 3) {
        return false;
    }
    if (destData[0].isEmpty()) {
        destData.removeAt(0);
    }
    QStringList destRowAndCol = destData[0].trimmed().split(",");
    if (destRowAndCol.count() != 2) {
        return false;
    }
    int destRow = destRowAndCol[0].toInt();
    const int destCol = destRowAndCol[1].toInt();

    double* srcMatrixData = new double[static_cast<unsigned long long>(srcRow * srcCol)];
    memset(srcMatrixData, 0, sizeof (double)* static_cast<unsigned long long>(srcRow * srcCol));
    int dataIdx = 0;
    for (int rowIdx = 0; rowIdx < srcRow; rowIdx++) {
        QStringList colDatas = srcData[rowIdx + 1].split(",");
        for (int colIdx = 0; colIdx < srcCol; colIdx++) {
            srcMatrixData[dataIdx] = colDatas[colIdx].toDouble();
            dataIdx++;
        }
    }

    double* destMatrixData = new double[static_cast<unsigned long long>(destRow * destCol)];
    memset(destMatrixData, 0, sizeof (double)* static_cast<unsigned long long>(destRow * destCol));
    dataIdx = 0;
    for (int rowIdx = 0; rowIdx < destRow; rowIdx++) {
        QStringList colDatas = destData[rowIdx + 1].split(",");
        for (int colIdx = 0; colIdx < destCol; colIdx++) {
            destMatrixData[dataIdx] = colDatas[colIdx].toDouble();
            dataIdx++;
        }
    }

    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\nnull\n");
    // 执行GUL接口
    QString gulRet("GUL Result\n");
    DOUBLE* leftMatrix = new DOUBLE[static_cast<unsigned long long>(srcRow*srcCol)];
    memset(leftMatrix, 0, static_cast<unsigned long long>(srcRow*srcCol));
    dataIdx = 1;
    int srcIdx = 0;
    for (int rowIdx = 0; rowIdx < srcRow; ++ rowIdx) {
        QStringList colData = srcData[dataIdx].split(",");
        for (int colIdx = 0; colIdx < srcCol; ++ colIdx) {
            leftMatrix[srcIdx] = colData[colIdx].toDouble();
            ++ srcIdx;
        }
        ++dataIdx;
    }

    DOUBLE* rightMatrix = new DOUBLE[static_cast<unsigned long long>(destRow*destCol)];
    memset(rightMatrix, 0, static_cast<unsigned long long>(destRow*destCol));
    dataIdx = 1;
    srcIdx = 0;
    for (int rowIdx = 0; rowIdx < destRow; ++ rowIdx) {
        QStringList colData = destData[dataIdx].split(",");
        for (int colIdx = 0; colIdx < destCol; ++ colIdx) {
            rightMatrix[srcIdx] = colData[colIdx].toDouble();
            ++ srcIdx;
        }
        ++dataIdx;
    }

    unsigned int outRow = static_cast<unsigned int>(srcRow);
    unsigned int outCol = static_cast<unsigned int>(destCol);
    DOUBLE* outMatrix = new DOUBLE[static_cast<unsigned long long>(outRow*outCol)];
    memset(outMatrix, 0, static_cast<unsigned long long>(outRow*outCol));

    sixents::GNSSMathUtilityLib::MatrixAdd(leftMatrix, static_cast<unsigned int>(srcRow), static_cast<unsigned int>(srcCol),
                                           rightMatrix, static_cast<unsigned int>(destRow), static_cast<unsigned int>(destCol),
                                           outMatrix, outRow, outCol);
    gulRet += QString::number(outRow) + "," + QString::number(outCol) + "\n";
    dataIdx = 0;
    for (UINT32 rIdx = 0; rIdx < outRow; ++rIdx) {
        for (UINT32 cIdx = 0; cIdx < outCol; ++cIdx) {
            gulRet += QString::number(outMatrix[dataIdx], 'f', MATRIX_ACCURACY);
            ++dataIdx;
            if (cIdx != static_cast<unsigned int>(outCol) - 1) {
                gulRet += ",";
            }
        }
        gulRet = gulRet + "\n";
    }

    // 写文件
    result = rtkRet + "\n" + gulRet;
    QDateTime curDateTime =QDateTime::currentDateTime();
    QString curDateTimeStr =curDateTime.toString("yyyyMMddhhmmss");
    QString destFileName = __func__ + curDateTimeStr + ".txt";
    WriteTxtFile(destDataFilePath + "/" + destFileName, result);
    return true;
}

bool CTestFunc::MatrixSub(const QString testData, QString& result)
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
    QString srcDataFilePath = srcTestData[0];
    QString destDataFilePath = srcTestData[1];
    if (srcDataFilePath.isEmpty() || destDataFilePath.isEmpty()) {
        return false;
    }

    QString twoMatrixData = ReadTxtFile(srcDataFilePath);
    QStringList allData = twoMatrixData.split(";");
    if (allData.count() != 2) {
        return false;
    }

    QStringList srcData = allData[0].split("\n");
    if (srcData.count() < 2) {
        return false;
    }
    QStringList srcRowAndCol = srcData[0].trimmed().split(",");
    if (srcRowAndCol.count() != 2) {
        return false;
    }
    int srcRow = srcRowAndCol[0].toInt();
    const int srcCol = srcRowAndCol[1].toInt();

    QStringList destData = allData[1].split("\n");
    if (destData.count() < 3) {
        return false;
    }
    if (destData[0].isEmpty()) {
        destData.removeAt(0);
    }
    QStringList destRowAndCol = destData[0].trimmed().split(",");
    if (destRowAndCol.count() != 2) {
        return false;
    }
    int destRow = destRowAndCol[0].toInt();
    const int destCol = destRowAndCol[1].toInt();

    double* srcMatrixData = new double[static_cast<unsigned long long>(srcRow * srcCol)];
    memset(srcMatrixData, 0, sizeof (double)* static_cast<unsigned long long>(srcRow * srcCol));
    int dataIdx = 0;
    for (int rowIdx = 0; rowIdx < srcRow; ++rowIdx) {
        QStringList colDatas = srcData[rowIdx + 1].split(",");
        for (int colIdx = 0; colIdx < srcCol; ++colIdx) {
            srcMatrixData[dataIdx] = colDatas[colIdx].toDouble();
            dataIdx++;
        }
    }

    double* destMatrixData = new double[static_cast<unsigned long long>(destRow * destCol)];
    memset(destMatrixData, 0, sizeof (double)* static_cast<unsigned long long>(destRow * destCol));
    dataIdx = 0;
    for (int rowIdx = 0; rowIdx < destRow; ++rowIdx) {
        QStringList colDatas = destData[rowIdx + 1].split(",");
        for (int colIdx = 0; colIdx < destCol; ++colIdx) {
            destMatrixData[dataIdx] = colDatas[colIdx].toDouble();
            dataIdx++;
        }
    }

    double* resultMatrixData = new double[static_cast<unsigned long long>(srcRow * destCol)];
    memset(resultMatrixData, 0, sizeof (double)* static_cast<unsigned long long>(srcRow * destCol));

    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\nnull\n");
    // 执行GUL接口
    QString gulRet("GUL Result\n");
    DOUBLE* leftMatrix = new DOUBLE[static_cast<unsigned long long>(srcRow*srcCol)];
    memset(leftMatrix, 0, static_cast<unsigned long long>(srcRow*srcCol));
    dataIdx = 1;
    int srcIdx = 0;
    for (int rowIdx = 0; rowIdx < srcRow; ++ rowIdx) {
        QStringList colData = srcData[dataIdx].split(",");
        for (int colIdx = 0; colIdx < srcCol; ++ colIdx) {
            leftMatrix[srcIdx] = colData[colIdx].toDouble();
            ++ srcIdx;
        }
        ++dataIdx;
    }

    DOUBLE* rightMatrix = new DOUBLE[static_cast<unsigned long long>(destRow*destCol)];
    memset(rightMatrix, 0, static_cast<unsigned long long>(destRow*destCol));
    dataIdx = 1;
    srcIdx = 0;
    for (int rowIdx = 0; rowIdx < destRow; ++ rowIdx) {
        QStringList colData = destData[dataIdx].split(",");
        for (int colIdx = 0; colIdx < destCol; ++ colIdx) {
            rightMatrix[srcIdx] = colData[colIdx].toDouble();
            ++ srcIdx;
        }
        ++dataIdx;
    }

    unsigned int outRow = static_cast<unsigned int>(srcRow);
    unsigned int outCol = static_cast<unsigned int>(destCol);
    DOUBLE* outMatrix = new DOUBLE[static_cast<unsigned long long>(outRow*outCol)];
    memset(outMatrix, 0, static_cast<unsigned long long>(outRow*outCol));

    sixents::GNSSMathUtilityLib::MatrixSub(leftMatrix, static_cast<unsigned int>(srcRow), static_cast<unsigned int>(srcCol),
                                           rightMatrix, static_cast<unsigned int>(destRow), static_cast<unsigned int>(destCol),
                                           outMatrix, outRow, outCol);
    gulRet += QString::number(outRow) + "," + QString::number(outCol) + "\n";
    dataIdx = 0;
    for (UINT32 rIdx = 0; rIdx < outRow; ++rIdx) {
        for (UINT32 cIdx = 0; cIdx < outCol; ++cIdx) {
            gulRet += QString::number(outMatrix[dataIdx], 'f', MATRIX_ACCURACY);
            ++dataIdx;
            if (cIdx != static_cast<unsigned int>(outCol) - 1) {
                gulRet += ",";
            }
        }
        gulRet = gulRet + "\n";
    }

    // 写文件
    result = rtkRet + "\n" + gulRet;
    QDateTime curDateTime =QDateTime::currentDateTime();
    QString curDateTimeStr =curDateTime.toString("yyyyMMddhhmmss");
    QString destFileName = __func__ + curDateTimeStr + ".txt";
    WriteTxtFile(destDataFilePath + "/" + destFileName, result);
    return true;
}

bool CTestFunc::MatrixMul(const QString testData, QString& result)
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
    QString srcDataFilePath = srcTestData[0];
    QString destDataFilePath = srcTestData[1];
    if (srcDataFilePath.isEmpty() || destDataFilePath.isEmpty()) {
        return false;
    }

    QString twoMatrixData = ReadTxtFile(srcDataFilePath);
    QStringList allData = twoMatrixData.split(";");
    if (allData.count() != 2) {
        return false;
    }

    QStringList srcData = allData[0].split("\n");
    if (srcData.count() < 2) {
        return false;
    }
    QStringList srcRowAndCol = srcData[0].trimmed().split(",");
    if (srcRowAndCol.count() != 2) {
        return false;
    }
    int srcRow = srcRowAndCol[0].toInt();
    int srcCol = srcRowAndCol[1].toInt();

    QStringList destData = allData[1].split("\n");
    if (destData.count() < 3) {
        return false;
    }
    if (destData[0].isEmpty()) {
        destData.removeAt(0);
    }
    QStringList destRowAndCol = destData[0].trimmed().split(",");
    if (destRowAndCol.count() != 2) {
        return false;
    }
    int destRow = destRowAndCol[0].toInt();
    int destCol = destRowAndCol[1].toInt();
    if (srcCol != destRow) {
        return false;
    }

    double* srcMatrixData = new double[static_cast<unsigned long long>(srcRow * srcCol)];
    memset(srcMatrixData, 0, sizeof (double)* static_cast<unsigned long long>(srcRow * srcCol));
    int dataIdx = 0;
    for (int rowIdx = 0; rowIdx < srcRow; ++rowIdx) {
        QStringList colDatas = srcData[rowIdx + 1].split(",");
        for (int colIdx = 0; colIdx < srcCol; ++colIdx) {
            srcMatrixData[rowIdx + colIdx * srcRow] = colDatas[colIdx].toDouble();
//            srcMatrixData[dataIdx++] = colDatas[colIdx].toDouble();
        }
    }

    double* destMatrixData = new double[static_cast<unsigned long long>(destRow * destCol)];
    memset(destMatrixData, 0, sizeof (double)* static_cast<unsigned long long>(destRow * destCol));
    dataIdx = 0;
    for (int rowIdx = 0; rowIdx < destRow; ++rowIdx) {
        QStringList colDatas = destData[rowIdx + 1].split(",");
        for (int colIdx = 0; colIdx < destCol; ++colIdx) {
            destMatrixData[rowIdx + colIdx * destRow] = colDatas[colIdx].toDouble();
//            destMatrixData[dataIdx++] = colDatas[colIdx].toDouble();
        }
    }

    double* resultMatrixData = new double[static_cast<unsigned long long>(srcRow * destCol)];
    memset(resultMatrixData, 0, sizeof (double)* static_cast<unsigned long long>(srcRow * destCol));

    double alpha = 1.0;
    double beta = 0.0;
    // 执行Rtk接口，未实现该结果
    matmul("NN", srcRow, destCol, srcCol, alpha, srcMatrixData, destMatrixData, beta, resultMatrixData);
    QString rtkRet("Rtk Result\n");
    rtkRet += QString::number(srcRow) + "," + QString::number(destCol) + "\n";
    dataIdx = 0;
    for (int rIdx = 0; rIdx < srcRow; rIdx ++) {
        for (int cIdx = 0; cIdx < destCol; cIdx++) {
            rtkRet += QString::number(resultMatrixData[rIdx + cIdx * srcRow], 'f', MATRIX_ACCURACY);
            if (cIdx != destCol - 1) {
                rtkRet += ",";
            }
            dataIdx ++;
        }
        rtkRet = rtkRet + "\n";
    }
    // 执行GUL接口
    QString gulRet("GUL Result\n");
    DOUBLE* leftMatrix = new DOUBLE[static_cast<unsigned long long>(srcRow*srcCol)];
    memset(leftMatrix, 0, static_cast<unsigned long long>(srcRow*srcCol));
    dataIdx = 1;
    int srcIdx = 0;
    for (int rowIdx = 0; rowIdx < srcRow; ++ rowIdx) {
        QStringList colData = srcData[dataIdx].split(",");
        for (int colIdx = 0; colIdx < srcCol; ++ colIdx) {
            leftMatrix[srcIdx] = colData[colIdx].toDouble();
            ++ srcIdx;
        }
        ++dataIdx;
    }

    DOUBLE* rightMatrix = new DOUBLE[static_cast<unsigned long long>(destRow*destCol)];
    memset(rightMatrix, 0, static_cast<unsigned long long>(destRow*destCol));
    dataIdx = 1;
    srcIdx = 0;
    for (int rowIdx = 0; rowIdx < destRow; ++ rowIdx) {
        QStringList colData = destData[dataIdx].split(",");
        for (int colIdx = 0; colIdx < destCol; ++ colIdx) {
            rightMatrix[srcIdx] = colData[colIdx].toDouble();
            ++ srcIdx;
        }
        ++dataIdx;
    }

    unsigned int outRow = static_cast<unsigned int>(srcRow);
    unsigned int outCol = static_cast<unsigned int>(destCol);
    DOUBLE* outMatrix = new DOUBLE[static_cast<unsigned long long>(outRow*outCol)];
    memset(outMatrix, 0, static_cast<unsigned long long>(outRow*outCol));

    sixents::GNSSMathUtilityLib::MatrixMul(leftMatrix, static_cast<unsigned int>(srcRow), static_cast<unsigned int>(srcCol),
                                           rightMatrix, static_cast<unsigned int>(destRow), static_cast<unsigned int>(destCol),
                                           outMatrix, outRow, outCol);
    gulRet += QString::number(outRow) + "," + QString::number(outCol) + "\n";
    dataIdx = 0;
    for (UINT32 rIdx = 0; rIdx < outRow; ++rIdx) {
        for (UINT32 cIdx = 0; cIdx < outCol; ++cIdx) {
            gulRet += QString::number(outMatrix[dataIdx], 'f', MATRIX_ACCURACY);
            ++dataIdx;
            if (cIdx != static_cast<unsigned int>(outCol) - 1) {
                gulRet += ",";
            }
        }
        gulRet = gulRet + "\n";
    }

    // 写文件
    result = rtkRet + "\n" + gulRet;
    QDateTime curDateTime =QDateTime::currentDateTime();
    QString curDateTimeStr =curDateTime.toString("yyyyMMddhhmmss");
    QString destFileName = __func__ + curDateTimeStr + ".txt";
    WriteTxtFile(destDataFilePath + "/" + destFileName, result);
    return true;
}

bool CTestFunc::MatrixTransposition(const QString testData, QString& result)
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
    QString srcDataFilePath = srcTestData[0];
    QString destDataFilePath = srcTestData[1];
    if (srcDataFilePath.isEmpty() || destDataFilePath.isEmpty()) {
        return false;
    }

    QString srcData = ReadTxtFile(srcDataFilePath);
    QStringList allData = srcData.split("\n");
    if (allData.count() < 2) {
        return false;
    }
    QStringList rowAndCol = allData[0].split(",");
    if (rowAndCol.count() != 2) {
        return false;
    }
    int row = rowAndCol[0].toInt();
    int col = rowAndCol[1].toInt();

    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\nnull\n");
    // 执行GUL接口
    QString gulRet("GUL Result\n");
    DOUBLE* srcMatrix = new DOUBLE[static_cast<unsigned long long>(row*col)];
    memset(srcMatrix, 0, static_cast<unsigned long long>(row*col));

    int dataIdx = 1;
    int srcIdx = 0;
    for (int rowIdx = 0; rowIdx < row; ++ rowIdx) {
        QStringList colData = allData[dataIdx].split(",");
        for (int colIdx = 0; colIdx < col; ++ colIdx) {
            srcMatrix[srcIdx] = colData[colIdx].toDouble();
            ++ srcIdx;
        }
        ++dataIdx;
    }

    unsigned int outRow = static_cast<unsigned int>(col);
    unsigned int outCol = static_cast<unsigned int>(row);
    DOUBLE* destMatrix = new DOUBLE[static_cast<unsigned long long>(outRow*outCol)];
    memset(destMatrix, 0, static_cast<unsigned long long>(outRow*outCol));

    sixents::GNSSMathUtilityLib::MatrixTransposition(srcMatrix, static_cast<unsigned int>(row), static_cast<unsigned int>(col),
                                                     destMatrix, outRow, outCol);
    gulRet += QString::number(outRow) + "," + QString::number(outCol) + "\n";
    dataIdx = 0;
    for (UINT32 rIdx = 0; rIdx < outRow; ++rIdx) {
        for (UINT32 cIdx = 0; cIdx < outCol; ++cIdx) {
            gulRet += QString::number(destMatrix[dataIdx], 'f', MATRIX_ACCURACY);
            ++dataIdx;
            if (cIdx != static_cast<unsigned int>(outCol) - 1) {
                gulRet += ",";
            }
        }
        gulRet = gulRet + "\n";
    }

    // 写文件
    result = rtkRet + "\n" + gulRet;
    QDateTime curDateTime =QDateTime::currentDateTime();
    QString curDateTimeStr =curDateTime.toString("yyyyMMddhhmmss");
    QString destFileName = __func__ + curDateTimeStr + ".txt";
    WriteTxtFile(destDataFilePath + "/" + destFileName, result);
    return true;
}

bool CTestFunc::MatrixInverse(const QString testData, QString& result)
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
    QString srcDataFilePath = srcTestData[0];
    QString destDataFilePath = srcTestData[1];
    if (srcDataFilePath.isEmpty() || destDataFilePath.isEmpty()) {
        return false;
    }

    QString srcData = ReadTxtFile(srcDataFilePath);
    QStringList allData = srcData.split("\n");
    if (allData.count() < 2) {
        return false;
    }
    QStringList rowAndCol = allData[0].split(",");
    if (rowAndCol.count() != 2) {
        return false;
    }
    int row = rowAndCol[0].toInt();
    const int col = rowAndCol[1].toInt();
    if (row != col) {
        return false;
    }

    double* data = new double[static_cast<unsigned long long>(row * col)];
    memset(data, 0, sizeof (double)* static_cast<unsigned long long>(row * col));
    int dataIdx = 0;
    for (int rowIdx = 0; rowIdx < row; rowIdx++) {
        QStringList colDatas = allData[rowIdx + 1].split(",");
        for (int colIdx = 0; colIdx < col; colIdx++) {
            //data[rowIdx + colIdx * row] = colDatas[colIdx].toDouble();
            data[dataIdx] = colDatas[colIdx].toDouble();
            dataIdx++;
        }
    }
    // 执行Rtk接口，未实现该结果
    matinv(data, row);
    QString rtkRet("Rtk Result\n");
    rtkRet += QString::number(row) + "," + QString::number(col) + "\n";
    dataIdx = 0;
    for (int rIdx = 0; rIdx < row; rIdx ++) {
        for (int cIdx = 0; cIdx < col; cIdx++) {
            rtkRet += QString::number(data[dataIdx], 'f', MATRIX_ACCURACY);
            if (cIdx != col - 1) {
                rtkRet += ",";
            }
            dataIdx ++;
        }
        rtkRet = rtkRet + "\n";
    }
    // 执行GUL接口
    QString gulRet("GUL Result\n");
    DOUBLE* srcMatrix = new DOUBLE[static_cast<unsigned long long>(row*col)];
    memset(srcMatrix, 0, static_cast<unsigned long long>(row*col));

    dataIdx = 1;
    int srcIdx = 0;
    for (int rowIdx = 0; rowIdx < row; ++ rowIdx) {
        QStringList colData = allData[dataIdx].split(",");
        for (int colIdx = 0; colIdx < col; ++ colIdx) {
            srcMatrix[srcIdx] = colData[colIdx].toDouble();
            ++ srcIdx;
        }
        ++dataIdx;
    }

    DOUBLE* destMatrix = new DOUBLE[static_cast<unsigned long long>(row*col)];
    memset(destMatrix, 0, static_cast<unsigned long long>(row*col));
    unsigned int outRow = static_cast<unsigned int>(row);
    unsigned int outCol = static_cast<unsigned int>(col);
    sixents::GNSSMathUtilityLib::MatrixInverse(srcMatrix, static_cast<unsigned int>(row), static_cast<unsigned int>(col),
                                               destMatrix, outRow, outCol);
    gulRet += QString::number(outRow) + "," + QString::number(outCol) + "\n";
    dataIdx = 0;
    for (UINT32 rIdx = 0; rIdx < outRow; ++rIdx) {
        for (UINT32 cIdx = 0; cIdx < outCol; ++cIdx) {
            gulRet += QString::number(destMatrix[dataIdx], 'f', MATRIX_ACCURACY);
            ++dataIdx;
            if (cIdx != outCol - 1) {
                gulRet += ",";
            }
        }
        gulRet = gulRet + "\n";
    }

    // 写文件
    result = rtkRet + "\n" + gulRet;
    QDateTime curDateTime =QDateTime::currentDateTime();
    QString curDateTimeStr =curDateTime.toString("yyyyMMddhhmmss");
    QString destFileName = __func__ + curDateTimeStr + ".txt";
    WriteTxtFile(destDataFilePath + "/" + destFileName, result);
    return true;
}

bool CTestFunc::MatrixAddRowCol(const QString testData, QString& result)
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
    QString srcDataFilePath = srcTestData[0];
    QString destDataFilePath = srcTestData[1];
    if (srcDataFilePath.isEmpty() || destDataFilePath.isEmpty()) {
        return false;
    }

    QString srcData = ReadTxtFile(srcDataFilePath);
    QStringList srcDataList = srcData.split(";");
    if (srcDataList.count() != 2) {
        return false;
    }

    QStringList newMatrixRowCol = srcDataList[1].split(",");
    if (newMatrixRowCol.count() != 2) {
        return false;
    }
    int addRow = newMatrixRowCol[0].toInt();
    int addCol = newMatrixRowCol[1].toInt();

    QStringList allData = srcDataList[0].split("\n");
    if (allData.count() < 2) {
        return false;
    }
    QStringList rowAndCol = allData[0].split(",");
    if (rowAndCol.count() != 2) {
        return false;
    }
    int row = rowAndCol[0].toInt();
    int col = rowAndCol[1].toInt();

    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\nnull\n");
    // 执行GUL接口
    QString gulRet("GUL Result\n");
    DOUBLE* srcMatrix = new DOUBLE[static_cast<unsigned long long>(row*col)];
    memset(srcMatrix, 0, static_cast<unsigned long long>(row*col));

    int dataIdx = 1;
    int srcIdx = 0;
    for (int rowIdx = 0; rowIdx < row; ++ rowIdx) {
        QStringList colData = allData[dataIdx].split(",");
        for (int colIdx = 0; colIdx < col; ++ colIdx) {
            srcMatrix[srcIdx] = colData[colIdx].toDouble();
            ++ srcIdx;
        }
        ++dataIdx;
    }

    unsigned int outRow = static_cast<unsigned int>(row + addRow);
    unsigned int outCol = static_cast<unsigned int>(col + addCol);
    DOUBLE* destMatrix = new DOUBLE[static_cast<unsigned long long>(outRow*outCol)];
    memset(destMatrix, 0, static_cast<unsigned long long>(outRow*outCol));

    sixents::GNSSMathUtilityLib::MatrixAddRowCol(srcMatrix, static_cast<unsigned int>(row), static_cast<unsigned int>(col),
                                                 destMatrix, outRow, outCol);
    gulRet += QString::number(outRow) + "," + QString::number(outCol) + "\n";
    dataIdx = 0;
    for (UINT32 rIdx = 0; rIdx < outRow; ++rIdx) {
        for (UINT32 cIdx = 0; cIdx < outCol; ++cIdx) {
            gulRet += QString::number(destMatrix[dataIdx], 'f', MATRIX_ACCURACY);
            ++dataIdx;
            if (cIdx != outCol - 1) {
                gulRet += ",";
            }
        }
        gulRet = gulRet + "\n";
    }

    // 写文件
    result = rtkRet + "\n" + gulRet;
    QDateTime curDateTime =QDateTime::currentDateTime();
    QString curDateTimeStr =curDateTime.toString("yyyyMMddhhmmss");
    QString destFileName = __func__ + curDateTimeStr + ".txt";
    WriteTxtFile(destDataFilePath + "/" + destFileName, result);
    return true;
}

bool CTestFunc::MatrixSubRowCol(const QString testData, QString& result)
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
    QString srcDataFilePath = srcTestData[0];
    QString destDataFilePath = srcTestData[1];
    if (srcDataFilePath.isEmpty() || destDataFilePath.isEmpty()) {
        return false;
    }

    QString srcData = ReadTxtFile(srcDataFilePath);
    QStringList srcDataList = srcData.split(";");
    if (srcDataList.count() != 2) {
        return false;
    }

    QStringList subRowCol = srcDataList[1].split(",");
    if (subRowCol.count() != 2) {
        return false;
    }
    int subRow = subRowCol[0].toInt();
    int subCol = subRowCol[1].toInt();

    QStringList allData = srcDataList[0].split("\n");
    if (allData.count() < 2) {
        return false;
    }
    QStringList rowAndCol = allData[0].split(",");
    if (rowAndCol.count() != 2) {
        return false;
    }
    int row = rowAndCol[0].toInt();
    int col = rowAndCol[1].toInt();

    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\nnull\n");
    // 执行GUL接口
    QString gulRet("GUL Result\n");
    DOUBLE* srcMatrix = new DOUBLE[static_cast<unsigned long long>(row*col)];
    memset(srcMatrix, 0, static_cast<unsigned long long>(row*col));

    int dataIdx = 1;
    int srcIdx = 0;
    for (int rowIdx = 0; rowIdx < row; ++ rowIdx) {
        QStringList colData = allData[dataIdx].split(",");
        for (int colIdx = 0; colIdx < col; ++ colIdx) {
            srcMatrix[srcIdx] = colData[colIdx].toDouble();
            ++ srcIdx;
        }
        ++dataIdx;
    }
    unsigned int outRow = static_cast<unsigned int>(row - subRow);
    unsigned int outCol = static_cast<unsigned int>(col - subCol);
    DOUBLE* destMatrix = new DOUBLE[static_cast<unsigned long long>(outRow*outCol)];
    memset(destMatrix, 0, static_cast<unsigned long long>(outRow*outCol));

    sixents::GNSSMathUtilityLib::MatrixSubRowCol(srcMatrix, static_cast<unsigned int>(row), static_cast<unsigned int>(col),
                                                 destMatrix, outRow, outCol);
    gulRet += QString::number(outRow) + "," + QString::number(outCol) + "\n";
    dataIdx = 0;
    for (UINT32 rIdx = 0; rIdx < outRow; ++rIdx) {
        for (UINT32 cIdx = 0; cIdx < outCol; ++cIdx) {
            gulRet += QString::number(destMatrix[dataIdx], 'f', MATRIX_ACCURACY);
            ++dataIdx;
            if (cIdx != outCol - 1) {
                gulRet += ",";
            }
        }
        gulRet = gulRet + "\n";
    }

    // 写文件
    result = rtkRet + "\n" + gulRet;
    QDateTime curDateTime =QDateTime::currentDateTime();
    QString curDateTimeStr =curDateTime.toString("yyyyMMddhhmmss");
    QString destFileName = __func__ + curDateTimeStr + ".txt";
    WriteTxtFile(destDataFilePath + "/" + destFileName, result);
    return true;
}

QString CTestFunc::ReadTxtFile(const QString &filePath)
{
    QString readData("");
    QFile fileObj(filePath);
    // 文件不存在或以只读方式打开文本失败，返回
    if (!fileObj.exists() || !fileObj.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return readData;
    }
    QTextStream fileDataObj(&fileObj);
    readData = fileDataObj.readAll();
    fileObj.close();
    return readData;
}

void CTestFunc::WriteTxtFile(const QString &filePath, const QString &data)
{
    QFile fileObj(filePath);
    // 文件以只写方式打开文本失败，返回
    if (!fileObj.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return ;
    }
    QTextStream fileDataObj(&fileObj);
    fileDataObj << data << endl;
    fileObj.flush();
    fileObj.close();
}

void CTestFunc::FileConvertToBin(const QString &filePath, QString &outFilePath)
{
    QString destFilePath(".dat");
    QStringList filePaths = filePath.split(".");
    outFilePath = filePaths[0] + destFilePath;
    QFile srcFileObj(filePath);
    QFile destFileObj(outFilePath);
    if (!srcFileObj.open(QIODevice::ReadOnly) || !destFileObj.open(QIODevice::WriteOnly)) {
        return;
    }
    QTextStream srcStream(&srcFileObj);
    QString srcData = srcStream.readAll();
    srcData.trimmed();
    QByteArray srcDataArr = QByteArray::fromHex(srcData.toLocal8Bit());
    QDataStream destStream(&destFileObj);
//    destStream.setByteOrder(QDataStream::BigEndian); // 设置大端在前
    destStream.setByteOrder(QDataStream::LittleEndian); // 设置小端在前
    destStream << srcDataArr;
    destFileObj.close();
    srcFileObj.close();
}


