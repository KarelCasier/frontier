#pragma once

#include <input/InputEvent.hpp>

namespace frontier {

/// Interface to receive events
class IInputConsumer {
public:
    virtual ~IInputConsumer() = default;

    /// Receive an action event
    /// @param event The input event to receive
    virtual void receive(const ActionEvent& event) = 0;

    /// Receive a mouse event
    /// @param event The mouse event to receive
    virtual void receive(const MouseEvent& event) = 0;

    /// Receive a mouse motion event
    /// @param event The mouse motion event to receive
    virtual void receive(const MouseMotionEvent& event) = 0;
};

} // namespace frontier
