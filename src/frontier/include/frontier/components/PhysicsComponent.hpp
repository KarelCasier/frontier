#pragma once

#include <entityx/entityx.h>

#include <math/Vector2.hpp>

namespace frontier {

class PhysicsComponent : public entityx::Component<PhysicsComponent> {
public:
    PhysicsComponent(
        double mass, Vector2f velocity, double friction = 0.7, double angularVelocity = 0.0, double torque = 0.0)
    : _mass{mass}
    , _velocity{std::move(velocity)}
    , _friction{friction}
    , _angularVelocity{angularVelocity}
    , _torque{torque}
    {
    }

    double _mass;
    Vector2f _velocity;
    double _friction;
    double _angularVelocity;
    double _torque;
};

} // namespace frontier
