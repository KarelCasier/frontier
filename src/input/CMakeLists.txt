project(input LANGUAGES CXX)

set(HEADERS
    include/input/BindingContext.hpp
    include/input/BindingData.hpp
    include/input/IInputConsumer.hpp
    include/input/IInputProducer.hpp
    include/input/InputActions.hpp
    include/input/InputConsumer.hpp
    include/input/InputEvent.hpp
    include/input/InputManager.hpp

    include/input/Optional.hpp
    include/input/Util.hpp
    )

set(SOURCES
    src/BindingContext.cpp
    src/InputConsumer.cpp
    src/InputManager.cpp
    )

add_library(input STATIC ${SOURCES} ${HEADERS})

target_include_directories(input
    PUBLIC
    include
    PRIVATE
    src
    )

target_link_libraries(input
    PUBLIC
    PRIVATE
    log
    ${SDL2_LIBRARY}
    )
