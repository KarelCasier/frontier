#pragma once

#include <memory>
#include <graphics/ISelfRenderable.hpp>

namespace frontier {

class DebugDrawableEvent {
public:
    DebugDrawableEvent(std::weak_ptr<ISelfRenderable> debugDrawable, bool enable)
    : _debugDrawable{std::move(debugDrawable)}
    , _enable{enable}
    {
    }

    std::weak_ptr<ISelfRenderable> get() const { return _debugDrawable; }
    bool enable() const { return _enable; }

private:
    std::weak_ptr<ISelfRenderable> _debugDrawable;
    bool _enable;
};

} // namespace frontier
