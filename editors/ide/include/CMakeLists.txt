cmake_minimum_required( VERSION 2.8.9 )

add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/core")
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/style")

set(Panopticon_SRC
   ${Panopticon_SRC}
   PARENT_SCOPE
)
