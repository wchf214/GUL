/**
 * @file        Constants.h
 * @author      yangchengyi@sixents.com,zhuquanlin@sixents.com,yangzhenxing@sixents.com
 * @version     1.0
 * @date        2019-12-20
 * @brief       常量定义头文件。
 * @details     定义了各种宏，字符串常量以及全局结构体等。
 * @note        change history:
 *                  <2019-12-20>  | 1.0 | yangchenyi | 创建初始版本
 * @copyright   Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef _RTCM_CONSTANTS_H_
#define _RTCM_CONSTANTS_H_
#include <map>
#include <string>
#include "BasicType.h"
namespace sixents
{
    namespace common
    {
        namespace rtcm
        {
            // 数据占用bit位的长度
            constexpr UINT32 DATA_LENGTH_1 = 1U;
            constexpr UINT32 DATA_LENGTH_2 = 2U;
            constexpr UINT32 DATA_LENGTH_3 = 3U;
            constexpr UINT32 DATA_LENGTH_4 = 4U;
            constexpr UINT32 DATA_LENGTH_5 = 5U;
            constexpr UINT32 DATA_LENGTH_6 = 6U;
            constexpr UINT32 DATA_LENGTH_7 = 7U;
            constexpr UINT32 DATA_LENGTH_8 = 8U;
            constexpr UINT32 DATA_LENGTH_9 = 9U;
            constexpr UINT32 DATA_LENGTH_10 = 10U;
            constexpr UINT32 DATA_LENGTH_11 = 11U;
            constexpr UINT32 DATA_LENGTH_12 = 12U;
            constexpr UINT32 DATA_LENGTH_13 = 13U;
            constexpr UINT32 DATA_LENGTH_14 = 14U;
            constexpr UINT32 DATA_LENGTH_15 = 15U;
            constexpr UINT32 DATA_LENGTH_16 = 16U;
            constexpr UINT32 DATA_LENGTH_17 = 17U;
            constexpr UINT32 DATA_LENGTH_18 = 18U;
            constexpr UINT32 DATA_LENGTH_19 = 19U;
            constexpr UINT32 DATA_LENGTH_20 = 20U;
            constexpr UINT32 DATA_LENGTH_21 = 21U;
            constexpr UINT32 DATA_LENGTH_22 = 22U;
            constexpr UINT32 DATA_LENGTH_23 = 23U;
            constexpr UINT32 DATA_LENGTH_24 = 24U;
            constexpr UINT32 DATA_LENGTH_25 = 25U;
            constexpr UINT32 DATA_LENGTH_26 = 26U;
            constexpr UINT32 DATA_LENGTH_27 = 27U;
            constexpr UINT32 DATA_LENGTH_28 = 28U;
            constexpr UINT32 DATA_LENGTH_29 = 29U;
            constexpr UINT32 DATA_LENGTH_30 = 30U;
            constexpr UINT32 DATA_LENGTH_31 = 31U;
            constexpr UINT32 DATA_LENGTH_32 = 32U;
            constexpr UINT32 DATA_LENGTH_33 = 33U;
            constexpr UINT32 DATA_LENGTH_34 = 34U;
            constexpr UINT32 DATA_LENGTH_35 = 35U;
            constexpr UINT32 DATA_LENGTH_36 = 36U;
            constexpr UINT32 DATA_LENGTH_37 = 37U;
            constexpr UINT32 DATA_LENGTH_38 = 38U;
            constexpr UINT32 DATA_LENGTH_39 = 39U;
            constexpr UINT32 DATA_LENGTH_40 = 40U;
            constexpr UINT32 DATA_LENGTH_41 = 41U;
            constexpr UINT32 DATA_LENGTH_42 = 42U;
            constexpr UINT32 DATA_LENGTH_43 = 43U;
            constexpr UINT32 DATA_LENGTH_44 = 44U;
            constexpr UINT32 DATA_LENGTH_45 = 45U;
            constexpr UINT32 DATA_LENGTH_46 = 46U;
            constexpr UINT32 DATA_LENGTH_47 = 47U;
            constexpr UINT32 DATA_LENGTH_48 = 48U;
            constexpr UINT32 DATA_LENGTH_49 = 49U;
            constexpr UINT32 DATA_LENGTH_50 = 50U;
            constexpr UINT32 DATA_LENGTH_51 = 51U;
            constexpr UINT32 DATA_LENGTH_52 = 52U;
            constexpr UINT32 DATA_LENGTH_53 = 53U;
            constexpr UINT32 DATA_LENGTH_54 = 54U;
            constexpr UINT32 DATA_LENGTH_55 = 55U;
            constexpr UINT32 DATA_LENGTH_56 = 56U;
            constexpr UINT32 DATA_LENGTH_57 = 57U;
            constexpr UINT32 DATA_LENGTH_58 = 58U;
            constexpr UINT32 DATA_LENGTH_59 = 59U;
            constexpr UINT32 DATA_LENGTH_60 = 60U;
            constexpr UINT32 DATA_LENGTH_61 = 61U;
            constexpr UINT32 DATA_LENGTH_62 = 62U;
            constexpr UINT32 DATA_LENGTH_63 = 63U;
            constexpr UINT32 DATA_LENGTH_64 = 64U;
            constexpr UINT32 DATA_LENGTH_65 = 65U;
            constexpr UINT32 DATA_LENGTH_66 = 66U;
            constexpr UINT32 DATA_LENGTH_67 = 67U;
            constexpr UINT32 DATA_LENGTH_68 = 68U;
            constexpr UINT32 DATA_LENGTH_69 = 69U;
            constexpr UINT32 DATA_LENGTH_70 = 70U;
            constexpr UINT32 DATA_LENGTH_71 = 71U;
            constexpr UINT32 DATA_LENGTH_72 = 72U;
            constexpr UINT32 DATA_LENGTH_73 = 73U;
            constexpr UINT32 DATA_LENGTH_74 = 74U;
            constexpr UINT32 DATA_LENGTH_75 = 75U;
            constexpr UINT32 DATA_LENGTH_76 = 76U;
            constexpr UINT32 DATA_LENGTH_77 = 77U;
            constexpr UINT32 DATA_LENGTH_78 = 78U;
            constexpr UINT32 DATA_LENGTH_79 = 79U;
            constexpr UINT32 DATA_LENGTH_80 = 80U;
            constexpr UINT32 DATA_LENGTH_81 = 81U;
            constexpr UINT32 DATA_LENGTH_82 = 82U;
            constexpr UINT32 DATA_LENGTH_83 = 83U;
            constexpr UINT32 DATA_LENGTH_84 = 84U;
            constexpr UINT32 DATA_LENGTH_85 = 85U;
            constexpr UINT32 DATA_LENGTH_86 = 86U;
            constexpr UINT32 DATA_LENGTH_87 = 87U;
            constexpr UINT32 DATA_LENGTH_88 = 88U;
            constexpr UINT32 DATA_LENGTH_89 = 89U;
            constexpr UINT32 DATA_LENGTH_90 = 90U;
            constexpr UINT32 DATA_LENGTH_91 = 91U;
            constexpr UINT32 DATA_LENGTH_92 = 92U;
            constexpr UINT32 DATA_LENGTH_93 = 93U;
            constexpr UINT32 DATA_LENGTH_94 = 94U;
            constexpr UINT32 DATA_LENGTH_95 = 95U;
            constexpr UINT32 DATA_LENGTH_96 = 96U;
            constexpr UINT32 DATA_LENGTH_97 = 97U;
            constexpr UINT32 DATA_LENGTH_98 = 98U;
            constexpr UINT32 DATA_LENGTH_99 = 99U;
            constexpr UINT32 DATA_LENGTH_100 = 100U;

            // MSM4卫星数据的总长度
            constexpr UINT32 MSM4_SAT_DATA_LENGTH = 18U;
            // MSM4信号数据的总长度
            constexpr UINT32 MSM4_SIG_DATA_LENGTH = 48U;

            // 2的－n次方，用于比例因子计算
            constexpr DOUBLE P2_4 = 0.0625;                 /* 2^-4 */
            constexpr DOUBLE P2_5 = 0.03125;                /* 2^-5 */
            constexpr DOUBLE P2_6 = 0.015625;               /* 2^-6 */
            constexpr DOUBLE P2_10 = 0.0009765625;          /* 2^-10 */
            constexpr DOUBLE P2_11 = 4.882812500000000E-04; /* 2^-11 */
            constexpr DOUBLE P2_15 = 3.051757812500000E-05; /* 2^-15 */
            constexpr DOUBLE P2_17 = 7.629394531250000E-06; /* 2^-17 */
            constexpr DOUBLE P2_19 = 1.907348632812500E-06; /* 2^-19 */
            constexpr DOUBLE P2_20 = 9.536743164062500E-07; /* 2^-20 */
            constexpr DOUBLE P2_21 = 4.768371582031250E-07; /* 2^-21 */
            constexpr DOUBLE P2_23 = 1.192092895507810E-07; /* 2^-23 */
            constexpr DOUBLE P2_24 = 5.960464477539063E-08; /* 2^-24 */
            constexpr DOUBLE P2_27 = 7.450580596923828E-09; /* 2^-27 */
            constexpr DOUBLE P2_29 = 1.862645149230957E-09; /* 2^-29 */
            constexpr DOUBLE P2_30 = 9.313225746154785E-10; /* 2^-30 */
            constexpr DOUBLE P2_31 = 4.656612873077393E-10; /* 2^-31 */
            constexpr DOUBLE P2_32 = 2.328306436538696E-10; /* 2^-32 */
            constexpr DOUBLE P2_33 = 1.164153218269348E-10; /* 2^-33 */
            constexpr DOUBLE P2_34 = 5.820766091346740E-11; /* 2^-34 */
            constexpr DOUBLE P2_35 = 2.910383045673370E-11; /* 2^-35 */
            constexpr DOUBLE P2_38 = 3.637978807091710E-12; /* 2^-38 */
            constexpr DOUBLE P2_39 = 1.818989403545856E-12; /* 2^-39 */
            constexpr DOUBLE P2_40 = 9.094947017729280E-13; /* 2^-40 */
            constexpr DOUBLE P2_43 = 1.136868377216160E-13; /* 2^-43 */
            constexpr DOUBLE P2_46 = 1.421085471520200E-14; /* 2^-46 */
            constexpr DOUBLE P2_48 = 3.552713678800501E-15; /* 2^-48 */
            constexpr DOUBLE P2_50 = 8.881784197001252E-16; /* 2^-50 */
            constexpr DOUBLE P2_55 = 2.775557561562891E-17; /* 2^-55 */
            constexpr DOUBLE P2_59 = 1.734723475976810E-18; /* 2^-59 */
            constexpr DOUBLE P2_66 = 1.355252715606880E-20; /* 2^-66 */

            // 10的－n次方，用于比例因子计算
            constexpr DOUBLE P104 = 1000.0; /* 10^4 */

            // 2的4次方，用于比例因子计算
            constexpr UINT32 P2T4 = 16U; /* 2^4 */

            constexpr DOUBLE CLIGHT = 299792458.0;        /* speed of light (m/s) */
            constexpr DOUBLE RANGE_MS = (CLIGHT * 0.001); /* range in 1 ms */

            constexpr DOUBLE FREQ1 = 1.57542E9;      /* L1/E1  frequency (Hz) */
            constexpr DOUBLE FREQ2 = 1.22760E9;      /* L2     frequency (Hz) */
            constexpr DOUBLE FREQ5 = 1.17645E9;      /* L5/E5a frequency (Hz) */
            constexpr DOUBLE FREQ6 = 1.27875E9;      /* E6/LEX frequency (Hz) */
            constexpr DOUBLE FREQ7 = 1.20714E9;      /* E5b    frequency (Hz) */
            constexpr DOUBLE FREQ8 = 1.191795E9;     /* E5a+b  frequency (Hz) */
            constexpr DOUBLE FREQ9 = 2.492028E9;     /* S      frequency (Hz) */
            constexpr DOUBLE FREQ1_GLO = 1.60200E9;  /* GLONASS G1 base frequency (Hz) */
            constexpr DOUBLE DFRQ1_GLO = 0.56250E6;  /* GLONASS G1 bias frequency (Hz/n) */
            constexpr DOUBLE FREQ2_GLO = 1.24600E9;  /* GLONASS G2 base frequency (Hz) */
            constexpr DOUBLE DFRQ2_GLO = 0.43750E6;  /* GLONASS G2 bias frequency (Hz/n) */
            constexpr DOUBLE FREQ3_GLO = 1.202025E9; /* GLONASS G3 frequency (Hz) */
            constexpr DOUBLE FREQ1_CMP = 1.561098E9; /* BeiDou B1 frequency (Hz) */
            constexpr DOUBLE FREQ2_CMP = 1.20714E9;  /* BeiDou B2 frequency (Hz) */
            constexpr DOUBLE FREQ3_CMP = 1.26852E9;  /* BeiDou B3 frequency (Hz) */

            constexpr DOUBLE PRUNIT_GPS = 299792.458; /* rtcm ver.3 unit of gps pseudorange (m) */
            constexpr DOUBLE PRUNIT_GLO = 599584.916; /* rtcm ver.3 unit of glonass pseudorange (m) */

            // 比例因子

            constexpr DOUBLE SCALE_DF011 = 0.02;
            constexpr DOUBLE SCALE_DF012 = 0.0005;
            constexpr DOUBLE SCALE_DF015 = 0.25;
            constexpr DOUBLE SCALE_DF017 = 0.02;
            constexpr DOUBLE SCALE_DF018 = 0.0005;

            constexpr DOUBLE SCALE_DF041 = 0.02;
            constexpr DOUBLE SCALE_DF042 = 0.0005;
            constexpr DOUBLE SCALE_DF045 = 0.25;
            constexpr DOUBLE SCALE_DF047 = 0.02;
            constexpr DOUBLE SCALE_DF048 = 0.0005;

            constexpr UINT32 SCALE_DF110 = 15U;
            constexpr UINT32 SCALE_DF134 = 4U;
            constexpr UINT32 SCALE_DF493 = 8U;
            constexpr UINT32 SCALE_DF505 = 8U;
            constexpr UINT32 SCALE_DF293 = 60U;
            constexpr UINT32 SCALE_DF304 = 60U;
            constexpr UINT32 SCALE_DF452 = 1024U;
            constexpr UINT32 SCALE_DF289 = 4096U;
            constexpr UINT32 SCALE_DF489 = 8192U;
            constexpr UINT32 SCALE_DF419 = 7U;

            constexpr DOUBLE SCALE_DF365 = 0.0001;
            constexpr DOUBLE SCALE_DF366 = 0.0004;
            constexpr DOUBLE SCALE_DF367 = 0.0004;

            constexpr DOUBLE SCALE_DF368 = 0.000001;
            constexpr DOUBLE SCALE_DF369 = 0.000004;
            constexpr DOUBLE SCALE_DF370 = 0.000004;

            constexpr DOUBLE SCALE_DF376 = 0.0001;
            constexpr DOUBLE SCALE_DF377 = 0.000001;
            constexpr DOUBLE SCALE_DF378 = 0.00000002;

            constexpr DOUBLE SCALE_DF390 = 0.0001;

            constexpr DOUBLE GLONASSFrequencyChannelNumber = 7.0;

            constexpr DOUBLE L2subL1pseudorange = 163.82;
            // 信号强度的比例因子
            constexpr UINT32 SCALE_SIGNAL_STRENGTH = 4U;

            static constexpr DOUBLE SC2RAD = 3.1415926535898; /* semi-circle to radian (IS-GPS) */
            static constexpr DOUBLE SQRTM_TO_M = 2.0;

            // 返回值定义
            static const INT32 RETURN_SUCCESS = 0;               // 成功
            static const INT32 RETURN_FAIL = -1;                 // 失败
            static const INT32 RETURN_PACKAGE_LENGHT_ERROR = -2; // 包长度错误
            static const INT32 RETURN_CRC_CHECK_FAILED = -3;     // CRC校验失败
            static const INT32 RETURN_STATION_CORRECT = -4;      // StatioinId校验失败
            static const INT32 RETURN_PERMISSION_ERROR = -5;     // 权限错误
            static const INT32 RETURN_UNSUPPORTED_RTCM_MSG = -6; // 暂不支持的协议
            static const INT32 RETURN_NOT_INITIALIZED = -7;      // 未初始化
            static const INT32 RETURN_INVALID_PARAMETER = -8;    // 无效参数

            // 返回值对应的错误描述
            static PCSTR ERRINF_SUCCESS = "Success";
            static PCSTR ERRINF_FAIL = "General error";
            static PCSTR ERRINF_PACKAGE_LENGHT_ERROR = "Invalid package length";
            static PCSTR ERRINF_CRC_CHECK_FAILED = "Invalidation to check CRC";
            static PCSTR ERRINF_STATION_CORRECT = "Failed to verify ID of Reference station";
            static PCSTR ERRINF_PERMISSION_ERROR = "Permission error";
            static PCSTR ERRINF_UNSUPPORTED_RTCM_MSG = "Unsupported RTCM message";
            static PCSTR ERRINF_NOT_INITIALIZED = "Not initialized";
            static PCSTR ERRINF_INVALID_PARAMETER = "Invalid parameter";

            //// GNSS数据无效值定义
            // constexpr INT32 GNSS_INT8_INVALID_VALUE = -128;
            // constexpr INT32 GNSS_INT9_INVALID_VALUE = -256;
            // constexpr INT32 GNSS_INT10_INVALID_VALUE = -512;
            constexpr INT32 GNSS_INT14_INVALID_VALUE = -8192; // 0xFFFFE000
            // constexpr INT32 GNSS_INT15_INVALID_VALUE = -16384;
            // constexpr INT32 GNSS_INT16_INVALID_VALUE = -32768;
            // constexpr INT32 GNSS_INT17_INVALID_VALUE = -65536;
            // constexpr INT32 GNSS_INT19_INVALID_VALUE = -262144;
            constexpr INT32 GNSS_INT20_INVALID_VALUE = -524288; // 0xFFF80000
            // constexpr INT32 GNSS_INT21_INVALID_VALUE = -1048576;
            // constexpr INT32 GNSS_INT22_INVALID_VALUE = -2097152;
            // constexpr INT32 GNSS_INT23_INVALID_VALUE = -4194304;
            // constexpr INT32 GNSS_INT24_INVALID_VALUE = -8388608;
            // constexpr INT32 GNSS_INT25_INVALID_VALUE = -16777216;
            // constexpr INT32 GNSS_INT26_INVALID_VALUE = -33554432;
            // constexpr INT32 GNSS_INT27_INVALID_VALUE = -67108864;
            // constexpr INT32 GNSS_INT30_INVALID_VALUE = -536870912;
            // constexpr INT32 GNSS_INT32_INVALID_VALUE = -2147483648;
            // constexpr INT64 GNSS_INT34_INVALID_VALUE = -8589934592;
            // constexpr INT64 GNSS_INT35_INVALID_VALUE = -17179869184;
            // constexpr INT64 GNSS_INT38_INVALID_VALUE = -137438953472;

            static const UINT32 MSG_UNKNOWN = 0U; // 未知消息类型
            static const UINT32 MSG_1004 = 1004U; // 1004消息
            static const UINT32 MSG_1005 = 1005U; // 1005消息
            static const UINT32 MSG_1006 = 1006U; // 1006消息
            static const UINT32 MSG_1012 = 1012U; // 1012消息
            static const UINT32 MSG_1019 = 1019U; // 1019消息
            static const UINT32 MSG_1020 = 1020U; // 1020消息
            static const UINT32 MSG_1033 = 1033U; // 1033消息
            static const UINT32 MSG_1042 = 1042U; // 1042消息
            static const UINT32 MSG_1044 = 1044U; // 1044消息
            static const UINT32 MSG_1045 = 1045U; // 1045消息
            static const UINT32 MSG_1046 = 1046U; // 1046消息
            static const UINT32 MSG_1057 = 1057U; // 1057消息
            static const UINT32 MSG_1058 = 1058U; // 1058消息
            static const UINT32 MSG_1059 = 1059U; // 1059消息
            static const UINT32 MSG_1060 = 1060U; // 1060消息
            static const UINT32 MSG_1061 = 1061U; // 1061消息
            static const UINT32 MSG_1062 = 1062U; // 1062消息
            static const UINT32 MSG_1063 = 1063U; // 1063消息
            static const UINT32 MSG_1064 = 1064U; // 1064消息
            static const UINT32 MSG_1065 = 1065U; // 1065消息
            static const UINT32 MSG_1066 = 1066U; // 1065消息
            static const UINT32 MSG_1067 = 1067U; // 1067消息
            static const UINT32 MSG_1068 = 1068U; // 1068消息
            static const UINT32 MSG_1074 = 1074U; // 1074消息
            static const UINT32 MSG_1077 = 1077U; // 1077消息
            static const UINT32 MSG_1084 = 1084U; // 1084消息
            static const UINT32 MSG_1087 = 1087U; // 1087消息
            static const UINT32 MSG_1094 = 1094U; // 1094消息
            static const UINT32 MSG_1097 = 1097U; // 1097消息
            static const UINT32 MSG_1114 = 1114U; // 1114消息
            static const UINT32 MSG_1117 = 1117U; // 1117消息
            static const UINT32 MSG_1124 = 1124U; // 1124消息
            static const UINT32 MSG_1127 = 1127U; // 1127消息

            static const INT32 POLYCRC32 = 0xEDB88320U;             // CRC32 polynomial
            static const UINT32 MSG_HEAD_LENGTH = 24U;              // 消息头的比特位数
            static const UINT32 MSG_HEAD_BYTE_LENGTH = 3U;          // 消息头长度
            static const UINT32 MSG_MAX_LENGTH = 1024U;             // 消息体的最大长度
            static const UINT32 MSG_DATA_LENGTH_START_INDEX = 14U;  // 消息长度开始的比特位
            static const UINT32 MSG_HEAD_PROTOCOL_LENGTH = 8U;      // 消息头中协议号占用比特位
            static const UINT32 MSG_HEAD_RESERVED_LENGTH = 6U;      // 消息头预留比特位
            static const UINT32 MSG_DATA_LENGTH = 10U;              // 消息长度占用比特位
            static const BYTE RTCM32_PREABLE = 0xD3;                // 消息头标示
            static const UINT32 RTCM32_PREABLE_INDEX = 0x00U;       // 头标示偏移
            static const UINT32 MSG_LENGTH_FIELD_BYTE_SIZE = 0x02U; // 长度字段占用字节

            static const UINT32 MSG_TYPE_BIT_OFFSET = 24U; // 电文类型位偏移
            static const UINT32 MSG_TYPE_BIT_SIZE = 12U;   // 电文类型字段占用字节

            static const INT32 INT_BIT_LENGTH = 32;            // int类型占用比特位
            static const INT32 NUMBER_63 = 0x3F;               // 数字63，用于取最后6个比特位
            static const INT32 MSG_1005_DATA_BYTE_LENGTH = 19; // 1005的消息体总长度
            static const UINT32 CRC24_DATA_LENGTH = 3U;        // CRC24 校验码长度
            static const UINT32 BYTE_TO_BIT_COUNT = 8U;        // 字节转比特位的个数
            static const UINT32 ZERO = 0U;                     // 0值
            static const UINT32 ONE = 1U;                      // 1值

            // 编解码模块相关字符串
            static PCSTR PN_PTR_LOG_OBJECT = "ptrLogObject";
            static PCSTR PN_BA_MESSAGE_DATA = "baMsgData";
            static PCSTR PN_INT_MESSAGE_TYPE = "intMsgType";
            static PCSTR PN_PTR_GNSS_DATA_OBJECT = "ptrGnssDataObj";
            static PCSTR PN_INT_NAVI_SYSTEM = "intNaviSystem";
            static PCSTR PN_INT_DNSS_DATA_TYPE = "intDnssDataType";
            static PCSTR PN_INT_CMD_CODE = "intCmdCode";
            static PCSTR PN_INT_STATUS = "intStatus";
            static PCSTR PN_STR_ERR_INF = "strErrInf";
            static PCSTR PN_STR_CONFIG_FILE = "strConfig";
            static PCSTR PN_STR_LOG_FILE_NAME = "strLogFileName";
            static PCSTR PN_INT_LOG_LEVEL = "intLogLevel";
            static PCSTR PN_INT_LOG_FILE_NUM = "intLogFileNum";
            static PCSTR PN_INT_LOG_MAX_SIZE = "intLogMaxSizeMb";

            static PCSTR STR_DEFAULT_CONFIG_NAME = "./SixentsRtcm.ini"; // 默认配置文件名

            // RtcmCmd 命令码
            static const UINT32 CMD_SET_LOG = 01;
            static const UINT32 CMD_GET_LOG = 02;

            // 解码相关
            static const DOUBLE SCALE_1E_1 = 0.1;
            static const DOUBLE SCALE_1E_2 = 0.01;
            static const DOUBLE SCALE_1E_3 = 0.001;
            static const DOUBLE SCALE_1E_4 = 0.0001;
            static const UINT32 MAX_SATELLITE_NUM = 64;
            static const UINT32 MAX_SIGNAL_NUM = 32;
            static const UINT32 MAX_CELL_NUM = 64;

            // 缺省值
            static PCSTR MSG_DATA_DEFAULT_VALUE = "0";          // 数据缺省值
            static const INT8 BUFFER_DEFAULT_VALUE = '0';       // buffer填充缺省值
            static PCSTR TIME_FORMAT_DEF = "%Y-%m-%d %H:%M:%S"; //  时间的缺省格式
            static PCSTR MSG_1005_ARP_ECEF_X_STR = "ArpEcefX";  // x坐标
            static PCSTR MSG_1005_ARP_ECEF_Y_STR = "ArpEcefY";  // y坐标
            static PCSTR MSG_1005_ARP_ECEF_Z_STR = "ArpEcefZ";  // z坐标
            static PCSTR STATION_ID_STR = "StationId";          // 参考站id

            // 配置相关
            static PCSTR STR_CONFIG_LOG_LEVEL = "Log::Level";
            static PCSTR STR_CONFIG_LOG_MAX_FILE_NUM = "Log::MaxFileNum";
            static PCSTR STR_CONFIG_LOG_FILE_MAX_SIZE = "Log::FileMaxSize";
            static PCSTR STR_CONFIG_LOG_FILE_NAME = "Log::FileName";

            static const std::map< std::string, std::string > MAP_CONFIG_DEF{
                {STR_CONFIG_LOG_LEVEL, "23"},
                {STR_CONFIG_LOG_MAX_FILE_NUM, "3"},
                {STR_CONFIG_LOG_FILE_MAX_SIZE, "10"},
                {STR_CONFIG_LOG_FILE_NAME, "./rtcm.log"},
            };

            const INT32 MAX_SECTION = 260;       // Section最大长度
            const INT32 MAX_KEY = 65535;         // KeyValues最大长度
            const INT32 MAX_ALLSECTIONS = 65535; // 所有Section的最大长度
            const INT32 MAX_ALLKEYS = 65535;     // 所有KeyValue的最大长度

            const UINT32 CCFG_MNG_VALUE_1 = 1U; // 消除魔鬼数字

            const std::string SEC_KEY_DIVISION("::"); // 用于在Value中的名字分为Section名以及Key名
            const std::string UNDEFINED_SECTION("UNDEFIND");
        } // namespace rtcm
    }     // namespace common
} // namespace sixents

#endif
