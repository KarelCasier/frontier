#pragma once

#include <entityx/entityx.h>

#include <math/Vector2.hpp>

namespace frontier {

class TransformComponent : public entityx::Component<TransformComponent> {
public:
    TransformComponent(Vector2f position, double orientation)
    : _position{std::move(position)}
    , _orientation{orientation}
    {
    }

    Vector2f _position;
    double _orientation; // radians
};

} // namespace frontier
