#pragma once

#include <entityx/Event.h>

namespace frontier {

class Command {
public:
    virtual ~Command() = default;

    /// Execute the command.
    ///
    /// @param eventManager The event manager that allows for event injection.
    virtual void execute(entityx::EventManager& eventManager) = 0;
};

} // namespace frontier
