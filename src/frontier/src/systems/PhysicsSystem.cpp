#include <frontier/systems/PhysicsSystem.hpp>

#include <frontier/components/PositionComponent.hpp>
#include <frontier/components/VelocityComponent.hpp>

namespace frontier {
using namespace entityx;

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(entityx::EntityManager& entities, entityx::EventManager& /* events */, entityx::TimeDelta dt)
{
    ComponentHandle<PositionComponent> position;
    ComponentHandle<VelocityComponent> velocity;
    for (Entity entity : entities.entities_with_components(position, velocity)) {
        (void)entity; // no unused warn
        position->_position += (velocity->_velocity * dt);
    }
}

} // namespace frontier
