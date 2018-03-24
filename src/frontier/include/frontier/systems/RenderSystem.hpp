#pragma once

#include <entityx/entityx.h>
#include <graphics/Window.hpp>
#include <graphics/IRenderable.hpp>
#include <frontier/events/DebugDrawableEvent.hpp>

namespace frontier {

class RenderSystem : public entityx::System<RenderSystem>, public entityx::Receiver<RenderSystem> {
public:
    RenderSystem(std::shared_ptr<Window> window);
    ~RenderSystem() override = default;

    /// @name System overrides
    /// @{
    void configure(entityx::EventManager& eventManager) override;
    void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
    /// @}

    /// @name Receiver events
    /// @{
    void receive(const DebugDrawableEvent& debugDrawableEvent);
    /// @}

private:
    std::shared_ptr<Window> _window;
    std::vector<std::weak_ptr<IRenderable>> _debugDrawables;
};

} // namespace frontier
