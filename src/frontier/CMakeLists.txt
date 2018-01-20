project(frontier LANGUAGES CXX)

add_executable(frontier
    src/main.cpp
    )

target_link_libraries(frontier
    PRIVATE
    navigation
    )

