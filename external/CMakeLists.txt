add_subdirectory(fmtlib)
add_subdirectory(cxxopts)

target_include_directories(${PROJECT_NAME} 
	PUBLIC external/fmtlib/include
	PUBLIC external/cxxopts/include
)

target_link_directories(${PROJECT_NAME} 
	PRIVATE external/fmtlib
	PRIVATE external/cxxopts
)

target_link_libraries(${PROJECT_NAME} fmt cxxopts)
