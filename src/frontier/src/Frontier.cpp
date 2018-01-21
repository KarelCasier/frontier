#include <frontier/Frontier.hpp>

#include "config.hpp"

namespace frontier {

Frontier::Frontier()
: SDLApplication(
      "Frontier", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)
{
}

int Frontier::exec()
{
    auto textureRef = _textureManager->loadTexture("Test.png");
    SDL_RenderClear(_renderer);
    // Draw the texture
    SDL_RenderCopy(_renderer, textureRef->texture(), NULL, NULL);
    // Update the screen
    SDL_RenderPresent(_renderer);
    SDL_Delay(10000);
    return 0;
}

} // namespace frontier
