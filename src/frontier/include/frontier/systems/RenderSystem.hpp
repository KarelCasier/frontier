#pragma once

#include <entityx/entityx.h>
#include <texture_manager/TextureManager.hpp>
#include <debug_draw/IDebugDrawable.hpp>
#include <frontier/events/DebugDrawableEvent.hpp>

namespace frontier {

class RenderSystem : public entityx::System<RenderSystem>, public entityx::Receiver<RenderSystem> {
public:
    RenderSystem(std::shared_ptr<TextureManager> textureManager);
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
    std::shared_ptr<TextureManager> _textureManager;
    std::vector<std::weak_ptr<IDebugDrawable>> _debugDrawables;
};

} // namespace frontier
