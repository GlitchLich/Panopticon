cmake_minimum_required(VERSION 2.8)
include_directories("${PROJECT_SOURCE_DIR}/include")
set(Panopticon_SRC
    ${Panopticon_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/panopticon.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/types.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/operators.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/errors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/heap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/stack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/function.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/containers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/list.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/container_primitives.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Trie.cpp
    PARENT_SCOPE
)
