#ifndef CONSTANTDEF_H
#define CONSTANTDEF_H
#include <QString>
#include <QObject>

const static QString ChoiceOneIF = QString::fromLocal8Bit("请选择一个业务需求");

// 需要加载的Lib库名称
const static QString RtcmLibName = "rtcm";
const static QString GulUtilityLibName = "GulUtility";
const static QString GulMathLibName = "GulMath";

// 精度常量定义
const static int COORDINATE_ACCURACY = 9;  // 空间直角坐标，以及大地坐标中高程的精确度
const static int BLH_ACCURACY = 11;        // 大地坐标中经纬度的精确度
const static int MSEC_ACCURACY = 3;        // 小数秒的精确度（精确到毫秒）
const static int MATRIX_ACCURACY = 6;      // 矩阵中double数据的精确度

// 间隔符定义
const QString COMMA = ",";
const QString SEMICOLON = ";";
const QString COLON = ":";
const QString DASH_LINE = "-";
const QString SPACE = " ";

// 星历电文类型
enum TeleTextID {
    GLONASS_EPH = 1020,
    GPS_EPH = 1019,
    GAL_EPH = 1045,
    BDS_EPH = 1046
};


#endif // CONSTANTDEF_H
