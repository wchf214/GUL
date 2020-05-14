/**
 * @file        CLog.h
 * @author      yangchenyi/yangchengyi@sixents.com
 * @version     1.0
 * @date        2019-12-20
 * @brief       配置管理模块，支持各种数据的序列化和反序列化功能。
 * @details
 通过模板方法实现了多种类型数据值的获取,内部自实现了标准INI文件格式解析，通过简单map<string,string>映射来管理配置项
                本模块在之前的模块上进行了大规模的精简，摒弃了之前对CValue的强依赖关系。
 * @note        change history:
 *                  <2019-12-20>  | 1.0 | yangchenyi | 创建初始版本
 * @copyright   Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */

#ifndef CCFG_MNG_H
#define CCFG_MNG_H

#include <functional>
#include <inttypes.h>
#include <map>
#include <memory>
#include <sstream>
#include <vector>
#include "../Platform/BasicType.h"

namespace sixents
{
    using pfnNewObjInt = std::function< sixents::PVOID(const std::string& pthSecKey) >;

    /**
     * @class      CCfgMng
     * @brief      配置管理，实现各种数据的配置存储。
     * @author     yangchengyi@sixents.com
     * @note       N/A
     */
    class CCfgMng final
    {
    public:
        /**
         * @brief        CCfgMng() 默认构造函数
         * @author       yangchengyi@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       N/A
         * @retval       N/A
         * @note         N/A
         */
        CCfgMng() = default;

        /**
         * @brief        ~CCfgMng() 析构函数
         * @author       yangchengyi@sixents.com
         * @param[in]    pthCfgPath：配置路径
         * @param[out]   N/A
         * @exception    N/A
         * @return       N/A
         * @retval       N/A
         * @note         N/A
         */
        ~CCfgMng();

        /**
         * @brief        Init初始化函数
         * @author       yangchengyi@sixents.com
         * @param[in]    strConfigPath：配置文件路径
         * @param[out]   N/A
         * @exception    N/A
         * @return       N/A
         * @retval       N/A
         * @note         N/A
         */
        BOOL_T Init(const std::string& strConfigPath);

        /**
         * @brief        UpdateByDefaultValue 更新代码中预制的的配置到配置模块
         * @author       yangchengyi@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        BOOL_T UpdateByDefaultValue();

        /**
         * @brief        Release 资源释放接口
         * @author       yangchengyi@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        static BOOL_T Release();

        /**
         * @brief        GetValue 模板方法 通过key获取value
         * @author       yangchengyi@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        template < typename T >
        BOOL_T GetValue(const std::string& strKey, T& out);

        /**
         * @brief        SetValue 模板方法 设置指定key的value
         * @author       yangchengyi@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        template < typename T >
        BOOL_T SetValue(const std::string& strKey, const T& in);


    private:
        // 读取配置文件
        /**
         * @brief        ParseConfig 解析通过初始化指定的配置文件
         * @author       yangchengyi@sixents.com
         * @param[in]    N/A
         * @param[out]   N/A
         * @exception    N/A
         * @return       BOOL_T
         * @retval       (true,false)
         * @note         N/A
         */
        BOOL_T ParseConfig();

    private:
        std::map< std::string, std::string > m_mapCfg; // 配置文件中的内容
        std::string m_strConfigPath;                   // 配置文件的路径
    };

    template < typename T >
    BOOL_T CCfgMng::GetValue(const std::string& strKey, T& out)
    {
        if (strKey.empty())
        {
            return false;
        }
        auto iter = m_mapCfg.find(strKey);
        if (iter == m_mapCfg.end())
        {
            return false;
        }

        std::stringstream ss;
        ss << iter->second;
        ss >> out;

        return true;
    }

    template < typename T >
    BOOL_T CCfgMng::SetValue(const std::string& strKey, const T& in)
    {
        if (strKey.empty())
        {
            return false;
        }
        auto iter = m_mapCfg.find(strKey);
        if (iter == m_mapCfg.end())
        {
            return false;
        }

        std::stringstream ss;
        ss << in;
        ss >> iter->second;

        return true;
    }


}; // namespace sixents

#endif // CCFG_MNG_H
