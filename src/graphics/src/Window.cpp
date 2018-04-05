#include <graphics/Window.hpp>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_opengl.h>

#include <sstream>
#include <stack>

#include <graphics/IRenderable.hpp>
#include <graphics/TextureRef.hpp>
#include <log/log.hpp>
#include <math/Misc.hpp>
#include <math/Printers.hpp>

namespace {

SDL_Rect toSDLRect(const Recti& rect)
{
    return {rect.x(), rect.y(), rect.w(), rect.h()};
}

/// [[[ SDLRenderColorState ---------------------------------------------------

class SDLRenderColorState {
public:
    SDLRenderColorState(SDL_Renderer* renderer);

    void push();
    void pop();
    void set(const Color& color);

private:
    SDL_Renderer* _renderer;
    std::stack<Color> _colorState;
};

SDLRenderColorState::SDLRenderColorState(SDL_Renderer* renderer)
: _renderer{renderer}
{
}

void SDLRenderColorState::push()
{
    auto color = Color{};
    SDL_GetRenderDrawColor(_renderer, &color.r, &color.g, &color.b, &color.a);
    _colorState.emplace(std::move(color));
}

void SDLRenderColorState::pop()
{
    assert(!_colorState.empty());
    set(_colorState.top());
    _colorState.pop();
}

void SDLRenderColorState::set(const Color& color)
{
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}

/// ]]] SDLRenderColorState ---------------------------------------------------

} // namespace

namespace frontier {

Window::Window(const std::string& title, int32_t x, int32_t y, int32_t width, int32_t height)
: _camera{{0, 0}, {0, 0}}
{
    _window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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

    _camera = createSizedCamera();
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
    render(_camera, texture, srcRect, destRect, rotation, origin);
}

void Window::render(const Camera& camera,
                    const TextureRef* texture,
                    const Recti& srcRect,
                    const Recti& destRect,
                    const double rotation,
                    const std::optional<Vector2i> origin)
{
    assert(texture);

    const auto topLeft = cameraToScreen(static_cast<Vector2f>(destRect.position()), camera);
    const auto bottomRight = cameraToScreen(static_cast<Vector2f>(destRect.position() + destRect.dimensions()), camera);
    const auto destRectOffset = Recti{topLeft, bottomRight - topLeft};

    SDL_Point sdlOrigin;
    if (origin) {
        sdlOrigin.x = origin->x();
        sdlOrigin.y = origin->y();
    }
    const auto sdlSrcRect = toSDLRect(srcRect);
    const auto sdlDestRect = toSDLRect(destRectOffset);

    SDL_RenderCopyEx(_renderer, texture->texture(), &sdlSrcRect, &sdlDestRect, toDegrees(rotation),
                     origin ? &sdlOrigin : NULL, SDL_FLIP_NONE);
}

void Window::render(const std::vector<Vector2f>& vertices, PrimativeType type, const Color& color)
{
    render(_camera, vertices, type, color);
}

void Window::render(const Camera& camera, const std::vector<Vector2f>& vertices, PrimativeType type, const Color& color)
{
    switch (type) {
    case PrimativeType::Points:
        renderPoints(camera, vertices, color);
        break;
    case PrimativeType::LineStrip:
        renderLineStrip(camera, vertices, color);
        break;
    }
}

void Window::renderPoints(const Camera& camera, const std::vector<Vector2f>& vertices, const Color& color)
{
    std::vector<SDL_Point> sdlPoints{};
    std::transform(std::begin(vertices), std::end(vertices), std::back_inserter(sdlPoints),
                   [this, &camera](const Vector2f& vec) -> SDL_Point {
                       auto screenPt = cameraToScreen({vec.x(), vec.y()}, camera);
                       return {screenPt.x(), screenPt.y()};
                   });
    auto colorState = SDLRenderColorState{_renderer};
    colorState.push();
    colorState.set(color);
    SDL_RenderDrawPoints(_renderer, sdlPoints.data(), sdlPoints.size());
    colorState.pop();
}

void Window::renderLineStrip(const Camera& camera, const std::vector<Vector2f>& vertices, const Color& color)
{
    std::vector<SDL_Point> sdlPoints{};
    std::transform(std::begin(vertices), std::end(vertices), std::back_inserter(sdlPoints),
                   [this, &camera](const Vector2f& vec) -> SDL_Point {
                       auto screenPt = cameraToScreen({vec.x(), vec.y()}, camera);
                       return {screenPt.x(), screenPt.y()};
                   });
    auto colorState = SDLRenderColorState{_renderer};
    colorState.push();
    colorState.set(color);
    SDL_RenderDrawLines(_renderer, sdlPoints.data(), sdlPoints.size());
    colorState.pop();
}

void Window::render(IRenderable& renderable)
{
    renderable.render(*this);
}

Vector2f Window::screenToCamera(const Vector2i& screenPoint) const
{
    return screenToCamera(screenPoint, getCamera());
}

Vector2i Window::cameraToScreen(const Vector2f& cameraPoint) const
{
    return cameraToScreen(cameraPoint, getCamera());
}

Vector2f Window::screenToCamera(const Vector2i& screenPoint, const Camera& camera) const
{
    const auto windowSize = static_cast<Vector2f>(size());
    auto normalized = Vector2f{};
    normalized.x(-1.f + 2.f * (screenPoint.x()) / windowSize.x());
    normalized.y(1.f - 2.f * (screenPoint.y()) / windowSize.y());
    return camera.inverseTransform().transformPoint(normalized);
}

Vector2i Window::cameraToScreen(const Vector2f& cameraPoint, const Camera& camera) const
{
    const auto windowSize = static_cast<Vector2f>(size());
    const auto normalized = camera.transform().transformPoint(cameraPoint);
    auto pixel = Vector2i{};
    pixel.x(static_cast<int>(std::round((normalized.x() + 1.f) / 2.f * windowSize.x())));
    pixel.y(static_cast<int>(std::round((-normalized.y() + 1.f) / 2.f * windowSize.y())));
    return pixel;
}

void Window::setCamera(const Camera& camera)
{
    _camera = camera;
}

const Camera& Window::getCamera() const
{
    return _camera;
}

Camera Window::createSizedCamera() const
{
    const auto windowSize = size();
    return {static_cast<Rectf>(Recti{0, 0, windowSize.x(), windowSize.y()})};
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
