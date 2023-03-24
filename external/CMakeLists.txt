add_subdirectory(fmtlib)
add_subdirectory(argparse)
add_subdirectory(googletest)

target_include_directories(${PROJECT_NAME} 
	PUBLIC external/fmtlib/include
	PUBLIC external/argparse/include
)

target_link_directories(${PROJECT_NAME} 
	PRIVATE external/fmtlib
	PRIVATE external/argparse
)

target_link_libraries(${PROJECT_NAME} fmt argparse)
