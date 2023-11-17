add_library(Parser
  Operand.cpp
  Instruction.cpp
  Instructions/Label.cpp 
  Instructions/Nop.cpp
  Instructions/Load.cpp
  Instructions/Store.cpp
  Instructions/Bitwise.cpp
  Instructions/Stack.cpp
  Instructions/Math.cpp
  Instructions/Compare.cpp
  Instructions/Jump.cpp
  Instructions/Subroutine.cpp
  Instructions/Halt.cpp
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
