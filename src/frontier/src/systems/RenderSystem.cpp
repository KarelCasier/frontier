#include <frontier/systems/RenderSystem.hpp>

#include <frontier/components/TransformComponent.hpp>
#include <frontier/components/SpriteComponent.hpp>
#include <log/log.hpp>

namespace {

/// Compare two weak_ptrs
template <typename T>
struct WeakPtrCompare {
    WeakPtrCompare(const std::weak_ptr<T>& first)
    : _first{first}
    {
    }

    bool operator()(const std::weak_ptr<T>& second)
    {
        return !_first.owner_before(second) && !second.owner_before(_first);
    }

    const std::weak_ptr<T>& _first;
};

} // namespace

namespace frontier {

using namespace entityx;

RenderSystem::RenderSystem(std::shared_ptr<TextureManager> textureManager)
: _textureManager{std::move(textureManager)}
{
}

void RenderSystem::configure(EventManager& eventManager)
{
    eventManager.subscribe<DebugDrawableEvent>(*this);
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

    for (auto I = begin(_debugDrawables); I != end(_debugDrawables); ++I) {
        if (auto strongDrawable = I->lock()) {
            strongDrawable->debugDraw(_textureManager->getRenderer());
        } else {
            LOGI << "Removing debug drawable due to failed promotion to shared_ptr";
            I = _debugDrawables.erase(I);
        }
    }
}

void RenderSystem::receive(const DebugDrawableEvent& debugDrawableEvent)
{
    if (debugDrawableEvent.enable()) {
        _debugDrawables.push_back(debugDrawableEvent.get());
    } else {
        _debugDrawables.erase(std::remove_if(begin(_debugDrawables), end(_debugDrawables),
                                             WeakPtrCompare<IDebugDrawable>{debugDrawableEvent.get()}));
    }
}

} // namespace frontier
