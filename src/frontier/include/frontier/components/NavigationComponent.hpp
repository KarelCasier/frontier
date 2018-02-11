#pragma once

#include <entityx/entityx.h>

#include <math/Vector2.hpp>
#include <vector>

namespace frontier {

class NavigationComponent : public entityx::Component<NavigationComponent> {
public:
    NavigationComponent(Vector2f target)
    : _target{std::move(target)}
    {
    }

    Vector2f _target;

    std::vector<Vector2f> _path;
};

} // namespace frontier
