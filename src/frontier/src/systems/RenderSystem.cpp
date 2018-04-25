#include <frontier/systems/RenderSystem.hpp>

#include <frontier/components/NavigationComponent.hpp>
#include <frontier/components/ShapeComponent.hpp>
#include <frontier/components/SpriteComponent.hpp>
#include <frontier/components/TransformComponent.hpp>
#include <frontier/components/Util.hpp>
#include <log/log.hpp>
#include <math/Misc.hpp>

namespace {

/// Compare two weak_ptrs
template <typename T>
struct WeakPtrCompare {
    explicit WeakPtrCompare(const std::weak_ptr<T>& first)
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
    ComponentHandle<ShapeComponent> shape;
    for (Entity entity __unused : entities.entities_with_components(transform, sprite, shape)) {
        const auto srcRect = static_cast<Recti>(sprite->_srcRect);
        assert(shape->_type == ShapeComponent::Type::Rect); // TODO(Karel): add support for other shapes
        const auto destRect =
            Recti{static_cast<int>(transform->_position.x()), static_cast<int>(transform->_position.y()),
                  static_cast<int>(shape->_shape._rect.x()), static_cast<int>(shape->_shape._rect.y())};
        const auto orientation = transform->_orientation;
        _window->render(sprite->_ref, srcRect, destRect, orientation);

        // Debug draw bounds
        auto transShape = transformedShape(transform, shape);
        _window->render(transShape.points(), PrimativeType::LineStrip, {0,255, 0});
        auto norms = transShape.normals();
        for (auto i{0u}; i < norms.size(); ++i) {
            const auto o = (i + 1) % norms.size();
            const auto faceMid = Vector2f{transShape.point(o) - transShape.point(i)} / 2.f;
            const auto pt = transShape.point(i) + faceMid;
            _window->render({pt, pt + norms[i] * 5.f}, PrimativeType::LineStrip, {0,255, 0});
        }
    }

    ComponentHandle<NavigationComponent> nav;
    for (Entity entity __unused : entities.entities_with_components(nav)) {
        _window->render(nav->getPath(), PrimativeType::LineStrip, {0, 0, 255});
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
