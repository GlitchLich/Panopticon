cmake_minimum_required(VERSION 2.8)

set(Panopticon_SRC
   	${Panopticon_SRC}
   	${CMAKE_CURRENT_SOURCE_DIR}/grammar.h
   	${CMAKE_CURRENT_SOURCE_DIR}/lexglobal.h
	${CMAKE_CURRENT_SOURCE_DIR}/parse.h
	${CMAKE_CURRENT_SOURCE_DIR}/tokens.h
	PARENT_SCOPE
)
