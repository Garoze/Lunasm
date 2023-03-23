cmake_minimum_required(VERSION 3.24)

project(
	Lunasm 
	VERSION 0.0.1 
	DESCRIPTION "A simple assembly language for the Luna16 fantasy console."  
	LANGUAGES CXX
)

# Update project submodules
include(cmake/UpdateSubmodules.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(src)
add_subdirectory(external)

target_include_directories(${PROJECT_NAME}
	PUBLIC include/Lunasm
)
