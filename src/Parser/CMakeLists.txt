add_library(Parser
  Parser.cpp
)

target_link_libraries(Parser Lexer fmt)

target_include_directories(Parser
  PUBLIC "${PROJECT_SOURCE_DIR}/include/Lunasm/"
)
