# 指定cmake最低版本
cmake_minimum_required(VERSION 3.10)
# 设置项目名
project(hash_demo)
# 指定编程语言版本
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
# 配置编译选项
add_compile_options(-Wall)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11")
# 设置编译类型参数
# debug
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
# release
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
# 添加头文件的搜索目录
include_directories(./)
# 设置输出文件位置
set(LIBRARY_OUTPUT_PATH lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY tmp)
# 编译动态库
file(GLOB_RECURSE HASH_LIB_SRC src/*.c)
add_library(hash SHARED ${HASH_LIB_SRC})
# 编译可执行文件
add_executable(hash_test test/test.c)
# 声明链接库
target_link_libraries(hash_test hash)