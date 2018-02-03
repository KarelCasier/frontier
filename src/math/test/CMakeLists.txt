set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/test)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(tests test_Vector2.cpp)
add_test(NAME tests COMMAND $<TARGET_FILE:tests>)
target_link_libraries(tests math gtest gmock)
target_include_directories(math
    PUBLIC
    ../include
    PRIVATE
    ../src
)
