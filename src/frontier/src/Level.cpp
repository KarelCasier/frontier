#include <frontier/Level.hpp>

#include <frontier/systems/PhysicsSystem.hpp>
#include <frontier/systems/RenderSystem.hpp>
#include <frontier/systems/NavigationSystem.hpp>

#include <frontier/events/DebugDrawableEvent.hpp>

namespace frontier {

using namespace std::chrono;

Level::Level(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
}

void Level::finishInit()
{
    _entityX.systems.configure();
    auto navSystem = _entityX.systems.system<NavigationSystem>();
    _entityX.events.emit<DebugDrawableEvent>(navSystem->getNavMesh(), true);
}

void Level::update(milliseconds delta)
{
    const auto secondsDelta = duration<double, seconds::period>(delta).count();
    _entityX.systems.update<PhysicsSystem>(secondsDelta);
    _entityX.systems.update<NavigationSystem>(secondsDelta);
}

void Level::render()
{
    _entityX.systems.update<RenderSystem>(0);
}

} // namespace frontier
