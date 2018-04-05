project(navigation LANGUAGES CXX)

set (HEADERS
    include/navigation/AStar.hpp
    include/navigation/INavAlgorithm.hpp
    include/navigation/NavMesh.hpp
    include/navigation/NavPoly.hpp
    )

set(SOURCES
    src/AStar.cpp
    src/NavMesh.cpp
    )

add_library(navigation STATIC ${SOURCES} ${HEADERS})

target_include_directories(navigation
    PUBLIC
    include
    PRIVATE
    src
)

target_link_libraries(navigation
    PUBLIC
    PRIVATE
    log
    math
    graphics
    )

