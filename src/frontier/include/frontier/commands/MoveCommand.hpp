#pragma once

#include <entityx/Entity.h>
#include "Command.hpp"

namespace frontier {

class MoveCommand : public Command {
public:
    MoveCommand(entityx::Entity entity);

}

}
