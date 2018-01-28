#pragma once

#include <entityx/entityx.h>

#include <math/Vector2.hpp>

namespace frontier {

class PhysicsComponent : public entityx::Component<PhysicsComponent> {
public:
    PhysicsComponent(Vector2f velocity, float friction = 0.7f)
    : _velocity{std::move(velocity)}
    , _friction{friction}
    {
    }

    Vector2f _velocity;
    float _friction;
};

} // namespace frontier
