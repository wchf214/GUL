/**
 * @file        CParam.h
 * @author      yangzhenxing@sixents.com
 * @version     1.0
 * @date        2019-12-20
 * @brief       参数封装类
 * @details     对各种参数类型进行封装，以便于在接口中做为输入，输出的形参使用。
 * @note        change history:
 *                  <2019-12-20>  | 1.0 | yangzhenxing | 创建初始版本
 * @copyright   Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */
#ifndef _RTCM_PARAM_H_
#define _RTCM_PARAM_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "BasicType.h"

namespace sixents
{
    class CValue;
    /**
     * @class      CParam
     * @brief      对各种参数类型进行封装，以便于在接口中做为输入，输出的形参使用。
     * @author     yangzhenxing@sixents.com
     * @note       N/A
     */
    class DLL_API CParam
    {
    public:
        /**
         * @brief        CParam()  默认的构造函数
         * @author       yangzhenxing@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       N/A
         * @retval       N/A
         * @note         N/A
         */
        CParam() = default;

        /**
         * @brief        ~CParam()  默认的析构函数
         * @author       yangzhenxing@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       N/A
         * @retval       N/A
         * @note         N/A
         */
        virtual ~CParam();

        /**
         * @brief        AddValue()  添加参数值
         * @author       yangzhenxing@sixents.com
         * @param[in]    strKey:参数项名称
                         enPDT:参数类型
                         pvValue:指针参数
                         pvParam:指针参数
                         不同的PARAM_DATA_TYPE类型，pvValue和pvParam的处理不一样，下面一一列举
                         CValueInt:pvValue 为int*指针,pvParam 无效
                         CValueDouble:pvValue 为double*指针 ,pvParam 无效
                         CValueString:pvValue 为std::string*指针 ,pvParam 无效
                         CValuePointer:pvValue 指向指针的内存地址(即双重指针),pvParam 无效
                         CValueByteArray:pvValue 指向存放BYTE数组的内存地址,pvParam 为unsigned int类型，用于表示输入长度
                         CValueIntArray:pvValue 指向存放Int数组的内存地址,pvParam 为unsigned int类型，用于表示输入长度
                         CValueDoubleArray:pvValue 指向存放double数组的地址,pvParam 为unsigned int类型，用于表示输入长度
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        BOOL_T
        AddValue(const std::string& strKey, const PARAM_DATA_TYPE enPDT, PVOID const pvValue, PVOID const pvParam);

        /**
         * @brief        GetValue()  获取参数值
         * @author       yangzhenxing@sixents.com
         * @param[out]   pvValue:指针参数
                         pvParam:指针参数
                         不同的CValue类型，pvValue和pvParam的输出处理不一样，下面一一列举
                         CValueInt:pvValue 指向输出int变量的内存地址 ,pvParam 无效
                         CValueDouble:pvValue 指向输出 double 变量的内存地址 ,pvParam 无效
                         CValueString:pvValue 指向输出 string对象的地址
                         CValuePointer:pvValue 指向输出指针的内存地址(即双重指针),pvParam 无效
                         CValueByteArray:pvValue 指向输出buf的内存地址,pvParam 为unsigned
         int*类型，用于表示输入/输出长度 当pvValue为0时，本函数通过 pvParam 返回实际需要的内存大小， 即"*((unsigned
         int*)pvParam)=uiDataLen;" 当pvValue不为0，pvParam 作为输入，表示接收Buf大小；作为输出，表示实际返回数据大小
                         CValueDoubleArray:pvValue 指向输出double的内存首地址,pvParam 为unsigned
         int*类型，用于表示输入/输出长度 当pvValue为0时，本函数通过 pvParam 返回实际需要的内存大小, 即"*((unsigned
         int*)pvParam)=uiDataLen;" 当pvValue不为0，pvParam
         作为输入，表示接收double数组大小；作为输出，表示实际接收到的double长度
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        BOOL_T GetValue(const std::string& strKey, PVOID const pvValue, PVOID const pvParam);


        /**
         * @brief        IsExist(const std::string& strKey)  判断key是否存在
         * @author       yangzhenxing@sixents.com
         * @param[out]   strKey:参数项名称
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        BOOL_T IsExist(const std::string& strKey);
        BOOL_T IsExist(const std::string& strKeyList, const std::string& strSeparator);

        /**
         * @brief        DeleteValue()  获取参数值
         * @author       yangzhenxing@sixents.com
         * @param[out]   strKey:参数项名称
         * @exception    N/A
         * @return       void
         * @retval       N/A
         * @note         N/A
         */
        void DeleteValue(const std::string& strKey);

        /**
         * @brief        Release()
         * 释放函数，用于释放当前管理的参数对象CValue，如果CValue为指针类型，不对指针进行delete操作。
         * @author       yangzhenxing@sixents.com
         * @param[out]   N/A
         * @exception    N/A
         * @return       void
         * @retval       N/A
         * @note         N/A
         */
        void Release();

    private:
        /**
         * @brief        AddValue()  添加参数值
         * @author       yangzhenxing@sixents.com
         * @param[in]    strKey:参数项名称
                         pValue:参数对象
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        BOOL_T AddValue(const std::string& strKey, CValue* pValue);

        /**
         * @brief        GetValue()  获取参数值
         * @author       yangzhenxing@sixents.com
         * @param[out]   strKey:参数项名称
                         ppobjRet:输出CValue指针
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        BOOL_T GetValue(const std::string& strKey, CValue** const ppobjRet);




        // 防止拷贝和赋值
        CParam& operator=(const CParam&) = delete;
        CParam(const CParam&) = delete;

    private:
        std::recursive_mutex m_objMutex;
        std::map< std::string, CValue* > m_mapValues;
    }; // class CParam
} // namespace sixents

#endif // _RTCM_PARAM_H_
