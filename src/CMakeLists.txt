add_executable(${PROJECT_NAME} 
        Kind.cpp
	Token.cpp
	Lexer.cpp
	Main.cpp
)

target_sources(${PROJECT_NAME}
  PRIVATE 
	Kind.cpp 
	Token.cpp 
	Lexer.cpp 
	Main.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
