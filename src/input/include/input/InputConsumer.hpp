#pragma once

#include <memory>
#include <input/InputEvent.hpp>
#include <input/IInputConsumer.hpp>

namespace frontier {

class IInputProducer;

/// Helper class that auto subcribes to a consumer on construction and unsubscribes on destruction
class InputConsumer : public IInputConsumer {
public:
    /// Construct a input consumer that subscribes to a producer
    /// @param inputProducer The input producer to subscribe to
    InputConsumer(std::shared_ptr<IInputProducer> inputProducer);
    virtual ~InputConsumer();

    /// @name IInputConsumer overrides
    /// @{
    void receive(const ActionEvent& event) override = 0;
    void receive(const MouseEvent& event) override = 0;
    /// @}

private:
    std::shared_ptr<IInputProducer> _inputProducer;
};

} // namespace frontier
