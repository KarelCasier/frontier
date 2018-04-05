#pragma once

#include <entityx/entityx.h>

#include <math/Vector2.hpp>
#include <vector>

namespace frontier {

class NavigationComponent : public entityx::Component<NavigationComponent> {
public:
    NavigationComponent(Vector2f target)
    : _target{std::move(target)}
    , _stalePath{true}
    {
    }

    bool stale() const { return _stalePath; }
    void invalidate() { _stalePath = true; }

    void setTarget(const Vector2f& target)
    {
        if (target != _target) {
            _target = target;
            _stalePath = true;
        }
    }

    const Vector2f& getTarget() const { return _target; }

    const std::vector<Vector2f>& getPath() const { return _path; }

private:
    friend class NavigationSystem;

    void setPath(std::vector<Vector2f> path)
    {
        _path = std::move(path);
        _stalePath = false;
    }

    Vector2f _target;
    bool _stalePath;
    std::vector<Vector2f> _path;
};

} // namespace frontier
