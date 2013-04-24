project(Panopticon)
cmake_minimum_required(VERSION 2.8)
set(Panopticon_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_subdirectory ("${PROJECT_SOURCE_DIR}/src")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/Grammar")

add_subdirectory ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory ("${PROJECT_SOURCE_DIR}/include/Grammar")

add_executable(Panopticon ${Panopticon_SRC})

