#include <input/InputManager.hpp>

#include <utility>
#include <map>
#include <stdio.h>

#include <input/BindingContext.hpp>
#include <input/InputConsumer.hpp>
#include <log/log.hpp>

namespace {

using namespace frontier;

/// Convert SDL modifier bitmask to modifer bitset
ModifierBitset toModifierBitset(uint16_t sdlModifiers)
{
    auto modifiers = ModifierBitset{};
    static const auto modifierMap = std::map<SDL_Keymod, Modifier>{
        {SDL_Keymod::KMOD_LSHIFT, Modifier::SHIFT}, {SDL_Keymod::KMOD_RSHIFT, Modifier::SHIFT},
        {SDL_Keymod::KMOD_LCTRL, Modifier::CTRL},   {SDL_Keymod::KMOD_RCTRL, Modifier::CTRL},
        {SDL_Keymod::KMOD_LALT, Modifier::ALT},     {SDL_Keymod::KMOD_RALT, Modifier::ALT},
    };
    for (const auto& [sdlMod, mod] : modifierMap) {
        if ((sdlModifiers & sdlMod) == sdlMod) {
            modifiers.set(mod);
        }
    }
    return modifiers;
}

/// Convert SDL button state to ButtonState
ButtonState toButtonState(uint8_t sdlButtonState)
{
    static const auto buttonStateMap = std::map<uint8_t, ButtonState>{
        {SDL_PRESSED, ButtonState::PRESSED},
        {SDL_RELEASED, ButtonState::RELEASED},
    };
    for (const auto& [sdlState, state] : buttonStateMap) {
        if (sdlState == sdlButtonState) {
            return state;
        }
    }
    throw std::runtime_error{"Invalid sdl button state"};
}

/// Convert SDL mouse button to MouseButton
MouseButton toMouseButton(uint8_t sdlMouseButton)
{
    static const auto mouseButtonMap = std::map<uint8_t, MouseButton>{
        {SDL_BUTTON_LEFT, MouseButton::LEFT},
        {SDL_BUTTON_MIDDLE, MouseButton::MIDDLE},
        {SDL_BUTTON_RIGHT, MouseButton::RIGHT},
    };
    for (const auto& [sdlButton, button] : mouseButtonMap) {
        if (sdlButton == sdlMouseButton) {
            return button;
        }
    }
    throw std::runtime_error{"Invalid sdl mouse button"};
}

/// Convert a SDL_KeyboardEvent to the corresponding KeyboardBindingData structure
KeyboardBindingData toKeyboardBindingData(const SDL_KeyboardEvent& event)
{
    return {event.keysym.sym, toButtonState(event.state), toModifierBitset(event.keysym.mod)};
}

/// Convert a SDL_MouseButtonEvent to the corresponding MouseButtonBindingData structure
MouseButtonBindingData toMouseButtonBindingData(const SDL_MouseButtonEvent& event)
{
    return {toMouseButton(event.button), toButtonState(event.state)};
}

} // namespace

namespace frontier {

void InputManager::pushContext(std::weak_ptr<BindingContext> context)
{
    _contexts.emplace_back(std::move(context));
}

bool InputManager::popContext()
{
    if (_contexts.empty()) {
        return false;
    }
    _contexts.pop_back();
    return true;
}

void InputManager::handleEvent(const SDL_Event& event)
{
    const auto& type = event.type;
    switch (type) {
    case SDL_EventType::SDL_KEYUP:
    case SDL_EventType::SDL_KEYDOWN:
        handleKeyboardEvent(event.key);
        break;
    case SDL_EventType::SDL_MOUSEBUTTONUP:
    case SDL_EventType::SDL_MOUSEBUTTONDOWN:
        handleMouseButtonEvent(event.button);
        break;
    case SDL_EventType::SDL_MOUSEMOTION:
        /// TODO: Map to axis
        break;
    default:
        break;
    }
}

void InputManager::handleKeyboardEvent(const SDL_KeyboardEvent& event)
{
    const auto& context = topContext();
    if (!context) {
        LOGW << "Input ignored as there are no binding contexts";
        return;
    }
    const auto action = context->mapKeyboardBindingToAction(toKeyboardBindingData(event));
    if (action) {
        notifyAll(ActionEvent{*action});
    }
}

void InputManager::handleMouseButtonEvent(const SDL_MouseButtonEvent& event)
{
    const auto& context = topContext();
    if (!context) {
        LOGW << "Input ignored as there are no binding contexts";
        return;
    }
    const auto action = context->mapMouseButtonBindingToAction(toMouseButtonBindingData(event));
    if (action) {
        notifyAll(MouseEvent{*action, event.x, event.y});
    }
}

template <typename EventT>
void InputManager::notifyAll(const EventT& event)
{
    for (auto I = begin(_inputConsumers); I != end(_inputConsumers); ++I) {
        (*I)->receive(event);
    }
}

/// Explicit template instances (avoid having to define in header)
template void InputManager::notifyAll(const ActionEvent& event);
template void InputManager::notifyAll(const MouseEvent& event);

void InputManager::subscribe(InputConsumer* inputConsumer)
{
    const auto I = std::find(begin(_inputConsumers), end(_inputConsumers), inputConsumer);
    if (I == end(_inputConsumers)) {
        _inputConsumers.emplace_back(std::move(inputConsumer));
    } else {
        LOGW << "Unable to subscribe input consumer as it is already subscribed";
    }
}

void InputManager::unsubscribe(InputConsumer* inputConsumer)
{
    const auto I = std::find(begin(_inputConsumers), end(_inputConsumers), inputConsumer);
    if (I != end(_inputConsumers)) {
        _inputConsumers.erase(I);
    } else {
        LOGW << "Unable to unsubscribe input consumer as it is not subscribed";
    }
}

std::shared_ptr<BindingContext> InputManager::topContext()
{
    for (auto I = std::rbegin(_contexts); I != std::rend(_contexts); ++I) {
        if (auto strongContext = I->lock()) {
            return strongContext;
        } else {
            /// Reverse iterators are offset 1 from forward iterators
            auto forwardI = _contexts.erase(std::next(I).base());
            I = std::reverse_iterator{forwardI};
            LOGW << "Removing binding context as it failed to promote to a shared_ptr";
        }
    }
    return nullptr;
}

} // namespace frontier
