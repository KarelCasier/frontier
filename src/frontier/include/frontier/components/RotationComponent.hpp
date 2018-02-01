#pragma once

#include <entityx/entityx.h>

#include <math/Vector2.hpp>

namespace frontier {

class RotationComponent : public entityx::Component<RotationComponent> {
public:
    RotationComponent(double orientation = 0.f, double angularVelocity = 0.f, double torque = 0.f)
    : _orientation{orientation}
    , _angularVelocity{angularVelocity}
    , _torque{torque}
    {
    }

    double _orientation; // radians
    double _angularVelocity;
    double _torque;
};

} // namespace frontier
