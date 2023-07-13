add_library(Parser
  Instruction.cpp
  Label.cpp 
  ASLL.cpp
  Parser.cpp
)

target_link_libraries(Parser Lexer fmt)

target_include_directories(Parser
  PUBLIC "${PROJECT_SOURCE_DIR}/include/Lunasm/"
)
