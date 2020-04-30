/**@file           CGNSSCoord
 *  @brief         坐标类
 *  @details       所有坐标相关的算法
 *  @author        wuchuanfei@sixens.com
 *  @date          2020/04/14
 *  @version       1.0
 *  @note          暂无
 *  @copyright     Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */
#ifndef _GNSS_DATA_STRUCT_H
#define _GNSS_DATA_STRUCT_H

namespace sixents
{
    namespace GNSSUtilityLib
    {
        // bool类型
        using BOOL_T = bool; // 注意此类型不能用vector<BOOL>

        // 有符号类型定义
        using INT8 = signed char; // 8位整型 用来代替char
        using INT16 = short;      // 16位整型 用来代替short
        using INT32 = int;        // 32位整型
        using INT64 = long long;  // 64位整型

        // 无符号类型定义
        using CHAR = char;                 // 8位符号 char
        using BYTE = unsigned char;        // 8位无符号整型 unsigned char 和 byte类型
        using UINT8 = unsigned char;       // 8位无符号整型 unsigned char 和 byte类型
        using WORD = unsigned short;       // 双字节
        using UINT16 = unsigned short;     // 双字节 同(WORD)
        using UINT32 = unsigned int;       // 32位无符号整型
        using UINT64 = unsigned long long; // 64位无符号整型

        // 浮点类型数据定义
        using FLOAT = float;   // 32位浮点数
        using DOUBLE = double; // 64位浮点数

        // 指针类型
        using PVOID = void*;       // 主要是用于CParam传输
        using PCSTR = const char*; // C类型的字符串处理

        /**
         * @class   : SEphemeris
         * @author  : wuchuanfei@sixents.com
         * @brief   : 星历数据结构体
         * @note    : 保存星历所有数据
         */
        struct SEphemeris
        {
            // DF002: 电文类型号,用于区分差分电文。
            UINT16 m_ui16MsgType = 0U;

            // DF009: GPS卫星号
            // DF252: Galileo卫星号
            // DF429: QZSS卫星 ID
            // DF488: BDS 卫星号
            UINT8 m_ui8SatId = 0U;

            // DF076: GPS周数,起算于1980 年1 月5 日子夜，每1024 周一个循环。
            // DF289: Galileo周数，每4096周（约78年）一个循环。GST在OS-SIS-ICD-1.1中定义，开始于 1999 年 8 月 22
            // 日星期日 00:00UT（8 月 21 日和 8 月 22 日之间的午夜）。 DF452: QZSS星期数，循环周期为1024 周。起始于1980
            // 年1 月5 号晚上的午夜 / 1 月6 号的早上。 DF489: Roll-over every 8192 weeks starting from 00:00:00 UTC on
            // Jan. 1,2006 of BDT.
            UINT16 m_ui16WeekNum = 0U;

            // DF077: GPS卫星的用户等效距离精度，单位m
            // DF453: QZSS星历的精度，无单位。
            // DF490: BDS卫星的用户距离精度（URA）指数，无单位，
            UINT8 m_ui8URA = 0U;

            // DF078: GPS测距码标志,表示所观测的GPS L2 测距码类型。00=保留；01=P 码；10=C/A 码；11 = L2C 码。
            // DF451: QZSS卫星L2测距码类型
            UINT8 m_ui8CodeOnL2 = 0U;

            // DF079: GPS卫星轨道倾角变化率
            // DF292: Galileo卫星轨道倾角变化率
            // DF449: QZSS卫星轨道倾角变化率
            // DF491: BDS 卫星轨道倾角变化率
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π/s) 已经转换成常用模式(单位:deg/s)
            // 单位：deg/s
            DOUBLE m_dbIdot = 0.0;

            // DF071: GPS来自广播星历，表示卫星星历数据期号
            // DF434： QZSS 卫星星历期卷号，无单位。
            UINT8 m_ui8Iode = 0U;

            // DF081: GPS卫星钟参考时刻，单位s。
            // DF293: Galileo卫星钟参考时间。
            // DF430: QZZS卫星钟参数参考时刻
            // DF493: BDS 卫星钟数据参考时刻，单位s。
            UINT32 m_ui32Toc = 0U;

            // DF082: GPS卫星钟钟漂改正参数，单位s/s2。
            // DF294: Galileo卫星钟漂改正参数，单位 s/s 2 。
            // DF431: QZSS卫星钟钟漂改正参数，单位 s/s 2 。
            // DF494: BDS卫星钟钟漂改正参数，单位 s/s 2 。
            DOUBLE m_dbAf2 = 0.0;

            // DF083: GPS卫星钟钟速改正参数，单位s/s。
            // DF295: Galileo卫星钟速改正参数，单位 s/s。
            // DF432: QZSS卫星钟钟速改正参数，单位 s/s。
            // DF495: BDS卫星钟钟速改正参数，单位 s/s。
            DOUBLE m_dbAf1 = 0.0;

            // DF084: GPS卫星钟钟差改正参数，单位s。
            // DF296: Galileo卫星钟差改正参数，单位 s。
            // DF433: QZSS卫星钟钟差改正参数，单位 s。
            // DF496: BDS卫星钟钟速改正参数，单位 s/s。
            DOUBLE m_dbAf0 = 0.0;

            // DF085: 表示卫星钟参数期卷号，低8 位与IODE 相同。
            // DF456:  QZSS 卫星钟参数期卷号，同一组数据中 DF456 的低 8 位与 QZSSIODE(DF434)相同。与 GPS IODC
            // 不同的是，QZSS IODC 的最高 2 位是 SV 时钟参数的计数器，每 15min 变更一次。单位：无单位
            UINT16 m_ui16Iodc = 0U;

            // DF086: GPS卫星轨道半径正弦调和改正项的振幅，单位m。
            // DF297: Galileo卫星轨道半径正弦调和改正项的振幅，单位 m。
            // DF435: QZSS卫星轨道半径正弦调和改正项的振幅，单位 m。
            // DF498: BDS卫星轨道半径正弦调和改正项的振幅，单位 m。
            DOUBLE m_dbCrs = 0.0;

            // DF087: GPS卫星平均运动速率与计算值之差
            // DF298: Galileo卫星平均运动速率与计算值之差
            // DF436: QZSS卫星平均运动速率与计算值之差
            // DF499: BDS卫星平均运动速率与计算值之差
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π/s) 已经转换成常用模式(单位:deg/s)
            // 单位：deg/s
            DOUBLE m_dbDeltaN = 0.0;

            // DF088: GPS卫星参考时间的平近点角，单位π。
            // DF299: Galileo卫星参考时间的平近点角，单位 π。
            // DF437: QZSS卫星参考时间的平近点角，单位 π。
            // DF500: BDS卫星参考时间的平近点角，单位 π。
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
            // 单位：deg
            DOUBLE m_dbM0 = 0.0;

            // DF089: GPS卫星纬度幅角的余弦调和改正项的振幅，单位rad。
            // DF300: Galileo卫星纬度幅角的余弦调和改正项的振幅，单位 rad。
            // DF438: QZSS卫星纬度幅角的余弦调和改正项的振幅，单位 rad。
            // DF501: BDS卫星纬度幅角的余弦调和改正项的振幅，单位 rad。
            DOUBLE m_dbCuc = 0.0;

            // DF090: GPS卫星轨道偏心率，无单位。
            // DF301: Galileo卫星轨道偏心率，无单位。
            // DF439: QZSS卫星轨道偏心率，无单位。
            // DF502: BDS卫星轨道偏心率，无单位。
            DOUBLE m_dbEccentricity = 0.0;

            // DF091: GPS卫星纬度幅角的正弦调和改正项的振幅，单位rad。
            // DF302: Galileo卫星纬度幅角的正弦调和改正项的振幅，单位 rad。
            // DF440: QZSS卫星纬度幅角的正弦调和改正项的振幅，单位 rad。
            // DF503: BDS卫星纬度幅角的正弦调和改正项的振幅，单位 rad。
            DOUBLE m_dbCus = 0.0;

            // DF092: GPS卫星轨道长半轴的平方根。
            // DF303: Galileo卫星轨道长半轴的平方根 。
            // DF441: QZSS卫星轨道长半轴与 42,164,200m 之差的平方根。
            // DF504: BDS卫星轨道长半轴与 42,164,200m 之差的平方根。
            // 参考RTCM STANDARD 10403.3数据单位:m1/2 需要转换成常用模式单位:m 转换方式是value * value
            DOUBLE m_dbAHalf = 0.0;

            // DF093: GPS卫星星历参考时间，单位s。
            // DF304: Galileo卫星星历参考时间。
            // DF442: QZSS卫星星历参考时间，单位 s。
            // DF505: BDS卫星星历参考时间，单位 s。
            UINT32 m_ui32Toe = 0U;

            // DF094: GPS卫星轨道倾角的余弦调和改正项的振幅，单位rad。
            // DF305: Galileo卫星轨道倾角的余弦调和改正项的振幅，单位 rad。
            // DF443: QZSS卫星轨道倾角的余弦调和改正项的振幅，单位 rad。
            // DF506: BDS卫星轨道倾角的余弦调和改正项的振幅，单位 rad。
            DOUBLE m_dbCic = 0.0;

            // DF095: GPS卫星按参考时间计算的升交点赤经
            // DF306: Galileo卫星按参考时间计算的升交点赤经
            // DF444: QZSS卫星按参考时间计算的升交点赤经
            // DF507: BDS卫星按参考时间计算的升交点赤经
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
            // 单位：deg
            DOUBLE m_dbOmega0 = 0.0;

            // DF096: GPS卫星轨道倾角的正弦调和改正项的振幅，单位rad。
            // DF307: Galileo卫星轨道倾角的正弦调和改正项的振幅，单位 rad。
            // DF445: QZSS卫星轨道倾角的正弦调和改正项的振幅，单位 rad。
            // DF508: BDS卫星轨道倾角的正弦调和改正项的振幅，单位 rad。
            DOUBLE m_dbCis = 0.0;

            // DF097: GPS卫星参考时间的轨道倾角
            // DF308: Galileo卫星参考时间的轨道倾角
            // DF446: QZSS卫星参考时间的轨道倾角
            // DF509: BDS卫星参考时间的轨道倾角
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
            // 单位：deg
            DOUBLE m_dbI0 = 0.0;

            // DF098: GPS卫星轨道半径的余弦调和改正项的振幅，单位m。
            // DF309: Galileo卫星轨道半径的余弦调和改正项的振幅，单位 m。
            // DF447: QZSS卫星轨道半径的余弦调和改正项的振幅，单位 m。
            // DF510: BDS卫星轨道半径的余弦调和改正项的振幅，单位 m。
            DOUBLE m_dbCrc = 0.0;

            // DF099: GPS卫星近地点幅角
            // DF310: Galileo卫星近地点幅角
            // DF448: QZSS卫星近地点幅角
            // DF511: BDS卫星近地点幅角
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
            // 单位：deg
            DOUBLE m_dbArgumentOfPerigee = 0.0;

            // DF100: GPS卫星升交点赤经变化率
            // DF311: Galileo卫星升交点赤经变化率
            // DF449: QZSS卫星升交点赤经变化率
            // DF512: BDS卫星升交点赤经变化率
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π/s) 已经转换成常用模式(单位:deg/s)
            // 单位：deg/s
            DOUBLE m_dbOmegaDot = 0.0;

            // DF450:  QZSS 卫星轨道倾角变化率，单位 π/s
            DOUBLE m_dbIODot = 0.0;

            // DF101: 表示卫星L1 和L2 信号频率的群延迟差，单位s。
            // DF455:  LCQZSS 和 L1 C/A 码群延迟，单位 s。LCQZSS 是 QZSS L1 C/A 和L2C 信号无电离层线性组合信号。
            DOUBLE m_dbTgd = 0.0;

            // DF102: GPS0卫星健康状态，0=所有导航数据正常；1=某些或所有导航数据不正常。
            // DF454: QZSS卫星健康状态，DF454 每个比特位代表一个卫星信号，其状态表示对应信号的可用性，最高位(MSB)：0 =
            // 所有导航数据正常，1 = 部分或者所有导航数据有问题。
            // DF515: 表示BDS卫星健康信息，0=所有导航数据正常；1=某些或所有导航数据不正常。
            UINT8 m_ui8SvHealth = 0U;

            // DF103: 取自导航电文子帧1，第4 字，第1 位，含义如下：0 = L2 P 码导航电文可用；1 = L2 P 码导航电文不可用。
            UINT8 m_ui8L2PDataFlag = 0U;

            // DF137: 代表导航电文子帧2 第10 字的第17 位。0 = 曲线拟合间隔为4 小时；1 = 曲线拟合间隔大于4 小时。
            // DF457: 表示数据拟合间隔。DF457=0 表示拟合间隔为 2h，DF457=1 表示拟合间隔大于 2h
            UINT8 m_ui8FitInterval = 0U;

            // DF286 Galileo SISA Index (E1,E5b)
            UINT8 m_ui8SISAIndex = 0U;
            // DF290: Galileo导航数据的期卷号，无单位。
            UINT16 m_ui16IODnav = 0U;
            // DF291: Galileo卫星的 SIS 精度，在 Galileo OS-SIS-ICD-1.1 中定义了该保留字段，但未定义数据内容。
            UINT8 m_ui8SvSisa = 0U;
            // DF312: Galileo卫星 E1/E5a 播发群延迟，单位 s。
            DOUBLE m_dbBgdE1E5a = 0.0;
            // DF313: Galileo 卫星 E5b/E1 播发群延迟，单位 s。
            DOUBLE m_dbBgdE5bE1 = 0.0;
            // DF314: Galileo卫星 E5a 信号健康状况：0 = 信号健康；1 = 信号不可用；2 = 信号处于测试中。
            UINT8 m_ui8OSHS = 0U;
            // DF315: Galileo卫星 E5a 上导航数据的有效性状态，用于告诉用户卫星数据的性能水平（例如，卫星不可用）。
            UINT8 m_ui8OSDVS = 0U;
            // DF316: The E5b Signal Health Status Bit Values are:
            // 0 - Signal OK
            // 1 - Signal out of service
            // 2 - Signal will be out of service
            // 3- Signal Component currently in Test
            UINT8 m_ui8E5bSignalHealthStatus = 0U;
            // DF317 Galileo SOL NAV Data Validity Status
            UINT8 m_ui8E5bDataValidityStatus = 0U;
            // 287 Galileo E1-B Signal Health Status
            UINT8 m_ui8E1bSignalHealthStatus = 0U;
            // 288 Galileo E1-B  Data Validity Status
            UINT8 m_ui8E1bDataValidityStatus = 0U;

            // DF492: BDS卫星星历数据龄期
            UINT8 m_ui8AgeOfDataEphemeris = 0U;
            // DF497: BDS 卫星钟时钟数据龄期，无单位。
            UINT8 m_ui8AgeOfDataClock = 0U;
            // DF513: BDS卫星B1I 星上设备时延差，单位ns。
            DOUBLE m_dbTgd1 = 0.0;
            // DF514:BDS卫星B2I 星上设备时延差，单位ns。
            DOUBLE m_dbTgd2 = 0.0;
            // Reserved
            UINT8 m_ui8Reserved = 0U;
        };

        /**
         * @class   : SGlonassEphemeris
         * @author  : wuchuanfei@sixents.com
         * @brief   : Glonass星历结构体
         * @note    : 保存Glonass星历所有
         */
        struct SGlonassEphemeris
        {
            // Contents of GLONASS Satellite Ephemeris Data, Message Type 1020
            // DF002: 电文类型号,用于区分差分电文。
            UINT16 m_ui16MsgType = 0U;
            // DF038: GLONASS 的卫星星位号。
            UINT8 m_ui8SatId = 0U;
            // DF040: GLONASS 卫星的频率通道号。通过 DF038 和 DF040，用户无需历书就可知道卫星的频率。
            UINT8 m_ui8SatFrequencyChannelNumber = 0U;
            // DF104: GLONASS 历书健康状况
            UINT8 m_ui8AlmanacHealth = 0U;
            // DF105: 历书健康状况可用性标志
            // AHAI means AlmanacHealthAvailabilityIndicator
            UINT8 m_ui8AHAI = 0U;
            // DF106: GLONASS P1 字
            UINT8 m_ui8P1 = 0U;
            // DF107:当天 GLONASS子帧的起点为零点的时间。(bits 11 - 7 : 0 - 23 bits 6 - 1 : 0 - 59 bit 0 : 0 - 1)
            UINT16 m_ui16Tk = 0U;
            // DF108: 星历健康状况标志。
            UINT8 m_ui8MsbOfBn = 0U;
            // DF109 : P2 码可用性。
            UINT8 m_ui8P2 = 0U;
            // DF110: GLONASS 导航数据的参考时间。(单位:15min)
            UINT16 m_ui16Tb = 0U;
            // DF111: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 X 分量
            DOUBLE m_dbXnTbFirstDerivative = 0.0;
            // DF112: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 X 分量
            DOUBLE m_dbXnTb = 0.0;
            // DF113: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 X 分量
            DOUBLE m_dbXnTbSecondDerivative = 0.0;
            // DF114: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Y 分量
            DOUBLE m_dbYnTbFirstDerivative = 0.0;
            // DF115: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Y 分量
            DOUBLE m_dbYnTb = 0.0;
            // DF116: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Y 分量
            DOUBLE m_dbYnTbSecondDerivative = 0.0;
            // DF117: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Z 分量
            DOUBLE m_dbZnTbFirstDerivative = 0.0;
            // DF118: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Z 分量
            DOUBLE m_dbZnTb = 0.0;
            // DF119: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Z 分量
            DOUBLE m_dbZnTbSecondDerivative = 0.0;
            // DF120: 表示 P3 码可用性。
            UINT8 m_ui8P3 = 0U;
            // DF121: 是预计的 GLONASS 卫星载波频率导数（相对于名义值）。
            DOUBLE m_dbGammaTb = 0.0;
            // DF122: GLONASS M 卫星的 P 码标志。
            UINT8 m_ui8GmP = 0U;
            // DF123: GLONASS 导航电文子帧的第三个字符串中提取出 l n 字。
            UINT8 m_ui8GmLn3 = 0U;
            // DF124: 相对 GLONASS 系统时间的卫星时间改正。
            DOUBLE m_dbTnTb = 0.0;
            // DF125: GLONASS L2 子带与 L1 子带中传输导航 RF 信号之间的时间差。
            DOUBLE m_dbGmDeltaTn = 0.0;
            // DF126: GLONASS 导航数据的龄期。
            UINT8 m_ui8En = 0U;
            // DF127: GLONASS M 卫星的 P4 码标志。
            UINT8 m_ui8GmP4 = 0U;
            // DF128: Tb 时刻 GLONASS-M 卫星 URA 估计值
            UINT8 m_ui8GmFt = 0U;
            // DF129: 以四年为间隔的，从闰年的一月一日开始的 GLONASS 日历天数。如果 DF129 不为零，则其值是与参数 t b
            // 相应日历天数的计算值。
            UINT16 m_ui16GmNt = 0U;
            // DF130:  GLONASS 卫星类型。01 = GLONASS - M 卫星，所有 GLONASS - M 数据字段均有效；00 = 非 GLONASS - M
            // 卫星，所有 GLONASS - M 数据字段无效。
            UINT8 m_ui8GmM = 0U;
            // DF131: 表示电文中是否包含从子帧第五字符串提取出的 GLONASS 星历电文的其余参数（如
            // DF132~DF136）。这些参数不属于预定义的星历数据，但有助于定位与授时。1 = 电文中包含附加数据；0 =
            // DF132~DF136 无效，取值随机。 AOAD means AvailabilityOfAdditionalData
            UINT8 m_ui8AOAD = 0U;
            // DF132: 表示以四年为周期的，参数 τ C 所使用 GLONASS 日历天数。
            UINT16 m_ui16NA = 0U;
            // DF133: 表示以 N A 日起始时刻为参考的 GLONASS 系统时与 UTC（SU）之差。
            DOUBLE m_dbTc = 0.0;
            // DF134: 表示从 1996 年开始的，以 4 年为周期的周期数。
            UINT8 m_ui8GmN4 = 0U;
            // DF135: 表示从子帧中第 5 个字符串中提取出的 GLONASS-M l n 字。
            DOUBLE m_dbGmTGps = 0.0;
            // DF136: 表示从子帧中第 5 个字符串中提取出的 GLONASS-M l n 字。
            UINT8 m_ui8GmLn5 = 0U;
            // Reserved
            UINT8 m_ui8Reserved = 0U;
        };

        /**
         *  @class       SStandardTime
         *  @brief       年月日时分秒的时间结构
         *  @author      wuchuanfei@sixents.com
         *  @note        秒精确到毫秒
         */
        struct SStandardTime
        {
            UINT32 m_year;     // 年
            UINT32 m_month;    // 月
            UINT32 m_day;      // 日
            UINT32 m_hour;     // 时
            UINT32 m_minute;   // 分
            DOUBLE m_second;   // 秒，精确度：3位小数（毫秒级）
            UINT32 m_timeType; // TYPE_TIME中支持的类型
        };

        /**
         *  @class       SGNSSTime
         *  @brief       周内秒的时间结构
         *  @author      wuchuanfei@sixents.com
         *  @note        秒精确到毫秒，目前仅支持GPS/BD/Galileo三种卫星系统
         */
        struct SGNSSTime
        {
            UINT64 m_week;       // 周
            DOUBLE m_secAndMsec; // 秒，精确度：3位小数（毫秒级）
            UINT32 m_timeType;   // TYPE_TIME中支持的类型
        };

        // 大地坐标
        struct SBLH
        {
            DOUBLE m_lon;    // 经度，精确度：11位小数
            DOUBLE m_lat;    // 纬度，精确度：11位小数
            DOUBLE m_height; // 高程，精确度：9位小数
        };

        // 空间直角坐标
        struct SXYZ
        {
            DOUBLE m_x; // x轴，精确度：9位小数
            DOUBLE m_y; // x轴，精确度：9位小数
            DOUBLE m_z; // x轴，精确度：9位小数
        };

        // 站心坐标
        struct SENU
        {
            DOUBLE m_east;  // 东，精确度：9位小数
            DOUBLE m_north; // 北，精确度：9位小数
            DOUBLE m_up;    // 天，精确度：9位小数
        };

        // 坐标系统结构定义
        struct SCoordData
        {
            DOUBLE m_a; // 地球长半轴，精确度：1位小数
            DOUBLE m_f; // 地球扁率，分母精确度：9位小数
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents

#endif