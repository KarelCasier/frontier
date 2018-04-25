#pragma once

#include <entityx/entityx.h>

#include <navigation/NavMesh.hpp>

struct SDL_Renderer;

namespace frontier {

class NavigationSystem : public entityx::System<NavigationSystem> {
public:
    NavigationSystem(const std::string& file);
    ~NavigationSystem() override = default;

    const std::shared_ptr<NavMesh> getNavMesh() const;

    /// @name System overrides
    /// @{
    void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
    /// @}

private:
    std::shared_ptr<NavMesh> _navMesh;
};

} // namespace frontier

