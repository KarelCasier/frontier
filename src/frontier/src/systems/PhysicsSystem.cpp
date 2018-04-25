#include <frontier/systems/PhysicsSystem.hpp>

#include <frontier/components/PhysicsComponent.hpp>
#include <frontier/components/ShapeComponent.hpp>
#include <frontier/components/TransformComponent.hpp>
#include <frontier/components/Util.hpp>

#include <graphics/Transform.hpp>
#include <math/Collision.hpp>
#include <math/Misc.hpp>

#include <log/log.hpp>

namespace {

using namespace entityx;
using namespace frontier;

} // namespace

namespace frontier {

using namespace entityx;

PhysicsSystem::PhysicsSystem() = default;

void PhysicsSystem::update(entityx::EntityManager& entities, entityx::EventManager& /* events */, entityx::TimeDelta dt)
{
    // Move phase
    ComponentHandle<TransformComponent> transform;
    ComponentHandle<PhysicsComponent> physics;
    for (Entity entity __unused: entities.entities_with_components(transform, physics)) {
        transform->_position += (physics->_velocity * dt);
        physics->_velocity *= std::pow(physics->_friction, dt);

        transform->_orientation += (physics->_angularVelocity * dt);
        physics->_angularVelocity *= std::pow(physics->_friction, dt);
    }

    // Collide phase
    ComponentHandle<TransformComponent> transformA;
    ComponentHandle<ShapeComponent> shapeA;
    ComponentHandle<PhysicsComponent> physicsA;

    ComponentHandle<TransformComponent> transformB;
    ComponentHandle<ShapeComponent> shapeB;
    ComponentHandle<PhysicsComponent> physicsB;

    std::set<Entity> considered{};
    for (Entity entityA : entities.entities_with_components(transformA, shapeA, physicsA)) {
        for (Entity entityB : entities.entities_with_components(transformB, shapeB, physicsB)) {
            if (entityA == entityB || considered.find(entityB) != end(considered)) {
                continue;
            }

            const auto transformedShapeA = transformedShape(transformA, shapeA);
            const auto transformedShapeB = transformedShape(transformB, shapeB);

            if (!!intersects(transformedShapeA, transformedShapeB)) {
                LOGI << "Collided: " << entityA.id().id() << " " << entityB.id().id();
            }
        }
        considered.insert(entityA);
    }
}

} // namespace frontier
