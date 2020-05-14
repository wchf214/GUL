/**
 * @copyright   Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 * @file        CValue.h
 * @author      yangzhenxing/yangzhenxing@sixents.com
 * @version     1.0
 * @date        2019-12-20
 * @brief       以CValue 为基类的数据封装类，作为CParam的依赖和关联的基本单元
 * @details 本模块包含多个类型的数据封装类，通过统一的基类虚方法,实现了对各种数据的序列化和反序列化以及数据设置/读取功能
 * @note        N/A
 *    change history:
 *    <2019-12-20>  | 1.0 | yangchenyi | 创建初始版本
 */

#ifndef _VALUE_H_
#define _VALUE_H_

#include <vector>

#include "../Platform/BasicType.h"

namespace sixents
{
    using std::string;

    const std::string STR_VALUE_TYPE_INT = "int";
    const std::string STR_VALUE_TYPE_DOUBLE = "double";
    const std::string STR_VALUE_TYPE_STRING = "string";
    const std::string STR_VALUE_TYPE_INT_ARRAY = "int_array";
    const std::string STR_VALUE_TYPE_CHAR_ARRAY = "char_array";
    const std::string STR_VALUE_TYPE_DOUBLE_ARRAY = "double_array";
    const std::string STR_VALUE_TYPE_BYTE_ARRAY = "byte_array";
    const std::string STR_VALUE_TYPE_POINTER = "pointer";

    /**
     * @class      CValue
     * @brief      数据封装类的基类，定义了常用的虚接口
     * @author     yangzhenxing@sixents.com
     * @note       N/A
     */
    class CValue
    {
    public:
        using PPCValue = CValue**;

        CValue()
            : m_enDataType(PDT_TYPE_MASK)
        {}
        virtual ~CValue() = default;

        /**
         * @brief        GetType()  获取参数类型
         * @author       yangzhenxing@sixents.com
         * @param[out]   N/A
         * @exception    N/A
         * @return       PARAM_DATA_TYPE
         * @retval       PARAM_DATA_TYPE 枚举类型
         * @note         N/A
         */
        virtual PARAM_DATA_TYPE GetType();

        /**
         * @brief       SetValue()  获取参数值
         * @author      yangzhenxing@sixents.com
         * @param[in]   pvValue:指针参数
                        pvParam:指针参数
                        不同的PARAM_DATA_TYPE类型，pvValue和pvParam的处理不一样，下面一一列举
                        CValueInt:pvValue 为int*指针,pvParam 无效
                        CValueDouble:pvValue 为double*指针 ,pvParam 无效
                        CValueString:pvValue 为std::string*指针 ,pvParam 无效
                        CValuePointer:pvValue 指向指针的内存地址(即双重指针),pvParam 无效
                        CValueByteArray:pvValue 指向存放BYTE数组的内存地址,pvParam 为unsigned int类型，用于表示输入长度
                        CValueIntArray:pvValue 指向存放Int数组的内存地址,pvParam 为unsigned int类型，用于表示输入长度
                        CValueDoubleArray:pvValue 指向存放double数组的地址,pvParam 为unsigned
         int类型，用于表示输入长度ouble长度
         * @param[out]  N/A
         * @exception   N/A
         * @return      BOOL_T
         * @retval      (true,false)
         * @note        N/A
         */
        virtual BOOL_T SetValue(PVOID pvValue, PVOID pvParam) = 0;

        /**
         * @brief       GetValue()  获取参数值
         * @author      yangzhenxing@sixents.com
         * @param[out]  pvValue:指针参数
                        pvParam:指针参数
                        不同的CValue类型，pvValue和pvParam的输出处理不一样，下面一一列举
                        CValueInt:pvValue 指向输出int变量的内存地址 ,pvParam 无效
                        CValueDouble:pvValue 指向输出 double 变量的内存地址 ,pvParam 无效
                        CValueString:pvValue 指向输出 string对象的地址
                        CValuePointer:pvValue 指向输出指针的内存地址(即双重指针),pvParam 无效
                        CValueByteArray:pvValue 指向输出buf的内存地址,pvParam 为unsigned int*类型，用于表示输入/输出长度
                               当pvValue为0时，本函数通过 pvParam 返回实际需要的内存大小，
                               即"*((unsigned int*)pvParam)=uiDataLen;"
                               当pvValue不为0，pvParam 作为输入，表示接收Buf大小；作为输出，表示实际返回数据大小
                        CValueDoubleArray:pvValue 指向输出double的内存首地址,pvParam 为unsigned
         int*类型，用于表示输入/输出长度 当pvValue为0时，本函数通过 pvParam 返回实际需要的内存大小, 即"*((unsigned
         int*)pvParam)=uiDataLen;" 当pvValue不为0，pvParam
         作为输入，表示接收double数组大小；作为输出，表示实际接收到的double长度
         * @exception   N/A
         * @return      BOOL_T
         * @retval      (true,false)
         * @note        N/A
         */
        virtual BOOL_T GetValue(PVOID pvValue, PVOID pvParam) = 0;

        /**
         * @brief        GetStringValue()  获取参数值
         * @author       yangzhenxing@sixents.com
         * @param[out]   strValue:表示序列化后的字符串
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        virtual BOOL_T GetStringValue(string& strValue) = 0;

        /**
         * @brief       SetStringValue()  获取参数值
         * @author      yangzhenxing@sixents.com
         * @param[in]   strValue:表示反序列化输入的字符串
         * @param[out]  N/A
         * @exception   N/A
         * @return      BOOL_T
         * @retval      (true,false)
         * @note        N/A
         */
        virtual BOOL_T SetStringValue(const string& strValue) = 0;

        /**
         * @brief        Clone() 对象克隆
         * @author       yangzhenxing@sixents.com
         * @param[out]   ppValueRet:对当前CValue进行克隆，输出的目的地址的指针
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        virtual BOOL_T Clone(PPCValue ppValueRet) = 0;

        /**
         * @brief        GetTypeString() 获取当前CValue对象的类型字符串
         * @author       yangzhenxing@sixents.com
         * @param[out]   N/A
         * @exception    N/A
         * @return       string
         * @retval       字符串
         * @note         N/A
         */
        std::string GetTypeString() const;

        /**
         * @brief        CreateValueByType() 通过CValue类型创建对象
         * @author       yangzhenxing@sixents.com

         * @param[out]   N/A
         * @exception    N/A
         * @return       string
         * @retval       字符串
         * @note         N/A
         */
        static CValue* CreateValueByType(const PARAM_DATA_TYPE enValueType);

    protected:
        PARAM_DATA_TYPE m_enDataType;
    };

    /**
     * @class      CValueDouble
     * @brief      Double类型的封装类
     * @author     yangzhenxing@sixents.com
     * @note       N/A
     */
    class CValueDouble : public CValue
    {
    public:
        CValueDouble();
        virtual ~CValueDouble() = default;
        virtual PARAM_DATA_TYPE GetType() override;
        virtual BOOL_T SetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetStringValue(string& strValue) override;
        virtual BOOL_T SetStringValue(const string& strValue) override;
        virtual BOOL_T Clone(PPCValue const ppValueRet) override;
        static PVOID CreateValueObj();

    private:
        DOUBLE m_dbValue;
    };

    /**
     * @class      CValueInt
     * @brief      Int类型的封装类
     * @author     yangzhenxing@sixents.com
     * @note       N/A
     */
    class CValueInt : public CValue
    {
    public:
        CValueInt();
        virtual ~CValueInt() = default;
        virtual PARAM_DATA_TYPE GetType() override;
        virtual BOOL_T SetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetStringValue(string& strValue) override;
        virtual BOOL_T SetStringValue(const string& strValue) override;
        virtual BOOL_T Clone(PPCValue const ppValueRet) override;
        static PVOID CreateValueObj();

    private:
        INT32 m_i32Value;
    };

    /**
     * @class      CValuePointer
     * @brief      PVOID类型的封装类
     * @author     yangzhenxing@sixents.com
     * @note       N/A
     */
    class CValuePointer : public CValue
    {
    public:
        CValuePointer();
        virtual ~CValuePointer() = default;
        virtual PARAM_DATA_TYPE GetType() override;
        virtual BOOL_T SetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetStringValue(string& strValue) override;
        virtual BOOL_T SetStringValue(const string& strValue) override;
        virtual BOOL_T Clone(PPCValue const ppValueRet) override;
        static PVOID CreateValueObj();

    private:
        PVOID m_pvValue;
    };

    /**
     * @class      CValueString
     * @brief      string类型的封装类
     * @author     yangzhenxing@sixents.com
     * @note       N/A
     */
    class CValueString : public CValue
    {
    public:
        CValueString();
        virtual ~CValueString() = default;

    public:
        virtual PARAM_DATA_TYPE GetType() override;
        virtual BOOL_T SetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetStringValue(string& strValue) override;
        virtual BOOL_T SetStringValue(const string& strValue) override;
        virtual BOOL_T Clone(PPCValue const ppValueRet) override;
        static PVOID CreateValueObj();

    private:
        string m_strValue;
    };

    /**
     * @class      CValueByteArray
     * @brief      ByteArray类型的封装类
     * @author     yangzhenxing@sixents.com
     * @note       N/A
     */
    class CValueByteArray : public CValue
    {
    public:
        CValueByteArray();
        virtual ~CValueByteArray() = default;

        virtual PARAM_DATA_TYPE GetType() override;
        virtual BOOL_T SetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetStringValue(string& strValue) override;
        virtual BOOL_T SetStringValue(const string& strValue) override;
        virtual BOOL_T Clone(PPCValue const ppValueRet) override;
        static PVOID CreateValueObj();

    private:
        std::string m_objValues;
    };

    /**
     * @class      CValueIntArray
     * @brief      IntArray类型的封装类
     * @author     yangzhenxing@sixents.com
     * @note       N/A
     */
    class CValueIntArray : public CValue
    {
    public:
        CValueIntArray();
        virtual ~CValueIntArray() = default;

        virtual PARAM_DATA_TYPE GetType() override;
        virtual BOOL_T SetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetStringValue(string& strValue) override;
        virtual BOOL_T SetStringValue(const string& strValue) override;
        virtual BOOL_T Clone(PPCValue const ppValueRet) override;
        static PVOID CreateValueObj();

    private:
        std::vector< INT32 > m_objValues;
    };

    /**
     * @class      CValueDoubleArray
     * @brief      DoubleArray类型的封装类
     * @author     yangzhenxing@sixents.com
     * @note       N/A
     */
    class CValueDoubleArray : public CValue
    {
    public:
        CValueDoubleArray();
        virtual ~CValueDoubleArray() = default;

        virtual PARAM_DATA_TYPE GetType() override;
        virtual BOOL_T SetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetValue(PVOID const pvValue, PVOID const pvParam) override;
        virtual BOOL_T GetStringValue(string& strValue) override;
        virtual BOOL_T SetStringValue(const string& strValue) override;
        virtual BOOL_T Clone(PPCValue const ppValueRet) override;
        static PVOID CreateValueObj();

    private:
        std::vector< DOUBLE > m_objValues;
    };

} // namespace sixents

#endif // ___VALUE_H___
