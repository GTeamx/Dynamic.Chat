cmake_minimum_required(VERSION 3.28)
project(Dynamic_Chat)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_executable(Dynamic_Chat main.cpp)
target_link_libraries(Dynamic_Chat ws2_32)