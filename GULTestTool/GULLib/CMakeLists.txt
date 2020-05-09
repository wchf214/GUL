# 指定CMake编译器的最低版本
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_STANDARD 11)


# 设置工程名
project(gul)

# 设置项目版本号
set(gul_VERSION_1.0)

# 添加编译选项
add_compile_options(-g)

# 添加子目录
add_subdirectory(GNSSMathUtilityLib)
add_subdirectory(GNSSUtilityLibrary)