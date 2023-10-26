add_executable(${PROJECT_NAME}
  Lunasm.cpp
)

target_sources(${PROJECT_NAME}
  PRIVATE 
    Lunasm.cpp
)

add_subdirectory(Lexer)
add_subdirectory(Parser)

target_link_libraries(${PROJECT_NAME}
  Lexer
  Parser
)

target_include_directories(${PROJECT_NAME} 
  PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}
)
