cmake_minimum_required(VERSION 2.8)

set(Panopticon_SRC
   	${Panopticon_SRC}
   	${CMAKE_CURRENT_SOURCE_DIR}/grammar.cpp
   	${CMAKE_CURRENT_SOURCE_DIR}/lex.yy.c
	PARENT_SCOPE
)
