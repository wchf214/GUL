# 指定CMake编译器的最低版本
cmake_minimum_required(VERSION 2.8)

# 指定c/c++的编译器
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# 指定包含的C++标准
set(CMAKE_CXX_STANDARD 11)

# 设置工程名
project(gul)

# 设置项目版本号
set(gul_VERSION_1.1.2.2020)

# 添加编译选项
add_compile_options(-g)

# 添加子目录
add_subdirectory(GNSSMathUtilityLib)
add_subdirectory(GNSSUtilityLibrary)