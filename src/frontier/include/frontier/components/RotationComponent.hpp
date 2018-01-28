#pragma once

#include <entityx/entityx.h>

#include <math/Vector2.hpp>

namespace frontier {

class RotationComponent : public entityx::Component<RotationComponent> {
public:
    RotationComponent(float orientation = 0.f, float angularVelocity = 0.f, float torque = 0.f)
    : _orientation{orientation}
    , _angularVelocity{angularVelocity}
    , _torque{torque}
    {
    }

    float _orientation; // radians
    float _angularVelocity;
    float _torque;
};

} // namespace frontier
