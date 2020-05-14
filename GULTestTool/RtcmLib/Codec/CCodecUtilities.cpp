#include "CCodecUtilities.h"
#include <cassert>
#include <cfloat>
#include <cmath>
#include "../Framework/CommonFunc.h"

namespace sixents
{
    using std::string;
    using namespace sixents::common::rtcm;

    namespace
    {
        constexpr DOUBLE DB_DOUBLE_LOW_SCALE = 64.0;
        constexpr DOUBLE DB_SIGNAL_FINE_PSEUDORANGE_MAX_VALUE = 292.7;
        constexpr DOUBLE DB_SIGNAL_FINE_PSEUDORANGE_INVALID_VALUE = -16384.0;
        constexpr DOUBLE DB_SIGNAL_FINE_PHASERANGE_MAX_VALUE = 1171.0;
        constexpr DOUBLE DB_SIGNAL_FINE_PHASERANGE_INVALID_VALUE = -2097152.0;

        const sixents::UINT32 TABLE_CRC24Q[] = {
            0x000000U, 0x864CFBU, 0x8AD50DU, 0x0C99F6U, 0x93E6E1U, 0x15AA1AU, 0x1933ECU, 0x9F7F17U, 0xA18139U,
            0x27CDC2U, 0x2B5434U, 0xAD18CFU, 0x3267D8U, 0xB42B23U, 0xB8B2D5U, 0x3EFE2EU, 0xC54E89U, 0x430272U,
            0x4F9B84U, 0xC9D77FU, 0x56A868U, 0xD0E493U, 0xDC7D65U, 0x5A319EU, 0x64CFB0U, 0xE2834BU, 0xEE1ABDU,
            0x685646U, 0xF72951U, 0x7165AAU, 0x7DFC5CU, 0xFBB0A7U, 0x0CD1E9U, 0x8A9D12U, 0x8604E4U, 0x00481FU,
            0x9F3708U, 0x197BF3U, 0x15E205U, 0x93AEFEU, 0xAD50D0U, 0x2B1C2BU, 0x2785DDU, 0xA1C926U, 0x3EB631U,
            0xB8FACAU, 0xB4633CU, 0x322FC7U, 0xC99F60U, 0x4FD39BU, 0x434A6DU, 0xC50696U, 0x5A7981U, 0xDC357AU,
            0xD0AC8CU, 0x56E077U, 0x681E59U, 0xEE52A2U, 0xE2CB54U, 0x6487AFU, 0xFBF8B8U, 0x7DB443U, 0x712DB5U,
            0xF7614EU, 0x19A3D2U, 0x9FEF29U, 0x9376DFU, 0x153A24U, 0x8A4533U, 0x0C09C8U, 0x00903EU, 0x86DCC5U,
            0xB822EBU, 0x3E6E10U, 0x32F7E6U, 0xB4BB1DU, 0x2BC40AU, 0xAD88F1U, 0xA11107U, 0x275DFCU, 0xDCED5BU,
            0x5AA1A0U, 0x563856U, 0xD074ADU, 0x4F0BBAU, 0xC94741U, 0xC5DEB7U, 0x43924CU, 0x7D6C62U, 0xFB2099U,
            0xF7B96FU, 0x71F594U, 0xEE8A83U, 0x68C678U, 0x645F8EU, 0xE21375U, 0x15723BU, 0x933EC0U, 0x9FA736U,
            0x19EBCDU, 0x8694DAU, 0x00D821U, 0x0C41D7U, 0x8A0D2CU, 0xB4F302U, 0x32BFF9U, 0x3E260FU, 0xB86AF4U,
            0x2715E3U, 0xA15918U, 0xADC0EEU, 0x2B8C15U, 0xD03CB2U, 0x567049U, 0x5AE9BFU, 0xDCA544U, 0x43DA53U,
            0xC596A8U, 0xC90F5EU, 0x4F43A5U, 0x71BD8BU, 0xF7F170U, 0xFB6886U, 0x7D247DU, 0xE25B6AU, 0x641791U,
            0x688E67U, 0xEEC29CU, 0x3347A4U, 0xB50B5FU, 0xB992A9U, 0x3FDE52U, 0xA0A145U, 0x26EDBEU, 0x2A7448U,
            0xAC38B3U, 0x92C69DU, 0x148A66U, 0x181390U, 0x9E5F6BU, 0x01207CU, 0x876C87U, 0x8BF571U, 0x0DB98AU,
            0xF6092DU, 0x7045D6U, 0x7CDC20U, 0xFA90DBU, 0x65EFCCU, 0xE3A337U, 0xEF3AC1U, 0x69763AU, 0x578814U,
            0xD1C4EFU, 0xDD5D19U, 0x5B11E2U, 0xC46EF5U, 0x42220EU, 0x4EBBF8U, 0xC8F703U, 0x3F964DU, 0xB9DAB6U,
            0xB54340U, 0x330FBBU, 0xAC70ACU, 0x2A3C57U, 0x26A5A1U, 0xA0E95AU, 0x9E1774U, 0x185B8FU, 0x14C279U,
            0x928E82U, 0x0DF195U, 0x8BBD6EU, 0x872498U, 0x016863U, 0xFAD8C4U, 0x7C943FU, 0x700DC9U, 0xF64132U,
            0x693E25U, 0xEF72DEU, 0xE3EB28U, 0x65A7D3U, 0x5B59FDU, 0xDD1506U, 0xD18CF0U, 0x57C00BU, 0xC8BF1CU,
            0x4EF3E7U, 0x426A11U, 0xC426EAU, 0x2AE476U, 0xACA88DU, 0xA0317BU, 0x267D80U, 0xB90297U, 0x3F4E6CU,
            0x33D79AU, 0xB59B61U, 0x8B654FU, 0x0D29B4U, 0x01B042U, 0x87FCB9U, 0x1883AEU, 0x9ECF55U, 0x9256A3U,
            0x141A58U, 0xEFAAFFU, 0x69E604U, 0x657FF2U, 0xE33309U, 0x7C4C1EU, 0xFA00E5U, 0xF69913U, 0x70D5E8U,
            0x4E2BC6U, 0xC8673DU, 0xC4FECBU, 0x42B230U, 0xDDCD27U, 0x5B81DCU, 0x57182AU, 0xD154D1U, 0x26359FU,
            0xA07964U, 0xACE092U, 0x2AAC69U, 0xB5D37EU, 0x339F85U, 0x3F0673U, 0xB94A88U, 0x87B4A6U, 0x01F85DU,
            0x0D61ABU, 0x8B2D50U, 0x145247U, 0x921EBCU, 0x9E874AU, 0x18CBB1U, 0xE37B16U, 0x6537EDU, 0x69AE1BU,
            0xEFE2E0U, 0x709DF7U, 0xF6D10CU, 0xFA48FAU, 0x7C0401U, 0x42FA2FU, 0xC4B6D4U, 0xC82F22U, 0x4E63D9U,
            0xD11CCEU, 0x575035U, 0x5BC9C3U, 0xDD8538U};

        constexpr DOUBLE MHZ_TO_HZ = 1000000.0;                     // MHz 转 Hz
        constexpr DOUBLE GPS_L1_FREQENCY = 1575.42 * MHZ_TO_HZ;     // GPS L1 Frequency(Hz)
        constexpr DOUBLE GPS_L2_FREQENCY = 1227.60 * MHZ_TO_HZ;     // GPS L2 Frequency(Hz)
        constexpr DOUBLE GPS_L5_FREQENCY = 1176.45 * MHZ_TO_HZ;     // GPS L5 Frequency(Hz)
        constexpr DOUBLE GLO_G1_FREQENCY = 1602.0 * MHZ_TO_HZ;      // GLONASS G1 Frequency(Hz)
        constexpr DOUBLE GLO_G2_FREQENCY = 1246.0 * MHZ_TO_HZ;      // GLONASS G2 Frequency(Hz)
        constexpr DOUBLE GAL_E1_FREQENCY = 1575.42 * MHZ_TO_HZ;     // Galileo E1 Frequency(Hz)
        constexpr DOUBLE GAL_E5A_FREQENCY = 1176.45 * MHZ_TO_HZ;    // Galileo E5A Frequency(Hz)
        constexpr DOUBLE GAL_E5B_FREQENCY = 1207.140 * MHZ_TO_HZ;   // Galileo E5B Frequency(Hz)
        constexpr DOUBLE GAL_E5AB_FREQENCY = 1191.795 * MHZ_TO_HZ;  // Galileo E5(A+B) Frequency(Hz)
        constexpr DOUBLE GAL_E6_FREQENCY = 1278.75 * MHZ_TO_HZ;     // Galileo E6 Frequency(Hz)
        constexpr DOUBLE SBAS_L1_FREQENCY = 1575.42 * MHZ_TO_HZ;    // SBAS L1 Frequency(Hz)
        constexpr DOUBLE SBAS_L5_FREQENCY = 1176.45 * MHZ_TO_HZ;    // SBAS L5 Frequency(Hz)
        constexpr DOUBLE QZSS_L1_FREQENCY = 1575.42 * MHZ_TO_HZ;    // QZSS L1 Frequency(Hz)
        constexpr DOUBLE QZSS_L2_FREQENCY = 1227.60 * MHZ_TO_HZ;    // QZSS L2 Frequency(Hz)
        constexpr DOUBLE QZSS_L5_FREQENCY = 1176.45 * MHZ_TO_HZ;    // QZSS L5 Frequency(Hz)
        constexpr DOUBLE QZSS_LEX_FREQENCY = 1278.75 * MHZ_TO_HZ;   // QZSS LEX Frequency(Hz)
        constexpr DOUBLE BEIDOU_B1_FREQENCY = 1561.098 * MHZ_TO_HZ; // BeiDou B1 Frequency(Hz)
        constexpr DOUBLE BEIDOU_B2_FREQENCY = 1207.140 * MHZ_TO_HZ; // BeiDou B2 Frequency(Hz)
        constexpr DOUBLE BEIDOU_B3_FREQENCY = 1268.52 * MHZ_TO_HZ;  // BeiDou B3 Frequency(Hz)

        const std::map< IGnssDataInterface::SatelliteSystem, std::map< UINT32, DOUBLE > >& GetSatFreqObsMap()
        {
            static const std::map< IGnssDataInterface::SatelliteSystem, std::map< UINT32, DOUBLE > > FREQ_OBS_MAP = {
                {IGnssDataInterface::SYS_GPS,
                 {{IGnssDataInterface::SC_GPS_1C & IGnssDataInterface::SC_REMOVE_MASK, GPS_L1_FREQENCY},
                  {IGnssDataInterface::SC_GPS_1P & IGnssDataInterface::SC_REMOVE_MASK, GPS_L1_FREQENCY},
                  {IGnssDataInterface::SC_GPS_1W & IGnssDataInterface::SC_REMOVE_MASK, GPS_L1_FREQENCY},
                  {IGnssDataInterface::SC_GPS_2C & IGnssDataInterface::SC_REMOVE_MASK, GPS_L2_FREQENCY},
                  {IGnssDataInterface::SC_GPS_2P & IGnssDataInterface::SC_REMOVE_MASK, GPS_L2_FREQENCY},
                  {IGnssDataInterface::SC_GPS_2W & IGnssDataInterface::SC_REMOVE_MASK, GPS_L2_FREQENCY},
                  {IGnssDataInterface::SC_GPS_2S & IGnssDataInterface::SC_REMOVE_MASK, GPS_L2_FREQENCY},
                  {IGnssDataInterface::SC_GPS_2L & IGnssDataInterface::SC_REMOVE_MASK, GPS_L2_FREQENCY},
                  {IGnssDataInterface::SC_GPS_2X & IGnssDataInterface::SC_REMOVE_MASK, GPS_L2_FREQENCY},
                  {IGnssDataInterface::SC_GPS_5I & IGnssDataInterface::SC_REMOVE_MASK, GPS_L5_FREQENCY},
                  {IGnssDataInterface::SC_GPS_5Q & IGnssDataInterface::SC_REMOVE_MASK, GPS_L5_FREQENCY},
                  {IGnssDataInterface::SC_GPS_5X & IGnssDataInterface::SC_REMOVE_MASK, GPS_L5_FREQENCY},
                  {IGnssDataInterface::SC_GPS_1S & IGnssDataInterface::SC_REMOVE_MASK, GPS_L1_FREQENCY},
                  {IGnssDataInterface::SC_GPS_1L & IGnssDataInterface::SC_REMOVE_MASK, GPS_L1_FREQENCY},
                  {IGnssDataInterface::SC_GPS_1X & IGnssDataInterface::SC_REMOVE_MASK, GPS_L1_FREQENCY}}},
                {IGnssDataInterface::SYS_GLO,
                 {{IGnssDataInterface::SC_GLO_1C & IGnssDataInterface::SC_REMOVE_MASK, GLO_G1_FREQENCY},
                  {IGnssDataInterface::SC_GLO_1P & IGnssDataInterface::SC_REMOVE_MASK, GLO_G1_FREQENCY},
                  {IGnssDataInterface::SC_GLO_2C & IGnssDataInterface::SC_REMOVE_MASK, GLO_G2_FREQENCY},
                  {IGnssDataInterface::SC_GLO_2P & IGnssDataInterface::SC_REMOVE_MASK, GLO_G2_FREQENCY}}},
                {IGnssDataInterface::SYS_GAL,
                 {{IGnssDataInterface::SC_GAL_1C & IGnssDataInterface::SC_REMOVE_MASK, GAL_E1_FREQENCY},
                  {IGnssDataInterface::SC_GAL_1A & IGnssDataInterface::SC_REMOVE_MASK, GAL_E1_FREQENCY},
                  {IGnssDataInterface::SC_GAL_1B & IGnssDataInterface::SC_REMOVE_MASK, GAL_E1_FREQENCY},
                  {IGnssDataInterface::SC_GAL_1X & IGnssDataInterface::SC_REMOVE_MASK, GAL_E1_FREQENCY},
                  {IGnssDataInterface::SC_GAL_1Z & IGnssDataInterface::SC_REMOVE_MASK, GAL_E1_FREQENCY},
                  {IGnssDataInterface::SC_GAL_6C & IGnssDataInterface::SC_REMOVE_MASK, GAL_E6_FREQENCY},
                  {IGnssDataInterface::SC_GAL_6A & IGnssDataInterface::SC_REMOVE_MASK, GAL_E6_FREQENCY},
                  {IGnssDataInterface::SC_GAL_6B & IGnssDataInterface::SC_REMOVE_MASK, GAL_E6_FREQENCY},
                  {IGnssDataInterface::SC_GAL_6X & IGnssDataInterface::SC_REMOVE_MASK, GAL_E6_FREQENCY},
                  {IGnssDataInterface::SC_GAL_6Z & IGnssDataInterface::SC_REMOVE_MASK, GAL_E6_FREQENCY},
                  {IGnssDataInterface::SC_GAL_7I & IGnssDataInterface::SC_REMOVE_MASK, GAL_E5B_FREQENCY},
                  {IGnssDataInterface::SC_GAL_7Q & IGnssDataInterface::SC_REMOVE_MASK, GAL_E5B_FREQENCY},
                  {IGnssDataInterface::SC_GAL_7X & IGnssDataInterface::SC_REMOVE_MASK, GAL_E5B_FREQENCY},
                  {IGnssDataInterface::SC_GAL_8I & IGnssDataInterface::SC_REMOVE_MASK, GAL_E5AB_FREQENCY},
                  {IGnssDataInterface::SC_GAL_8Q & IGnssDataInterface::SC_REMOVE_MASK, GAL_E5AB_FREQENCY},
                  {IGnssDataInterface::SC_GAL_8X & IGnssDataInterface::SC_REMOVE_MASK, GAL_E5AB_FREQENCY},
                  {IGnssDataInterface::SC_GAL_5I & IGnssDataInterface::SC_REMOVE_MASK, GAL_E5A_FREQENCY},
                  {IGnssDataInterface::SC_GAL_5Q & IGnssDataInterface::SC_REMOVE_MASK, GAL_E5A_FREQENCY},
                  {IGnssDataInterface::SC_GAL_5X & IGnssDataInterface::SC_REMOVE_MASK, GAL_E5A_FREQENCY}}},
                {IGnssDataInterface::SYS_QZS,
                 {{IGnssDataInterface::SC_QZSS_1C & IGnssDataInterface::SC_REMOVE_MASK, QZSS_L1_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_6S & IGnssDataInterface::SC_REMOVE_MASK, QZSS_LEX_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_6L & IGnssDataInterface::SC_REMOVE_MASK, QZSS_LEX_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_6X & IGnssDataInterface::SC_REMOVE_MASK, QZSS_LEX_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_2S & IGnssDataInterface::SC_REMOVE_MASK, QZSS_L2_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_2L & IGnssDataInterface::SC_REMOVE_MASK, QZSS_L2_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_2X & IGnssDataInterface::SC_REMOVE_MASK, QZSS_L2_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_5I & IGnssDataInterface::SC_REMOVE_MASK, QZSS_L5_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_5Q & IGnssDataInterface::SC_REMOVE_MASK, QZSS_L5_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_5X & IGnssDataInterface::SC_REMOVE_MASK, QZSS_L5_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_1S & IGnssDataInterface::SC_REMOVE_MASK, QZSS_L1_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_1L & IGnssDataInterface::SC_REMOVE_MASK, QZSS_L1_FREQENCY},
                  {IGnssDataInterface::SC_QZSS_1X & IGnssDataInterface::SC_REMOVE_MASK, QZSS_L1_FREQENCY}}},
                {IGnssDataInterface::SYS_SBS,
                 {{IGnssDataInterface::SC_SBAS_1C & IGnssDataInterface::SC_REMOVE_MASK, SBAS_L1_FREQENCY},
                  {IGnssDataInterface::SC_SBAS_5I & IGnssDataInterface::SC_REMOVE_MASK, SBAS_L5_FREQENCY},
                  {IGnssDataInterface::SC_SBAS_5Q & IGnssDataInterface::SC_REMOVE_MASK, SBAS_L5_FREQENCY},
                  {IGnssDataInterface::SC_SBAS_5X & IGnssDataInterface::SC_REMOVE_MASK, SBAS_L5_FREQENCY}}},
                {IGnssDataInterface::SYS_CMP,
                 {{IGnssDataInterface::SC_BDS_2I & IGnssDataInterface::SC_REMOVE_MASK, BEIDOU_B1_FREQENCY},
                  {IGnssDataInterface::SC_BDS_2Q & IGnssDataInterface::SC_REMOVE_MASK, BEIDOU_B1_FREQENCY},
                  {IGnssDataInterface::SC_BDS_2X & IGnssDataInterface::SC_REMOVE_MASK, BEIDOU_B1_FREQENCY},
                  {IGnssDataInterface::SC_BDS_6I & IGnssDataInterface::SC_REMOVE_MASK, BEIDOU_B3_FREQENCY},
                  {IGnssDataInterface::SC_BDS_6Q & IGnssDataInterface::SC_REMOVE_MASK, BEIDOU_B3_FREQENCY},
                  {IGnssDataInterface::SC_BDS_6X & IGnssDataInterface::SC_REMOVE_MASK, BEIDOU_B3_FREQENCY},
                  {IGnssDataInterface::SC_BDS_7I & IGnssDataInterface::SC_REMOVE_MASK, BEIDOU_B2_FREQENCY},
                  {IGnssDataInterface::SC_BDS_7Q & IGnssDataInterface::SC_REMOVE_MASK, BEIDOU_B2_FREQENCY},
                  {IGnssDataInterface::SC_BDS_7X & IGnssDataInterface::SC_REMOVE_MASK, BEIDOU_B2_FREQENCY}}}};

            return FREQ_OBS_MAP;
        }

    } // namespace

    UINT32 CCodecUtilities::GetUnsignedIntBit(const UINT8* const pBuff, const UINT32 ui32Pos, const UINT32 ui32Len)
    {
        UINT32 ui32Bits = 0U;
        if (pBuff == nullptr)
        {
            return ui32Bits;
        }

        std::size_t szIndex = 0U;
        UINT32 ui32BitNum = 0U;
        for (UINT32 i = ui32Pos; i < (ui32Pos + ui32Len); ++i)
        {
            szIndex = static_cast< std::size_t >(i) / static_cast< std::size_t >(BYTE_TO_BIT_COUNT);
            ui32BitNum = DATA_LENGTH_7 - i % BYTE_TO_BIT_COUNT;
            ui32Bits =
                (ui32Bits << DATA_LENGTH_1) + ((static_cast< UINT32 >(pBuff[szIndex]) >> ui32BitNum) & DATA_LENGTH_1);
        }

        return ui32Bits;
    }

    UINT64 CCodecUtilities::GetUnsignedInt64Bit(const UINT8* const pBuff, const UINT32 ui32Pos, const UINT32 ui32Len)
    {
        UINT64 bits = 0U;
        std::size_t szIndex = 0U;
        UINT32 ui32BitNum = 0U;
        for (UINT32 i = ui32Pos; i < (ui32Pos + ui32Len); ++i)
        {
            szIndex = static_cast< std::size_t >(i) / static_cast< std::size_t >(BYTE_TO_BIT_COUNT);
            ui32BitNum = DATA_LENGTH_7 - i % BYTE_TO_BIT_COUNT;
            bits = (bits << DATA_LENGTH_1) + ((static_cast< UINT64 >(pBuff[szIndex]) >> ui32BitNum) & DATA_LENGTH_1);
        }

        return bits;
    }

    //解码有符号二进制
    INT32 CCodecUtilities::GetIntBit(const UINT8* const pBuff, const UINT32 ui32Pos, const UINT32 ui32Len)
    {

        sixents::common::SixentsAssert(pBuff != nullptr, "pBuff is nullptr");
        INT32 i32Result = -1;

        const UINT32 bits = GetUnsignedIntBit(pBuff, ui32Pos, ui32Len);

        if ((ui32Len < DATA_LENGTH_1) || (DATA_LENGTH_32 <= ui32Len))
        {
            return static_cast< INT32 >(bits);
        }

        const BOOL_T check = ((bits & (static_cast< UINT32 >(DATA_LENGTH_1) << (ui32Len - DATA_LENGTH_1))) != ZERO);
        if (!check)
        {
            return static_cast< INT32 >(bits);
        }

        const UINT32 ui32Value = bits | (~ZERO << ui32Len);
        i32Result = static_cast< INT32 >(ui32Value);

        return i32Result;
    }

    DOUBLE CCodecUtilities::GetSignMagnitudeIntBit(const UINT8* const pBuff, const UINT32 ui32Pos, const UINT32 ui32Len)
    {
        const DOUBLE dbValue =
            static_cast< DOUBLE >(GetUnsignedIntBit(pBuff, ui32Pos + DATA_LENGTH_1, ui32Len - DATA_LENGTH_1));
        return (GetUnsignedIntBit(pBuff, ui32Pos, DATA_LENGTH_1) != ZERO) ? -dbValue : dbValue;
    }

    //解码double
    DOUBLE CCodecUtilities::GetDoubleBit(const UINT8* const pBuff, const UINT32 ui32Pos)
    {
        sixents::common::SixentsAssert(pBuff != nullptr, "pBuff is nullptr");

        const DOUBLE dbDataPart1 = static_cast< DOUBLE >(GetIntBit(pBuff, ui32Pos, DATA_LENGTH_32));
        const DOUBLE dbDataPart2 =
            static_cast< DOUBLE >(GetUnsignedIntBit(pBuff, ui32Pos + DATA_LENGTH_32, DATA_LENGTH_6));
        return dbDataPart1 * DB_DOUBLE_LOW_SCALE + dbDataPart2;
    }

    //编码无符号二进制
    UINT32
    CCodecUtilities::SetUnsignedIntBit(string& pBuff, const UINT32 ui32Pos, const UINT32 ui32Len, const UINT32 data)
    {
        if (ui32Len < DATA_LENGTH_1 || DATA_LENGTH_32 < ui32Len)
        {
            return ui32Pos;
        }

        const UINT32 offset = ui32Len - DATA_LENGTH_1;
        UINT32 mask = static_cast< UINT32 >(ONE) << offset;

        const UINT32 ui32End = ui32Pos + ui32Len;
        const UINT32 ui32Length =
            (((ui32End % BYTE_TO_BIT_COUNT) == ZERO) ? (ui32End / BYTE_TO_BIT_COUNT)
                                                     : (ui32End / BYTE_TO_BIT_COUNT + DATA_LENGTH_1));
        if (ui32Length > pBuff.length())
        {
            pBuff.resize(static_cast< std::size_t >(ui32Length), static_cast< char >(ZERO));
        }

        UINT32 ui32Result = 0U;
        std::size_t szIndex = 0U;
        for (UINT32 i = ui32Pos; i < (ui32Pos + ui32Len); ++i)
        {
            szIndex = static_cast< std::size_t >(i) / static_cast< std::size_t >(BYTE_TO_BIT_COUNT);
            ui32Result = static_cast< UINT32 >(DATA_LENGTH_1) << (DATA_LENGTH_7 - i % BYTE_TO_BIT_COUNT);
            UINT8 ui8Value = ZERO;
            if ((data & mask) != 0U)
            {
                ui8Value = static_cast< UINT8 >(pBuff[szIndex]) | static_cast< UINT8 >(ui32Result);
            }
            else
            {
                ui8Value = static_cast< UINT8 >(pBuff[szIndex]) & static_cast< UINT8 >(~ui32Result);
            }
            pBuff[szIndex] = static_cast< CHAR >(ui8Value);

            mask >>= DATA_LENGTH_1;
        }

        return ui32Pos + ui32Len;
    }

    //编码有符号二进制
    UINT32 CCodecUtilities::SetIntBit(string& pBuff, const UINT32 ui32Pos, const UINT32 ui32Len, INT32 i32Data)
    {
        const UINT32 ui32BitNum = ui32Len - ONE;
        UINT32 ui32Result = ONE << ui32BitNum;
        UINT32 ui32Value = static_cast< UINT32 >(i32Data);
        if (i32Data < static_cast< INT32 >(ZERO))
        {
            ui32Value |= ui32Result;
        }
        else
        {
            ui32Result = ~ui32Result;
            ui32Value &= ui32Result;
        }

        return SetUnsignedIntBit(pBuff, ui32Pos, ui32Len, ui32Value);
    }

    //编码有符号量的二进制
    UINT32 CCodecUtilities::SetSignMagnitudeIntBit(string& pBuff, UINT32 ui32Pos, const UINT32 ui32Len, INT32 i32Data)
    {
        UINT32 ui32Value = ZERO;
        if (i32Data < static_cast< INT32 >(ZERO))
        {
            ui32Value = ONE;
            i32Data = -i32Data;
        }
        else
        {
            ui32Value = ZERO;
        }

        ui32Pos = SetUnsignedIntBit(pBuff, ui32Pos, DATA_LENGTH_1, ui32Value);

        return SetUnsignedIntBit(pBuff, ui32Pos, ui32Len - DATA_LENGTH_1, static_cast< UINT32 >(i32Data));
    }

    //编码double
    UINT32 CCodecUtilities::SetDoubleBit(string& pBuff, UINT32 ui32Pos, const DOUBLE dbValue)
    {
        const DOUBLE dbWordHigh = floor(dbValue / DB_DOUBLE_LOW_SCALE);
        ui32Pos = SetIntBit(pBuff, ui32Pos, DATA_LENGTH_32, static_cast< INT32 >(dbWordHigh));

        const DOUBLE dbWordLow = dbValue - dbWordHigh * DB_DOUBLE_LOW_SCALE;
        return SetUnsignedIntBit(pBuff, ui32Pos, DATA_LENGTH_6, static_cast< UINT32 >(dbWordLow));
    }

    // crc校验
    UINT32 CCodecUtilities::RtkCrc24q(const string& strBuff)
    {
        UINT32 ui32Crc = 0U;

        for (std::size_t i = 0U; i < strBuff.length(); ++i)
        {
            ui32Crc =
                ((ui32Crc << DATA_LENGTH_8) & static_cast< UINT32 >(0xFFFFFF))
                ^ TABLE_CRC24Q[((ui32Crc >> DATA_LENGTH_16) ^ static_cast< UINT32 >(static_cast< UINT8 >(strBuff[i])))];
        }

        return ui32Crc;
    }
    UINT32 CCodecUtilities::RtkCrc24q(const UINT8* const pBuff, const UINT32 ui32Len)
    {
        UINT32 ui32Crc = 0U;
        for (std::size_t i = 0U; i < ui32Len; ++i)
        {
            ui32Crc =
                ((ui32Crc << DATA_LENGTH_8) & static_cast< UINT32 >(0xFFFFFF))
                ^ TABLE_CRC24Q[((ui32Crc >> DATA_LENGTH_16) ^ static_cast< UINT32 >(static_cast< UINT8 >(pBuff[i])))];
        }
        return ui32Crc;
    }

    BOOL_T CCodecUtilities::DoubleEqualToZero(const DOUBLE dbValue)
    {
        const BOOL_T bResult = (std::abs(dbValue) <= DBL_EPSILON);
        return bResult;
    }

    /* encode rough range integer ms ---------------------------------------------*/
    UINT32 CCodecUtilities::EncodeMsmIntRrng(const SEpochSatObs& stObs, UINT32 ui32Pos, string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_8, static_cast< UINT32 >(sat.second.m_ui8Milliseconds));
        }
        return ui32Pos;
    }

    UINT32 CCodecUtilities::EncodeMsmSatExInfo(const SEpochSatObs& stObs, UINT32 ui32Pos, string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut, ui32Pos, DATA_LENGTH_4, static_cast< UINT32 >(sat.second.m_ui8ExtendedSatInfo));
        }
        return ui32Pos;
    }

    /* encode rough range modulo 1 ms --------------------------------------------*/
    UINT32 CCodecUtilities::EncodeMsmModRrng(const SEpochSatObs& stObs, UINT32 ui32Pos, string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                strOut,
                ui32Pos,
                DATA_LENGTH_10,
                static_cast< UINT32 >(std::round(sat.second.m_dbModulo1Millisecond / P2_10)));
        }
        return ui32Pos;
    }

    UINT32 CCodecUtilities::EncodeMsmRrate(const SEpochSatObs& stObs, UINT32 ui32Pos, string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            ui32Pos =
                CCodecUtilities::SetIntBit(strOut,
                                           ui32Pos,
                                           DATA_LENGTH_14,
                                           static_cast< INT32 >(std::round(sat.second.m_i32RoughPhaseRangeRates)));
        }
        return ui32Pos;
    }

    UINT32
    CCodecUtilities::EncodeMsmPsrng(const SEpochSatObs& stObs,
                                    UINT32 ui32Pos,
                                    const std::map< INT32, INT32 >& mapCells,
                                    string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            const INT32 i32CellSize = static_cast< INT32 >(mapCells.size());
            for (auto i = 0; i < i32CellSize; ++i)
            {
                const auto iter = mapCells.find(i);
                if (iter != mapCells.end())
                {
                    const auto signalIter = sat.second.m_mapSignalValues.find(iter->second);
                    if (signalIter != sat.second.m_mapSignalValues.end())
                    {
                        auto psrng = signalIter->second.m_dbFinePseudoranges;
                        if (fabs(psrng) > DB_SIGNAL_FINE_PSEUDORANGE_MAX_VALUE)
                        {
                            psrng = DB_SIGNAL_FINE_PSEUDORANGE_INVALID_VALUE;
                        }
                        else
                        {
                            psrng = std::round(psrng / P2_24);
                        }
                        ui32Pos =
                            CCodecUtilities::SetIntBit(strOut, ui32Pos, DATA_LENGTH_15, static_cast< INT32 >(psrng));
                    }
                }
            }
        }

        return ui32Pos;
    }

    UINT32
    CCodecUtilities::EncodeMsmPsrngEx(const SEpochSatObs& stObs,
                                      UINT32 ui32Pos,
                                      const std::map< INT32, INT32 >& mapCells,
                                      string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            const INT32 i32CellSize = static_cast< INT32 >(mapCells.size());
            for (auto i = 0; i < i32CellSize; ++i)
            {
                const auto iter = mapCells.find(i);
                if (iter != mapCells.end())
                {
                    const auto signalIter = sat.second.m_mapSignalValues.find(iter->second);
                    if (signalIter != sat.second.m_mapSignalValues.end())
                    {
                        auto psrng = signalIter->second.m_dbFinePseudorangesWithER;
                        if (fabs(psrng) > DB_SIGNAL_FINE_PSEUDORANGE_MAX_VALUE)
                        {
                            psrng = DB_SIGNAL_FINE_PSEUDORANGE_INVALID_VALUE;
                        }
                        else
                        {
                            psrng = std::round(psrng / P2_29);
                        }
                        ui32Pos =
                            CCodecUtilities::SetIntBit(strOut, ui32Pos, DATA_LENGTH_20, static_cast< INT32 >(psrng));
                    }
                }
            }
        }

        return ui32Pos;
    }

    UINT32
    CCodecUtilities::EncodeMsmPhrng(const SEpochSatObs& stObs,
                                    UINT32 ui32Pos,
                                    const std::map< INT32, INT32 >& mapCells,
                                    string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            const INT32 i32CellSize =
                static_cast< INT32 >(mapCells.size()) * static_cast< INT32 >(stObs.m_mapSatValues.size());
            for (auto i = 0; i < i32CellSize; ++i)
            {
                const auto iter = mapCells.find(i);
                if (iter != mapCells.end())
                {
                    const auto signalIter = sat.second.m_mapSignalValues.find(iter->second);
                    if (signalIter != sat.second.m_mapSignalValues.end())
                    {
                        auto phrng = signalIter->second.m_dbFinePhaserange;
                        if (fabs(phrng) > DB_SIGNAL_FINE_PHASERANGE_MAX_VALUE)
                        {
                            phrng = DB_SIGNAL_FINE_PHASERANGE_INVALID_VALUE;
                        }
                        else
                        {
                            phrng = std::round(phrng / P2_29);
                        }
                        ui32Pos =
                            CCodecUtilities::SetIntBit(strOut, ui32Pos, DATA_LENGTH_22, static_cast< INT32 >(phrng));
                    }
                }
            }
        }
        return ui32Pos;
    }

    UINT32
    CCodecUtilities::EncodeMsmPhrngEx(const SEpochSatObs& stObs,
                                      UINT32 ui32Pos,
                                      const std::map< INT32, INT32 >& mapCells,
                                      string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            const INT32 i32CellSize =
                static_cast< INT32 >(mapCells.size()) * static_cast< INT32 >(stObs.m_mapSatValues.size());
            for (auto i = 0; i < i32CellSize; ++i)
            {
                const auto iter = mapCells.find(i);
                if (iter != mapCells.end())
                {
                    const auto signalIter = sat.second.m_mapSignalValues.find(iter->second);
                    if (signalIter != sat.second.m_mapSignalValues.end())
                    {
                        auto phrng = signalIter->second.m_dbFinePhaserangeWithER;
                        if (fabs(phrng) > DB_SIGNAL_FINE_PHASERANGE_MAX_VALUE)
                        {
                            phrng = DB_SIGNAL_FINE_PHASERANGE_INVALID_VALUE;
                        }
                        else
                        {
                            phrng = std::round(phrng / P2_31);
                        }
                        ui32Pos =
                            CCodecUtilities::SetIntBit(strOut, ui32Pos, DATA_LENGTH_24, static_cast< INT32 >(phrng));
                    }
                }
            }
        }
        return ui32Pos;
    }

    UINT32
    CCodecUtilities::EncodeMsmLock(const SEpochSatObs& stObs,
                                   UINT32 ui32Pos,
                                   const std::map< INT32, INT32 >& mapCells,
                                   string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            const INT32 i32CellSize =
                static_cast< INT32 >(mapCells.size()) * static_cast< INT32 >(stObs.m_mapSatValues.size());

            for (auto i = 0; i < i32CellSize; ++i)
            {
                const auto iter = mapCells.find(i);
                if (iter != mapCells.end())
                {
                    const auto itSignal = sat.second.m_mapSignalValues.find(iter->second);
                    if (itSignal != sat.second.m_mapSignalValues.end())
                    {
                        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                            strOut,
                            ui32Pos,
                            DATA_LENGTH_4,
                            static_cast< UINT32 >(itSignal->second.m_ui8LockTimeIndicator));
                    }
                }
            }
        }

        return ui32Pos;
    }

    UINT32
    CCodecUtilities::EncodeMsmLockEx(const SEpochSatObs& stObs,
                                     UINT32 ui32Pos,
                                     const std::map< INT32, INT32 >& mapCells,
                                     string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            const INT32 i32CellSize =
                static_cast< INT32 >(mapCells.size()) * static_cast< INT32 >(stObs.m_mapSatValues.size());
            for (auto i = 0; i < i32CellSize; ++i)
            {
                const auto iter = mapCells.find(i);
                if (iter != mapCells.end())
                {
                    const auto itSignal = sat.second.m_mapSignalValues.find(iter->second);
                    if (itSignal != sat.second.m_mapSignalValues.end())
                    {
                        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                            strOut,
                            ui32Pos,
                            DATA_LENGTH_10,
                            static_cast< UINT32 >(itSignal->second.m_ui16PLTIWithERAR));
                    }
                }
            }
        }

        return ui32Pos;
    }

    UINT32 CCodecUtilities::EncodeMsmHalfAmb(const SEpochSatObs& stObs,
                                             UINT32 ui32Pos,
                                             const std::map< INT32, INT32 >& mapCells,
                                             string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            const INT32 i32CellSize =
                static_cast< INT32 >(mapCells.size()) * static_cast< INT32 >(stObs.m_mapSatValues.size());
            for (auto i = 0; i < i32CellSize; ++i)
            {
                const auto iter = mapCells.find(i);
                if (iter != mapCells.end())
                {
                    const auto itSignal = sat.second.m_mapSignalValues.find(iter->second);
                    if (itSignal != sat.second.m_mapSignalValues.end())
                    {
                        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                            strOut, ui32Pos, DATA_LENGTH_1, static_cast< UINT32 >(itSignal->second.m_ui8HCAI));
                    }
                }
            }
        }

        return ui32Pos;
    }

    UINT32
    CCodecUtilities::EncodeMsmCnr(const SEpochSatObs& stObs,
                                  UINT32 ui32Pos,
                                  const std::map< INT32, INT32 >& mapCells,
                                  string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            const INT32 i32CellSize =
                static_cast< INT32 >(mapCells.size()) * static_cast< INT32 >(stObs.m_mapSatValues.size());
            for (auto i = 0; i < i32CellSize; ++i)
            {
                const auto iter = mapCells.find(i);
                if (iter != mapCells.end())
                {
                    const auto itSignal = sat.second.m_mapSignalValues.find(iter->second);
                    if (itSignal != sat.second.m_mapSignalValues.end())
                    {
                        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                            strOut,
                            ui32Pos,
                            DATA_LENGTH_6,
                            static_cast< UINT32 >(std::round(itSignal->second.m_dbSignalCnr)));
                    }
                }
            }
        }

        return ui32Pos;
    }

    UINT32
    CCodecUtilities::EncodeMsmCnrEx(const SEpochSatObs& stObs,
                                    UINT32 ui32Pos,
                                    const std::map< INT32, INT32 >& mapCells,
                                    string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            const INT32 i32CellSize =
                static_cast< INT32 >(mapCells.size()) * static_cast< INT32 >(stObs.m_mapSatValues.size());
            for (auto i = 0; i < i32CellSize; ++i)
            {
                const auto iter = mapCells.find(i);
                if (iter != mapCells.end())
                {
                    const auto itSignal = sat.second.m_mapSignalValues.find(iter->second);
                    if (itSignal != sat.second.m_mapSignalValues.end())
                    {
                        auto cnr_val = itSignal->second.m_dbSignalCnrsWER;
                        cnr_val = std::round(cnr_val / P2_4);
                        ui32Pos = CCodecUtilities::SetUnsignedIntBit(
                            strOut, ui32Pos, DATA_LENGTH_10, static_cast< UINT32 >(cnr_val));
                    }
                }
            }
        }

        return ui32Pos;
    }

    UINT32
    CCodecUtilities::EncodeMsmRate(const SEpochSatObs& stObs,
                                   UINT32 ui32Pos,
                                   const std::map< INT32, INT32 >& mapCells,
                                   string& strOut)
    {
        for (auto& sat : stObs.m_mapSatValues)
        {
            const INT32 i32CellSize =
                static_cast< INT32 >(mapCells.size()) * static_cast< INT32 >(stObs.m_mapSatValues.size());
            for (auto i = 0; i < i32CellSize; ++i)
            {
                const auto iter = mapCells.find(i);
                if (iter != mapCells.end())
                {
                    const auto itSignal = sat.second.m_mapSignalValues.find(iter->second);
                    if (itSignal != sat.second.m_mapSignalValues.end())
                    {
                        auto cnr_val = itSignal->second.m_dbFPRates;
                        cnr_val = std::round(cnr_val / SCALE_1E_4);
                        ui32Pos =
                            CCodecUtilities::SetIntBit(strOut, ui32Pos, DATA_LENGTH_15, static_cast< INT32 >(cnr_val));
                    }
                }
            }
        }

        return ui32Pos;
    }

    DOUBLE
    CCodecUtilities::GetSatWaveLen(const IGnssDataInterface::SatelliteSystem eSys,
                                   const IGnssDataInterface::SignalCode eSig,
                                   const UINT8 ui8SatFrequencyChannelNumber)
    {

        DOUBLE dbResult = 0.0;
        auto mapFreqObs = GetSatFreqObsMap();
        auto satIter = mapFreqObs.find(eSys);
        if (satIter != mapFreqObs.end())
        {
            auto sigIter = satIter->second.find(eSig & IGnssDataInterface::SC_REMOVE_MASK);
            if (sigIter != satIter->second.end())
            {
                DOUBLE dbFrq = sigIter->second;
                if (eSys == IGnssDataInterface::SYS_GLO) // GLONASS
                {
                    if (DoubleEqualToZero(GLO_G1_FREQENCY - dbFrq))
                    {
                        // 参考RTCM STANDARD 10403.3  Table 3.5-73  GLONASS G1 比例因子
                        static constexpr DOUBLE GloG1FrequencyExScale = 9.0 / 16.0;
                        DOUBLE dbFrqNum =
                            static_cast< DOUBLE >(ui8SatFrequencyChannelNumber) - static_cast< DOUBLE >(SCALE_DF419);
                        dbFrq += static_cast< DOUBLE >(dbFrqNum) * GloG1FrequencyExScale * MHZ_TO_HZ;
                    }
                    else if (DoubleEqualToZero(GLO_G2_FREQENCY - dbFrq))
                    {
                        // 参考RTCM STANDARD 10403.3  Table 3.5-73  GLONASS G2 比例因子
                        static constexpr DOUBLE GloG2FrequencyExScale = 7.0 / 16.0;
                        DOUBLE dbFrqNum =
                            static_cast< DOUBLE >(ui8SatFrequencyChannelNumber) - static_cast< DOUBLE >(SCALE_DF419);
                        dbFrq += static_cast< DOUBLE >(dbFrqNum) * GloG2FrequencyExScale * MHZ_TO_HZ;
                    }
                    else
                    {
                        // Do nothing
                    }
                }

                if (!DoubleEqualToZero(dbFrq))
                {
                    dbResult = CLIGHT / dbFrq;
                }
            }
        }

        return dbResult;
    }
} // namespace sixents
