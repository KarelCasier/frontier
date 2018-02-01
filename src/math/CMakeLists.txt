project(math LANGUAGES CXX)

set (HEADERS
    include/math/Collision.hpp
    include/math/Misc.hpp
    include/math/Rect.hpp
    include/math/Vector2.hpp
    )

set(SOURCES
    src/Collision.cpp
    )

add_library(math STATIC ${SOURCES} ${HEADERS})

target_include_directories(math
    PUBLIC
    include
    PRIVATE
    src
)

