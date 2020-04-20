
#include "TestFunc.h"
#include "ConstantDef.h"

// rtk lib
#include "RtkLib/rtklib.h"

// gul lib
#include "GULLib/GNSSUtilityInterface.h"
#include "GULLib/GNSSMathInterface.h"

//#include <ctime>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

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
        flag = "1";
        break;
    case 2: // GLONASS时间格式化
    case 6: // GLONASS时间转为UTC时间
    case 10: // UTC时间转为GLONASS时间
        flag = "2";
        break;
    case 3: // Galileo时间格式化
    case 7: // GALILEO时间转为UTC时间
    case 11: // UTC时间转为GALILEO时间
        flag = "3";
        break;
    case 4: // 北斗时间格式化
    case 8: // 北斗时间转为UTC时间
    case 12: // UTC时间转为北斗时间
        flag = "4";
        break;
    case 13: // 北斗时间转为GPS时间
        flag = "4,1";
        break;
    case 14: // GLONASS时间转为GPS时间
        flag = "2,1";
        break;
    case 15: // GALILEO时间转为GPS时间
        flag = "3,1";
        break;
    case 16: // GPS时间转为北斗时间
        flag = "1,4";
        break;
    case 17: // GPS时间转为GLONASS时间
        flag = "1,2";
        break;
    case 18: // GPS时间转为GALILEO时间
        flag = "1,3";
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
    mFuncs[23] = &CTestFunc::XYZ2BLH; // 大地坐标转换为空间直角坐标
    mFuncs[24] = &CTestFunc::BLH2XYZ; // 空间直角坐标转换为大地坐标
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
    if (weekSecData.count() != 3) {
        return false;
    }
    int week = weekSecData[0].toInt();
    double sec = weekSecData[1].toDouble();
    int satType = weekSecData[2].toInt();

    char* outStr = nullptr;
    int outStrLen = 0;
    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    QString gulRet("null");
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
    int flag = testDatas[1].toInt();
    QStringList weekSecData = testDatas[0].split(",");
    if (weekSecData.count() != 6) {
        return false;
    }
    int year = weekSecData[0].toInt();
    int month = weekSecData[1].toInt();
    int day = weekSecData[2].toInt();
    int hour = weekSecData[3].toInt();
    int minute = weekSecData[4].toInt();
    double sec = weekSecData[5].toDouble();

    char* outStr = nullptr;
    int outStrLen = 0;
    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    QString gulRet("null");
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

    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    double second = 0.0;
    // 执行Rtk接口，未实现该结果
    // 调用Rtk时间接口
    gtime_t rtkTime;
    switch (flag) {
    case 1:    // GPS时间
        rtkTime = gpst2time(week, sec);
        break;
    case 3:    // Galileo时间
        rtkTime = gst2time(week, sec);
        break;
    case 4:    // BD时间
        rtkTime = bdt2time(week, sec);
        break;
    default:
        break;
    }
    gtime_t rtkRetTime = gpst2utc(rtkTime);
    char* chRet = new char[50];
    memset(chRet, 0, sizeof (char)*50);
    int n = 3;
    time2str(rtkRetTime, chRet, n);
    if (chRet == nullptr) {
        return false;
    }
    QString rtkRet(chRet);
    // 执行GUL接口
    QString gulRet("null");
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
    int week = 0;
    double second = 0.0;
    // 执行Rtk接口，未实现该结果
    switch (flag) {
    case 1:    // GPS时间
        second = time2gpst(rtkTime, &week);
        break;
    case 3:    // Galileo时间
        second = time2gst(rtkTime, &week);
        break;
    case 4:    // BD时间
        second = time2bdt(rtkTime, &week);
        break;
    default:
        break;
    }

    QString rtkRet = QString::number(week) + "," + QString::number(second, 'f', 3);
    // 执行GUL接口
    QString gulRet("null");
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
    QStringList weekSecData = testData.split(",");
    if (weekSecData.count() != 4) {
        return false;
    }
    int srcWeek = weekSecData[0].toInt();
    double srcSec = weekSecData[1].toDouble();
    int srcSatType = weekSecData[2].toInt();
    int destSatType = weekSecData[3].toInt();

    int destWeek = 0;
    double destSec = 0.0;
    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    QString gulRet("null");
    // 组装结果
    result = rtkRet + ";" + gulRet;
    return true;
}

bool CTestFunc::GlonassToUTC(const QString testData, QString &result)
{
    return true;
}

bool CTestFunc::UTCToGlonass(const QString testData, QString &result)
{
    return true;
}

bool CTestFunc::GlonassToGPS(const QString testData, QString &result)
{
    return true;
}

bool CTestFunc::GPSToGlonass(const QString testData, QString &result)
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
    double seconde = timeList[2].toDouble();

    // 从文件中读取星历电文

    // 执行Rtk接口，未实现该结果
    // 调用Rtk接口，解码星历电文

    // 调用Rtk接口解算
    QString rtkRet("null");
    // 执行GUL接口
    // 调用RTCM接口，解码星历电文

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
    double seconde = timeList[2].toDouble();

    // 从文件中读取星历电文

    // 执行Rtk接口，未实现该结果
    // 调用Rtk接口，解码星历电文

    // 调用Rtk接口解算
    QString rtkRet("null");
    // 执行GUL接口
    // 调用RTCM接口，解码星历电文

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
    double seconde = timeList[2].toDouble();

    // 从文件中读取星历电文

    // 执行Rtk接口，未实现该结果
    // 调用Rtk接口，解码星历电文

    // 调用Rtk接口解算
    QString rtkRet("null");
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
    double seconde = timeList[2].toDouble();

    // 从文件中读取星历电文

    // 执行Rtk接口，未实现该结果
    // 调用Rtk接口，解码星历电文

    // 调用Rtk接口解算
    QString rtkRet("null");
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
    QString gulRet("null");
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
    QString gulRet("null");
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
    QString gulRet("null");
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
    QString gulRet("null");
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
    QString gulRet("null");
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
    QString gulRet("null");
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

    double* srcMatrixData = new double[srcRow * srcCol];
    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\nnull");
    // 执行GUL接口
    QString gulRet("GUL Result\n");
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

    double* srcMatrixData = new double[srcRow * srcCol];
    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\nnull");
    // 执行GUL接口
    QString gulRet("GUL Result");
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

    double* srcMatrixData = new double[srcRow * srcCol];
    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result");
    // 执行GUL接口
    QString gulRet("GUL Result");
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
    const int col = rowAndCol[1].toInt();

    double* data = new double[row * col];
    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\nnull");
    // 执行GUL接口
    QString gulRet("GUL Result");
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

    double* data = new double[row * col];
    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\n");
    // 执行GUL接口
    QString gulRet("GUL Result");
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

    double* data = new double[row * col];
    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\nnull");
    // 执行GUL接口
    QString gulRet("GUL Result");
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

    double* data = new double[row * col];
    // 执行Rtk接口，未实现该结果
    QString rtkRet("Rtk Result\nnull");
    // 执行GUL接口
    QString gulRet("GUL Result");
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


