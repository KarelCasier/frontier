project(texture_manager LANGUAGES CXX)

find_package(SDL2_image REQUIRED)

set (TEXTURE_MANAGER_HEADERS
    include/texture_manager/TextureManager.hpp
    )

set(TEXTURE_MANAGER_SOURCES
    src/TextureManager.cpp
    )

add_library(texture_manager STATIC ${TEXTURE_MANAGER_SOURCES} ${TEXTURE_MANAGER_HEADERS})

target_link_libraries(texture_manager
    PRIVATE
    log
    math
    asset_util
    ${SDL2_IMAGE_LIBRARIES}
    )

target_include_directories(texture_manager
    PUBLIC
    include
    PRIVATE
    src
    )

project(asset_util LANGUAGES CXX)

set (ASSET_UTIL_HEADERS
    include/asset_util/Util.hpp
    )

set(ASSET_UTIL_SOURCES
    src/Util.cpp
    )

add_library(asset_util STATIC ${ASSET_UTIL_SOURCES} ${ASSET_UTIL_HEADERS})

target_link_libraries(asset_util
    PRIVATE
    log
    )

target_include_directories(asset_util
    PUBLIC
    include
    PRIVATE
    src
    )

project(debug_draw LANGUAGES CXX)

add_library(debug_draw INTERFACE)

target_include_directories(debug_draw
    INTERFACE
    include
    )
