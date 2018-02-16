#pragma once

namespace frontier {

class Command {
public:
    virtual ~Command() = default;

    /// Execute the command.
    virtual void execute() = 0;
};

} // namespace frontier
