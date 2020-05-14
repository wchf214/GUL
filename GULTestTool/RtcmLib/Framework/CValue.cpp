/*
 * Copyright (c) Beijing Sixents Technology Co., Ltd. 2018-2019. All rights reserved.
 * Description: Parse variable to different type
 * Author: yangzhenxing
 * Create: 2018-11-08
 */
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <sstream>

#include "CommonFunc.h"
#include "CValue.h"

using namespace std;
using namespace sixents;

namespace
{
    const UINT32 CVALUE_INT_4 = 4U;
    const UINT32 CVALUE_INT_8 = 8U;
    const UINT32 CVALUE_INT_10 = 10U;
    const UINT32 CVALUE_INT_55 = 55U;
    const UINT8 CVALUE_CHAR_A = static_cast< UINT8 >('A');
    const UINT8 CVALUE_CHAR_SA = static_cast< UINT8 >('a');
    const UINT8 CVALUE_CHAR_F = static_cast< UINT8 >('F');
    const UINT8 CVALUE_CHAR_0 = static_cast< UINT8 >('0');
    const UINT8 CVALUE_CHAR_9 = static_cast< UINT8 >('9');
} // namespace
PARAM_DATA_TYPE CValue::GetType()
{
    return m_enDataType;
}

string CValue::GetTypeString() const
{
    string strType;

    switch (this->m_enDataType)
    {
        case PDT_INT:
        {
            strType = STR_VALUE_TYPE_INT;
        }
        break;
        case PDT_DOUBLE:
        {
            strType = STR_VALUE_TYPE_DOUBLE;
        }
        break;
        case PDT_STRING:
        {
            strType = STR_VALUE_TYPE_STRING;
        }
        break;
        case PDT_INT_ARR:
        {
            strType = STR_VALUE_TYPE_INT_ARRAY;
        }
        break;
        case PDT_DOUBLE_ARR:
        {
            strType = STR_VALUE_TYPE_DOUBLE_ARRAY;
        }
        break;
        case PDT_BYTE_ARRAY:
        {
            strType = STR_VALUE_TYPE_BYTE_ARRAY;
        }
        break;
        default:
        {
            strType = STR_VALUE_TYPE_INT;
        }
        break;
    }

    return strType;
}

CValue* CValue::CreateValueByType(const PARAM_DATA_TYPE enValueType)
{
    CValue* pValue = nullptr;

    switch (enValueType)
    {
        case PDT_POINTER:
        {
            pValue = static_cast< CValue* >(new CValuePointer());
        }
        break;
        case PDT_INT:
        {
            pValue = static_cast< CValue* >(new CValueInt());
        }
        break;
        case PDT_DOUBLE:
        {
            pValue = static_cast< CValue* >(new CValueDouble());
        }
        break;
        case PDT_STRING:
        {
            pValue = static_cast< CValue* >(new CValueString());
        }
        break;
        case PDT_INT_ARR:
        {
            pValue = static_cast< CValue* >(new CValueIntArray());
        }
        break;
        case PDT_DOUBLE_ARR:
        {
            pValue = static_cast< CValue* >(new CValueDoubleArray());
        }
        break;
        case PDT_BYTE_ARRAY:
        {
            pValue = static_cast< CValue* >(new CValueByteArray());
        }
        break;
        default:
        {
            // Do nothing
        }
        break;
    }
    return pValue;
};

CValueDouble::CValueDouble()
    : CValue()
    , m_dbValue(0.0)
{
    m_enDataType = PDT_DOUBLE;
}

PARAM_DATA_TYPE CValueDouble::GetType()
{
    return m_enDataType;
}

BOOL_T CValueDouble::SetValue(PVOID const pvValue, PVOID const pvParam)
{
    UNREFERENCED_PARAMETER(pvParam);
    if (pvValue == nullptr)
    {
        return false;
    }

    m_dbValue = *(static_cast< DOUBLE* >(pvValue));
    return true;
}

BOOL_T CValueDouble::GetValue(PVOID const pvValue, PVOID const pvParam)
{
    UNREFERENCED_PARAMETER(pvParam);
    DOUBLE* const pdbTmp = static_cast< DOUBLE* >(pvValue);
    if (pdbTmp == nullptr)
    {
        return false;
    }

    *pdbTmp = m_dbValue;
    return true;
}

BOOL_T CValueDouble::GetStringValue(string& strValue)
{
    strValue = to_string(m_dbValue);
    return true;
}

BOOL_T CValueDouble::SetStringValue(const string& strValue)
{
    try
    {
        m_dbValue = stod(strValue);
    }
    catch (exception&)
    {
        return false;
    }

    return true;
}

BOOL_T CValueDouble::Clone(PPCValue const ppValueRet)
{
    BOOL_T ret = false;
    CValue* pobjValueNew = nullptr;

    do
    {
        if (ppValueRet == nullptr)
        {
            break;
        }

        pobjValueNew = new CValueDouble();
        if (pobjValueNew == nullptr)
        {
            break;
        }

        if (pobjValueNew->SetValue(&m_dbValue, nullptr) == false)
        {
            break;
        }

        *ppValueRet = pobjValueNew;
        pobjValueNew = nullptr;

        ret = true;
    } while (false);

    if (ret == false)
    {
        if (pobjValueNew != nullptr)
        {
            delete pobjValueNew;
            pobjValueNew = nullptr;
        }
    }

    return ret;
}

PVOID CValueDouble::CreateValueObj()
{
    PVOID const pvObj = dynamic_cast< PVOID >(new CValueDouble());
    return pvObj;
}

CValueInt::CValueInt()
    : CValue()
    , m_i32Value(0)
{
    m_enDataType = PDT_INT;
}

PARAM_DATA_TYPE CValueInt::GetType()
{
    return m_enDataType;
}

BOOL_T CValueInt::SetValue(PVOID const pvValue, PVOID const pvParam)
{
    UNREFERENCED_PARAMETER(pvParam);
    INT32* const piTemp = static_cast< INT32* >(pvValue);
    if (piTemp == nullptr)
    {
        return false;
    }

    m_i32Value = *piTemp;
    return true;
}

BOOL_T CValueInt::GetValue(PVOID const pvValue, PVOID const pvParam)
{
    UNREFERENCED_PARAMETER(pvParam);
    if (pvValue == nullptr)
    {
        return false;
    }

    *(static_cast< INT32* >(pvValue)) = m_i32Value;
    return true;
}

BOOL_T CValueInt::GetStringValue(string& strValue)
{
    try
    {
        strValue = to_string(m_i32Value);
    }
    catch (exception&)
    {
        return false;
    }

    return true;
}

BOOL_T CValueInt::SetStringValue(const string& strValue)
{
    try
    {
        m_i32Value = stoi(strValue);
    }
    catch (exception&)
    {
        return false;
    }

    return true;
}

BOOL_T CValueInt::Clone(PPCValue const ppValueRet)
{
    BOOL_T ret = false;
    CValue* pobjValueNew = nullptr;

    do
    {
        if (ppValueRet == nullptr)
        {
            break;
        }

        pobjValueNew = new CValueInt();
        if (pobjValueNew == nullptr)
        {
            break;
        }

        if (pobjValueNew->SetValue(&m_i32Value, nullptr) == false)
        {
            break;
        }

        *ppValueRet = pobjValueNew;
        pobjValueNew = nullptr;

        ret = true;
    } while (false);

    if (ret == false)
    {
        if (pobjValueNew != nullptr)
        {
            delete pobjValueNew;
            pobjValueNew = nullptr;
        }
    }

    return ret;
}

PVOID CValueInt::CreateValueObj()
{
    PVOID const pvObj = dynamic_cast< PVOID >(new CValueInt());
    return pvObj;
}

CValuePointer::CValuePointer()
    : CValue()
    , m_pvValue(nullptr)
{
    m_enDataType = PDT_POINTER;
}

PARAM_DATA_TYPE CValuePointer::GetType()
{
    return m_enDataType;
}

BOOL_T CValuePointer::SetValue(PVOID const pvValue, PVOID const pvParam)
{
    UNREFERENCED_PARAMETER(pvParam);
    if (pvValue == nullptr)
    {
        return false;
    }

    m_pvValue = pvValue;
    return true;
}

BOOL_T CValuePointer::GetValue(PVOID const pvValue, PVOID const pvParam)
{
    UNREFERENCED_PARAMETER(pvParam);
    if (pvValue == nullptr)
    {
        return false;
    }

    *(static_cast< PVOID* >(pvValue)) = m_pvValue;
    return true;
}

BOOL_T CValuePointer::GetStringValue(string& strValue)
{
    ostringstream ostr;
    ostr << hex << setw(static_cast< std::streamsize >(CVALUE_INT_8)) << setfill('0') << m_pvValue << endl;
    strValue = ostr.str();

    return true;
}

BOOL_T CValuePointer::SetStringValue(const string& strValue)
{
    stringstream objStrStream;
    objStrStream << strValue;
    objStrStream >> m_pvValue;

    return true;
}

BOOL_T CValuePointer::Clone(PPCValue const ppValueRet)
{
    BOOL_T ret = false;
    CValue* pobjValueNew = nullptr;

    do
    {
        if (ppValueRet == nullptr)
        {
            break;
        }

        pobjValueNew = static_cast< CValue* >(new CValuePointer());
        if (pobjValueNew == nullptr)
        {
            break;
        }

        if (pobjValueNew->SetValue(m_pvValue, nullptr) == false)
        {
            break;
        }

        *ppValueRet = pobjValueNew;
        pobjValueNew = nullptr;

        ret = true;
    } while (false);

    if (ret == false)
    {
        if (pobjValueNew != nullptr)
        {
            delete pobjValueNew;
            pobjValueNew = nullptr;
        }
    }

    return ret;
}

PVOID CValuePointer::CreateValueObj()
{
    PVOID const pvObj = dynamic_cast< PVOID >(new CValuePointer());
    return pvObj;
}

CValueString::CValueString()
    : CValue()
{
    m_enDataType = PDT_STRING;
}

PARAM_DATA_TYPE CValueString::GetType()
{
    return m_enDataType;
}

BOOL_T CValueString::SetValue(PVOID const pvValue, PVOID const pvParam)
{
    UNREFERENCED_PARAMETER(pvParam);
    string* const pstrValue = reinterpret_cast< string* >(pvValue);
    if (pstrValue == nullptr)
    {
        return false;
    }

    m_strValue = *pstrValue;

    return true;
}

BOOL_T CValueString::GetValue(PVOID const pvValue, PVOID const pvParam)
{
    UNREFERENCED_PARAMETER(pvParam);
    if (pvValue == nullptr)
    {
        return false;
    }

    *(reinterpret_cast< string* >(pvValue)) = m_strValue;

    return true;
}

BOOL_T CValueString::GetStringValue(string& strValue)
{
    strValue = m_strValue;
    return true;
}

BOOL_T CValueString::SetStringValue(const string& strValue)
{
    m_strValue = strValue;
    return true;
}

BOOL_T CValueString::Clone(PPCValue const ppValueRet)
{
    BOOL_T ret = false;
    CValue* pobjValueNew = nullptr;

    do
    {
        if (ppValueRet == nullptr)
        {
            break;
        }

        pobjValueNew = static_cast< CValue* >(new CValueString());
        if (pobjValueNew == nullptr)
        {
            break;
        }

        if (pobjValueNew->SetStringValue(m_strValue) == false)
        {
            break;
        }

        *ppValueRet = pobjValueNew;
        pobjValueNew = nullptr;

        ret = true;
    } while (false);

    if (ret == false)
    {
        if (pobjValueNew != nullptr)
        {
            delete pobjValueNew;
            pobjValueNew = nullptr;
        }
    }

    return ret;
}

PVOID CValueString::CreateValueObj()
{
    PVOID const pvObj = dynamic_cast< PVOID >(new CValueString());
    return pvObj;
}

CValueByteArray::CValueByteArray()
    : CValue()
{
    m_enDataType = PDT_BYTE_ARRAY;
}

PARAM_DATA_TYPE CValueByteArray::GetType()
{
    return m_enDataType;
}

BOOL_T CValueByteArray::SetValue(PVOID const pvValue, PVOID const pvParam)
{
    // if pvValue is non-null and pvParam is null , pvValue will be regarded as "ByteArray" object
    if ((pvValue != nullptr) && (pvParam == nullptr))
    {
        string* pobjValue = nullptr;
        pobjValue = reinterpret_cast< string* >(pvValue);
        if (pobjValue == nullptr)
        {
            return false;
        }

        m_objValues = *pobjValue;
        return true;
    }
    else if ((pvValue != nullptr) && (pvParam != nullptr))
    {
        // if both pvValue and pvParam are non-null,  pvValue will be regarded as "BYTE*" object
        // and pvParam is regarded as length of current pvValue(Byte*), *"UINT32" ,
        // [INPUT](pvParam) means the length of buffer size
        CHAR* const pbyBuf = static_cast< CHAR* >(pvValue);
        const UINT32 uiLen = static_cast< UINT32 >(reinterpret_cast< intptr_t >(pvParam));

        if ((pbyBuf == nullptr) || (uiLen == 0U))
        {
            return false;
        }

        m_objValues.assign(pbyBuf, static_cast< std::size_t >(uiLen));
        return true;
    }
    else
    {
        // Do nothing
    }

    return false;
}

BOOL_T CValueByteArray::GetValue(PVOID const pvValue, PVOID const pvParam)
{
    // 20191223 modified by yangchengyi
    if ((pvValue == nullptr) && (pvParam != nullptr))
    {
        *static_cast< UINT32* >(pvParam) = static_cast< UINT32 >(m_objValues.length());
        return true;
    }
    else if (pvValue != nullptr)
    {
        const UINT32 len = static_cast< UINT32 >(reinterpret_cast< intptr_t >(pvParam));
        if (len != 0U)
        {
            const CHAR* const pPtr = m_objValues.c_str();
            memcpy(
                pvValue, pPtr, min(static_cast< std::size_t >(len), static_cast< std::size_t >(m_objValues.length())));
            return true;
        }
        else
        {
            string* const pbaRet = reinterpret_cast< string* >(pvValue);
            if (pbaRet == nullptr)
            {
                return false;
            }

            *pbaRet = m_objValues;
            return true;
        }
    }
    else
    {
        // Do nothing
    }

    return false;
}

BOOL_T CValueByteArray::GetStringValue(string& strValue)
{
    strValue = common::HexStr2Str(m_objValues);
    return true;
}

BOOL_T CValueByteArray::SetStringValue(const string& strValue)
{
    m_objValues = common::Str2HexStr(strValue);
    return true;
}

BOOL_T CValueByteArray::Clone(PPCValue const ppValueRet)
{
    BOOL_T ret = false;
    CValue* pobjValueNew = nullptr;

    do
    {
        if (ppValueRet == nullptr)
        {
            break;
        }

        pobjValueNew = static_cast< CValue* >(new CValueByteArray());
        if (pobjValueNew == nullptr)
        {
            break;
        }

        if (pobjValueNew->SetValue(&m_objValues, nullptr) == false)
        {
            break;
        }

        *ppValueRet = pobjValueNew;
        pobjValueNew = nullptr;

        ret = true;
    } while (false);

    if (ret == false)
    {
        if (pobjValueNew != nullptr)
        {
            delete pobjValueNew;
            pobjValueNew = nullptr;
        }
    }

    return ret;
}

PVOID CValueByteArray::CreateValueObj()
{
    PVOID const pvObj = dynamic_cast< PVOID >(new CValueByteArray());
    return pvObj;
}

CValueIntArray::CValueIntArray()
    : CValue()
{
    m_enDataType = PDT_INT_ARR;
}

PARAM_DATA_TYPE CValueIntArray::GetType()
{
    return m_enDataType;
}

BOOL_T CValueIntArray::SetValue(PVOID const pvValue, PVOID const pvParam)
{
    BOOL_T bRet = false;
    INT32* piIn = nullptr;
    UINT32 uiLen = 0U;

    do
    {
        if ((pvValue == nullptr) || (pvParam == nullptr))
        {
            break;
        }

        piIn = static_cast< INT32* >(pvValue);
        uiLen = static_cast< UINT32 >(reinterpret_cast< intptr_t >(pvParam));
        if ((piIn == nullptr) || (uiLen == 0U))
        {
            break;
        }

        m_objValues.clear();
        while (uiLen > 0U)
        {
            m_objValues.push_back(*piIn);
            piIn++;
            uiLen--;
        }
        bRet = true;
    } while (false);

    return bRet;
}

BOOL_T CValueIntArray::GetValue(PVOID const pvValue, PVOID const pvParam)
{
    BOOL_T bRet = false;
    INT32* piOut = nullptr;
    UINT32* puiLen = nullptr;

    do
    {
        if ((pvValue == nullptr) || (pvParam == nullptr))
        {
            break;
        }

        piOut = static_cast< INT32* >(pvValue);
        puiLen = static_cast< UINT32* >(pvParam);
        if ((puiLen == nullptr) || (*puiLen == 0U))
        {
            break;
        }

        if (piOut == nullptr)
        {
            *puiLen = static_cast< UINT32 >(m_objValues.size());
            bRet = true;
            break;
        }

        if (*puiLen < static_cast< UINT32 >(m_objValues.size()))
        {
            break;
        }

        *puiLen = static_cast< UINT32 >(m_objValues.size());

        auto it = m_objValues.begin();
        while (*puiLen > 0U)
        {
            *piOut = *it;
            it++;
            piOut++;
            (*puiLen)--;
        }
        bRet = true;
    } while (false);

    return bRet;
}

BOOL_T CValueIntArray::GetStringValue(string& strValue)
{
    string strSum("{");

    ostringstream ostr;
    for (const auto item : m_objValues)
    {
        ostr << item << ",";
    }
    strSum = ostr.str();

    if (*strSum.rbegin() == ',')
    {
        *strSum.rbegin() = '}';
    }

    strValue = move(strSum);
    return true;
}

BOOL_T CValueIntArray::SetStringValue(const string& strValue)
{
    const BOOL_T ret = true;
    INT32 iTemp = 0;

    string strParse = strValue;
    strParse = common::Trim(strParse, " ");

    strParse.erase(strParse.find_first_of('{'));
    strParse.erase(strParse.find_last_of('}'));
    m_objValues.clear();
    while (true)
    {
        if (strParse.empty() == true)
        {
            break;
        }
        const size_t pos = strParse.find(',');
        const string strTemp = strParse.substr(0U, pos);
        strParse = strParse.substr(pos + 1U);

        iTemp = stoi(strTemp);
        m_objValues.push_back(iTemp);
    }

    return ret;
}

BOOL_T CValueIntArray::Clone(PPCValue const ppValueRet)
{
    BOOL_T ret = false;
    CValue* pobjValueNew = nullptr;

    do
    {
        if (!ppValueRet)
        {
            break;
        }

        pobjValueNew = new CValueIntArray();
        if (!pobjValueNew)
        {
            break;
        }

        if (!pobjValueNew->SetValue(&m_objValues, nullptr))
        {
            break;
        }

        *ppValueRet = pobjValueNew;
        pobjValueNew = nullptr;

        ret = true;
    } while (false);
    if (!ret)
    {
        if (pobjValueNew != nullptr)
        {
            delete pobjValueNew;
            pobjValueNew = nullptr;
        }
    }

    return ret;
}

PVOID CValueIntArray::CreateValueObj()
{
    PVOID const pvObj = dynamic_cast< PVOID >(new CValueIntArray());
    return pvObj;
}

CValueDoubleArray::CValueDoubleArray()
    : CValue()
{
    m_enDataType = PDT_DOUBLE_ARR;
}

PARAM_DATA_TYPE CValueDoubleArray::GetType()
{
    return m_enDataType;
}

BOOL_T CValueDoubleArray::SetValue(PVOID const pvValue, PVOID const pvParam)
{

    BOOL_T bRet = false;
    DOUBLE* pdbIn = nullptr;
    UINT32 uiLen = 0U;

    do
    {
        if ((pvValue == nullptr) || (pvParam == nullptr))
        {
            break;
        }

        pdbIn = static_cast< DOUBLE* >(pvValue);
        uiLen = static_cast< UINT32 >(reinterpret_cast< intptr_t >(pvParam));
        if ((pdbIn == nullptr) || (uiLen == 0U))
        {
            break;
        }

        m_objValues.clear();
        while (uiLen > 0U)
        {
            m_objValues.push_back(*pdbIn);
            pdbIn++;
            uiLen--;
        }
        bRet = true;
    } while (false);

    return bRet;
}

BOOL_T CValueDoubleArray::GetValue(PVOID const pvValue, PVOID const pvParam)
{
    BOOL_T bRet = false;
    DOUBLE* pdbIn = nullptr;
    UINT32* puiLen = nullptr;

    do
    {
        if ((pvValue == nullptr) || (pvParam == nullptr))
        {
            break;
        }

        pdbIn = static_cast< DOUBLE* >(pvValue);
        puiLen = static_cast< UINT32* >(pvParam);
        if ((puiLen == nullptr) || (*puiLen == 0U))
        {
            break;
        }

        if (pdbIn == nullptr)
        {
            *puiLen = static_cast< UINT32 >(m_objValues.size());
            bRet = true;
            break;
        }

        if (*puiLen < static_cast< UINT32 >(m_objValues.size()))
        {
            break;
        }

        *puiLen = static_cast< UINT32 >(m_objValues.size());

        auto it = m_objValues.begin();
        while (*puiLen > 0U)
        {
            *pdbIn = *it;
            it++;
            pdbIn++;
            (*puiLen)--;
        }
        bRet = true;
    } while (false);

    return bRet;
}

BOOL_T CValueDoubleArray::GetStringValue(string& strValue)
{
    string strSum;

    strSum.clear();

    ostringstream ostr;
    for (const auto item : m_objValues)
    {
        ostr << item << ",";
    }
    strSum = ostr.str();

    if (*strSum.rbegin() == ',')
    {
        *strSum.rbegin() = '}';
    }

    strValue = strSum;
    return true;
}

BOOL_T CValueDoubleArray::SetStringValue(const string& strValue)
{
    const BOOL_T ret = true;
    DOUBLE dbTemp = 0.0;

    string strParse = strValue;
    strParse = common::Trim(strParse, " ");

    strParse.erase(strParse.find_first_of('{'));
    strParse.erase(strParse.find_last_of('}'));
    m_objValues.clear();
    while (true)
    {
        if (strParse.empty() == true)
        {
            break;
        }
        const size_t pos = strParse.find(',');
        const string strTemp = strParse.substr(0U, pos);
        strParse = strParse.substr(pos + 1U);

        dbTemp = stod(strTemp);
        m_objValues.push_back(dbTemp);
    }

    return ret;
}

BOOL_T CValueDoubleArray::Clone(PPCValue const ppValueRet)
{
    BOOL_T ret = false;
    CValue* pobjValueNew = nullptr;

    do
    {
        if (!ppValueRet)
        {
            break;
        }
        pobjValueNew = static_cast< CValue* >(new CValueDoubleArray());
        if (!pobjValueNew)
        {
            break;
        }

        if (!pobjValueNew->SetValue(&m_objValues, nullptr))
        {
            break;
        }

        *ppValueRet = pobjValueNew;
        pobjValueNew = nullptr;

        ret = true;
    } while (false);

    if (!ret)
    {
        if (pobjValueNew != nullptr)
        {
            delete pobjValueNew;
            pobjValueNew = nullptr;
        }
    }

    return ret;
}

PVOID CValueDoubleArray::CreateValueObj()
{
    PVOID const pvObj = dynamic_cast< PVOID >(new CValueDoubleArray());
    return pvObj;
}
