project(frontier LANGUAGES CXX)

add_library(frontier_lib
    src/SDLApplication.cpp
    )

target_include_directories(frontier_lib
    PUBLIC
    include
    PRIVATE
    src
    )

target_link_libraries(frontier_lib
    PRIVATE
    log
    ${SDL2_LIBRARIES}
    )

add_executable(frontier
    src/main.cpp
    )

target_link_libraries(frontier
    PRIVATE
    frontier_lib
    )

