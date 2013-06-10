cmake_minimum_required(VERSION 2.8)

set(Panopticon_SRC
   	${Panopticon_SRC}
	${CMAKE_CURRENT_SOURCE_DIR}/panopticon.h
        ${CMAKE_CURRENT_SOURCE_DIR}/types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/operators.h
        ${CMAKE_CURRENT_SOURCE_DIR}/errors.h
        ${CMAKE_CURRENT_SOURCE_DIR}/heap.h
        ${CMAKE_CURRENT_SOURCE_DIR}/stack.h
        ${CMAKE_CURRENT_SOURCE_DIR}/function.h
        ${CMAKE_CURRENT_SOURCE_DIR}/containers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/list.h
        ${CMAKE_CURRENT_SOURCE_DIR}/container_primitives.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Memory.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Trie.h
        ${CMAKE_CURRENT_SOURCE_DIR}/thunk.h
	PARENT_SCOPE
)
