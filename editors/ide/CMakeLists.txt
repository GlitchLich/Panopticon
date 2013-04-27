cmake_minimum_required( VERSION 2.8.9 )

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5UiTools REQUIRED)
find_package(Qt5Network REQUIRED)

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "resources/ide/")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources" "resources/ide")

if(LINUX)
   install(PROGRAMS PanopticonIDE.desktop  DESTINATION "share/applications")
endif(LINUX)

add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_subdirectory ("${CMAKE_CURRENT_SOURCE_DIR}/src")

set(Panopticon_SRC
    ${Panopticon_SRC}
    PARENT_SCOPE
)
