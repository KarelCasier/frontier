#include <frontier/components/InputComponent.hpp>

#include <log/log.hpp>

namespace frontier {

InputComponent::InputComponent() = default;

void InputComponent::bindActionCallback(const std::string& action, ActionCallback callback)
{
    actionCallbacks[action].push_back(std::move(callback));
}

void InputComponent::bindMouseCallback(const std::string& action, MouseCallback callback)
{
    mouseButtonCallbacks[action].push_back(std::move(callback));
}

void InputComponent::bindMouseMotionCallback(const std::string& action, MouseCallback callback)
{
    mouseMotionCallbacks[action].push_back(std::move(callback));
}

void InputComponent::handleInputEvent(const ActionEvent& event)
{
    for (const auto& callback : actionCallbacks[event.action]) {
        callback();
    }
}

void InputComponent::handleInputEvent(const MouseEvent& event)
{
    for (const auto& callback : mouseButtonCallbacks[event.action]) {
        callback(event.x, event.y);
    }
}

void InputComponent::handleInputEvent(const MouseMotionEvent& event)
{
    for (const auto& callback : mouseMotionCallbacks[event.action]) {
        callback(event.x, event.y);
    }
}

} // namespace frontier
