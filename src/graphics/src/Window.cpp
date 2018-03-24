#include <graphics/Window.hpp>

#include <SDL2/SDL_render.h>

#include <sstream>

#include <graphics/IRenderable.hpp>
#include <graphics/TextureRef.hpp>
#include <log/log.hpp>
#include <math/Misc.hpp>

namespace {

SDL_Rect toSDLRect(const Recti& rect)
{
    return {rect.x(), rect.y(), rect.w(), rect.h()};
}

} // namespace

namespace frontier {

Window::Window(const std::string& title, int32_t x, int32_t y, int32_t width, int32_t height)
{
    _window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
    if (_window == nullptr) {
        const auto err = std::stringstream{} << "Error creating window: " << SDL_GetError();
        LOGE << err.str();
        throw std::runtime_error(err.str());
    }
    _id = SDL_GetWindowID(_window);

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr) {
        const auto err = std::stringstream{} << "SDL_CreateRenderer Error: " << SDL_GetError();
        LOGE << err.str();
        throw std::runtime_error(err.str());
    }
}

Window::~Window()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
    if (_window) {
        SDL_DestroyWindow(_window);
    }
}

void Window::preRender()
{
    SDL_RenderClear(_renderer);
}

void Window::postRender()
{
    SDL_RenderPresent(_renderer);
}

void Window::render(const TextureRef* texture,
                    const Recti& srcRect,
                    const Recti& destRect,
                    const double rotation,
                    const std::optional<Vector2i> origin)
{
    assert(texture);

    SDL_Point sdlOrigin;
    if (origin) {
        sdlOrigin.x = origin->x();
        sdlOrigin.y = origin->y();
    }
    auto sdlSrcRect = toSDLRect(srcRect);
    auto sdlDestRect = toSDLRect(destRect);

    SDL_RenderCopyEx(_renderer, texture->texture(), &sdlSrcRect, &sdlDestRect, toDegrees(rotation),
                     origin ? &sdlOrigin : NULL, SDL_FLIP_NONE);
}

void Window::render(const Camera& /*camera*/,
                    const TextureRef* /*texture*/,
                    const Recti& /*srcRect*/,
                    const Recti& /*destRect*/,
                    const double /*rotation*/,
                    const std::optional<Vector2i> /*origin*/)
{
    throw std::logic_error{"Unimplemented"};
    // assert(texture);
    // auto offsetDestRect = SDL_Rect{};
    // const auto cameraBounds = camera.bounds();
    // offsetDestRect.x = cameraBounds.x();
    // offsetDestRect.y = cameraBounds.y();
    //
    // offsetDestRect.w = cameraDimensions.x();
    // offsetDestRect.h = cameraDimensions.y();
    // render(texture, srcRect, offsetDestRect, rotation, origin);
}

void Window::render(IRenderable& renderable)
{
    renderable.render(*this);
}

Vector2i Window::position() const
{
    int x, y;
    SDL_GetWindowPosition(_window, &x, &y);
    return {x, y};
}

Vector2i Window::size() const
{
    int x, y;
    SDL_GetWindowSize(_window, &x, &y);
    return {x, y};
}

uint32_t Window::id() const
{
    return _id;
}

bool Window::focused() const
{
    return _focused;
}

bool Window::shown() const
{
    return _shown;
}

bool Window::closed() const
{
    return _closed;
}

SDL_Window* Window::getSDLWindow() const
{
    return _window;
}

SDL_Renderer* Window::getSDLRenderer() const
{
    return _renderer;
}

void Window::handleWindowEvent(SDL_Event& event)
{
    if (event.type == SDL_WINDOWEVENT && event.window.windowID == _id) {
        switch (event.window.type) {
        case SDL_WINDOWEVENT_SHOWN:
            _shown = true;
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            _shown = true;
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            _focused = true;
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            _focused = false;
            break;
        case SDL_WINDOWEVENT_CLOSE:
            _closed = true;
            SDL_HideWindow(_window);
        default:
            break;
        }
    }
}

} // namespace frontier
