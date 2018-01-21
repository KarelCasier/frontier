project(log LANGUAGES CXX)

set (HEADERS
    include/log/log.hpp
    )

set(SOURCES
    src/log.cpp
    )

add_library(log STATIC ${SOURCES} ${HEADERS})

target_include_directories(log
    PUBLIC
    include
    PRIVATE
    src
)

