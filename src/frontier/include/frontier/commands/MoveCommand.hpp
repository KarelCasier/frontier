#pragma once

#include <entityx/Entity.h>
#include "Command.hpp"

namespace frontier {

class MoveCommand : public Command {
public:
    enum class Direction {
        N,
        NE,
        E,
        SE,
        S,
        SW,
        W,
        NW,
    };

    MoveCommand(entityx::Entity entity, Direction direction, float force)
    : _entity{std::move(entity)}
    , _direction{direction}
    , _force{force}
    {
    }

    /// @name Command overrides
    /// @{
    void execute(entityx::EventManager& eventManager) override {}
    /// @}

private:
    entityx::Entity _entity;
    Direction _direction;
    float _force;
};

} // namespace frontier
