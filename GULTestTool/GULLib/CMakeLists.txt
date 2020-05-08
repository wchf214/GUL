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

# 头文件包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 附加库包含目录
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)

# 添加子目录
add_subdirectory(GNSSMathUtilityLib)

