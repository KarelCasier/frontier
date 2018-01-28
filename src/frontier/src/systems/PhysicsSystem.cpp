#include <frontier/systems/PhysicsSystem.hpp>

#include <frontier/components/PositionComponent.hpp>
#include <frontier/components/PhysicsComponent.hpp>

namespace frontier {
using namespace entityx;

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(entityx::EntityManager& entities, entityx::EventManager& /* events */, entityx::TimeDelta dt)
{
    ComponentHandle<PositionComponent> position;
    ComponentHandle<PhysicsComponent> physics;
    for (Entity entity : entities.entities_with_components(position, physics)) {
        (void)entity; // no unused warn
        position->_position += (physics->_velocity * dt);
        physics->_velocity *= std::pow(physics->_friction, dt);
    }
}

} // namespace frontier
