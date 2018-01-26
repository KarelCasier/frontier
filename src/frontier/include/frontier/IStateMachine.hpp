#pragma once

#include <memory>
#include <chrono>

#include "IState.hpp"

namespace frontier {

class IStateMachine {
public:
    virtual ~IStateMachine() = default;

    /// Push a state onto the stack.
    ///
    /// @param state The state to push onto the stack.
    /// @param immediate Signals to do this action immediately.
    virtual void push(std::shared_ptr<IState> state, bool immediate = false) = 0;

    /// Pop a state off the stack.
    ///
    /// @param immediate Signals to do this action immediately.
    virtual void pop(bool immediate = false) = 0;

    /// Replace the top state with another.
    ///
    /// @param immediate Signals to do this action immediately.
    virtual void replace(std::shared_ptr<IState> state, bool immediate = false) = 0;

    /// Clear all states from the stack.
    virtual void clear() = 0;

    /// Trigger the state to update.
    ///
    /// @param delta The time delta since last update.
    virtual void update(std::chrono::milliseconds delta) = 0;

    /// Trigger the state to render.
    virtual void render() = 0;

    /// Trigger the state to handle a event.
    ///
    /// @param event The event to handle.
    virtual void handleEvent(const SDL_Event& event) = 0;

    /// Check if the state machine is empty.
    ///
    /// @returns true if the state machine is empty, false otherwise.
    virtual bool empty() const = 0;
};

} // namespace frontier
