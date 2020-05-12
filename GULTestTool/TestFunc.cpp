
#include "TestFunc.h"
#include "ConstantDef.h"
#include "mainwindow.h"

// rtk lib
#include "RtkLib/rtklib.h"

// gul lib
#include "GULLib/GNSSUtilityLibrary/DllMain/GNSSUtilityInterface.h"
#include "GULLib/GNSSUtilityLibrary/DllMain/GNSSDataStruct.h"
// gul math lib
#include "GULLib/GNSSMathUtilityLib/DllMain/GNSSMathInterface.h"
#include "GULLib/GNSSMathUtilityLib/DllMain/GNSSCommonStruct.h"
// rtcm lib
#include "RtcmLib/include/BasicType.h"
#include "RtcmLib/include/Constants.h"
#include "RtcmLib/include/CParam.h"
#include "RtcmLib/include/IGnssDataInterface.h"
#include "RtcmLib/include/IAppOpt.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDataStream>
#include <QDebug>

#include <stdio.h>

namespace sixents {
    extern "C" {  // For Rtcm
    DLL_API INT32 STD_CALL RtcmInit(CParam& pamIn, CParam& pamOut);
    DLL_API INT32 STD_CALL RtcmGetMessage(const BYTE* pbyBuf,
                                          const UINT32& uiLen,
                                          UINT32& uiMsgType,
                                          UINT32& uiMsgPos,
                                          UINT32& uiExpectLen);
    DLL_API INT32 STD_CALL RtcmDecode(CParam& pamIn, CParam& pamOut);
    DLL_API INT32 STD_CALL RtcmEncode(CParam& pamIn, CParam& pamOut);
    DLL_API INT32 STD_CALL RtcmCmd(CParam& pamIn, CParam& pamOut);
    DLL_API INT32 STD_CALL RtcmFinal();
    }
    namespace Math {  // For Gul
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
                                                  const unsigned int minute,
                                                  const double sec,
                                                  char* formatString,
                                                  unsigned int& len,
                                                  const bool formatType);
            DLL_API int STD_CALL Deg2Rad(const double degree, double& radian);
            DLL_API int STD_CALL DMS2Rad(const int degree, const unsigned int minute, const double sec, double& radian);
            DLL_API int STD_CALL Rad2Deg(const double radian, double& degree);
            DLL_API int STD_CALL Rad2DMS(const double radian, int& degree, unsigned int& minute, double& sec);
            DLL_API int STD_CALL MatrixAdd(const double* leftMatrixData,
                                           const unsigned int leftRow,
                                           const unsigned int leftCol,
                                           const double* rightMatrixData,
                                           const unsigned int rightRow,
                                           const unsigned int rightCol,
                                           const unsigned int outRow,
                                           const unsigned int outCol,
                                           double* outMatrixData);
            DLL_API int STD_CALL MatrixSub(const double* leftMatrixData,
                                           const unsigned int leftRow,
                                           const unsigned int leftCol,
                                           const double* rightMatrixData,
                                           const unsigned int rightRow,
                                           const unsigned int rightCol,
                                           const unsigned int outRow,
                                           const unsigned int outCol,
                                           double* outMatrixData);
            DLL_API int STD_CALL MatrixMul(const double* leftMatrixData,
                                           const unsigned int leftRow,
                                           const unsigned int leftCol,
                                           const double* rightMatrixData,
                                           const unsigned int rightRow,
                                           const unsigned int rightCol,
                                           const unsigned int outRow,
                                           const unsigned int outCol,
                                           double* outMatrixData);
            DLL_API int STD_CALL MatrixTransposition(const double* inMatrixData,
                                                     const unsigned int inRow,
                                                     const unsigned int inCol,
                                                     const unsigned int outRow,
                                                     const unsigned int outCol,
                                                     double* outMatrixData);
            DLL_API int STD_CALL MatrixInverse(const double* inMatrixData,
                                               const unsigned int inRow,
                                               const unsigned int inCol,
                                               const unsigned int outRow,
                                               const unsigned int outCol,
                                               double* outMatrixData);
            DLL_API int STD_CALL MatrixAddRowCol(const double* inMatrixData,
                                                 const unsigned int inRow,
                                                 const unsigned int inCol,
                                                 const unsigned int outRow,
                                                 const unsigned int outCol,
                                                 double* outMatrixData);
            DLL_API int STD_CALL MatrixSubRowCol(const double* inMatrixData,
                                                 const unsigned int inRow,
                                                 const unsigned int inCol,
                                                 const unsigned int outRow,
                                                 const unsigned int outCol,
                                                 double* outMatrixData);
        }
    } // end namespace Math
} // end namespace sixents

// For RtkLib
extern "C" {
// 时间转换
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
// 时间格式化
EXPORT void    time2str(gtime_t t, char *str, int n);

// 坐标
EXPORT void ecef2pos(const double *r, double *pos);
EXPORT void pos2ecef(const double *pos, double *r);
EXPORT void ecef2enu(const double *pos, const double *r, double *e);
EXPORT void enu2ecef(const double *pos, const double *e, double *r);
EXPORT void xyz2enu (const double *pos, double *E);

// 角度
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
}

CTestFunc::CTestFunc(MainWindow* parent)
    : mLoadRtkLibFlag(false)
    , mLoadGULLibFlag(false)
    , mLoadGULMathLibFlag(false)
    , mRtcmLibObj(nullptr)
    , mGULLibObj(nullptr)
    , mGULMathLibObj(nullptr)
{
    InitFuncMap();
    mParent = parent;
}

CTestFunc::~CTestFunc()
{
    if (mRtcmLibObj) {
        delete mRtcmLibObj;
        mRtcmLibObj = nullptr;
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

bool CTestFunc::LoadRtcmLib()
{
    mLoadRtkLibFlag = false;
    if (mRtcmLibObj) {
        delete mRtcmLibObj;
        mRtcmLibObj = nullptr;
    }

    do {
        mRtcmLibObj = new QLibrary(RtcmLibName);
        if (mRtcmLibObj == nullptr) {
            break;
        }
        if (!mRtcmLibObj->load()) {
            break;
        }
        mLoadRtkLibFlag = true;
    } while(false);

    return mLoadRtkLibFlag;
}

void CTestFunc::UnloadRtcmLib()
{
    if (!mLoadRtkLibFlag && nullptr == mRtcmLibObj) {
        return;
    }
    if (mRtcmLibObj->unload()) {
        mLoadRtkLibFlag = false;
    }
}

bool CTestFunc::LoadGULLib()
{
    mLoadGULLibFlag = false;
    if (mGULLibObj) {
        delete mGULLibObj;
        mGULLibObj = nullptr;
    }

    do {
        mGULLibObj = new QLibrary(GulUtilityLibName);
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
    if (mGULMathLibObj != nullptr) {
        delete mGULMathLibObj;
        mGULMathLibObj = nullptr;
    }

    do {
        mGULMathLibObj = new QLibrary(GulMathLibName);
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
        mParent->showInfomationdlg("Tips", "Execute Success");
        return 0;
    }
    mParent->showInfomationdlg("Tips", "Execute Failed");
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
    sixents::Math::FormatWeekSecTime(static_cast<unsigned int>(week), sec, static_cast<unsigned int>(flag),
                                               outStr, outStrLen);
    if (outStrLen == 0) {
        return false;
    }
    outStr = new char[static_cast<unsigned long long>(outStrLen)];
    memset(outStr, 0, sizeof (char) * static_cast<unsigned long long>(outStrLen));
    sixents::Math::FormatWeekSecTime(static_cast<unsigned int>(week), sec, static_cast<unsigned int>(flag),
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
    sixents::Math::FormatStandardTime(static_cast<unsigned int>(year), static_cast<unsigned int>(month),
                                                static_cast<unsigned int>(day), static_cast<unsigned int>(hour),
                                                static_cast<unsigned int>(minute), sec, outStr, outStrLen);
    if (outStrLen == 0) {
        return false;
    }
    outStr = new char[static_cast<unsigned long long>(outStrLen)];
    memset(outStr, 0, sizeof (char)* static_cast<unsigned long long>(outStrLen));
    sixents::Math::FormatStandardTime(static_cast<unsigned int>(year), static_cast<unsigned int>(month),
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
    sixents::Math::GNSSTimeToUTCTime(static_cast<unsigned int>(week), sec, static_cast<unsigned int>(flag),
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
    sixents::Math::UTCTimeToGNSSTime(static_cast<UINT32>(year),
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
    sixents::Math::GNSSTimeConvert(static_cast<UINT32>(srcWeek), srcSec, static_cast<UINT32>(srcType),
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
    sixents::Math::GlonassTimeToUTCTime(static_cast<unsigned int>(year), static_cast<unsigned int>(month),
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
    sixents::Math::UTCTimeToGlonassTime(static_cast<unsigned int>(year), static_cast<unsigned int>(month),
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
    sixents::Math::GlonassTimeToGPSTime(static_cast<unsigned int>(year), static_cast<unsigned int>(month),
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
    sixents::Math::GPSTimeToGlonassTime(static_cast<unsigned int>(week), second,
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
    sixents::Math::XYZ2BLH(xyz[0], xyz[1], xyz[2], b, l, h);
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
    sixents::Math::BLH2XYZ(blh[0], blh[1], blh[2], x, y, z);
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
    sixents::Math::XYZ2ENU(srcXYZ[0], srcXYZ[1], srcXYZ[2], refXYZ[0], refXYZ[1], refXYZ[2],
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
    sixents::Math::ENU2XYZ(srcENU[0], srcENU[1], srcENU[2], refXYZ[0], refXYZ[1], refXYZ[2],
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


    sixents::Math::SGlonassEphemeris glonassEphemeris;

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
    gtime_t rtkSecTime = epoch2time(epochTime);
    rtkClk = utc2gpst(rtkSecTime);
    double rtkClkRet = eph2clk(rtkClk, rtcm.nav.eph);
    free_rtcm(&rtcm);
    QString rtkRet = QString::number(rtkClkRet, 'f', COORDINATE_ACCURACY);

    // 执行GUL接口
    // 调用RTCM接口，解码星历电文
    // 加载RtcmLib库
    if(!LoadRtcmLib()) {
        return false;
    }

    // 初始化RTCM
    sixents::CParam paramInForInit;
    sixents::CParam paramOutForInit;
    INT32 retInit = sixents::RtcmInit(paramInForInit, paramOutForInit);
    if (retInit != sixents::common::rtcm::RETURN_SUCCESS) {
        qDebug() << __FUNCTION__ << __LINE__ << "loadRtcm failed";
        return false;
    }

    // 读取星历电文
    QFile fileObj(testDataFilePath);
    if (!fileObj.exists() || !fileObj.open(QIODevice::ReadOnly)) {
        return false;
    }
    QByteArray ephHexText = fileObj.readAll();// 原始电文
    // 从所有电文中读取星历电文
    UINT32 msgType = 0;
    UINT32 msgPos = 0;
    UINT32 expectLen = 0;
    QByteArray msg;
    do {
        INT32 retGetMsg = sixents::RtcmGetMessage(reinterpret_cast<BYTE *>(const_cast<char *>(ephHexText.data())),
                                         static_cast<UINT32>(ephHexText.count()), msgType, msgPos, expectLen);
        if (retGetMsg < sixents::common::rtcm::RETURN_SUCCESS) {  // 未找到D3或其它原因失败
            ephHexText.clear();
            msgPos = 0;
            break;
        } else if (retGetMsg == sixents::common::rtcm::RETURN_SUCCESS) {  // 找到D3，但电文不全
            ephHexText.remove(0, static_cast<int>(msgPos));
            msgPos = 0;
            break;
        } else if (retGetMsg > sixents::common::rtcm::RETURN_SUCCESS) {  // 有至少一包完整电文
            if (msgType == GPS_EPH || msgType == BDS_EPH || msgType == GAL_EPH) {  // 当收到一包完整星历电文
                msg = ephHexText.mid(static_cast<int>(msgPos), static_cast<int>(retGetMsg));
                break;
            }
            int startPos = 0;    // 删除时的起始位置
            int delLength = static_cast<int>(msgPos) + static_cast<int>(retGetMsg);    // 删除电文的长度
            ephHexText.remove(startPos, delLength);
            msgPos = 0;
            msgType = 0;
        }
        qDebug() << "ephHexText length:" << ephHexText.length();
    } while (!ephHexText.isEmpty());

    // 解星历电文
    if (msg.isEmpty()) { // 当前指针不能为空指针
        return false;
    }
    // 1、AddValue,把电文添加到入参
    sixents::CParam paramInForDecode;
    int msgLen = static_cast<int>(msg.count());
    paramInForDecode.AddValue(sixents::common::rtcm::PN_BA_MESSAGE_DATA, sixents::PDT_BYTE_ARRAY,
                              reinterpret_cast<PVOID>(const_cast<char *>(msg.toStdString().data())),
                              reinterpret_cast<PVOID>(static_cast<long long>(msgLen)));
    // 2、Decode
    sixents::CParam paramOutForDecode;
    INT32 retDecode = RtcmDecode(paramInForDecode, paramOutForDecode);
    if (retDecode == sixents::common::rtcm::RETURN_SUCCESS) {
        return false;
    }

    // 3、GetValue,解析outputParam，找到IGnssDataInterface对象
    // 注：最后一步处理，不对返回值进行判断
    sixents::IGnssDataInterface *gnssData = nullptr;
    sixents::Math::SEphemeris ephemeris;
    sixents::SEphemeris ephTemp;
    bool retGetValue = paramOutForDecode.GetValue(sixents::common::rtcm::PN_PTR_GNSS_DATA_OBJECT, &gnssData, nullptr);
    if (!retGetValue || !gnssData) {
        return false;
    }
    sixents::IGnssDataInterface::GnssDataType dataType = gnssData->GetGnssDataType();
    if (dataType == sixents::IGnssDataInterface::GDT_EPH) {
        sixents::CEphemeris *ephObj = dynamic_cast<sixents::CEphemeris *>(gnssData);
        ephTemp = ephObj->GetEphemeris();
    } else {
        return false;
    }
    RtcmEphToMathEph(&ephTemp, &ephemeris);
    // 将当前时间转为double时间
    double clock=0;
    double gulSecTime = static_cast<double>(rtkSecTime.time) + rtkSecTime.sec;

    sixents::Math::CalcEphSatClock(gulSecTime, ephemeris, clock);
    // 释放RTCM对象
    sixents::RtcmFinal();
    // 卸载RTCM Lib
    UnloadRtcmLib();
    // 调用GUL接口解算
    QString gulRet = QString::number(clock, 'f', COORDINATE_ACCURACY);
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
    sixents::Math::FormatAngleByDegree(deg, gulChRet, len);

    gulChRet=new char[len + 1];
    sixents::Math::FormatAngleByDegree(deg, gulChRet, len);

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
    unsigned int minute = static_cast<unsigned int>(dmsList[1].toInt());
    double sec = dmsList[2].toDouble();

    // 执行Rtk接口，未实现该结果
    QString rtkRet("null");
    // 执行GUL接口
    char* gulChRet = nullptr;
    unsigned int len = 0;
    sixents::Math::FormatAngleByDMS(degree, minute, sec, gulChRet, len, false);

    gulChRet=new char[len + 1];
    sixents::Math::FormatAngleByDMS(degree, minute, sec, gulChRet, len, false);

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
    sixents::Math::Deg2Rad(deg, gulRad);
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
    sixents::Math::DMS2Rad(degree, static_cast<unsigned int>(minute), sec, gulRad);
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
    sixents::Math::Rad2Deg(rad, gulDeg);
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
    unsigned int gulMinute = 0;
    double gulSec = 0.0;
    sixents::Math::Rad2DMS(rad, gulDegree, gulMinute, gulSec);
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
    UINT32 timeGulBeg = GetTickCount();
    sixents::Math::MatrixAdd(leftMatrix, static_cast<unsigned int>(srcRow), static_cast<unsigned int>(srcCol),
                                           rightMatrix, static_cast<unsigned int>(destRow), static_cast<unsigned int>(destCol),
                                           outRow, outCol, outMatrix);
    UINT32 timeGulEnd = GetTickCount();
    UINT32 gulUseTime = timeGulEnd - timeGulBeg;
    gulRet += "Begin Time:" + QString::number(timeGulBeg) +
            "\nEnd Time:" + QString::number(timeGulEnd) +
            "\nUse Time:" + QString::number(gulUseTime) + "\n";
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
    UINT32 timeGulBeg = GetTickCount();
    sixents::Math::MatrixSub(leftMatrix, static_cast<unsigned int>(srcRow), static_cast<unsigned int>(srcCol),
                                           rightMatrix, static_cast<unsigned int>(destRow), static_cast<unsigned int>(destCol),
                                           outRow, outCol, outMatrix);
    UINT32 timeGulEnd = GetTickCount();
    UINT32 gulUseTime = timeGulEnd - timeGulBeg;
    gulRet += "Begin Time:" + QString::number(timeGulBeg) +
            "\nEnd Time:" + QString::number(timeGulEnd) +
            "\nUse Time:" + QString::number(gulUseTime) + "\n";
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
    UINT32 timeRtkBeg = GetTickCount();
    matmul("NN", srcRow, destCol, srcCol, alpha, srcMatrixData, destMatrixData, beta, resultMatrixData);
    UINT32 timeRtkEnd = GetTickCount();
    UINT32 rtkUseTime = timeRtkEnd - timeRtkBeg;
    QString rtkRet("Rtk Result\n");
    rtkRet += "Begin Time:" + QString::number(timeRtkBeg) +
            "\nEnd Time:" + QString::number(timeRtkEnd) +
            "\nUse Time:" +QString::number(rtkUseTime) + "\n";
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


    UINT32 timeGulBeg = GetTickCount();
    sixents::Math::MatrixMul(leftMatrix, static_cast<unsigned int>(srcRow), static_cast<unsigned int>(srcCol),
                                           rightMatrix, static_cast<unsigned int>(destRow), static_cast<unsigned int>(destCol),
                                           outRow, outCol, outMatrix);
    UINT32 timeGulEnd = GetTickCount();
    UINT32 gulUseTime = timeGulEnd - timeGulBeg;
    gulRet += "Begin Time:" + QString::number(timeGulBeg) +
            "\nEnd Time:" + QString::number(timeGulEnd) +
            "\nUse Time:" + QString::number(gulUseTime) + "\n";
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

    sixents::Math::MatrixTransposition(srcMatrix, static_cast<unsigned int>(row), static_cast<unsigned int>(col),
                                       outRow, outCol, destMatrix);
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
    UINT32 timeRtkBeg = GetTickCount();
    matinv(data, row);
    UINT32 timeRtkEnd = GetTickCount();
    UINT32 rtkUseTime = timeRtkEnd - timeRtkBeg;
    QString rtkRet("Rtk Result\n");
    rtkRet += "Begin Time:" + QString::number(timeRtkBeg) +
            "\nEnd Time:" + QString::number(timeRtkEnd) +
            "\nUse Time:" +QString::number(rtkUseTime) + "\n";
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
    UINT32 timeGulBeg = GetTickCount();
    sixents::Math::MatrixInverse(srcMatrix, static_cast<unsigned int>(row), static_cast<unsigned int>(col),
                                 outRow, outCol, destMatrix);
    UINT32 timeGulEnd = GetTickCount();
    UINT32 gulUseTime = timeGulEnd - timeGulBeg;
    gulRet += "Begin Time:" + QString::number(timeGulBeg) +
            "\nEnd Time:" + QString::number(timeGulEnd) +
            "\nUse Time:" + QString::number(gulUseTime) + "\n";
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

    sixents::Math::MatrixAddRowCol(srcMatrix, static_cast<unsigned int>(row), static_cast<unsigned int>(col),
                                   outRow, outCol, destMatrix);
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

    sixents::Math::MatrixSubRowCol(srcMatrix, static_cast<unsigned int>(row), static_cast<unsigned int>(col),
                                   outRow, outCol, destMatrix);
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
    if (filePaths[1] != "txt") {
        outFilePath = filePath;
        return ;
    }
    outFilePath = filePaths[0] + destFilePath;
    QFile srcFileObj(filePath);
    QFile destFileObj(outFilePath);
    bool srcRet = srcFileObj.open(QIODevice::ReadOnly);
    bool destRet = destFileObj.open(QIODevice::WriteOnly);
    if (!srcRet || !destRet) {
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

void CTestFunc::RtcmEphToMathEph(sixents::SEphemeris *rtcmEph, sixents::Math::SEphemeris *gulEph)
{
    if (rtcmEph == nullptr || gulEph == nullptr) {
        return;
    }
    gulEph->m_ui16MsgType               = rtcmEph->m_ui16MsgType;
    gulEph->m_ui8SatId                  = rtcmEph->m_ui8SatId;
    gulEph->m_ui16WeekNum               = rtcmEph->m_ui16WeekNum;
    gulEph->m_ui8URA                    = rtcmEph->m_ui8URA;
    gulEph->m_ui8CodeOnL2               = rtcmEph->m_ui8CodeOnL2;
    gulEph->m_dbIdot                    = rtcmEph->m_dbIdot;
    gulEph->m_ui8Iode                   = rtcmEph->m_ui8Iode;
    gulEph->m_ui32Toc                   = rtcmEph->m_ui32Toc;
    gulEph->m_dbAf2                     = rtcmEph->m_dbAf2;
    gulEph->m_dbAf1                     = rtcmEph->m_dbAf1;
    gulEph->m_dbAf0                     = rtcmEph->m_dbAf0;
    gulEph->m_ui16Iodc                  = rtcmEph->m_ui16Iodc;
    gulEph->m_dbCrs                     = rtcmEph->m_dbCrs;
    gulEph->m_dbDeltaN                  = rtcmEph->m_dbDeltaN;
    gulEph->m_dbM0                      = rtcmEph->m_dbM0;
    gulEph->m_dbCuc                     = rtcmEph->m_dbCuc;
    gulEph->m_dbEccentricity            = rtcmEph->m_dbEccentricity;
    gulEph->m_dbCus                     = rtcmEph->m_dbCus;
    gulEph->m_dbAHalf                   = rtcmEph->m_dbAHalf;
    gulEph->m_ui32Toe                   = rtcmEph->m_ui32Toe;
    gulEph->m_dbCic                     = rtcmEph->m_dbCic;
    gulEph->m_dbOmega0                  = rtcmEph->m_dbOmega0;
    gulEph->m_dbCis                     = rtcmEph->m_dbCis;
    gulEph->m_dbI0                      = rtcmEph->m_dbI0;
    gulEph->m_dbCrc                     = rtcmEph->m_dbCrc;
    gulEph->m_dbArgumentOfPerigee       = rtcmEph->m_dbArgumentOfPerigee;
    gulEph->m_dbOmegaDot                = rtcmEph->m_dbOmegaDot;
    gulEph->m_dbIODot                   = rtcmEph->m_dbIODot;
    gulEph->m_dbTgd                     = rtcmEph->m_dbTgd;
    gulEph->m_ui8SvHealth               = rtcmEph->m_ui8SvHealth;
    gulEph->m_ui8L2PDataFlag            = rtcmEph->m_ui8L2PDataFlag;
    gulEph->m_ui8FitInterval            = rtcmEph->m_ui8FitInterval;
    gulEph->m_ui8SISAIndex              = rtcmEph->m_ui8SISAIndex;
    gulEph->m_ui16IODnav                = rtcmEph->m_ui16IODnav;
    gulEph->m_ui8SvSisa                 = rtcmEph->m_ui8SvSisa;
    gulEph->m_dbBgdE1E5a                = rtcmEph->m_dbBgdE1E5a;
    gulEph->m_dbBgdE5bE1                = rtcmEph->m_dbBgdE5bE1;
    gulEph->m_ui8OSHS                   = rtcmEph->m_ui8OSHS;
    gulEph->m_ui8OSDVS                  = rtcmEph->m_ui8OSDVS;
    gulEph->m_ui8E5bSignalHealthStatus  = rtcmEph->m_ui8E5bSignalHealthStatus;
    gulEph->m_ui8E5bDataValidityStatus   = rtcmEph->m_ui8E5bDataValidityStatus;
    gulEph->m_ui8E1bSignalHealthStatus  = rtcmEph->m_ui8E1bSignalHealthStatus;
    gulEph->m_ui8E1bDataValidityStatus  = rtcmEph->m_ui8E1bDataValidityStatus;
    gulEph->m_ui8AgeOfDataEphemeris     = rtcmEph->m_ui8AgeOfDataEphemeris;
    gulEph->m_ui8AgeOfDataClock         = rtcmEph->m_ui8AgeOfDataClock;
    gulEph->m_dbTgd1                    = rtcmEph->m_dbTgd1;
    gulEph->m_dbTgd2                    = rtcmEph->m_dbTgd2;
    gulEph->m_ui8Reserved               = rtcmEph->m_ui8Reserved;
}

void CTestFunc::RtcmGloEphToMathGloEph(sixents::SGlonassEphemeris *rtcmEph, sixents::Math::SGlonassEphemeris *gulEph)
{
    if (rtcmEph == nullptr || gulEph == nullptr) {
        return;
    }
    gulEph->m_ui16MsgType                  = rtcmEph->m_ui16MsgType;
    gulEph->m_ui8SatId                     = rtcmEph->m_ui8SatId;
    gulEph->m_ui8SatFrequencyChannelNumber = rtcmEph->m_ui8SatFrequencyChannelNumber;
    gulEph->m_ui8AlmanacHealth             = rtcmEph->m_ui8AlmanacHealth;
    gulEph->m_ui8AHAI                      = rtcmEph->m_ui8AHAI;
    gulEph->m_ui8P1                        = rtcmEph->m_ui8P1;
    gulEph->m_ui16Tk                       = rtcmEph->m_ui16Tk;
    gulEph->m_ui8MsbOfBn                   = rtcmEph->m_ui8MsbOfBn;
    gulEph->m_ui8P2                        = rtcmEph->m_ui8P2;
    gulEph->m_ui16Tb                       = rtcmEph->m_ui16Tb;
    gulEph->m_dbXnTbFirstDerivative        = rtcmEph->m_dbXnTbFirstDerivative;
    gulEph->m_dbXnTb                       = rtcmEph->m_dbXnTb;
    gulEph->m_dbXnTbSecondDerivative       = rtcmEph->m_dbXnTbSecondDerivative;
    gulEph->m_dbYnTbFirstDerivative        = rtcmEph->m_dbYnTbFirstDerivative;
    gulEph->m_dbYnTb                       = rtcmEph->m_dbYnTb;
    gulEph->m_dbYnTbSecondDerivative       = rtcmEph->m_dbYnTbSecondDerivative;
    gulEph->m_dbZnTbFirstDerivative        = rtcmEph->m_dbZnTbFirstDerivative;
    gulEph->m_dbZnTb                       = rtcmEph->m_dbZnTb;
    gulEph->m_dbZnTbSecondDerivative       = rtcmEph->m_dbZnTbSecondDerivative;
    gulEph->m_ui8P3                        = rtcmEph->m_ui8P3;
    gulEph->m_dbGammaTb                    = rtcmEph->m_dbGammaTb;
    gulEph->m_ui8GmP                       = rtcmEph->m_ui8GmP;
    gulEph->m_ui8GmLn3                     = rtcmEph->m_ui8GmLn3;
    gulEph->m_dbTnTb                       = rtcmEph->m_dbTnTb;
    gulEph->m_dbGmDeltaTn                  = rtcmEph->m_dbGmDeltaTn;
    gulEph->m_ui8En                        = rtcmEph->m_ui8En;
    gulEph->m_ui8GmP4                      = rtcmEph->m_ui8GmP4;
    gulEph->m_ui8GmFt                      = rtcmEph->m_ui8GmFt;
    gulEph->m_ui16GmNt                     = rtcmEph->m_ui16GmNt;
    gulEph->m_ui8GmM                       = rtcmEph->m_ui8GmM;
    gulEph->m_ui8AOAD                      = rtcmEph->m_ui8AOAD;
    gulEph->m_ui16NA                       = rtcmEph->m_ui16NA;
    gulEph->m_dbTc                         = rtcmEph->m_dbTc;
    gulEph->m_ui8GmN4                      = rtcmEph->m_ui8GmN4;
    gulEph->m_dbGmTGps                     = rtcmEph->m_dbGmTGps;
    gulEph->m_ui8GmLn5                     = rtcmEph->m_ui8GmLn5;
    gulEph->m_ui8Reserved                  = rtcmEph->m_ui8Reserved;
}


