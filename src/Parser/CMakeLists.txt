add_library(Parser
  Operand.cpp
  Instruction.cpp
  Label.cpp 
  Nop.cpp
  Load.cpp
  Store.cpp
  Bitwise.cpp
  Stack.cpp
  Math.cpp
  Compare.cpp
  Jump.cpp
  Subroutine.cpp
  Halt.cpp
  Modes/Implicit.cpp
  Modes/Immediate.cpp
  Modes/Address.cpp
  Modes/Register.cpp
  Modes/Direct.cpp
  Modes/Absolute.cpp
  Modes/Reference.cpp
  Parser.cpp
)

target_link_libraries(Parser Lexer fmt)

target_include_directories(Parser
  PUBLIC "${PROJECT_SOURCE_DIR}/include/Lunasm/"
)
