#include <frontier/states/PlayState.hpp>

#include <input/BindingContext.hpp>
#include <input/BindingData.hpp>
#include <input/InputActions.hpp>
#include <input/InputManager.hpp>
#include <graphics/Window.hpp>
#include <graphics/TextureManager.hpp>

#include <log/log.hpp>

namespace frontier {

PlayState::PlayState(std::shared_ptr<Window> window,
                     std::shared_ptr<TextureManager> textureManager,
                     std::shared_ptr<InputManager> inputManager)
: _window{std::move(window)}
, _textureManager{std::move(textureManager)}
, _inputManager{std::move(inputManager)}
, _world{_window, _textureManager, _inputManager}
{
}

PlayState::~PlayState() {}

void PlayState::onEnter()
{
    _bindingContext = std::make_shared<BindingContext>();
    _bindingContext->addMouseActionBinding(LeftClick, MouseButtonBindingData{MouseButton::LEFT, ButtonState::PRESSED});
    _bindingContext->addMouseActionBinding(RightClick,
                                           MouseButtonBindingData{MouseButton::RIGHT, ButtonState::PRESSED});

    _bindingContext->addKeyboardActionBinding("Left", KeyboardBindingData{SDLK_LEFT, ButtonState::PRESSED, {}});
    _bindingContext->addKeyboardActionBinding("Right", KeyboardBindingData{SDLK_RIGHT, ButtonState::PRESSED, {}});
    _bindingContext->addKeyboardActionBinding("Up", KeyboardBindingData{SDLK_UP, ButtonState::PRESSED, {}});
    _bindingContext->addKeyboardActionBinding("Down", KeyboardBindingData{SDLK_DOWN, ButtonState::PRESSED, {}});
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
