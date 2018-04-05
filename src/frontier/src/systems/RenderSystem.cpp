#include <frontier/systems/RenderSystem.hpp>

#include <frontier/components/TransformComponent.hpp>
#include <frontier/components/SpriteComponent.hpp>
#include <frontier/components/NavigationComponent.hpp>
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

RenderSystem::RenderSystem(std::shared_ptr<Window> window)
: _window{std::move(window)}
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
    for (Entity entity __unused: entities.entities_with_components(transform, sprite)) {
        const auto srcRect = static_cast<Recti>(sprite->_rect);
        const auto destRect = Recti{static_cast<int>(transform->_position.x()), static_cast<int>(transform->_position.y()),
                          static_cast<int>(sprite->_rect.w()), static_cast<int>(sprite->_rect.h())};
        const auto orientation = transform->_orientation;
        _window->render(sprite->_ref, srcRect, destRect, orientation);
    }

    ComponentHandle<NavigationComponent> nav;
    for (Entity entity __unused: entities.entities_with_components(nav)) {
        _window->render(nav->getPath(), PrimativeType::LineStrip, {0,0,255});
    }

    for (auto I = begin(_debugDrawables); I != end(_debugDrawables); ++I) {
        if (auto strongDrawable = I->lock()) {
            _window->render(*strongDrawable);
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
                                             WeakPtrCompare<IRenderable>{debugDrawableEvent.get()}));
    }
}

} // namespace frontier
