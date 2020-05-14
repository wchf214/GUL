/**
 * @file            CCfgMng.cpp
 * @brief        	配置管理模块cpp实现模块
 * @details
 * 配置管理模块是外部配置文件和当前程序运行时之间的一个桥梁，用于同步他们之间的数据，可以通过简单的接口调用实现配置文件的读取
 * @author       	yangchenyi/yangchengyi@sixents.com
 * @date            2019-12-20
 * @version      	1.0
 * @note            N/A
 * @copyright   	Copyright(c) 2019-2020 Beijing Sixents Technology Co., Ltd. All rights reserved.
 */
#include <algorithm>
#include <fstream>

#include "CCfgMng.h"
#include "CommonFunc.h"
#include "Constants.h"

namespace sixents
{
    using std::string;
    using namespace sixents::common::rtcm;

    CCfgMng::~CCfgMng()
    {
        Release();
    }

    BOOL_T CCfgMng::Init(const std::string& strConfigPath)
    {
        if (strConfigPath.empty())
        {
            return false;
        }

        m_strConfigPath = strConfigPath;

        if (!ParseConfig())
        {
            return false;
        }

        return true;
    }

    BOOL_T CCfgMng::UpdateByDefaultValue()
    {
        m_mapCfg = common::rtcm::MAP_CONFIG_DEF;
        return true;
    }

    BOOL_T CCfgMng::Release()
    {
        return true;
    }

    BOOL_T CCfgMng::ParseConfig()
    {
        if (m_strConfigPath.empty())
        {
            return false;
        }

        std::ifstream fin(m_strConfigPath);
        if (!fin.is_open())
        {
            return false;
        }

        string strCurDomain = UNDEFINED_SECTION;
        string strLine;
        while (true)
        {
            if (getline(fin, strLine).eof() == true)
            {
                break;
            }

            strLine = common::Trim(strLine, " \r\n\t");

            if (strLine.empty())
            {
                continue;
            }
            // 以#开头的行是注释行
            if (strLine[0U] == '#')
            {
                continue;
            }
            else if (strLine[0U] == '[')
            {
                const string::size_type posl = strLine.find_first_of(']');

                if (posl != string::npos)
                {
                    strCurDomain = strLine.substr(CCFG_MNG_VALUE_1, posl - CCFG_MNG_VALUE_1);
                }
            }
            else
            {
                const auto pos = strLine.find_first_of('=');
                if (pos != string::npos)
                {
                    string key = strCurDomain + SEC_KEY_DIVISION + strLine.substr(0U, pos);
                    string value = strLine.substr(pos + CCFG_MNG_VALUE_1);
                    m_mapCfg.insert(make_pair(key, value));
                }
            }
        }
        fin.close();
        return true;
    }
} // namespace sixents
