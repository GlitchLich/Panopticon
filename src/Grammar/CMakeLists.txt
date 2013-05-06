cmake_minimum_required(VERSION 2.8)
include_directories("${PROJECT_SOURCE_DIR}/include")
set(Panopticon_SRC
   	${Panopticon_SRC}
        ${CMAKE_CURRENT_SOURCE_DIR}/grammar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.c
        ${CMAKE_CURRENT_SOURCE_DIR}/parse.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plus.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/minus.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/divide.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/conditionals.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/parsingutilities.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer.c
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l
        ${CMAKE_CURRENT_SOURCE_DIR}/grammar.y
        PARENT_SCOPE
)
