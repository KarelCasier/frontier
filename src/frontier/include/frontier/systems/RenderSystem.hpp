#pragma once

#include <entityx/entityx.h>
#include <graphics/RenderManager.hpp>
#include <graphics/ISelfRenderable.hpp>
#include <frontier/events/DebugDrawableEvent.hpp>

namespace frontier {

class RenderSystem : public entityx::System<RenderSystem>, public entityx::Receiver<RenderSystem> {
public:
    RenderSystem(std::shared_ptr<RenderManager> renderManager);
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
    std::shared_ptr<RenderManager> _renderManager;
    std::vector<std::weak_ptr<ISelfRenderable>> _debugDrawables;
};

} // namespace frontier
