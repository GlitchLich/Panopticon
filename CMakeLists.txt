cmake_minimum_required(VERSION 2.8)
project(Panopticon)
include("PanopticonVersion.txt")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}${PROJECT_VERSION_PATCH}")
message(STATUS "Panopticon Version: ${PROJECT_VERSION}")
add_definitions(-DPANOPTICON_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DPANOPTICON_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DPANOPTICON_VERSION_PATCH=${PROJECT_VERSION_PATCH})

find_package(LLVM)

# Define add_llvm_* macro's.
include(AddLLVM)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
llvm_map_components_to_libraries(REQ_LLVM_LIBRARIES jit native)

#set(ENV{CC} "clang")
#set(ENV{CXX} "clang++")

#SET(CMAKE_C_COMPILER "/usr/bin/clang")
#SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
#SET(CMAKE_CXX_COMPILER_ID "Clang")

SET(CMAKE_AR      "/usr/bin/llvm-ar")
SET(CMAKE_LINKER  "/usr/bin/llvm-ld")
SET(CMAKE_NM      "/usr/bin/llvm-nm")
SET(CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
SET(CMAKE_RANLIB  "/usr/bin/llvm-ranlib")

#message("Compiling with Clang")
#set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -g -O3 `llvm-config --cppflags --ldflags --libs core`")

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules
                      ${CMAKE_MODULE_PATH})

if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message("Compiling with Clang")
# `llvm-config --cppflags --ldflags --libs core`
    set(CMAKE_CXX_FLAGS "-v -std=c++11 -g -O3")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  message("Compiling with Clang")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  message("Compiling with GNU")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  message("Compiling with Intel")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
 message("Compiling with MSVC")
endif()

find_package(OpenGL)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    add_definitions(-D__LINUX__)
    add_definitions(-DLINUX)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL Apple)
    add_definitions(-D__APPLE__)
    add_definitions(-DAPPLE)
endif()

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
TARGET_LINK_LIBRARIES(Panopticon ${REQ_LLVM_LIBRARIES})

if(PN_QT)
    qt5_use_modules(Panopticon Core Gui Quick Widgets OpenGL Qml)
endif(PN_QT)
