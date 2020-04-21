#ifndef TESTFUNC_H
#define TESTFUNC_H

#include <QLibrary>
#include <map>
#include <functional>

class CTestFunc;
//typedef bool(CTestFunc::* TestFunc)(const QString , QString&);
//using FuncList = std::vector<TestFunc>;
using FuncList = std::map <int, std::function<bool(CTestFunc&, const QString, QString&)>>;

class CTestFunc
{
public:
    explicit CTestFunc();
    ~CTestFunc();

    // 加载动态库
    bool LoadRtkLib();
    void UnloadRtkLib();
    bool LoadGULLib();
    void UnloadGULLib();
    bool LoadGULMathLib();
    void UnloadGULMathLib();

    // 测试接口
    // dataType is true, test file data;
    // dataType is false, test simple data;
    int ExecuteTest(const QString testData, const int testFunc, QString& result);
private:
    void ExecuteTestTime(QString& testData, const int testFunc);
    // 测试函数接口
    bool FormatWeekSecTime(const QString testData, QString& result);
    bool FormatStandardTime(const QString testData, QString& result);
    bool GNSSTimeToUTCTime(const QString testData, QString& result);
    bool UTCTimeToGNSSTime(const QString testData, QString& result);
    bool GNSSTimeConvert(const QString testData, QString& result);
    bool GlonassToUTC(const QString testData, QString& result);
    bool UTCToGlonass(const QString testData, QString& result);
    bool GlonassToGPS(const QString testData, QString& result);
    bool GPSToGlonass(const QString testData, QString& result);
    bool XYZ2BLH(const QString testData, QString& result);
    bool BLH2XYZ(const QString testData, QString& result);
    bool XYZ2ENU(const QString testData, QString& result);
    bool ENU2XYZ(const QString testData, QString& result);
    bool CalcGlonassEphSatClock(const QString testData, QString& result);
    bool CalcEphSatClock(const QString testData, QString& result);
    bool CalcGlonassEphSatPos(const QString testData, QString& result);
    bool CalcEphSatPos(const QString testData, QString& result);
    bool FormatAngleByDegree(const QString testData, QString& result);
    bool FormatAngleByDMS(const QString testData, QString& result);
    bool Deg2Rad(const QString testData, QString& result);
    bool DMS2Rad(const QString testData, QString& result);
    bool Rad2Deg(const QString testData, QString& result);
    bool Rad2DMS(const QString testData, QString& result);
    bool MatrixAdd(const QString testData, QString& result);
    bool MatrixSub(const QString testData, QString& result);
    bool MatrixMul(const QString testData, QString& result);
    bool MatrixTransposition(const QString testData, QString& result);
    bool MatrixInverse(const QString testData, QString& result);
    bool MatrixAddRowCol(const QString testData, QString& result);
    bool MatrixSubRowCol(const QString testData, QString& result);
    // 读写TXT文件
    QString ReadTxtFile(const QString& filePath);

    // 读写矩阵文件
    void WriteTxtFile(const QString& filePath, const QString& data);

    // 读星历文件
    void FileConvertToBin(const QString& filePath, QString& outFilePath);
    // 生成文件名
    // 新生成的结果文件命名规则：接口名+当前时间（精确到秒）
    // 示例：FormatWeekSecTime20200416102203
    // 需要注意：同一秒内多次执行同一个测试函数时，后生成的文件会覆盖前一次生成的文件。
    QString GenNewFileName(const QString funcName);
    // 时间的自验证

    // 加函数映射
    void InitFuncMap();
private:
    bool mLoadRtkLibFlag;
    bool mLoadGULLibFlag;
    bool mLoadGULMathLibFlag;
    QLibrary* mRtkLibObj;
    QLibrary* mGULLibObj;
    QLibrary* mGULMathLibObj;
    FuncList mFuncs;
}; // end class TestFunc

#endif // TESTFUNC_H
