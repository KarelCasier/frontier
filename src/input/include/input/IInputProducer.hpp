#pragma once

#include <memory>

namespace frontier {

class InputConsumer;

/// Interface for allowing subscription to input events
class IInputProducer {
public:
    virtual ~IInputProducer() = default;

    /// Subscribe to input events
    /// @param inputConsumer The input consumer to subscribe to input events
    virtual void subscribe(InputConsumer* inputConsumer) = 0;
    /// Unsubscribe to input events
    /// @param inputConsumer The input consumer to unsubscribe to input events
    virtual void unsubscribe(InputConsumer* inputConsumer) = 0;
};

} // namespace frontier
