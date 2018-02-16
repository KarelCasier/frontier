#pragma once

#include <SDL2/SDL_events.h>
#include <entityx/Entity.h>

namespace frontier {

/// TODO: Key bindings
struct UserInputComponent {

    void handleInput(const SDL_Event& event, entityx::Entity& entity);
};

} // namespace frontier
