project(Panopticon)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
file(GLOB helloworld_SRC
    "*.h"
    "*.c"
    "*.cpp"
    "*.y"
)
add_executable(${PROJECT_NAME} ${SRC_LIST})

