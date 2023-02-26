cmake_minimum_required(VERSION 3.24)

project(Lunasm)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/fmtlib/)

include_directories(
	${PROJECT_SOURCE_DIR}/include/
)

add_executable(${PROJECT_NAME} 
	src/Kind.cpp
	src/Main.cpp
)

target_include_directories(${PROJECT_NAME} 
	PUBLIC external/fmtlib/include
)

target_link_directories(${PROJECT_NAME}
	PRIVATE external/fmtlib
)

target_link_libraries(${PROJECT_NAME} fmt)
