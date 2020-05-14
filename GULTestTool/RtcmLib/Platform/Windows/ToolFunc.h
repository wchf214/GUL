#ifndef _WINDOWS_TOOL_FUNC_H_
#define _WINDOWS_TOOL_FUNC_H_

#include <io.h>
#include <string>
#include <vector>

#include "../BasicType.h"

static sixents::BOOL_T ScanDirFiles(const std::string& sPath, std::vector< std::string >& vFiles)
{
    if (sPath.empty())
    {
        return false;
    }

    intptr_t hFile = 0;
    _finddata_t fileInfo;
    std::string exdName;
    // \\* 代表要遍历所有的类型
    if ((hFile = _findfirst((sPath + "\\*").c_str(), &fileInfo)) == -1)
    {
        return false;
    }
    do
    {
        if (fileInfo.attrib & _A_ARCH)
            vFiles.push_back(fileInfo.name);
    } while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return true;
}

static sixents::BOOL_T IsFileExist(const std::string& file)
{
    if (_access(file.c_str(), 0) == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
#endif
