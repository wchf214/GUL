/**
 * @copyright Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd.
 *       All rights reserved.
 * @file    CCodecUtilities.h
 * @author  yangchenyi/yangchengyi@sixents.com
 * @version 1.0
 * @date    2020-1-9
 * @brief   编解码相关函数
 * @details
 *
 * @note
 *    change history:
 *    <2020-1-9>  | 1.0 | yangchenyi | 创建初始版本
 */

#ifndef _CODEC_UTILITIES_H_
#define _CODEC_UTILITIES_H_

#include "../Framework/Constants.h"
#include "../GnssData/IGnssDataInterface.h"
#include "../Platform/BasicType.h"

namespace sixents
{
    /**
     * @class   CCodecUtilities
     * @brief   编解码涉及的基础函数
     * @author  yangchengyi
     * @note    N/A
     */
    class CCodecUtilities
    {
    public:
        /**
         * @brief       按比特位获取无符号32位的二进制数
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据的地址
         * @param[in]   ui32Pos 获取数据的比特位的起始位置
         * @param[in]   ui32Len 获取数据的比特位的长度
         * @param[strOut]  输出参数
         * @exception   N/A
         * @return      返回获取的数据
         * @retval
         * @note        pBuff指针不能为空和最多只能获取32个比特位数据
         */
        static UINT32 GetUnsignedIntBit(const UINT8* const pBuff, const UINT32 ui32Pos, const UINT32 ui32Len);
        /**
         * @brief       按比特位获取无符号64位的二进制数
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据的地址
         * @param[in]   ui32Pos 获取数据的比特位的起始位置
         * @param[in]   ui32Len 获取数据的比特位的长度
         * @param[strOut]  输出参数
         * @exception   N/A
         * @return      返回获取的数据
         * @retval
         * @note        pBuff指针不能为空和最多只能获取64个比特位数据
         */
        static UINT64 GetUnsignedInt64Bit(const UINT8* const pBuff, const UINT32 ui32Pos, const UINT32 ui32Len);
        /**
         * @brief       按比特位获取有符号32位的二进制数
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据的地址
         * @param[in]   ui32Pos 获取数据的比特位的起始位置
         * @param[in]   ui32Len 获取数据的比特位的长度
         * @param[strOut]  输出参数
         * @exception   N/A
         * @return      返回获取的数据
         * @retval
         * @note        pBuff指针不能为空和最多只能获取32个比特位数据
         */
        static INT32 GetIntBit(const UINT8* const pBuff, const UINT32 ui32Pos, const UINT32 ui32Len);
        /**
         * @brief       按比特位获取有符号32位的二进制数
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据的地址
         * @param[in]   ui32Pos 获取数据的比特位的起始位置
         * @param[in]   ui32Len 获取数据的比特位的长度
         * @param[strOut]  输出参数
         * @exception   N/A
         * @return      返回获取的数据
         * @retval
         * @note        pBuff指针不能为空和最多只能获取32个比特位数据
         */
        static DOUBLE GetSignMagnitudeIntBit(const UINT8* const pBuff, const UINT32 ui32Pos, const UINT32 ui32Len);
        /**
         * @brief       按比特位获取有符号38位的二进制数
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据的地址
         * @param[in]   ui32Pos 获取数据的比特位的起始位置
         * @param[strOut]  输出参数
         * @exception   N/A
         * @return      返回获取的数据
         * @retval
         * @note        pBuff指针不能为空和只能获取38个比特位数据
         */
        static DOUBLE GetDoubleBit(const UINT8* const pBuff, const UINT32 ui32Pos);
        /**
         * @brief       编码无符号数到pBuff中
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据的存放地址
         * @param[in]   ui32Pos 存放二进制数据的起始位置
         * @param[in]   ui32Len 需要存放的数据的长度
         * @param[in]   ui32Data 需要存放的数据
         * @param[strOut]  pBuff 编码数据后的pBuff
         * @exception   N/A
         * @return      ui32Pos + ui32Len
         * @retval
         * @note        ui32Len不能大于32
         */
        static UINT32
        SetUnsignedIntBit(std::string& pBuff, const UINT32 ui32Pos, const UINT32 ui32Len, const UINT32 ui32Data);
        /**
         * @brief       编码有符号数到pBuff中
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据的存放地址
         * @param[in]   ui32Pos 存放二进制数据的起始位置
         * @param[in]   ui32Len 需要存放的数据的长度
         * @param[in]   i32Data 需要存放的数据
         * @param[strOut]  pBuff 编码数据后的pBuff
         * @exception   N/A
         * @return      ui32Pos + ui32Len
         * @retval
         * @note        ui32Len不能大于32
         *              正数存放原码，负数存放补码
         */
        static UINT32 SetIntBit(std::string& pBuff, const UINT32 ui32Pos, const UINT32 ui32Len, INT32 i32Data);
        /**
         * @brief       编码有符号量的二进制数据到pBuff中
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据的存放地址
         * @param[in]   ui32Pos 存放二进制数据的起始位置
         * @param[in]   ui32Len 需要存放的数据的长度
         * @param[in]   i32Data 需要存放的数据
         * @param[strOut]  pBuff 编码数据后的pBuff
         * @exception   N/A
         * @return      ui32Pos + ui32Len
         * @retval
         * @note        ui32Len不能大于32
         *              正数首位存0，负数首位存1
         */
        static UINT32 SetSignMagnitudeIntBit(std::string& pBuff, UINT32 ui32Pos, const UINT32 ui32Len, INT32 i32Data);
        /**
         * @brief       编码38位的二进制数据到pBuff中
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据的存放地址
         * @param[in]   ui32Pos 存放二进制数据的起始位置
         * @param[in]   dbValue 需要存放的数据
         * @param[strOut]  pBuff 编码数据后的pBuff
         * @exception   N/A
         * @return      ui32Pos + 38
         * @retval
         * @note        N/A
         */
        static UINT32 SetDoubleBit(std::string& pBuff, UINT32 ui32Pos, const DOUBLE dbValue);
        /**
         * @brief       获取pBuff的CRC24校验值
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据
         * @param[strOut]  N/A
         * @exception   N/A
         * @return      pBuff的CRC24校验值
         * @retval
         * @note        N/A
         */
        static UINT32 RtkCrc24q(const std::string& strBuff);
        /**
         * @brief       获取pBuff的CRC24校验值
         * @author      yangchengyi
         * @param[in]   pBuff 二进制数据
         * @param[in]   ui32Len 二进制数据的长度
         * @param[strOut]  N/A
         * @exception   N/A
         * @return      pBuff的CRC24校验值
         * @retval
         * @note        N/A
         */
        static UINT32 RtkCrc24q(const UINT8* const pBuff, const UINT32 ui32Len);

        /**
         * @brief       判断double类型的数据是否为0
         * @author      yangchengyi
         * @param[in]   dbValue 数据
         * @param[strOut]  N/A
         * @exception   N/A
         * @return      返回是否为0
         * @retval
         *    true      0
         *    false     非0
         * @note        N/A
         */
        static BOOL_T DoubleEqualToZero(const DOUBLE dbValue);

        /**
         * @brief       编码卫星概略距离的整毫秒数
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入卫星概略距离的整毫秒数数据的起始比特位位置
         * @param[in]   strOut 写入卫星概略距离的整毫秒数数据的pBuff
         * @param[strOut]  strOut 写入卫星概略距离的整毫秒数数据后的pBuff
         * @exception   N/A
         * @return      写入卫星概略距离的整毫秒数数据后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmIntRrng(const SEpochSatObs& stObs, UINT32 ui32Pos, std::string& strOut);
        /**
         * @brief       编码扩展卫星信息
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入扩展卫星信息的起始比特位位置
         * @param[in]   strOut 写入扩展卫星信息的pBuff
         * @param[strOut]  strOut 写入扩展卫星信息后的pBuff
         * @exception   N/A
         * @return      写入扩展卫星信息后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmSatExInfo(const SEpochSatObs& stObs, UINT32 ui32Pos, std::string& strOut);
        /**
         * @brief       编码卫星概略距离的毫秒余数
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入卫星概略距离的毫秒余数的起始比特位位置
         * @param[in]   strOut 写入卫星概略距离的毫秒余数的pBuff
         * @param[strOut]  strOut 写入卫星概略距离的毫秒余数后的pBuff
         * @exception   N/A
         * @return      写入卫星概略距离的毫秒余数后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmModRrng(const SEpochSatObs& stObs, UINT32 ui32Pos, std::string& strOut);
        /**
         * @brief       编码卫星概略相位距离变化率
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入卫星概略相位距离变化率的起始比特位位置
         * @param[in]   strOut 写入卫星概略相位距离变化率的pBuff
         * @param[strOut]  strOut 写入卫星概略相位距离变化率后的pBuff
         * @exception   N/A
         * @return      写入卫星概略相位距离变化率后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmRrate(const SEpochSatObs& stObs, UINT32 ui32Pos, std::string& strOut);
        /**
         * @brief       编码信号精确伪距观测值
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入信号精确伪距观测值的起始比特位位置
         * @param[in]   mapCells 卫星信号对应的槽
         * @param[in]   strOut 写入信号精确伪距观测值的pBuff
         * @param[strOut]  strOut 写入信号精确伪距观测值后的pBuff
         * @exception   N/A
         * @return      写入信号精确伪距观测值后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmPsrng(const SEpochSatObs& stObs,
                                     UINT32 ui32Pos,
                                     const std::map< INT32, INT32 >& mapCells,
                                     std::string& strOut);
        /**
         * @brief       编码具有扩展分辨率的GNSS 信号精确伪距值
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入具有扩展分辨率的GNSS 信号精确伪距值的起始比特位位置
         * @param[in]   mapCells 卫星信号对应的槽
         * @param[in]   strOut 写入具有扩展分辨率的GNSS 信号精确伪距值的pBuff
         * @param[strOut]  strOut 写入具有扩展分辨率的GNSS 信号精确伪距值后的pBuff
         * @exception   N/A
         * @return      写入具有扩展分辨率的GNSS 信号精确伪距值后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmPsrngEx(const SEpochSatObs& stObs,
                                       UINT32 ui32Pos,
                                       const std::map< INT32, INT32 >& mapCells,
                                       std::string& strOut);
        /**
         * @brief       编码GNSS 信号精确相位距离数据
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入GNSS 信号精确相位距离数据的起始比特位位置
         * @param[in]   mapCells 卫星信号对应的槽
         * @param[in]   strOut 写入GNSS 信号精确相位距离数据的pBuff
         * @param[strOut]  strOut 写入GNSS 信号精确相位距离数据后的pBuff
         * @exception   N/A
         * @return      写入GNSS 信号精确相位距离数据后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmPhrng(const SEpochSatObs& stObs,
                                     UINT32 ui32Pos,
                                     const std::map< INT32, INT32 >& mapCells,
                                     std::string& strOut);
        /**
         * @brief       编码具有扩展分辨率的GNSS 信号精确相位距离
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入具有扩展分辨率的GNSS 信号精确相位距离的起始比特位位置
         * @param[in]   mapCells 卫星信号对应的槽
         * @param[in]   strOut 写入具有扩展分辨率的GNSS 信号精确相位距离的pBuff
         * @param[strOut]  strOut 写入具有扩展分辨率的GNSS 信号精确相位距离后的pBuff
         * @exception   N/A
         * @return      写入具有扩展分辨率的GNSS 信号精确相位距离后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmPhrngEx(const SEpochSatObs& stObs,
                                       UINT32 ui32Pos,
                                       const std::map< INT32, INT32 >& mapCells,
                                       std::string& strOut);
        /**
         * @brief       编码GNSS 相位距离锁定时间标志
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入GNSS 相位距离锁定时间标志的起始比特位位置
         * @param[in]   mapCells 卫星信号对应的槽
         * @param[in]   strOut 写入GNSS 相位距离锁定时间标志的pBuff
         * @param[strOut]  strOut 写入GNSS 相位距离锁定时间标志后的pBuff
         * @exception   N/A
         * @return      写入GNSS 相位距离锁定时间标志后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmLock(const SEpochSatObs& stObs,
                                    UINT32 ui32Pos,
                                    const std::map< INT32, INT32 >& mapCells,
                                    std::string& strOut);
        /**
         * @brief       编码具有扩展范围和分辨率的GNSS 相位距离时间锁定标志
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入具有扩展范围和分辨率的GNSS 相位距离时间锁定标志的起始比特位位置
         * @param[in]   mapCells 卫星信号对应的槽
         * @param[in]   strOut 写入具有扩展范围和分辨率的GNSS 相位距离时间锁定标志的pBuff
         * @param[strOut]  strOut 写入具有扩展范围和分辨率的GNSS 相位距离时间锁定标志后的pBuff
         * @exception   N/A
         * @return      写入具有扩展范围和分辨率的GNSS 相位距离时间锁定标志后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmLockEx(const SEpochSatObs& stObs,
                                      UINT32 ui32Pos,
                                      const std::map< INT32, INT32 >& mapCells,
                                      std::string& strOut);
        /**
         * @brief       编码半周模糊度指标
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入半周模糊度指标的起始比特位位置
         * @param[in]   mapCells 卫星信号对应的槽
         * @param[in]   strOut 写入半周模糊度指标的pBuff
         * @param[strOut]  strOut 写入半周模糊度指标后的pBuff
         * @exception   N/A
         * @return      写入半周模糊度指标后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmHalfAmb(const SEpochSatObs& stObs,
                                       UINT32 ui32Pos,
                                       const std::map< INT32, INT32 >& mapCells,
                                       std::string& strOut);
        /**
         * @brief       编码GNSS 信号CNR
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入GNSS 信号CNR的起始比特位位置
         * @param[in]   mapCells 卫星信号对应的槽
         * @param[in]   strOut 写入GNSS 信号CNR的pBuff
         * @param[strOut]  strOut 写入GNSS 信号CNR后的pBuff
         * @exception   N/A
         * @return      写入GNSS 信号CNR后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmCnr(const SEpochSatObs& stObs,
                                   UINT32 ui32Pos,
                                   const std::map< INT32, INT32 >& mapCells,
                                   std::string& strOut);
        /**
         * @brief       编码具有扩展分辨率的GNSS 信号信噪比
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入具有扩展分辨率的GNSS 信号信噪比的起始比特位位置
         * @param[in]   mapCells 卫星信号对应的槽
         * @param[in]   strOut 写入具有扩展分辨率的GNSS 信号信噪比的pBuff
         * @param[strOut]  strOut 写入具有扩展分辨率的GNSS 信号信噪比后的pBuff
         * @exception   N/A
         * @return      写入具有扩展分辨率的GNSS 信号信噪比后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmCnrEx(const SEpochSatObs& stObs,
                                     UINT32 ui32Pos,
                                     const std::map< INT32, INT32 >& mapCells,
                                     std::string& strOut);
        /**
         * @brief       编码GNSS 信号精确相位距离变化率
         * @author      yangchengyi
         * @param[in]   stObs 观测值对象
         * @param[in]   ui32Pos 写入GNSS 信号精确相位距离变化率的起始比特位位置
         * @param[in]   mapCells 卫星信号对应的槽
         * @param[in]   strOut 写入GNSS 信号精确相位距离变化率的pBuff
         * @param[strOut]  strOut 写入GNSS 信号精确相位距离变化率后的pBuff
         * @exception   N/A
         * @return      写入GNSS 信号精确相位距离变化率后的比特位位置
         * @retval
         * @note        N/A
         */
        static UINT32 EncodeMsmRate(const SEpochSatObs& stObs,
                                    UINT32 ui32Pos,
                                    const std::map< INT32, INT32 >& mapCells,
                                    std::string& strOut);
        /**
         * @brief       获取卫星信号的波长
         * @author      yangchengyi
         * @param[in]   eSys 卫星类型
         * @param[in]   eSig 卫星信号值
         * @exception   N/A
         * @return      卫星信号的波长
         * @retval
         * @note        N/A
         */

        static DOUBLE GetSatWaveLen(const IGnssDataInterface::SatelliteSystem eSys,
                                    const IGnssDataInterface::SignalCode eSig,
                                    const UINT8 ui8SatFrequencyChannelNumber);
    };
} // namespace sixents
#endif // _COMMON_ALGORITHM_H_
