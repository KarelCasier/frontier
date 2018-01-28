#include <frontier/Level.hpp>

#include <frontier/systems/PhysicsSystem.hpp>
#include <frontier/systems/RenderSystem.hpp>

namespace frontier {

Level::Level(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
}

void Level::finishInit()
{
    _entityX.systems.configure();
}

void Level::update(std::chrono::milliseconds delta)
{
    _entityX.systems.update<PhysicsSystem>(delta.count());
}

void Level::render()
{
    _entityX.systems.update<RenderSystem>(0);
}

} // namespace frontier
