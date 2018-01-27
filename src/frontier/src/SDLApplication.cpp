#include <frontier/SDLApplication.hpp>

#include <iostream>

#include <log/log.hpp>

namespace frontier {

using std::stringstream;

SDLApplication::SDLApplication(const char* title, int x, int y, int w, int h, Uint32 flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        const auto err = stringstream{} << "SDL_Init Error: " << SDL_GetError();
        LOGE << err.str();
        throw std::runtime_error(err.str());
    }

    _window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (_window == nullptr) {
        const auto err = stringstream{} << "SDL_CreateWindow Error: " << SDL_GetError();
        LOGE << err.str();
        throw std::runtime_error(err.str());
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr) {
        const auto err = stringstream{} << "SDL_CreateRenderer Error: " << SDL_GetError();
        LOGE << err.str();
        throw std::runtime_error(err.str());
    }
    _textureManager = std::make_shared<TextureManager>(_renderer);
}

SDLApplication::~SDLApplication()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
    if (_window) {
        SDL_DestroyWindow(_window);
    }
    SDL_Quit();
}

} // namespace frontier
