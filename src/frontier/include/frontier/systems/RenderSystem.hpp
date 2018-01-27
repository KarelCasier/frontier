#pragma once

#include <entityx/entityx.h>
#include <texture_manager/TextureManager.hpp>

namespace frontier {

class RenderSystem : public entityx::System<RenderSystem> {
public:
    RenderSystem(std::shared_ptr<TextureManager> textureManager);
    ~RenderSystem() override = default;

    /// @name System overrides
    /// @{
    void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
    /// @}

private:
    std::shared_ptr<TextureManager> _textureManager;
};

} // namespace frontier

