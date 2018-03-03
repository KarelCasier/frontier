#pragma once

#include <memory>
#include <graphics/IDebugDrawable.hpp>

namespace frontier {

class DebugDrawableEvent {
public:
    DebugDrawableEvent(std::weak_ptr<IDebugDrawable> debugDrawable, bool enable)
    : _debugDrawable{std::move(debugDrawable)}
    , _enable{enable}
    {
    }

    std::weak_ptr<IDebugDrawable> get() const { return _debugDrawable; }
    bool enable() const { return _enable; }

private:
    std::weak_ptr<IDebugDrawable> _debugDrawable;
    bool _enable;
};

} // namespace frontier
