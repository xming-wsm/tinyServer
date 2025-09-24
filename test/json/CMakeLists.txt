cmake_minimum_required(VERSION 3.10)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall")


project(jsontest)



include_directories(
    ${PROJECT_SOURCE_DIR}
)

aux_source_directory(${PROJECT_SOURCE_DIR} SOURCES)
message(STATUS "${PROJECT_SOURCE_DIR} - Files in SOURCES:")
foreach(src_file IN LISTS SOURCES)
    message(STATUS "  - ${src_file}")
endforeach()


add_executable(jsontest ${SOURCES})