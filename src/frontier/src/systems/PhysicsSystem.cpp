#include <frontier/systems/PhysicsSystem.hpp>

#include <frontier/components/TransformComponent.hpp>
#include <frontier/components/PhysicsComponent.hpp>

namespace frontier {
using namespace entityx;

PhysicsSystem::PhysicsSystem() {}

void PhysicsSystem::update(entityx::EntityManager& entities, entityx::EventManager& /* events */, entityx::TimeDelta dt)
{
    ComponentHandle<TransformComponent> transform;
    ComponentHandle<PhysicsComponent> physics;
    for (Entity entity : entities.entities_with_components(transform, physics)) {
        (void)entity; // no unused warn
        transform->_position += (physics->_velocity * dt);
        physics->_velocity *= std::pow(physics->_friction, dt);

        transform->_orientation += (physics->_angularVelocity * dt);
        physics->_angularVelocity *= std::pow(physics->_friction, dt);
    }
}

} // namespace frontier
