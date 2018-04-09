project(frontier LANGUAGES CXX)

find_package(SDL2 REQUIRED)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

set(HEADERSS
    include/frontier/components/InputComponent.hpp
    include/frontier/components/NavigationComponent.hpp
    include/frontier/components/PhysicsComponent.hpp
    include/frontier/components/PositionComponent.hpp
    include/frontier/components/SpriteComponent.hpp
    include/frontier/components/Util.hpp

    include/frontier/commands/Command.hpp
    include/frontier/commands/MoveCommand.hpp

    include/frontier/event/DebugDrawableEvent.hpp

    include/frontier/states/IState.hpp
    include/frontier/states/IStateMachine.hpp
    include/frontier/states/PlayState.hpp
    include/frontier/states/StateMachine.hpp

    include/frontier/systems/InputSystem.hpp
    include/frontier/systems/NavigationSystem.hpp
    include/frontier/systems/PhysicsSystem.hpp
    include/frontier/systems/RenderSystem.hpp

    include/frontier/Frontier.hpp
    include/frontier/Level.hpp
    include/frontier/LevelNavParser.hpp
    include/frontier/LevelParser.hpp
    include/frontier/SDLApplication.hpp
    include/frontier/World.hpp
    )

set(SOURCES
    src/components/InputComponent.cpp

    src/states/PlayState.cpp
    src/states/StateMachine.cpp

    src/systems/InputSystem.cpp
    src/systems/NavigationSystem.cpp
    src/systems/PhysicsSystem.cpp
    src/systems/RenderSystem.cpp

    src/Frontier.cpp
    src/Level.cpp
    src/LevelNavParser.cpp
    src/LevelParser.cpp
    src/SDLApplication.cpp
    src/World.cpp
    )

add_library(frontier_lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(frontier_lib
    PUBLIC
    include
    PRIVATE
    ${SDL2_INCLUDE_DIR}
    ../ext/entityx
    ../ext/moment
    ../ext/tinyxml2
    )

target_link_libraries(frontier_lib
    PUBLIC
    graphics
    PRIVATE
    input
    log
    navigation
    ${SDL2_LIBRARY}
    entityx
    tinyxml2
    moment_lib
    )

set (EXEC_HEADERS
    )

set (EXEC_SOURCES
    src/main.cpp
    )

add_executable(frontier ${EXEC_SOURCES} ${EXEC_HEADERS})

target_link_libraries(frontier
    frontier_lib
    )

