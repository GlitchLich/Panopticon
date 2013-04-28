cmake_minimum_required(VERSION 2.8)

set(Panopticon_SRC
   ${Panopticon_SRC}
   ${CMAKE_CURRENT_SOURCE_DIR}/ide.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/SyntaxHighlighter.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/EditBuffer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Session.cpp
   PARENT_SCOPE
)
