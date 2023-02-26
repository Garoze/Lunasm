cmake_minimum_required(VERSION 3.24)

project(Lunasm)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} 
	src/Main.cpp
)
