#include <frontier/World.hpp>

namespace frontier {

World::World(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
    ref = _textureManager->loadTexture("Test.png");
}

void World::update(std::chrono::milliseconds /* delta */) {}
void World::render() {
    _textureManager->render(ref, 300, 300, 100, 100);
}

} // namespace frontier
