#pragma once

#include <memory>
#include <SDL2/SDL.h>

#include <texture_manager/TextureManager.hpp>

namespace frontier {

class SDLApplication {
public:
    SDLApplication(const char* title, int x, int y, int w, int h, Uint32 flags);
    virtual ~SDLApplication();

    virtual int exec() = 0;

protected:
    SDL_Window* _window{nullptr};
    SDL_Renderer* _renderer{nullptr};
    std::unique_ptr<TextureManager> _textureManager;
};

} // namespace frontier
