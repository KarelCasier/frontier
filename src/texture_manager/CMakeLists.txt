project(texture_manager LANGUAGES CXX)

find_package(SDL2_image REQUIRED)

add_library(texture_manager
    src/TextureManager.cpp
    )

target_include_directories(texture_manager
    PUBLIC
    include
    PRIVATE
    src
    )

target_link_libraries(texture_manager
    PRIVATE
    log
    ${SDL2_IMAGE_LIRARIES}
    )
