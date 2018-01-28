#pragma once

#include <entityx/entityx.h>

#include <math/Vector2.hpp>

namespace frontier {

class PositionComponent : public entityx::Component<PositionComponent> {
public:
    PositionComponent(Vector2f position)
    : _position{std::move(position)}
    {
    }

    Vector2f _position;
};

} // namespace frontier
