#pragma once

#include <entityx/entityx.h>

#include <math/Vector2.hpp>

namespace frontier {

class VelocityComponent : public entityx::Component<VelocityComponent> {
public:
    VelocityComponent(Vector2f velocity)
    : _velocity{std::move(velocity)}
    {
    }

    Vector2f _velocity;
};

} // namespace frontier
