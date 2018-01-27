#include <frontier/World.hpp>

#include <frontier/systems/RenderSystem.hpp>

namespace frontier {

World::World(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
    ref = _textureManager->loadTexture("Test.png");
    _entityX.systems.add<RenderSystem>(_textureManager);
    _entityX.systems.configure();
}

void World::update(std::chrono::milliseconds /* delta  */) {}

void World::render()
{
    _entityX.systems.update<RenderSystem>(0);
    _textureManager->render(ref, 300, 300, 100, 100);
}

} // namespace frontier
