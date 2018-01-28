#include <frontier/World.hpp>

#include <frontier/LevelParser.hpp>

namespace frontier {

World::World(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
    _level = LevelParser{_textureManager}.parse("level1.xml");
}

void World::update(std::chrono::milliseconds delta)
{
    _level->update(delta);
}

void World::render()
{
    _level->render();
}

} // namespace frontier
