project(frontier LANGUAGES CXX)

find_package(SDL2 REQUIRED)

add_library(frontier_lib
    src/Frontier.cpp
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
    texture_manager
    )

