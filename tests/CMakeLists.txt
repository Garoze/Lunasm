enable_testing()

add_executable(lunasm_test lunasm_test.cpp)

target_link_libraries(
  lunasm_test 
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lunasm_test)

target_include_directories(${PROJECT_NAME} 
  PUBLIC 
    "${PROJECT_SOURCE_DIR}/external/googletest"
)
