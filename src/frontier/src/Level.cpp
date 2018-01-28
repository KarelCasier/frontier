#include <frontier/Level.hpp>

#include <frontier/systems/RenderSystem.hpp>
#include <frontier/components/Position.hpp>
#include <frontier/components/Sprite.hpp>

namespace frontier {

Level::Level(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
}

void Level::finishInit()
{
    _entityX.systems.configure();
}

void Level::update(std::chrono::milliseconds /* delta  */) {}

void Level::render()
{
    _entityX.systems.update<RenderSystem>(0);
}

} // namespace frontier
