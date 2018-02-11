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

set (HEADERS
    include/asset_util/Util.hpp
    )

set(SOURCES
    src/Util.cpp
    )

add_library(asset_util STATIC ${SOURCES} ${HEADERS})

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

