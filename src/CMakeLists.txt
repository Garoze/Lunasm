add_executable(${PROJECT_NAME}
  Lunasm.cpp
)

target_sources(${PROJECT_NAME}
  PRIVATE 
    Lunasm.cpp
)

add_subdirectory(Lexer)

target_link_libraries(${PROJECT_NAME}
  Lexer
)

target_include_directories(${PROJECT_NAME} 
  PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}
)
