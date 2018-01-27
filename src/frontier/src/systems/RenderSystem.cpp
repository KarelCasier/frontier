#include <frontier/systems/RenderSystem.hpp>

#include <frontier/components/Position.hpp>
#include <frontier/components/Sprite.hpp>

namespace frontier {
using namespace entityx;

RenderSystem::RenderSystem(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
}

void RenderSystem::update(entityx::EntityManager& entities, entityx::EventManager& /* events */, entityx::TimeDelta /* dt */)
{
    ComponentHandle<Position> position;
    ComponentHandle<Sprite> sprite;
    for (Entity entity : entities.entities_with_components(position, sprite)) {
        (void)entity; // no unused warn
        _textureManager->render(sprite->_ref, position->_position.x, position->_position.y, sprite->_rect.w,
                                sprite->_rect.h);
    }
}

} // namespace frontier
