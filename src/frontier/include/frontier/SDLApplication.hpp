#pragma once

#include <memory>
#include <SDL2/SDL.h>

namespace frontier {

class RenderManager;
class TextureManager;
class InputManager;

class SDLApplication {
public:
    SDLApplication(const char* title, int x, int y, int w, int h, Uint32 flags);
    virtual ~SDLApplication();

    virtual int exec() = 0;

protected:
    SDL_Window* _window{nullptr};
    SDL_Renderer* _renderer{nullptr};
    std::shared_ptr<RenderManager> _renderManager;
    std::shared_ptr<TextureManager> _textureManager;
    std::shared_ptr<InputManager> _inputManager;
};

} // namespace frontier
