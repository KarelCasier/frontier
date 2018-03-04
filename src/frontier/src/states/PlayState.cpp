#include <frontier/states/PlayState.hpp>

#include <input/BindingContext.hpp>
#include <input/BindingData.hpp>
#include <input/InputActions.hpp>
#include <input/InputManager.hpp>
#include <graphics/RenderManager.hpp>
#include <graphics/TextureManager.hpp>

#include <log/log.hpp>

namespace frontier {

PlayState::PlayState(std::shared_ptr<RenderManager> renderManager,
                     std::shared_ptr<TextureManager> textureManager,
                     std::shared_ptr<InputManager> inputManager)
: _renderManager{std::move(renderManager)}
, _textureManager{std::move(textureManager)}
, _inputManager{std::move(inputManager)}
, _world{_renderManager, _textureManager, _inputManager}
{
}

PlayState::~PlayState() {}

void PlayState::onEnter()
{
    _bindingContext = std::make_shared<BindingContext>();
    _bindingContext->addMouseActionBinding(LeftClick, MouseButtonBindingData{MouseButton::LEFT, ButtonState::PRESSED});
    _bindingContext->addMouseActionBinding(RightClick,
                                           MouseButtonBindingData{MouseButton::RIGHT, ButtonState::PRESSED});
    _bindingContext->addKeyboardActionBinding("A", KeyboardBindingData{SDLK_a, ButtonState::PRESSED, ModifierBitset{}});
    _bindingContext->addKeyboardActionBinding("ARel",
                                              KeyboardBindingData{SDLK_a, ButtonState::RELEASED, ModifierBitset{}});
    ModifierBitset alt{};
    alt.set(Modifier::ALT);
    _bindingContext->addKeyboardActionBinding("Alt-A", KeyboardBindingData{SDLK_a, ButtonState::PRESSED, alt});
    _inputManager->pushContext(_bindingContext);
}

void PlayState::onExit()
{
    _inputManager->popContext();
}

void PlayState::update(std::chrono::milliseconds delta)
{
    _world.update(delta);
}

void PlayState::render()
{
    _world.render();
}

void PlayState::handleEvent(const SDL_Event& event)
{
    _inputManager->handleEvent(event);
}

} // namespace frontier
