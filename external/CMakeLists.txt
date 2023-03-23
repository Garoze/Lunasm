add_subdirectory(fmtlib)

target_include_directories(${PROJECT_NAME}
			PUBLIC external/fmtlib/include
)

target_link_directories(${PROJECT_NAME}
			PRIVATE external/fmtlib
)

target_link_libraries(${PROJECT_NAME} fmt)
