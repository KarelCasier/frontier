project(frontier LANGUAGES CXX)

find_package(SDL2 REQUIRED)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

set(HEADERSS
    include/frontier/Frontier.hpp
    include/frontier/SDLApplication.hpp
    src/config.hpp
    )

set(SOURCES
    src/Frontier.cpp
    src/SDLApplication.cpp
    )

add_library(frontier_lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(frontier_lib
    PUBLIC
    include
    PRIVATE
    ${SDL2_INCLUDE_DIR}
    )

target_link_libraries(frontier_lib
    PUBLIC
    texture_manager
    PRIVATE
    log
    ${SDL2_LIBRARY}
    )

set (EXEC_HEADERS
    )

set (EXEC_SOURCES
    src/main.cpp
    )

add_executable(frontier ${EXEC_SOURCES} ${EXEC_HEADERS})

target_link_libraries(frontier
    frontier_lib
    )

