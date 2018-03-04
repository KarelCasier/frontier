project(graphics LANGUAGES CXX)

find_package(SDL2_image REQUIRED)

set (HEADERS
    include/graphics/Camera.hpp
    include/graphics/ISelfRenderable.hpp
    include/graphics/RenderManager.hpp
    include/graphics/TextureManager.hpp
    include/graphics/Transform.hpp
    include/graphics/Util.hpp
    )

set(SOURCES
    src/Camera.cpp
    src/RenderManager.cpp
    src/TextureManager.cpp
    src/Transform.cpp
    src/Util.cpp
    )

add_library(graphics STATIC ${SOURCES} ${HEADERS})

target_link_libraries(graphics
    PUBLIC
    math
    PRIVATE
    log
    ${SDL2_IMAGE_LIBRARIES}
    )

target_include_directories(graphics
    PUBLIC
    include
    PRIVATE
    src
    )
