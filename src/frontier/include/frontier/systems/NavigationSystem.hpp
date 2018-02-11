#pragma once

#include <entityx/entityx.h>

#include <navigation/NavMesh.hpp>

namespace frontier {

class NavigationSystem : public entityx::System<NavigationSystem> {
public:
    NavigationSystem(const std::string& navMeshFile);
    ~NavigationSystem() override = default;

    /// @name System overrides
    /// @{
    void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
    /// @}

private:
    std::shared_ptr<NavMesh<float>> _navMesh;
};

} // namespace frontier

