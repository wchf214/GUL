/**
 * @copyright Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd.
 *       All rights reserved.
 * @file     : IGnssDataInterface.h
 * @author   : zhuquanlin@sixents.com
 * @version  : 1.0
 * @date     : 2019/12/20 16:25
 * @brief    : 定义Gnss数据结构和对象
 * @details  : 定义了RTCM使用到全部17个结构体以及9个Gnss对象，所有电文原始数据都会保存到对应结构体中。
               数据结构体封装到Gnss对象中，用户可以通过对象提供的方法获取相对应的结构体数据。
 * @note
 *    change history:
 *    <2019/12/20>  | 1.0 | zhuquanlin | 创建初始版本
 */
#ifndef _IGNSS_DATA_CLASS_
#define _IGNSS_DATA_CLASS_

#include <array>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
#include "../Platform/BasicType.h"

#ifdef UNIT_TEST
#undef private
#undef protected
#define private public
#define protected public
#endif

namespace sixents
{
    constexpr INT32 MAX_SAT_ID = 64;
    constexpr INT32 MIN_SAT_ID = 1;

    /**
     * @class   : IGnssDataInterface
     * @author  : zhuquanlin@sixents.com
     * @brief   : Gnss对象接口类
     * @note    : Gnss数据对象都继承自IGnssDataInterface
     */
    class DLL_API IGnssDataInterface
    {
    public:
        enum GnssDataType
        {
            GDT_OBS = 0,     // 观测值类型
            GDT_EPH,         // 星历类型
            GDT_GLO_EPH,     // Glonass星历类型
            GDT_REF_INFO,    // 参考站类型
            GDT_ORBIT,       // 轨道改正参数类型
            GDT_CLOCK,       // 钟差改正参数类型
            GDT_ORBIT_CLOCK, // 轨道和钟差改正参数类型
            GDT_DCB,         // 码偏差参数类型
            GDT_URA,         // URA类型
            GDT_UNKNOW
        };

        enum SignalCode : UINT32
        {
            SC_REMOVE_MASK = 0x0000003fU,
            SC_GPS_MASK = 0x40000000U,
            SC_GLO_MASK = 0x20000000U,
            SC_GAL_MASK = 0x10000000U,
            SC_QZSS_MASK = 0x08000000U,
            SC_SBAS_MASK = 0x04000000U,
            SC_BDS_MASK = 0x02000000U,
            // GPS signal code
            SC_GPS_1C = 0x02U | SC_GPS_MASK, // 2
            SC_GPS_1P = 0x03U | SC_GPS_MASK, // 3
            SC_GPS_1W = 0x04U | SC_GPS_MASK, // 4
            SC_GPS_2C = 0x08U | SC_GPS_MASK, // 8
            SC_GPS_2P = 0x09U | SC_GPS_MASK, // 9
            SC_GPS_2W = 0x0AU | SC_GPS_MASK, // 10
            SC_GPS_2S = 0x0FU | SC_GPS_MASK, // 15
            SC_GPS_2L = 0x10U | SC_GPS_MASK, // 16
            SC_GPS_2X = 0x11U | SC_GPS_MASK, // 17
            SC_GPS_5I = 0x16U | SC_GPS_MASK, // 22
            SC_GPS_5Q = 0x17U | SC_GPS_MASK, // 23
            SC_GPS_5X = 0x18U | SC_GPS_MASK, // 24
            SC_GPS_1S = 0x1EU | SC_GPS_MASK, // 30
            SC_GPS_1L = 0x1FU | SC_GPS_MASK, // 31
            SC_GPS_1X = 0x20U | SC_GPS_MASK, // 32
            // GLONASS signal code
            SC_GLO_1C = 0x02U | SC_GLO_MASK, // 2
            SC_GLO_1P = 0x03U | SC_GLO_MASK, // 3
            SC_GLO_2C = 0x08U | SC_GLO_MASK, // 8
            SC_GLO_2P = 0x09U | SC_GLO_MASK, // 9
            // Galileo signal code
            SC_GAL_1C = 0x02U | SC_GAL_MASK, // 2
            SC_GAL_1A = 0x03U | SC_GAL_MASK, // 3
            SC_GAL_1B = 0x04U | SC_GAL_MASK, // 4
            SC_GAL_1X = 0x05U | SC_GAL_MASK, // 5
            SC_GAL_1Z = 0x06U | SC_GAL_MASK, // 6
            SC_GAL_6C = 0x08U | SC_GAL_MASK, // 8
            SC_GAL_6A = 0x09U | SC_GAL_MASK, // 9
            SC_GAL_6B = 0x0AU | SC_GAL_MASK, // 10
            SC_GAL_6X = 0x0BU | SC_GAL_MASK, // 11
            SC_GAL_6Z = 0x0CU | SC_GAL_MASK, // 12
            SC_GAL_7I = 0x0EU | SC_GAL_MASK, // 14
            SC_GAL_7Q = 0x0FU | SC_GAL_MASK, // 15
            SC_GAL_7X = 0x10U | SC_GAL_MASK, // 16
            SC_GAL_8I = 0x12U | SC_GAL_MASK, // 18
            SC_GAL_8Q = 0x13U | SC_GAL_MASK, // 19
            SC_GAL_8X = 0x14U | SC_GAL_MASK, // 20
            SC_GAL_5I = 0x16U | SC_GAL_MASK, // 22
            SC_GAL_5Q = 0x17U | SC_GAL_MASK, // 23
            SC_GAL_5X = 0x18U | SC_GAL_MASK, // 24
            // QZSS signal code
            SC_QZSS_1C = 0x02U | SC_QZSS_MASK, // 2
            SC_QZSS_6S = 0x09U | SC_QZSS_MASK, // 9
            SC_QZSS_6L = 0x0AU | SC_QZSS_MASK, // 10
            SC_QZSS_6X = 0x0BU | SC_QZSS_MASK, // 11
            SC_QZSS_2S = 0x0FU | SC_QZSS_MASK, // 15
            SC_QZSS_2L = 0x10U | SC_QZSS_MASK, // 16
            SC_QZSS_2X = 0x11U | SC_QZSS_MASK, // 17
            SC_QZSS_5I = 0x16U | SC_QZSS_MASK, // 22
            SC_QZSS_5Q = 0x17U | SC_QZSS_MASK, // 23
            SC_QZSS_5X = 0x18U | SC_QZSS_MASK, // 24
            SC_QZSS_1S = 0x1EU | SC_QZSS_MASK, // 30
            SC_QZSS_1L = 0x1FU | SC_QZSS_MASK, // 31
            SC_QZSS_1X = 0x20U | SC_QZSS_MASK, // 32
            // SBAS signal code
            SC_SBAS_1C = 0x02U | SC_SBAS_MASK, // 2
            SC_SBAS_5I = 0x16U | SC_SBAS_MASK, // 22
            SC_SBAS_5Q = 0x17U | SC_SBAS_MASK, // 23
            SC_SBAS_5X = 0x18U | SC_SBAS_MASK, // 24
            // BDS signal code
            SC_BDS_2I = 0x02U | SC_BDS_MASK, // 2
            SC_BDS_2Q = 0x03U | SC_BDS_MASK, // 3
            SC_BDS_2X = 0x04U | SC_BDS_MASK, // 4
            SC_BDS_6I = 0x08U | SC_BDS_MASK, // 8
            SC_BDS_6Q = 0x09U | SC_BDS_MASK, // 9
            SC_BDS_6X = 0x0AU | SC_BDS_MASK, // 10
            SC_BDS_7I = 0x0EU | SC_BDS_MASK, // 14
            SC_BDS_7Q = 0x0FU | SC_BDS_MASK, // 15
            SC_BDS_7X = 0x10U | SC_BDS_MASK  // 16
        };

        enum SatelliteSystem
        {
            SYS_NONE = 0x00, /* navigation system: none */
            SYS_GPS = 0x01,  /* navigation system: GPS */
            SYS_SBS = 0x02,  /* navigation system: SBAS */
            SYS_GLO = 0x04,  /* navigation system: GLONASS */
            SYS_GAL = 0x08,  /* navigation system: Galileo */
            SYS_QZS = 0x10,  /* navigation system: QZSS */
            SYS_CMP = 0x20,  /* navigation system: BeiDou */
            SYS_IRN = 0x40,  /* navigation system: IRNS */
            SYS_LEO = 0x80,  /* navigation system: LEO */
            SYS_ALL = 0xFF   /* navigation system: all */
        };

        /**
         * @brief      : IGnssDataInterface构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        IGnssDataInterface();

        /**
         * @brief      : IGnssDataInterface析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual ~IGnssDataInterface();

        /**
         * @brief      : 获取当前对象Gnss数据类型
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回Gnss数据类型
         * @retval     :
         *  GDT_OBS  观测值类型
         *  GDT_EPH 星历类型
         *  GDT_GLO_EPH Glonass星历类型
         *  GDT_REF_INFO 参考站类型
         *  GDT_ORBIT 轨道改正参数类型
         *  GDT_CLOCK 钟差改正参数类型
         *  GDT_ORBIT_CLOCK 轨道和钟差改正参数类型
         *  GDT_DCB 码偏差参数类型
         *  GDT_URA URA类型
         *  GDT_UNKNOW 异常类型
         * @note       : N/A
         */
        GnssDataType GetGnssDataType() const;

        /**
         * @brief      : 获取当前对象卫星系统
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回卫星系统
         * @retval     :
         *  SYS_NONE = 0x00, navigation system: none
         *  SYS_GPS = 0x01,  navigation system: GPS
         *  SYS_SBS = 0x02,  navigation system: SBAS
         *  SYS_GLO = 0x04,  navigation system: GLONASS
         *  SYS_GAL = 0x08,  navigation system: Galileo
         *  SYS_QZS = 0x10,  navigation system: QZSS
         *  SYS_CMP = 0x20,  navigation system: BeiDou
         *  SYS_IRN = 0x40,  navigation system: IRNS
         *  SYS_LEO = 0x80,  navigation system: LEO
         * @note : N / A
         */
        SatelliteSystem GetSatelliteSystemType() const;

        /**
         * @brief      : 设置卫星系统
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : enSatelliteSystem    设置的卫星系统
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */

        void SetSatelliteSystemType(const SatelliteSystem enSatelliteSystem);
        /**
         * @brief      : 获取对象名字
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回对象名字
         * @retval     : 名字字符串窜
         * @note       : N/A
         */
        std::string GetName() const;

        /**
         * @brief      : 设置对象名字
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : strName    设置的对象名字
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void SetName(const std::string& strName);

        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual void InitData() = 0;

    protected:
        // 数据对象名
        std::string m_strName;
        // 数据类型
        GnssDataType m_enDataType = GDT_UNKNOW;
        // 卫星系统类型
        SatelliteSystem m_enSatSys = SYS_NONE;
    };

    /**
     * @class   : SSignalValue
     * @author  : zhuquanlin@sixents.com
     * @brief   : 信号数据结构体
     * @note    : 保存一颗卫星中一个信号的数据
     */
    struct DLL_API SSignalValue
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();

        //  MSM 1-7 satellite data part
        // Signal Data
        // DF400: GNSS 信号精确伪距观测值
        sixents::DOUBLE m_dbFinePseudoranges = 0.0;

        // DF401: GNSS 信号精确相位距离数据
        sixents::DOUBLE m_dbFinePhaserange = 0.0;

        // DF402: GNSS 相位距离锁定时间标志，提供接收机连续锁定卫星信号的时间长度。
        sixents::UINT8 m_ui8LockTimeIndicator = 0U;

        // DF403: GNSS 信号CNR，提供卫星信号的载噪比，单位dB-Hz。DF403=0 表示数值未计算或不可用。
        sixents::DOUBLE m_dbSignalCnr = 0.0;

        // DF404: GNSS 信号精确相位距离变化率
        // FP means FinePhaserange
        sixents::DOUBLE m_dbFPRates = 0.0;

        // DF405: 具有扩展分辨率的GNSS 信号精确伪距值
        // ER means ExtendedResolution
        sixents::DOUBLE m_dbFinePseudorangesWithER = 0.0;

        // DF406: 具有扩展分辨率的GNSS 信号精确相位距离
        // ER means ExtendedResolution
        sixents::DOUBLE m_dbFinePhaserangeWithER = 0.0;

        // DF407: 具有扩展范围和分辨率的GNSS 相位距离时间锁定标志
        // PLTI means PhaserangeLockTimeIndicator
        // ERAR means WithExtendedRangeAndResolution
        sixents::UINT16 m_ui16PLTIWithERAR = 0U;

        // DF408: 具有扩展分辨率的GNSS 信号信噪比
        // WER means WithExtendedResolution
        sixents::DOUBLE m_dbSignalCnrsWER = 0.0;

        // DF420: 半周模糊度指标，0=没有半周模糊度；1=半周模糊度。
        // HCAI means HalfCycleAmbiguityIndicator
        sixents::UINT8 m_ui8HCAI = 0U;

        // DF010 : GPS L1 码标志
        // DF010 : GPS L1 Code Indicator
        // DF039 : GLONASS L1 码标志
        // DF030 : GLONASS L1 Code Indicator
        // DF016 : GPS L2 码标志
        // DF016 : GPS L2 Code Indicator
        // DF046 : GLONASS L2 码标志
        // DF046 : GLONASS L2 Code Indicator
        sixents::UINT8 m_ui8CodeMark = 0U;

        // 对于标准精度电文（MSM1~MSM3），有：
        // Pseudorange(i) = c / 1000 ×(Nms + Rough_range + Fine_Pseudorange(i))
        // PhaseRange(i) = c / 1000 ×(Nms + Rough_range + Fine_PhaseRange(i))
        // PhaseRangeRate(i) = Rough_PhaseRangeRate + Fine_PhaseRangeRate(i)
        // 对于高精度电文（MSM4~MSM7），有：
        // Pseudorange(i) = c / 1000 ×(Nms + Rough_range + Fine_Pseudorange(i))
        // PhaseRange(i) = c / 1000 ×(Nms + Rough_range + Fine_PhaseRange(i))
        // PhaseRangeRate(i) = Rough_PhaseRangeRate + Fine_PhaseRangeRate(i)
        // GNSS 计算后信号精确伪距
        sixents::DOUBLE m_dbPseudoranges = 0.0;

        // GNSS 计算后信号精确相位距离
        sixents::DOUBLE m_dbPhaserange = 0.0;

        // GNSS 计算后信号精确相位距离变化率
        sixents::DOUBLE m_dbPhaseRangeRate = 0.0;
    };

    /**
     * @class   : SSatelliteValue
     * @author  : zhuquanlin@sixents.com
     * @brief   : 卫星数据结构体（包含信号数据）
     * @note    : 保存观测值每颗卫星的数据
     */
    struct DLL_API SSatelliteValue
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // Satellite Data
        // DF397: GNSS 卫星概略距离的整毫秒数，用于恢复某颗卫星的完整观测值。
        sixents::UINT8 m_ui8Milliseconds = 0U;

        // 扩展卫星信息
        sixents::UINT8 m_ui8ExtendedSatInfo = 0U;

        // DF398: GNSS 卫星概略距离的毫秒余数，可以1/1024ms（约300m）的精度恢复完整的GNSS概略距离
        sixents::DOUBLE m_dbModulo1Millisecond = 0.0;

        // DF399: GNSS 卫星概略相位距离变化率
        sixents::INT32 m_i32RoughPhaseRangeRates = 0U;

        // DF040: GLONASS 卫星的频率通道号。通过 DF038 和 DF040，用户无需历书就可知道卫星的频率。
        // 注意编码时这个值需要从1020取值（1087扩展信息DF419） Glonass专用
        // 注意Glonass编码时必须赋值, 否则编码失败
        sixents::UINT8 m_ui8SatFrequencyChannelNumber = 255;

        std::map< INT32, SSignalValue > m_mapSignalValues;
    };

    /**
     * @class   : SEpochSatObs
     * @author  : zhuquanlin@sixents.com
     * @brief   : 观测值数据结构体
     * @note    : 保存观测值所有数据
     */
    struct DLL_API SEpochSatObs
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();

        // MSM 1-7  head part
        // DF002: 电文类型号,用于区分差分电文。
        sixents::UINT16 m_ui16MsgType = 0U;

        // DF003: 参考站 ID 由服务提供者确定。
        sixents::UINT32 m_ui32GmNtiRefStationID = 0U;
        // DF416: GLONASS 卫星导航电文和信号的星期数
        sixents::UINT8 m_ui8DayOfWeek = 0U;

        // GNSS 历元时刻：GPS DF004
        // GNSS 历元时刻：Galileo DF248
        // GNSS 历元时刻：Glonass DF034
        // GNSS 历元时刻：SBAS DF004
        // GNSS 历元时刻：QZSS DF428
        // GNSS 历元时刻：BeiDou DF427
        sixents::UINT32 m_ui32GnssEpochTime = 0U;

        // DF005: 同步GNSS电文标志
        // DF393: MSM 后续电文情况：1 = 还有相对给定时刻与参考站ID 的更多电文；0 = 本条电文时给定时刻与参考站ID
        // 的最后一条。
        sixents::UINT8 m_ui8MultiMsgBit = 0U;

        // DF409: 表示测站数据期卷号（Issue Of Data
        // Station），为保留字段，用于将MSM与今后的测站说明（接收机、天线说明等）联系起来。DF409 = 0
        // 表示未使用本数据字段。
        sixents::UINT8 m_ui8IODS = 0U;

        // DF001: 预留数据，保留7位
        sixents::INT8 m_i8Reserved = 0U;

        // DF411: 时钟校准标志，表示时钟校准的情况。
        //  0 = 未使用时钟校准，此时，接收机钟差必须保持小于±1ms（约±300km）；
        //  1 = 使用了时钟校准，此时，接收机钟差必须保持小于±1 微秒（约±300m）；
        //  2 = 未知的时钟校准状态；
        //  3 = 保留。
        sixents::UINT8 m_ui8ClockSteeringIndicator = 0U;

        // DF412: 扩展时钟标志，表示时钟校准的情况。
        //  0 = 使用内部时钟；
        //  1 = 使用外部时钟，状态为“锁定”；
        //  2 = 使用外部时钟，状态为“未锁定”，表示外部时钟失效，传输的数据可能不可靠；
        //  3 = 使用时钟状态未知。
        sixents::UINT8 m_ui8ExternalClockIndicator = 0U;

        // DF007: GPS 无弥散平滑标志
        // DF036: GLONASS 无弥散平滑标志
        // DF417: GNSS 平滑类型标志，1=使用非无弥散平滑；0=其他平滑类型。
        sixents::UINT8 m_ui8GnssSmoothingIndicator = 0U;

        // DF008: GPS 平滑间隔
        // DF037: GLONASS 平滑间隔
        // DF418: GNSS 平滑区间，指使用载波平滑伪距的时段长度。
        sixents::UINT8 m_ui8GnssSmoothingInterval = 0U;

        // DF394: 卫星掩码
        sixents::UINT64 m_ui64SatMask = 0U;

        // DF395: 信号掩码
        sixents::UINT32 m_ui32SignalMask = 0U;

        // DF396: 单元掩码
        sixents::UINT64 m_ui64CellMask = 0U;

        std::map< INT32, SSatelliteValue > m_mapSatValues;
    };

    /**
     * @class   : SEphemeris
     * @author  : zhuquanlin@sixents.com
     * @brief   : 星历数据结构体
     * @note    : 保存星历所有数据
     */
    struct DLL_API SEphemeris
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF002: 电文类型号,用于区分差分电文。
        sixents::UINT16 m_ui16MsgType = 0U;

        // DF009: GPS卫星号
        // DF252: Galileo卫星号
        // DF429: QZSS卫星 ID
        // DF488: BDS 卫星号
        sixents::UINT8 m_ui8SatId = 0U;

        // DF076: GPS周数,起算于1980 年1 月5 日子夜，每1024 周一个循环。
        // DF289: Galileo周数，每4096周（约78年）一个循环。GST在OS-SIS-ICD-1.1中定义，开始于 1999 年 8 月 22 日星期日
        // 00:00UT（8 月 21 日和 8 月 22 日之间的午夜）。
        // DF452: QZSS星期数，循环周期为1024 周。起始于1980 年1 月5 号晚上的午夜 / 1 月6 号的早上。
        // DF489: Roll-over every 8192 weeks starting from 00:00:00 UTC on Jan. 1,2006 of BDT.
        sixents::UINT16 m_ui16WeekNum = 0U;

        // DF077: GPS卫星的用户等效距离精度，单位m
        // DF453: QZSS星历的精度，无单位。
        // DF490: BDS卫星的用户距离精度（URA）指数，无单位，
        sixents::UINT8 m_ui8URA = 0U;

        // DF078: GPS测距码标志,表示所观测的GPS L2 测距码类型。00=保留；01=P 码；10=C/A 码；11 = L2C 码。
        // DF451: QZSS卫星L2测距码类型
        sixents::UINT8 m_ui8CodeOnL2 = 0U;

        // DF079: GPS卫星轨道倾角变化率
        // DF292: Galileo卫星轨道倾角变化率
        // DF449: QZSS卫星轨道倾角变化率
        // DF491: BDS 卫星轨道倾角变化率
        // 参考RTCM STANDARD 10403.3解码后的数据(单位:π/s) 已经转换成常用模式(单位:deg/s)
        // 单位：deg/s
        sixents::DOUBLE m_dbIdot = 0.0;

        // DF071: GPS来自广播星历，表示卫星星历数据期号
        // DF434： QZSS 卫星星历期卷号，无单位。
        sixents::UINT8 m_ui8Iode = 0U;

        // DF081: GPS卫星钟参考时刻，单位s。
        // DF293: Galileo卫星钟参考时间。
        // DF430: QZZS卫星钟参数参考时刻
        // DF493: BDS 卫星钟数据参考时刻，单位s。
        sixents::UINT32 m_ui32Toc = 0U;

        // DF082: GPS卫星钟钟漂改正参数，单位s/s2。
        // DF294: Galileo卫星钟漂改正参数，单位 s/s 2 。
        // DF431: QZSS卫星钟钟漂改正参数，单位 s/s 2 。
        // DF494: BDS卫星钟钟漂改正参数，单位 s/s 2 。
        sixents::DOUBLE m_dbAf2 = 0.0;

        // DF083: GPS卫星钟钟速改正参数，单位s/s。
        // DF295: Galileo卫星钟速改正参数，单位 s/s。
        // DF432: QZSS卫星钟钟速改正参数，单位 s/s。
        // DF495: BDS卫星钟钟速改正参数，单位 s/s。
        sixents::DOUBLE m_dbAf1 = 0.0;

        // DF084: GPS卫星钟钟差改正参数，单位s。
        // DF296: Galileo卫星钟差改正参数，单位 s。
        // DF433: QZSS卫星钟钟差改正参数，单位 s。
        // DF496: BDS卫星钟钟速改正参数，单位 s/s。
        sixents::DOUBLE m_dbAf0 = 0.0;

        // DF085: 表示卫星钟参数期卷号，低8 位与IODE 相同。
        // DF456:  QZSS 卫星钟参数期卷号，同一组数据中 DF456 的低 8 位与 QZSSIODE(DF434)相同。与 GPS IODC 不同的是，QZSS
        // IODC 的最高 2 位是 SV 时钟参数的计数器，每 15min 变更一次。单位：无单位
        sixents::UINT16 m_ui16Iodc = 0U;

        // DF086: GPS卫星轨道半径正弦调和改正项的振幅，单位m。
        // DF297: Galileo卫星轨道半径正弦调和改正项的振幅，单位 m。
        // DF435: QZSS卫星轨道半径正弦调和改正项的振幅，单位 m。
        // DF498: BDS卫星轨道半径正弦调和改正项的振幅，单位 m。
        sixents::DOUBLE m_dbCrs = 0.0;

        // DF087: GPS卫星平均运动速率与计算值之差
        // DF298: Galileo卫星平均运动速率与计算值之差
        // DF436: QZSS卫星平均运动速率与计算值之差
        // DF499: BDS卫星平均运动速率与计算值之差
        // 参考RTCM STANDARD 10403.3解码后的数据(单位:π/s) 已经转换成常用模式(单位:deg/s)
        // 单位：deg/s
        sixents::DOUBLE m_dbDeltaN = 0.0;

        // DF088: GPS卫星参考时间的平近点角，单位π。
        // DF299: Galileo卫星参考时间的平近点角，单位 π。
        // DF437: QZSS卫星参考时间的平近点角，单位 π。
        // DF500: BDS卫星参考时间的平近点角，单位 π。
        // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
        // 单位：deg
        sixents::DOUBLE m_dbM0 = 0.0;

        // DF089: GPS卫星纬度幅角的余弦调和改正项的振幅，单位rad。
        // DF300: Galileo卫星纬度幅角的余弦调和改正项的振幅，单位 rad。
        // DF438: QZSS卫星纬度幅角的余弦调和改正项的振幅，单位 rad。
        // DF501: BDS卫星纬度幅角的余弦调和改正项的振幅，单位 rad。
        sixents::DOUBLE m_dbCuc = 0.0;

        // DF090: GPS卫星轨道偏心率，无单位。
        // DF301: Galileo卫星轨道偏心率，无单位。
        // DF439: QZSS卫星轨道偏心率，无单位。
        // DF502: BDS卫星轨道偏心率，无单位。
        sixents::DOUBLE m_dbEccentricity = 0.0;

        // DF091: GPS卫星纬度幅角的正弦调和改正项的振幅，单位rad。
        // DF302: Galileo卫星纬度幅角的正弦调和改正项的振幅，单位 rad。
        // DF440: QZSS卫星纬度幅角的正弦调和改正项的振幅，单位 rad。
        // DF503: BDS卫星纬度幅角的正弦调和改正项的振幅，单位 rad。
        sixents::DOUBLE m_dbCus = 0.0;

        // DF092: GPS卫星轨道长半轴的平方根。
        // DF303: Galileo卫星轨道长半轴的平方根 。
        // DF441: QZSS卫星轨道长半轴与 42,164,200m 之差的平方根。
        // DF504: BDS卫星轨道长半轴与 42,164,200m 之差的平方根。
        // 参考RTCM STANDARD 10403.3数据单位:m1/2 需要转换成常用模式单位:m 转换方式是value * value
        sixents::DOUBLE m_dbAHalf = 0.0;

        // DF093: GPS卫星星历参考时间，单位s。
        // DF304: Galileo卫星星历参考时间。
        // DF442: QZSS卫星星历参考时间，单位 s。
        // DF505: BDS卫星星历参考时间，单位 s。
        sixents::UINT32 m_ui32Toe = 0U;

        // DF094: GPS卫星轨道倾角的余弦调和改正项的振幅，单位rad。
        // DF305: Galileo卫星轨道倾角的余弦调和改正项的振幅，单位 rad。
        // DF443: QZSS卫星轨道倾角的余弦调和改正项的振幅，单位 rad。
        // DF506: BDS卫星轨道倾角的余弦调和改正项的振幅，单位 rad。
        sixents::DOUBLE m_dbCic = 0.0;

        // DF095: GPS卫星按参考时间计算的升交点赤经
        // DF306: Galileo卫星按参考时间计算的升交点赤经
        // DF444: QZSS卫星按参考时间计算的升交点赤经
        // DF507: BDS卫星按参考时间计算的升交点赤经
        // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
        // 单位：deg
        sixents::DOUBLE m_dbOmega0 = 0.0;

        // DF096: GPS卫星轨道倾角的正弦调和改正项的振幅，单位rad。
        // DF307: Galileo卫星轨道倾角的正弦调和改正项的振幅，单位 rad。
        // DF445: QZSS卫星轨道倾角的正弦调和改正项的振幅，单位 rad。
        // DF508: BDS卫星轨道倾角的正弦调和改正项的振幅，单位 rad。
        sixents::DOUBLE m_dbCis = 0.0;

        // DF097: GPS卫星参考时间的轨道倾角
        // DF308: Galileo卫星参考时间的轨道倾角
        // DF446: QZSS卫星参考时间的轨道倾角
        // DF509: BDS卫星参考时间的轨道倾角
        // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
        // 单位：deg
        sixents::DOUBLE m_dbI0 = 0.0;

        // DF098: GPS卫星轨道半径的余弦调和改正项的振幅，单位m。
        // DF309: Galileo卫星轨道半径的余弦调和改正项的振幅，单位 m。
        // DF447: QZSS卫星轨道半径的余弦调和改正项的振幅，单位 m。
        // DF510: BDS卫星轨道半径的余弦调和改正项的振幅，单位 m。
        sixents::DOUBLE m_dbCrc = 0.0;

        // DF099: GPS卫星近地点幅角
        // DF310: Galileo卫星近地点幅角
        // DF448: QZSS卫星近地点幅角
        // DF511: BDS卫星近地点幅角
        // 参考RTCM STANDARD 10403.3解码后的数据(单位:π) 已经转换成常用模式(单位:deg)
        // 单位：deg
        sixents::DOUBLE m_dbArgumentOfPerigee = 0.0;

        // DF100: GPS卫星升交点赤经变化率
        // DF311: Galileo卫星升交点赤经变化率
        // DF449: QZSS卫星升交点赤经变化率
        // DF512: BDS卫星升交点赤经变化率
        // 参考RTCM STANDARD 10403.3解码后的数据(单位:π/s) 已经转换成常用模式(单位:deg/s)
        // 单位：deg/s
        sixents::DOUBLE m_dbOmegaDot = 0.0;

        // DF450:  QZSS 卫星轨道倾角变化率，单位 π/s
        sixents::DOUBLE m_dbIODot = 0.0;

        // DF101: 表示卫星L1 和L2 信号频率的群延迟差，单位s。
        // DF455:  LCQZSS 和 L1 C/A 码群延迟，单位 s。LCQZSS 是 QZSS L1 C/A 和L2C 信号无电离层线性组合信号。
        sixents::DOUBLE m_dbTgd = 0.0;

        // DF102: GPS0卫星健康状态，0=所有导航数据正常；1=某些或所有导航数据不正常。
        // DF454: QZSS卫星健康状态，DF454 每个比特位代表一个卫星信号，其状态表示对应信号的可用性，最高位(MSB)：0 =
        // 所有导航数据正常，1 = 部分或者所有导航数据有问题。
        // DF515: 表示BDS卫星健康信息，0=所有导航数据正常；1=某些或所有导航数据不正常。
        sixents::UINT8 m_ui8SvHealth = 0U;

        // DF103: 取自导航电文子帧1，第4 字，第1 位，含义如下：0 = L2 P 码导航电文可用；1 = L2 P 码导航电文不可用。
        sixents::UINT8 m_ui8L2PDataFlag = 0U;

        // DF137: 代表导航电文子帧2 第10 字的第17 位。0 = 曲线拟合间隔为4 小时；1 = 曲线拟合间隔大于4 小时。
        // DF457: 表示数据拟合间隔。DF457=0 表示拟合间隔为 2h，DF457=1 表示拟合间隔大于 2h
        sixents::UINT8 m_ui8FitInterval = 0U;

        // DF286 Galileo SISA Index (E1,E5b)
        sixents::UINT8 m_ui8SISAIndex = 0U;
        // DF290: Galileo导航数据的期卷号，无单位。
        sixents::UINT16 m_ui16IODnav = 0U;
        // DF291: Galileo卫星的 SIS 精度，在 Galileo OS-SIS-ICD-1.1 中定义了该保留字段，但未定义数据内容。
        sixents::UINT8 m_ui8SvSisa = 0U;
        // DF312: Galileo卫星 E1/E5a 播发群延迟，单位 s。
        sixents::DOUBLE m_dbBgdE1E5a = 0.0;
        // DF313: Galileo 卫星 E5b/E1 播发群延迟，单位 s。
        sixents::DOUBLE m_dbBgdE5bE1 = 0.0;
        // DF314: Galileo卫星 E5a 信号健康状况：0 = 信号健康；1 = 信号不可用；2 = 信号处于测试中。
        sixents::UINT8 m_ui8OSHS = 0U;
        // DF315: Galileo卫星 E5a 上导航数据的有效性状态，用于告诉用户卫星数据的性能水平（例如，卫星不可用）。
        sixents::UINT8 m_ui8OSDVS = 0U;
        // DF316: The E5b Signal Health Status Bit Values are:
        // 0 - Signal OK
        // 1 - Signal out of service
        // 2 - Signal will be out of service
        // 3- Signal Component currently in Test
        sixents::UINT8 m_ui8E5bSignalHealthStatus = 0U;
        // DF317 Galileo SOL NAV Data Validity Status
        sixents::UINT8 m_ui8E5bDataValidityStatus = 0U;
        // 287 Galileo E1-B Signal Health Status
        sixents::UINT8 m_ui8E1bSignalHealthStatus = 0U;
        // 288 Galileo E1-B  Data Validity Status
        sixents::UINT8 m_ui8E1bDataValidityStatus = 0U;

        // DF492: BDS卫星星历数据龄期
        sixents::UINT8 m_ui8AgeOfDataEphemeris = 0U;
        // DF497: BDS 卫星钟时钟数据龄期，无单位。
        sixents::UINT8 m_ui8AgeOfDataClock = 0U;
        // DF513: BDS卫星B1I 星上设备时延差，单位ns。
        sixents::DOUBLE m_dbTgd1 = 0.0;
        // DF514:BDS卫星B2I 星上设备时延差，单位ns。
        sixents::DOUBLE m_dbTgd2 = 0.0;
        // Reserved
        sixents::UINT8 m_ui8Reserved = 0U;
    };

    /**
     * @class   : SGlonassEphemeris
     * @author  : zhuquanlin@sixents.com
     * @brief   : Glonass星历结构体
     * @note    : 保存Glonass星历所有
     */
    struct DLL_API SGlonassEphemeris
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // Contents of GLONASS Satellite Ephemeris Data, Message Type 1020
        // DF002: 电文类型号,用于区分差分电文。
        sixents::UINT16 m_ui16MsgType = 0U;
        // DF038: GLONASS 的卫星星位号。
        sixents::UINT8 m_ui8SatId = 0U;
        // DF040: GLONASS 卫星的频率通道号。通过 DF038 和 DF040，用户无需历书就可知道卫星的频率。
        sixents::UINT8 m_ui8SatFrequencyChannelNumber = 0U;
        // DF104: GLONASS 历书健康状况
        sixents::UINT8 m_ui8AlmanacHealth = 0U;
        // DF105: 历书健康状况可用性标志
        // AHAI means AlmanacHealthAvailabilityIndicator
        sixents::UINT8 m_ui8AHAI = 0U;
        // DF106: GLONASS P1 字
        sixents::UINT8 m_ui8P1 = 0U;
        // DF107:当天 GLONASS子帧的起点为零点的时间。(bits 11 - 7 : 0 - 23 bits 6 - 1 : 0 - 59 bit 0 : 0 - 1)
        sixents::UINT16 m_ui16Tk = 0U;
        // DF108: 星历健康状况标志。
        sixents::UINT8 m_ui8MsbOfBn = 0U;
        // DF109 : P2 码可用性。
        sixents::UINT8 m_ui8P2 = 0U;
        // DF110: GLONASS 导航数据的参考时间。(单位:15min)
        sixents::UINT16 m_ui16Tb = 0U;
        // DF111: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 X 分量
        sixents::DOUBLE m_dbXnTbFirstDerivative = 0.0;
        // DF112: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 X 分量
        sixents::DOUBLE m_dbXnTb = 0.0;
        // DF113: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 X 分量
        sixents::DOUBLE m_dbXnTbSecondDerivative = 0.0;
        // DF114: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Y 分量
        sixents::DOUBLE m_dbYnTbFirstDerivative = 0.0;
        // DF115: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Y 分量
        sixents::DOUBLE m_dbYnTb = 0.0;
        // DF116: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Y 分量
        sixents::DOUBLE m_dbYnTbSecondDerivative = 0.0;
        // DF117: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Z 分量
        sixents::DOUBLE m_dbZnTbFirstDerivative = 0.0;
        // DF118: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Z 分量
        sixents::DOUBLE m_dbZnTb = 0.0;
        // DF119: 用于组成 PZ-90 坐标系下 GLONASS 卫星速度矢量的 Z 分量
        sixents::DOUBLE m_dbZnTbSecondDerivative = 0.0;
        // DF120: 表示 P3 码可用性。
        sixents::UINT8 m_ui8P3 = 0U;
        // DF121: 是预计的 GLONASS 卫星载波频率导数（相对于名义值）。
        sixents::DOUBLE m_dbGammaTb = 0.0;
        // DF122: GLONASS M 卫星的 P 码标志。
        sixents::UINT8 m_ui8GmP = 0U;
        // DF123: GLONASS 导航电文子帧的第三个字符串中提取出 l n 字。
        sixents::UINT8 m_ui8GmLn3 = 0U;
        // DF124: 相对 GLONASS 系统时间的卫星时间改正。
        sixents::DOUBLE m_dbTnTb = 0.0;
        // DF125: GLONASS L2 子带与 L1 子带中传输导航 RF 信号之间的时间差。
        sixents::DOUBLE m_dbGmDeltaTn = 0.0;
        // DF126: GLONASS 导航数据的龄期。
        sixents::UINT8 m_ui8En = 0U;
        // DF127: GLONASS M 卫星的 P4 码标志。
        sixents::UINT8 m_ui8GmP4 = 0U;
        // DF128: Tb 时刻 GLONASS-M 卫星 URA 估计值
        sixents::UINT8 m_ui8GmFt = 0U;
        // DF129: 以四年为间隔的，从闰年的一月一日开始的 GLONASS 日历天数。如果 DF129 不为零，则其值是与参数 t b
        // 相应日历天数的计算值。
        sixents::UINT16 m_ui16GmNt = 0U;
        // DF130:  GLONASS 卫星类型。01 = GLONASS - M 卫星，所有 GLONASS - M 数据字段均有效；00 = 非 GLONASS - M
        // 卫星，所有 GLONASS - M 数据字段无效。
        sixents::UINT8 m_ui8GmM = 0U;
        // DF131: 表示电文中是否包含从子帧第五字符串提取出的 GLONASS 星历电文的其余参数（如
        // DF132~DF136）。这些参数不属于预定义的星历数据，但有助于定位与授时。1 = 电文中包含附加数据；0 = DF132~DF136
        // 无效，取值随机。 AOAD means AvailabilityOfAdditionalData
        sixents::UINT8 m_ui8AOAD = 0U;
        // DF132: 表示以四年为周期的，参数 τ C 所使用 GLONASS 日历天数。
        sixents::UINT16 m_ui16NA = 0U;
        // DF133: 表示以 N A 日起始时刻为参考的 GLONASS 系统时与 UTC（SU）之差。
        sixents::DOUBLE m_dbTc = 0.0;
        // DF134: 表示从 1996 年开始的，以 4 年为周期的周期数。
        sixents::UINT8 m_ui8GmN4 = 0U;
        // DF135: 表示从子帧中第 5 个字符串中提取出的 GLONASS-M l n 字。
        sixents::DOUBLE m_dbGmTGps = 0.0;
        // DF136: 表示从子帧中第 5 个字符串中提取出的 GLONASS-M l n 字。
        sixents::UINT8 m_ui8GmLn5 = 0U;
        // Reserved
        sixents::UINT8 m_ui8Reserved = 0U;
    };

    /**
     * @class   : SReferenceInfo
     * @author  : zhuquanlin@sixents.com
     * @brief   : 参考站数据结构体(包含天线和基站坐标)
     * @note    : 保存参考站相关所有数据
     */
    struct DLL_API SReferenceInfo
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF002: 电文类型号,用于区分差分电文。
        sixents::UINT16 m_ui16MsgType = 0U;
        // DF003: 参考站 ID 由服务提供者确定。
        sixents::UINT16 m_ui16RefStaionId = 0U;
        // DF021: 表示坐标框架定义并实现的年份
        sixents::UINT8 m_ui8ItrfYear = 0U;
        // DF022: 0=没有 GPS 服务支持；1=有 GPS 服务支持。
        sixents::UINT8 m_ui8GPSIndicator = 0U;
        // DF023: 0=没有 GLONASS 服务支持；1=有 GLONASS 服务支持。
        sixents::UINT8 m_ui8GlonassIndicator = 0U;
        // DF024: 0=没有 Galileo 服务支持；1=有 Galileo 服务支持。
        sixents::UINT8 m_ui8GalileoIndicator = 0U;
        // DF141: 0=物理参考站；1 = 非物理或计算所得的参考站。
        sixents::UINT8 m_ui8RefStationIndicator = 0U;
        // DF025: ARP 在地心地固坐标系中的 X 坐标，坐标系历元为 DF021d 规定的参考历元。
        sixents::DOUBLE m_dbArpEcefX = 0.0;
        // DF142: 0=电文类型 1001~1004 与电文类型 1009~1012 中的原始数据可能是在不同时刻观测的。
        // 除非完全满足 DF142 = 1 的条件，否则 DF142 应置 0；1 = 电文类型 1001~1004 与电文类型 1009~1012
        // 中的原始数据为同时观测 ROI means ReceiverOscillatorIndicator
        sixents::UINT8 m_ui8SingleROI = 0U;
        // DF458: 0=没有 BDS 服务支持；1=有 BDS 服务支持。
        sixents::UINT8 m_ui8BDSIndicator = 0U;
        // DF026: ARP 在地心地固坐标系中的 Y 坐标，坐标系历元为 DF021d 规定的参考历元。
        sixents::DOUBLE m_dbArpEcefY = 0.0;
        // DF364:  用于说明统一频率上所跟踪的不同载波相位信号相位是否相同。即同一频率两个信号的相位距离差是否为 1 / 4 周
        sixents::UINT8 m_ui8QuarterCycleIndicator = 0U;
        // DF027: ARP 在地心地固坐标系中的 Z 坐标，坐标系历元为 DF021d 规定的参考历元。
        sixents::DOUBLE m_dbArpEcefZ = 0.0;
        // DF028: 提供从测量标志起算到天线参考点 ARP 的高度值。
        sixents::DOUBLE m_dbAntennaHeight = 0.0;
        // DF226: 物理参考站 ID
        sixents::UINT16 m_ui16PhysicalRefStationId = 0U;
        // DF029: 提供了 DF030 中的字节数，即天线标识符中的字符数
        sixents::UINT8 m_ui8DescriptorCount = 0U;
        // DF030: 由字母组成，说明天线类型等信息。
        std::array< sixents::INT8, 32 > m_objAntennaDescriptor = {};
        // DF031: 0=使用 IGS 标准模型；1~255=特殊天线设置号。
        sixents::UINT8 m_ui8AntennaSetupId = 0U;
        // DF032: 定义了天线序列号的字符数，按照 8bit 字节计算。
        sixents::UINT8 m_ui8SerialNumberCount = 0U;
        // DF033: 以字母数字字符的形式提供了天线序列号。
        std::array< sixents::INT8, 32 > m_objAntennaSerialNumber = {};
        // DF227: 表示接收机类型所含的字符数。
        // RTDC means ReceiverTypeDescriptorCount
        sixents::UINT8 m_ui8RTDC = 0U;
        // DF228: 表示接收机类型所含的字符。
        std::array< sixents::INT8, 32 > m_objReceiverTypeDescriptor = {};
        // DF229: 表示接收机固件版本号所含的字符数。
        // RFVC means ReceiverFirmwareVersionCount
        sixents::UINT8 m_ui8RFVC = 0U;
        // DF230: 表示接收机固件版本号所含的字符。
        std::array< sixents::INT8, 32 > m_objReceiverFirmwareVersion = {};
        // DF231: 表示接收机序列号所含的字符数。
        sixents::UINT8 m_ui8ReceiverSerialNumberCount = 0U;
        // DF232: 表示接收机序列号所含的字符。
        std::array< sixents::INT8, 32 > m_objReceiverSerialNumber = {};
    };

    /**
     * @class   : SOrbitCorrectionInfo
     * @author  : zhuquanlin@sixents.com
     * @brief   : 轨道改正参数每颗卫星数据结构体
     * @note    : 保存轨道改正参数所有数据
     */
    struct DLL_API SOrbitCorrectionInfo
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF068 表示卫星号
        // DF384 GLONASS 卫星号
        sixents::UINT8 m_ui8SatId = 0U;
        // DF071  GPS 卫星星历数据期号
        // DF392  GLONASS 广播星历的数据期号。
        sixents::UINT8 m_ui8IODE = 0U;
        // DF365 轨道面径向改正值
        sixents::DOUBLE m_dbDeltaRadial = 0.0;
        // DF366 轨道面切向改正值
        sixents::DOUBLE m_dbDeltaAlongTrack = 0.0;
        // DF367 轨道面法向改正值
        sixents::DOUBLE m_dbDeltaCrossTrack = 0.0;
        // DF368 轨道面径向改正值变化率
        sixents::DOUBLE m_dbDotDeltaRadial = 0.0;
        // DF369 轨道面切向改正值变化率
        sixents::DOUBLE m_dbDotDeltaAlongTrack = 0.0;
        // DF370 轨道面法向改正值变化率
        sixents::DOUBLE m_dbDotDeltaCrossTrack = 0.0;
    };

    /**
     * @class   : SOrbitCorrection
     * @author  : zhuquanlin@sixents.com
     * @brief   : 轨道改正参数结构体
     * @note    : 保存轨道改正参数所有数据
     */
    struct DLL_API SOrbitCorrection
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF002 报文类型
        sixents::UINT16 m_ui16MsgType = 0U;
        // DF385 GPS 历元时刻
        // DF386 Glonass 历元时刻
        sixents::UINT32 m_ui32EpochTime = 0U;
        // DF391 SSR 更新间隔
        sixents::UINT8 m_ui32SSRUpdateInterval = 0U;
        // DF388 多电文标志
        sixents::UINT8 m_ui8MulMsgIndicator = 0U;
        // DF375 卫星参考基准
        sixents::UINT8 m_ui8SatRefDatum = 0U;
        // DF413 IOD SSR
        sixents::UINT8 m_ui8IodSsr = 0U;
        // DF414 SSR 供应商 ID
        sixents::UINT32 m_ui32SsrProviderID = 0U;
        // DF415 SSR 解决方案 ID
        sixents::UINT8 m_ui8SsrSolutionID = 0U;
        // DF387 卫星数量
        sixents::UINT8 m_ui8SatNum = 0U;
        // 卫星数据
        std::map< INT32, SOrbitCorrectionInfo > m_mapOrbitCorrectionInfo;
    };

    // 钟差改正参数数据结构体
    /**
     * @class   : SClockCorrectionInfo
     * @author  : zhuquanlin@sixents.com
     * @brief   : 钟差改正参数每颗卫星数据结构体
     * @note    : 保存一颗卫星的钟差改正数据
     */
    struct DLL_API SClockCorrectionInfo
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF068 GPS 卫星号（即PRN 号）。
        // DF384 Glonass 卫星号（即PRN 号）。
        sixents::UINT8 m_ui8SatId = 0U;
        // DF376 表示相对于广播星历的卫星钟差改正多项式的C0系数。
        sixents::DOUBLE m_dbDeltaC0 = 0.0;
        // 参考时刻t0为 历元时刻（DF385和DF386）加上DF391的1/2。DF391=0时，参考时间t0 即为历元时刻
        // DF377 表示相对于广播星历的卫星钟差改正多项式的C1系数
        sixents::DOUBLE m_dbDeltaC1 = 0.0;
        // DF378 表示相对于广播星历的卫星钟差改正多项式的C2系数
        sixents::DOUBLE m_dbDeltaC2 = 0.0;
        // DF390 高频钟差改正数
        sixents::DOUBLE m_dbDeltaHighFrequencyNum = 0.0;
    };

    /**
     * @class   : SClockCorrection
     * @author  : zhuquanlin@sixents.com
     * @brief   : 钟差改正参数结构体
     * @note    : 保存钟差改正参数所有数据
     */
    struct DLL_API SClockCorrection
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF002 报文类型
        sixents::UINT16 m_ui16MsgType = 0U;
        // DF385 GPS 历元时刻
        // DF386 Glonass 历元时刻
        sixents::UINT32 m_ui32EpochTime = 0U;
        // DF391 SSR 更新间隔
        sixents::UINT8 m_ui32SSRUpdateInterval = 0U;
        // DF388 多电文标志
        sixents::UINT8 m_ui8MulMsgIndicator = 0U;
        // DF413 IOD SSR
        sixents::UINT8 m_ui8IodSsr = 0U;
        // DF414 SSR 供应商 ID
        sixents::UINT32 m_ui32SsrProviderID = 0U;
        // DF415 SSR 解决方案 ID
        sixents::UINT8 m_ui8SsrSolutionID = 0U;
        // DF387 卫星数量
        sixents::UINT8 m_ui8SatNum = 0U;

        std::map< INT32, SClockCorrectionInfo > m_mapClockCorrectionInfo;
    };

    /**
     * @class   : SOrbitClockCorrectionInfo
     * @author  : zhuquanlin@sixents.com
     * @brief   : 轨道钟差每颗卫星数据结构体
     * @note    : 保存一颗卫星的轨道钟差数据
     */
    struct DLL_API SOrbitClockCorrectionInfo
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF068 GPS 卫星号（即PRN 号）。
        // DF384 Glonass 卫星号（即PRN 号）。
        sixents::UINT8 m_ui8SatId = 0U;
        // DF071  GPS 卫星星历数据期号
        // DF392  GLONASS 广播星历的数据期号。
        sixents::UINT8 m_ui8IODE = 0U;
        // DF365 轨道面径向改正值
        sixents::DOUBLE m_db8DeltaRadial = 0.0;
        // DF366 轨道面切向改正值
        sixents::DOUBLE m_dbDeltaAlongTrack = 0.0;
        // DF367 轨道面法向改正值
        sixents::DOUBLE m_dbDeltaCrossTrack = 0.0;
        // DF368 轨道面径向改正值变化率
        sixents::DOUBLE m_dbDotDeltaRadial = 0.0;
        // DF369 轨道面切向改正值变化率
        sixents::DOUBLE m_dbDotDeltaAlongTrack = 0.0;
        // DF370 轨道面法向改正值变化率
        sixents::DOUBLE m_dbDotDeltaCrossTrack = 0.0;
        // DF376 表示相对于广播星历的卫星钟差改正多项式的C0系数。
        sixents::DOUBLE m_dbDeltaC0 = 0.0;
        // DF377 表示相对于广播星历的卫星钟差改正多项式的C1系数
        sixents::DOUBLE m_dbDeltaC1 = 0.0;
        // DF378 表示相对于广播星历的卫星钟差改正多项式的C2系数
        sixents::DOUBLE m_dbDeltaC2 = 0.0;
    };

    /**
     * @class   : SOrbitClockCorrection
     * @author  : zhuquanlin@sixents.com
     * @brief   : 轨道钟差结构体
     * @note    : 保存轨道钟差所有数据
     */
    struct DLL_API SOrbitClockCorrection
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF002 报文类型
        sixents::UINT16 m_ui16MsgType = 0U;
        // DF385 GPS 历元时刻
        // DF386 Glonass 历元时刻
        sixents::UINT32 m_ui32EpochTime = 0U;
        // DF391 SSR 更新间隔
        sixents::UINT8 m_ui32SSRUpdateInterval = 0U;
        // DF388 多电文标志
        sixents::UINT8 m_ui8MulMsgIndicator = 0U;
        // DF375 卫星参考基准
        sixents::UINT8 m_ui8SatRefDatum = 0U;
        // DF413 IOD SSR
        sixents::UINT8 m_ui8IodSsr = 0U;
        // DF414 SSR 供应商 ID
        sixents::UINT32 m_ui32SsrProviderID = 0U;
        // DF415 SSR 解决方案 ID
        sixents::UINT8 m_ui8SsrSolutionID = 0U;
        // DF387 卫星数量
        sixents::UINT8 m_ui8SatNum = 0U;

        std::map< INT32, SOrbitClockCorrectionInfo > m_mapOrbitClockCorrectionInfo;
    };

    // DCB数据结构体
    /**
     * @class   : SDcbInfo
     * @author  : zhuquanlin@sixents.com
     * @brief   : 每颗卫星中每个码偏差数据结构体
     * @note    : 保存一颗卫星中一个码偏差数据
     */
    struct DLL_API SDcbInfo
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF380 GPS 信号及其跟踪模式
        // DF381 GLONASS 信号及其跟踪模式
        sixents::UINT8 m_ui8SignalTrackingModeIndicator = 0U;
        // DF383 码偏差
        sixents::DOUBLE m_dbCodeBias = 0.0;
    };

    /**
     * @class   : SDcbSatInfo
     * @author  : zhuquanlin@sixents.com
     * @brief   : 每颗卫星码偏差数据结构体
     * @note    : 保存一颗卫星中所有码偏差数据
     */
    struct DLL_API SDcbSatInfo
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF068 表示GPS卫星号
        // DF384 表示Glonass卫星号
        sixents::UINT8 m_ui8SatId = 0U;
        // DF379 码偏差数量
        sixents::UINT8 m_ui8SsrUraNum = 0U;
        // 码偏差信息
        std::map< INT32, SDcbInfo > m_mapDcbInfo;
    };

    /**
     * @class   : SDcb
     * @author  : zhuquanlin@sixents.com
     * @brief   : 码偏差结构体
     * @note    : 保存码偏差所有数据
     */
    struct DLL_API SDcb
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // DF002: 电文类型号,用于区分差分电文。
        sixents::UINT16 m_ui16MsgType = 0U;
        // DF385 GPS 历元时刻
        // DF386 Glonass 历元时刻
        sixents::UINT32 m_ui32EpochTime = 0U;
        // DF391 SSR 更新间隔
        sixents::UINT8 m_ui32SSRUpdateInterval = 0U;
        // DF388 多电文标志
        sixents::UINT8 m_ui8MulMsgIndicator = 0U;
        // DF413 IOD SSR
        sixents::UINT8 m_ui8IodSsr = 0U;
        // DF414 SSR 供应商 ID
        sixents::UINT32 m_ui32SsrProviderID = 0U;
        // DF415 SSR 解决方案 ID
        sixents::UINT8 m_ui8SsrSolutionID = 0U;
        // DF387 卫星数量
        sixents::UINT8 m_ui8SatNum = 0U;
        // 码偏差卫星信息
        std::map< INT32, SDcbSatInfo > m_mapDcbSatInfo;
    };

    /**
     * @class   : SUraInfo
     * @author  : zhuquanlin@sixents.com
     * @brief   : 每颗卫星的用户距离精度数据结构体
     * @note    : 保存一颗卫星的用户距离精度数据
     */
    struct DLL_API SUraInfo
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // Satellite Specific Part of the SSR GPS URA Message 1061
        // DF068 表示GPS卫星号
        // DF384 表示Glonass卫星号
        sixents::UINT8 m_ui8SatId = 0U;
        // DF389 DF389是SSR距离改正值的URA精度（一倍中误差），该数值由RTCM SSR 电文中的完整的SSR数据计算得到
        sixents::UINT8 m_ui8SsrUra = 0U;
    };

    // URA数据结构体
    /**
     * @class   : SUra
     * @author  : zhuquanlin@sixents.com
     * @brief   : 用户距离精度数据结构体
     * @note    : 保存用户距离精度所有数据
     */
    struct DLL_API SUra
    {
        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void InitData();
        // Header Part of the SSR GPS URA Message 1061
        // DF002: 电文类型号,用于区分差分电文。
        sixents::UINT16 m_ui16MsgType = 0U;
        // DF385 GPS 历元时刻
        // DF386 Glonass 历元时刻
        sixents::UINT32 m_ui32EpochTime = 0U;
        // DF391 SSR 更新间隔
        sixents::UINT8 m_ui32SSRUpdateInterval = 0U;
        // DF388 多电文标志
        sixents::UINT8 m_ui8MulMsgIndicator = 0U;
        // DF413 IOD SSR
        sixents::UINT8 m_ui8IodSsr = 0U;
        // DF414 SSR 供应商 ID
        sixents::UINT32 m_ui32SsrProviderID = 0U;
        // DF415 SSR 解决方案 ID
        sixents::UINT8 m_ui8SsrSolutionID = 0U;
        // DF387 卫星数量
        sixents::UINT8 m_ui8SatNum = 0U;

        std::map< INT32, SUraInfo > m_mapUraInfo;
    };

    /**
     * @class   : CEpochObs
     * @author  : zhuquanlin@sixents.com
     * @brief   : 观测值对象
     * @note    : 包含观测值所有数据
     */
    class DLL_API CEpochObs : public IGnssDataInterface
    {
    public:
        /**
         * @brief      : CEpochObs对象构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        CEpochObs();

        /**
         * @brief      : CEpochObs对象析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual ~CEpochObs();

        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual void InitData() override;

        /**
         * @brief      : 获取观测值数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回观测值数据结构体
         * @retval     : SEpochSatObs
         * @note       : N/A
         */
        const SEpochSatObs& GetEpochSatObs() const;

        /**
         * @brief      : 设置观测值数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : stEpochSatObs    观测值结构体
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void SetEpochSatObs(const SEpochSatObs& stEpochSatObs);

        /**
         * @brief      : 获取一颗卫星的数据
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : i32SatId    卫星ID号
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回对应卫星的数据指针
         * @retval     :
         *  <em>nullptr</em>   表示没有找到对应卫星ID数据
         *  <em>非nullptr</em> 表示有对应卫星ID数据
         * @note       : N/A
         */
        SSatelliteValue* GetSatellite(const INT32 i32SatId);

        /**
         * @brief      : 获取指定卫星的一个信号数据
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : i32SatId    卫星ID号
         * @param[in]  : enSigCode   信号码
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回对应卫星对应信号码的信号数据指针
         * @retval     :
         *  <em>nullptr</em>   表示没有找到对应卫星ID对应信号码的信号数据
         *  <em>非nullptr</em> 表示找到对应卫星ID对应信号码的信号数据
         * @note       : N/A
         */
        SSignalValue* GetSignal(const INT32 i32SatId, const IGnssDataInterface::SignalCode enSigCode);

        /**
         * @brief      : 获取指定卫星指定信号码的信号强度
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : i32SatId    卫星ID号
         * @param[in]  : enSigCode   信号码
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回对应卫星对应信号码的信号强度
         * @retval     :
         *  <em>0</em>   表示没有找到对应卫星ID对应信号码的信号强度
         *  <em>非0</em> 表示找到对应卫星ID对应信号码的信号强度
         * @note       : N/A
         */
        sixents::DOUBLE GetSignalStrength(const INT32 i32SatId, const IGnssDataInterface::SignalCode enSigCode);

        // loss of lock indicator
        // sixents::UINT8 GetLossOfLockIndicator(const INT32 i32SatId, IGnssDataInterface::SignalCode enSigCode);

        //（MSM1~MSM3） 获取伪距 Pseudorange (i) = c/1000 ×(Nms +Rough_range /1024 + (2^–24) × Fine_Pseudorange(i))
        //（MSM4~MSM7） 获取伪距 Pseudorange (i) = c/1000 ×(Nms +Rough_range /1024 + (2^–29) × Fine_Pseudorange(i))
        /**
         * @brief      : 获取指定卫星指定信号码的伪距
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : i32SatId    卫星ID号
         * @param[in]  : enSigCode   信号码
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回对应卫星对应信号码的伪距
         * @retval     :
         *  <em>0.0</em> 表示没有找到对应卫星ID对应信号码的伪距
         *  <em>非0</em> 表示找到对应卫星ID对应信号码的伪距
         * @note       : 注意浮点数与0.0的比较
         */
        sixents::DOUBLE GetPseudorange(const INT32 i32SatId, const IGnssDataInterface::SignalCode enSigCode);

        //（MSM1~MSM3） 获取相位距离 PhaseRange (i) = c/1000 × (Nms + Rough_range /1024 + (2^–29) × Fine_PhaseRange(i))
        //（MSM4~MSM7） 获取相位距离 PhaseRange (i) = c/1000 × (Nms + Rough_range /1024 + (2^–31) × Fine_PhaseRange(i))
        /**
         * @brief      : 获取指定卫星指定信号码的相位距离
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : i32SatId    卫星ID号
         * @param[in]  : enSigCode   信号码
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回对应卫星对应信号码的相位距离
         * @retval     :
         *  <em>0.0</em> 表示没有找到对应卫星ID对应信号码的相位距离
         *  <em>非0</em> 表示找到对应卫星ID对应信号码的相位距离
         * @note       : 注意浮点数与0.0的比较
         */
        sixents::DOUBLE GetPhaseRange(const INT32 i32SatId, const IGnssDataInterface::SignalCode enSigCode);

        //（MSM1~MSM3） 获取相位距离变化率 PhaseRange (i) = Rough_PhaseRangeRate + 0.0001 × Fine_PhaseRangeRate(i)
        //（MSM4~MSM7） 获取相位距离变化率 PhaseRangeRate(i) = Rough_PhaseRangeRate + 0.0001 × Fine_PhaseRangeRate(i)
        /**
         * @brief      : 获取指定卫星指定信号码的相位距离变化率
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : i32SatId    卫星ID号
         * @param[in]  : enSigCode   信号码
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回对应卫星对应信号码的相位距离变化率
         * @retval     :
         *  <em>0.0</em> 表示没有找到对应卫星ID对应信号码的相位距离变化率
         *  <em>非0</em> 表示找到对应卫星ID对应信号码的相位距离变化率
         * @note       : 注意浮点数与0.0的比较
         */
        sixents::DOUBLE GetPhaseRangeRate(const INT32 i32SatId, const IGnssDataInterface::SignalCode enSigCode);

    private:
        SEpochSatObs m_stEpochSatObs;
    };

    /**
     * @class   : CEphemeris
     * @author  : zhuquanlin@sixents.com
     * @brief   : 星历对象（不包含Glonass系统）
     * @note    : 包含星历所有数据
     */
    class DLL_API CEphemeris : public IGnssDataInterface
    {
    public:
        /**
         * @brief      : CEphemeris对象构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        CEphemeris();

        /**
         * @brief      : CEphemeris对象析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual ~CEphemeris();

        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual void InitData() override;

        /**
         * @brief      : 获取星历数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回星历数据结构体
         * @retval     : SEphemeris
         * @note       : N/A
         */
        const SEphemeris& GetEphemeris() const;

        /**
         * @brief      : 设置星历数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : stEphemeris    星历结构体
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void SetEphemeris(const SEphemeris& stEphemeris);

    private:
        SEphemeris m_stEphemeris;
    };

    /**
     * @class   : CGlonassEphemeris
     * @author  : zhuquanlin@sixents.com
     * @brief   : Glonass系统星历对象
     * @note    : 包含Glonass系统星历所有数据
     */
    class DLL_API CGlonassEphemeris : public IGnssDataInterface
    {
    public:
        /**
         * @brief      : CGlonassEphemeris对象构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        CGlonassEphemeris();

        /**
         * @brief      : CGlonassEphemeris对象析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual ~CGlonassEphemeris();

        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual void InitData() override;

        /**
         * @brief      : 获取Glonass星历数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回Glonass星历数据结构体
         * @retval     : SGlonassEphemeris
         * @note       : N/A
         */
        const SGlonassEphemeris& GetGlonassEphemeris() const;

        /**
         * @brief      : 设置Glonass星历数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : stGlonassEphemeris    Glonass星历结构体
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void SetGlonassEphemeris(const SGlonassEphemeris& stGlonassEphemeris);

    private:
        SGlonassEphemeris m_stGlonassEphemeris;
    };

    /**
     * @class   : CReferenceInfo
     * @author  : zhuquanlin@sixents.com
     * @brief   : 参考站对象
     * @note    : 包含参考站所有数据
     */
    class DLL_API CReferenceInfo : public IGnssDataInterface
    {
    public:
        /**
         * @brief      : CReferenceInfo对象构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        CReferenceInfo();

        /**
         * @brief      : CReferenceInfo对象析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual ~CReferenceInfo();

        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual void InitData() override;

        /**
         * @brief      : 获取参考站数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回参考站数据结构体
         * @retval     : SReferenceInfo
         * @note       : N/A
         */
        const SReferenceInfo& GetReferenceInfo() const;

        /**
         * @brief      : 设置参考站数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : stReferenceInfo    参考站结构体
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void SetReferenceInfo(const SReferenceInfo& stReferenceInfo);

    private:
        SReferenceInfo m_stReferenceInfo;
    };

    /**
     * @class   : COrbitCorrection
     * @author  : zhuquanlin@sixents.com
     * @brief   : 轨道改正参数对象
     * @note    : 包含轨道改正参数所有数据
     */
    class DLL_API COrbitCorrection : public IGnssDataInterface
    {
    public:
        /**
         * @brief      : COrbitCorrection对象构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        COrbitCorrection();

        /**
         * @brief      : COrbitCorrection对象析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual ~COrbitCorrection();

        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual void InitData() override;

        /**
         * @brief      : 获取轨道改正参数数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回轨道改正参数数据结构体
         * @retval     : SOrbitCorrection
         * @note       : N/A
         */
        SOrbitCorrection& GetOrbitCorrection();

        /**
         * @brief      : 设置轨道改正参数数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : stCOrbitCorrection    轨道改正参数结构体
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void SetOrbitCorrection(const SOrbitCorrection& stOrbitCorrection);

    private:
        SOrbitCorrection m_stOrbitCorrection;
    };

    /**
     * @class   : CClockCorrection
     * @author  : zhuquanlin@sixents.com
     * @brief   : 钟差改正参数对象
     * @note    : 包含钟差改正参数所有数据
     */
    class DLL_API CClockCorrection : public IGnssDataInterface
    {
    public:
        /**
         * @brief      : CClockCorrection对象构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        CClockCorrection();

        /**
         * @brief      : CClockCorrection对象析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual ~CClockCorrection();

        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual void InitData() override;

        /**
         * @brief      : 获取钟差改正参数数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回钟差改正参数数据结构体
         * @retval     : SClockCorrection
         * @note       : N/A
         */
        SClockCorrection& GetClockCorrection();

        /**
         * @brief      : 设置钟差改正参数数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : stSatClock    钟差改正参数结构体
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void SetClockCorrection(const SClockCorrection& stSatClock);

    private:
        SClockCorrection m_stClockCorrection;
    };

    /**
     * @class   : COrbitClockCorrection
     * @author  : zhuquanlin@sixents.com
     * @brief   : 轨道钟差改正参数对象
     * @note    : 包含轨道钟差改正参数所有数据
     */
    class DLL_API COrbitClockCorrection : public IGnssDataInterface
    {
    public:
        /**
         * @brief      : COrbitClockCorrection对象构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        COrbitClockCorrection();

        /**
         * @brief      : COrbitClockCorrection对象析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual ~COrbitClockCorrection();

        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual void InitData() override;

        /**
         * @brief      : 获取轨道钟差改正参数数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回轨道钟差改正参数数据结构体
         * @retval     : SOrbitClockCorrection
         * @note       : N/A
         */
        SOrbitClockCorrection& GetOrbitClockCorrection();

        /**
         * @brief      : 设置轨道钟差改正参数数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : stOrbitClockCorrection    轨道钟差改正参数结构体
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void SetOrbitClockCorrection(const SOrbitClockCorrection& stOrbitClockCorrection);

    private:
        SOrbitClockCorrection m_stOrbitClockCorrection;
    };

    /**
     * @class   : CDcb
     * @author  : zhuquanlin@sixents.com
     * @brief   : Different Code Bias对象
     * @note    : 包含码偏差所有数据
     */
    class DLL_API CDcb : public IGnssDataInterface
    {
    public:
        /**
         * @brief      : CDcb对象构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        CDcb();

        /**
         * @brief      : CDcb对象析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual ~CDcb();

        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual void InitData() override;

        /**
         * @brief      : 获取码偏差数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回码偏差数据结构体
         * @retval     : SDcb
         * @note       : N/A
         */
        const SDcb& GetDcb() const;

        /**
         * @brief      : 设置码偏差数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : stDcb    码偏差结构体
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void SetDcb(const SDcb& stDcb);

    private:
        SDcb m_stDcb;
    };

    // URA对象
    /**
     * @class   : CUra
     * @author  : zhuquanlin@sixents.com
     * @brief   : User range accuracy对象
     * @note    : 包含用户距离精度所有数据
     */
    class DLL_API CUra : public IGnssDataInterface
    {
    public:
        /**
         * @brief      : CUra对象构造函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        CUra();

        /**
         * @brief      : CUra对象析构函数
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual ~CUra();

        /**
         * @brief      : 初始化所有数据成员
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        virtual void InitData() override;

        /**
         * @brief      : 获取用户距离精度数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : N/A
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : 返回用户距离精度数据结构体
         * @retval     : SUra
         * @note       : N/A
         */
        const SUra& GetUra() const;

        /**
         * @brief      : 设置用户距离精度数据结构体
         * @author     : zhuquanlin@sixents.com
         * @param[in]  : stUra    用户距离精度结构体
         * @param[out] : N/A
         * @exception  : N/A
         * @return     : N/A
         * @retval     : N/A
         * @note       : N/A
         */
        void SetUra(const SUra& stUra);

    private:
        SUra m_stUra;
    };
} // namespace sixents

#ifdef UNIT_TEST
#undef private
#undef protected
#define private private
#define protected protected
#endif

#endif // _IGNSS_DATA_CLASS_
