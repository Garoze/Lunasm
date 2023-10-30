add_library(Parser
  Operand.cpp
  Instruction.cpp
  Label.cpp 
  Nop.cpp
  Load.cpp
  Store.cpp
  Bitwise.cpp
  Stack.cpp
  # ASL.cpp
  Parser.cpp
)

target_link_libraries(Parser Lexer fmt)

target_include_directories(Parser
  PUBLIC "${PROJECT_SOURCE_DIR}/include/Lunasm/"
)
