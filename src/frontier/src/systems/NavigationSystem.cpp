#include <frontier/systems/NavigationSystem.hpp>

#include <frontier/components/NavigationComponent.hpp>
#include <frontier/components/TransformComponent.hpp>

#include <graphics/Util.hpp>
#include <frontier/LevelNavParser.hpp>

namespace frontier {
using namespace entityx;

NavigationSystem::NavigationSystem(const std::string& file)
{
    _navMesh = LevelNavParser{}.parse(file);
}

const std::shared_ptr<NavMesh> NavigationSystem::getNavMesh() const
{
    return _navMesh;
}

void NavigationSystem::update(entityx::EntityManager& entities,
                              entityx::EventManager& /* events */,
                              entityx::TimeDelta /* dt */)
{
    ComponentHandle<NavigationComponent> navigation;
    ComponentHandle<TransformComponent> transform;
    for (Entity entity : entities.entities_with_components(transform, navigation)) {
        (void)entity; // no unused warn

        if (navigation->stale()) {
            navigation->setPath(_navMesh->findPath(transform->_position, navigation->getTarget()));
        }
    }
}

} // namespace frontier
