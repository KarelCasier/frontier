project(graphics LANGUAGES CXX)

find_package(SDL2_image REQUIRED)

set (HEADERS
    include/graphics/IDebugDrawable.hpp
    include/graphics/TextureManager.hpp
    include/graphics/Util.hpp
    )

set(SOURCES
    src/TextureManager.cpp
    src/Util.cpp
    )

add_library(graphics STATIC ${SOURCES} ${HEADERS})

target_link_libraries(graphics
    PRIVATE
    log
    math
    ${SDL2_IMAGE_LIBRARIES}
    )

target_include_directories(graphics
    PUBLIC
    include
    PRIVATE
    src
    )
