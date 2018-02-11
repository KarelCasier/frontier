#include <frontier/systems/NavigationSystem.hpp>

#include <frontier/components/NavigationComponent.hpp>
#include <frontier/components/TransformComponent.hpp>

#include <asset_util/Util.hpp>
#include <frontier/LevelNavParser.hpp>

namespace frontier {
using namespace entityx;

NavigationSystem::NavigationSystem(const std::string& file)
{
    _navMesh = LevelNavParser{}.parse(file);
}

void NavigationSystem::update(entityx::EntityManager& entities,
                              entityx::EventManager& /* events */,
                              entityx::TimeDelta /* dt */)
{
    ComponentHandle<NavigationComponent> navigation;
    ComponentHandle<TransformComponent> transform;
    for (Entity entity : entities.entities_with_components(transform, navigation)) {
        (void)entity; // no unused warn

        navigation->_path = _navMesh->navigationPath(transform->_position, navigation->_target);
    }
}

} // namespace frontier
