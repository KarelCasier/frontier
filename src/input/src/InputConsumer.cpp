#include <input/InputConsumer.hpp>
#include <input/IInputProducer.hpp>
#include <log/log.hpp>

namespace frontier {

InputConsumer::InputConsumer(std::shared_ptr<IInputProducer> inputProducer)
: _inputProducer{std::move(inputProducer)}
{
    _inputProducer->subscribe(this);
}

InputConsumer::~InputConsumer()
{
    _inputProducer->unsubscribe(this);
}

} // namespace frontier
