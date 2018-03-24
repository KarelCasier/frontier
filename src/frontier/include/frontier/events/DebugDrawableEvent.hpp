#pragma once

#include <memory>
#include <graphics/IRenderable.hpp>

namespace frontier {

class DebugDrawableEvent {
public:
    DebugDrawableEvent(std::weak_ptr<IRenderable> debugDrawable, bool enable)
    : _debugDrawable{std::move(debugDrawable)}
    , _enable{enable}
    {
    }

    std::weak_ptr<IRenderable> get() const { return _debugDrawable; }
    bool enable() const { return _enable; }

private:
    std::weak_ptr<IRenderable> _debugDrawable;
    bool _enable;
};

} // namespace frontier
