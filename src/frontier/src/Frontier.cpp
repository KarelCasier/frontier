#include <frontier/Frontier.hpp>

#include "config.hpp"

namespace frontier {

Frontier::Frontier(std::unique_ptr<TextureManager>)
: SDLApplication("Frontier",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)
{
}

int Frontier::exec() {
    SDL_Delay(10000);
    return 0;
}

} // namespace frontier
