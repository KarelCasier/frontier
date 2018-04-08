#pragma once

#include <input/IInputProducer.hpp>
#include <input/InputEvent.hpp>
#include <SDL2/SDL_events.h>
#include <vector>
#include <deque>
#include <string>

namespace frontier {

class BindingContext;

/// Class to convert raw SDL events to input events and notify input consumers
class InputManager : public IInputProducer {
public:
    /// Push a binding context onto the stack
    /// @param context The binding context to push onto the stack
    void pushContext(std::weak_ptr<BindingContext> context);

    /// Pop a binding context from the stack
    /// @returns true if a context was popped off the stack, false otherwise
    bool popContext();

    /// Handle a SDL Event and attept to map it to a input event
    /// @param event The SDL Event to handle
    void handleEvent(const SDL_Event& event);

    /// @name IInputProducer Overrides
    /// @{
    void subscribe(InputConsumer* inputConsumer) override;
    void unsubscribe(InputConsumer* inputConsumer) override;
    /// @}

private:
    std::shared_ptr<BindingContext> topContext();
    void handleKeyboardEvent(const SDL_KeyboardEvent& event);
    void handleMouseButtonEvent(const SDL_MouseButtonEvent& event);
    void handleMouseMotionEvent(const SDL_MouseMotionEvent& event);
    template <typename EventT>
    void notifyAll(const EventT& event);

    std::vector<InputConsumer*> _inputConsumers;
    std::deque<std::weak_ptr<BindingContext>> _contexts;
};

} // namespace frontier
