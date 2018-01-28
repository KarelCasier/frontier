#pragma once

#include <entityx/entityx.h>
#include <texture_manager/TextureManager.hpp>

namespace frontier {

class PhysicsSystem : public entityx::System<PhysicsSystem> {
public:
    PhysicsSystem();
    ~PhysicsSystem() override = default;

    /// @name System overrides
    /// @{
    void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
    /// @}

private:
};

} // namespace frontier

