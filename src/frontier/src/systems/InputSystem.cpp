#include <frontier/systems/InputSystem.hpp>

#include <frontier/components/InputComponent.hpp>
#include <log/log.hpp>

namespace frontier {

using namespace entityx;

InputSystem::InputSystem(std::shared_ptr<IInputProducer> inputProducer)
: InputConsumer{std::move(inputProducer)}
{
}

void InputSystem::update(entityx::EntityManager& entities,
                         entityx::EventManager& /* events */,
                         entityx::TimeDelta /* dt */)
{
    ComponentHandle<InputComponent> input;

    for (const auto& event : _actionEvents) {
        for (auto entity : entities.entities_with_components(input)) {
            (void)entity; // no unused warn
            input->handleInputEvent(event);
        }
    }
    _actionEvents.clear();

    for (const auto& event : _mouseEvents) {
        for (auto entity : entities.entities_with_components(input)) {
            (void)entity; // no unused warn
            input->handleInputEvent(event);
        }
    }
    _mouseEvents.clear();
}

void InputSystem::receive(const ActionEvent& event)
{
    _actionEvents.push_back(event);
}

void InputSystem::receive(const MouseEvent& event)
{
    _mouseEvents.push_back(event);
}

} // namespace frontier
