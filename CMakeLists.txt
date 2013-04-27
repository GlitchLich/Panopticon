cmake_minimum_required(VERSION 2.8)
project(Panopticon)
include("PanopticonVersion.txt")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}${PROJECT_VERSION_PATCH}")
message(STATUS "Panopticon Version: ${PROJECT_VERSION}")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules
                      ${CMAKE_MODULE_PATH})

find_package(OpenGL)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    add_definitions(-D__LINUX__)
    add_definitions(-DLINUX)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL Apple)
    add_definitions(-D__APPLE__)
    add_definitions(-DAPPLE)
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/editors")
set(Panopticon_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_subdirectory ("${PROJECT_SOURCE_DIR}/src")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/core")
add_subdirectory ("${PROJECT_SOURCE_DIR}/src/Grammar")

add_subdirectory ("${PROJECT_SOURCE_DIR}/include")
add_subdirectory ("${PROJECT_SOURCE_DIR}/include/core")
add_subdirectory ("${PROJECT_SOURCE_DIR}/include/Grammar")

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "resources")

option(PN_QT "Build Panopticon with Qt IDE" ON)

if(PN_QT)
    message(STATUS "Compiling with Qt")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    add_subdirectory ("${PROJECT_SOURCE_DIR}/editors/ide")
    add_definitions(-DPN_IDE)
endif(PN_QT)

add_executable(Panopticon ${Panopticon_SRC})

TARGET_LINK_LIBRARIES(Panopticon ${OPENGL_LIBRARIES})

if(PN_QT)
    qt5_use_modules(Panopticon Core Gui Quick Widgets OpenGL Qml)
endif(PN_QT)
