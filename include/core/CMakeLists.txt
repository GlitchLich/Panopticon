cmake_minimum_required(VERSION 2.8)

set(Panopticon_SRC
   	${Panopticon_SRC}
	${CMAKE_CURRENT_SOURCE_DIR}/panopticon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/operators.h
        ${CMAKE_CURRENT_SOURCE_DIR}/errors.h
	PARENT_SCOPE
)
