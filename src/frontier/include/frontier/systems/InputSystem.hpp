#pragma once

#include <entityx/entityx.h>
#include <input/InputConsumer.hpp>
#include <input/IInputProducer.hpp>
#include <vector>

namespace frontier {

class InputSystem : public entityx::System<InputSystem>, public InputConsumer {
public:
    InputSystem(std::shared_ptr<IInputProducer> inputManager);
    ~InputSystem() override = default;

    /// @name System overrides
    /// @{
    void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
    /// @}

    /// @name InputConsumer Overrides
    /// @{
    void receive(const ActionEvent& event) override;
    void receive(const MouseEvent& event) override;
    /// @}

private:
    std::vector<ActionEvent> _actionEvents;
    std::vector<MouseEvent> _mouseEvents;
};


} // namespace frontier
