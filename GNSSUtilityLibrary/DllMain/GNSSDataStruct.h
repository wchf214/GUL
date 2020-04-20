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

#include <map>

namespace sixents
{
    namespace GNSSUtilityLib
    {
        /**
         * @class   : SSignalValue
         * @author  : zhuquanlin@sixents.com
         * @brief   : 信号数据结构体
         * @note    : 保存一颗卫星中一个信号的数据
         */
        struct SSignalValue
        {
            //  MSM 1-7 satellite data part
            // Signal Data
            // DF400: GNSS 信号精确伪距观测值
            double m_dbFinePseudoranges = 0.0;

            // DF401: GNSS 信号精确相位距离数据
            double m_dbFinePhaserange = 0.0;

            // DF402: GNSS 相位距离锁定时间标志，提供接收机连续锁定卫星信号的时间长度。
            unsigned char m_ui8LockTimeIndicator = 0U;

            // DF403: GNSS 信号CNR，提供卫星信号的载噪比，单位dB-Hz。DF403=0 表示数值未计算或不可用。
            double m_dbSignalCnr = 0.0;

            // DF404: GNSS 信号精确相位距离变化率
            // FP means FinePhaserange
            double m_dbFPRates = 0.0;

            // DF405: 具有扩展分辨率的GNSS 信号精确伪距值
            // ER means ExtendedResolution
            double m_dbFinePseudorangesWithER = 0.0;

            // DF406: 具有扩展分辨率的GNSS 信号精确相位距离
            // ER means ExtendedResolution
            double m_dbFinePhaserangeWithER = 0.0;

            // DF407: 具有扩展范围和分辨率的GNSS 相位距离时间锁定标志
            // PLTI means PhaserangeLockTimeIndicator
            // ERAR means WithExtendedRangeAndResolution
            unsigned short m_ui16PLTIWithERAR = 0U;

            // DF408: 具有扩展分辨率的GNSS 信号信噪比
            // WER means WithExtendedResolution
            double m_dbSignalCnrsWER = 0.0;

            // DF420: 半周模糊度指标，0=没有半周模糊度；1=半周模糊度。
            // HCAI means HalfCycleAmbiguityIndicator
            unsigned char m_ui8HCAI = 0U;

            // DF010 : GPS L1 码标志
            // DF010 : GPS L1 Code Indicator
            // DF039 : GLONASS L1 码标志
            // DF030 : GLONASS L1 Code Indicator
            // DF016 : GPS L2 码标志
            // DF016 : GPS L2 Code Indicator
            // DF046 : GLONASS L2 码标志
            // DF046 : GLONASS L2 Code Indicator
            unsigned char m_ui8CodeMark = 0U;

            // 对于标准精度电文（MSM1~MSM3），有：
            // Pseudorange(i) = c / 1000 ×(Nms + Rough_range + Fine_Pseudorange(i))
            // PhaseRange(i) = c / 1000 ×(Nms + Rough_range + Fine_PhaseRange(i))
            // PhaseRangeRate(i) = Rough_PhaseRangeRate + Fine_PhaseRangeRate(i)
            // 对于高精度电文（MSM4~MSM7），有：
            // Pseudorange(i) = c / 1000 ×(Nms + Rough_range + Fine_Pseudorange(i))
            // PhaseRange(i) = c / 1000 ×(Nms + Rough_range + Fine_PhaseRange(i))
            // PhaseRangeRate(i) = Rough_PhaseRangeRate + Fine_PhaseRangeRate(i)
            // GNSS 计算后信号精确伪距
            double m_dbPseudoranges = 0.0;

            // GNSS 计算后信号精确相位距离
            double m_dbPhaserange = 0.0;

            // GNSS 计算后信号精确相位距离变化率
            double m_dbPhaseRangeRate = 0.0;
        };

        /**
         * @class   : SSatelliteValue
         * @author  : zhuquanlin@sixents.com
         * @brief   : 卫星数据结构体（包含信号数据）
         * @note    : 保存观测值每颗卫星的数据
         */
        struct SSatelliteValue
        {
            // Satellite Data
            // DF397: GNSS 卫星概略距离的整毫秒数，用于恢复某颗卫星的完整观测值。
            unsigned char m_ui8Milliseconds = 0U;

            // 扩展卫星信息
            unsigned char m_ui8ExtendedSatInfo = 0U;

            // DF398: GNSS 卫星概略距离的毫秒余数，可以1/1024ms（约300m）的精度恢复完整的GNSS概略距离
            double m_dbModulo1Millisecond = 0.0;

            // DF399: GNSS 卫星概略相位距离变化率
            int m_i32RoughPhaseRangeRates = 0U;

            // DF040: GLONASS 卫星的频率通道号。通过 DF038 和 DF040，用户无需历书就可知道卫星的频率。
            // 注意编码时这个值需要从1020取值（1087扩展信息DF419） Glonass专用
            // 注意Glonass编码时必须赋值, 否则编码失败
            unsigned char m_ui8SatFrequencyChannelNumber = 255;

            std::map< int, SSignalValue > m_mapSignalValues;
        };

        /**
         * @class   : SEpochSatObs
         * @author  : zhuquanlin@sixents.com
         * @brief   : 观测值数据结构体
         * @note    : 保存观测值所有数据
         */
        struct SEpochSatObs
        {
            // MSM 1-7  head part
            // DF002: 电文类型号,用于区分差分电文。
            unsigned short m_ui16MsgType = 0U;

            // DF003: 参考站 ID 由服务提供者确定。
            unsigned int m_ui32GmNtiRefStationID = 0U;
            // DF416: GLONASS 卫星导航电文和信号的星期数
            unsigned char m_ui8DayOfWeek = 0U;

            // GNSS 历元时刻：GPS DF004
            // GNSS 历元时刻：Galileo DF248
            // GNSS 历元时刻：Glonass DF034
            // GNSS 历元时刻：SBAS DF004
            // GNSS 历元时刻：QZSS DF428
            // GNSS 历元时刻：BeiDou DF427
            unsigned int m_ui32GnssEpochTime = 0U;

            // DF005: 同步GNSS电文标志
            // DF393: MSM 后续电文情况：1 = 还有相对给定时刻与参考站ID 的更多电文；0 = 本条电文时给定时刻与参考站ID
            // 的最后一条。
            unsigned char m_ui8MultiMsgBit = 0U;

            // DF409: 表示测站数据期卷号（Issue Of Data
            // Station），为保留字段，用于将MSM与今后的测站说明（接收机、天线说明等）联系起来。DF409 = 0
            // 表示未使用本数据字段。
            unsigned char m_ui8IODS = 0U;

            // DF001: 预留数据，保留7位
            signed char m_i8Reserved = 0U;

            // DF411: 时钟校准标志，表示时钟校准的情况。
            //  0 = 未使用时钟校准，此时，接收机钟差必须保持小于±1ms（约±300km）；
            //  1 = 使用了时钟校准，此时，接收机钟差必须保持小于±1 微秒（约±300m）；
            //  2 = 未知的时钟校准状态；
            //  3 = 保留。
            unsigned char m_ui8ClockSteeringIndicator = 0U;

            // DF412: 扩展时钟标志，表示时钟校准的情况。
            //  0 = 使用内部时钟；
            //  1 = 使用外部时钟，状态为“锁定”；
            //  2 = 使用外部时钟，状态为“未锁定”，表示外部时钟失效，传输的数据可能不可靠；
            //  3 = 使用时钟状态未知。
            unsigned char m_ui8ExternalClockIndicator = 0U;

            // DF007: GPS 无弥散平滑标志
            // DF036: GLONASS 无弥散平滑标志
            // DF417: GNSS 平滑类型标志，1=使用非无弥散平滑；0=其他平滑类型。
            unsigned char m_ui8GnssSmoothingIndicator = 0U;

            // DF008: GPS 平滑间隔
            // DF037: GLONASS 平滑间隔
            // DF418: GNSS 平滑区间，指使用载波平滑伪距的时段长度。
            unsigned char m_ui8GnssSmoothingInterval = 0U;

            // DF394: 卫星掩码
            unsigned long long m_ui64SatMask = 0U;

            // DF395: 信号掩码
            unsigned int m_ui32SignalMask = 0U;

            // DF396: 单元掩码
            unsigned long long m_ui64CellMask = 0U;

            std::map< int, SSatelliteValue > m_mapSatValues;
        };

        /**
         * @class   : SEphemeris
         * @author  : wuchuanfei@sixents.com
         * @brief   : 星历数据结构体
         * @note    : 保存星历所有数据
         */
        struct SEphemeris
        {
            // DF002: 电文类型号,用于区分差分电文。
            unsigned short m_ui16MsgType = 0U;

            // DF009: GPS卫星号
            // DF252: Galileo卫星号
            // DF429: QZSS卫星 ID
            // DF488: BDS 卫星号
            unsigned char m_ui8SatId = 0U;

            // DF076: GPS周数,起算于1980 年1 月5 日子夜，每1024 周一个循环。
            // DF289: Galileo周数，每4096周（约78年）一个循环。GST在OS-SIS-ICD-1.1中定义，开始于 1999 年 8 月 22 日星期日
            // 00:00UT（8 月 21 日和 8 月 22 日之间的午夜）。
            // DF452: QZSS星期数，循环周期为1024 周。起始于1980 年1 月5 号晚上的午夜 / 1 月6 号的早上。
            // DF489: Roll-over every 8192 weeks starting from 00:00:00 UTC on Jan. 1,2006 of BDT.
            unsigned char m_ui16WeekNum = 0U;

            // DF077: GPS卫星的用户等效距离精度，单位m
            // DF453: QZSS星历的精度，无单位。
            // DF490: BDS卫星的用户距离精度（URA）指数，无单位，
            unsigned char m_ui8URA = 0U;

            // DF078: GPS测距码标志,表示所观测的GPS L2 测距码类型。00=保留；01=P 码；10=C/A 码；11 = L2C 码。
            // DF451: QZSS卫星L2测距码类型
            unsigned char m_ui8CodeOnL2 = 0U;

            // DF079: GPS卫星轨道倾角变化率
            // DF292: Galileo卫星轨道倾角变化率
            // DF449: QZSS卫星轨道倾角变化率
            // DF491: BDS 卫星轨道倾角变化率
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π/s) 已经转换成常用模式(单位:deg/s)
            // 单位：deg/s
            double m_dbIdot = 0.0;

            // DF071: GPS来自广播星历，表示卫星星历数据期号
            // DF434： QZSS 卫星星历期卷号，无单位。
            unsigned char m_ui8Iode = 0U;

            // DF081: GPS卫星钟参考时刻，单位s。
            // DF293: Galileo卫星钟参考时间。
            // DF430: QZZS卫星钟参数参考时刻
            // DF493: BDS 卫星钟数据参考时刻，单位s。
            unsigned int m_ui32Toc = 0U;

            // DF082: GPS卫星钟钟漂改正参数，单位s/s2。
            // DF294: Galileo卫星钟漂改正参数，单位 s/s 2 。
            // DF431: QZSS卫星钟钟漂改正参数，单位 s/s 2 。
            // DF494: BDS卫星钟钟漂改正参数，单位 s/s 2 。
            double m_dbAf2 = 0.0;

            // DF083: GPS卫星钟钟速改正参数，单位s/s。
            // DF295: Galileo卫星钟速改正参数，单位 s/s。
            // DF432: QZSS卫星钟钟速改正参数，单位 s/s。
            // DF495: BDS卫星钟钟速改正参数，单位 s/s。
            double m_dbAf1 = 0.0;

            // DF084: GPS卫星钟钟差改正参数，单位s。
            // DF296: Galileo卫星钟差改正参数，单位 s。
            // DF433: QZSS卫星钟钟差改正参数，单位 s。
            // DF496: BDS卫星钟钟速改正参数，单位 s/s。
            double m_dbAf0 = 0.0;

            // DF085: 表示卫星钟参数期卷号，低8 位与IODE 相同。
            // DF456:  QZSS 卫星钟参数期卷号，同一组数据中 DF456 的低 8 位与 QZSSIODE(DF434)相同。与 GPS IODC 不同的是，QZSS
            // IODC 的最高 2 位是 SV 时钟参数的计数器，每 15min 变更一次。单位：无单位
            unsigned char m_ui16Iodc = 0U;

            // DF086: GPS卫星轨道半径正弦调和改正项的振幅，单位m。
            // DF297: Galileo卫星轨道半径正弦调和改正项的振幅，单位 m。
            // DF435: QZSS卫星轨道半径正弦调和改正项的振幅，单位 m。
            // DF498: BDS卫星轨道半径正弦调和改正项的振幅，单位 m。
            double m_dbCrs = 0.0;

            // DF087: GPS卫星平均运动速率与计算值之差
            // DF298: Galileo卫星平均运动速率与计算值之差
            // DF436: QZSS卫星平均运动速率与计算值之差
            // DF499: BDS卫星平均运动速率与计算值之差
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π/s) 已经转换成常用模式(单位:deg/s)
            // 单位：deg/s
            double m_dbDeltaN = 0.0;

            // DF088: GPS卫星参考时间的平近点角，单位π。
            // DF299: Galileo卫星参考时间的平近点角，单位 π。
            // DF437: QZSS卫星参考时间的平近点角，单位 π。
            // DF500: BDS卫星参考时间的平近点角，单位 π。
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
            // 单位：deg
            double m_dbM0 = 0.0;

            // DF089: GPS卫星纬度幅角的余弦调和改正项的振幅，单位rad。
            // DF300: Galileo卫星纬度幅角的余弦调和改正项的振幅，单位 rad。
            // DF438: QZSS卫星纬度幅角的余弦调和改正项的振幅，单位 rad。
            // DF501: BDS卫星纬度幅角的余弦调和改正项的振幅，单位 rad。
            double m_dbCuc = 0.0;

            // DF090: GPS卫星轨道偏心率，无单位。
            // DF301: Galileo卫星轨道偏心率，无单位。
            // DF439: QZSS卫星轨道偏心率，无单位。
            // DF502: BDS卫星轨道偏心率，无单位。
            double m_dbEccentricity = 0.0;

            // DF091: GPS卫星纬度幅角的正弦调和改正项的振幅，单位rad。
            // DF302: Galileo卫星纬度幅角的正弦调和改正项的振幅，单位 rad。
            // DF440: QZSS卫星纬度幅角的正弦调和改正项的振幅，单位 rad。
            // DF503: BDS卫星纬度幅角的正弦调和改正项的振幅，单位 rad。
            double m_dbCus = 0.0;

            // DF092: GPS卫星轨道长半轴的平方根。
            // DF303: Galileo卫星轨道长半轴的平方根 。
            // DF441: QZSS卫星轨道长半轴与 42,164,200m 之差的平方根。
            // DF504: BDS卫星轨道长半轴与 42,164,200m 之差的平方根。
            // 参考RTCM STANDARD 10403.3数据单位:m1/2 需要转换成常用模式单位:m 转换方式是value * value
            double m_dbAHalf = 0.0;

            // DF093: GPS卫星星历参考时间，单位s。
            // DF304: Galileo卫星星历参考时间。
            // DF442: QZSS卫星星历参考时间，单位 s。
            // DF505: BDS卫星星历参考时间，单位 s。
            unsigned int m_ui32Toe = 0U;

            // DF094: GPS卫星轨道倾角的余弦调和改正项的振幅，单位rad。
            // DF305: Galileo卫星轨道倾角的余弦调和改正项的振幅，单位 rad。
            // DF443: QZSS卫星轨道倾角的余弦调和改正项的振幅，单位 rad。
            // DF506: BDS卫星轨道倾角的余弦调和改正项的振幅，单位 rad。
            double m_dbCic = 0.0;

            // DF095: GPS卫星按参考时间计算的升交点赤经
            // DF306: Galileo卫星按参考时间计算的升交点赤经
            // DF444: QZSS卫星按参考时间计算的升交点赤经
            // DF507: BDS卫星按参考时间计算的升交点赤经
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
            // 单位：deg
            double m_dbOmega0 = 0.0;

            // DF096: GPS卫星轨道倾角的正弦调和改正项的振幅，单位rad。
            // DF307: Galileo卫星轨道倾角的正弦调和改正项的振幅，单位 rad。
            // DF445: QZSS卫星轨道倾角的正弦调和改正项的振幅，单位 rad。
            // DF508: BDS卫星轨道倾角的正弦调和改正项的振幅，单位 rad。
            double m_dbCis = 0.0;

            // DF097: GPS卫星参考时间的轨道倾角
            // DF308: Galileo卫星参考时间的轨道倾角
            // DF446: QZSS卫星参考时间的轨道倾角
            // DF509: BDS卫星参考时间的轨道倾角
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
            // 单位：deg
            double m_dbI0 = 0.0;

            // DF098: GPS卫星轨道半径的余弦调和改正项的振幅，单位m。
            // DF309: Galileo卫星轨道半径的余弦调和改正项的振幅，单位 m。
            // DF447: QZSS卫星轨道半径的余弦调和改正项的振幅，单位 m。
            // DF510: BDS卫星轨道半径的余弦调和改正项的振幅，单位 m。
            double m_dbCrc = 0.0;

            // DF099: GPS卫星近地点幅角
            // DF310: Galileo卫星近地点幅角
            // DF448: QZSS卫星近地点幅角
            // DF511: BDS卫星近地点幅角
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
            // 单位：deg
            double m_dbArgumentOfPerigee = 0.0;

            // DF100: GPS卫星升交点赤经变化率
            // DF311: Galileo卫星升交点赤经变化率
            // DF449: QZSS卫星升交点赤经变化率
            // DF512: BDS卫星升交点赤经变化率
            // 参考RTCM STANDARD 10403.3解码后的数据(单位:π/s) 已经转换成常用模式(单位:deg/s)
            // 单位：deg/s
            double m_dbOmegaDot = 0.0;

            // DF450:  QZSS 卫星轨道倾角变化率，单位 π/s
            double m_dbIODot = 0.0;

            // DF101: 表示卫星L1 和L2 信号频率的群延迟差，单位s。
            // DF455:  LCQZSS 和 L1 C/A 码群延迟，单位 s。LCQZSS 是 QZSS L1 C/A 和L2C 信号无电离层线性组合信号。
            double m_dbTgd = 0.0;

            // DF102: GPS0卫星健康状态，0=所有导航数据正常；1=某些或所有导航数据不正常。
            // DF454: QZSS卫星健康状态，DF454 每个比特位代表一个卫星信号，其状态表示对应信号的可用性，最高位(MSB)：0 =
            // 所有导航数据正常，1 = 部分或者所有导航数据有问题。
            // DF515: 表示BDS卫星健康信息，0=所有导航数据正常；1=某些或所有导航数据不正常。
            unsigned char m_ui8SvHealth = 0U;

            // DF103: 取自导航电文子帧1，第4 字，第1 位，含义如下：0 = L2 P 码导航电文可用；1 = L2 P 码导航电文不可用。
            unsigned char m_ui8L2PDataFlag = 0U;

            // DF137: 代表导航电文子帧2 第10 字的第17 位。0 = 曲线拟合间隔为4 小时；1 = 曲线拟合间隔大于4 小时。
            // DF457: 表示数据拟合间隔。DF457=0 表示拟合间隔为 2h，DF457=1 表示拟合间隔大于 2h
            unsigned char m_ui8FitInterval = 0U;

            // DF286 Galileo SISA Index (E1,E5b)
            unsigned char m_ui8SISAIndex = 0U;
            // DF290: Galileo导航数据的期卷号，无单位。
            unsigned char m_ui16IODnav = 0U;
            // DF291: Galileo卫星的 SIS 精度，在 Galileo OS-SIS-ICD-1.1 中定义了该保留字段，但未定义数据内容。
            unsigned char m_ui8SvSisa = 0U;
            // DF312: Galileo卫星 E1/E5a 播发群延迟，单位 s。
            double m_dbBgdE1E5a = 0.0;
            // DF313: Galileo 卫星 E5b/E1 播发群延迟，单位 s。
            double m_dbBgdE5bE1 = 0.0;
            // DF314: Galileo卫星 E5a 信号健康状况：0 = 信号健康；1 = 信号不可用；2 = 信号处于测试中。
            unsigned char m_ui8OSHS = 0U;
            // DF315: Galileo卫星 E5a 上导航数据的有效性状态，用于告诉用户卫星数据的性能水平（例如，卫星不可用）。
            unsigned char m_ui8OSDVS = 0U;
            // DF316: The E5b Signal Health Status Bit Values are:
            // 0 - Signal OK
            // 1 - Signal out of service
            // 2 - Signal will be out of service
            // 3- Signal Component currently in Test
            unsigned char m_ui8E5bSignalHealthStatus = 0U;
            // DF317 Galileo SOL NAV Data Validity Status
            unsigned char m_ui8E5bDataValidityStatus = 0U;
            // 287 Galileo E1-B Signal Health Status
            unsigned char m_ui8E1bSignalHealthStatus = 0U;
            // 288 Galileo E1-B  Data Validity Status
            unsigned char m_ui8E1bDataValidityStatus = 0U;

            // DF492: BDS卫星星历数据龄期
            unsigned char m_ui8AgeOfDataEphemeris = 0U;
            // DF497: BDS 卫星钟时钟数据龄期，无单位。
            unsigned char m_ui8AgeOfDataClock = 0U;
            // DF513: BDS卫星B1I 星上设备时延差，单位ns。
            double m_dbTgd1 = 0.0;
            // DF514:BDS卫星B2I 星上设备时延差，单位ns。
            double m_dbTgd2 = 0.0;
            // Reserved
            unsigned char m_ui8Reserved = 0U;
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
            unsigned char m_ui16MsgType = 0U;
            // DF038: GLONASS 的卫星星位号。
            unsigned char m_ui8SatId = 0U;
            // DF040: GLONASS 卫星的频率通道号。通过 DF038 和 DF040，用户无需历书就可知道卫星的频率。
            unsigned char m_ui8SatFrequencyChannelNumber = 0U;
            // DF104: GLONASS 历书健康状况
            unsigned char m_ui8AlmanacHealth = 0U;
            // DF105: 历书健康状况可用性标志
            // AHAI means AlmanacHealthAvailabilityIndicator
            unsigned char m_ui8AHAI = 0U;
            // DF106: GLONASS P1 字
            unsigned char m_ui8P1 = 0U;
            // DF107:当天 GLONASS子帧的起点为零点的时间。(bits 11 - 7 : 0 - 23 bits 6 - 1 : 0 - 59 bit 0 : 0 - 1)
            unsigned char m_ui16Tk = 0U;
            // DF108: 星历健康状况标志。
            unsigned char m_ui8MsbOfBn = 0U;
            // DF109 : P2 码可用性。
            unsigned char m_ui8P2 = 0U;
            // DF110: GLONASS 导航数据的参考时间。(单位:15min)
            unsigned char m_ui16Tb = 0U;
            // DF111: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 X 分量
            double m_dbXnTbFirstDerivative = 0.0;
            // DF112: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 X 分量
            double m_dbXnTb = 0.0;
            // DF113: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 X 分量
            double m_dbXnTbSecondDerivative = 0.0;
            // DF114: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Y 分量
            double m_dbYnTbFirstDerivative = 0.0;
            // DF115: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Y 分量
            double m_dbYnTb = 0.0;
            // DF116: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Y 分量
            double m_dbYnTbSecondDerivative = 0.0;
            // DF117: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Z 分量
            double m_dbZnTbFirstDerivative = 0.0;
            // DF118: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Z 分量
            double m_dbZnTb = 0.0;
            // DF119: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Z 分量
            double m_dbZnTbSecondDerivative = 0.0;
            // DF120: 表示 P3 码可用性。
            unsigned char m_ui8P3 = 0U;
            // DF121: 是预计的 GLONASS 卫星载波频率导数（相对于名义值）。
            double m_dbGammaTb = 0.0;
            // DF122: GLONASS M 卫星的 P 码标志。
            unsigned char m_ui8GmP = 0U;
            // DF123: GLONASS 导航电文子帧的第三个字符串中提取出 l n 字。
            unsigned char m_ui8GmLn3 = 0U;
            // DF124: 相对 GLONASS 系统时间的卫星时间改正。
            double m_dbTnTb = 0.0;
            // DF125: GLONASS L2 子带与 L1 子带中传输导航 RF 信号之间的时间差。
            double m_dbGmDeltaTn = 0.0;
            // DF126: GLONASS 导航数据的龄期。
            unsigned char m_ui8En = 0U;
            // DF127: GLONASS M 卫星的 P4 码标志。
            unsigned char m_ui8GmP4 = 0U;
            // DF128: Tb 时刻 GLONASS-M 卫星 URA 估计值
            unsigned char m_ui8GmFt = 0U;
            // DF129: 以四年为间隔的，从闰年的一月一日开始的 GLONASS 日历天数。如果 DF129 不为零，则其值是与参数 t b
            // 相应日历天数的计算值。
            unsigned char m_ui16GmNt = 0U;
            // DF130:  GLONASS 卫星类型。01 = GLONASS - M 卫星，所有 GLONASS - M 数据字段均有效；00 = 非 GLONASS - M
            // 卫星，所有 GLONASS - M 数据字段无效。
            unsigned char m_ui8GmM = 0U;
            // DF131: 表示电文中是否包含从子帧第五字符串提取出的 GLONASS 星历电文的其余参数（如
            // DF132~DF136）。这些参数不属于预定义的星历数据，但有助于定位与授时。1 = 电文中包含附加数据；0 = DF132~DF136
            // 无效，取值随机。 AOAD means AvailabilityOfAdditionalData
            unsigned char m_ui8AOAD = 0U;
            // DF132: 表示以四年为周期的，参数 τ C 所使用 GLONASS 日历天数。
            unsigned char m_ui16NA = 0U;
            // DF133: 表示以 N A 日起始时刻为参考的 GLONASS 系统时与 UTC（SU）之差。
            double m_dbTc = 0.0;
            // DF134: 表示从 1996 年开始的，以 4 年为周期的周期数。
            unsigned char m_ui8GmN4 = 0U;
            // DF135: 表示从子帧中第 5 个字符串中提取出的 GLONASS-M l n 字。
            double m_dbGmTGps = 0.0;
            // DF136: 表示从子帧中第 5 个字符串中提取出的 GLONASS-M l n 字。
            unsigned char m_ui8GmLn5 = 0U;
            // Reserved
            unsigned char m_ui8Reserved = 0U;
        };

        struct SStandardTime
        {
            int m_year;
            int m_month;
            int m_day;
            int m_hour;
            int m_minute;
            double m_seconde;
            int m_timeType;
        };

        struct SGNSSTime
        {
            int m_week;
            double m_secAndMsec;
            int m_satType;
        };

        // 大地坐标
        struct SBLH
        {
            double m_lon;
            double m_lat;
            double m_height;
        };

        // 空间直角坐标
        struct SXYZ
        {
            double m_x;
            double m_y;
            double m_z;
        };

        // 站心坐标
        struct SENU
        {
            double m_east;
            double m_north;
            double m_up;
        };
    } // end namespace GNSSUtilityLib
} // end namespace sixents

#endif