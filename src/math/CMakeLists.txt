project(math LANGUAGES CXX)

add_library(math INTERFACE)

target_include_directories(math
    INTERFACE
    include
)

target_link_libraries(math
    INTERFACE
    utils
)

add_subdirectory(test)
