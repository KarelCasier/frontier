#include <frontier/components/UserInputComponent.hpp>

namespace {

using namespace entityx;

enum class Direction {
    UP,
    LEFT,
    DOWN,
    RIGHT,
};

}

namespace frontier {

using namespace entityx;

void UserInputComponent::handleInput(const SDL_Event& event, Entity& entity)
{
    switch (event.type) {
    case SDL_KEYDOWN:
        break;
    default:
        break;
    }
}

} // namespace frontier
