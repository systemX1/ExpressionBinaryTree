cmake_minimum_required(VERSION 3.0.0)
project(HOMRWORK52)

add_definitions(-std=c++11)

include(CTest)
enable_testing()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

#debug 模式
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

set(SRC_LIST Main.cpp)

# 可执行程序 ${PROJECT_NAME}.exe
add_executable(result ${SRC_LIST})

#设置静态编译
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

#链接gcc-g++静态库
target_link_libraries(result libgcc.a)
target_link_libraries(result libstdc++.a)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
