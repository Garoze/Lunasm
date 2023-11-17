add_library(Assembler
  Assembler.cpp
)

target_link_libraries(Assembler fmt)

target_include_directories(Assembler
  PUBLIC "${PROJECT_SOURCE_DIR}/include/Lunasm/"
)
