#pragma once

#include <entityx/entityx.h>
#include <texture_manager/TextureManager.hpp>
#include <debug_draw/IDebugDrawable.hpp>

namespace frontier {

class RenderSystem : public entityx::System<RenderSystem> {
public:
    RenderSystem(std::shared_ptr<TextureManager> textureManager);
    ~RenderSystem() override = default;

    void debugDraw(std::shared_ptr<IDebugDrawable> debugDrawable);

    /// @name System overrides
    /// @{
    void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
    /// @}

private:
    std::shared_ptr<TextureManager> _textureManager;
    std::vector<std::shared_ptr<IDebugDrawable>> _debugDrawables;
};

} // namespace frontier

