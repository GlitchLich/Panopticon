cmake_minimum_required( VERSION 2.8.9 )

set(Panopticon_SRC
   ${Panopticon_SRC}
   ${CMAKE_CURRENT_SOURCE_DIR}/ide.h
   ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h
   ${CMAKE_CURRENT_SOURCE_DIR}/SyntaxHighlighter.h
   ${CMAKE_CURRENT_SOURCE_DIR}/EditBuffer.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Session.h
   ${CMAKE_CURRENT_SOURCE_DIR}/FilePanel.h
   PARENT_SCOPE
)
