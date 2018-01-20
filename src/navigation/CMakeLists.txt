project(navigation LANGUAGES CXX)

add_library(navigation
    src/test.cpp
    )

target_include_directories(navigation
    PUBLIC
    include
    PRIVATE
    src
    )

target_link_libraries(navigation
    PRIVATE
    )
