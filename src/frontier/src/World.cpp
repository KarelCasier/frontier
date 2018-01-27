#include <frontier/World.hpp>

#include <frontier/systems/RenderSystem.hpp>
#include <frontier/components/Position.hpp>
#include <frontier/components/Sprite.hpp>

namespace frontier {

World::World(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
    _entityX.systems.add<RenderSystem>(_textureManager);
    _entityX.systems.configure();

    auto entity = _entityX.entities.create();
    auto ref = _textureManager->loadTexture("Test.png");
    entity.assign<Position>(Point2i{0,0});
    entity.assign<Sprite>(ref, Recti{0, 0, 100,100});
}

void World::update(std::chrono::milliseconds /* delta  */) {}

void World::render()
{
    _entityX.systems.update<RenderSystem>(0);
}

} // namespace frontier
