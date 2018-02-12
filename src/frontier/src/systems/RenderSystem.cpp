#include <frontier/systems/RenderSystem.hpp>

#include <frontier/components/TransformComponent.hpp>
#include <frontier/components/SpriteComponent.hpp>

namespace frontier {

using namespace entityx;

RenderSystem::RenderSystem(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
}

void RenderSystem::debugDraw(std::shared_ptr<IDebugDrawable> debugDrawable) {
    _debugDrawables.push_back(std::move(debugDrawable));
}

void RenderSystem::update(entityx::EntityManager& entities,
                          entityx::EventManager& /* events */,
                          entityx::TimeDelta /* dt */)
{
    ComponentHandle<TransformComponent> transform;
    ComponentHandle<SpriteComponent> sprite;
    for (Entity entity : entities.entities_with_components(transform, sprite)) {
        (void)entity; // no unused warn
        SDL_Rect srcRect{0, 0, static_cast<int>(sprite->_rect.w()), static_cast<int>(sprite->_rect.h())};
        SDL_Rect destRect{static_cast<int>(transform->_position.x()), static_cast<int>(transform->_position.y()),
                          static_cast<int>(sprite->_rect.w()), static_cast<int>(sprite->_rect.h())};
        const auto orientation = transform->_orientation;
        _textureManager->render(sprite->_ref, srcRect, destRect, orientation);
    }

    for (const auto& drawable : _debugDrawables) {
        drawable->debugDraw(_textureManager->getRenderer());
    }
}

} // namespace frontier
