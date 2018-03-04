#include <frontier/Level.hpp>

#include <graphics/TextureManager.hpp>
#include <input/InputManager.hpp>
#include <frontier/systems/InputSystem.hpp>
#include <frontier/systems/NavigationSystem.hpp>
#include <frontier/systems/PhysicsSystem.hpp>
#include <frontier/systems/RenderSystem.hpp>
#include <frontier/components/InputComponent.hpp>
#include <frontier/events/DebugDrawableEvent.hpp>
#include <input/InputActions.hpp>

#include <log/log.hpp>

namespace frontier {

using namespace std::chrono;

Level::Level(std::shared_ptr<RenderManager> renderManager,
             std::shared_ptr<TextureManager> textureManager,
             std::shared_ptr<InputManager> inputManager)
: _renderManager{std::move(renderManager)}
, _textureManager{std::move(textureManager)}
, _inputManager{std::move(inputManager)}
{
}

void Level::finishInit()
{
    _entityX.systems.configure();
    auto navSystem = _entityX.systems.system<NavigationSystem>();
    _entityX.events.emit<DebugDrawableEvent>(navSystem->getNavMesh(), true);

    auto e = _entityX.entities.create();
    auto input = InputComponent{};
    input.bindMouseCallback(LeftClick, [](int x, int y) { LOGI << "LEFT: " << x << ", " << y; });
    input.bindMouseCallback(RightClick, [](int x, int y) { LOGI << "RIGHT: " << x << ", " << y; });
    input.bindActionCallback("A", []() { LOGI << "A"; });
    input.bindActionCallback("ARel", []() { LOGI << "ARel"; });
    input.bindActionCallback("Alt-A", []() { LOGI << "Alt-A"; });
    e.assign_from_copy(input);
}

void Level::update(milliseconds delta)
{
    const auto secondsDelta = duration<double, seconds::period>(delta).count();
    _entityX.systems.update<PhysicsSystem>(secondsDelta);
    _entityX.systems.update<NavigationSystem>(secondsDelta);
    _entityX.systems.update<InputSystem>(secondsDelta);
}

void Level::render()
{
    _entityX.systems.update<RenderSystem>(0);
}

} // namespace frontier
