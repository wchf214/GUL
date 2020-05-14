#include "CParam.h"
#include "CValue.h"
#include "CommonFunc.h"

namespace sixents
{

    CParam::~CParam()
    {
        try
        {
            Release();
        }
        catch (...)
        {
            // Do nothing
        }
    }

    BOOL_T
    CParam::AddValue(const std::string& strKey, const PARAM_DATA_TYPE enPDT, PVOID const pvValue, PVOID const pvParam)
    {
        BOOL_T bRet = false;
        const std::lock_guard< std::recursive_mutex > lock(m_objMutex);
        // 根据名称来确定具体的CValue类型，然后再通过CValue.SetValue的方法进行初始化
        CValue* pobjValue = nullptr;

        do
        {
            if (strKey.empty())
            {
                break;
            }
            pobjValue = CValue::CreateValueByType(enPDT);
            if (pobjValue == nullptr)
            {
                break;
            }

            if (!pobjValue->SetValue(pvValue, pvParam))
            {
                break;
            }

            if (!AddValue(strKey, pobjValue))
            {
                break;
            }

            pobjValue = nullptr;

            bRet = true;
        } while (false);

        if (pobjValue != nullptr)
        {
            delete pobjValue;
            pobjValue = nullptr;
        }

        return bRet;
    }

    BOOL_T CParam::AddValue(const std::string& strKey, CValue* pValue)
    {
        const std::lock_guard< std::recursive_mutex > lock(m_objMutex);

        if (strKey.empty())
        {
            return false;
        }

        std::map< std::string, CValue* >::iterator it = m_mapValues.find(strKey);
        if (it != m_mapValues.end())
        {
            DeleteValue(strKey); // overwrite by default
        }
        m_mapValues.insert(make_pair(strKey, pValue));
        return true;
    }

    void CParam::DeleteValue(const std::string& strKey)
    {
        const std::lock_guard< std::recursive_mutex > lock(m_objMutex);

        if (strKey.empty())
        {
            return;
        }

        auto iter = m_mapValues.find(strKey);
        if (iter == m_mapValues.end())
        {
            return;
        }
        if (iter->second != nullptr)
        {
            delete iter->second; // delete CValue only, this will not impact on the object
                                 // which is pointed by the deleting CValue .
            iter->second = nullptr;
        }
        m_mapValues.erase(strKey);
    }

    BOOL_T CParam::GetValue(const std::string& strKey, CValue** const ppobjRet)
    {
        const std::lock_guard< std::recursive_mutex > lock(m_objMutex);

        if (strKey.empty())
        {
            return false;
        }

        auto iter = m_mapValues.find(strKey);
        if ((iter == m_mapValues.end()) || (ppobjRet == nullptr))
        {
            return false;
        }
        *ppobjRet = iter->second;
        return true;
    }

    BOOL_T CParam::GetValue(const std::string& strKey, PVOID const pvValue, PVOID const pvParam)
    {
        const std::lock_guard< std::recursive_mutex > lock(m_objMutex);

        if (strKey.empty())
        {
            return false;
        }

        auto iter = m_mapValues.find(strKey);
        if ((iter == m_mapValues.end()) || (iter->second == nullptr))
        {
            return false;
        }
        if (!iter->second->GetValue(pvValue, pvParam))
        {
            return false;
        }

        return true;
    }

    sixents::BOOL_T CParam::IsExist(const std::string& strKey)
    {
        const std::lock_guard< std::recursive_mutex > lock(m_objMutex);
        if (strKey.empty())
        {
            return false;
        }

        auto it = m_mapValues.find(strKey);
        if (it == m_mapValues.end())
        {
            return false;
        }

        return true;
    }

    sixents::BOOL_T CParam::IsExist(const std::string& strKeyList, const std::string& strSeparator)
    {
        const std::lock_guard< std::recursive_mutex > lock(m_objMutex);
        size_t nBeginOffset = 0U;
        size_t nEndOffset = 0U;
        string strKey;

        if (strKeyList.empty())
        {
            return false;
        }

        while (true)
        {
            if (nBeginOffset >= strKeyList.length())
            {
                break;
            }
            // try to extract individual string key from list
            nEndOffset = strKeyList.find_first_of(strSeparator, nBeginOffset);

            if (nEndOffset == string::npos)
            {
                // No separators been found from list, intercept the rests of list and take it as a new key
                strKey = strKeyList.substr(nBeginOffset);
                nBeginOffset = strKeyList.length();
            }
            else
            {
                // if two continual separators exist in the strKeylist, skip currrent round after nBeginOffset++;
                if (nEndOffset <= (nBeginOffset + strSeparator.length()))
                {
                    nBeginOffset++;
                    continue;
                }
                strKey = strKeyList.substr(nBeginOffset, nEndOffset - nBeginOffset);
                nBeginOffset = nEndOffset + strSeparator.length();
            }

            strKey = sixents::common::Trim(strKey);
            auto it = m_mapValues.find(strKey);
            if (it == m_mapValues.end())
            {
                return false;
            }
        }

        return true;
    }

    void CParam::Release()
    {
        const std::lock_guard< std::recursive_mutex > lock(m_objMutex);
        auto it = m_mapValues.begin();
        auto itEnd = m_mapValues.end();
        while (it != itEnd)
        {
            if (it->second != nullptr)
            {
                delete it->second; // delete the CValue object managed by this CParam .
                it->second = nullptr;
            }
            it++;
        }
        m_mapValues.clear();
    }

} // namespace sixents
