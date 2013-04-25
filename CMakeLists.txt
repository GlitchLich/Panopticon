project(Panopticon)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(Panopticon_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_subdirectory ("${PROJECT_SOURCE_DIR}/src")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/core")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/Grammar")

add_subdirectory ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory ("${PROJECT_SOURCE_DIR}/include/core")
add_subdirectory ("${PROJECT_SOURCE_DIR}/include/Grammar")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(Panopticon ${Panopticon_SRC})

