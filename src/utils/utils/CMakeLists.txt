project(utils LANGUAGES CXX)

add_library(utils INTERFACE)

target_include_directories(utils
    INTERFACE
    include
)

