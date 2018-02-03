set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/test)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(math_tests test_Vector2.cpp)

add_test(NAME math_tests COMMAND $<TARGET_FILE:math_tests>)
target_link_libraries(math_tests math gtest gmock)
