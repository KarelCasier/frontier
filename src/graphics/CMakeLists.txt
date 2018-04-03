project(graphics LANGUAGES CXX)

find_package(SDL2_image REQUIRED)

set (HEADERS
    include/graphics/Camera.hpp
    include/graphics/Color.hpp
    include/graphics/IRenderTarget.hpp
    include/graphics/IRenderable.hpp
    include/graphics/PrimativeType.hpp
    include/graphics/TextureManager.hpp
    include/graphics/TextureRef.hpp
    include/graphics/Transform.hpp
    include/graphics/Util.hpp
    include/graphics/Window.hpp
    )

set(SOURCES
    src/Camera.cpp
    src/TextureManager.cpp
    src/Transform.cpp
    src/Util.cpp
    src/Window.cpp
    )

add_library(graphics STATIC ${SOURCES} ${HEADERS})

target_link_libraries(graphics
    PUBLIC
    math
    utils
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
