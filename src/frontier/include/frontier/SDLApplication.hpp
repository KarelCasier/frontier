#pragma once

#include <SDL2/SDL.h>

namespace frontier {

class SDLApplication {
public:
    SDLApplication(const char* title, int x, int y, int w, int h, Uint32 flags);
    virtual ~SDLApplication();

    virtual int exec() = 0;

protected:
    SDL_Window* _window{nullptr};
    SDL_Renderer* _renderer{nullptr};
};

} // namespace frontier
