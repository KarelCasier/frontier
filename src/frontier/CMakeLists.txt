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
    ${SDL2_INCLUDE_DIR}
    )

target_link_libraries(frontier_lib
    PUBLIC
    texture_manager
    PRIVATE
    log
    ${SDL2_LIBRARY}
    )

add_executable(frontier
    src/main.cpp
    )

target_link_libraries(frontier
    PRIVATE
    frontier_lib
    )

