#include <frontier/systems/RenderSystem.hpp>

#include <frontier/components/PositionComponent.hpp>
#include <frontier/components/RotationComponent.hpp>
#include <frontier/components/SpriteComponent.hpp>

namespace frontier {

using namespace entityx;

RenderSystem::RenderSystem(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
}

void RenderSystem::update(entityx::EntityManager& entities,
                          entityx::EventManager& /* events */,
                          entityx::TimeDelta /* dt */)
{
    ComponentHandle<PositionComponent> position;
    ComponentHandle<SpriteComponent> sprite;
    for (Entity entity : entities.entities_with_components(position, sprite)) {
        (void)entity; // no unused warn
        SDL_Rect srcRect{0, 0, static_cast<int>(sprite->_rect.w), static_cast<int>(sprite->_rect.h)};
        SDL_Rect destRect{static_cast<int>(position->_position.x), static_cast<int>(position->_position.y),
                          static_cast<int>(sprite->_rect.w), static_cast<int>(sprite->_rect.h)};
        auto rotation = entity.component<RotationComponent>();
        auto orientation{0.0};
        if (rotation.valid()) {
            orientation = rotation->_orientation;
        }
        _textureManager->render(sprite->_ref, srcRect, destRect, orientation);
    }
}

} // namespace frontier
