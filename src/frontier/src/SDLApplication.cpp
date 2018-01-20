#include <frontier/SDLApplication.hpp>

#include <iostream>

#include <log/log.hpp>

namespace frontier {

SDLApplication::SDLApplication() {}

SDLApplication::~SDLApplication() {}

int SDLApplication::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOGE << "SDL_Init Error: " << SDL_GetError();
        return 1;
    }
    return 0;
}

int SDLApplication::exec() {
    return 0;
}

} // namespace frontier
