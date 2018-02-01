#pragma once

#include <entityx/entityx.h>

#include <math/Vector2.hpp>

namespace frontier {

class PhysicsComponent : public entityx::Component<PhysicsComponent> {
public:
    PhysicsComponent(Vector2f velocity, double friction = 0.7, double angularVelocity = 0.0, double torque = 0.0)
    : _velocity{std::move(velocity)}
    , _friction{friction}
    , _angularVelocity{angularVelocity}
    , _torque{torque}
    {
    }

    Vector2f _velocity;
    double _friction;
    double _angularVelocity;
    double _torque;
};

} // namespace frontier
