project(texture_manager LANGUAGES CXX)

find_package(SDL2_image REQUIRED)

set (HEADERS
    include/texture_manager/TextureManager.hpp
    )

set(SOURCES
    src/TextureManager.cpp
    )

add_library(texture_manager STATIC ${SOURCES} ${HEADERS})

target_link_libraries(texture_manager
    PRIVATE
    log
    math
    ${SDL2_IMAGE_LIBRARIES}
    )

target_include_directories(texture_manager
    PUBLIC
    include
    PRIVATE
    src
    )

