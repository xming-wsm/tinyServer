cmake_minimum_required(VERSION 3.10)

# 设置编译器为 Clangd 与 debug 模式
# set(CMAKE_CXX_COMPILE_FEATURES "/usr/bin/clang++")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall")



# 设置为 C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 项目名称
project(tinyServer)

# 生成 compiler_commands 文件
set(CMAKE_EXPORT_COMPILE_COMMANDS True)


# ----------- 添加头文件目录 -----------
include_directories(
    ${PROJECT_SOURCE_DIR}/inc/logger
)


# ---------- 添加源文件目录 ------------
# 搜索 src/ 目录下的所有 .cpp 文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/logger SOURCES)


message(STATUS "Files in SOURCES:")
foreach(src_file IN LISTS SOURCES)
    message(STATUS "  - ${src_file}")
endforeach()


#----------- 构建项目 -----------------
add_executable(tinyServer ${SOURCES})
