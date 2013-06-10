cmake_minimum_required(VERSION 2.8)

set(Panopticon_SRC
   	${Panopticon_SRC}
   	${CMAKE_CURRENT_SOURCE_DIR}/grammar.h
   	${CMAKE_CURRENT_SOURCE_DIR}/lexglobal.h
	${CMAKE_CURRENT_SOURCE_DIR}/parse.h
	${CMAKE_CURRENT_SOURCE_DIR}/tokens.h
        ${CMAKE_CURRENT_SOURCE_DIR}/parsingutilities.h
        ${CMAKE_CURRENT_SOURCE_DIR}/plus.h
        ${CMAKE_CURRENT_SOURCE_DIR}/minus.h
        ${CMAKE_CURRENT_SOURCE_DIR}/divide.h
        ${CMAKE_CURRENT_SOURCE_DIR}/conditionals.h
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/typeinference.h
	PARENT_SCOPE
)
