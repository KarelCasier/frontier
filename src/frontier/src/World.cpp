#include <frontier/World.hpp>

#include <frontier/Level.hpp>
#include <frontier/LevelParser.hpp>
#include <graphics/TextureManager.hpp>
#include <graphics/Window.hpp>
#include <input/InputManager.hpp>
#include <log/log.hpp>

namespace frontier {

World::World(std::shared_ptr<Window> window,
             std::shared_ptr<TextureManager> textureManager,
             std::shared_ptr<InputManager> inputManager)
: _window{std::move(window)}
, _textureManager{std::move(textureManager)}
, _inputManager{std::move(inputManager)}
{
    _level = LevelParser{_window, _textureManager, _inputManager}.parse("level1.xml");
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
