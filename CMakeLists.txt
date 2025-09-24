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
message(STATUS "Current Proejct Sourrce Path: ${PROJECT_SOURCE_DIR}")
include_directories(
    ${PROJECT_SOURCE_DIR}/inc/logger
    ${PROJECT_SOURCE_DIR}/inc/net
    ${PROJECT_SOURCE_DIR}/inc/process
    ${PROJECT_SOURCE_DIR}/inc/config
)


# ---------- 添加源文件目录 ------------
# 搜索 src/ 目录下的所有 .cpp 文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src/logger SOURCES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/net SOURCES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/process SOURCES)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/config SOURCES)



message(STATUS "Files in SOURCES:")
foreach(src_file IN LISTS SOURCES)
    message(STATUS "  - ${src_file}")
endforeach()


#----------- 构建项目 -----------------
add_executable(
    tinyServer 
    ${SOURCES}
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)










#-----------unit test----------------
enable_testing()

find_package(GTest REQUIRED)
if (GTest_FOUND)
    message(STATUS "Founded Google Test")
    message(STATUS "Add testing files ...")

    # 搜索测试文件
    aux_source_directory(${PROJECT_SOURCE_DIR}/test TEST_SOURCES_LIST)
    foreach(test_file IN LISTS TEST_SOURCES_LIST)
        message(STATUS "  - ${test_file}")
    endforeach()

    # 创建测试可执行文件
    add_executable(tinyServerUnitTests ${SOURCES} ${TEST_SOURCES_LIST})


    # 链接测试依赖
    target_link_libraries(
        tinyServerUnitTests
        gtest
        gtest_main
        pthread
    )

    # 头文件路径
    include_directories(
        ${PROJECT_SOURCE_DIR}/inc/logger
        ${PROJECT_SOURCE_DIR}/inc/net
        ${PROJECT_SOURCE_DIR}/lib/json
        ${PROJECT_SOURCE_DIR}/lib/configure
    )

    # 确保 test 目录存在
    file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/test)

    # 设置测试报告输出路径
    set(TEST_REPORT_DIR ${PROJECT_SOURCE_DIR}/test)


    # 注册测试
    add_test(
        NAME tinyServerUnitTests
        COMMAND tinyServerUnitTests
    )

    

else()
    message(WARNING "Google Test not found, tests will not be built")
endif()






