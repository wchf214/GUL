#ifndef _BASIC_TYPE_
#define _BASIC_TYPE_
#include <list>
#include <string>

namespace sixents
{
#ifdef _WIN32
#define STD_CALL _stdcall
#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
#else
#define DLL_API __attribute__((visibility("default")))
#define STD_CALL
#endif
#define UNREFERENCED_PARAMETER(P) (P)

    enum PARAM_DATA_TYPE
    {
        PDT_TYPE_MASK = 0x0000FFFF,
        PDT_TYPE_BASE = 0x00008000,         // 表示基本数据类型
        PDT_TYPE_ARRAY_MASK = 0x00000100,   // 表示数组类型掩码
        PDT_TYPE_POINTER_MASK = 0x00000200, // 表示指针类型掩码

        PDT_INT = 0x01 | PDT_TYPE_BASE,    // int 类型
        PDT_DOUBLE = 0x02 | PDT_TYPE_BASE, // double 类型
        PDT_STRING = 0x04 | PDT_TYPE_BASE, // string类型

        PDT_POINTER = 0x01 | PDT_TYPE_POINTER_MASK,  // 指针 类型
        PDT_INT_ARR = 0x02 | PDT_TYPE_ARRAY_MASK,    // int 数组
        PDT_DOUBLE_ARR = 0x04 | PDT_TYPE_ARRAY_MASK, // double 数组
        PDT_BYTE_ARRAY = 0x08 | PDT_TYPE_ARRAY_MASK  // ByteArray类型
    };

    // bool类型
    using BOOL_T = bool; // 注意此类型不能用vector<BOOL>

    // 有符号类型定义
    using INT8 = signed char; // 8位整型 用来代替char
    using INT16 = short;      // 16位整型 用来代替short
    using INT32 = int;        // 32位整型
    using INT64 = long long;  // 64位整型

    // 无符号类型定义
    using CHAR = char;                 // 8位符号 char
    using BYTE = unsigned char;        // 8位无符号整型 unsigned char 和 byte类型
    using UINT8 = unsigned char;       // 8位无符号整型 unsigned char 和 byte类型
    using WORD = unsigned short;       // 双字节
    using UINT16 = unsigned short;     // 双字节 同(WORD)
    using UINT32 = unsigned int;       // 32位无符号整型
    using UINT64 = unsigned long long; // 64位无符号整型

    // 浮点类型数据定义
    using FLOAT = float;   // 32位浮点数
    using DOUBLE = double; // 64位浮点数

    // 指针类型
    using PVOID = void*;       // 主要是用于CParam传输
    using PCSTR = const char*; // C类型的字符串处理

}; // namespace sixents

#endif // _BASIC_TYPE_
