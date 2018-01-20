project(log LANGUAGES CXX)

add_library(log
    INTERFACE
    )

target_include_directories(log
    INTERFACE
    include
)
